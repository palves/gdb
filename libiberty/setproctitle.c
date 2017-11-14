/* Set the title of a process.
   Copyright (C) 2010-2018 Free Software Foundation, Inc.

This file is part of the libiberty library.
Libiberty is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Libiberty is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with libiberty; see the file COPYING.LIB.  If not,
write to the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
Boston, MA 02110-1301, USA.  */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_SYS_PRCTL_H
#include <sys/types.h>
#include <sys/prctl.h>
#endif
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include "ansidecl.h"

static const char *_progname = NULL;

static const char *
getprogname(void)
{
	return _progname;
}

static void
setprogname(const char *progname)
{
	const char *last_slash;

	last_slash = strrchr(progname, '/');
	if (last_slash == NULL)
		_progname = progname;
	else
		_progname = last_slash + 1;
}

static void
bsd_warnx (const char *fmt, ...)
{
  va_list v;

  va_start (v, fmt);
  vfprintf (stderr, fmt, v);
  va_end (v);
}

#undef warnx
#define warnx bsd_warnx

/* From libbsd's setproctitle.c: */

/*
 * Copyright © 2010 William Ahern
 * Copyright © 2012-2013 Guillem Jover <guillem@hadrons.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <errno.h>
#include <stddef.h>
#include <stdarg.h>
/* #include <stdbool.h> */
#include <stdlib.h>
#include <stdio.h>
/* #include <err.h> */
#include <unistd.h>
#include <string.h>

static struct {
	/* Original value. */
	const char *arg0;

	/* Title space available. */
	char *base, *end;

	 /* Pointer to original nul character within base. */
	char *nul;

	int warned;
	int reset;
	int error;
} SPT;


static inline size_t
spt_min(size_t a, size_t b)
{
	return a < b ? a : b;
}

/*
 * For discussion on the portability of the various methods, see
 * https://lists.freebsd.org/pipermail/freebsd-stable/2008-June/043136.html
 */
static int
spt_clearenv(void)
{
#ifdef HAVE_CLEARENV
	return clearenv();
#else
	char **tmp;

	tmp = (char **)malloc(sizeof(*tmp));
	if (tmp == NULL)
		return errno;

	tmp[0] = NULL;
	environ = tmp;

	return 0;
#endif
}

static int
spt_copyenv(int envc, char *envp[])
{
	char **envcopy;
	char *eq;
	int envsize;
	int i, error;

	if (environ != envp)
		return 0;

	/* Make a copy of the old environ array of pointers, in case
	 * clearenv() or setenv() is implemented to free the internal
	 * environ array, because we will need to access the old environ
	 * contents to make the new copy. */
	envsize = (envc + 1) * sizeof(char *);
	envcopy = (char **)malloc(envsize);
	if (envcopy == NULL)
		return errno;
	memcpy(envcopy, envp, envsize);

	error = spt_clearenv();
	if (error) {
		environ = envp;
		free(envcopy);
		return error;
	}

	for (i = 0; envcopy[i]; i++) {
		eq = strchr(envcopy[i], '=');
		if (eq == NULL)
			continue;

		*eq = '\0';
		if (setenv(envcopy[i], eq + 1, 1) < 0)
			error = errno;
		*eq = '=';

		if (error) {
#ifdef HAVE_CLEARENV
			/* Because the old environ might not be available
			 * anymore we will make do with the shallow copy. */
			environ = envcopy;
#else
			environ = envp;
			free(envcopy);
#endif
			return error;
		}
	}

	/* Dispose of the shallow copy, now that we've finished transfering
	 * the old environment. */
	free(envcopy);

	return 0;
}

static int
spt_copyargs(int argc, char *argv[])
{
	char *tmp;
	int i;

	for (i = 1; i < argc || (i >= argc && argv[i]); i++) {
		if (argv[i] == NULL)
			continue;

		tmp = strdup(argv[i]);
		if (tmp == NULL)
			return errno;

		argv[i] = tmp;
	}

	return 0;
}

void
setproctitle_init(int argc, char *argv[], char *envp[])
{
	char *base, *end, *nul, *tmp;
	int i, envc, error;

	/* Try to make sure we got called with main() arguments. */
	if (argc < 0)
		return;

	base = argv[0];
	if (base == NULL)
		return;

	nul = &base[strlen(base)];
	end = nul + 1;

	for (i = 0; i < argc || (i >= argc && argv[i]); i++) {
		if (argv[i] == NULL || argv[i] != end)
			continue;

		end = argv[i] + strlen(argv[i]) + 1;
	}

	for (i = 0; envp[i]; i++) {
		if (envp[i] != end)
			continue;

		end = envp[i] + strlen(envp[i]) + 1;
	}
	envc = i;

	SPT.arg0 = strdup(argv[0]);
	if (SPT.arg0 == NULL) {
		SPT.error = errno;
		return;
	}

	tmp = strdup(argv[0]);
	if (tmp == NULL) {
		SPT.error = errno;
		return;
	}
	setprogname(tmp);

	error = spt_copyenv(envc, envp);
	if (error) {
		SPT.error = error;
		return;
	}

	error = spt_copyargs(argc, argv);
	if (error) {
		SPT.error = error;
		return;
	}

	SPT.nul  = nul;
	SPT.base = base;
	SPT.end  = end;
}

#ifndef SPT_MAXTITLE
#define SPT_MAXTITLE 255
#endif

/*

@deftypefn Supplemental void setproctitle (const char *@var{fmt}, ...)

Set the title of a process to @var{fmt}.

@end deftypefn

*/

void
setproctitle(const char *fmt, ...)
{
	/* Use buffer in case argv[0] is passed. */
	char buf[SPT_MAXTITLE + 1];
	va_list ap;
	char *nul;
	int len;

	if (SPT.base == NULL) {
		if (!SPT.warned) {
			warnx("setproctitle not initialized, please call "
			      "setproctitle_init().");
			SPT.warned = 1;
		}
		return;
	}

	if (fmt) {
		if (fmt[0] == '-') {
			/* Skip program name prefix. */
			fmt++;
			len = 0;
		} else {
			/* Print program name heading for grep. */
			snprintf(buf, sizeof(buf), "%s: ", getprogname());
			len = strlen(buf);
		}

		va_start(ap, fmt);
		len += vsnprintf(buf + len, sizeof(buf) - len, fmt, ap);
		va_end(ap);
	} else {
		len = snprintf(buf, sizeof(buf), "%s", SPT.arg0);
	}

	if (len <= 0) {
		SPT.error = errno;
		return;
	}

	if (!SPT.reset) {
		memset(SPT.base, 0, SPT.end - SPT.base);
		SPT.reset = 1;
	} else {
		memset(SPT.base, 0, spt_min(sizeof(buf), SPT.end - SPT.base));
	}

	len = spt_min(len, spt_min(sizeof(buf), SPT.end - SPT.base) - 1);
	memcpy(SPT.base, buf, len);
	nul = &SPT.base[len];

	if (nul < SPT.nul) {
		*SPT.nul = '.';
	} else if (nul == SPT.nul && &nul[1] < SPT.end) {
		*SPT.nul = ' ';
		*++nul = '\0';
	}
}
