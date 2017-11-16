/* This testcase is part of GDB, the GNU debugger.

   Copyright 2016-2017 Free Software Foundation, Inc.

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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>

/* GDB sets watchpoint here.  */
static volatile int globalvar;

/* Whether it's expected that the child exits with a signal, vs
   exiting normally.  GDB sets this.  */
static volatile int expect_signaled;

static void
marker (void)
{
}

static void
child_function (void)
{
  while (1)
    sleep (1);
}

static void
child_signalled ()
{
}

static void
child_exited ()
{
}

int p_to_c[2] = {-1, -1};
int c_to_p[2] = {-1, -1};

static ssize_t
my_read (int fd, unsigned char *buf, size_t size)
{
  int res;

  do
    {
      res = read (fd, buf, size);
    }
  while (res == -1 && errno == EINTR);

  return res;
}

static ssize_t
my_write (int fd, const unsigned char *buf, size_t size)
{
  int res;

  do
    {
      res = write (fd, buf, size);
    }
  while (res == -1 && errno == EINTR);

  return res;
}

int
main (void)
{
  pid_t child;
  int res;

  res = pipe (p_to_c);
  assert (res == 0);
  res = pipe (c_to_p);
  assert (res == 0);

  child = fork ();
  if (child == -1)
    exit (1);
  else if (child != 0)
    {
      int status, ret;
      size_t i = 0;

      close (p_to_c[0]);
      p_to_c[0] = -1;
      close (c_to_p[1]);
      c_to_p[1] = -1;

      while (1)
      for (i = 0; i < 100; i++)
	{
	  unsigned char sent = i;
	  unsigned char rcvd = 0xff;

	  res = my_write (p_to_c[1], &sent, 1);
	  assert (res == 1);
	  res = my_read (c_to_p[0], &rcvd, 1);
	  assert (res == 1);

	  assert (rcvd == sent * 2);
	}

      close (p_to_c[1]);
      p_to_c[1] = 1;
      close (c_to_p[0]);
      c_to_p[0] = -1;

      ret = waitpid (child, &status, 0);
      if (ret == -1)
	exit (2);
      else if (!WIFEXITED (status))
	exit (4);
      else
	marker ();
    }
  else
    {
      close (p_to_c[1]);
      p_to_c[1] = -1;
      close (c_to_p[0]);
      c_to_p[0] = -1;

      while (1)
	{
	  unsigned char rcvd;
	  unsigned char sent;
	  int res;

	  res = my_read (p_to_c[0], &rcvd, 1);
	  if (res == 0)
	    exit (0);
	  else if (res == -1)
	    {
	      perror ("read");
	      exit (1);
	    }

	  sent = rcvd * 2;

	  res = my_write (c_to_p[1], &sent, 1);
	  if (res == -1)
	    {
	      perror ("write");
	      exit (1);
	    }
	  else if (res == 0)
	    exit (1);
	}
      
      child_function ();
    }

  exit (0);
}
