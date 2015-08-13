/* Manages interpreters for GDB, the GNU debugger.

   Copyright (C) 2000-2015 Free Software Foundation, Inc.

   Written by Jim Ingham <jingham@apple.com> of Apple Computer, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* This is just a first cut at separating out the "interpreter"
   functions of gdb into self-contained modules.  There are a couple
   of open areas that need to be sorted out:

   1) The interpreter explicitly contains a UI_OUT, and can insert itself
   into the event loop, but it doesn't explicitly contain hooks for readline.
   I did this because it seems to me many interpreters won't want to use
   the readline command interface, and it is probably simpler to just let
   them take over the input in their resume proc.  */

#include "defs.h"
#include "gdbcmd.h"
#include "ui-out.h"
#include "event-loop.h"
#include "event-top.h"
#include "interps.h"
#include "completer.h"
#include "top.h"		/* For command_loop.  */
#include "continuations.h"
#include "terminal.h"
#include "observer.h"

/* True if the current interpreter in is async mode.  See interps.h
   for more details.  This starts out disabled, until all the explicit
   command line arguments (e.g., `gdb -ex "start" -ex "next"') are
   processed.  */
int interpreter_async = 0;

struct interp_factory
{
  /* This is the name in "-i=" and set interpreter.  */
  const char *name;

  interp_factory_func func;
};

typedef struct interp_factory *interp_factory_p;
DEF_VEC_P(interp_factory_p);

VEC(interp_factory_p) *interpreter_factories = NULL;

void
interp_factory_register (const char *name, interp_factory_func func)
{
  struct interp_factory *f = XNEW (struct interp_factory);

  f->name = name;
  f->func = func;

  /* FIXME: assert that no factory for NAME is already registered.  */
  VEC_safe_push (interp_factory_p, interpreter_factories, f);
}

struct interp *
interp_lookup (struct terminal *terminal, const char *name)
{
  struct interp *interp;
  int ix;

  /* Only create each interpreter once per terminal.  */
  for (ix = 0;
       VEC_iterate (interp_ptr, terminal->interpreters, ix, interp);
       ++ix)
    if (strcmp (interp->name, name) == 0)
      return interp;

  return NULL;
}

static void interp_add (struct terminal *terminal, struct interp *interp);

struct interp *
interp_create (const char *name, struct terminal *terminal)
{
  struct interp_factory *factory;
  struct interp *interp;
  int ix;

  /* Only create each interpreter once per terminal.  */
  interp = interp_lookup (terminal, name);
  if (interp != NULL)
    return interp;

  for (ix = 0;
       VEC_iterate (interp_factory_p, interpreter_factories, ix, factory);
       ++ix)
    if (strcmp (factory->name, name) == 0)
      {
	interp = factory->func (name, terminal);
	interp_add (terminal, interp);
	return interp;
      }

  return NULL;
}

/* The magic initialization routine for this module.  */

void _initialize_interpreter (void);

/* Variables local to this file: */

struct interp *interp_list = NULL;
struct interp *current_interpreter = NULL;
struct interp *top_level_interpreter_ptr = NULL;

/* interp_ctor - This fills the fields from the inputs.  */

void
interp_ctor (struct interp *self,
	     const char *name, const struct interp_procs *procs,
	     struct terminal *terminal)
{
  self->name = xstrdup (name);
  self->data = NULL;
  self->quiet_p = 0;
  self->procs = procs;
  self->inited = 0;
  self->terminal = terminal;

  /* Check for required procs.  */
  gdb_assert (procs->command_loop_proc != NULL);
}

/* interp_new - This allocates space for a new interpreter,
   fills the fields from the inputs, and returns a pointer to the
   interpreter.  */

struct interp *
interp_new (const char *name, const struct interp_procs *procs,
	    struct terminal *terminal)
{
  struct interp *new_interp;

  new_interp = XNEW (struct interp);
  interp_ctor (new_interp, name, procs, terminal);
  return new_interp;
}

/* Add interpreter INTERP to both gdb interpreter list, and to the
   terminal's interpreter VEC.  The interpreter with this name must
   not have previously been added to this terminal.  */

static void
interp_add (struct terminal *terminal, struct interp *interp)
{
  gdb_assert (interp_lookup (terminal, interp->name) == NULL);
  VEC_safe_push (interp_ptr, terminal->interpreters, interp);

  interp->next = interp_list;
  interp_list = interp;
}

#if 0

/// XXX call these when the terminal is removed.  Note that thread's
/// also have a reference to interpreters (through
/// command_interpreter).

static void
interp_remove (struct interp *todel)
{
  struct interp *interp, *prev;

  prev = NULL;

  for (interp = interp_list;
       interp != NULL;
       prev = interp, interp = interp->next)
    if (interp == todel)
      break;

  if (prev != NULL)
    prev->next = interp->next;
  else
    interp_list = interp->next;
}

/* Add interpreter INTERP to the gdb interpreter list.  The
   interpreter must not have previously been added.  */
static void
interp_delete (struct interp *interp)
{
  /* FIXME: should call dtor method.  */
  xfree (interp);
}
#endif

/* This sets the current interpreter to be INTERP.  If INTERP has not
   been initialized, then this will also run the init proc.  If the
   init proc is successful, return 1, if it fails, set the old
   interpreter back in place and return 0.  If we can't restore the
   old interpreter, then raise an internal error, since we are in
   pretty bad shape at this point.

   The TOP_LEVEL parameter tells if this new interpreter is
   the top-level one.  The top-level is what is requested
   on the command line, and is responsible for reporting general
   notification about target state changes.  For example, if
   MI is the top-level interpreter, then it will always report
   events such as target stops and new thread creation, even if they
   are caused by CLI commands.  */
int
interp_set (struct interp *interp, int top_level)
{
  struct interp *old_interp = current_interpreter;
  int first_time = 0;
  char buffer[64];

  /* If we already have an interpreter, then trying to
     set top level interpreter is kinda pointless.  */
  gdb_assert (!top_level || !current_interpreter);
  gdb_assert (!top_level || !top_level_interpreter_ptr);

  if (current_interpreter != NULL)
    {
      ui_out_flush (current_uiout);
      if (current_interpreter->procs->suspend_proc
	  && !current_interpreter->procs->suspend_proc (current_interpreter))
	{
	  error (_("Could not suspend interpreter \"%s\"."),
		 current_interpreter->name);
	}
    }
  else
    {
      first_time = 1;
    }

  current_interpreter = interp;
  if (top_level)
    top_level_interpreter_ptr = interp;

  /* We use interpreter_p for the "set interpreter" variable, so we need
     to make sure we have a malloc'ed copy for the set command to free.  */
  if (interpreter_p != NULL
      && strcmp (current_interpreter->name, interpreter_p) != 0)
    {
      xfree (interpreter_p);

      interpreter_p = xstrdup (current_interpreter->name);
    }

  /* Run the init proc.  If it fails, try to restore the old interp.  */

  if (!interp->inited)
    {
      if (interp->procs->init_proc != NULL)
	{
	  interp->data = interp->procs->init_proc (interp, top_level);
	}
      interp->inited = 1;
    }

  /* Do this only after the interpreter is initialized.  */
  current_uiout = interp->procs->ui_out_proc (interp);

  /* Clear out any installed interpreter hooks/event handlers.  */
  clear_interpreter_hooks ();

  if (interp->procs->resume_proc != NULL
      && (!interp->procs->resume_proc (interp)))
    {
      if (old_interp == NULL || !interp_set (old_interp, 0))
	internal_error (__FILE__, __LINE__,
			_("Failed to initialize new interp \"%s\" %s"),
			interp->name, "and could not restore old interp!\n");
      return 0;
    }

  if (!first_time && !interp_quiet_p (interp))
    {
      xsnprintf (buffer, sizeof (buffer),
		 "Switching to interpreter \"%.24s\".\n", interp->name);
      ui_out_text (current_uiout, buffer);
    }

  return 1;
}

/* Returns the current interpreter.  */

struct ui_out *
interp_ui_out (struct interp *interp)
{
  if (interp != NULL)
    return interp->procs->ui_out_proc (interp);

  return current_interpreter->procs->ui_out_proc (current_interpreter);
}

int
current_interp_set_logging (int start_log, struct ui_file *out,
			    struct ui_file *logfile)
{
  if (current_interpreter == NULL
      || current_interpreter->procs->set_logging_proc == NULL)
    return 0;

  return current_interpreter->procs->set_logging_proc (current_interpreter,
						       start_log, out,
						       logfile);
}

/* Returns the interpreter's cookie.  */

void *
interp_data (struct interp *interp)
{
  return interp->data;
}

/* Returns the interpreter's name.  */

const char *
interp_name (struct interp *interp)
{
  return interp->name;
}

/* Returns true if the current interp is the passed in name.  */
int
current_interp_named_p (const char *interp_name)
{
  if (current_interpreter)
    return (strcmp (current_interpreter->name, interp_name) == 0);

  return 0;
}

/* The interpreter that is active while `interp_exec' is active, NULL
   at all other times.  */
static struct interp *command_interpreter;

/* The interpreter that was active when a command was executed.
   Normally that'd always be CURRENT_INTERPRETER, except that MI's
   -interpreter-exec command doesn't actually flip the current
   interpreter when running its sub-command.  The
   `command_interpreter' global tracks when interp_exec is called
   (IOW, when -interpreter-exec is called).  If that is set, it is
   INTERP in '-interpreter-exec INTERP "CMD"' or in 'interpreter-exec
   INTERP "CMD".  Otherwise, interp_exec isn't active, and so the
   interpreter running the command is the current interpreter.  */

struct interp *
command_interp (void)
{
  if (command_interpreter != NULL)
    return command_interpreter;
  else
    return current_interpreter;
}

/* Run the current command interpreter's main loop.  */
void
current_interp_command_loop (void)
{
  gdb_assert (current_interpreter != NULL);

  current_interpreter->procs->command_loop_proc (current_interpreter->data);
}

int
interp_quiet_p (struct interp *interp)
{
  if (interp != NULL)
    return interp->quiet_p;
  else
    return current_interpreter->quiet_p;
}

static int
interp_set_quiet (struct interp *interp, int quiet)
{
  int old_val = interp->quiet_p;

  interp->quiet_p = quiet;
  return old_val;
}

/* interp_exec - This executes COMMAND_STR in the current 
   interpreter.  */

struct gdb_exception
interp_exec (struct interp *interp, const char *command_str)
{
  struct gdb_exception ex;
  struct interp *save_command_interp;

  gdb_assert (interp->procs->exec_proc != NULL);

  /* See `command_interp' for why we do this.  */
  save_command_interp = command_interpreter;
  command_interpreter = interp;

  ex = interp->procs->exec_proc (interp, command_str);

  command_interpreter = save_command_interp;

  return ex;
}

/* A convenience routine that nulls out all the common command hooks.
   Use it when removing your interpreter in its suspend proc.  */
void
clear_interpreter_hooks (void)
{
  deprecated_print_frame_info_listing_hook = 0;
  /*print_frame_more_info_hook = 0; */
  deprecated_query_hook = 0;
  deprecated_warning_hook = 0;
  deprecated_interactive_hook = 0;
  deprecated_readline_begin_hook = 0;
  deprecated_readline_hook = 0;
  deprecated_readline_end_hook = 0;
  deprecated_context_hook = 0;
  deprecated_target_wait_hook = 0;
  deprecated_call_command_hook = 0;
  deprecated_error_begin_hook = 0;
}

static void
interpreter_exec_cmd (char *args, int from_tty)
{
  struct interp *old_interp, *interp_to_use;
  char **prules = NULL;
  char **trule = NULL;
  unsigned int nrules;
  unsigned int i;
  int old_quiet, use_quiet;
  struct cleanup *cleanup;

  if (args == NULL)
    error_no_arg (_("interpreter-exec command"));

  prules = gdb_buildargv (args);
  cleanup = make_cleanup_freeargv (prules);

  nrules = 0;
  for (trule = prules; *trule != NULL; trule++)
    nrules++;

  if (nrules < 2)
    error (_("usage: interpreter-exec <interpreter> [ <command> ... ]"));

  old_interp = current_interpreter;

  /* FIXME: leaking interpreter.  */
  interp_to_use = interp_create (prules[0], current_terminal);
  if (interp_to_use == NULL)
    error (_("Could not find interpreter \"%s\"."), prules[0]);

  /* Temporarily set interpreters quiet.  */
  old_quiet = interp_set_quiet (old_interp, 1);
  use_quiet = interp_set_quiet (interp_to_use, 1);

  if (!interp_set (interp_to_use, 0))
    error (_("Could not switch to interpreter \"%s\"."), prules[0]);

  for (i = 1; i < nrules; i++)
    {
      struct gdb_exception e = interp_exec (interp_to_use, prules[i]);

      if (e.reason < 0)
	{
	  interp_set (old_interp, 0);
	  interp_set_quiet (interp_to_use, use_quiet);
	  interp_set_quiet (old_interp, old_quiet);
	  error (_("error in command: \"%s\"."), prules[i]);
	}
    }

  interp_set (old_interp, 0);
  interp_set_quiet (interp_to_use, use_quiet);
  interp_set_quiet (old_interp, old_quiet);

  do_cleanups (cleanup);
}

/* List the possible interpreters which could complete the given text.  */
static VEC (char_ptr) *
interpreter_completer (struct cmd_list_element *ignore,
		       const char *text, const char *word)
{
  int textlen;
  VEC (char_ptr) *matches = NULL;
  struct interp *interp;

  textlen = strlen (text);
  ALL_INTERPS (interp)
    {
      if (strncmp (interp->name, text, textlen) == 0)
	{
	  char *match;

	  match = (char *) xmalloc (strlen (word) + strlen (interp->name) + 1);
	  if (word == text)
	    strcpy (match, interp->name);
	  else if (word > text)
	    {
	      /* Return some portion of interp->name.  */
	      strcpy (match, interp->name + (word - text));
	    }
	  else
	    {
	      /* Return some of text plus interp->name.  */
	      strncpy (match, word, text - word);
	      match[text - word] = '\0';
	      strcat (match, interp->name);
	    }
	  VEC_safe_push (char_ptr, matches, match);
	}
    }

  return matches;
}

struct interp *
top_level_interpreter (void)
{
  return top_level_interpreter_ptr;  
}

void *
top_level_interpreter_data (void)
{
  gdb_assert (top_level_interpreter_ptr);
  return top_level_interpreter_ptr->data;  
}

#define GEN_INTERP_CALL(method, params, args)				\
static void								\
interp_ ## method params						\
{									\
  struct interp *interp;						\
  struct interp *prev_interp = current_interpreter;			\
  struct terminal *prev_terminal = current_terminal;			\
									\
  ALL_INTERPS (interp)							\
    {									\
      if (interp_quiet_p (interp))					\
	continue;							\
									\
      if (interp->procs-> method != NULL)				\
	{								\
	  struct interp *prev_interp;					\
									\
	  switch_to_terminal (interp->terminal);			\
									\
	  prev_interp = current_interpreter;				\
	  current_interpreter = interp;					\
	  interp->procs-> method args;					\
	  current_interpreter = prev_interp;				\
	}								\
    }									\
									\
  switch_to_terminal (prev_terminal);					\
  current_interpreter = prev_interp;					\
}

GEN_INTERP_CALL (on_normal_stop, (struct bpstats *bs,
				  int print_frame), (bs, print_frame))
GEN_INTERP_CALL (on_signal_received, (enum gdb_signal siggnal), (siggnal))
GEN_INTERP_CALL (on_end_stepping_range, (void), ())
GEN_INTERP_CALL (on_signal_exited, (enum gdb_signal siggnal), (siggnal))
GEN_INTERP_CALL (on_exited, (int exitstatus), (exitstatus))
GEN_INTERP_CALL (on_no_history, (void), ())
GEN_INTERP_CALL (on_sync_execution_done, (void), ())
GEN_INTERP_CALL (on_new_thread, (struct thread_info *t), (t))
GEN_INTERP_CALL (on_thread_exit,
		 (struct thread_info *t, int silent), (t, silent))
GEN_INTERP_CALL (on_target_resumed, (ptid_t ptid), (ptid))
GEN_INTERP_CALL (on_about_to_proceed, (void), ())
GEN_INTERP_CALL (on_breakpoint_created, (struct breakpoint *b), (b))
GEN_INTERP_CALL (on_breakpoint_deleted, (struct breakpoint *b), (b))
GEN_INTERP_CALL (on_breakpoint_modified, (struct breakpoint *b), (b))
GEN_INTERP_CALL (on_inferior_added, (struct inferior *inf), (inf))
GEN_INTERP_CALL (on_inferior_appeared, (struct inferior *inf), (inf))
GEN_INTERP_CALL (on_inferior_exit, (struct inferior *inf), (inf))
GEN_INTERP_CALL (on_inferior_removed, (struct inferior *inf), (inf))
GEN_INTERP_CALL (on_tsv_created,
		 (const struct trace_state_variable *tsv), (tsv))
GEN_INTERP_CALL (on_tsv_deleted,
		 (const struct trace_state_variable *tsv), (tsv))
GEN_INTERP_CALL (on_tsv_modified,
		 (const struct trace_state_variable *tsv), (tsv))
GEN_INTERP_CALL (on_record_changed,
		 (struct inferior *inferior, int started),
		 (inferior, started))
GEN_INTERP_CALL (on_solib_loaded, (struct so_list *solib), (solib))
GEN_INTERP_CALL (on_solib_unloaded, (struct so_list *solib), (solib))
GEN_INTERP_CALL (on_traceframe_changed, (int tfnum, int tpnum), (tfnum, tpnum))
GEN_INTERP_CALL (on_command_param_changed,
		 (const char *param, const char *value), (param, value))
GEN_INTERP_CALL (on_command_error, (void), ())

GEN_INTERP_CALL (on_memory_changed,
		 (struct inferior *inferior, CORE_ADDR addr,
		  ssize_t len, const bfd_byte *data),
		 (inferior, addr, len, data))

void
_initialize_interpreter (void)
{
  struct cmd_list_element *c;

  c = add_cmd ("interpreter-exec", class_support,
	       interpreter_exec_cmd, _("\
Execute a command in an interpreter.  It takes two arguments:\n\
The first argument is the name of the interpreter to use.\n\
The second argument is the command to execute.\n"), &cmdlist);
  set_cmd_completer (c, interpreter_completer);

  observer_attach_signal_received (interp_on_signal_received);
  observer_attach_end_stepping_range (interp_on_end_stepping_range);
  observer_attach_signal_exited (interp_on_signal_exited);
  observer_attach_exited (interp_on_exited);
  observer_attach_no_history (interp_on_no_history);
  observer_attach_new_thread (interp_on_new_thread);
  observer_attach_thread_exit (interp_on_thread_exit);
  observer_attach_inferior_added (interp_on_inferior_added);
  observer_attach_inferior_appeared (interp_on_inferior_appeared);
  observer_attach_inferior_exit (interp_on_inferior_exit);
  observer_attach_inferior_removed (interp_on_inferior_removed);
  observer_attach_record_changed (interp_on_record_changed);
  observer_attach_normal_stop (interp_on_normal_stop);
  observer_attach_target_resumed (interp_on_target_resumed);
  observer_attach_solib_loaded (interp_on_solib_loaded);
  observer_attach_solib_unloaded (interp_on_solib_unloaded);
  observer_attach_about_to_proceed (interp_on_about_to_proceed);
  observer_attach_traceframe_changed (interp_on_traceframe_changed);
  observer_attach_tsv_created (interp_on_tsv_created);
  observer_attach_tsv_deleted (interp_on_tsv_deleted);
  observer_attach_tsv_modified (interp_on_tsv_modified);
  observer_attach_breakpoint_created (interp_on_breakpoint_created);
  observer_attach_breakpoint_deleted (interp_on_breakpoint_deleted);
  observer_attach_breakpoint_modified (interp_on_breakpoint_modified);
  observer_attach_command_param_changed (interp_on_command_param_changed);
  observer_attach_memory_changed (interp_on_memory_changed);
  observer_attach_sync_execution_done (interp_on_sync_execution_done);
  observer_attach_command_error (interp_on_command_error);
}
