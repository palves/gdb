/* TUI data manipulation routines.

   Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2006, 2007, 2008,
   2009, 2010 Free Software Foundation, Inc.

   Contributed by Hewlett-Packard Company.

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
#include "symtab.h"
#include "tui/tui.h"
#include "tui/tui-data.h"
#include "tui/tui-wingeneral.h"

#include "gdb_string.h"
#include "gdb_curses.h"
#include "gdb_assert.h"

/****************************
** GLOBAL DECLARATIONS
****************************/
struct tui_win_info *(tui_win_list[MAX_MAJOR_WINDOWS]);

/***************************
** Private data
****************************/
static enum tui_layout_type current_layout = UNDEFINED_LAYOUT;
static int term_height, term_width;
static struct tui_gen_win_info _locator;
static struct tui_gen_win_info exec_info[2];
static struct tui_winsource_win *src_win_list[2];
static struct tui_list source_windows = {(void **) src_win_list, 0};
static int default_tab_len = DEFAULT_TAB_LEN;
static struct tui_win_info *win_with_focus = (struct tui_win_info *) NULL;
static struct tui_layout_def layout_def = {
  SRC_WIN,			/* DISPLAY_MODE */
  FALSE,			/* SPLIT */
  TUI_UNDEFINED_REGS,		/* REGS_DISPLAY_TYPE */
  TUI_SFLOAT_REGS};		/* FLOAT_REGS_DISPLAY_TYPE */

static int win_resized = FALSE;


/*********************************
** Static function forward decls
**********************************/
static void free_content (tui_win_content, 
			  int, 
			  enum tui_win_type);
static void free_content_elements (tui_win_content, 
				   int, 
				   enum tui_win_type);



/*********************************
** PUBLIC FUNCTIONS
**********************************/

int
tui_win_is_source_type (enum tui_win_type win_type)
{
  return (win_type == SRC_WIN || win_type == DISASSEM_WIN);
}

int
tui_win_is_auxillary (enum tui_win_type win_type)
{
  return (win_type > MAX_MAJOR_WINDOWS);
}

int
tui_source_win_has_locator (struct tui_winsource_win *win_info)
{
  return (win_info != NULL 
	  && win_info->has_locator);
}

void
tui_set_win_highlight (struct tui_win_info *win_info, 
		       int highlight)
{
  if (win_info != NULL)
    win_info->is_highlighted = highlight;
}

/******************************************
** ACCESSORS & MUTATORS FOR PRIVATE DATA
******************************************/

/* Answer a whether the terminal window has been resized or not.  */
int
tui_win_resized (void)
{
  return win_resized;
}


/* Set a whether the terminal window has been resized or not.  */
void
tui_set_win_resized_to (int resized)
{
  win_resized = resized;
}


/* Answer a pointer to the current layout definition.  */
struct tui_layout_def *
tui_layout_def (void)
{
  return &layout_def;
}


/* Answer the window with the logical focus.  */
struct tui_win_info *
tui_win_with_focus (void)
{
  return win_with_focus;
}


/* Set the window that has the logical focus.  */
void
tui_set_win_with_focus (struct tui_win_info *win_info)
{
  win_with_focus = win_info;
}


/* Answer the length in chars, of tabs.  */
int
tui_default_tab_len (void)
{
  return default_tab_len;
}


/* Set the length in chars, of tabs.  */
void
tui_set_default_tab_len (int len)
{
  default_tab_len = len;
}


/* Accessor for the current source window.  Usually there is only one
   source window (either source or disassembly), but both can be
   displayed at the same time.  */
struct tui_list *
tui_source_windows (void)
{
  return &source_windows;
}


/* Clear the list of source windows.  Usually there is only one source
   window (either source or disassembly), but both can be displayed at
   the same time.  */
void
tui_clear_source_windows (void)
{
  source_windows.list[0] = NULL;
  source_windows.list[1] = NULL;
  source_windows.count = 0;
}


/* Clear the pertinant detail in the source windows.  */
void
tui_clear_source_windows_detail (void)
{
  int i;

  for (i = 0; i < (tui_source_windows ())->count; i++)
    tui_clear_win_detail ((tui_source_windows ())->list[i]);
}


/* Add a window to the list of source windows.  Usually there is only
   one source window (either source or disassembly), but both can be
   displayed at the same time.  */
void
tui_add_to_source_windows (struct tui_winsource_win *win_info)
{
  if (source_windows.count < 2)
    source_windows.list[source_windows.count++] = (void *) win_info;
}


/* Clear the pertinant detail in the windows.  */
void
tui_clear_win_detail (struct tui_win_info *win_info)
{
  if (win_info != NULL)
    win_info->vtable->clear_detail (win_info);
}


/* Accessor for the source execution info ptr.  */
struct tui_gen_win_info *
tui_source_exec_info_win_ptr (void)
{
  return &exec_info[0];
}


/* Accessor for the disassem execution info ptr.  */
struct tui_gen_win_info *
tui_disassem_exec_info_win_ptr (void)
{
  return &exec_info[1];
}


/* Accessor for the locator win info.  Answers a pointer to the static
   locator win info struct.  */
struct tui_gen_win_info *
tui_locator_win_info_ptr (void)
{
  return &_locator;
}


/* Accessor for the term_height.  */
int
tui_term_height (void)
{
  return term_height;
}


/* Mutator for the term height.  */
void
tui_set_term_height_to (int h)
{
  term_height = h;
}


/* Accessor for the term_width.  */
int
tui_term_width (void)
{
  return term_width;
}


/* Mutator for the term_width.  */
void
tui_set_term_width_to (int w)
{
  term_width = w;
}


/* Accessor for the current layout.  */
enum tui_layout_type
tui_current_layout (void)
{
  return current_layout;
}


/* Mutator for the current layout.  */
void
tui_set_current_layout_to (enum tui_layout_type new_layout)
{
  current_layout = new_layout;
}


/* Set the origin of the window.  */
void
set_gen_win_origin (struct tui_gen_win_info *win_info, 
		    int x, int y)
{
  win_info->origin.x = x;
  win_info->origin.y = y;
}


/*****************************
** OTHER PUBLIC FUNCTIONS
*****************************/


/* Answer the next window in the list, cycling back to the top if
   necessary.  */
struct tui_win_info *
tui_next_win (struct tui_win_info *cur_win)
{
  enum tui_win_type type = cur_win->generic.type;
  struct tui_win_info *next_win = (struct tui_win_info *) NULL;

  if (cur_win->generic.type == CMD_WIN)
    type = SRC_WIN;
  else
    type = cur_win->generic.type + 1;
  while (type != cur_win->generic.type && (next_win == NULL))
    {
      if (tui_win_list[type]
	  && tui_win_list[type]->generic.is_visible)
	next_win = tui_win_list[type];
      else
	{
	  if (type == CMD_WIN)
	    type = SRC_WIN;
	  else
	    type++;
	}
    }

  return next_win;
}


/* Answer the prev window in the list, cycling back to the bottom if
   necessary.  */
struct tui_win_info *
tui_prev_win (struct tui_win_info *cur_win)
{
  enum tui_win_type type = cur_win->generic.type;
  struct tui_win_info *prev = (struct tui_win_info *) NULL;

  if (cur_win->generic.type == SRC_WIN)
    type = CMD_WIN;
  else
    type = cur_win->generic.type - 1;
  while (type != cur_win->generic.type && (prev == NULL))
    {
      if (tui_win_list[type]
	  && tui_win_list[type]->generic.is_visible)
	prev = tui_win_list[type];
      else
	{
	  if (type == SRC_WIN)
	    type = CMD_WIN;
	  else
	    type--;
	}
    }

  return prev;
}


/* Answer the window represented by name.  */
struct tui_win_info *
tui_partial_win_by_name (char *name)
{
  struct tui_win_info *win_info = (struct tui_win_info *) NULL;

  if (name != (char *) NULL)
    {
      int i = 0;

      while (i < MAX_MAJOR_WINDOWS && win_info == NULL)
	{
          if (tui_win_list[i] != 0)
            {
              const char *cur_name = tui_win_name (tui_win_list[i]);
              if (strlen (name) <= strlen (cur_name)
		  && strncmp (name, cur_name, strlen (name)) == 0)
                win_info = tui_win_list[i];
            }
	  i++;
	}
    }

  return win_info;
}


/* Answer the name of the window.  */
const char *
tui_win_name (struct tui_win_info *win_info)
{
  if (win_info->name == NULL)
    return "";

  return win_info->name;
}


void
tui_initialize_static_data (void)
{
  tui_init_generic_part (tui_source_exec_info_win_ptr ());
  tui_init_generic_part (tui_disassem_exec_info_win_ptr ());
  tui_init_generic_part (tui_locator_win_info_ptr ());
}


struct tui_gen_win_info *
tui_alloc_generic_win_info (void)
{
  struct tui_gen_win_info *win;

  if ((win = XMALLOC (struct tui_gen_win_info)) != NULL)
    tui_init_generic_part (win);

  return win;
}


void
tui_init_generic_part (struct tui_gen_win_info *win)
{
  win->width =
    win->height =
    win->origin.x =
    win->origin.y =
    win->viewport_height =
    win->content_size =
    win->last_visible_line = 0;
  win->handle = (WINDOW *) NULL;
  win->content = NULL;
  win->content_in_use =
    win->is_visible = FALSE;
  win->title = 0;
}


/* init_content_element().
 */
static void
init_content_element (struct tui_win_element *element, 
		      enum tui_win_type type)
{
  element->highlight = FALSE;
  switch (type)
    {
    case SRC_WIN:
    case DISASSEM_WIN:
      element->which_element.source.line = (char *) NULL;
      element->which_element.source.line_or_addr.loa = LOA_LINE;
      element->which_element.source.line_or_addr.u.line_no = 0;
      element->which_element.source.is_exec_point = FALSE;
      element->which_element.source.has_break = FALSE;
      break;
    case DATA_WIN:
      tui_init_generic_part (&element->which_element.data_window);
      element->which_element.data_window.type = DATA_ITEM_WIN;
      ((struct tui_gen_win_info *) & element->which_element.data_window)->content =
	(void **) tui_alloc_content (1, DATA_ITEM_WIN);
      ((struct tui_gen_win_info *)
       & element->which_element.data_window)->content_size = 1;
      break;
    case CMD_WIN:
      element->which_element.command.line = (char *) NULL;
      break;
    case DATA_ITEM_WIN:
      element->which_element.data.name = (char *) NULL;
      element->which_element.data.type = TUI_REGISTER;
      element->which_element.data.item_no = UNDEFINED_ITEM;
      element->which_element.data.value = NULL;
      element->which_element.data.highlight = FALSE;
      element->which_element.data.content = (char*) NULL;
      break;
    case LOCATOR_WIN:
      element->which_element.locator.file_name[0] =
	element->which_element.locator.proc_name[0] = (char) 0;
      element->which_element.locator.line_no = 0;
      element->which_element.locator.addr = 0;
      break;
    case EXEC_INFO_WIN:
      memset(element->which_element.simple_string, ' ',
             sizeof(element->which_element.simple_string));
      break;
    default:
      break;
    }
}

static void
tui_win_info_clear_detail (struct tui_win_info *win_info)
{
}

static void
tui_win_info_vertical_scroll (struct tui_win_info *win_info,
			      enum tui_scroll_direction direction, int i)
{
}

static void
tui_win_info_horizontal_scroll (struct tui_win_info *win_info,
				enum tui_scroll_direction direction, int i)
{
}

static void
tui_win_info_refresh (struct tui_win_info *win_info)
{
  touchwin (win_info->generic.handle);
  tui_refresh_win (&win_info->generic);
}

static void
tui_win_info_refresh_win (struct tui_win_info *win_info)
{
}

static void
tui_win_info_del_window (struct tui_win_info *win_info)
{
  if (win_info->generic.handle != (WINDOW *) NULL)
    {
      tui_delete_win (win_info->generic.handle);
      win_info->generic.handle = (WINDOW *) NULL;
      win_info->generic.is_visible = FALSE;
    }
}

static void
tui_win_info_free_window (struct tui_win_info *win_info)
{
  if (win_info->generic.handle != (WINDOW *) NULL)
    {
      tui_delete_win (win_info->generic.handle);
      win_info->generic.handle = (WINDOW *) NULL;
      tui_free_win_content (&win_info->generic);
    }
  xfree (win_info->generic.title);
  xfree (win_info);
}

static void
tui_win_info_make_invisible_and_set_new_height (struct tui_win_info *win_info,
						int height)
{
  struct tui_gen_win_info *gen_win_info;

  tui_make_invisible (&win_info->generic);
  win_info->generic.height = height;
  if (height > 1)
    win_info->generic.viewport_height = height - 1;
  else
    win_info->generic.viewport_height = height;
  win_info->generic.viewport_height--;
}

static void
tui_win_info_make_visible_with_new_heigth (struct tui_win_info *win_info)
{
  tui_make_visible (&win_info->generic);
  tui_check_and_display_highlight_if_needed (win_info);
}

static struct tui_win_info_ops tui_win_info_vtable =
  {
    tui_win_info_clear_detail,
    tui_win_info_refresh,
    tui_win_info_refresh_win,
    tui_win_info_make_invisible_and_set_new_height,
    tui_win_info_make_visible_with_new_heigth,
    tui_win_info_vertical_scroll,
    tui_win_info_horizontal_scroll,
    tui_win_info_del_window,
    tui_win_info_free_window,
  };

static void
init_win_info (struct tui_win_info *win_info, const char *name)
{
  tui_init_generic_part (&win_info->generic);

  win_info->can_highlight =
    win_info->is_highlighted = FALSE;
  win_info->name = name;

  win_info->vtable = &tui_win_info_vtable;
}

#include "tui/tui-source.h"
#include "tui/tui-disasm.h"
#include "tui/tui-windata.h"
#include "tui/tui-winsource.h"

static void
tui_source_win_clear_detail (struct tui_win_info *self_)
{
  struct tui_winsource_win *self
    = (struct tui_winsource_win *) self_;

  self->gdbarch = NULL;
  self->start_line_or_addr.loa = LOA_ADDRESS;
  self->start_line_or_addr.u.addr = 0;
  self->horizontal_offset = 0;
}

static void
tui_vertical_source_or_disasm_scroll (struct tui_win_info *win_info,
				      enum tui_scroll_direction direction,
				      int num_to_scroll)
{
  if (win_info == (void *) TUI_SRC_WIN)
    tui_vertical_source_scroll (win_info, direction, num_to_scroll);
  else if (win_info == (void *) TUI_DISASM_WIN)
    tui_vertical_disassem_scroll (win_info, direction, num_to_scroll);
}

static void
tui_source_win_refresh (struct tui_win_info *win_info)
{
  struct tui_winsource_win *src_win
    = (struct tui_winsource_win *) win_info;
  touchwin (src_win->execution_info->handle);
  tui_refresh_win (src_win->execution_info);

  tui_win_info_refresh (win_info);
}

static void
tui_source_win_refresh_win (struct tui_win_info *win_info)
{
  struct tui_winsource_win *src_win = (struct tui_winsource_win *) win_info;

  tui_show_source_content (src_win);
  tui_check_and_display_highlight_if_needed (win_info);
  tui_erase_exec_info_content (src_win);
  tui_update_exec_info (src_win);
}

#include "symtab.h"
#include "breakpoint.h"
#include "frame.h"
#include "cli/cli-cmds.h"
#include "top.h"
#include "source.h"
#include "tui-stack.h"

static void
tui_source_win_make_invisible_and_set_new_heigth (struct tui_win_info *win_info,
						  int height)
{
  struct tui_gen_win_info *gen_win_info;
  struct tui_winsource_win *src_win_info;

  tui_win_info_make_invisible_and_set_new_height (win_info, height);

  src_win_info = (struct tui_winsource_win *) win_info;

  /* Now deal with the auxillary windows associated with win_info.  */

  gen_win_info = src_win_info->execution_info;
  tui_make_invisible (gen_win_info);
  gen_win_info->height = height;
  gen_win_info->origin.y = win_info->generic.origin.y;
  if (height > 1)
    gen_win_info->viewport_height = height - 1;
  else
    gen_win_info->viewport_height = height;
  gen_win_info->viewport_height--;

  if (tui_source_win_has_locator (src_win_info))
    {
      gen_win_info = tui_locator_win_info_ptr ();
      tui_make_invisible (gen_win_info);
      gen_win_info->origin.y = win_info->generic.origin.y + height;
    }
}

static void
tui_source_win_make_visible_with_new_heigth (struct tui_win_info *win_info)
{
  struct tui_winsource_win *src_win_info;
  struct symtab *s;

  tui_make_visible (&win_info->generic);
  tui_check_and_display_highlight_if_needed (win_info);

  src_win_info = (struct tui_winsource_win *) win_info;
  tui_free_win_content (src_win_info->execution_info);
  tui_make_visible (src_win_info->execution_info);
  if (win_info->generic.content != NULL)
    {
      struct gdbarch *gdbarch = src_win_info->gdbarch;
      struct tui_line_or_address line_or_addr;
      struct symtab_and_line cursal
	= get_current_source_symtab_and_line ();

      line_or_addr = src_win_info->start_line_or_addr;
      tui_free_win_content (&win_info->generic);
      tui_update_source_window (src_win_info, gdbarch,
				cursal.symtab, line_or_addr, TRUE);
    }
  else if (deprecated_safe_get_selected_frame () != NULL)
    {
      struct tui_line_or_address line;
      struct symtab_and_line cursal = get_current_source_symtab_and_line ();
      struct frame_info *frame = deprecated_safe_get_selected_frame ();
      struct gdbarch *gdbarch = get_frame_arch (frame);

      s = find_pc_symtab (get_frame_pc (frame));
      if (win_info->generic.type == SRC_WIN)
	{
	  line.loa = LOA_LINE;
	  line.u.line_no = cursal.line;
	}
      else
	{
	  line.loa = LOA_ADDRESS;
	  find_line_pc (s, cursal.line, &line.u.addr);
	}
      tui_update_source_window (src_win_info, gdbarch, s, line, TRUE);
    }
  if (tui_source_win_has_locator (src_win_info))
    {
      tui_make_visible (tui_locator_win_info_ptr ());
      tui_show_locator_content ();
    }
}

static void src_disasm_win_del_window (struct tui_win_info *win_info);
static void src_disasm_win_free_window (struct tui_win_info *win_info);

static struct tui_win_info_ops src_win_vtable =
  {
    tui_source_win_clear_detail,
    tui_source_win_refresh,
    tui_source_win_refresh_win,
    tui_source_win_make_invisible_and_set_new_heigth,
    tui_source_win_make_visible_with_new_heigth,
    tui_vertical_source_or_disasm_scroll,
    tui_horizontal_source_scroll,
    src_disasm_win_del_window,
    src_disasm_win_free_window,
  };

static void
init_source_disasm_win_info_1 (struct tui_winsource_win *win_info,
			       const char *name)
{
  init_win_info (&win_info->win_info, name);

  win_info->execution_info = (struct tui_gen_win_info *) NULL;
  win_info->has_locator = FALSE;
  win_info->horizontal_offset = 0;
  win_info->gdbarch = NULL;
  win_info->start_line_or_addr.loa = LOA_ADDRESS;
  win_info->start_line_or_addr.u.addr = 0;
  win_info->filename = 0;

  win_info->win_info.vtable = &src_win_vtable;
}

static void
init_source_win_info (struct tui_winsource_win *win_info)
{
  init_source_disasm_win_info_1 (win_info, SRC_NAME);
}

static void
tui_data_display_win_clear_detail (struct tui_win_info *self_)
{
  struct tui_data_display_win_info *self
    = (struct tui_data_display_win_info *) self_;

  self->data_content = (tui_win_content) NULL;
  self->data_content_count = 0;
  self->regs_content = (tui_win_content) NULL;
  self->regs_content_count = 0;
  self->regs_display_type = TUI_UNDEFINED_REGS;
  self->regs_column_count = 1;
  self->display_regs = FALSE;
}

static void
tui_data_win_refresh_win (struct tui_win_info *win_info)
{
  tui_refresh_data_win ();
}

static void
tui_data_win_make_invisible_and_set_new_height (struct tui_win_info *win_info,
						int height)
{
  struct tui_gen_win_info *gen_win_info;
  int i;

  tui_win_info_make_invisible_and_set_new_height (win_info, height);

  /* Now deal with the auxillary windows associated with win_info.  */

  /* Delete all data item windows.  */
  for (i = 0; i < win_info->generic.content_size; i++)
    {
      gen_win_info = (struct tui_gen_win_info *) & ((struct tui_win_element *)
						    win_info->generic.content[i])->which_element.data_window;
      tui_delete_win (gen_win_info->handle);
      gen_win_info->handle = (WINDOW *) NULL;
    }
}

static void
tui_data_win_make_visible_with_new_height (struct tui_win_info *win_info)
{
  tui_make_visible (&win_info->generic);
  tui_check_and_display_highlight_if_needed (win_info);

  tui_display_all_data ();
}

static void data_win_del_window (struct tui_win_info *win_info);
static void data_win_free_window (struct tui_win_info *win_info);

static struct tui_win_info_ops data_win_vtable =
  {
    tui_data_display_win_clear_detail,
    tui_win_info_refresh,
    tui_data_win_refresh_win,
    tui_data_win_make_invisible_and_set_new_height,
    tui_data_win_make_visible_with_new_height,
    tui_vertical_data_scroll,
    tui_win_info_horizontal_scroll,
    data_win_del_window,
    data_win_free_window,
  };

static void
init_disasm_win_info (struct tui_winsource_win *win_info)
{
  init_source_disasm_win_info_1 (win_info, DISASSEM_NAME);
}

static void
init_data_display_win_info (struct tui_data_display_win_info *win_info)
{
  init_win_info (&win_info->win_info, DATA_NAME);

  win_info->data_content = (tui_win_content) NULL;
  win_info->data_content_count = 0;
  win_info->regs_content = (tui_win_content) NULL;
  win_info->regs_content_count = 0;
  win_info->regs_display_type = TUI_UNDEFINED_REGS;
  win_info->regs_column_count = 1;
  win_info->display_regs = FALSE;
  win_info->current_group = 0;

  win_info->win_info.vtable = &data_win_vtable;
}

static void
tui_command_win_clear_detail (struct tui_win_info *self_)
{
  struct tui_command_win_info *self = (struct tui_command_win_info *) self_;

  self->cur_line = self->curch = 0;
}

static void
tui_cmd_win_make_invisible_and_set_new_height (struct tui_win_info *win_info,
					       int height)
{
  struct tui_gen_win_info *gen_win_info;

  tui_make_invisible (&win_info->generic);
  win_info->generic.height = height;
  if (height > 1)
    win_info->generic.viewport_height = height - 1;
  else
    win_info->generic.viewport_height = height;
}

static void
tui_cmd_win_make_visible_with_new_height (struct tui_win_info *win_info)
{
  struct tui_command_win_info *cmd_win_info
    = (struct tui_command_win_info *) win_info;

  tui_make_visible (&win_info->generic);
  tui_check_and_display_highlight_if_needed (win_info);

  cmd_win_info->cur_line = 0;
  cmd_win_info->curch = 0;
  wmove (win_info->generic.handle,
	 cmd_win_info->cur_line,
	 cmd_win_info->curch);
}

static struct tui_win_info_ops command_win_vtable =
  {
    tui_command_win_clear_detail,
    tui_win_info_refresh,
    tui_win_info_refresh_win,
    tui_cmd_win_make_invisible_and_set_new_height,
    tui_cmd_win_make_visible_with_new_height,
    tui_win_info_vertical_scroll,
    tui_win_info_horizontal_scroll,
    tui_win_info_del_window,
    tui_win_info_free_window,
  };

static void
init_command_win_info (struct tui_command_win_info *win_info)
{
  init_win_info (&win_info->win_info, CMD_NAME);

  win_info->cur_line = 0;
  win_info->curch = 0;

  win_info->win_info.vtable = &command_win_vtable;
}

struct tui_win_info *
tui_alloc_win_info (enum tui_win_type type)
{
  switch (type)
    {
    case SRC_WIN:
      {
	struct tui_winsource_win *win_info
	  = XMALLOC (struct tui_winsource_win);
	init_source_win_info (win_info);
	return &win_info->win_info;
      }
    case DISASSEM_WIN:
      {
      	struct tui_winsource_win *win_info
	  = XMALLOC (struct tui_winsource_win);
	init_disasm_win_info (win_info);
	return &win_info->win_info;
      }
    case DATA_WIN:
      {
      	struct tui_data_display_win_info *win_info
	  = XMALLOC (struct tui_data_display_win_info);
	init_data_display_win_info (win_info);
	return &win_info->win_info;
      }
    case CMD_WIN:
      {
      	struct tui_command_win_info *win_info
	  = XMALLOC (struct tui_command_win_info);
	init_command_win_info (win_info);
	return &win_info->win_info;
      }
      break;
    default:
      gdb_assert (0);
      break;
    }
}


/* Allocates the content and elements in a block.  */
tui_win_content
tui_alloc_content (int num_elements, enum tui_win_type type)
{
  tui_win_content content;
  char *element_block_ptr;
  int i;

  content = xmalloc (sizeof (struct tui_win_element *) *num_elements);
  if (content != NULL)
    {
      /*
       * All windows, except the data window, can allocate the
       * elements in a chunk.  The data window cannot because items
       * can be added/removed from the data display by the user at any
       * time.
       */
      if (type != DATA_WIN)
	{
	  element_block_ptr =
	    xmalloc (sizeof (struct tui_win_element) * num_elements);
	  if (element_block_ptr != NULL)
	    {
	      for (i = 0; i < num_elements; i++)
		{
		  content[i] = (struct tui_win_element *) element_block_ptr;
		  init_content_element (content[i], type);
		  element_block_ptr += sizeof (struct tui_win_element);
		}
	    }
	  else
	    {
	      xfree (content);
	      content = (tui_win_content) NULL;
	    }
	}
    }

  return content;
}


/* Adds the input number of elements to the windows's content.  If no
   content has been allocated yet, alloc_content() is called to do
   this.  The index of the first element added is returned, unless
   there is a memory allocation error, in which case, (-1) is
   returned.  */
int
tui_add_content_elements (struct tui_gen_win_info *win_info, 
			  int num_elements)
{
  struct tui_win_element *element_ptr;
  int i, index_start;

  if (win_info->content == NULL)
    {
      win_info->content = (void **) tui_alloc_content (num_elements, win_info->type);
      index_start = 0;
    }
  else
    index_start = win_info->content_size;
  if (win_info->content != NULL)
    {
      for (i = index_start; (i < num_elements + index_start); i++)
	{
	  if ((element_ptr = XMALLOC (struct tui_win_element)) != NULL)
	    {
	      win_info->content[i] = (void *) element_ptr;
	      init_content_element (element_ptr, win_info->type);
	      win_info->content_size++;
	    }
	  else	/* Things must be really hosed now!  We ran out of
		   memory!?  */
	    return (-1);
	}
    }

  return index_start;
}

static void
src_disasm_win_del_window (struct tui_win_info *win_info)
{
  struct tui_winsource_win *src_win = (struct tui_winsource_win *)win_info;
  struct tui_gen_win_info *generic_win;

  generic_win = tui_locator_win_info_ptr ();
  if (generic_win != NULL)
    {
      tui_delete_win (generic_win->handle);
      generic_win->handle = (WINDOW *) NULL;
      generic_win->is_visible = FALSE;
    }

  xfree (src_win->filename);
  src_win->filename = NULL;

  generic_win = src_win->execution_info;
  if (generic_win != NULL)
    {
      tui_delete_win (generic_win->handle);
      generic_win->handle = (WINDOW *) NULL;
      generic_win->is_visible = FALSE;
    }

  tui_win_info_del_window (win_info);
}

static void
src_disasm_win_free_window (struct tui_win_info *win_info)
{
  struct tui_winsource_win *src_win
    = (struct tui_winsource_win *) win_info;
  struct tui_gen_win_info *generic_win;

  generic_win = tui_locator_win_info_ptr ();
  if (generic_win != (struct tui_gen_win_info *) NULL)
    {
      tui_delete_win (generic_win->handle);
      generic_win->handle = (WINDOW *) NULL;
    }
  tui_free_win_content (generic_win);

  xfree (src_win->filename);
  src_win->filename = 0;

  generic_win = src_win->execution_info;
  if (generic_win != NULL)
    {
      tui_delete_win (generic_win->handle);
      generic_win->handle = (WINDOW *) NULL;
      tui_free_win_content (generic_win);
    }

  tui_win_info_free_window (win_info);
}

static void
data_win_del_window (struct tui_win_info *win_info)
{
  struct tui_data_display_win_info *data_win
    = (struct tui_data_display_win_info *) win_info;

  if (win_info->generic.content != NULL)
    {
      tui_del_data_windows (data_win->regs_content,
			    data_win->regs_content_count);
      tui_del_data_windows (data_win->data_content,
			    data_win->data_content_count);
    }

  tui_win_info_del_window (win_info);
}

static void
data_win_free_window (struct tui_win_info *win_info)
{
  struct tui_data_display_win_info *data_win
    = (struct tui_data_display_win_info *) win_info;

  if (win_info->generic.content != NULL)
    {
      tui_free_data_content (data_win->regs_content,
			     data_win->regs_content_count);
      data_win->regs_content = NULL;
      data_win->regs_content_count = 0;
      tui_free_data_content (data_win->data_content,
			     data_win->data_content_count);
      data_win->data_content = NULL;
      data_win->data_content_count = 0;
      data_win->regs_display_type = TUI_UNDEFINED_REGS;
      data_win->regs_column_count = 1;
      data_win->display_regs = FALSE;

      win_info->generic.content = NULL;
      win_info->generic.content_size = 0;
    }

  tui_win_info_free_window (win_info);
}


/* Delete all curses windows associated with win_info, leaving
   everything else intact.  */
void
tui_del_window (struct tui_win_info *win_info)
{
  win_info->vtable->del_window (win_info);
}

void
tui_free_window (struct tui_win_info *win_info)
{
  win_info->vtable->free_window (win_info);
}

void
tui_free_all_source_wins_content (void)
{
  int i;

  for (i = 0; i < (tui_source_windows ())->count; i++)
    {
      struct tui_win_info *win_info = (tui_source_windows ())->list[i];

      if (win_info != NULL)
	{
	  struct tui_winsource_win *src_win_info;
	  src_win_info = (struct tui_winsource_win *) win_info;

	  tui_free_win_content (&win_info->generic);
	  tui_free_win_content (src_win_info->execution_info);
	}
    }
}


void
tui_free_win_content (struct tui_gen_win_info *win_info)
{
  if (win_info->content != NULL)
    {
      free_content ((tui_win_content) win_info->content,
		   win_info->content_size,
		   win_info->type);
      win_info->content = NULL;
    }
  win_info->content_size = 0;
}


void
tui_del_data_windows (tui_win_content content, 
		      int content_size)
{
  int i;

  /* Remember that data window content elements are of type struct
     tui_gen_win_info *, each of which whose single element is a data
     element.  */
  for (i = 0; i < content_size; i++)
    {
      struct tui_gen_win_info *generic_win = &content[i]->which_element.data_window;

      if (generic_win != (struct tui_gen_win_info *) NULL)
	{
	  tui_delete_win (generic_win->handle);
	  generic_win->handle = (WINDOW *) NULL;
	  generic_win->is_visible = FALSE;
	}
    }
}


void
tui_free_data_content (tui_win_content content, 
		       int content_size)
{
  int i;

  /* Remember that data window content elements are of type struct
     tui_gen_win_info *, each of which whose single element is a data
     element.  */
  for (i = 0; i < content_size; i++)
    {
      struct tui_gen_win_info *generic_win = &content[i]->which_element.data_window;

      if (generic_win != (struct tui_gen_win_info *) NULL)
	{
	  tui_delete_win (generic_win->handle);
	  generic_win->handle = (WINDOW *) NULL;
	  tui_free_win_content (generic_win);
	}
    }
  free_content (content,
		content_size,
		DATA_WIN);
}


/**********************************
** LOCAL STATIC FUNCTIONS        **
**********************************/


static void
free_content (tui_win_content content, 
	      int content_size, 
	      enum tui_win_type win_type)
{
  if (content != (tui_win_content) NULL)
    {
      free_content_elements (content, content_size, win_type);
      xfree (content);
    }
}


/* free_content_elements().
 */
static void
free_content_elements (tui_win_content content, 
		       int content_size, 
		       enum tui_win_type type)
{
  if (content != (tui_win_content) NULL)
    {
      int i;

      if (type == SRC_WIN || type == DISASSEM_WIN)
	{
	  /* Free whole source block.  */
	  xfree (content[0]->which_element.source.line);
	}
      else
	{
	  for (i = 0; i < content_size; i++)
	    {
	      struct tui_win_element *element;

	      element = content[i];
	      if (element != (struct tui_win_element *) NULL)
		{
		  switch (type)
		    {
		    case DATA_WIN:
		      xfree (element);
		      break;
		    case DATA_ITEM_WIN:
		      /* Note that data elements are not allocated in
		         a single block, but individually, as
		         needed.  */
		      if (element->which_element.data.type != TUI_REGISTER)
			xfree ((void *)element->which_element.data.name);
		      xfree (element->which_element.data.value);
                      xfree (element->which_element.data.content);
		      xfree (element);
		      break;
		    case CMD_WIN:
		      xfree (element->which_element.command.line);
		      break;
		    default:
		      break;
		    }
		}
	    }
	}
      if (type != DATA_WIN && type != DATA_ITEM_WIN)
	xfree (content[0]);	/* Free the element block.  */
    }
}
