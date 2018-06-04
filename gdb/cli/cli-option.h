/* xxxx, for GDB.

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

#ifndef CLI_OPTION_H
#define CLI_OPTION_H 1

#include "common/gdb_optional.h"
#include "common/array-view.h"
#include "completer.h"
#include <string>
#include "command.h"

namespace gdb {
namespace option {

/* An option definition.  The actual type of the option is stored in
   the TYPE field.  */
struct option_def
{
  /* The ctor is protected because you're supposed to construct using
     one of bool_option_def, etc. below.  */
protected:
  typedef void * (erased_var_address_ftype) ();

  // option_def () = default;
  constexpr option_def (const char *name_,
			var_types var_type_,
			erased_var_address_ftype *erased_var_address_,
			show_value_ftype *show_cmd_cb_,
			const char *set_doc_,
			const char *show_doc_,
			const char *help_doc_)
    : name (name_), type (var_type_),
      erased_var_address (erased_var_address_),
      var_address {},
      show_cmd_cb (show_cmd_cb_),
      set_doc (set_doc_), show_doc (show_doc_), help_doc (help_doc_)
  {}

public:
  const char *name;
  var_types type;

// private:
  /* Get the controlling variable's address.  Each type of variable
     uses a different union member.  We do this instead of having a
     single hook that return a "void*", for better type safety.  This
     way, actual instance of concrete option_def types
     (boolean_option_def, etc.) fail to compile if you pass in a
     function with incorrect return type.  CTX here is the aggregate
     object that groups the option variables from which the callback
     returns address of some member.  */
  erased_var_address_ftype *erased_var_address;

  union
    {
      int *(*boolean) (const option_def &, void *ctx);
      unsigned int *(*uinteger) (const option_def &, void *ctx);
      const char **(*enumeration) (const option_def &, void *ctx);
    }
  var_address;

  /* Pointer to NULL terminated list of enumerated values (like
     argv).  */
  const char *const *enums = NULL;

  bool have_argument = true;
public:
  /* The "show" callback to use in the associated command.  E.g.,
     "show print elements".  */
  show_value_ftype *show_cmd_cb;

  /* The set/show/help strings.  These are shown in both the help of
     commands that use the option group this option belongs to (e.g.,
     "help print"), and in the associated commands (e.g., "set/show
     print elements", "help set print elements").  */
  const char *set_doc;
  const char *show_doc;
  const char *help_doc;
};

namespace detail
{

template<typename RetType, typename Context>
static inline RetType *
get_var_address (const option_def &option, void *ctx)
{
  using unerased_ftype = RetType *(Context *);
  unerased_ftype *fun = (unerased_ftype *) option.erased_var_address;
  return fun ((Context *) ctx);
}

template<typename T>
static T *
return_self (T *self)
{
  return self;
}

} /* namespace detail */

/* A boolean command line option.  */
template<typename Context>
struct boolean_option_def : option_def
{
  boolean_option_def (const char *long_option_,
		      int *(*var_address_cb_) (Context *),
		      show_value_ftype *show_cmd_cb_,
		      const char *set_doc_,
		      const char *show_doc_,
		      const char *help_doc_)
    : option_def (long_option_, var_boolean,
		  (erased_var_address_ftype *) var_address_cb_,
		  show_cmd_cb_,
		  set_doc_, show_doc_, help_doc_)
  {
    var_address.boolean = detail::get_var_address<int, Context>;
  }
};

/* A boolean command line option.  */
template<typename Context>
struct switch_option_def : boolean_option_def<Context>
{
  switch_option_def (const char *long_option_,
		     int *(*var_address_cb_) (Context *),
		     const char *set_doc_,
		     const char *help_doc_ = NULL)
    : boolean_option_def<Context> (long_option_,
				   var_address_cb_,
				   NULL,
				   set_doc_, NULL, help_doc_)
  {
    this->have_argument = false;
  }

  switch_option_def (const char *long_option_,
		     const char *set_doc_,
		     const char *help_doc_ = NULL)
    : boolean_option_def<Context> (long_option_,
				   detail::return_self,
				   NULL,
				   set_doc_, NULL, help_doc_)
  {
    this->have_argument = false;
  }
};

template<typename Context>
struct uinteger_option_def : option_def
{
  uinteger_option_def (const char *long_option_,
		       unsigned int *(*var_address_cb_) (Context *),
		       show_value_ftype *show_cmd_cb_,
		       const char *set_doc_,
		       const char *show_doc_,
		       const char *help_doc_)
    : option_def (long_option_, var_uinteger,
		  (erased_var_address_ftype *) var_address_cb_,
		  show_cmd_cb_,
		  set_doc_, show_doc_, help_doc_)
  {
    var_address.uinteger = detail::get_var_address<unsigned int, Context>;
  }
};

/* An enum command line option.  */
template<typename Context>
struct enum_option_def : option_def
{
  enum_option_def (const char *long_option_,
		   const char *const *enumlist,
		   const char **(*var_address_cb_) (Context *),
		   show_value_ftype *show_cmd_cb_,
		   const char *set_doc_,
		   const char *show_doc_,
		   const char *help_doc_)
    : option_def (long_option_, var_enum,
		  (erased_var_address_ftype *) var_address_cb_,
		  show_cmd_cb_,
		  set_doc_, show_doc_, help_doc_)
  {
    var_address.enumeration = detail::get_var_address<const char *, Context>;
    this->enums = enumlist;
  }
};


struct option_def_group
{
  gdb::array_view<const option_def> options;
  void *ctx;
};

extern bool complete_options (gdb::array_view<const option_def> options,
			      completion_tracker &tracker,
			      const char *text, const char *word);

extern bool complete_options (gdb::array_view<const option_def_group> options_group,
			      completion_tracker &tracker,
			      const char *text, const char *word);

extern void build_help (gdb::array_view<const option_def> options,
			std::string &help);

extern void process_options (gdb::array_view<const option_def> options,
			     void *ctx, const char **args);

extern void process_options
  (gdb::array_view<const option_def_group> options_group,
   const char **args);

extern void add_setshow_cmds_for_options (command_class cmd_class, void *ctx,
					  gdb::array_view<const option_def> options,
					  struct cmd_list_element **set_list,
					  struct cmd_list_element **show_list);

} /* namespace option */
} /* namespace gdb */

#endif /* CLI_OPTION_H */
