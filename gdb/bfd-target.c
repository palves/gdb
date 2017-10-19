/* Very simple "bfd" target, for GDB, the GNU debugger.

   Copyright (C) 2003-2017 Free Software Foundation, Inc.

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
#include "target.h"
#include "bfd-target.h"
#include "exec.h"
#include "gdb_bfd.h"

/* A target that wraps a BFD.  */
class target_bfd : public target_ops
{
private:
  /* The BFD we're wrapping.  */
  struct bfd *m_bfd;

  /* The section table build from the ALLOC sections in BFD.  Note
     that we can't rely on extracting the BFD from a random section in
     the table, since the table can be legitimately empty.  */
  struct target_section_table m_table;

public:
  explicit target_bfd (struct bfd *bfd);
  ~target_bfd () override;

  const char *shortname () override
  { return "bfd"; }

  const char *longname () override
  { return _("BFD backed target"); }

  const char *doc () override
  { return _("You should never see this"); }

  target_xfer_status
    xfer_partial (target_object object,
		  const char *annex, gdb_byte *readbuf,
		  const gdb_byte *writebuf,
		  ULONGEST offset, ULONGEST len,
		  ULONGEST *xfered_len) override;

  target_section_table *get_section_table () override;
};

target_xfer_status
target_bfd::xfer_partial (target_object object,
			  const char *annex, gdb_byte *readbuf,
			  const gdb_byte *writebuf,
			  ULONGEST offset, ULONGEST len,
			  ULONGEST *xfered_len)
{
  switch (object)
    {
    case TARGET_OBJECT_MEMORY:
      {
	return section_table_xfer_memory_partial (readbuf, writebuf,
						  offset, len, xfered_len,
						  m_table.sections,
						  m_table.sections_end,
						  NULL);
      }
    default:
      return TARGET_XFER_E_IO;
    }
}

target_section_table *
target_bfd::get_section_table ()
{
  return &this->m_table;
}

target_bfd::target_bfd (struct bfd *abfd)
{
  m_bfd = abfd;
  gdb_bfd_ref (abfd);
  m_table.sections = NULL;
  m_table.sections_end = NULL;
  build_section_table (abfd, &m_table.sections, &m_table.sections_end);
}

target_bfd::~target_bfd ()
{
  gdb_bfd_unref (m_bfd);
  xfree (m_table.sections);
}

target_ops *
target_bfd_reopen (struct bfd *abfd)
{
  return new target_bfd (abfd);
}

void
target_bfd_close (target_ops *targ)
{
  target_close (targ);
  delete targ;
}
