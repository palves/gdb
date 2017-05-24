/* Filename-seen cache for the GNU debugger, GDB.

   Copyright (C) 1986-2017 Free Software Foundation, Inc.

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
#include "common/function-view.h"

/* Cache to watch for file names already seen.  */

class filename_seen_cache
{
public:
  filename_seen_cache ();
  ~filename_seen_cache ();

  /* Disable copy.  */
  filename_seen_cache (const filename_seen_cache &) = delete;
  void operator= (const filename_seen_cache &) = delete;

  /* Empty the cache, but do not delete it.  */
  void clear ();

  /* If FILE is not already in the table of files in CACHE, return
     false; otherwise return true.  Optionally add FILE to the table
     if ADD is true.

     NOTE: We don't manage space for FILE, we assume FILE lives as
     long as the caller needs.  */
  bool filename_seen (const char *file, bool add);

  /* Traverse all cache entries, calling CALLBACK on each.  The
     filename is passed as argument to CALLBACK.  */
  void traverse (gdb::function_view<void (const char *)> callback)
  {
    htab_traverse_noresize (m_tab,
			    [] (void **slot, void *info) -> int
			    {
			      auto filename = (const char *) *slot;
			      auto cb = (gdb::function_view<void (const char *)> *) info;
			      (*cb) (filename);
			      return 1;
			    },
			    &callback);
  }

private:
  /* Table of files seen so far.  */
  htab_t m_tab;
};
