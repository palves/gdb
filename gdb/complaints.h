/* Definitions for complaint handling during symbol reading in GDB.

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


#if !defined (COMPLAINTS_H)
#define COMPLAINTS_H

/* Opaque object used to track the number of complaints of a
   particular category.  */
struct complaints;

/* Predefined categories.  */
extern struct complaints *symfile_complaints;

/* Helper for complaint.  */
extern void complaint_internal (struct complaints **complaints,
				const char *file, int line,
				const char *fmt, ...)
  ATTRIBUTE_PRINTF (4, 5);

/* Register a complaint.  This is a macro around complaint_internal to
   avoid computing complaint's arguments when complaints are disabled.
   Running FMT via gettext [i.e., _(FMT)] can be quite expensive, for
   example.  */
#define complaint(COMPLAINTS, FMT, ...)				\
  do								\
    {								\
      extern int stop_whining;					\
								\
      if (stop_whining > 0)					\
	complaint_internal (COMPLAINTS, __FILE__, __LINE__,	\
			    FMT, ##__VA_ARGS__);		\
    }								\
  while (0)

/* Clear out / initialize all complaint counters that have ever been
   incremented.  */

extern void clear_complaints (struct complaints **complaints);

#endif /* !defined (COMPLAINTS_H) */
