/* Top level stuff for GDB, the GNU debugger.

   Copyright (C) 1999-2016 Free Software Foundation, Inc.

   Written by Elena Zannoni <ezannoni@cygnus.com> of Cygnus Solutions.

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
#include "top.h"
#include "inferior.h"
#include "infrun.h"
#include "target.h"
#include "terminal.h"		/* for job_control */
#include "event-loop.h"
#include "event-top.h"
#include "interps.h"
#include <signal.h>
#include "cli/cli-script.h"     /* for reset_command_nest_depth */
#include "main.h"
#include "gdbthread.h"
#include "observer.h"
#include "continuations.h"
#include "gdbcmd.h"		/* for dont_repeat() */
#include "annotate.h"
#include "maint.h"
#include "inflow.h"
#include "serial.h"
#include "buffer.h"

/* readline include files.  */
#include "readline/readline.h"
#include "readline/history.h"

/* readline defines this.  */
#undef savestring

static void rl_callback_read_char_wrapper (gdb_client_data client_data);
static char *top_level_prompt (void);

/* Signal handlers.  */
#ifdef SIGQUIT
static void handle_sigquit (int sig);
#endif
#ifdef SIGHUP
static void handle_sighup (int sig);
#endif
static void handle_sigfpe (int sig);

/* Functions to be invoked by the event loop in response to
   signals.  */
#if defined (SIGQUIT) || defined (SIGHUP)
static void async_do_nothing (gdb_client_data);
#endif
#ifdef SIGHUP
static void async_disconnect (gdb_client_data);
#endif
static void async_float_handler (gdb_client_data);
#ifdef STOP_SIGNAL
static void async_stop_sig (gdb_client_data);
#endif
static void async_sigterm_handler (gdb_client_data arg);

/* Instead of invoking (and waiting for) readline to read the command
   line and pass it back for processing, we use readline's alternate
   interface, via callback functions, so that the event loop can react
   to other event sources while we wait for input.  */

/* Important variables for the event loop.  */

/* This is used to determine if GDB is using the readline library or
   its own simplified form of readline.  It is used by the asynchronous
   form of the set editing command.
   ezannoni: as of 1999-04-29 I expect that this
   variable will not be used after gdb is changed to use the event
   loop as default engine, and event-top.c is merged into top.c.  */
int set_editing_cmd_var;

/* This is used to display the notification of the completion of an
   asynchronous execution command.  */
int exec_done_display_p = 0;

/* Used by the stdin event handler to compensate for missed stdin events.
   Setting this to a non-zero value inside an stdin callback makes the callback
   run again.  */
int call_stdin_event_handler_again_p;

/* Signal handling variables.  */
/* Each of these is a pointer to a function that the event loop will
   invoke if the corresponding signal has received.  The real signal
   handlers mark these functions as ready to be executed and the event
   loop, in a later iteration, calls them.  See the function
   invoke_async_signal_handler.  */
static struct async_signal_handler *sigint_token;
#ifdef SIGHUP
static struct async_signal_handler *sighup_token;
#endif
#ifdef SIGQUIT
static struct async_signal_handler *sigquit_token;
#endif
static struct async_signal_handler *sigfpe_token;
#ifdef STOP_SIGNAL
static struct async_signal_handler *sigtstp_token;
#endif
static struct async_signal_handler *async_sigterm_token;

/* This hook is called by rl_callback_read_char_wrapper after each
   character is processed.  */
void (*after_char_processing_hook) (void);


/* Wrapper function for calling into the readline library.  The event
   loop expects the callback function to have a paramter, while
   readline expects none.  */
static void
rl_callback_read_char_wrapper (gdb_client_data client_data)
{
  rl_callback_read_char ();
  if (after_char_processing_hook)
    (*after_char_processing_hook) ();
}

/* Change the function to be invoked every time there is a character
   ready on stdin.  This is used when the user sets the editing off,
   therefore bypassing readline, and letting gdb handle the input
   itself, via gdb_readline_callback_no_editing.  Also it is used in
   the opposite case in which the user sets editing on again, by
   restoring readline handling of the input.

   NOTE: this operates on input_fd, not instream.  If we are reading
   commands from a file, instream will point to the file.  However, we
   always read commands from a file with editing off.  This means that
   the 'set editing on/off' will have effect only on the interactive
   session.  */

void
change_line_handler (int editing)
{
  struct ui *ui = current_ui;

  /* We can only have one instance of readline, so we only allow
     editing on the main UI.  */
  if (ui != main_ui)
    return;

  /* Don't try enabling editing if the interpreter doesn't support it
     (e.g., MI).  */
  if (!interp_supports_command_editing (top_level_interpreter ())
      || !interp_supports_command_editing (command_interp ()))
    return;

  if (editing)
    {
      gdb_assert (ui == main_ui);

      /* Turn on editing by using readline.  */
      ui->call_readline = rl_callback_read_char_wrapper;
    }
  else
    {
      /* Turn off editing by using gdb_readline_callback_no_editing.  */
      if (ui->command_editing)
	gdb_rl_callback_handler_remove ();
      ui->call_readline = gdb_readline_callback_no_editing;
    }
  ui->command_editing = editing;
}

/* The functions below are wrappers for rl_callback_handler_remove and
   rl_callback_handler_install that keep track of whether the callback
   handler is installed in readline.  This is necessary because after
   handling a target event of a background execution command, we may
   need to reinstall the callback handler if it was removed due to a
   secondary prompt.  See gdb_readline_wrapper_line.  We don't
   unconditionally install the handler for every target event because
   that also clears the line buffer, thus installing it while the user
   is typing would lose input.  */

/* Whether we've registered a callback handler with readline.  */
static int callback_handler_installed;

/* See event-top.h, and above.  */

void
gdb_rl_callback_handler_remove (void)
{
  struct ui *ui = current_ui;

  gdb_assert (ui == main_ui);

  rl_callback_handler_remove ();
  callback_handler_installed = 0;
}

/* See event-top.h, and above.  Note this wrapper doesn't have an
   actual callback parameter because we always install
   INPUT_HANDLER.  */

void
gdb_rl_callback_handler_install (const char *prompt)
{
  struct ui *ui = current_ui;

  gdb_assert (ui == main_ui);

  /* Calling rl_callback_handler_install resets readline's input
     buffer.  Calling this when we were already processing input
     therefore loses input.  */
  gdb_assert (!callback_handler_installed);

  rl_callback_handler_install (prompt, ui->input_handler);
  callback_handler_installed = 1;
}

/* See event-top.h, and above.  */

void
gdb_rl_callback_handler_reinstall (void)
{
  struct ui *ui = current_ui;

  gdb_assert (ui == main_ui);

  if (!callback_handler_installed)
    {
      /* Passing NULL as prompt argument tells readline to not display
	 a prompt.  */
      gdb_rl_callback_handler_install (NULL);
    }
}

/* Displays the prompt.  If the argument NEW_PROMPT is NULL, the
   prompt that is displayed is the current top level prompt.
   Otherwise, it displays whatever NEW_PROMPT is as a local/secondary
   prompt.

   This is used after each gdb command has completed, and in the
   following cases:

   1. When the user enters a command line which is ended by '\'
   indicating that the command will continue on the next line.  In
   that case the prompt that is displayed is the empty string.

   2. When the user is entering 'commands' for a breakpoint, or
   actions for a tracepoint.  In this case the prompt will be '>'

   3. On prompting for pagination.  */

void
display_gdb_prompt (const char *new_prompt)
{
  char *actual_gdb_prompt = NULL;
  struct cleanup *old_chain;

  annotate_display_prompt ();

  /* Reset the nesting depth used when trace-commands is set.  */
  reset_command_nest_depth ();

  old_chain = make_cleanup (free_current_contents, &actual_gdb_prompt);

  /* Do not call the python hook on an explicit prompt change as
     passed to this function, as this forms a secondary/local prompt,
     IE, displayed but not set.  */
  if (! new_prompt)
    {
      struct ui *ui = current_ui;

      if (ui->prompt_state == PROMPTED)
	internal_error (__FILE__, __LINE__, _("double prompt"));
      else if (ui->prompt_state == PROMPT_BLOCKED)
	{
	  /* This is to trick readline into not trying to display the
	     prompt.  Even though we display the prompt using this
	     function, readline still tries to do its own display if
	     we don't call rl_callback_handler_install and
	     rl_callback_handler_remove (which readline detects
	     because a global variable is not set).  If readline did
	     that, it could mess up gdb signal handlers for SIGINT.
	     Readline assumes that between calls to rl_set_signals and
	     rl_clear_signals gdb doesn't do anything with the signal
	     handlers.  Well, that's not the case, because when the
	     target executes we change the SIGINT signal handler.  If
	     we allowed readline to display the prompt, the signal
	     handler change would happen exactly between the calls to
	     the above two functions.  Calling
	     rl_callback_handler_remove(), does the job.  */

	  if (current_ui->command_editing)
	    gdb_rl_callback_handler_remove ();
	  do_cleanups (old_chain);
	  return;
	}
      else if (ui->prompt_state == PROMPT_NEEDED)
	{
	  /* Display the top level prompt.  */
	  actual_gdb_prompt = top_level_prompt ();
	  ui->prompt_state = PROMPTED;
	}
    }
  else
    actual_gdb_prompt = xstrdup (new_prompt);

  if (current_ui->command_editing)
    {
      gdb_rl_callback_handler_remove ();
      gdb_rl_callback_handler_install (actual_gdb_prompt);
    }
  /* new_prompt at this point can be the top of the stack or the one
     passed in.  It can't be NULL.  */
  else
    {
      /* Don't use a _filtered function here.  It causes the assumed
         character position to be off, since the newline we read from
         the user is not accounted for.  */
      fputs_unfiltered (actual_gdb_prompt, gdb_stdout);
      gdb_flush (gdb_stdout);
    }

  do_cleanups (old_chain);
}

/* Return the top level prompt, as specified by "set prompt", possibly
   overriden by the python gdb.prompt_hook hook, and then composed
   with the prompt prefix and suffix (annotations).  The caller is
   responsible for freeing the returned string.  */

static char *
top_level_prompt (void)
{
  char *prompt;

  /* Give observers a chance of changing the prompt.  E.g., the python
     `gdb.prompt_hook' is installed as an observer.  */
  observer_notify_before_prompt (get_prompt ());

  prompt = get_prompt ();

  if (annotation_level >= 2)
    {
      /* Prefix needs to have new line at end.  */
      const char prefix[] = "\n\032\032pre-prompt\n";

      /* Suffix needs to have a new line at end and \032 \032 at
	 beginning.  */
      const char suffix[] = "\n\032\032prompt\n";

      return concat (prefix, prompt, suffix, NULL);
    }

  return xstrdup (prompt);
}

static struct ui main_ui_;

struct ui *main_ui = &main_ui_;
struct ui *current_ui = &main_ui_;
struct ui *ui_list = &main_ui_;

void
restore_ui_cleanup (void *data)
{
  current_ui = (struct ui *) data;
}

void
switch_thru_all_uis_init (struct switch_thru_all_uis *state)
{
  state->iter = ui_list;
  state->old_chain = make_cleanup (restore_ui_cleanup, current_ui);
}

int
switch_thru_all_uis_cond (struct switch_thru_all_uis *state)
{
  if (state->iter != NULL)
    {
      current_ui = state->iter;
      return 1;
    }
  else
    {
      do_cleanups (state->old_chain);
      return 0;
    }
}

void
switch_thru_all_uis_next (struct switch_thru_all_uis *state)
{
  state->iter = state->iter->next;
}

/* Get a pointer to the current UI's line builder.  */

static struct buffer *
get_line_builder (void)
{
  return &current_ui->line_builder;
}

/* When there is an event ready on the stdin file descriptor, instead
   of calling readline directly throught the callback function, or
   instead of calling gdb_readline2, give gdb a chance to detect
   errors and do something.  */

void
stdin_event_handler (int error, gdb_client_data client_data)
{
  struct ui *ui = (struct ui *) client_data;

  /* Switch to the UI whose input descriptor woke up the event
     loop.  */
  current_ui = ui;

  if (error)
    {
      printf_unfiltered (_("error detected on stdin\n"));
      delete_file_handler (ui->input_fd);
      /* If stdin died, we may as well kill gdb.  */
      quit_command ((char *) 0, stdin == ui->instream);
    }
  else
    {
      do
	{
	  call_stdin_event_handler_again_p = 0;
	  ui->call_readline (client_data);
	} while (call_stdin_event_handler_again_p != 0);
    }
}

/* Re-enable stdin after the end of an execution command in
   synchronous mode, or after an error from the target, and we aborted
   the exec operation.  */

void
async_enable_stdin (void)
{
  struct ui *ui = current_ui;

  if (ui->prompt_state == PROMPT_BLOCKED)
    {
      target_terminal_ours ();
      ui->prompt_state = PROMPT_NEEDED;
    }
}

/* Disable reads from stdin (the console) marking the command as
   synchronous.  */

void
async_disable_stdin (void)
{
  struct ui *ui = current_ui;

  ui->prompt_state = PROMPT_BLOCKED;
}


/* Handle a gdb command line.  This function is called when
   handle_line_of_input has concatenated one or more input lines into
   a whole command.  */

void
command_handler (char *command)
{
  struct ui *ui = current_ui;
  struct cleanup *stat_chain;
  char *c;

  clear_quit_flag ();
  if (ui->instream == stdin)
    reinitialize_more_filter ();

  stat_chain = make_command_stats_cleanup (1);

  /* Do not execute commented lines.  */
  for (c = command; *c == ' ' || *c == '\t'; c++)
    ;
  if (c[0] != '#')
    {
      execute_command (command, ui->instream == stdin);

      /* Do any commands attached to breakpoint we stopped at.  */
      bpstat_do_actions ();
    }

  do_cleanups (stat_chain);
}

/* Append RL to the buffer maintained by CMD_BUILDER.  Returns false if
   more input is expected (line ends in a backslash), true if we have
   a whole command line.  Takes ownership of RL.  */

static char *
cmd_builder_append (struct buffer *cmd_builder, char *rl)
{
  char *cmd;
  size_t len;

  len = strlen (rl);

  if (len > 0 && rl[len - 1] == '\\')
    {
      /* Don't copy the backslash and wait for more.  */
      buffer_grow (cmd_builder, rl, len - 1);
      cmd = NULL;
    }
  else
    {
      /* Copy whole line including terminating null, and we're
	 done.  */
      buffer_grow (cmd_builder, rl, len + 1);
      cmd = cmd_builder->buffer;
    }

  /* Allocated in readline.  */
  xfree (rl);

  return cmd;
}

/* Handle a line of input coming from readline.

   If the read line ends with a continuation character (backslash),
   save the partial input in CMD_BUILDER (except the backslash), and
   return NULL.  Otherwise, save the partial input and return a
   pointer to CMD_BUILDER's buffer (null terminated), indicating a
   whole command line is ready to be executed.

   Returns EOF on end of file.

   If REPEAT, handle command repetitions:

     - If the input command line is NOT empty, the command returned is
       copied into the global 'saved_command_line' var so that it can
       be repeated later.

     - OTOH, if the input command line IS empty, return the previously
       saved command instead of the empty input line.
*/

char *
handle_line_of_input (struct buffer *cmd_builder,
		      char *rl, int repeat, char *annotation_suffix)
{
  struct ui *ui = current_ui;
  char *p1;
  char *cmd;

  if (rl == NULL)
    return (char *) EOF;

  cmd = cmd_builder_append (cmd_builder, rl);
  if (cmd == NULL)
    return NULL;

  /* We have a complete command line now.  Prepare for the next
     command, but leave ownership of memory to the buffer .  */
  cmd_builder->used_size = 0;

  if (annotation_level > 1 && ui->instream == stdin)
    {
      printf_unfiltered (("\n\032\032post-"));
      puts_unfiltered (annotation_suffix);
      printf_unfiltered (("\n"));
    }

#define SERVER_COMMAND_PREFIX "server "
  if (startswith (cmd, SERVER_COMMAND_PREFIX))
    {
      /* Note that we don't set `saved_command_line'.  Between this
         and the check in dont_repeat, this insures that repeating
         will still do the right thing.  */
      return cmd + strlen (SERVER_COMMAND_PREFIX);
    }

  /* Do history expansion if that is wished.  */
  if (history_expansion_p && ui->instream == stdin
      && ISATTY (ui->instream))
    {
      char *history_value;
      int expanded;

      expanded = history_expand (cmd, &history_value);
      if (expanded)
	{
	  size_t len;

	  /* Print the changes.  */
	  printf_unfiltered ("%s\n", history_value);

	  /* If there was an error, call this function again.  */
	  if (expanded < 0)
	    {
	      xfree (history_value);
	      return cmd;
	    }

	  /* history_expand returns an allocated string.  Just replace
	     our buffer with it.  */
	  len = strlen (history_value);
	  xfree (buffer_finish (cmd_builder));
	  cmd_builder->buffer = history_value;
	  cmd_builder->buffer_size = len + 1;
	  cmd = history_value;
	}
    }

  /* If we just got an empty line, and that is supposed to repeat the
     previous command, return the previously saved command.  */
  for (p1 = cmd; *p1 == ' ' || *p1 == '\t'; p1++)
    ;
  if (repeat && *p1 == '\0')
    return saved_command_line;

  /* Add command to history if appropriate.  Note: lines consisting
     solely of comments are also added to the command history.  This
     is useful when you type a command, and then realize you don't
     want to execute it quite yet.  You can comment out the command
     and then later fetch it from the value history and remove the
     '#'.  The kill ring is probably better, but some people are in
     the habit of commenting things out.  */
  if (*cmd && input_from_terminal_p ())
    gdb_add_history (cmd);

  /* Save into global buffer if appropriate.  */
  if (repeat)
    {
      xfree (saved_command_line);
      saved_command_line = xstrdup (cmd);
      return saved_command_line;
    }
  else
    return cmd;
}

/* Handle a complete line of input.  This is called by the callback
   mechanism within the readline library.  Deal with incomplete
   commands as well, by saving the partial input in a global
   buffer.

   NOTE: This is the asynchronous version of the command_line_input
   function.  */

void
command_line_handler (char *rl)
{
  struct ui *ui = current_ui;
  struct buffer *cmd_builder = get_line_builder ();
  char *cmd;

  cmd = handle_line_of_input (cmd_builder, rl,
			      ui->instream == stdin, "prompt");
  if (cmd == (char *) EOF)
    {
      /* stdin closed.  The connection with the terminal is gone.
	 This happens at the end of a testsuite run, after Expect has
	 hung up but GDB is still alive.  In such a case, we just quit
	 gdb killing the inferior program too.  */
      printf_unfiltered ("quit\n");
      execute_command ("quit", stdin == ui->instream);
    }
  else if (cmd == NULL)
    {
      /* We don't have a full line yet.  Print an empty prompt.  */
      display_gdb_prompt ("");
    }
  else
    {
      ui->prompt_state = PROMPT_NEEDED;

      command_handler (cmd);

      if (ui->prompt_state != PROMPTED)
	display_gdb_prompt (0);
    }
}

/* Does reading of input from terminal w/o the editing features
   provided by the readline library.  Calls the line input handler
   once we have a whole input line.  */

void
gdb_readline_callback_no_editing (gdb_client_data client_data)
{
  struct ui *ui = current_ui;
  struct buffer *builder = get_line_builder ();
  int c;
  char *r;

  /* We still need the while loop here, even though it would seem
     obvious to invoke gdb_readline2 at every character entered.  If
     not using the readline library, the terminal is in cooked mode,
     which sends the characters all at once.  Poll will notice that the
     input fd has changed state only after enter is pressed.  At this
     point we still need to fetch all the chars entered.  */

  while (1)
    {
      /* A non-blocking read.  */
      c = serial_readchar (ui->stdin_serial, 0);

      if (c == SERIAL_ERROR)
	{
	  /* No chars left.  Go back to event loop.  */
	  return;
	}

      if (c == SERIAL_EOF)
	{
	  if (builder->used_size > 0)
	    {
	      /* The last line does not end with a newline.  Return
		 it, and if we are called again serial_readchar will
		 still return EOF and we'll signal error then.  */
	      break;
	    }
	  xfree (buffer_finish (builder));
	  ui->input_handler (NULL);
	  return;
	}

      if (c == '\n')
	{
	  if (builder->used_size > 0
	      && builder->buffer[builder->used_size - 1] == '\r')
	    builder->used_size--;
	  break;
	}

      buffer_grow_char (builder, c);
    }

  buffer_grow_char (builder, '\0');

  r = buffer_finish (builder);
  ui->input_handler (r);
}


/* Initialization of signal handlers and tokens.  There is a function
   handle_sig* for each of the signals GDB cares about.  Specifically:
   SIGINT, SIGFPE, SIGQUIT, SIGTSTP, SIGHUP, SIGWINCH.  These
   functions are the actual signal handlers associated to the signals
   via calls to signal().  The only job for these functions is to
   enqueue the appropriate event/procedure with the event loop.  Such
   procedures are the old signal handlers.  The event loop will take
   care of invoking the queued procedures to perform the usual tasks
   associated with the reception of the signal.  */
/* NOTE: 1999-04-30 This is the asynchronous version of init_signals.
   init_signals will become obsolete as we move to have to event loop
   as the default for gdb.  */
void
async_init_signals (void)
{
  signal (SIGINT, handle_sigint);
  sigint_token =
    create_async_signal_handler (async_request_quit, NULL);
  signal (SIGTERM, handle_sigterm);
  async_sigterm_token
    = create_async_signal_handler (async_sigterm_handler, NULL);

  /* If SIGTRAP was set to SIG_IGN, then the SIG_IGN will get passed
     to the inferior and breakpoints will be ignored.  */
#ifdef SIGTRAP
  signal (SIGTRAP, SIG_DFL);
#endif

#ifdef SIGQUIT
  /* If we initialize SIGQUIT to SIG_IGN, then the SIG_IGN will get
     passed to the inferior, which we don't want.  It would be
     possible to do a "signal (SIGQUIT, SIG_DFL)" after we fork, but
     on BSD4.3 systems using vfork, that can affect the
     GDB process as well as the inferior (the signal handling tables
     might be in memory, shared between the two).  Since we establish
     a handler for SIGQUIT, when we call exec it will set the signal
     to SIG_DFL for us.  */
  signal (SIGQUIT, handle_sigquit);
  sigquit_token =
    create_async_signal_handler (async_do_nothing, NULL);
#endif
#ifdef SIGHUP
  if (signal (SIGHUP, handle_sighup) != SIG_IGN)
    sighup_token =
      create_async_signal_handler (async_disconnect, NULL);
  else
    sighup_token =
      create_async_signal_handler (async_do_nothing, NULL);
#endif
  signal (SIGFPE, handle_sigfpe);
  sigfpe_token =
    create_async_signal_handler (async_float_handler, NULL);

#ifdef STOP_SIGNAL
  sigtstp_token =
    create_async_signal_handler (async_stop_sig, NULL);
#endif
}

/* Tell the event loop what to do if SIGINT is received.
   See event-signal.c.  */
void
handle_sigint (int sig)
{
  signal (sig, handle_sigint);

  /* We could be running in a loop reading in symfiles or something so
     it may be quite a while before we get back to the event loop.  So
     set quit_flag to 1 here.  Then if QUIT is called before we get to
     the event loop, we will unwind as expected.  */

  set_quit_flag ();

  /* If immediate_quit is set, we go ahead and process the SIGINT right
     away, even if we usually would defer this to the event loop.  The
     assumption here is that it is safe to process ^C immediately if
     immediate_quit is set.  If we didn't, SIGINT would be really
     processed only the next time through the event loop.  To get to
     that point, though, the command that we want to interrupt needs to
     finish first, which is unacceptable.  If immediate quit is not set,
     we process SIGINT the next time through the loop, which is fine.  */
  gdb_call_async_signal_handler (sigint_token, immediate_quit);
}

/* Handle GDB exit upon receiving SIGTERM if target_can_async_p ().  */

static void
async_sigterm_handler (gdb_client_data arg)
{
  struct ui *ui;

  /* Async signal handlers have no connection to whichever was the
     current UI, and thus always run on the main one.  */
  ui = main_ui;
  current_ui = ui;

  quit_force (NULL, stdin == ui->instream);
}

/* See defs.h.  */
volatile int sync_quit_force_run;

/* Quit GDB if SIGTERM is received.
   GDB would quit anyway, but this way it will clean up properly.  */
void
handle_sigterm (int sig)
{
  signal (sig, handle_sigterm);

  sync_quit_force_run = 1;
  set_quit_flag ();

  mark_async_signal_handler (async_sigterm_token);
}

/* Do the quit.  All the checks have been done by the caller.  */
void
async_request_quit (gdb_client_data arg)
{
  /* If the quit_flag has gotten reset back to 0 by the time we get
     back here, that means that an exception was thrown to unwind the
     current command before we got back to the event loop.  So there
     is no reason to call quit again here.  */

  if (check_quit_flag ())
    quit ();
}

#ifdef SIGQUIT
/* Tell the event loop what to do if SIGQUIT is received.
   See event-signal.c.  */
static void
handle_sigquit (int sig)
{
  mark_async_signal_handler (sigquit_token);
  signal (sig, handle_sigquit);
}
#endif

#if defined (SIGQUIT) || defined (SIGHUP)
/* Called by the event loop in response to a SIGQUIT or an
   ignored SIGHUP.  */
static void
async_do_nothing (gdb_client_data arg)
{
  /* Empty function body.  */
}
#endif

#ifdef SIGHUP
/* Tell the event loop what to do if SIGHUP is received.
   See event-signal.c.  */
static void
handle_sighup (int sig)
{
  mark_async_signal_handler (sighup_token);
  signal (sig, handle_sighup);
}

/* Called by the event loop to process a SIGHUP.  */
static void
async_disconnect (gdb_client_data arg)
{

  TRY
    {
      quit_cover ();
    }

  CATCH (exception, RETURN_MASK_ALL)
    {
      fputs_filtered ("Could not kill the program being debugged",
		      gdb_stderr);
      exception_print (gdb_stderr, exception);
    }
  END_CATCH

  TRY
    {
      pop_all_targets ();
    }
  CATCH (exception, RETURN_MASK_ALL)
    {
    }
  END_CATCH

  signal (SIGHUP, SIG_DFL);	/*FIXME: ???????????  */
  raise (SIGHUP);
}
#endif

#ifdef STOP_SIGNAL
void
handle_stop_sig (int sig)
{
  mark_async_signal_handler (sigtstp_token);
  signal (sig, handle_stop_sig);
}

static void
async_stop_sig (gdb_client_data arg)
{
  char *prompt = get_prompt ();

#if STOP_SIGNAL == SIGTSTP
  signal (SIGTSTP, SIG_DFL);
#if HAVE_SIGPROCMASK
  {
    sigset_t zero;

    sigemptyset (&zero);
    sigprocmask (SIG_SETMASK, &zero, 0);
  }
#elif HAVE_SIGSETMASK
  sigsetmask (0);
#endif
  raise (SIGTSTP);
  signal (SIGTSTP, handle_stop_sig);
#else
  signal (STOP_SIGNAL, handle_stop_sig);
#endif
  printf_unfiltered ("%s", prompt);
  gdb_flush (gdb_stdout);

  /* Forget about any previous command -- null line now will do
     nothing.  */
  dont_repeat ();
}
#endif /* STOP_SIGNAL */

/* Tell the event loop what to do if SIGFPE is received.
   See event-signal.c.  */
static void
handle_sigfpe (int sig)
{
  mark_async_signal_handler (sigfpe_token);
  signal (sig, handle_sigfpe);
}

/* Event loop will call this functin to process a SIGFPE.  */
static void
async_float_handler (gdb_client_data arg)
{
  /* This message is based on ANSI C, section 4.7.  Note that integer
     divide by zero causes this, so "float" is a misnomer.  */
  error (_("Erroneous arithmetic operation."));
}


/* Set things up for readline to be invoked via the alternate
   interface, i.e. via a callback function (rl_callback_read_char),
   and hook up instream to the event loop.  */

void
gdb_setup_readline (int editing)
{
  struct ui *ui = current_ui;

  /* This function is a noop for the sync case.  The assumption is
     that the sync setup is ALL done in gdb_init, and we would only
     mess it up here.  The sync stuff should really go away over
     time.  */
  if (!batch_silent)
    gdb_stdout = stdio_fileopen (ui->outstream);
  gdb_stderr = stderr_fileopen (ui->errstream);
  gdb_stdlog = gdb_stderr;  /* for moment */
  gdb_stdtarg = gdb_stderr; /* for moment */
  gdb_stdtargerr = gdb_stderr; /* for moment */

  /* If the input stream is connected to a terminal, turn on editing.
     However, that is only allowed on the main top level, as we can
     only have one instance of readline.  */
  if (ISATTY (ui->instream) && editing && ui == main_ui)
    {
      /* Tell gdb that we will be using the readline library.  This
	 could be overwritten by a command in .gdbinit like 'set
	 editing on' or 'off'.  */
      ui->command_editing = 1;

      /* When a character is detected on instream by select or poll,
	 readline will be invoked via this callback function.  */
      ui->call_readline = rl_callback_read_char_wrapper;

      /* Tell readline to use the same input stream that gdb uses.  */
      rl_instream = ui->instream;
    }
  else
    {
      ui->command_editing = 0;
      ui->call_readline = gdb_readline_callback_no_editing;
    }

  /* Now create the event source for this UI's input file descriptor.
     Another source is going to be the target program (inferior), but
     that must be registered only when it actually exists (I.e. after
     we say 'run' or after we connect to a remote target.  */
  add_file_handler (ui->input_fd, stdin_event_handler, ui);
}

/* Disable command input through the standard CLI channels.  Used in
   the suspend proc for interpreters that use the standard gdb readline
   interface, like the cli & the mi.  */

void
gdb_disable_readline (void)
{
  struct ui *ui = current_ui;

  /* FIXME - It is too heavyweight to delete and remake these every
     time you run an interpreter that needs readline.  It is probably
     better to have the interpreters cache these, which in turn means
     that this needs to be moved into interpreter specific code.  */

#if 0
  ui_file_delete (gdb_stdout);
  ui_file_delete (gdb_stderr);
  gdb_stdlog = NULL;
  gdb_stdtarg = NULL;
  gdb_stdtargerr = NULL;
#endif

  if (ui->command_editing)
    gdb_rl_callback_handler_remove ();
  delete_file_handler (ui->input_fd);
}
