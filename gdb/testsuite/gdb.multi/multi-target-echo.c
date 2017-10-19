/* This testcase is part of GDB, the GNU debugger.

   Copyright 2017 Free Software Foundation, Inc.

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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 1

static pthread_barrier_t barrier;

static void *
thread_start (void *arg)
{
  pthread_barrier_wait (&barrier);

  while (1)
    sleep (1);
  return NULL;
}

static void
all_started (void)
{
}

static void
function1 (void)
{
}

static void
function2 (void)
{
}

static void
function3 (void)
{
}

static void
function4 (void)
{
}

int
main (int argc, char ** argv)
{
  pthread_t thread;
  int len;

  pthread_barrier_init (&barrier, NULL, NUM_THREADS + 1);
  pthread_create (&thread, NULL, thread_start, NULL);

  pthread_barrier_wait (&barrier);
  all_started ();

  while (1)
    {
      function1 ();
      function2 ();
      function3 ();
      function4 ();
      sleep (1);
    }

  return 0;
}
