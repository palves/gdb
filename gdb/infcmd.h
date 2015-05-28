/* Copyright (C) 1986-2014 Free Software Foundation, Inc.

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

#ifndef INFCMD_H
#define INFCMD_H 1

struct itset;
struct thread_info;

#include "infrun.h"

extern char *parse_execution_args (char *args, enum execution_arg *exec_option);

typedef void (*aec_callback_func) (struct thread_info *thr, void *data);

extern void
  apply_execution_command (int stepping_command,
			   enum execution_arg exec_option,
			   struct thread_info *parallel_leader,
			   aec_callback_func callback, void *callback_data);

extern void ensure_runnable (struct thread_info *thr);

extern struct itset *default_run_free_itset (struct itset *apply_itset,
					     int step);

#endif /* INFCMD_H */
