/* CLI Definitions for GDB, the GNU debugger.

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

#include "defs.h"
#include "interps.h"
#include "event-top.h"
#include "ui-out.h"
#include "cli-out.h"
#include "top.h"		/* for "execute_command" */
#include "infrun.h"
#include "observer.h"

struct cli_interp
{
  /* CLI's output channels */
  struct ui_file *out;
  struct ui_file *err;
  struct ui_file *log;
  struct ui_file *targ;

  /* CLI's builder.  */
  struct ui_out *uiout;
};

/* Longjmp-safe wrapper for "execute_command".  */
static struct gdb_exception safe_execute_command (struct ui_out *uiout,
						  char *command, 
						  int from_tty);

static int console_interp_p (struct interp *interp);

/* Observers for several run control events.  If the interpreter is
   quiet (i.e., another interpreter is being run with
   interpreter-exec), print nothing.  */

/* Observer for the normal_stop notification.  */

static void
cli_on_normal_stop (struct bpstats *bs, int print_frame)
{
  struct interp *interp;

  if (!print_frame)
    return;

  ALL_CONSOLE_INTERPS (interp)
    {
      print_stop_event (interp_ui_out (interp));
    }
}

/* Observer for the signal_received notification.  */

static void
cli_on_signal_received (enum gdb_signal siggnal)
{
  struct interp *interp = current_interpreter;

  print_signal_received_reason (interp_ui_out (interp), siggnal);
}

/* Observer for the end_stepping_range notification.  */

static void
cli_on_end_stepping_range (void)
{
  struct interp *interp = current_interpreter;

  print_end_stepping_range_reason (interp_ui_out (interp));
}

/* Observer for the signalled notification.  */

static void
cli_on_signal_exited (enum gdb_signal siggnal)
{
  struct interp *interp = current_interpreter;

  print_signal_exited_reason (interp_ui_out (interp), siggnal);
}

/* Observer for the exited notification.  */

static void
cli_on_exited (int exitstatus)
{
  struct interp *interp = current_interpreter;

  print_exited_reason (interp_ui_out (interp), exitstatus);
}

/* Observer for the no_history notification.  */

static void
cli_on_no_history (void)
{
  struct interp *interp = current_interpreter;

  print_no_history_reason (interp_ui_out (interp));
}

/* Observer for the sync_execution_done notification.  */

static void
cli_on_sync_execution_done (void)
{
  struct interp *interp = current_interpreter;

  display_gdb_prompt (NULL);
}

/* Observer for the command_error notification.  */

static void
cli_on_command_error (void)
{
  if (console_interp_p (current_interpreter))
    display_gdb_prompt (NULL);
}

/* These implement the cli out interpreter: */

static void *
cli_interpreter_init (struct interp *self, int top_level)
{
  struct cli_interp *cli = XNEW (struct cli_interp);

  cli->out = gdb_stdout;
  cli->err = gdb_stderr;
  cli->log = gdb_stdlog;
  cli->targ = gdb_stdtarg;
  cli->uiout = cli_out_new (cli->out);

  return cli;
}

static int
cli_interpreter_resume (struct interp *self)
{
  struct cli_interp *cli = self->data;
#if 0
  struct ui_file *stream;
#endif

  /*sync_execution = 1; */

  /* gdb_setup_readline will change gdb_stdout.  If the CLI was
     previously writing to gdb_stdout, then set it to the new
     gdb_stdout afterwards.  */
#if 0
  stream = cli_out_set_stream (cli_uiout, gdb_stdout);
  if (stream != gdb_stdout)
    {
      cli_out_set_stream (cli_uiout, stream);
      stream = NULL;
    }
#endif

  gdb_stdout = cli->out;
  gdb_stderr = cli->err;
  gdb_stdlog = cli->log;
  gdb_stdtarg = cli->targ;
  gdb_stdtargerr = cli->targ;

  gdb_setup_readline ();

#if 0
  if (stream != NULL)
    cli_out_set_stream (cli_uiout, gdb_stdout);
#endif

  return 1;
}

static int
cli_interpreter_suspend (struct interp *self)
{
  gdb_disable_readline ();
  return 1;
}

static struct gdb_exception
cli_interpreter_exec (struct interp *self, const char *command_str)
{
  struct ui_file *old_stream;
  struct gdb_exception result;

  /* FIXME: cagney/2003-02-01: Need to const char *propogate
     safe_execute_command.  */
  char *str = (char *) alloca (strlen (command_str) + 1);
  strcpy (str, command_str);

  /* gdb_stdout could change between the time cli_uiout was
     initialized and now.  Since we're probably using a different
     interpreter which has a new ui_file for gdb_stdout, use that one
     instead of the default.

     It is important that it gets reset everytime, since the user
     could set gdb to use a different interpreter.  */
#if 0
  old_stream = cli_out_set_stream (cli_uiout, gdb_stdout);
  result = safe_execute_command (cli_uiout, str, 1);
  cli_out_set_stream (cli_uiout, old_stream);
#endif

  result = safe_execute_command (current_uiout, str, 1);

  return result;
}

static struct gdb_exception
safe_execute_command (struct ui_out *command_uiout, char *command, int from_tty)
{
  struct gdb_exception e = exception_none;
  struct ui_out *saved_uiout;

  /* Save and override the global ``struct ui_out'' builder.  */
  saved_uiout = current_uiout;
  current_uiout = command_uiout;

  TRY
    {
      execute_command (command, from_tty);
    }
  CATCH (exception, RETURN_MASK_ALL)
    {
      e = exception;
    }
  END_CATCH

  /* Restore the global builder.  */
  current_uiout = saved_uiout;

  /* FIXME: cagney/2005-01-13: This shouldn't be needed.  Instead the
     caller should print the exception.  */
  exception_print (gdb_stderr, e);
  return e;
}

static struct ui_out *
cli_ui_out (struct interp *self)
{
  struct cli_interp *cli = self->data;

  return cli->uiout;
}

/* Standard gdb initialization hook.  */
extern initialize_file_ftype _initialize_cli_interp; /* -Wmissing-prototypes */

static const struct interp_procs console_interp_procs = {
  cli_interpreter_init,	/* init_proc */
  cli_interpreter_resume,	/* resume_proc */
  cli_interpreter_suspend,	/* suspend_proc */
  cli_interpreter_exec,	/* exec_proc */
  cli_ui_out,			/* ui_out_proc */
  NULL,                       /* set_logging_proc */
  cli_command_loop            /* command_loop_proc */
};

static struct interp *
console_interp_factory (const char *name, struct terminal *terminal)
{
  return interp_new (name, &console_interp_procs, terminal);
}

static int
console_interp_p (struct interp *interp)
{
  return interp->procs == &console_interp_procs;
}

void
_initialize_cli_interp (void)
{
  interp_factory_register (INTERP_CONSOLE, console_interp_factory);

  /* If changing this, remember to update tui-interp.c as well.  */
  observer_attach_normal_stop (cli_on_normal_stop);
  observer_attach_end_stepping_range (cli_on_end_stepping_range);
  observer_attach_signal_received (cli_on_signal_received);
  observer_attach_signal_exited (cli_on_signal_exited);
  observer_attach_exited (cli_on_exited);
  observer_attach_no_history (cli_on_no_history);
  observer_attach_sync_execution_done (cli_on_sync_execution_done);
  observer_attach_command_error (cli_on_command_error);
}
