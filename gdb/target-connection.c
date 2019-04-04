/* List of target connections for GDB.

   Copyright (C) 2017-2018 Free Software Foundation, Inc.

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
#include "inferior.h"

/* Prints the list of target connections and their details on UIOUT.

   If REQUESTED_CONNECTIONS is not NULL, it's a list of GDB ids of the
   target connections that should be printed.  Otherwise, all target
   connections are printed.  */

static void
print_connection (struct ui_out *uiout, const char *requested_connections)
{
  int count = 0;
  size_t name_len = 0;

  /* Compute number of lines we will print.  */
  for (const auto &it : all_process_targets ())
    {
      if (!number_is_in_list (requested_connections, it.first))
	continue;

      ++count;

      target_ops *t = it.second;

      size_t l = strlen (t->shortname ());
      if (t->connection_string () != NULL)
	l += 1 + strlen (t->connection_string ());

      if (l > name_len)
	name_len = l;
    }

  if (count == 0)
    {
      uiout->message (_("No connections.\n"));
      return;
    }

  ui_out_emit_table table_emitter (uiout, 4, all_process_targets ().size (),
				   "connections");

  uiout->table_header (1, ui_left, "current", "");
  uiout->table_header (4, ui_left, "number", "Num");
  uiout->table_header (name_len + 1, ui_left, "name", "Name");
  uiout->table_header (17, ui_left, "description", "Description");

  uiout->table_body ();

  for (const auto &it : all_process_targets ())
    {
      target_ops *t = it.second;

      if (!number_is_in_list (requested_connections, t->connection_number))
	continue;

      ui_out_emit_tuple tuple_emitter (uiout, NULL);

      if (current_inferior ()->process_target () == t)
	uiout->field_string ("current", "*");
      else
	uiout->field_skip ("current");

      uiout->field_int ("number", t->connection_number);

      if (t->connection_string () != NULL)
	{
	  std::string str = string_printf ("%s %s", t->shortname (),
					   t->connection_string ());
	  uiout->field_string ("name", str.c_str ());
	}
      else
	uiout->field_string ("name", t->shortname ());

      uiout->field_string ("description", t->longname ());

      uiout->text ("\n");
    }
}

static void
info_connections_command (const char *args, int from_tty)
{
  print_connection (current_uiout, args);
}

void
_initialize_target_connection ()
{
  add_info ("connections", info_connections_command,
	    _("\
Names of target connections being debugged.\n\
Shows the list of targets currently in use as well as their description."));
}
