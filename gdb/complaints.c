/* Support for complaint handling during symbol reading in GDB.

   Copyright (C) 1990-2017 Free Software Foundation, Inc.

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
#include "complaints.h"
#include "command.h"
#include "gdbcmd.h"

/* Structure to manage complaints about symbol file contents.  */

struct complain
{
  const char *file;
  int line;
  const char *fmt;
  int counter;
  struct complain *next;
};

struct complaints
{
  /* The list of complaints ever filed on this category.  */
  struct complain *root;
};

static struct complain complaint_sentinel;

/* The symbol table complaint table.  */

static struct complaints symfile_complaint_book = {
  &complaint_sentinel,
};
struct complaints *symfile_complaints = &symfile_complaint_book;

static struct complain * ATTRIBUTE_PRINTF (4, 0)
find_complaint (struct complaints *complaints, const char *file,
		int line, const char *fmt)
{
  struct complain *complaint;

  /* Find the complaint in the table.  A more efficient search
     algorithm (based on hash table or something) could be used.  But
     that can wait until someone shows evidence that this lookup is
     a real bottle neck.  */
  for (complaint = complaints->root;
       complaint != NULL;
       complaint = complaint->next)
    {
      if (complaint->fmt == fmt
	  && complaint->file == file
	  && complaint->line == line)
	return complaint;
    }

  /* Oops not seen before, fill in a new complaint.  */
  complaint = XNEW (struct complain);
  complaint->fmt = fmt;
  complaint->file = file;
  complaint->line = line;
  complaint->counter = 0;
  complaint->next = NULL;

  /* File it, return it.  */
  complaint->next = complaints->root;
  complaints->root = complaint;
  return complaint;
}


/* How many complaints about a particular thing should be printed
   before we stop whining about it?  Default is no whining at all,
   since so many systems have ill-constructed symbol files.  */

int stop_whining = 0;

/* Print a complaint, and link the complaint block into a chain for
   later handling.  */

static void ATTRIBUTE_PRINTF (4, 0)
vcomplaint (struct complaints **c, const char *file, 
	    int line, const char *fmt,
	    va_list args)
{
  struct complaints *complaints = *c;
  struct complain *complaint = find_complaint (complaints, file, 
					       line, fmt);

  gdb_assert (complaints != NULL);

  complaint->counter++;
  if (complaint->counter > stop_whining)
    return;

  /* Pass 'fmt' instead of 'complaint->fmt' to printf-like callees
     from here on, to avoid "format string is not a string literal"
     warnings.  'fmt' is this function's printf-format parameter, so
     the compiler can assume the passed in argument is a literal
     string somewhere up the call chain.  */
  gdb_assert (complaint->fmt == fmt);

  vwarning (fmt, args);

  /* If GDB dumps core, we'd like to see the complaints first.
     Presumably GDB will not be sending so many complaints that this
     becomes a performance hog.  */

  gdb_flush (gdb_stderr);
}

void
complaint_internal (struct complaints **complaints,
		    const char *file, int line,
		    const char *fmt, ...)
{
  va_list args;

  va_start (args, fmt);
  vcomplaint (complaints, file, line, fmt, args);
  va_end (args);
}

/* Clear out / initialize all complaint counters that have ever been
   incremented.  If LESS_VERBOSE is 1, be less verbose about
   successive complaints, since the messages are appearing all
   together during a command that is reporting a contiguous block of
   complaints (rather than being interleaved with other messages).  If
   noisy is 1, we are in a noisy command, and our caller will print
   enough context for the user to figure it out.  */

void
clear_complaints (struct complaints **c)
{
  struct complaints *complaints = *c;
  struct complain *p;

  for (p = complaints->root; p != NULL; p = p->next)
    {
      p->counter = 0;
    }
}

static void
complaints_show_value (struct ui_file *file, int from_tty,
		       struct cmd_list_element *cmd, const char *value)
{
  fprintf_filtered (file, _("Max number of complaints about incorrect"
			    " symbols is %s.\n"),
		    value);
}

void
_initialize_complaints (void)
{
  add_setshow_zinteger_cmd ("complaints", class_support, 
			    &stop_whining, _("\
Set max number of complaints about incorrect symbols."), _("\
Show max number of complaints about incorrect symbols."), NULL,
			    NULL, complaints_show_value,
			    &setlist, &showlist);
}
