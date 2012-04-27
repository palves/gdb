/* Generic code for supporting multiple C++ ABI's

   Copyright (C) 2001-2003, 2005-2012 Free Software Foundation, Inc.

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
#include "value.h"
#include "cp-abi.h"
#include "command.h"
#include "exceptions.h"
#include "gdbcmd.h"
#include "ui-out.h"
#include "gdb_assert.h"
#include "gdb_string.h"

static struct cp_abi_ops *find_cp_abi (const char *short_name);

static struct cp_abi_ops *current_cp_abi = NULL;
static struct cp_abi_ops *auto_cp_abi = NULL;

/* cp_abi_mode ==
   cp_abi_auto:   current_cp_abi automatically set upon selection
   of scope (e.g. stack frame)
   cp_abi_manual: current_cp_abi set only by user.  */

enum cp_abi_mode
  {
    cp_abi_mode_auto, cp_abi_mode_manual
  }
cp_abi_mode = cp_abi_mode_auto;

#define CP_ABI_MAX 8
static struct cp_abi_ops *cp_abis[CP_ABI_MAX];
static int num_cp_abis = 0;

enum ctor_kinds
is_constructor_name (const char *name)
{
  if ((current_cp_abi->is_constructor_name) == NULL)
    error (_("ABI doesn't define required function is_constructor_name"));
  return (*current_cp_abi->is_constructor_name) (name);
}

enum dtor_kinds
is_destructor_name (const char *name)
{
  if ((current_cp_abi->is_destructor_name) == NULL)
    error (_("ABI doesn't define required function is_destructor_name"));
  return (*current_cp_abi->is_destructor_name) (name);
}

int
is_vtable_name (const char *name)
{
  if ((current_cp_abi->is_vtable_name) == NULL)
    error (_("ABI doesn't define required function is_vtable_name"));
  return (*current_cp_abi->is_vtable_name) (name);
}

int
is_operator_name (const char *name)
{
  if ((current_cp_abi->is_operator_name) == NULL)
    error (_("ABI doesn't define required function is_operator_name"));
  return (*current_cp_abi->is_operator_name) (name);
}

int
baseclass_offset (struct type *type, int index, const gdb_byte *valaddr,
		  int embedded_offset, CORE_ADDR address,
		  const struct value *val)
{
  volatile struct gdb_exception ex;
  int res = 0;

  gdb_assert (current_cp_abi->baseclass_offset != NULL);

  TRY_CATCH (ex, RETURN_MASK_ERROR)
    {
      res = (*current_cp_abi->baseclass_offset) (type, index, valaddr,
						 embedded_offset,
						 address, val);
    }

  if (ex.reason < 0 && ex.error == NOT_AVAILABLE_ERROR)
    throw_error (NOT_AVAILABLE_ERROR,
		 _("Cannot determine virtual baseclass offset "
		   "of incomplete object"));
  else if (ex.reason < 0)
    throw_exception (ex);
  else
    return res;
}

struct value *
value_virtual_fn_field (struct value **arg1p,
			struct fn_field *f, int j,
			struct type *type, int offset)
{
  if ((current_cp_abi->virtual_fn_field) == NULL)
    return NULL;
  return (*current_cp_abi->virtual_fn_field) (arg1p, f, j,
					      type, offset);
}

struct type *
value_rtti_type (struct value *v, int *full,
		 int *top, int *using_enc)
{
  struct type *ret = NULL;
  volatile struct gdb_exception e;

  if (current_cp_abi->rtti_type == NULL)
    return NULL;
  TRY_CATCH (e, RETURN_MASK_ERROR)
    {
      ret = (*current_cp_abi->rtti_type) (v, full, top, using_enc);
    }
  if (e.reason < 0)
    return NULL;
  return ret;
}

void
cplus_print_method_ptr (const gdb_byte *contents,
			struct type *type,
			struct ui_file *stream)
{
  if (current_cp_abi->print_method_ptr == NULL)
    error (_("GDB does not support pointers to methods on this target"));
  (*current_cp_abi->print_method_ptr) (contents, type, stream);
}

int
cplus_method_ptr_size (struct type *to_type)
{
  if (current_cp_abi->method_ptr_size == NULL)
    error (_("GDB does not support pointers to methods on this target"));
  return (*current_cp_abi->method_ptr_size) (to_type);
}

void
cplus_make_method_ptr (struct type *type, gdb_byte *contents,
		       CORE_ADDR value, int is_virtual)
{
  if (current_cp_abi->make_method_ptr == NULL)
    error (_("GDB does not support pointers to methods on this target"));
  (*current_cp_abi->make_method_ptr) (type, contents, value, is_virtual);
}

CORE_ADDR
cplus_skip_trampoline (struct frame_info *frame,
		       CORE_ADDR stop_pc)
{
  if (current_cp_abi->skip_trampoline == NULL)
    return 0;
  return (*current_cp_abi->skip_trampoline) (frame, stop_pc);
}

struct value *
cplus_method_ptr_to_value (struct value **this_p,
			   struct value *method_ptr)
{
  if (current_cp_abi->method_ptr_to_value == NULL)
    error (_("GDB does not support pointers to methods on this target"));
  return (*current_cp_abi->method_ptr_to_value) (this_p, method_ptr);
}

/* See cp-abi.h.  */

void
cplus_print_vtable (struct value *value)
{
  if (current_cp_abi->print_vtable == NULL)
    error (_("GDB cannot print the vtable on this target"));
  return (*current_cp_abi->print_vtable) (value);
}

int
cp_pass_by_reference (struct type *type)
{
  if ((current_cp_abi->pass_by_reference) == NULL)
    return 0;
  return (*current_cp_abi->pass_by_reference) (type);
}

/* Set the current C++ ABI to SHORT_NAME.  */

static int
switch_to_cp_abi (const char *short_name)
{
  struct cp_abi_ops *abi;

  abi = find_cp_abi (short_name);
  if (abi == NULL)
    return 0;

  current_cp_abi = abi;
  return 1;
}

/* The current value of the "set cp-abi" enum command.  */
static const char *cp_abi;

static void set_cp_abi_cmd (char *ignore, int from_tty,
			    struct cmd_list_element *c);
static void show_cp_abi_cmd (struct ui_file *file, int from_tty,
			     struct cmd_list_element *c, const char *value);

/* Add ABI to the list of supported C++ ABI's.  */

int
register_cp_abi (struct cp_abi_ops *abi)
{
  /* For the "set cp-abi" command.  */
  static const char **cp_abi_names = NULL;
  /* For the "help set cp-abi" command.  */
  char *cp_abi_set_doc = NULL;

  int i;
  struct ui_file *tmp_stream;

  if (num_cp_abis == CP_ABI_MAX)
    internal_error (__FILE__, __LINE__,
		    _("Too many C++ ABIs, please increase "
		      "CP_ABI_MAX in cp-abi.c"));

  cp_abis[num_cp_abis++] = abi;

  /* Build the language names array, to be used as enumeration in the
     set language" enum command.  */
  cp_abi_names = xrealloc (cp_abi_names,
			   (num_cp_abis + 1 + 1) * sizeof (const char *));

  cp_abi_names[0] = "auto";
  for (i = 0; i < num_cp_abis; ++i)
    cp_abi_names[i + 1] = cp_abis[i]->shortname;
  cp_abi_names[i + 1] = NULL;

  /* Build the "help set language" docs.  */
  tmp_stream = mem_fileopen ();

#if 0
  fprintf_unfiltered (tmp_stream, _("\
Set the current C++ ABI.\n\
The available C++ ABIs are:\n\n\
auto    Automatic setting based on source file\n"));

  struct cleanup *cleanup_chain;
  int i;

  ui_out_text (uiout, "The available C++ ABIs are:\n");
  cleanup_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "cp-abi-list");
  for (i = 0; i < num_cp_abis; i++)
    {
      char pad[14];
      int padcount;

      ui_out_text (uiout, "  ");
      ui_out_field_string (uiout, "cp-abi", cp_abis[i]->shortname);

      padcount = 16 - 2 - strlen (cp_abis[i]->shortname);
      pad[padcount] = 0;
      while (padcount > 0)
	pad[--padcount] = ' ';
      ui_out_text (uiout, pad);

      ui_out_field_string (uiout, "doc", cp_abis[i]->doc);
      ui_out_text (uiout, "\n");
    }
  do_cleanups (cleanup_chain);
#endif

  cp_abi_set_doc = ui_file_xstrdup (tmp_stream, NULL);
  ui_file_delete (tmp_stream);

  add_setshow_enum_cmd ("cp-abi", class_obscure,
			(const char **) cp_abi_names,
			&cp_abi,
			cp_abi_set_doc, _("\
Show the current source cp-abi."), NULL,
			set_cp_abi_cmd,
			show_cp_abi_cmd,
			&setlist, &showlist);

  return 1;
}

/* Set the ABI to use in "auto" mode to SHORT_NAME.  */

void
set_cp_abi_as_auto_default (const char *short_name)
{
  char *new_longname, *new_doc;
  struct cp_abi_ops *abi = find_cp_abi (short_name);

  if (abi == NULL)
    internal_error (__FILE__, __LINE__,
		    _("Cannot find C++ ABI \"%s\" to set it as auto default."),
		    short_name);

  auto_cp_abi = abi;

  if (cp_abi_mode == cp_abi_mode_auto)
    current_cp_abi = abi;
}

/* Return the ABI operations associated with SHORT_NAME.  */

static struct cp_abi_ops *
find_cp_abi (const char *short_name)
{
  int i;

  for (i = 0; i < num_cp_abis; i++)
    if (strcmp (cp_abis[i]->shortname, short_name) == 0)
      return cp_abis[i];

  return NULL;
}

/* Display the list of registered C++ ABIs.  */
#if 0
static void
list_cp_abis (int from_tty)
{
  struct ui_out *uiout = current_uiout;
  struct cleanup *cleanup_chain;
  int i;

  ui_out_text (uiout, "The available C++ ABIs are:\n");
  cleanup_chain = make_cleanup_ui_out_tuple_begin_end (uiout,
						       "cp-abi-list");
  for (i = 0; i < num_cp_abis; i++)
    {
      char pad[14];
      int padcount;

      ui_out_text (uiout, "  ");
      ui_out_field_string (uiout, "cp-abi", cp_abis[i]->shortname);

      padcount = 16 - 2 - strlen (cp_abis[i]->shortname);
      pad[padcount] = 0;
      while (padcount > 0)
	pad[--padcount] = ' ';
      ui_out_text (uiout, pad);

      ui_out_field_string (uiout, "doc", cp_abis[i]->doc);
      ui_out_text (uiout, "\n");
    }
  do_cleanups (cleanup_chain);
}
#endif

/* Set the current C++ ABI, or display the list of options if no
   argument is given.  */

static void
set_cp_abi_cmd (char *ignore, int from_tty, struct cmd_list_element *c)
{
  if (strcmp (cp_abi, "auto") == 0)
    {
      cp_abi_mode = cp_abi_mode_auto;
      switch_to_cp_abi (auto_cp_abi->shortname);
    }
  else
    {
      cp_abi_mode = cp_abi_mode_manual;
      switch_to_cp_abi (cp_abi);
    }
}

/* Show the currently selected C++ ABI.  */

static void
show_cp_abi_cmd (struct ui_file *file, int from_tty,
		 struct cmd_list_element *c, const char *value)
{
  struct ui_out *uiout = current_uiout;

  ui_out_text (uiout, "The currently selected C++ ABI is \"");

  if (cp_abi_mode == cp_abi_mode_auto)
    {
      ui_out_field_string (uiout, "cp-abi", "auto");
      ui_out_text (uiout, "\" (currently \"");
      ui_out_field_string (uiout, "longname", current_cp_abi->shortname);
      ui_out_text (uiout, "\").\n");
    }
  else
    {
      ui_out_field_string (uiout, "cp-abi", current_cp_abi->shortname);
      ui_out_text (uiout, "\" (");
      ui_out_field_string (uiout, "longname", current_cp_abi->longname);
      ui_out_text (uiout, ").\n");
    }
}

extern initialize_file_ftype _initialize_cp_abi; /* -Wmissing-prototypes */

void
_initialize_cp_abi (void)
{
#if 0
  register_cp_abi (&auto_cp_abi);
  switch_to_cp_abi ("auto");

  add_cmd ("cp-abi", class_obscure, set_cp_abi_cmd, _("\
Set the ABI used for inspecting C++ objects.\n\
\"set cp-abi\" with no arguments will list the available ABIs."),
	   &setlist);

  add_cmd ("cp-abi", class_obscure, show_cp_abi_cmd,
	   _("Show the ABI used for inspecting C++ objects."),
	   &showlist);
#endif
}
