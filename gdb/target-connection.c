/* Select target systems and architectures at runtime for GDB.

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

#include "defs.h"
#include "target-connection.h"
#include "target.h"
#include "gdbcmd.h"
#include "cli/cli-utils.h"

static std::vector<target_connection *> target_connections;

target_connection *current_target_connection;

static int highest_target_connection_num;

static const char targ_desc[] =
  R"(Names of targets and files being debugged.
Shows the entire stack of targets currently in use (including the exec-file,
core-file, and process, if any), as well as the symbol file name.)";

target_ops *make_dummy_target ();

target_connection::target_connection ()
{
  this->num = highest_target_connection_num++;
  this->top_target = make_dummy_target ();
}

/* Prints the list of inferiors and their details on UIOUT.  This is a
   version of 'info_inferior_command' suitable for use from MI.

   If REQUESTED_INFERIORS is not NULL, it's a list of GDB ids of the
   inferiors that should be printed.  Otherwise, all inferiors are
   printed.  */

static void
print_connection (struct ui_out *uiout, char *requested_inferiors)
{
  struct target_connection *inf;
  struct cleanup *old_chain;
  int inf_count = 0;

  /* Compute number of inferiors we will print.  */
  for (target_connection *con : target_connections)
    {
      if (!number_is_in_list (requested_inferiors, con->num))
	continue;

      ++inf_count;
    }

  if (inf_count == 0)
    {
      uiout->message ("No connections.\n");
      return;
    }

  old_chain = make_cleanup_ui_out_table_begin_end (uiout, 3, inf_count,
						   "connections");
  uiout->table_header (1, ui_left, "current", "");
  uiout->table_header (4, ui_left, "number", "Num");
  uiout->table_header (17, ui_left, "description", "Description");

  uiout->table_body ();
  for (target_connection *inf : target_connections)
    {
      struct cleanup *chain2;

      if (!number_is_in_list (requested_inferiors, inf->num))
	continue;

      chain2 = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);

      if (inf == current_target_connection)
	uiout->field_string ("current", "*");
      else
	uiout->field_skip ("current");

      uiout->field_int ("number", inf->num);

      uiout->field_string ("description", inf->top_target->longname ());

      uiout->text ("\n");
      do_cleanups (chain2);
    }

  do_cleanups (old_chain);
}

static void
info_connections_command (char *args, int from_tty)
{
  print_connection (current_uiout, args);
}

static void
add_connection_command (char *args, int from_tty)
{
  target_connection *tc = new target_connection ();
  target_connections.push_back (tc);
}

static void
connection_command (char *args, int from_tty)
{
}

void
initialize_target_connections ()
{
  current_target_connection = new target_connection ();
  target_connections.push_back (current_target_connection);

  add_info ("connections", info_connections_command, targ_desc);

  add_com ("add-connection", no_class, add_connection_command,
	   _(R"(Add a new target connection.
Usage: add-connection
N is the optional number of connections to add, default is 1.)"));

  add_cmd ("connection", class_run, connection_command, _("\
Use this command to switch between inferiors.\n\
The new inferior ID must be currently known."),
	   &cmdlist);
}
