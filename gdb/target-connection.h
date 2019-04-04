/* Interface between GDB and target environments, including files and processes

   Copyright (C) 2017 Free Software Foundation, Inc.

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

#if !defined (TARGET_CONNECTION_H)
#define TARGET_CONNECTION_H

#include <map>

struct process_stratum_target;

/* A map between connection number and representative process_stratum
   target.  */
typedef std::map<int, process_stratum_target *> process_targets_map;

/* Return the map between connection number and representative
   process_stratum target.  */
extern const process_targets_map &all_process_targets ();

#endif /* !defined (TARGET_CONNECTION_H) */
