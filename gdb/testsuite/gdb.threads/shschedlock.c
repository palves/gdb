/* This testcase is part of GDB, the GNU debugger.

   Copyright 2004, 2007, 2008 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifdef __WIN32__
#include <windows.h>
#define dlopen(name, mode) LoadLibrary (TEXT (name))
#ifdef _WIN32_WCE
# define dlsym(handle, func) GetProcAddress (handle, TEXT (func))
#else
# define dlsym(handle, func) GetProcAddress (handle, func)
#endif
#define dlclose(handle) FreeLibrary (handle)
#define dlerror() "error %d occurred", GetLastError ()
#else
#include <dlfcn.h>
#endif

int k = 0;

void *
thread_function1 (void *arg)
{
  sleep (1000);
  pthread_exit(NULL);
  return 0;
}

void *
thread_function0 (void *arg)
{
  void *handle;
  int (*unloadshr) (int);
  int y;
  const char *msg;

  sleep (10);

  handle = dlopen (SHLIB_NAME, RTLD_LAZY);

  if (!handle)
    {
      fprintf (stderr, dlerror ());
      exit (1);
    }

  unloadshr = (int (*)(int)) dlsym (handle, "shrfunc1");

  if (!unloadshr)
    {
      fprintf (stderr, dlerror ());
      exit (1);
    }

  y = (*unloadshr)(3);

  printf ("y is %d\n", y);

#if 0
  while (1)
    {
      sleep (1);
      printf ("woke up\n");
    }
#endif

  dlclose (handle);

#if 1
  while (1)
    {
      sleep (1);
      printf ("woke up\n");
    }
#endif

  pthread_exit(NULL);
  return 0;
}

int
main ()
{
    pthread_t threads[2];
    int res;

    res = pthread_create(&threads[0],
			 NULL,
			 thread_function0,
			 (void *) NULL);

    res = pthread_create(&threads[1],
			 NULL,
			 thread_function1,
			 (void *) NULL);

    pthread_join (threads[0], NULL);
    pthread_join (threads[1], NULL);
    return 0;
}
