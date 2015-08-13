/* Terminal interface definitions for GDB, the GNU Debugger.
   Copyright (C) 1986-2015 Free Software Foundation, Inc.

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

#if !defined (TERMINAL_H)
#define TERMINAL_H 1

struct terminal;
struct term_state;

/* If we're using autoconf, it will define HAVE_TERMIOS_H,
   HAVE_TERMIO_H and HAVE_SGTTY_H for us.  One day we can rewrite
   ser-unix.c and inflow.c to inspect those names instead of
   HAVE_TERMIOS, HAVE_TERMIO and the implicit HAVE_SGTTY (when neither
   HAVE_TERMIOS or HAVE_TERMIO is set).  Until then, make sure that
   nothing has already defined the one of the names, and do the right
   thing.  */

#if !defined (HAVE_TERMIOS) && !defined(HAVE_TERMIO) && !defined(HAVE_SGTTY)
#if defined(HAVE_TERMIOS_H)
#define HAVE_TERMIOS
#else /* ! defined (HAVE_TERMIOS_H) */
#if defined(HAVE_TERMIO_H)
#define HAVE_TERMIO
#else /* ! defined (HAVE_TERMIO_H) */
#if defined(HAVE_SGTTY_H)
#define HAVE_SGTTY
#endif /* ! defined (HAVE_SGTTY_H) */
#endif /* ! defined (HAVE_TERMIO_H) */
#endif /* ! defined (HAVE_TERMIOS_H) */
#endif /* !defined (HAVE_TERMIOS) && !defined (HAVE_TERMIO) &&
	  !defined (HAVE_SGTTY) */

#if defined(HAVE_TERMIOS)
#include <termios.h>
#endif

#if !defined(_WIN32) && !defined (HAVE_TERMIOS)

/* Define a common set of macros -- BSD based -- and redefine whatever
   the system offers to make it look like that.  FIXME: serial.h and
   ser-*.c deal with this in a much cleaner fashion; as soon as stuff
   is converted to use them, can get rid of this crap.  */

#ifdef HAVE_TERMIO

#include <termio.h>

#undef TIOCGETP
#define TIOCGETP TCGETA
#undef TIOCSETN
#define TIOCSETN TCSETA
#undef TIOCSETP
#define TIOCSETP TCSETAF
#define TERMINAL struct termio

#else /* sgtty */

#include <fcntl.h>
#include <sgtty.h>
#include <sys/ioctl.h>
#define TERMINAL struct sgttyb

#endif /* sgtty */
#endif

#include "vec.h"
#include "interps.h"

struct inferior;

extern void new_tty_prefork (const char *);

extern void new_tty (const char *tty_name);

extern void new_tty_postfork (void);

extern void copy_terminal_info (struct inferior *to, struct inferior *from);

/* Do we have job control?  Can be assumed to always be the same within
   a given run of GDB.  In inflow.c.  */
extern int job_control;

extern pid_t create_tty_session (void);

/* Set the process group of the caller to its own pid, or do nothing if
   we lack job control.  */
extern int gdb_setpgid (void);

/* Set up a serial structure describing the terminal's standard
   input.  */
extern void initialize_stdin_serial (struct terminal *terminal);

extern int gdb_has_a_terminal (void);

extern void gdb_save_tty_state (void);

extern void set_initial_gdb_ttystate (void);

/* Set the process group of the caller to its own pid, or do nothing
   if we lack job control.  */
extern int gdb_setpgid (void);

extern struct terminal *main_terminal;
extern struct terminal *current_terminal;

extern FILE *terminal_outstream (struct terminal *terminal);
extern FILE *terminal_errstream (struct terminal *terminal);

extern void init_terminal (void);

extern void switch_to_terminal (struct terminal *terminal);

struct term_state *new_term_state (void);

struct terminal_readline_state;
struct target_term_state;

typedef struct interp *interp_ptr;
DEF_VEC_P(interp_ptr);

struct terminal
{
  int input_fd;
  FILE *instream;
  FILE *outstream;
  FILE *errstream;

  /* Output channels */
  struct ui_file *out;
  struct ui_file *err;
  struct ui_file *log;

  struct ui_out *current_uiout;

  struct interp *current_interpreter;
  struct interp *top_level_interpreter_ptr;

  VEC(interp_ptr) *interpreters;

  int sync_execution;

  /* Readline-related things.  Private to most of GDB.  */
  struct terminal_readline_state *rl;

  struct term_state *term_state;

  struct target_term_state *target_term_state;
};

typedef struct terminal *terminal_ptr;
DEF_VEC_P(terminal_ptr);

extern VEC(terminal_ptr) *terminals;

#endif /* !defined (TERMINAL_H) */
