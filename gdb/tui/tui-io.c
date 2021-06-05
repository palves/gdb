/* TUI support I/O functions.

   Copyright (C) 1998-2021 Free Software Foundation, Inc.

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
#include "target.h"
#include "gdbsupport/event-loop.h"
#include "event-top.h"
#include "command.h"
#include "top.h"
#include "tui/tui.h"
#include "tui/tui-data.h"
#include "tui/tui-io.h"
#include "tui/tui-command.h"
#include "tui/tui-win.h"
#include "tui/tui-wingeneral.h"
#include "tui/tui-file.h"
#include "tui/tui-out.h"
#include "ui-out.h"
#include "cli-out.h"
#include <fcntl.h>
#include <signal.h>
#ifdef __MINGW32__
#include <windows.h>
#endif
#include "gdbsupport/filestuff.h"
#include "completer.h"
#include "gdb_curses.h"
#include <map>

/* This redefines CTRL if it is not already defined, so it must come
   after terminal state releated include files like <term.h> and
   "gdb_curses.h".  */
#include "readline/readline.h"

#ifdef __MINGW32__
static SHORT ncurses_norm_attr;
#endif

static int tui_getc (FILE *fp);

static int
key_is_start_sequence (int ch)
{
  return (ch == 27);
}

/* Use definition from readline 4.3.  */
#undef CTRL_CHAR
#define CTRL_CHAR(c) \
     ((c) < control_character_threshold && (((c) & 0x80) == 0))

/* This file controls the IO interactions between gdb and curses.
   When the TUI is enabled, gdb has two modes a curses and a standard
   mode.

   In curses mode, the gdb outputs are made in a curses command
   window.  For this, the gdb_stdout and gdb_stderr are redirected to
   the specific ui_file implemented by TUI.  The output is handled by
   tui_puts().  The input is also controlled by curses with
   tui_getc().  The readline library uses this function to get its
   input.  Several readline hooks are installed to redirect readline
   output to the TUI (see also the note below).

   In normal mode, the gdb outputs are restored to their origin, that
   is as if TUI is not used.  Readline also uses its original getc()
   function with stdin.

   Note SCz/2001-07-21: the current readline is not clean in its
   management of the output.  Even if we install a redisplay handler,
   it sometimes writes on a stdout file.  It is important to redirect
   every output produced by readline, otherwise the curses window will
   be garbled.  This is implemented with a pipe that TUI reads and
   readline writes to.  A gdb input handler is created so that reading
   the pipe is handled automatically.  This will probably not work on
   non-Unix platforms.  The best fix is to make readline clean enough
   so that is never write on stdout.

   Note SCz/2002-09-01: we now use more readline hooks and it seems
   that with them we don't need the pipe anymore (verified by creating
   the pipe and closing its end so that write causes a SIGPIPE).  The
   old pipe code is still there and can be conditionally removed by
   #undef TUI_USE_PIPE_FOR_READLINE.  */

/* For gdb 5.3, prefer to continue the pipe hack as a backup wheel.  */
#ifdef HAVE_PIPE
#define TUI_USE_PIPE_FOR_READLINE
#endif
/* #undef TUI_USE_PIPE_FOR_READLINE */

/* TUI output files.  */
static struct ui_file *tui_stdout;
static struct ui_file *tui_stderr;
struct ui_out *tui_out;

/* GDB output files in non-curses mode.  */
static struct ui_file *tui_old_stdout;
static struct ui_file *tui_old_stderr;
cli_ui_out *tui_old_uiout;

/* Readline previous hooks.  */
static rl_getc_func_t *tui_old_rl_getc_function;
static rl_voidfunc_t *tui_old_rl_redisplay_function;
static rl_vintfunc_t *tui_old_rl_prep_terminal;
static rl_voidfunc_t *tui_old_rl_deprep_terminal;
static rl_compdisp_func_t *tui_old_rl_display_matches_hook;
static int tui_old_rl_echoing_p;

/* Readline output stream.
   Should be removed when readline is clean.  */
static FILE *tui_rl_outstream;
static FILE *tui_old_rl_outstream;
#ifdef TUI_USE_PIPE_FOR_READLINE
static int tui_readline_pipe[2];
#endif

/* Print a character in the curses command window.  The output is
   buffered.  It is up to the caller to refresh the screen if
   necessary.  */

static void
do_tui_putc (WINDOW *w, char c)
{
  /* Expand TABs, since ncurses on MS-Windows doesn't.  */
  if (c == '\t')
    {
      int col;

      col = getcurx (w);
      do
	{
	  waddch (w, ' ');
	  col++;
	}
      while ((col % 8) != 0);
    }
  else
    waddch (w, c);
}

/* Update the cached value of the command window's start line based on
   the window's current Y coordinate.  */

static void
update_cmdwin_start_line ()
{
  TUI_CMD_WIN->start_line = getcury (TUI_CMD_WIN->handle.get ());
}

/* Print a character in the curses command window.  The output is
   buffered.  It is up to the caller to refresh the screen if
   necessary.  */

static void
tui_putc (char c)
{
  do_tui_putc (TUI_CMD_WIN->handle.get (), c);
  update_cmdwin_start_line ();
}

/* This maps colors to their corresponding color index.  */

static std::map<ui_file_style::color, int> color_map;

/* This holds a pair of colors and is used to track the mapping
   between a color pair index and the actual colors.  */

struct color_pair
{
  int fg;
  int bg;

  bool operator< (const color_pair &o) const
  {
    return fg < o.fg || (fg == o.fg && bg < o.bg);
  }
};

/* This maps pairs of colors to their corresponding color pair
   index.  */

static std::map<color_pair, int> color_pair_map;

/* This is indexed by ANSI color offset from the base color, and holds
   the corresponding curses color constant.  */

static const int curses_colors[] = {
  COLOR_BLACK,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_CYAN,
  COLOR_WHITE
};

/* Given a color, find its index.  */

static bool
get_color (const ui_file_style::color &color, int *result)
{
  if (color.is_none ())
    *result = -1;
  else if (color.is_basic ())
    *result = curses_colors[color.get_value ()];
  else
    {
      auto it = color_map.find (color);
      if (it == color_map.end ())
	{
	  /* The first 8 colors are standard.  */
	  int next = color_map.size () + 8;
	  if (next >= COLORS)
	    return false;
	  uint8_t rgb[3];
	  color.get_rgb (rgb);
	  /* We store RGB as 0..255, but curses wants 0..1000.  */
	  if (init_color (next, rgb[0] * 1000 / 255, rgb[1] * 1000 / 255,
			  rgb[2] * 1000 / 255) == ERR)
	    return false;
	  color_map[color] = next;
	  *result = next;
	}
      else
	*result = it->second;
    }
  return true;
}

/* The most recently emitted color pair.  */

static int last_color_pair = -1;

/* The most recently applied style.  */

static ui_file_style last_style;

/* If true, we're highlighting the current source line in reverse
   video mode.  */
static bool reverse_mode_p = false;

/* The background/foreground colors before we entered reverse
   mode.  */
static ui_file_style::color reverse_save_bg (ui_file_style::NONE);
static ui_file_style::color reverse_save_fg (ui_file_style::NONE);

/* Given two colors, return their color pair index; making a new one
   if necessary.  */

static int
get_color_pair (int fg, int bg)
{
  color_pair c = { fg, bg };
  auto it = color_pair_map.find (c);
  if (it == color_pair_map.end ())
    {
      /* Color pair 0 is our default color, so new colors start at
	 1.  */
      int next = color_pair_map.size () + 1;
      /* Curses has a limited number of available color pairs.  Fall
	 back to the default if we've used too many.  */
      if (next >= COLOR_PAIRS)
	return 0;
      init_pair (next, fg, bg);
      color_pair_map[c] = next;
      return next;
    }
  return it->second;
}

/* Apply STYLE to W.  */

void
tui_apply_style (WINDOW *w, ui_file_style style)
{
  /* Reset.  */
  wattron (w, A_NORMAL);
  wattroff (w, A_BOLD);
  wattroff (w, A_DIM);
  wattroff (w, A_REVERSE);
  if (last_color_pair != -1)
    wattroff (w, COLOR_PAIR (last_color_pair));
  wattron (w, COLOR_PAIR (0));

  const ui_file_style::color &fg = style.get_foreground ();
  const ui_file_style::color &bg = style.get_background ();
  if (!fg.is_none () || !bg.is_none ())
    {
      int fgi, bgi;
      if (get_color (fg, &fgi) && get_color (bg, &bgi))
	{
#ifdef __MINGW32__
	  /* MS-Windows port of ncurses doesn't support implicit
	     default foreground and background colors, so we must
	     specify them explicitly when needed, using the colors we
	     saw at startup.  */
	  if (fgi == -1)
	    fgi = ncurses_norm_attr & 15;
	  if (bgi == -1)
	    bgi = (ncurses_norm_attr >> 4) & 15;
#endif
	  int pair = get_color_pair (fgi, bgi);
	  if (last_color_pair != -1)
	    wattroff (w, COLOR_PAIR (last_color_pair));
	  wattron (w, COLOR_PAIR (pair));
	  last_color_pair = pair;
	}
    }

  switch (style.get_intensity ())
    {
    case ui_file_style::NORMAL:
      break;

    case ui_file_style::BOLD:
      wattron (w, A_BOLD);
      break;

    case ui_file_style::DIM:
      wattron (w, A_DIM);
      break;

    default:
      gdb_assert_not_reached ("invalid intensity");
    }

  if (style.is_reverse ())
    wattron (w, A_REVERSE);

  last_style = style;
}

/* Apply an ANSI escape sequence from BUF to W.  BUF must start with
   the ESC character.  If BUF does not start with an ANSI escape,
   return 0.  Otherwise, apply the sequence if it is recognized, or
   simply ignore it if not.  In this case, the number of bytes read
   from BUF is returned.  */

static size_t
apply_ansi_escape (WINDOW *w, const char *buf)
{
  ui_file_style style = last_style;
  size_t n_read;

  if (!style.parse (buf, &n_read))
    return n_read;

  if (reverse_mode_p)
    {
      /* We want to reverse _only_ the default foreground/background
	 colors.  If the foreground color is not the default (because
	 the text was styled), we want to leave it as is.  If e.g.,
	 the terminal is fg=BLACK, and bg=WHITE, and the style wants
	 to print text in RED, we want to reverse the background color
	 (print in BLACK), but still print the text in RED.  To do
	 that, we enable the A_REVERSE attribute, and re-reverse the
	 parsed-style's fb/bg colors.

	 Notes on the approach:

	  - there's no portable way to know which colors the default
	    fb/bg colors map to.

	  - this approach does the right thing even if you change the
	    terminal colors while GDB is running -- the reversed
	    colors automatically adapt.
      */
      if (!style.is_default ())
	{
	  ui_file_style::color bg = style.get_background ();
	  ui_file_style::color fg = style.get_foreground ();
	  style.set_fg (bg);
	  style.set_bg (fg);
	}

      /* Enable A_REVERSE.  */
      style.set_reverse (true);
    }

  tui_apply_style (w, style);
  return n_read;
}

/* See tui.io.h.  */

void
tui_set_reverse_mode (WINDOW *w, bool reverse)
{
  ui_file_style style = last_style;

  reverse_mode_p = reverse;
  style.set_reverse (reverse);

  if (reverse)
    {
      reverse_save_bg = style.get_background ();
      reverse_save_fg = style.get_foreground ();
    }
  else
    {
      style.set_bg (reverse_save_bg);
      style.set_fg (reverse_save_fg);
    }

  tui_apply_style (w, style);
}

/* Print LENGTH characters from the buffer pointed to by BUF to the
   curses command window.  The output is buffered.  It is up to the
   caller to refresh the screen if necessary.  */

void
tui_write (const char *buf, size_t length)
{
  /* We need this to be \0-terminated for the regexp matching.  */
  std::string copy (buf, length);
  tui_puts (copy.c_str ());
}

/* Print a string in the curses command window.  The output is
   buffered.  It is up to the caller to refresh the screen if
   necessary.  */

void
tui_puts (const char *string, WINDOW *w)
{
  if (w == nullptr)
    w = TUI_CMD_WIN->handle.get ();

  while (true)
    {
      const char *next = strpbrk (string, "\n\1\2\033\t");

      /* Print the plain text prefix.  */
      size_t n_chars = next == nullptr ? strlen (string) : next - string;
      if (n_chars > 0)
	waddnstr (w, string, n_chars);

      /* We finished.  */
      if (next == nullptr)
	break;

      char c = *next;
      switch (c)
	{
	case '\1':
	case '\2':
	  /* Ignore these, they are readline escape-marking
	     sequences.  */
	  ++next;
	  break;

	case '\n':
	case '\t':
	  do_tui_putc (w, c);
	  ++next;
	  break;

	case '\033':
	  {
	    size_t bytes_read = apply_ansi_escape (w, next);
	    if (bytes_read > 0)
	      next += bytes_read;
	    else
	      {
		/* Just drop the escape.  */
		++next;
	      }
	  }
	  break;

	default:
	  gdb_assert_not_reached ("missing case in tui_puts");
	}

      string = next;
    }

  if (TUI_CMD_WIN != nullptr && w == TUI_CMD_WIN->handle.get ())
    update_cmdwin_start_line ();
}

static void
tui_puts_internal (WINDOW *w, const char *string, int *height)
{
  char c;
  int prev_col = 0;
  bool saw_nl = false;

  while ((c = *string++) != 0)
    {
      if (c == '\n')
	saw_nl = true;

      if (c == '\1' || c == '\2')
	{
	  /* Ignore these, they are readline escape-marking
	     sequences.  */
	}
      else
	{
	  if (c == '\033')
	    {
	      size_t bytes_read = apply_ansi_escape (w, string - 1);
	      if (bytes_read > 0)
		{
		  string = string + bytes_read - 1;
		  continue;
		}
	    }
	  do_tui_putc (w, c);

	  if (height != nullptr)
	    {
	      int col = getcurx (w);
	      if (col <= prev_col)
		++*height;
	      prev_col = col;
	    }
	}
    }
  if (TUI_CMD_WIN != nullptr && w == TUI_CMD_WIN->handle.get ())
    update_cmdwin_start_line ();
  if (saw_nl)
    wrefresh (w);
}

/* Readline callback.
   Redisplay the command line with its prompt after readline has
   changed the edited text.  */
void
tui_redisplay_readline (void)
{
  int prev_col;
  int height;
  int col;
  int c_pos;
  int c_line;
  int in;
  WINDOW *w;
  const char *prompt;
  int start_line;

  /* Detect when we temporarily left SingleKey and now the readline
     edit buffer is empty, automatically restore the SingleKey
     mode.  The restore must only be done if the command has finished.
     The command could call prompt_for_continue and we must not
     restore SingleKey so that the prompt and normal keymap are used.  */
  if (tui_current_key_mode == TUI_ONE_COMMAND_MODE && rl_end == 0
      && !gdb_in_secondary_prompt_p (current_ui))
    tui_set_key_mode (TUI_SINGLE_KEY_MODE);

  if (tui_current_key_mode == TUI_SINGLE_KEY_MODE)
    prompt = "";
  else
    prompt = rl_display_prompt;
  
  c_pos = -1;
  c_line = -1;
  w = TUI_CMD_WIN->handle.get ();
  start_line = TUI_CMD_WIN->start_line;
  wmove (w, start_line, 0);
  prev_col = 0;
  height = 1;
  if (prompt != nullptr)
    tui_puts_internal (w, prompt, &height);

  prev_col = getcurx (w);
  for (in = 0; in <= rl_end; in++)
    {
      unsigned char c;
      
      if (in == rl_point)
	{
	  getyx (w, c_line, c_pos);
	}

      if (in == rl_end)
	break;

      c = (unsigned char) rl_line_buffer[in];
      if (CTRL_CHAR (c) || c == RUBOUT)
	{
	  waddch (w, '^');
	  waddch (w, CTRL_CHAR (c) ? UNCTRL (c) : '?');
	}
      else if (c == '\t')
	{
	  /* Expand TABs, since ncurses on MS-Windows doesn't.  */
	  col = getcurx (w);
	  do
	    {
	      waddch (w, ' ');
	      col++;
	    } while ((col % 8) != 0);
	}
      else
	{
	  waddch (w, c);
	}
      if (c == '\n')
	TUI_CMD_WIN->start_line = getcury (w);
      col = getcurx (w);
      if (col < prev_col)
	height++;
      prev_col = col;
    }
  wclrtobot (w);
  TUI_CMD_WIN->start_line = getcury (w);
  if (c_line >= 0)
    wmove (w, c_line, c_pos);
  TUI_CMD_WIN->start_line -= height - 1;

  wrefresh (w);
  fflush(stdout);
}

/* Readline callback to prepare the terminal.  It is called once each
   time we enter readline.  Terminal is already setup in curses
   mode.  */
static void
tui_prep_terminal (int notused1)
{
#ifdef NCURSES_MOUSE_VERSION
  mousemask (ALL_MOUSE_EVENTS, NULL);
#endif
}

/* Readline callback to restore the terminal.  It is called once each
   time we leave readline.  There is nothing to do in curses mode.  */
static void
tui_deprep_terminal (void)
{
#ifdef NCURSES_MOUSE_VERSION
  mousemask (0, NULL);
#endif
}

#ifdef TUI_USE_PIPE_FOR_READLINE
/* Read readline output pipe and feed the command window with it.
   Should be removed when readline is clean.  */
static void
tui_readline_output (int error, gdb_client_data data)
{
  int size;
  char buf[256];

  size = read (tui_readline_pipe[0], buf, sizeof (buf) - 1);
  if (size > 0 && tui_active)
    {
      buf[size] = 0;
      tui_puts (buf);
    }
}
#endif

/* TUI version of displayer.crlf.  */

static void
tui_mld_crlf (const struct match_list_displayer *displayer)
{
  tui_putc ('\n');
}

/* TUI version of displayer.putch.  */

static void
tui_mld_putch (const struct match_list_displayer *displayer, int ch)
{
  tui_putc (ch);
}

/* TUI version of displayer.puts.  */

static void
tui_mld_puts (const struct match_list_displayer *displayer, const char *s)
{
  tui_puts (s);
}

/* TUI version of displayer.flush.  */

static void
tui_mld_flush (const struct match_list_displayer *displayer)
{
  wrefresh (TUI_CMD_WIN->handle.get ());
}

/* TUI version of displayer.erase_entire_line.  */

static void
tui_mld_erase_entire_line (const struct match_list_displayer *displayer)
{
  WINDOW *w = TUI_CMD_WIN->handle.get ();
  int cur_y = getcury (w);

  wmove (w, cur_y, 0);
  wclrtoeol (w);
  wmove (w, cur_y, 0);
}

/* TUI version of displayer.beep.  */

static void
tui_mld_beep (const struct match_list_displayer *displayer)
{
  beep ();
}

/* A wrapper for wgetch that enters nonl mode.  We We normally want
  curses' "nl" mode, but when reading from the user, we'd like to
  differentiate between C-j and C-m, because some users bind these
  keys differently in their .inputrc.  So, put curses into nonl mode
  just when reading from the user.  See PR tui/20819.  */

static int
gdb_wgetch (WINDOW *win)
{
  nonl ();
  int r = wgetch (win);
  nl ();
  return r;
}

/* Helper function for tui_mld_read_key.
   This temporarily replaces tui_getc for use during tab-completion
   match list display.  */

static int
tui_mld_getc (FILE *fp)
{
  WINDOW *w = TUI_CMD_WIN->handle.get ();
  int c = gdb_wgetch (w);

  return c;
}

/* TUI version of displayer.read_key.  */

static int
tui_mld_read_key (const struct match_list_displayer *displayer)
{
  rl_getc_func_t *prev = rl_getc_function;
  int c;

  /* We can't use tui_getc as we need NEWLINE to not get emitted.  */
  rl_getc_function = tui_mld_getc;
  c = rl_read_key ();
  rl_getc_function = prev;
  return c;
}

/* TUI version of rl_completion_display_matches_hook.
   See gdb_display_match_list for a description of the arguments.  */

static void
tui_rl_display_match_list (char **matches, int len, int max)
{
  struct match_list_displayer displayer;

  rl_get_screen_size (&displayer.height, &displayer.width);
  displayer.crlf = tui_mld_crlf;
  displayer.putch = tui_mld_putch;
  displayer.puts = tui_mld_puts;
  displayer.flush = tui_mld_flush;
  displayer.erase_entire_line = tui_mld_erase_entire_line;
  displayer.beep = tui_mld_beep;
  displayer.read_key = tui_mld_read_key;

  gdb_display_match_list (matches, len, max, &displayer);
}

/* Setup the IO for curses or non-curses mode.
   - In non-curses mode, readline and gdb use the standard input and
   standard output/error directly.
   - In curses mode, the standard output/error is controlled by TUI
   with the tui_stdout and tui_stderr.  The output is redirected in
   the curses command window.  Several readline callbacks are installed
   so that readline asks for its input to the curses command window
   with wgetch().  */
void
tui_setup_io (int mode)
{
  extern int _rl_echoing_p;

  if (mode)
    {
      /* Ensure that readline has been initialized before saving any
	 of its variables.  */
      tui_ensure_readline_initialized ();

      /* Redirect readline to TUI.  */
      tui_old_rl_redisplay_function = rl_redisplay_function;
      tui_old_rl_deprep_terminal = rl_deprep_term_function;
      tui_old_rl_prep_terminal = rl_prep_term_function;
      tui_old_rl_getc_function = rl_getc_function;
      tui_old_rl_display_matches_hook = rl_completion_display_matches_hook;
      tui_old_rl_outstream = rl_outstream;
      tui_old_rl_echoing_p = _rl_echoing_p;
      rl_redisplay_function = tui_redisplay_readline;
      rl_deprep_term_function = tui_deprep_terminal;
      rl_prep_term_function = tui_prep_terminal;
      rl_getc_function = tui_getc;
      _rl_echoing_p = 0;
      rl_outstream = tui_rl_outstream;
      rl_prompt = 0;
      rl_completion_display_matches_hook = tui_rl_display_match_list;
      rl_already_prompted = 0;

      /* Keep track of previous gdb output.  */
      tui_old_stdout = gdb_stdout;
      tui_old_stderr = gdb_stderr;
      tui_old_uiout = dynamic_cast<cli_ui_out *> (current_uiout);
      gdb_assert (tui_old_uiout != nullptr);

      /* Reconfigure gdb output.  */
      gdb_stdout = tui_stdout;
      gdb_stderr = tui_stderr;
      gdb_stdlog = gdb_stdout;	/* for moment */
      gdb_stdtarg = gdb_stderr;	/* for moment */
      gdb_stdtargerr = gdb_stderr;	/* for moment */
      current_uiout = tui_out;

      /* Save tty for SIGCONT.  */
      savetty ();
    }
  else
    {
      /* Restore gdb output.  */
      gdb_stdout = tui_old_stdout;
      gdb_stderr = tui_old_stderr;
      gdb_stdlog = gdb_stdout;	/* for moment */
      gdb_stdtarg = gdb_stderr;	/* for moment */
      gdb_stdtargerr = gdb_stderr;	/* for moment */
      current_uiout = tui_old_uiout;

      /* Restore readline.  */
      rl_redisplay_function = tui_old_rl_redisplay_function;
      rl_deprep_term_function = tui_old_rl_deprep_terminal;
      rl_prep_term_function = tui_old_rl_prep_terminal;
      rl_getc_function = tui_old_rl_getc_function;
      rl_completion_display_matches_hook = tui_old_rl_display_matches_hook;
      rl_outstream = tui_old_rl_outstream;
      _rl_echoing_p = tui_old_rl_echoing_p;
      rl_already_prompted = 0;

      /* Save tty for SIGCONT.  */
      savetty ();

      /* Clean up color information.  */
      last_color_pair = -1;
      last_style = ui_file_style ();
      color_map.clear ();
      color_pair_map.clear ();
    }
}

#ifdef SIGCONT
/* Catch SIGCONT to restore the terminal and refresh the screen.  */
static void
tui_cont_sig (int sig)
{
  if (tui_active)
    {
      /* Restore the terminal setting because another process (shell)
	 might have changed it.  */
      resetty ();

      /* Force a refresh of the screen.  */
      tui_refresh_all_win ();
    }
  signal (sig, tui_cont_sig);
}
#endif

/* Initialize the IO for gdb in curses mode.  */
void
tui_initialize_io (void)
{
#ifdef SIGCONT
  signal (SIGCONT, tui_cont_sig);
#endif

  /* Create tui output streams.  */
  tui_stdout = new tui_file (stdout);
  tui_stderr = new tui_file (stderr);
  tui_out = tui_out_new (tui_stdout);

  /* Create the default UI.  */
  tui_old_uiout = cli_out_new (gdb_stdout);

#ifdef TUI_USE_PIPE_FOR_READLINE
  /* Temporary solution for readline writing to stdout: redirect
     readline output in a pipe, read that pipe and output the content
     in the curses command window.  */
  if (gdb_pipe_cloexec (tui_readline_pipe) != 0)
    error (_("Cannot create pipe for readline"));

  tui_rl_outstream = fdopen (tui_readline_pipe[1], "w");
  if (tui_rl_outstream == 0)
    error (_("Cannot redirect readline output"));

  setvbuf (tui_rl_outstream, NULL, _IOLBF, 0);

#ifdef O_NONBLOCK
  (void) fcntl (tui_readline_pipe[0], F_SETFL, O_NONBLOCK);
#else
#ifdef O_NDELAY
  (void) fcntl (tui_readline_pipe[0], F_SETFL, O_NDELAY);
#endif
#endif
  add_file_handler (tui_readline_pipe[0], tui_readline_output, 0, "tui");
#else
  tui_rl_outstream = stdout;
#endif

#ifdef __MINGW32__
  /* MS-Windows port of ncurses doesn't support default foreground and
     background colors, so we must record the default colors at startup.  */
  HANDLE hstdout = (HANDLE)_get_osfhandle (fileno (stdout));
  DWORD cmode;
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if (hstdout != INVALID_HANDLE_VALUE
      && GetConsoleMode (hstdout, &cmode) != 0
      && GetConsoleScreenBufferInfo (hstdout, &csbi))
    ncurses_norm_attr = csbi.wAttributes;
#endif
}

/* Dispatch the correct tui function based upon the mouse event.  */

static void
tui_dispatch_mouse_event (const MEVENT &mev)
{
  for (tui_win_info *wi : all_tui_windows ())
    if (mev.x > wi->x && mev.x < wi->x + wi->width - 1
	&& mev.y > wi->y && mev.y < wi->y + wi->height - 1)
      {
	if ((mev.bstate & BUTTON1_CLICKED) != 0
	    || (mev.bstate & BUTTON2_CLICKED) != 0
	    || (mev.bstate & BUTTON3_CLICKED) != 0)
	  {
	    int button = (mev.bstate & BUTTON1_CLICKED) != 0 ? 1
	      :         ((mev.bstate & BUTTON2_CLICKED) != 0 ? 2
			 : 3);
	    wi->click (mev.x - wi->x - 1, mev.y - wi->y - 1, button);
	  }
#ifdef BUTTON5_PRESSED
	else if ((mev.bstate & BUTTON4_PRESSED) != 0)
	  wi->backward_scroll (3);
	else if ((mev.bstate & BUTTON5_PRESSED) != 0)
	  wi->forward_scroll (3);
#endif
	break;
      }
}

/* Dispatch the correct tui function based upon the control
   character.  */
static unsigned int
tui_dispatch_ctrl_char (unsigned int ch)
{
  struct tui_win_info *win_info = tui_win_with_focus ();

  /* Handle the CTRL-L refresh for each window.  */
  if (ch == '\f')
    tui_refresh_all_win ();

  /* If no window has the focus, or if the focus window can't scroll,
     just pass the character through.  */
  if (win_info == NULL
      || (win_info != TUI_CMD_WIN
	  && !win_info->can_scroll ()))
    return ch;

  switch (ch)
    {
    case KEY_NPAGE:
      win_info->forward_scroll (0);
      break;
    case KEY_PPAGE:
      win_info->backward_scroll (0);
      break;
    case KEY_DOWN:
    case KEY_SF:
      win_info->forward_scroll (1);
      break;
    case KEY_UP:
    case KEY_SR:
      win_info->backward_scroll (1);
      break;
    case KEY_RIGHT:
      win_info->left_scroll (1);
      break;
    case KEY_LEFT:
      win_info->right_scroll (1);
      break;
#ifdef NCURSES_MOUSE_VERSION
    case KEY_MOUSE:
	{
	  MEVENT mev;
	  if (getmouse (&mev) == OK)
	    tui_dispatch_mouse_event (mev);
	}
      break;
#endif
    case '\f':
      break;
    default:
      /* We didn't recognize the character as a control character, so pass it
	 through.  */
      return ch;
    }

  /* We intercepted the control character, so return 0 (which readline
     will interpret as a no-op).  */
  return 0;
}

/* See tui-io.h.   */

void
tui_inject_newline_into_command_window ()
{
  gdb_assert (tui_active);

  WINDOW *w= TUI_CMD_WIN->handle.get ();

  /* When hitting return with an empty input, gdb executes the last
     command.  If we emit a newline, this fills up the command window
     with empty lines with gdb prompt at beginning.  Instead of that,
     stay on the same line but provide a visual effect to show the
     user we recognized the command.  */
  if (rl_end == 0 && !gdb_in_secondary_prompt_p (current_ui))
    {
      wmove (w, getcury (w), 0);

      /* Clear the line.  This will blink the gdb prompt since
	 it will be redrawn at the same line.  */
      wclrtoeol (w);
      wrefresh (w);
      napms (20);
    }
  else
    {
      /* Move cursor to the end of the command line before emitting the
	 newline.  We need to do so because when ncurses outputs a newline
	 it truncates any text that appears past the end of the cursor.  */
      int px, py;
      getyx (w, py, px);
      px += rl_end - rl_point;
      py += px / TUI_CMD_WIN->width;
      px %= TUI_CMD_WIN->width;
      wmove (w, py, px);
      tui_putc ('\n');
    }
}

/* True if the mouse thread is the one reading stdin.  */
static volatile bool mouse_thread_stdin = false;
static volatile bool mouse_thread_stdin_out = false;

/* The handle to the mouse thread.  */
static pthread_t mouse_thread;

/* Pipe used to wake up / interrupt the mouse thread.  */
static int intr_mouse_thread[2];

/* Pipe used to feed input data into the magic mouse screen.  */
static int mouse_input_pipe[2];

/* Data we've read from stdin but did not want passed to ncurses.  */
static std::vector<int> mouse_chars;

/* True if the next tut_getc_1 should drain from CHARS.  */
static bool drain_mouse_chars;

/* Enable debugging the mouse screen and thread processing.  */
static bool debug_mouse_thread = 0;

/* The escape sequence header for a mouse event.  */
static const unsigned char mouse_seq[] = { 27, '[', 'M' };
/* Pointer to the next expected character in a mouse escape sequence.
   If we haven't seen any character of the sequence yet, this points
   to the first character of MOUSE_SEQ.  If we've seen the whole
   sequence header, this points to one-past-last of MOUSE_SEQ.  */
static const unsigned char *mouse_seq_pos = nullptr;

/* True if the last key we got out of gdb_wgetch was a KEY_MOUSE.  In
   that case, continue reading chars using the magic mouse screen.  */
static bool last_key_was_mouse = false;

/* The mouse screen used to read mouse keys.  This screen's main
   window has the keypad enabled so that it processes mouse escape
   sequences.  But instead of reading from stdin, it reads from a
   pipe.  This pipe is filled with data read from stdin, but filtered
   -- it won't ever include non-mouse escape sequences.  This means
   that reading from this curses screen either returns KEY_MOUSE, or
   regular ASCII key, never KEY_UP, etc.  */
static SCREEN *mouse_screen;

/* Write CH to the mouse input pipe.  */

static void
write_mouse_pipe (int ch)
{
  unsigned char buf = ch;
  write (mouse_input_pipe[1], &buf, 1);
}

/* Wake up the mouse thread.  */

static void
wake_mouse_thread ()
{
  unsigned char buf = '+';
  write (intr_mouse_thread[1], &buf, 1);
}

/* Flush the INTR_MOUSE_THREAD pipe.  */

static void
flush_intr_mouse_pipe ()
{
  int ret;

  do
    {
      char buf;
      ret = read (intr_mouse_thread[0], &buf, 1);
    }
  while (ret >= 0 || (ret == -1 && errno == EINTR));
}

/* Flush data out of stdin, into the MOUSE_INPUT_PIPE.  Except, if we
   see an escape sequence that isn't a mouse escape sequence, don't
   put it in the pipe.  The idea is that we never want ncurses to see
   non-mouse escape sequences.  We want to pass those directly to
   readline.  E.g., we don't want ncurses to return KEY_UP, we want
   readline instead to see the "key up" escape sequence, and call
   "previous-history".  */

static void *
mouse_thread_fn (void *)
{
  /* XXXX: Block signals in parent before spawning this.  */

  while (1)
    {
      fd_set readfds;

      FD_ZERO (&readfds);
      FD_SET (intr_mouse_thread[0], &readfds);

      if (mouse_thread_stdin)
	FD_SET (0, &readfds);

      if (select (intr_mouse_thread[0] + 1, &readfds, NULL, NULL, NULL) == -1)
	{
	  if (errno == EINTR)
	    continue;

	  /* XXX: shouldn't throw...  */
	  perror_with_name (("select"));
	}

      if (FD_ISSET (0, &readfds))
	{
	  unsigned char ch;
	  int n = read (0, &ch, 1);
	  if (n == 1)
	    {
	      if (ch == *mouse_seq_pos)
		{
		  /* Looks like another character part of a mouse
		     escape sequence.  */
		  mouse_seq_pos++;

		  if (mouse_seq_pos == mouse_seq + sizeof (mouse_seq))
		    {
		      /* Yup, we saw "ESC [ M".  */

		      if (debug_mouse_thread)
			fprintf (stderr, "thread: got mouse sequence header\n");

		      for (size_t i = 0; i < sizeof (mouse_seq); i++)
			{
			  write_mouse_pipe (mouse_seq[i]);
			  if (debug_mouse_thread)
			    fprintf (stderr, "thread: %c (%d) ",
				     mouse_seq[i], mouse_seq[i]);
			}

		      mouse_seq_pos = mouse_seq;
		    }
		}
	      else if (mouse_seq_pos > mouse_seq)
		{
		  if (debug_mouse_thread)
		    fprintf (stderr,
			     "thread: non-mouse escape sequence, STOP!\n");

		  /* Store the sequence in MOUSE_CHARS instead of in
		     the pipe.  We don't want ncurses to see it.  */
		  for (size_t i = 0; i < mouse_seq_pos - mouse_seq; i++)
		    {
		      mouse_chars.push_back (mouse_seq[i]);
		      if (debug_mouse_thread)
			fprintf (stderr, "thread: %c (%d) ",
				 mouse_seq[i], mouse_seq[i]);
		    }
		  mouse_chars.push_back (ch);
		  if (debug_mouse_thread)
		    fprintf (stderr, "thread: %c (%d) ", ch, ch);

		  /* The mainline code is blocked in wgetch, and we
		     need to wake it up, but we don't want to let
		     ncurses see this sequence.  Solve this by putting
		     a 0/NIL character in the pipe.  That pass through
		     wgetch and we will end up returning 0 to
		     readline, which readline interprets as "no op",
		     exactly what we want.  Phew!  */
		  write_mouse_pipe (0);

		  /* Reset the sequence position pointer, and stop
		     reading stdin until the mainline code tells us
		     otherwise.  */
		  mouse_seq_pos = mouse_seq;
		  mouse_thread_stdin = false;
		}
	      else
		{
		  write_mouse_pipe (ch);

		  if (debug_mouse_thread)
		    fprintf (stderr, "thread: %c (%d) ", ch, ch);
		}
	    }
	  else
	    {
	      if (debug_mouse_thread)
		fprintf (stderr, "thread: => -1!");
	    }
	  if (debug_mouse_thread)
	    fflush (stderr);
	}

      if (FD_ISSET (intr_mouse_thread[0], &readfds))
	{
	  int ret;

	  if (debug_mouse_thread)
	    fprintf (stderr, "break thread\n");

	  do
	    {
	      char buf;
	      ret = read (intr_mouse_thread[0], &buf, 1);
	    }
	  while (ret == -1 && errno == EINTR);

	  mouse_thread_stdin_out = mouse_thread_stdin;
	  continue;
	}
    }

  return nullptr;
}

/* Initialize the special mouse screen, and all auxiliary bits.  */

void
init_mouse_screen ()
{
  /* Pseudo-stdin pipe for the ncurses mouse "terminal".  */
  if (gdb_pipe_cloexec (mouse_input_pipe) != 0)
    error (_("Cannot create pipe for mouse"));

  /* The self-trick pipe used to wake up / interrupt the mouse
     thread.  */
  if (gdb_pipe_cloexec (intr_mouse_thread) != 0)
    error (_("Cannot create pipe for mouse interruption"));
  fcntl (intr_mouse_thread[0], F_SETFL, O_NONBLOCK);
  fcntl (intr_mouse_thread[1], F_SETFL, O_NONBLOCK);

  /* Create the mouse terminal.  It reads from the mouse input pipe,
     and writes nowhere.  */
  FILE *in = fdopen (mouse_input_pipe[0], "r");
  FILE *out = fopen ("/dev/null", "w+");
  setvbuf (in, NULL, _IONBF, BUFSIZ);

  mouse_screen = newterm (NULL, out, in);
  mousemask (ALL_MOUSE_EVENTS, NULL);

  /* Enable the keypad, we want to use this terminal to process mouse
     escape codes.  */
  WINDOW *w = stdscr;
  keypad (w, TRUE);

  /* Spawn the mouse thread.  */
  pthread_create (&mouse_thread, nullptr, mouse_thread_fn, nullptr);
}

/* Main worker for tui_getc.  Get a character from the command window.
   This is called from the readline package, but wrapped in a
   try/catch by tui_getc.  */

static int
tui_getc_1 (FILE *fp)
{
  int ch;
  WINDOW *w;

  w = TUI_CMD_WIN->handle.get ();

#ifdef TUI_USE_PIPE_FOR_READLINE
  /* Flush readline output.  */
  tui_readline_output (0, 0);
#endif

  if (tui_win_with_focus () == TUI_CMD_WIN && current_ui->command_editing)
    {
      if (drain_mouse_chars)
	{
	  ch = mouse_chars.front ();
	  mouse_chars.erase (mouse_chars.begin ());
	  if (debug_mouse_thread)
	    fprintf (stderr, "drain: got %c (%d), ", ch, ch);
	  if (mouse_chars.empty ())
	    {
	      drain_mouse_chars = false;
	      if (debug_mouse_thread)
		fprintf (stderr, " : done\r\n");
	    }
	  else
	    call_stdin_event_handler_again_p = 1;
	  return ch;
	}
      else if (!last_key_was_mouse)
	{
	  ch = gdb_wgetch (w);
	}

      if (last_key_was_mouse || key_is_start_sequence (ch))
	{
	  /* Process this key sequence with the special mouse ncurses
	     screen, which has the keypad enabled, and reads from
	     MOUSE_INPUT_PIPE.  */

	  /* Set the current screen to the mouse screen.  */
	  WINDOW *prev_stdscr = stdscr;
	  SCREEN *prev_s = set_term (mouse_screen);
	  /* The mouse WINDOW.  */
	  WINDOW *mw = stdscr;

	  if (last_key_was_mouse)
	    {
	      if (debug_mouse_thread)
		fprintf (stderr, "last key was mouse\r\n");
	    }

	  /* If we're just starting a sequence, block waiting for the
	     whole sequence.  If we're here because we returned a
	     mouse event before and we're now draining the curses
	     buffer, disable blocking.  */
	  if (last_key_was_mouse)
	    nodelay (mw, TRUE);
	  else
	    nodelay (mw, FALSE);

	  flush_intr_mouse_pipe ();

	  /* If we're starting a new sequence, reset the sequence
	     position.  If we last saw a mouse key, then the mouse
	     thread may have read a partial mouse event out of stdin,
	     so we need to let it continue the sequence where it left
	     it last.  */
	  if (!last_key_was_mouse)
	    mouse_seq_pos = &mouse_seq[1];

	  /* Set the thread reading from stdin.  */
	  mouse_thread_stdin = true;
	  wake_mouse_thread ();
	  while (!mouse_thread_stdin_out)
	    ;

	  using namespace std::chrono;

	  steady_clock::time_point before = steady_clock::now ();

	  /* Read one cooked key out of the mouse window.  */
	  ch = gdb_wgetch (mw);

	  steady_clock::time_point after = steady_clock::now ();

	  auto diff = after - before;
	  seconds s = duration_cast<seconds> (diff);
	  microseconds us = duration_cast<microseconds> (diff - s);
	  if (debug_mouse_thread)
	    fprintf (stderr, "wgetch took: %ld.%06ld\n",
		     (long) s.count (),
		     (long) us.count ());

	  /* Tell the thread to stop reading stdin, and wait until it
	     acknowledges it.  */
	  mouse_thread_stdin = false;
	  wake_mouse_thread ();
	  while (mouse_thread_stdin_out)
	    ;

	  if (ch == ERR)
	    {
	      /* We get here if the previous key returned was a mouse
		 key, and thus disabled blocked in order to flush all
		 keys.  ERR means there are no more keys in the curses
		 buffer.  */
	      if (debug_mouse_thread)
		fprintf (stderr, "got ERR\r\n");

	      /* Stop draining curses.  */
	      last_key_was_mouse = false;

	      /* If the thread saw a non-mouse escape sequence, we
		 need to drain it next.  */
	      if (!mouse_chars.empty ())
		{
		  drain_mouse_chars = true;
		  call_stdin_event_handler_again_p = 1;
		}

	      ch = 0;
	    }
	  else if (ch == KEY_MOUSE)
	    {
	      if (debug_mouse_thread)
		fprintf (stderr, "KEY_MOUSE\n");

	      /* Process this mouse key, and set up to drain other
		 keys that ncurses may have read into its internal
		 buffer already.  */
	      last_key_was_mouse = true;
	      call_stdin_event_handler_again_p = 1;

	      /* Get the mouse event.  This must be called with the
		 mouse screen as current.  */
	      MEVENT mev;
	      if (getmouse (&mev) == OK)
		{
		  /* Now handle the mouse event.  This must be done
		     with the normal screen as current.  */
		  set_term (prev_s);
		  stdscr = prev_stdscr;

		  /* Handle prev/next/up/down here.  */
		  tui_dispatch_mouse_event (mev);
		}

	      return 0;
	    }
	  else
	    {
	      if (debug_mouse_thread)
		fprintf (stderr, "not KEY_MOUSE, %c (%d)\n", ch, ch);

	      last_key_was_mouse = false;

	      /* Drain data buffered on the ncurses side and/or in the
		 pipe.  */
	      nodelay (mw, TRUE);

	      /* Data already in MOUSE_CHARS must be returned to
		 readline _after_ the data ncurses already fetched
		 from the pipe into its own internal buffer.  IOW, the
		 ncurses buffered data must be prepended into
		 MOUSE_CHARS.  Start by draining ncurses data into a
		 temporary vector.  */
	      std::vector<int> tmp_chars;
	      int ch2 = gdb_wgetch (mw);
	      if (ch2 != ERR)
		{
		  if (debug_mouse_thread)
		    fprintf (stderr, "more data!: %c (%d)", ch2, ch2);
		  gdb_assert (ch2 != KEY_MOUSE);
		  tmp_chars.push_back (ch2);
		  while (1)
		    {
		      ch2 = gdb_wgetch (mw);
		      if (ch2 == ERR)
			{
			  if (debug_mouse_thread)
			    fprintf (stderr, ", ERR");
			  break;
			}
		      else
			{
			  if (debug_mouse_thread)
			    fprintf (stderr, ", %c (%d)", ch2, ch2);
			  gdb_assert (ch2 != KEY_MOUSE);
			  tmp_chars.push_back (ch2);
			}
		    }
		  if (debug_mouse_thread)
		    {
		      fprintf (stderr, "\n");
		      fflush (stderr);
		    }
		}

	      nodelay (mw, FALSE);

	      /* Now append the data that was already in MOUSE_CHARS
		 in the temporary vector.  */
	      tmp_chars.insert (tmp_chars.end (),
				mouse_chars.begin (), mouse_chars.end ());

	      /* And make the result the new MOUSE_CHARS.  */
	      mouse_chars = std::move (tmp_chars);

	      if (debug_mouse_thread)
		fprintf (stderr, "got %c (%d), ", ch, ch);
	      if (!mouse_chars.empty ())
		{
		  drain_mouse_chars = true;
		  call_stdin_event_handler_again_p = 1;
		}
	    }

	  /* Restore the regular screen as current.  */
	  set_term (prev_s);
	  stdscr = prev_stdscr;
	}
      else
	{
	  if (debug_mouse_thread)
	    fprintf (stderr, "tui_get_c_1: not escape: %c (%d)\n", ch, ch);
	}
    }
  else
    {
      using namespace std::chrono;

      steady_clock::time_point before = steady_clock::now ();

      ch = gdb_wgetch (w);

      steady_clock::time_point after = steady_clock::now ();

      auto diff = after - before;
      seconds s = duration_cast<seconds> (diff);
      microseconds us = duration_cast<microseconds> (diff - s);
#if 0
      fprintf (stderr, "wgetch took: %ld.%06ld\n",
	       (long) s.count (),
	       (long) us.count ());
#endif

      /* Handle prev/next/up/down here.  */
      ch = tui_dispatch_ctrl_char (ch);
    }

  if (ch == KEY_BACKSPACE)
    return '\b';

#if 0
  /* XXX: see about re-enabling this.  */
  if (current_ui->command_editing && key_is_start_sequence (ch))
    {
      int ch_pending;

      nodelay (w, TRUE);
      ch_pending = gdb_wgetch (w);
      nodelay (w, FALSE);

      /* If we have pending input following a start sequence, call the stdin
	 event handler again because ncurses may have already read and stored
	 the input into its internal buffer, meaning that we won't get an stdin
	 event for it.  If we don't compensate for this missed stdin event, key
	 sequences as Alt_F (^[f) will not behave promptly.

	 (We only compensates for the missed 2nd byte of a key sequence because
	 2-byte sequences are by far the most commonly used. ncurses may have
	 buffered a larger, 3+-byte key sequence though it remains to be seen
	 whether it is useful to compensate for all the bytes of such
	 sequences.)  */
      if (ch_pending != ERR)
	{
	  ungetch (ch_pending);
	  call_stdin_event_handler_again_p = 1;
	}
    }
#endif

  return ch;
}

/* Get a character from the command window.  This is called from the
   readline package.  */

static int
tui_getc (FILE *fp)
{
  try
    {
      return tui_getc_1 (fp);
    }
  catch (const gdb_exception &ex)
    {
      /* Just in case, don't ever let an exception escape to readline.
	 This shouldn't ever happen, but if it does, print the
	 exception instead of just crashing GDB.  */
      exception_print (gdb_stderr, ex);

      /* If we threw an exception, it's because we recognized the
	 character.  */
      return 0;
    }
}
