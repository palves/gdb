/* This testcase is part of GDB, the GNU debugger.

   Copyright 2008-2014 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <signal.h>
#include <unistd.h>

int pid;

#ifdef SIGILL
#  define HAVE_SIGILL 1
#else
#  define HAVE_SIGILL 0
#endif

#ifdef SIGEMT
#  define HAVE_SIGEMT 1
#else
#  define HAVE_SIGEMT 0
#endif

#ifdef SIGSEGV
#  define HAVE_SIGSEGV 1
#else
#  define HAVE_SIGSEGV 0
#endif

int have_SIGILL = HAVE_SIGILL;
int have_SIGEMT = HAVE_SIGEMT;
int have_SIGSEGV = HAVE_SIGSEGV;

/* Signal handlers, we set breakpoints in them to make sure that the
   signals really get delivered.  */

#ifdef SIGILL
void
handle_ILL (int sig)
{
}
#endif

#ifdef SIGEMT
void
handle_EMT (int sig)
{
}
#endif

#ifdef SIGSEGV
void
handle_SEGV (int sig)
{
}
#endif

void
done (void)
{
}

void
gen_SIGILL (void)
{
#ifdef SIGILL
  kill (pid, SIGILL);
#endif
  done ();
}

void
gen_SIGEMT (void)
{
#ifdef SIGEMT
  kill (pid, SIGEMT);
#endif
  done ();
}

void
gen_SIGSEGV (void)
{
#ifdef SIGSEGV
  kill (pid, SIGSEGV);
#endif
  done ();
}

int
main ()
{
  pid = getpid ();

#ifdef SIGILL
  signal (SIGILL, handle_ILL);
#endif
#ifdef SIGEMT
  signal (SIGEMT, handle_EMT);
#endif
#ifdef SIGSEGV
  signal (SIGSEGV, handle_SEGV);
#endif

  /* The test single steps many times until the signal is delivered.
     Call 'kill' once, to continue over it once, resolving PLTs, which
     would be slow to single-step over.  */
  kill (pid, 0);

  gen_SIGILL (); /* set breakpoint SIGILL here */

  gen_SIGEMT (); /* set breakpoint SIGEMT here */

  gen_SIGSEGV (); /* set breakpoint SIGSEGV here */

  return 0;
}
