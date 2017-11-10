/* Low level interface to ptrace, for GDB when running under Unix.
   Copyright (C) 1986-2018 Free Software Foundation, Inc.

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
#include "frame.h"
#include "inferior.h"
#include "command.h"
#include "serial.h"
#include "terminal.h"
#include "target.h"
#include "gdbthread.h"
#include "observer.h"
#include <signal.h>
#include <fcntl.h>
#include "gdb_select.h"
#include <sys/wait.h>

#include "inflow.h"
#include "gdbcmd.h"
#ifdef HAVE_TERMIOS_H
#include <termios.h>
#endif
#include "job-control.h"
#include "top.h"

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifndef O_NOCTTY
#define O_NOCTTY 0
#endif

static void pass_signal (int);

static void child_terminal_ours_1 (target_terminal_state);

/* Record terminal status separately for debugger and inferior.  */

static struct serial *stdin_serial;

struct run_terminal_info
{
  ~run_terminal_info ()
  {
    xfree (this->ttyname);
  }

  /* The name of the tty (from the `tty' command) that we gave to the
     inferior when it was started.  */
  char *ttyname = NULL;

  int master_fd = -1;
  pid_t session_leader = -1;

  int refc = 0;
};

/* Terminal related info we need to keep track of.  Each inferior
   holds an instance of this structure --- we save it whenever the
   corresponding inferior stops, and restore it to the terminal when
   the inferior is resumed in the foreground.  */
struct terminal_info
{
  ~terminal_info ()
  {
    delete this->run_terminal;
    xfree (this->ttystate);
  }

  /* The name of the tty (from the `tty' command) that we gave to the
     inferior when it was started.  */
  run_terminal_info *run_terminal = NULL;

  /* TTY state.  We save it whenever the inferior stops, and restore
     it when it resumes in the foreground.  */
  serial_ttystate ttystate = NULL;

#ifdef HAVE_TERMIOS_H
  /* The terminal's foreground process group.  Saved whenever the
     inferior stops.  This is the pgrp displayed by "info terminal".
     Note that this may be not the inferior's actual process group,
     since each inferior that we spawn has its own process group, and
     only one can be in the foreground at a time.  When the inferior
     resumes, if we can determine the inferior's actual pgrp, then we
     make that the foreground pgrp instead of what was saved here.
     While it's a bit arbitrary which inferior's pgrp ends up in the
     foreground when we resume several inferiors, this at least makes
     'resume inf1+inf2' + 'stop all' + 'resume inf2' end up with
     inf2's pgrp in the foreground instead of inf1's (which would be
     problematic since it would be left stopped: Ctrl-C wouldn't work,
     for example).  */
  pid_t process_group = -1;
#endif

  /* fcntl flags.  Saved and restored just like ttystate.  */
  int tflags = 0;
};

/* Our own tty state, which we restore every time we need to deal with
   the terminal.  This is set once, when GDB first starts, and then
   whenever we enter/leave TUI mode (gdb_save_tty_state).  The
   settings of flags which readline saves and restores are
   unimportant.  */
static struct terminal_info our_terminal_info;

/* Snapshot of the initial tty state taken during initialization of
   GDB, before readline/ncurses have had a chance to change it.  This
   is used as the initial tty state given to each new spawned
   inferior.  Unlike our_terminal_info, this is only ever set
   once.  */
static serial_ttystate initial_gdb_ttystate;

static struct terminal_info *get_inflow_inferior_data (struct inferior *);

/* RAII class used to ignore SIGTTOU in a scope.  */

class scoped_ignore_sigttou
{
public:
  scoped_ignore_sigttou ()
  {
#ifdef SIGTTOU
    if (job_control)
      m_osigttou = signal (SIGTTOU, SIG_IGN);
#endif
  }

  ~scoped_ignore_sigttou ()
  {
#ifdef SIGTTOU
    if (job_control)
      signal (SIGTTOU, m_osigttou);
#endif
  }

  DISABLE_COPY_AND_ASSIGN (scoped_ignore_sigttou);

private:
#ifdef SIGTTOU
  sighandler_t m_osigttou = NULL;
#endif
};

/* While the inferior is running, we want SIGINT and SIGQUIT to go to the
   inferior only.  If we have job control, that takes care of it.  If not,
   we save our handlers in these two variables and set SIGINT and SIGQUIT
   to SIG_IGN.  */

static sighandler_t sigint_ours;
static sighandler_t sigquit_ours;

/* The name of the tty (from the `tty' command) that we're giving to
   the inferior when starting it up.  This is only (and should only
   be) used as a transient global by new_tty_prefork,
   create_tty_session, new_tty and new_tty_postfork, all called from
   fork_inferior, while forking a new child.  */
static const char *inferior_thisrun_terminal;

static int inferior_thisrun_terminal_master_fd = -1;

/* Track who owns GDB's terminal (is it GDB or some inferior?).  While
   target_terminal::is_ours() etc. tracks the core's intention and is
   independent of the target backend, this tracks the actual state of
   GDB's own tty.  So for example,

     (target_terminal::is_inferior () && gdb_tty_state == terminal_is_ours)

   is true when the (native) inferior is not sharing a terminal with
   GDB (e.g., because we attached to an inferior that is running on a
   different terminal).  */
static target_terminal_state gdb_tty_state = target_terminal_state::is_ours;

static bool input_fd_redirected = false;

/* See terminal.h.  */

void
set_initial_gdb_ttystate (void)
{
  /* Note we can't do any of this in _initialize_inflow because at
     that point stdin_serial has not been created yet.  */

  initial_gdb_ttystate = serial_get_tty_state (stdin_serial);

  if (initial_gdb_ttystate != NULL)
    {
      our_terminal_info.ttystate
	= serial_copy_tty_state (stdin_serial, initial_gdb_ttystate);
#ifdef F_GETFL
      our_terminal_info.tflags = fcntl (0, F_GETFL, 0);
#endif
#ifdef HAVE_TERMIOS_H
      our_terminal_info.process_group = tcgetpgrp (0);
#endif
    }
}

/* Does GDB have a terminal (on stdin)?  */

static int
gdb_has_a_terminal (void)
{
  return initial_gdb_ttystate != NULL;
}

/* Macro for printing errors from ioctl operations */

#define	OOPSY(what)	\
  if (result == -1)	\
    fprintf_unfiltered(gdb_stderr, "[%s failed in terminal_inferior: %s]\n", \
	    what, safe_strerror (errno))

/* Initialize the terminal settings we record for the inferior,
   before we actually run the inferior.  */

void
child_terminal_init (struct target_ops *self)
{
  if (!gdb_has_a_terminal ())
    return;

  inferior *inf = current_inferior ();
  terminal_info *tinfo = get_inflow_inferior_data (inf);

#ifdef HAVE_TERMIOS_H
  /* A child we spawn should be a process group leader (PGID==PID) at
     this point, though that may not be true if we're attaching to an
     existing process.  */
  tinfo->process_group = inf->pid;
#endif

  xfree (tinfo->ttystate);
  tinfo->ttystate = serial_copy_tty_state (stdin_serial, initial_gdb_ttystate);
}

/* Save the terminal settings again.  This is necessary for the TUI
   when it switches to TUI or non-TUI mode;  curses changes the terminal
   and gdb must be able to restore it correctly.  */

void
gdb_save_tty_state (void)
{
  if (gdb_has_a_terminal ())
    {
      xfree (our_terminal_info.ttystate);
      our_terminal_info.ttystate = serial_get_tty_state (stdin_serial);
    }
}

/* Try to determine whether TTY is GDB's input terminal.  Returns
   TRIBOOL_UNKNOWN if we can't tell.  */

static tribool
is_gdb_terminal (const char *tty)
{
  struct stat gdb_tty;
  struct stat other_tty;
  int res;

  if (strcmp (tty, "/dev/tty") == 0)
    return TRIBOOL_TRUE;

  res = stat (tty, &other_tty);
  if (res == -1)
    return TRIBOOL_UNKNOWN;

  res = fstat (STDIN_FILENO, &gdb_tty);
  if (res == -1)
    return TRIBOOL_UNKNOWN;

  return ((gdb_tty.st_dev == other_tty.st_dev
	   && gdb_tty.st_ino == other_tty.st_ino)
	  ? TRIBOOL_TRUE
	  : TRIBOOL_FALSE);
}

/* Helper for sharing_input_terminal.  Try to determine whether
   inferior INF is using the same TTY for input as GDB is.  Returns
   TRIBOOL_UNKNOWN if we can't tell.  */

static tribool
sharing_input_terminal_1 (inferior *inf)
{
  /* Using host-dependent code here is fine, because the
     child_terminal_foo functions are meant to be used by child/native
     targets.  */
#if defined (__linux__) || defined (__sun__)
  char buf[100];

  xsnprintf (buf, sizeof (buf), "/proc/%d/fd/0", inf->pid);
  return is_gdb_terminal (buf);
#else
  return TRIBOOL_UNKNOWN;
#endif
}

/* Return true if the inferior is using the same TTY for input as GDB
   is.  If this is true, then we save/restore terminal flags/state.

   This is necessary because if inf->attach_flag is set, we don't
   offhand know whether we are sharing a terminal with the inferior or
   not.  Attaching a process without a terminal is one case where we
   do not; attaching a process which we ran from the same shell as GDB
   via `&' is one case where we do.

   If we can't determine, we assume the TTY is being shared.  This
   works OK if you're only debugging one inferior.  However, if you're
   debugging more than one inferior, and e.g., one is spawned by GDB
   with "run" (sharing terminal with GDB), and another is attached to
   (and running on a different terminal, as is most common), then it
   matters, because we can only restore the terminal settings of one
   of the inferiors, and in that scenario, we want to restore the
   settings of the "run"'ed inferior.

   Note, this is not the same as determining whether GDB and the
   inferior are in the same session / connected to the same
   controlling tty.  An inferior (fork child) may call setsid,
   disconnecting itself from the ctty, while still leaving
   stdin/stdout/stderr associated with the original terminal.  If
   we're debugging that process, we should also save/restore terminal
   settings.  */

static bool
sharing_input_terminal (inferior *inf)
{
  terminal_info *tinfo = get_inflow_inferior_data (inf);

  tribool res = sharing_input_terminal_1 (inf);

  if (res == TRIBOOL_UNKNOWN)
    {
      /* As fallback, if we can't determine by stat'ing the inferior's
	 tty directly (because it's not supported on this host) and
	 the child was spawned, check whether run_terminal is our tty.
	 This isn't ideal, since this is checking the child's
	 controlling terminal, not the input terminal (which may have
	 been redirected), but is still better than nothing.  A false
	 positive ("set inferior-tty" points to our terminal, but I/O
	 was redirected) is much more likely than a false negative
	 ("set inferior-tty" points to some other terminal, and then
	 output was redirected to our terminal), and with a false
	 positive we just end up trying to save/restore terminal
	 settings when we didn't need to or we actually can't.  */
      if (tinfo->run_terminal != NULL)
	res = is_gdb_terminal (tinfo->run_terminal->ttyname);

      /* If we still can't determine, assume yes.  */
      if (res == TRIBOOL_UNKNOWN)
	return true;
    }

  return res == TRIBOOL_TRUE;
}

#include "event-loop.h"

static int debug_terminal = 0;

/* Wrappers around tcgetattr/tcsetattr to log errors.  We don't throw
   on error instead because an error here is most likely caused by
   stdin having been closed (e.g., GDB lost its terminal), and we may
   be called while handling/printing exceptions.  E.g., from
   target_target::ours_for_output() before printing an exception
   message.  */

static int
gdb_tcgetattr (int fd, struct termios *termios)
{
  if (tcgetattr (fd, termios) != 0)
    {
      if (debug_terminal)
	{
	  int err = errno;

	  fprintf_unfiltered (gdb_stderr,
			      _("[tcgetattr(fd=%d) failed: %d (%s)"),
			      fd, err, safe_strerror (err));
	}
      return -1;
    }

  return 0;
}

/* See gdb_tcgetattr.  */

static int
gdb_tcsetattr (int fd, int optional_actions, struct termios *termios)
{
  if (tcsetattr (fd, optional_actions, termios) != 0)
    {
      if (debug_terminal)
	{
	  int err = errno;

	  fprintf_unfiltered (gdb_stderr,
			      _("[tcsetattr(fd=%d) failed: %d (%s)"),
			      fd, err, safe_strerror (err));
	}
      return -1;
    }

  return 0;
}

/* Disable echo, canonical mode, and \r\n -> \n translation.  Leave
   ISIG, since we want to grab Ctrl-C before the inferior sees it.  */

static void
make_raw (struct termios *termios)
{
  termios->c_iflag &= ~(INLCR | IGNCR | ICRNL);
  termios->c_oflag = 0;
  termios->c_lflag &= ~(ECHO | ICANON);
  termios->c_cflag &= ~CSIZE;
  termios->c_cflag |= CLOCAL | CS8;
  termios->c_cc[VMIN] = 0;
  termios->c_cc[VTIME] = 0;
}

static void
set_raw ()
{
  struct termios termios;

  if (gdb_tcgetattr (STDIN_FILENO, &termios) == 0)
    {
      make_raw (&termios);
      gdb_tcsetattr (STDIN_FILENO, TCSADRAIN, &termios);
    }
}

class scoped_termios
{
public:
  scoped_termios ()
  {
    if (gdb_tcgetattr (STDIN_FILENO, &m_saved_termios) == 0)
      {
	m_saved_termios_p = true;

	struct termios raw_termios = m_saved_termios;
	make_raw (&raw_termios);
	gdb_tcsetattr (STDIN_FILENO, TCSADRAIN, &raw_termios);
      }
  }

  ~scoped_termios ()
  {
    if (m_saved_termios_p)
      gdb_tcsetattr (STDIN_FILENO, TCSADRAIN, &m_saved_termios);
  }

private:
  /* The saved termios data.  */
  struct termios m_saved_termios;

  /* True iff M_SAVED_TERMIOS is valid.  */
  bool m_saved_termios_p;
};

extern int tui_write_raw;

static void
child_terminal_flush_from_to (int read_fd, int write_fd,
			      const char *what)
{
  char buf[1024];

  scoped_termios save_termios;

  while (1)
    {
      int r = read (read_fd, buf, sizeof (buf));
      if (r <= 0)
	{
	  if (r == 0)
	    ;
	  else if (r == -1 && errno == EAGAIN)
	    ;
	  else if (r == -1 && errno == EIO)
	    {
	      if (debug_terminal)
		fprintf_unfiltered (gdb_stdlog, _("%s: bad read: closed?\n"),
				    what);
	    }
	  else
	    {
	      int err = errno;
	      fprintf_unfiltered (gdb_stdlog, _("%s: bad read: %d: (%d) %s\n"),
				  what, r, err, safe_strerror (err));
	    }
	  return;
	}

      const char *p = buf;

      while (r > 0)
	{
	  int w;

	  if (write_fd == STDOUT_FILENO)
	    {
	      scoped_restore restore_tui
		= make_scoped_restore (&tui_write_raw,  1);

	      gdb_stdout->write (p, r);
	      w = r;
	    }
	  else {

	  w = write (write_fd, p, r);
	  if (w == -1 && errno == EAGAIN)
	    continue;
	  else if (w <= 0)
	    {
	      int err = errno;
	      fprintf_unfiltered (gdb_stdlog, _("%s: bad write: %d: (%d) %s\n"),
				  what, r, err, safe_strerror (err));
	      return;
	    }

	  }

	  r -= w;
	  p += w;
	}
    }
}

static void
child_terminal_flush_stdout (run_terminal_info *run_terminal)
{
  gdb_assert (run_terminal->master_fd != -1);
  child_terminal_flush_from_to (run_terminal->master_fd, STDOUT_FILENO,
				"stdout");
}

static void
inferior_stdout_event_handler (int error, gdb_client_data client_data)
{
  run_terminal_info *run_terminal = (run_terminal_info *) client_data;
  child_terminal_flush_stdout (run_terminal);
}

static void
inferior_stdin_event_handler (int error, gdb_client_data client_data)
{
  run_terminal_info *run_terminal = (run_terminal_info *) client_data;
  gdb_assert (run_terminal->master_fd != -1);
  child_terminal_flush_from_to (STDIN_FILENO, run_terminal->master_fd,
				"stdin");
}

/* Put the inferior's terminal settings into effect.  This is
   preparation for starting or resuming the inferior.  */

void
child_terminal_inferior (struct target_ops *self)
{
  /* If we resume more than one inferior in the foreground on GDB's
     terminal, then the first inferior's terminal settings "win".
     Note that every child process is put in its own process group, so
     the first process that ends up resumed ends up determining which
     process group the kernel forwards Ctrl-C/Ctrl-Z (SIGINT/SIGTTOU)
     to.  */
  if (gdb_tty_state == target_terminal_state::is_inferior)
    return;

  inferior *inf = current_inferior ();
  terminal_info *tinfo = get_inflow_inferior_data (inf);

  if (gdb_has_a_terminal ()
      && tinfo->ttystate != NULL
      && ((tinfo->run_terminal != NULL
	   && tinfo->run_terminal->master_fd != -1)
	  || sharing_input_terminal (inf)))
    {
      int result;

      if (!job_control)
	{
	  sigint_ours = signal (SIGINT, SIG_IGN);
#ifdef SIGQUIT
	  sigquit_ours = signal (SIGQUIT, SIG_IGN);
#endif
	}

      scoped_ignore_sigttou ignore_sigttou;

      if (tinfo->run_terminal == NULL
	  || tinfo->run_terminal->master_fd == -1)
	{
#ifdef F_GETFL
	  result = fcntl (0, F_SETFL, tinfo->tflags);
	  OOPSY ("fcntl F_SETFL");
#endif

	  result = serial_set_tty_state (stdin_serial, tinfo->ttystate);
	  OOPSY ("setting tty state");
	}

      if (tinfo->run_terminal != NULL
	  && tinfo->run_terminal->master_fd != -1)
	{
	  /* Disable ECHO/ICANON.  */
	  set_raw ();

	  add_file_handler (0, inferior_stdin_event_handler,
			    tinfo->run_terminal);

	  input_fd_redirected = true;
	}
      else if (job_control)
	{
#ifdef HAVE_TERMIOS_H
	  /* If we can't tell the inferior's actual process group,
	     then restore whatever was the foreground pgrp the last
	     time the inferior was running.  See also comments
	     describing terminal_state::process_group.  */
#ifdef HAVE_GETPGID
	  result = tcsetpgrp (0, getpgid (inf->pid));
#else
	  result = tcsetpgrp (0, tinfo->process_group);
#endif
	  if (result == -1)
	    {
#if 0
	      /* This fails if either GDB has no controlling terminal,
		 e.g., running under 'setsid(1)', or if the inferior
		 is not attached to GDB's controlling terminal.  E.g.,
		 if it called setsid to create a new session or used
		 the TIOCNOTTY ioctl, or simply if we've attached to a
		 process running on another terminal and we couldn't
		 tell whether it was sharing GDB's terminal (and so
		 assumed yes).  */
	      fprintf_unfiltered
		(gdb_stderr,
		 "[tcsetpgrp failed in child_terminal_inferior: %s]\n",
		 safe_strerror (errno));
#endif
	    }
#endif
	}

      gdb_tty_state = target_terminal_state::is_inferior;
    }
}

/* Put some of our terminal settings into effect,
   enough to get proper results from our output,
   but do not change into or out of RAW mode
   so that no input is discarded.

   After doing this, either terminal_ours or terminal_inferior
   should be called to get back to a normal state of affairs.

   N.B. The implementation is (currently) no different than
   child_terminal_ours.  See child_terminal_ours_1.  */

void
child_terminal_ours_for_output (struct target_ops *self)
{
  child_terminal_ours_1 (target_terminal_state::is_ours_for_output);
}

/* Put our terminal settings into effect.
   First record the inferior's terminal settings
   so they can be restored properly later.

   N.B. Targets that want to use this with async support must build that
   support on top of this (e.g., the caller still needs to add stdin to the
   event loop).  E.g., see linux_nat_terminal_ours.  */

void
child_terminal_ours (struct target_ops *self)
{
  child_terminal_ours_1 (target_terminal_state::is_ours);
}

/* Save the current terminal settings in the inferior's terminal_info
   cache.  */

void
child_terminal_save_inferior (struct target_ops *self)
{
  /* Avoid attempting all the ioctl's when running in batch.  */
  if (!gdb_has_a_terminal ())
    return;

  inferior *inf = current_inferior ();
  terminal_info *tinfo = get_inflow_inferior_data (inf);
  run_terminal_info *run_terminal = tinfo->run_terminal;

  if (run_terminal != NULL && run_terminal->master_fd != -1)
    {
      child_terminal_flush_stdout (run_terminal);
      return;
    }

  /* No need to save/restore if the inferior is not sharing GDB's
     tty.  */
  if (!sharing_input_terminal (inf))
    return;

  xfree (tinfo->ttystate);
  tinfo->ttystate = serial_get_tty_state (stdin_serial);

#ifdef HAVE_TERMIOS_H
  tinfo->process_group = tcgetpgrp (0);
#endif

#ifdef F_GETFL
  tinfo->tflags = fcntl (0, F_GETFL, 0);
#endif
}

/* Switch terminal state to DESIRED_STATE, either is_ours, or
   is_ours_for_output.  */

static void
child_terminal_ours_1 (target_terminal_state desired_state)
{
  gdb_assert (desired_state != target_terminal_state::is_inferior);

  /* Avoid attempting all the ioctl's when running in batch.  */
  if (!gdb_has_a_terminal ())
    return;

  if (gdb_tty_state != desired_state)
    {
      int result ATTRIBUTE_UNUSED;

      /* Ignore SIGTTOU since it will happen when we try to set the
	 terminal's pgrp.  */
      scoped_ignore_sigttou ignore_sigttou;

      serial_set_tty_state (stdin_serial, our_terminal_info.ttystate);

      /* If we only want output, then:
	  - if the inferior is sharing GDB's session, leave the
	    inferior's pgrp in the foreground, so that Ctrl-C/Ctrl-Z
	    reach the inferior directly.
	  - if the inferior has its own session, leave stdin
            forwarding to the inferior.  */
      if (job_control && desired_state == target_terminal_state::is_ours)
	{
	  if (input_fd_redirected)
	    {
	      delete_file_handler (0);
	      input_fd_redirected = false;
	    }
	  else
	    {
#ifdef HAVE_TERMIOS_H
	      result = tcsetpgrp (0, our_terminal_info.process_group);
#if 0
	      /* This fails on Ultrix with EINVAL if you run the
		 testsuite in the background with nohup, and then log
		 out.  GDB never used to check for an error here, so
		 perhaps there are other such situations as well.  */
	      if (result == -1)
		fprintf_unfiltered (gdb_stderr,
				    "[tcsetpgrp failed in child_terminal_ours: %s]\n",
				    safe_strerror (errno));
#endif
#endif /* termios */
	    }
	}

      if (!job_control && desired_state == target_terminal_state::is_ours)
	{
	  signal (SIGINT, sigint_ours);
#ifdef SIGQUIT
	  signal (SIGQUIT, sigquit_ours);
#endif
	}

#ifdef F_GETFL
      result = fcntl (0, F_SETFL, our_terminal_info.tflags);
#endif

      gdb_tty_state = desired_state;
    }
}

/* Interrupt the inferior.  Implementation of target_interrupt for
   child/native targets.  */

void
child_interrupt (struct target_ops *self)
{
  /* Interrupt the first inferior that has a resumed thread.  */
  thread_info *thr;
  thread_info *resumed = NULL;
  ALL_NON_EXITED_THREADS (thr)
    {
      if (thr->executing)
	{
	  resumed = thr;
	  break;
	}
      if (thr->suspend.waitstatus_pending_p)
	resumed = thr;
    }

  if (resumed != NULL)
    {
      /* Note that unlike pressing Ctrl-C on the controlling terminal,
	 here we only interrupt one process, not the whole process
	 group.  This is because interrupting a process group (with
	 either Ctrl-C or with kill(3) with negative PID) sends a
	 SIGINT to each process in the process group, and we may not
	 be debugging all processes in the process group.  */
#ifndef _WIN32
      kill (resumed->inf->pid, SIGINT);
#endif
    }
}

/* Pass a Ctrl-C to the inferior as-if a Ctrl-C was pressed while the
   inferior was in the foreground.  Implementation of
   target_pass_ctrlc for child/native targets.  */

void
child_pass_ctrlc (struct target_ops *self)
{
  gdb_assert (!target_terminal::is_ours ());

#ifdef HAVE_TERMIOS_H
  if (job_control)
    {
      pid_t term_pgrp = tcgetpgrp (0);

      /* If there's any inferior sharing our terminal, pass the SIGINT
	 to the terminal's foreground process group.  This acts just
	 like the user typed a ^C on the terminal while the inferior
	 was in the foreground.  Note that using a negative process
	 number in kill() is a System V-ism.  The proper BSD interface
	 is killpg().  However, all modern BSDs support the System V
	 interface too.  */

      if (term_pgrp != -1 && term_pgrp != our_terminal_info.process_group)
	{
	  kill (-term_pgrp, SIGINT);
	  return;
	}
    }
#endif

  /* Otherwise, pass the Ctrl-C to the first inferior that was resumed
     in the foreground.  */
  inferior *inf;
  ALL_INFERIORS (inf)
    {
      if (inf->terminal_state != target_terminal_state::is_ours)
	{
	  gdb_assert (inf->pid != 0);

#ifndef _WIN32
	  kill (inf->pid, SIGINT);
#endif
	  return;
	}
    }

  /* If no inferior was resumed in the foreground, then how did the
     !is_ours assert above pass?  */
  gdb_assert_not_reached ("no inferior resumed in the fg found");
}

/* Per-inferior data key.  */
static const struct inferior_data *inflow_inferior_data;

static void
inflow_inferior_data_cleanup (struct inferior *inf, void *arg)
{
  terminal_info *info = (terminal_info *) arg;
  delete info;
}

/* Get the current svr4 data.  If none is found yet, add it now.  This
   function always returns a valid object.  */

static struct terminal_info *
get_inflow_inferior_data (struct inferior *inf)
{
  struct terminal_info *info;

  info = (struct terminal_info *) inferior_data (inf, inflow_inferior_data);
  if (info == NULL)
    {
      info = new terminal_info ();
      set_inferior_data (inf, inflow_inferior_data, info);
    }

  return info;
}

#ifdef TIOCGWINSZ

/* See inferior.h.  */

void
child_terminal_on_sigwinch ()
{
  struct winsize size;

  if (ioctl (0, TIOCGWINSZ, &size) == -1)
    return;

  /* For each inferior that is connected to a terminal that we
     created, resize the inferior's terminal to match GDB's.  */
  inferior *inf;
  ALL_INFERIORS (inf)
    {
      terminal_info *info
	= (terminal_info *) inferior_data (inf, inflow_inferior_data);
      if (info != NULL
	  && info->run_terminal != NULL
	  && info->run_terminal->master_fd != -1)
	ioctl (info->run_terminal->master_fd, TIOCSWINSZ, &size);
    }
}

#endif

#ifdef SIGTSTP

void
child_terminal_on_sigtstp (int)
{
  if (!target_terminal::is_ours ())
    {
      bool any = false;

      inferior *inf;
      ALL_INFERIORS (inf)
        {
	  if (inf->terminal_state == target_terminal_state::is_ours)
	    continue;

	  terminal_info *info
	    = (terminal_info *) inferior_data (inf, inflow_inferior_data);
	  if (info == NULL
	      || info->run_terminal == NULL
	      || info->run_terminal->master_fd == -1)
	    continue;

	  kill (inf->pid, SIGTSTP);
	  any = true;
	}

      if (any)
	return;
    }

  signal (SIGTSTP, SIG_DFL);
  raise (SIGTSTP);
}

#endif /* SIGTTOU */

/* This is a "inferior_exit" observer.  Releases the TERMINAL_INFO member
   of the inferior structure.  This field is private to inflow.c, and
   its type is opaque to the rest of GDB.  PID is the target pid of
   the inferior that is about to be removed from the inferior
   list.  */

static void
inflow_inferior_exit (struct inferior *inf)
{
  struct terminal_info *info;

  inf->terminal_state = target_terminal_state::is_ours;

  info = (struct terminal_info *) inferior_data (inf, inflow_inferior_data);
  if (info != NULL)
    {
      if (info->run_terminal != NULL)
	{
	  run_terminal_info *run_terminal = info->run_terminal;

	  if (--run_terminal->refc == 0)
	    {
	      if (run_terminal->master_fd != -1)
		{
		  delete_file_handler (run_terminal->master_fd);
		  child_terminal_flush_stdout (run_terminal);
		  close (run_terminal->master_fd);

		  /* Since we closed the controlling terminal, the
		     session leader should exit now, killed by SIGHUP.
		     Reap it.  */
		  if (debug_terminal)
		    fprintf_unfiltered (gdb_stdlog, "reaping session leader: %d\n",
					(int) run_terminal->session_leader);

		  int status;
		  int res = waitpid (run_terminal->session_leader,
				     &status, 0);
		  if (res == -1)
		    warning (_("unexpected waitstatus "
			       "reaping session leader: res=-1, errno=%d (%s)"),
			     errno, safe_strerror (errno));
		  else if (res != run_terminal->session_leader
			   || !WIFSIGNALED (status)
			   || WTERMSIG (status) != SIGHUP)
		    warning (_("unexpected waitstatus "
			       "reaping session leader: res=%d, status=0x%x"),
			       res, status);
		}
	      delete run_terminal;
	    }
	  info->run_terminal = NULL;
	}

      delete info;
      set_inferior_data (inf, inflow_inferior_data, NULL);
    }
}

bool
child_gdb_owns_session (inferior *inf)
{
  auto *info = (struct terminal_info *) inferior_data (inf, inflow_inferior_data);
  if (info != NULL)
    {
      auto *run_terminal = info->run_terminal;
      if (run_terminal != NULL && run_terminal->master_fd != -1)
	{
	  pid_t session = getsid (inf->pid);
	  return (session == run_terminal->session_leader);
	}
    }

  return false;
}

void
copy_terminal_info (struct inferior *to, struct inferior *from)
{
  struct terminal_info *tinfo_to, *tinfo_from;

  to->terminal_state = from->terminal_state;

  tinfo_to = (terminal_info *) inferior_data (to, inflow_inferior_data);
  gdb_assert (tinfo_to == NULL);

  tinfo_from = (terminal_info *) inferior_data (from, inflow_inferior_data);
  if (tinfo_from == NULL)
    {
      /* Nothing to copy.  */
      return;
    }

  tinfo_to = new terminal_info ();
  set_inferior_data (to, inflow_inferior_data, tinfo_to);

  *tinfo_to = *tinfo_from;
  if (tinfo_from->run_terminal != NULL)
    tinfo_from->run_terminal->refc++;

  if (tinfo_from->ttystate)
    tinfo_to->ttystate
      = serial_copy_tty_state (stdin_serial, tinfo_from->ttystate);

  /* Copy FROM's "set inferior-tty TTY" setting value at the time FROM
     was started to TO.  XXX should this copy the current value
     instead?  */
  if (tinfo_from->run_terminal != NULL
      && tinfo_from->run_terminal->master_fd == -1)
    to->set_tty (tinfo_from->run_terminal->ttyname);
}

void
info_terminal_command (const char *arg, int from_tty)
{
  target_terminal::info (arg, from_tty);
}

void
child_terminal_info (struct target_ops *self, const char *args, int from_tty)
{
  struct inferior *inf;
  struct terminal_info *tinfo;

  if (!gdb_has_a_terminal ())
    {
      printf_filtered (_("This GDB does not control a terminal.\n"));
      return;
    }

  if (ptid_equal (inferior_ptid, null_ptid))
    return;

  inf = current_inferior ();
  tinfo = get_inflow_inferior_data (inf);

  printf_filtered (_("Inferior's terminal status "
		     "(currently saved by GDB):\n"));

  /* First the fcntl flags.  */
  {
    int flags;

    flags = tinfo->tflags;

    printf_filtered ("File descriptor flags = ");

#ifndef O_ACCMODE
#define O_ACCMODE (O_RDONLY | O_WRONLY | O_RDWR)
#endif
    /* (O_ACCMODE) parens are to avoid Ultrix header file bug.  */
    switch (flags & (O_ACCMODE))
      {
      case O_RDONLY:
	printf_filtered ("O_RDONLY");
	break;
      case O_WRONLY:
	printf_filtered ("O_WRONLY");
	break;
      case O_RDWR:
	printf_filtered ("O_RDWR");
	break;
      }
    flags &= ~(O_ACCMODE);

#ifdef O_NONBLOCK
    if (flags & O_NONBLOCK)
      printf_filtered (" | O_NONBLOCK");
    flags &= ~O_NONBLOCK;
#endif

#if defined (O_NDELAY)
    /* If O_NDELAY and O_NONBLOCK are defined to the same thing, we will
       print it as O_NONBLOCK, which is good cause that is what POSIX
       has, and the flag will already be cleared by the time we get here.  */
    if (flags & O_NDELAY)
      printf_filtered (" | O_NDELAY");
    flags &= ~O_NDELAY;
#endif

    if (flags & O_APPEND)
      printf_filtered (" | O_APPEND");
    flags &= ~O_APPEND;

#if defined (O_BINARY)
    if (flags & O_BINARY)
      printf_filtered (" | O_BINARY");
    flags &= ~O_BINARY;
#endif

    if (flags)
      printf_filtered (" | 0x%x", flags);
    printf_filtered ("\n");
  }

#ifdef HAVE_TERMIOS_H
  printf_filtered ("Process group = %d\n", (int) tinfo->process_group);
#endif

  serial_print_tty_state (stdin_serial, tinfo->ttystate, gdb_stdout);
}

/* NEW_TTY_PREFORK is called before forking a new child process,
   so we can record the state of ttys in the child to be formed.
   TTYNAME is null if we are to share the terminal with gdb;
   or points to a string containing the name of the desired tty.

   NEW_TTY is called in new child processes under Unix, which will
   become debugger target processes.  This actually switches to
   the terminal specified in the NEW_TTY_PREFORK call.  */

void
new_tty_prefork (const char *ttyname)
{
  /* Save the name for later, for determining whether we and the child
     are sharing a tty.  */

  if (ttyname != NULL)
    {
      inferior_thisrun_terminal = ttyname;
      inferior_thisrun_terminal_master_fd = -1;
    }
  else
    {
      /* Open an unused pty master device.  */
      int master_fd = posix_openpt (O_RDWR | O_NONBLOCK | O_CLOEXEC | O_NOCTTY);
      if (master_fd == -1)
	perror_with_name ("posix_openpt");

      /* Grant access to the slave pty.  */
      if (grantpt (master_fd) == -1)
	{
	  close (master_fd); /* FIXME: errno.  */
	  perror_with_name ("grantpt");
	}

      /* Unlock the pty master/slave pair.  */
      if (unlockpt (master_fd) == -1)
	{
	  close (master_fd);
	  perror_with_name ("unlockpt");
	}

      inferior_thisrun_terminal = ptsname (master_fd);
      inferior_thisrun_terminal_master_fd = master_fd;

      serial *master_fd_serial = serial_fdopen (master_fd);
      int result = serial_set_tty_state (master_fd_serial, initial_gdb_ttystate);
      gdb_assert (result != -1);
      OOPSY ("setting tty state");

      serial_un_fdopen (master_fd_serial);
    }
}

#if !defined(__GO32__) && !defined(_WIN32)
/* If RESULT, assumed to be the return value from a system call, is
   negative, print the error message indicated by errno and exit.
   MSG should identify the operation that failed.  */
static void
check_syscall (const char *msg, int result)
{
  if (result < 0)
    {
      print_sys_errmsg (msg, errno);
      _exit (1);
    }
}
#endif

bool
created_managed_tty ()
{
  return inferior_thisrun_terminal_master_fd != -1;
}

void
new_tty (void)
{
  int tty;

  if (inferior_thisrun_terminal == 0
      || is_gdb_terminal (inferior_thisrun_terminal))
    return;
#if !defined(__GO32__) && !defined(_WIN32)
#ifdef TIOCNOTTY
  /* Disconnect the child process from our controlling terminal.  On some
     systems (SVR4 for example), this may cause a SIGTTOU, so temporarily
     ignore SIGTTOU.  */
  tty = open ("/dev/tty", O_RDWR);
  if (tty > 0)
    {
      scoped_ignore_sigttou ignore_sigttou;

      ioctl (tty, TIOCNOTTY, 0);
      close (tty);
    }
#endif

  /* Now open the specified new terminal.  */
  tty = open (inferior_thisrun_terminal, O_RDWR | O_NOCTTY);
  check_syscall (inferior_thisrun_terminal, tty);

  /* Avoid use of dup2; doesn't exist on all systems.  */
  if (tty != 0)
    {
      close (0);
      check_syscall ("dup'ing tty into fd 0", dup (tty));
    }
  if (tty != 1)
    {
      close (1);
      check_syscall ("dup'ing tty into fd 1", dup (tty));
    }
  if (tty != 2)
    {
      close (2);
      check_syscall ("dup'ing tty into fd 2", dup (tty));
    }

#ifdef TIOCSCTTY
  /* Make tty our new controlling terminal.  */
  if (ioctl (tty, TIOCSCTTY, 0) == -1)
    /* Mention GDB in warning because it will appear in the inferior's
       terminal instead of GDB's.  */
    warning (_("GDB: Failed to set controlling terminal: %s"),
	     safe_strerror (errno));
#endif

  if (tty > 2)
    close (tty);
#endif /* !go32 && !win32 */
}

/* NEW_TTY_POSTFORK is called after forking a new child process, and
   adding it to the inferior table, to store the TTYNAME being used by
   the child, or null if it sharing the terminal with gdb.  */

void
new_tty_postfork (void)
{
  /* Save the name for later, for determining whether we and the child
     are sharing a tty.  */

  struct inferior *inf = current_inferior ();
  struct terminal_info *tinfo = get_inflow_inferior_data (inf);
  auto *run_terminal = new run_terminal_info ();
  tinfo->run_terminal = run_terminal;

  if (inferior_thisrun_terminal)
    {
      run_terminal->ttyname = xstrdup (inferior_thisrun_terminal);
      run_terminal->master_fd = inferior_thisrun_terminal_master_fd;
      if (run_terminal->master_fd != -1)
	{
	  run_terminal->session_leader = getsid (inf->pid);
	  gdb_assert (run_terminal->session_leader != -1);
	}
      run_terminal->refc = 1;

      if (run_terminal->master_fd != -1)
	{
	  add_file_handler (run_terminal->master_fd,
			    inferior_stdout_event_handler, run_terminal);
	}
    }
  else
    run_terminal->ttyname = xstrdup ("/dev/tty");

  inferior_thisrun_terminal = NULL;
  inferior_thisrun_terminal_master_fd = -1;
}


/* Call set_sigint_trap when you need to pass a signal on to an attached
   process when handling SIGINT.  */

static void
pass_signal (int signo)
{
#ifndef _WIN32
  kill (ptid_get_pid (inferior_ptid), SIGINT);
#endif
}

static sighandler_t osig;
static int osig_set;

void
set_sigint_trap (void)
{
  struct inferior *inf = current_inferior ();
  struct terminal_info *tinfo = get_inflow_inferior_data (inf);

  if (inf->attach_flag || tinfo->run_terminal)
    {
      osig = signal (SIGINT, pass_signal);
      osig_set = 1;
    }
  else
    osig_set = 0;
}

void
clear_sigint_trap (void)
{
  if (osig_set)
    {
      signal (SIGINT, osig);
      osig_set = 0;
    }
}


/* Create a new session if the inferior will run in a different tty.
   A session is UNIX's way of grouping processes that share a controlling
   terminal, so a new one is needed if the inferior terminal will be
   different from GDB's.

   Returns the session id of the new session, 0 if no session was created
   or -1 if an error occurred.  */
pid_t
create_tty_session (void)
{
#ifdef HAVE_SETSID
  pid_t ret;

  if (!job_control
      || inferior_thisrun_terminal == NULL
      || is_gdb_terminal (inferior_thisrun_terminal))
    return 0;

  ret = setsid ();
  if (ret == -1)
    warning (_("Failed to create new terminal session: setsid: %s"),
	     safe_strerror (errno));

  return ret;
#else
  return 0;
#endif /* HAVE_SETSID */
}

/* Get all the current tty settings (including whether we have a
   tty at all!).  We can't do this in _initialize_inflow because
   serial_fdopen() won't work until the serial_ops_list is
   initialized, but we don't want to do it lazily either, so
   that we can guarantee stdin_serial is opened if there is
   a terminal.  */
void
initialize_stdin_serial (void)
{
  stdin_serial = serial_fdopen (0);
}

void
_initialize_inflow (void)
{
  add_info ("terminal", info_terminal_command,
	    _("Print inferior's saved terminal status."));

  /* OK, figure out whether we have job control.  */
  have_job_control ();

  observer_attach_inferior_exit (inflow_inferior_exit);

  inflow_inferior_data
    = register_inferior_data_with_cleanup (NULL, inflow_inferior_data_cleanup);

  signal (SIGTSTP, child_terminal_on_sigtstp);
}
