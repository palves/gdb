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
				 const char *text, const char *word,
				 completion_tracker &tracker);

static gdb::optional<option_def_and_value>
parse_option (const option_def *options, size_t options_size,
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
				       arg, completion->word,
				       completion->tracker);
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
    error (_("Unrecognized option at: -%s"), arg);

  if (completion != NULL && arg[len] == '\0')
    {
      complete_on_options (options, options_size,
			   arg, completion->word,
			   completion->tracker);
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

	if (**args == '-' || **args == '\0')
	  res = 1;
	else
	  {
	    res = parse_cli_boolean_value (args);
	    if (res < 0)
	      {
		if (completion != NULL)
		  {
		    *args = skip_to_space (*args);
		    if (**args == '\0')
		      {
			complete_on_enum (completion->tracker,
					  boolean_enums, val_str, val_str);
			return {};
		      }
		  }

		error (_("Unrecognized option value for -%s: %s"),
		       match->name, val_str);
	      }
	    else if (completion != NULL && **args == '\0')
	      {
		complete_on_enum (completion->tracker, boolean_enums,
				  val_str, val_str);
		return {};
	      }
	  }

	option_value val;
	val.boolean = res;
	return option_def_and_value {*match, val};
      }
    case var_uinteger:
      {
	option_value val;
	val.uinteger = parse_cli_var_uinteger (match->type, args);
	return option_def_and_value {*match, val};
      }
    case var_enum:
      {
	option_value val;

	if (completion != NULL)
	  {
	    const char *val_str = *args;
	    *args = skip_to_space (*args);
	    if (**args == '\0')
	      {
		complete_on_enum (completion->tracker,
				  match->enums, val_str, val_str);
		return {};
	      }
	  }

	if (check_for_argument (args, "--"))
	  args = NULL;
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
		     const char *text, const char *word,
		     completion_tracker &tracker)
{
  /* To keep it simple build the options enum array on demand.  We
     could get rid of this by inlining complete_on_enum here.  */
  std::vector<const char *> enum_options;

  for (size_t i = 0; i < options_size; i++)
    enum_options.push_back (options[i].name);

  /* This entry is for "--".  */
  enum_options.push_back ("-");

  /* complete_on_enum wants a NULL-terminated array.  */
  enum_options.push_back (NULL);
  complete_on_enum (tracker, enum_options.data (), text, word);
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

	  if (strcmp (args, "-") == 0 || strcmp (args, "--") == 0)
	    {
	      complete_on_options (options, options_size,
				   args + 1, completion_info.word,
				   tracker);
	    }
	  else if (args > text && *args == '\0' && isspace (args[-1]))
	    {
	      static const char opt[] = "-";
	      complete_on_options (options, options_size,
				   opt + 1, opt, tracker);
	    }
	  else
	    {
	      auto ov = parse_option (options, options_size,
				      &args, &completion_info);
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
  /* If ARGS starts with "-", look for a "--" sequence.  If one is
     found, then interpret everything up until the "--" as
     'gdb::option'-style command line options.  Otherwise, interpret
     ARGS as an expression.  We need this because otherwise e.g., the
     "-1" in "(gdb) print -1" would be interpreted as an option.  */
  if (*args == NULL || find_end_options_marker (*args) == NULL)
    return;

  while (1)
    {
      *args = skip_spaces (*args);

      auto ov = parse_option (options, options_size, args);
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
