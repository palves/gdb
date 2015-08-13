/* TUI Interpreter definitions for GDB, the GNU debugger.

   Copyright (C) 2003-2015 Free Software Foundation, Inc.

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
#include "top.h"
#include "event-top.h"
#include "event-loop.h"
#include "ui-out.h"
#include "cli-out.h"
#include "tui/tui-data.h"
#include "readline/readline.h"
#include "tui/tui-win.h"
#include "tui/tui.h"
#include "tui/tui-io.h"
#include "tui/tui-interp.h"
#include "infrun.h"
#include "observer.h"
#include "gdbthread.h"
#include "terminal.h"

/* Set to 1 when the TUI mode must be activated when we first start
   gdb.  */
static int tui_start_enabled = 0;

/* Cleanup the tui before exiting.  */

static void
tui_exit (void)
{
  /* Disable the tui.  Curses mode is left leaving the screen in a
     clean state (see endwin()).  */
  tui_disable ();
}

/* Observers for several run control events.  If the interpreter is
   quiet (i.e., another interpreter is being run with
   interpreter-exec), print nothing.  */

/* Observer for the normal_stop notification.  */

extern int should_print_stop_to_console (struct interp *interp,
					 struct thread_info *tp);

int
should_print_stop_to_console (struct interp *interp,
			      struct thread_info *tp)
{
  /* Breakpoint hits should always be mirrored to the console.
     Deciding what to mirror to the console wrt to breakpoints and
     random stops gets messy real fast.  E.g., say "s" trips on a
     breakpoint.  We'd clearly want to mirror the event to the console
     in this case.  But what about more complicated cases like "s&;
     thread n; s&", and one of those steps spawning a new thread, and
     that thread hitting a breakpoint?  It's impossible in general to
     track whether the thread had any relation to the commands that
     had been executed.  So we just simplify and always mirror
     breakpoints and random events to the console.

     FIXME comment. XXXXXXXX

     Also, CLI execution commands (-interpreter-exec console "next",
     for example) in async mode have the opposite issue as described
     in the "then" branch above -- normal_stop has already printed
     frame information to MI uiout, but nothing has printed the same
     information to the CLI channel.  We should print the source line
     to the console when stepping or other similar commands, iff the
     step was started by a console command (but not if it was started
     with -exec-step or similar).  */
  if ((!tp->control.stop_step
       && !tp->control.proceed_to_finish))
    return 1;

  if (tp->control.command_interp != NULL
       && tp->control.command_interp == interp)
    return 1;

  return 0;
}

static void
tui_on_normal_stop (struct bpstats *bs, int print_frame)
{
  struct interp *interp = current_interpreter;
  struct thread_info *tp;

  if (!print_frame)
    return;

  tp = inferior_thread ();

  /* Broadcast asynchronous stops to all consoles.  If we just
     finished a step, print this to the console if it was the console
     that started the step in the first place.  */
  if (should_print_stop_to_console (interp, tp))
    print_stop_event (interp_ui_out (interp));
}

/* Observer for the signal_received notification.  */

static void
tui_on_signal_received (enum gdb_signal siggnal)
{
  struct interp *interp = current_interpreter;

  print_signal_received_reason (interp_ui_out (interp), siggnal);
}

/* Observer for the end_stepping_range notification.  */

static void
tui_on_end_stepping_range (void)
{
  struct interp *interp = current_interpreter;

  print_end_stepping_range_reason (interp_ui_out (interp));
}

/* Observer for the signal_exited notification.  */

static void
tui_on_signal_exited (enum gdb_signal siggnal)
{
  struct interp *interp = current_interpreter;

  print_signal_exited_reason (interp_ui_out (interp), siggnal);
}

/* Observer for the exited notification.  */

static void
tui_on_exited (int exitstatus)
{
  struct interp *interp = current_interpreter;

  print_exited_reason (interp_ui_out (interp), exitstatus);
}

/* Observer for the no_history notification.  */

static void
tui_on_no_history (void)
{
  struct interp *interp = current_interpreter;

  print_no_history_reason (interp_ui_out (interp));
}

/* Observer for the sync_execution_done notification.  */

static void
tui_on_sync_execution_done (void)
{
  struct interp *interp = current_interpreter;

  if (interp->terminal->sync_execution)
    {
      async_enable_stdin ();
      display_gdb_prompt (NULL);
    }
}

/* Observer for the command_error notification.  */

static void
tui_on_command_error (void)
{
  display_gdb_prompt (NULL);
}

/* These implement the TUI interpreter.  */

static void *
tui_init (struct interp *self, int top_level)
{
  tui_initialize_static_data ();

  tui_initialize_io ();
  tui_initialize_win ();
  if (ui_file_isatty (gdb_stdout))
    tui_initialize_readline ();

  return NULL;
}

static int
tui_resume (struct interp *self)
{
  struct ui_file *stream;
  struct tui_interp *tui = (struct tui_interp *) self;

  gdb_setup_readline ();

  if (tui_start_enabled)
    tui_enable ();
  return 1;
}

static int
tui_suspend (struct interp *self)
{
  tui_start_enabled = tui_active;
  tui_disable ();
  return 1;
}

static struct ui_out *
tui_ui_out (struct interp *self)
{
  struct tui_interp *tui_interp = (struct tui_interp *) self;

  if (tui_active)
    return tui_io_out (tui_interp->io_data);
  else
    return tui_io_old_uiout (tui_interp->io_data);
}

static struct gdb_exception
tui_exec (struct interp *self, const char *command_str)
{
  internal_error (__FILE__, __LINE__, _("tui_exec called"));
}

static const struct interp_procs tui_interp_procs = {
  tui_init,
  tui_resume,
  tui_suspend,
  tui_exec,
  tui_ui_out,
  NULL,
  cli_command_loop,
  tui_on_normal_stop,
  tui_on_signal_received,
  tui_on_end_stepping_range,
  tui_on_signal_exited,
  tui_on_exited,
  tui_on_no_history,
  tui_on_sync_execution_done,
  NULL, /* on_new_thread */
  NULL, /* on_thread_exit */
  NULL, /* on_on_target_resumed */
  NULL, /* on_about_to_proceed */
  NULL, /* on_breakpoint_created */
  NULL, /* on_breakpoint_deleted */
  NULL, /* on_breakpoint_modified */
  NULL, /* on_inferior_added */
  NULL, /* on_inferior_appeared */
  NULL, /* on_inferior_exit */
  NULL, /* on_inferior_removed */
  NULL, /* on_tsv_created */
  NULL, /* on_tsv_deleted */
  NULL, /* on_tsv_modified */
  NULL, /* on_record_changed */
  NULL, /* on_solib_loaded */
  NULL, /* on_solib_unloaded */
  NULL, /* on_traceframe_changed */
  NULL, /* on_command_param_changed */
  tui_on_command_error,
  NULL, /* on_memory_changed */
};

static struct interp *
tui_interp_factory (const char *name, struct terminal *terminal)
{
  struct tui_interp *tui_interp;
  struct interp *interp;

  tui_interp = XNEW (struct tui_interp);
  tui_interp->io_data = tui_io_data_new ();

  interp = &tui_interp->interp;
  /* Create a default uiout builder for the TUI.  */
  interp_ctor (interp, INTERP_TUI, &tui_interp_procs, terminal);

  return interp;
}

/* Provide a prototype to silence -Wmissing-prototypes.  */
extern initialize_file_ftype _initialize_tui_interp;

void
_initialize_tui_interp (void)
{
  struct interp *tui_interp;

  interp_factory_register (INTERP_TUI, tui_interp_factory);

#if 0
  /* Create a default uiout builder for the TUI.  */
  tui_interp = tui_interp_factory (NULL);
  interp_add (tui_interp);
#endif

  if (interpreter_p && strcmp (interpreter_p, INTERP_TUI) == 0)
    tui_start_enabled = 1;

  if (interpreter_p && strcmp (interpreter_p, INTERP_CONSOLE) == 0)
    {
      xfree (interpreter_p);
      interpreter_p = xstrdup (INTERP_TUI);
    }

  /* Install exit handler to leave the screen in a good shape.  */
  atexit (tui_exit);
}
