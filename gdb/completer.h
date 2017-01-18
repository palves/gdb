/* Header for GDB line completion.
   Copyright (C) 2000-2017 Free Software Foundation, Inc.

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

#if !defined (COMPLETER_H)
#define COMPLETER_H 1

#include "gdb_vecs.h"
#include "command.h"

/* Types of functions in struct match_list_displayer.  */

struct match_list_displayer;

typedef void mld_crlf_ftype (const struct match_list_displayer *);
typedef void mld_putch_ftype (const struct match_list_displayer *, int);
typedef void mld_puts_ftype (const struct match_list_displayer *,
			     const char *);
typedef void mld_flush_ftype (const struct match_list_displayer *);
typedef void mld_erase_entire_line_ftype (const struct match_list_displayer *);
typedef void mld_beep_ftype (const struct match_list_displayer *);
typedef int mld_read_key_ftype (const struct match_list_displayer *);

/* Interface between CLI/TUI and gdb_match_list_displayer.  */

struct match_list_displayer
{
  /* The screen dimensions to work with when displaying matches.  */
  int height, width;

  /* Print cr,lf.  */
  mld_crlf_ftype *crlf;

  /* Not "putc" to avoid issues where it is a stdio macro.  Sigh.  */
  mld_putch_ftype *putch;

  /* Print a string.  */
  mld_puts_ftype *puts;

  /* Flush all accumulated output.  */
  mld_flush_ftype *flush;

  /* Erase the currently line on the terminal (but don't discard any text the
     user has entered, readline may shortly re-print it).  */
  mld_erase_entire_line_ftype *erase_entire_line;

  /* Ring the bell.  */
  mld_beep_ftype *beep;

  /* Read one key.  */
  mld_read_key_ftype *read_key;
};

using completion_list = std::vector<gdb::unique_xmalloc_ptr<char>>;

/* Object to track how many unique completions have been generated.
   Used to limit the size of generated completion lists.  */

/* Tracker for how many unique completions have been generated.  Used
   to terminate completion list generation early if the list has grown
   to a size so large as to be useless.  This helps avoid GDB seeming
   to lock up in the event the user requests to complete on something
   vague that necessitates the time consuming expansion of many symbol
   tables.  */

/* Create a new completion tracker.
   The result is a hash table to track added completions, or NULL
   if max_completions <= 0.  If max_completions < 0, tracking is disabled.
   If max_completions == 0, the max is indeed zero.  */

struct completion_tracker
{
  completion_tracker ();
  ~completion_tracker ();

  /* Add the completion NAME to the list of generated completions if
     it is not there already.  If too many completions were already
     found, this throws an error.  */
  void add_completion (gdb::unique_xmalloc_ptr<char> name,
		       const char *match_for_lcd = NULL);

  void add_completions (completion_list &&list);

  void advance_custom_word_point_by (size_t len);

  void set_quote_char (int quote_char)
  { m_quote_char = quote_char; }

  int quote_char () { return m_quote_char; }

  void set_use_custom_word_point (bool enable)
  { m_use_custom_word_point = enable; }

  bool use_custom_word_point () const
  { return m_use_custom_word_point; }

  int custom_word_point () const
  { return m_custom_word_point; }

  bool suppress_append_ws () const
  { return m_suppress_append_ws; }

  void set_suppress_append_ws (bool suppress)
  { m_suppress_append_ws = suppress; }

  void discard_completions ();

  completion_list m_entries_vec;

  /* XXXX: Do a final test for too many completions.  Individual
     completers may do some of this, but are not required to.
     Duplicates are also removed here.  Otherwise the user is left
     scratching his/her head: readline and complete_command will
     remove duplicates, and if removal of duplicates there brings the
     total under max_completions the user may think gdb quit searching
     too early.  */
  htab_t m_entries_hash;

  int m_quote_char = '\0';

  /* If true, the completer has its own idea of "word" point, and
     doesn't want to rely on readline computing it based on brkchars.
     Set in the handle_brkchars phase.  */
  bool m_use_custom_word_point = false;

  /* The completer's idea of where the "word" we were looking at is
     relative to RL_LINE_BUFFER.  This is advanced in the
     handle_brkchars phase as the completer discovers potential
     completable words.  */
  int m_custom_word_point = 0;

  bool m_suppress_append_ws = false;

  /* Our idea of lowest common denominator to hand over to readline.
     Some completers provide matches that don't start with the
     completion "word".  E.g., completing on "b push_ba" on a C++
     program usually completes to std::vector<...>::push_back,
     std::string::push_back etc.  If all matches start with "std::",
     then readline would figure out that the lowest common denominator
     is "std::", and thus would do a partial completion with that.
     I.e., it would replace "push_ba" in the input buffer with
     "std::", losing the original "push_ba", which is naturally
     undesirable.  Such completers pass the substring of the match
     that matters for common denominator computation as MATCH_FOR_LCD
     argument to add_completion.  The end result is passed to readline
     in gdb_rl_attempted_completion_function.  */
  char *m_lowest_common_denominator = NULL;

  /* If true, the LCD is unique.  I.e., all completions had the same
     MATCH_FOR_LCD substring, even if the completions were different.
     For example, if "break function<tab>" found "a::function()" and
     "b::function()", the LCD will be "function()" in both cases and
     so we want to tell readline to complete the line with
     "function()", instead of showing all the possible
     completions.  */
  bool m_lowest_common_denominator_unique = false;

private:
  completion_tracker (const completion_tracker &rhs) = delete;
  void operator= (const completion_tracker &rhs) = delete;

  /* Add the completion NAME to the list of generated completions if
     it is not there already.  If false is returned, too many
     completions were found.  */
  bool maybe_add_completion (gdb::unique_xmalloc_ptr<char> name,
			     const char *match_for_lcd);

  /* Given a new match, recompute the lowest common denominator (LCD)
     to hand over to readline.  Normally readline computes this itself
     based on all the whole set of matches.  However, some commands
     want to override readline, in order to be able to provide a LCD
     that is not really a prefix of the matches, but the lowest common
     denominator of some relevant substring of each match.  E.g., "b
     push_ba" completes to "std::vector<..>::push_back",
     "std::string::push_back", etc., and in this case we want the
     lowest common denominator to be "push_back" instead of
     "std::".  */
  void recompute_lowest_common_denominator (const char *new_match);
};

extern void gdb_display_match_list (char **matches, int len, int max,
				    const struct match_list_displayer *);

extern const char *get_max_completions_reached_message (void);

extern void complete_line (completion_tracker &tracker,
			   const char *text,
			   const char *line_buffer,
			   int point);

extern const char *completion_find_completion_word (completion_tracker &tracker,
						    const char *text,
						    int *quote_char);

/* The final result of a completion that is handed over to either
   readline or the completion command.  Mainly a wrapper for a
   readline-style match list array, though other bits of info are
   included too.  */

struct completion_result
{
  /* Create an empty result.  */
  completion_result ();

  /* Create a result.  */
  completion_result (char **match_list, size_t number_matches,
		     bool completion_suppress_append);

  /* Destroy a result.  */
  ~completion_result ();

  /* Move a result.  */
  completion_result (completion_result &&rhs);

  /* Release ownership of the match list array.  */
  char **release_match_list ();

private:
  /* Destroy the match list array and its contents.  */
  void reset_match_list ();

  /* Disable copying, since we don't need it.  */
  completion_result (const completion_result &rhs) = delete;
  void operator= (const completion_result &rhs) = delete;

public:
  /* The match list array, in the format that readline expects.
     match_list[0] contains the common prefix.  The real match list
     starts at index 1.  The list is NULL terminated.  If there's only
     one match, then match_list[1] is NULL.  If there are no matches,
     then this is NULL.  */
  char **match_list;
  /* The number of matched completions in MATCH_LIST.  Does not
     include the NULL terminator or the common prefix.  */
  size_t number_matches;

  /* Whether readline should suppress appending a whitespace, when
     there's only one possible completion.  */
  bool completion_suppress_append;
};

extern completion_result
  build_completion_result (completion_tracker &tracker,
			   const char *text, int start, int end);

const char *advance_to_expression_complete_word_point
  (completion_tracker &tracker, const char *text);

extern char **gdb_rl_attempted_completion_function (const char *text,
						    int start, int end);

/* Return true if we only have one completion, and it matches exactly
   the completion word.  I.e., completing results in what we already
   have.  */

extern bool completes_to_completion_word (completion_tracker &tracker,
					  const char *word);

extern void noop_completer (struct cmd_list_element *,
			    completion_tracker &tracker,
			    const char *, const char *);

extern void filename_completer (struct cmd_list_element *,
				completion_tracker &tracker,
				const char *, const char *);

extern void expression_completer (struct cmd_list_element *,
				  completion_tracker &tracker,
				  const char *, const char *);

extern void location_completer (struct cmd_list_element *,
				completion_tracker &tracker,
				const char *, const char *);

extern void symbol_completer (struct cmd_list_element *,
			      completion_tracker &tracker,
			      const char *, const char *);

extern void command_completer (struct cmd_list_element *,
			       completion_tracker &tracker,
			       const char *, const char *);

extern void signal_completer (struct cmd_list_element *,
			      completion_tracker &tracker,
			      const char *, const char *);

extern void reg_or_group_completer (struct cmd_list_element *,
				    completion_tracker &tracker,
				    const char *, const char *);

extern void reggroup_completer (struct cmd_list_element *,
				completion_tracker &tracker,
				const char *, const char *);

extern char *get_gdb_completer_quote_characters (void);

extern char *gdb_completion_word_break_characters (void);

/* Get the matching completer_handle_brkchars_ftype function for FN.
   FN is one of the core completer functions above (filename,
   location, symbol, etc.).  This function is useful for cases when
   the completer doesn't know the type of the completion until some
   calculation is done (e.g., for Python functions).  */

extern completer_handle_brkchars_ftype *
  completer_handle_brkchars_func_for_completer (completer_ftype *fn);

/* Exported to linespec.c */

extern completion_list complete_source_filenames (const char *text);

extern void complete_expression (completion_tracker &tracker,
				 const char *text, const char *word);

extern const char *skip_quoted_chars (const char *, const char *,
				      const char *);

extern const char *skip_quoted (const char *);

/* Maximum number of candidates to consider before the completer
   bails by throwing MAX_COMPLETIONS_REACHED_ERROR.  Negative values
   disable limiting.  */

extern int max_completions;


/* Wrapper to throw MAX_COMPLETIONS_REACHED_ERROR.  */ 

extern void throw_max_completions_reached_error (void);

#endif /* defined (COMPLETER_H) */
