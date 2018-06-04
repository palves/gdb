/* XXXX GNU debugger GDB.

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
#include "cli/cli-option.h"
#include "cli/cli-utils.h"
#include "cli/cli-setshow.h"
#include "command.h"
#include <vector>

namespace gdb {
namespace option {

union option_value
{
  bool boolean;
  unsigned int uinteger;
  const char *enumeration;
};

struct option_def_and_value
{
  const option_def &option;
  option_value value;
};

struct parse_option_completion_info
{
  const char *word;
  completion_tracker &tracker;
};

/* If ARGS starts with "-", look for a "--" sequence.  If one is
   found, then interpret everything up until the "--" as getopt-style
   command line options.  Otherwise, interpret ARGS as an expression.
   We need this because otherwise e.g., the "-1" in "(gdb) print -1"
   would be interpreted as an option.  */

static const char *
find_end_options_marker (const char *args)
{
  bool have_options = false;
  if (args[0] == '-')
    {
      const char *p = args;

      p = skip_spaces (p);
      while (*p)
	{
	  if (check_for_argument (&p, "--"))
	    return p;
	  else
	    p = skip_to_space (p);
	  p = skip_spaces (p);
	}
    }

  return NULL;
}

static void complete_on_options (const option_def *options,
				 size_t options_size,
				 completion_tracker &tracker,
				 const char *text, const char *word);

static void
complete_on_all_options (const option_def *options, size_t options_size,
			 completion_tracker &tracker)
{
  static const char opt[] = "-";
  complete_on_options (options, options_size, tracker, opt + 1, opt);
}

static gdb::unique_xmalloc_ptr<char>
make_unique_xstrdup (const char *str)
{
  return gdb::unique_xmalloc_ptr<char> (xstrdup (str));
}

static gdb::optional<option_def_and_value>
parse_option (const option_def *options, size_t options_size,
	      bool have_marker,
	      const char **args,
	      parse_option_completion_info *completion = NULL)
{
  if (*args == NULL
      || **args != '-'
      || check_for_argument (args, "--"))
    return {};

  const char *arg_entry = *args;

  /* Skip the initial '-'.  */
  *args += 1;

  const char *arg = *args;
  const char *after = skip_to_space (arg);
  size_t len = after - arg;
  const option_def *match = NULL;
  for (size_t i = 0; i < options_size; i++)
    {
      const auto &o = options[i];

      if (strncmp (o.name, arg, len) == 0)
	{
	  if (match != NULL)
	    {
	      if (completion != NULL && arg[len] == '\0')
		{
		  complete_on_options (options, options_size,
				       completion->tracker,
				       arg, completion->word);
		  return {};
		}

	      error (_("Ambiguous option at: -%s"), arg);
	    }

	  match = &o;

	  if (isspace (arg[len]) || arg[len] == '\0')
	    break; /* Exact match.  */
	}
    }

  if (match == NULL)
    {
      if (!have_marker)
	return {};

      error (_("Unrecognized option at: -%s"), arg);
    }

  if (completion != NULL && arg[len] == '\0')
    {
      complete_on_options (options, options_size,
			   completion->tracker,
			   arg, completion->word);
      return {};
    }

  *args += len;
  *args = skip_spaces (*args);
  if (completion != NULL)
    completion->word = *args;


  
  switch (match->type)
    {
    case var_boolean:
      {
	const char *val_str = *args;
	int res;

	if (**args == '\0' && completion != NULL)
	  {
	    /* Complete on both "on/off" and more options.  */

	    complete_on_enum (completion->tracker,
			      boolean_enums, val_str, val_str);
	    complete_on_all_options (options, options_size,
				     completion->tracker);
	    return {};
	  }
	else if (**args == '-')
	  {
	    /* Treat:
	         "p -boolean-option -another-opt..."
	       as:
	         "p -boolean-option on -another-opt..."
	     */
	    res = 1;
	  }
	else if (**args == '\0')
	  {
	    /* Treat:
	         (1) "p -boolean-option "
	       as:
	         (1) "p -boolean-option on"
	     */
	    res = 1;
	  }
	else
	  {
	    res = parse_cli_boolean_value (args);
	    if (res < 0)
	      {
		const char *end = skip_to_space (*args);
		if (completion != NULL)
		  {
		    if (*end == '\0')
		      {
			complete_on_enum (completion->tracker,
					  boolean_enums, val_str, val_str);
			return {};
		      }
		  }

		error (_("Unrecognized option value for -%s: %.*s"),
		       match->name, (int) (end - val_str), val_str);
	      }
	    else if (completion != NULL && **args == '\0')
	      {
		/* While "cmd -boolean [TAB]" only offers "on" and
		   "off", the boolean option actually accepts "1",
		   "yes", etc. as boolean values.  We complete on
		   VAL_STR instead of BOOLEAN_ENUMS here to make these
		   work:

		    "p -object 1[TAB]" -> "p -object 1 "
		    "p -object yes[TAB]" -> "p -object yes "

		   Etc.  Most importantly, the space is auto-appended.

		   Otherwise, if we only completed on on/off here,
		   then it might look to the user like "1" isn't
		   valid, like:
		    "p -object 1[TAB]" -> "p -object 1" (i.e., nothing happens).
		*/
		completion->tracker.add_completion
		  (make_unique_xstrdup (val_str));
		return {};
	      }
	  }

	option_value val;
	val.boolean = res;
	return option_def_and_value {*match, val};
      }
    case var_uinteger:
      {
	if (completion != NULL)
	  {
	    if (**args == '\0')
	      {
		/* Convenience to let the user know what the option
		   can accept.  Note there's not common prefix between
		   the strings on purpose, so that readline doesn't do
		   a partial match.  */
		completion->tracker.add_completion
		  (make_unique_xstrdup ("NUMBER"));
		completion->tracker.add_completion
		  (make_unique_xstrdup ("unlimited"));
		return {};
	      }
	    else if (startswith ("unlimited", *args))
	      {
		completion->tracker.add_completion
		  (make_unique_xstrdup ("unlimited"));
		return {};
	      }
	  }

	option_value val;
	val.uinteger = parse_cli_var_uinteger (match->type, args);
	return option_def_and_value {*match, val};
      }
    case var_enum:
      {
	if (completion != NULL)
	  {
	    const char *after = skip_to_space (*args);
	    if (*after == '\0')
	      {
		complete_on_enum (completion->tracker,
				  match->enums, *args, *args);
		return {};
	      }
	  }

	if (check_for_argument (args, "--"))
	  {
	    /* Treat e.g., "backtrace -entry-values --" as if there
	       was no argument after "-entry-values".  This makes
	       parse_cli_var_enum throw an error with a suggestion of
	       what are the valid options.  */
	    args = NULL;
	  }

	option_value val;
	val.enumeration = parse_cli_var_enum (args, match->enums);
	return option_def_and_value {*match, val};
      }

    default:
      /* Not yet.  */
      gdb_assert (0);
    }

  return {};
}

static void
complete_on_options (const option_def *options, size_t options_size,
		     completion_tracker &tracker,
		     const char *text, const char *word)
{
  size_t textlen = strlen (text);
  for (size_t i = 0; i < options_size; i++)
    {
      const char *oname = options[i].name;
      if (strncmp (oname, text, textlen) == 0)
	tracker.add_completion (make_completion_match_str (oname, text, word));
    }
}

bool
complete_options (const option_def *options, size_t options_size,
		  completion_tracker &tracker,
		  const char *text, const char *word)
{
  const char *marker;
  if (text[0] == '-'
      && ((marker = find_end_options_marker (text)) == NULL
	  || *marker == '\0'))
    {
      tracker.set_use_custom_word_point (true);

      const char *args = text;

      parse_option_completion_info completion_info {NULL, tracker};

      while (1)
	{
	  args = skip_spaces (args);
	  completion_info.word = args;

	  if (strcmp (args, "-") == 0)
	    {
	      complete_on_options (options, options_size,
				   tracker, args + 1, completion_info.word);
	    }
	  else if (strcmp (args, "--") == 0)
	    {
	      tracker.add_completion
		(gdb::unique_xmalloc_ptr<char> (xstrdup (args)));
	    }
	  else if (args > text && *args == '\0' && isspace (args[-1]))
	    {
	      complete_on_all_options (options, options_size, tracker);
	    }
	  else
	    {
	      auto ov = parse_option (options, options_size,
				      true, &args, &completion_info);
	      if (!ov && !tracker.have_completions ())
		return true;
	    }

	  if (tracker.have_completions ())
	    {
	      tracker.advance_custom_word_point_by
		(completion_info.word - text);
	      return true;
	    }
	}
    }

  tracker.set_use_custom_word_point (false);
  return false;
}

void
process_options (const option_def *options, size_t options_size,
		 void *ctx, const char **args)
{
  if (*args == NULL)
    return;

  /* If ARGS starts with "-", look for a "--" sequence.  If one is
     found, then interpret everything up until the "--" as
     'gdb::option'-style command line options.  Otherwise, interpret
     ARGS as an expression.  We need this because otherwise e.g., the
     "-1" in "(gdb) print -1" would be interpreted as an option.  */
  bool have_marker = find_end_options_marker (*args) != NULL;

  while (1)
    {
      *args = skip_spaces (*args);

      auto ov = parse_option (options, options_size, have_marker,
			      args);
      if (!ov)
	break;

      switch (ov->option.type)
	{
	case var_boolean:
	  *ov->option.var_address.boolean (ov->option, ctx)
	    = ov->value.boolean;
	  break;
	case var_uinteger:
	  *ov->option.var_address.uinteger (ov->option, ctx)
	    = ov->value.uinteger;
	  break;
	case var_enum:
	  *ov->option.var_address.enumeration (ov->option, ctx)
	    = ov->value.enumeration;
	  break;
	default:
	  gdb_assert_not_reached ("unhandled option type");
	}
    }
}

static const char *
get_val_type_str (var_types type)
{
  switch (type)
    {
    case var_boolean:
      return "[on|off]";
    case var_uinteger:
      return "NUMBER | unlimited";
    default:
      return NULL;
    }
}

void
build_help (const option_def *options, size_t options_size,
	    std::string &help)
{
  for (size_t i = 0; i < options_size; i++)
    {
      const auto &o = options[i];
      if (o.set_doc == NULL)
	continue;

      help += "  -";
      help += o.name;

      const char *val_type_str = get_val_type_str (o.type);
      if (val_type_str != NULL)
	{
	  help += ' ';
	  help += val_type_str;
	}
      help += "\n    ";
      help += o.set_doc;
      help += '\n';
      if (o.help_doc != NULL)
	{
	  help += "    ";
	  help += o.help_doc;
	  help += '\n';
	}
      help += '\n';
    }
}

void
add_setshow_cmds_for_options (command_class cmd_class,
			      void *ctx,
			      const option_def *options, size_t options_size,
			      struct cmd_list_element **set_list,
			      struct cmd_list_element **show_list)
{
  for (size_t i = 0; i < options_size; i++)
    {
      const auto &option = options[i];

      if (option.type == var_boolean)
	{
	  add_setshow_boolean_cmd (option.name, cmd_class,
				   option.var_address.boolean (option, ctx),
				   option.set_doc, option.show_doc,
				   option.help_doc,
				   NULL, option.show_cmd_cb,
				   set_list, show_list);
	}
      else if (option.type == var_uinteger)
	{
	  add_setshow_uinteger_cmd (option.name, cmd_class,
				    option.var_address.uinteger (option, ctx),
				    option.set_doc, option.show_doc,
				    option.help_doc,
				    NULL, option.show_cmd_cb,
				    set_list, show_list);
	}
      else if (option.type == var_enum)
	{
	  add_setshow_enum_cmd (option.name, cmd_class,
				option.enums,
				option.var_address.enumeration (option, ctx),
				option.set_doc, option.show_doc,
				option.help_doc,
				NULL, option.show_cmd_cb,
				set_list, show_list);
	}
      else
	gdb_assert_not_reached (_("option type not handled"));
    }
}

} /* namespace option */
} /* namespace gdb */
