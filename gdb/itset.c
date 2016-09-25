/* itset.c - Inferior/Thread sets.
   Copyright (C) 2010, 2011 Free Software Foundation, Inc.

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
#include "itset.h"
#include "vec.h"
#include "bfd.h"
#include "inferior.h"
#include "progspace.h"
#include <string.h>
#include "cli/cli-utils.h"
#include "gdbthread.h"
#include "command.h"
#include <ctype.h>
#include "gdbcmd.h"
#include "ada-lang.h"
#include "completer.h"
#include <vector>
#include <set>
#include <memory>

/* FIXME */
char itset_get_focus_object_type (itset *set);

/* Rather than creating/destroying these dynamic itsets when
   necessary, keep global copies around (itsets are refcounted).  */
static itset *all_itset;
static itset *empty_itset;
static itset *running_itset;
static itset *stopped_itset;
static itset *curinf_itset;
static itset *curthr_itset;
static itset *lockstep_itset;

/* Forward declaration of the base class.  */
struct itset_elt;

/* Forward declaration of the base class for object ranges.  */
struct itset_elt_range;

/* An element of an I/T set is a class with some virtual methods,
   defined here.  */

struct itset_elt
{
  /* Destroy the contents of this element.  */

  virtual ~itset_elt () {}

  /* Returns true if this is an itset_elt_range.  */

  virtual int is_range_type () { return 0; }

  /* Return true if the element contains the program space.  The
     element and the program space are passed as arguments.  */

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace)
  {
    return 0;
  }

  /* Return true if the element contains the inferior.  The element
     and the inferior are passed as arguments.  */

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width)
  {
    return 0;
  }

  /* Return true if the element contains the thread.  The element and
     the thread are passed as arguments.  */

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width)
  {
    return 0;
  }

  /* FIXME: some of these should be pure virtual? */

  /* Return true if the element is empty.  */

  virtual char *get_spec () { return NULL; };

  /* Return true if the element is empty.  */

  virtual enum itset_width get_width () { return ITSET_WIDTH_DEFAULT; }

  /* Return the element's TOI.  */

  virtual struct thread_info *get_toi () { return NULL; }

  /* Return true if the element's TOI is fixed.  */

  virtual int has_fixed_toi () { return 0; }

  /* Return the element's execution object type.  */

  virtual char get_focus_object_type () { return '\0'; }

  /* Return a clone of ELT.  */

  virtual struct itset_elt *clone () { return NULL; }
};

typedef std::vector<itset_elt *> itset_elt_vector;

static void set_free (const itset_elt_vector &elements);

class itset
{
public:
  itset ();
  ~itset ();

  void incref ()
  {
    ++this->m_refc;
  }

  void decref ()
  {
    if (--this->m_refc == 0)
      delete this;
  }

  /* The itset's name.  May be NULL.  */
  char *name;

  /* The original specification of the set.  */
  char *spec;

  /* The elements making up the set.  */
  itset_elt_vector elements;

private:
  /* The reference count.  */
  int m_refc;
};

itset::itset()
  : name (NULL), spec (NULL), m_refc (1)
{
}

itset::~itset()
{
  set_free (elements);
  xfree (name);
  xfree (spec);
}

const char *
itset_name (const itset *itset)
{
  return itset->name;
}

int
itset_is_empty_set (itset *set)
{
  return set->elements.empty ();
}



/* An element in the list of named itsets, which can be either
   debugger built-in (all, stopped, running, etc.), or user
   defined.  */

class named_itset
{
public:

  explicit named_itset (itset *wrapped_set)
    : next (NULL),
      number (0),
      set (wrapped_set)
  {}

  ~named_itset ()
  {
    itset_free (set);
  }

  /* Pointer to next in linked list.  XXX */
  named_itset *next;

  /* Unique identifier.  Positive if user defined, negative if
     internal and built-in.  */
  int number;

  /* The I/T set.  */
  itset *set;
};

/* The list of named I/T sets.  */

static std::vector<named_itset *> named_itsets;

/* Number of last named itset made.  */

static int named_itset_count;

/* Number of last internal named itset made.  */

static int internal_named_itset_count;

/* Traverse all named itsets.  */

#define ALL_NAMED_ITSETS_IT(it, set) \
  for (std::vector<struct named_itset *>::iterator it = named_itsets.begin (); \
       it != named_itsets.end ();					\
       ++it)								\
    if ((set = *it), true)

#define ALL_NAMED_ITSETS(set) \
  ALL_NAMED_ITSETS_IT(it, set)

/* Add IT at the end of the named itset chain.  */

static void
add_to_named_itset_chain (named_itset *it)
{
  /* Add this itset to the end of the vector so that a listing of
     itsets will come out in order of increasing numbers.  */
  named_itsets.push_back (it);
}

static named_itset *
get_named_itset (const char *name)
{
  for (std::vector<named_itset *>::iterator it = named_itsets.begin ();
       it != named_itsets.end ();
       ++it)
    if (strcmp ((*it)->set->name, name) == 0)
      return *it;
  return NULL;
}



/* A helper function that returns true if the inferior INF is
   contained by the set ELEMENTS.  */

static int
set_contains_program_space (const itset_elt_vector &elements,
			    enum itset_width default_width,
			    struct program_space *pspace)
{
  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;

      if (elt->contains_program_space (default_width, pspace))
	return 1;
    }

  return 0;
}

/* A helper function that returns true if the inferior INF is
   contained by the set ELEMENTS.  */

static int
set_contains_inferior (const itset_elt_vector &elements,
		       enum itset_width default_width,
		       struct inferior *inf,
		       int including_width)
{
  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;

      if (elt->contains_inferior (default_width,
				  inf, including_width))
	return 1;
    }

  return 0;
}

/* A helper function that returns true if the thread THR is contained
   by the set ELEMENTS.  */

static int
set_contains_thread (const itset_elt_vector &elements,
		     enum itset_width default_width,
		     struct thread_info *thr,
		     int including_width)
{
  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;

      if (elt->contains_thread (default_width, NULL, thr, including_width))
	return 1;
    }

  return 0;
}

/* A helper function to destroy all the elements in the set
   ELEMENTS.  */

static void
set_free (const itset_elt_vector &elements)
{
  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;

      delete elt;
    }
}



/* An I/T set element representing all inferiors using a certain
   executable.  */

struct itset_elt_exec : public itset_elt
{
  /* The name of the executable.  */
  char *exec_name;

  virtual ~itset_elt_exec();

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
};

/* Implementation of `destroy' method.  */

itset_elt_exec::~itset_elt_exec ()
{
  xfree (this->exec_name);
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_exec::contains_inferior (enum itset_width default_width,
				   struct inferior *inf,
				   int including_width)
{
  /* FIXME: smarter compare.  */
  return (inf->pspace->ebfd != NULL
	  && strcmp (this->exec_name,
		     bfd_get_filename (inf->pspace->ebfd)) == 0);
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_exec::contains_thread (enum itset_width default_width,
				 struct itset_elt_range *expanding,
				 struct thread_info *thr,
				 int including_width)
{
  struct inferior *inf = get_thread_inferior (thr);

  /* FIXME: smarter compare.  */
  return (inf->pspace->ebfd != NULL
	  && strcmp (this->exec_name,
		     bfd_get_filename (inf->pspace->ebfd)) == 0);
}

/* Create a new `exec' I/T set element.  */

static struct itset_elt *
create_exec_itset (char *arg)
{
  struct itset_elt_exec *elt;

  elt = new itset_elt_exec ();
  elt->exec_name = arg;

  return (struct itset_elt *) elt;
}



struct spec_range
{
  int first;
  int last;
};

/* The value representing any inferior or thread.  */

#define WILDCARD -1

struct itset_elt_range : public itset_elt
{
  char object_type;
  enum itset_width width;

  /* If WIDTH is explicit, this is the width set, otherwise NULL.  */
  itset *explicit_width;

  /* The selected group, otherwise NULL.  */
  struct itset_elt *group;

  int is_current;
  /* The first and last in this range.  If FIRST is WILDCARD, then
     LAST is unused.  */
  struct spec_range range;

  virtual ~itset_elt_range ();

  virtual int is_range_type ();

  virtual enum itset_width get_width ();

  virtual char get_focus_object_type ();

  char *range_get_spec (int range_type_char);
};

/* Compute range's effective width.  If the range's width is not
   default, use it. otherwise, use DEFAULT_WIDTH.  */

static enum itset_width
effective_width (enum itset_width width, enum itset_width default_width)
{
  gdb_assert (default_width != ITSET_WIDTH_DEFAULT);
  gdb_assert (default_width != ITSET_WIDTH_EXPLICIT);

  if (width == ITSET_WIDTH_DEFAULT)
    return default_width;
  return width;
}

itset_elt_range::~itset_elt_range ()
{
  itset_free (this->explicit_width);
}

int
itset_elt_range::is_range_type ()
{
  return 1;
}

enum itset_width
itset_elt_range::get_width ()
{
  return this->width;
}

char
itset_elt_range::get_focus_object_type ()
{
  return this->object_type;
}

static int
range_width_char (enum itset_width width)
{
  switch (width)
    {
    case ITSET_WIDTH_ALL:
      return 'a';
    case ITSET_WIDTH_EXPLICIT:
      return 'e';
    case ITSET_WIDTH_GROUP:
      return 'g';
    case ITSET_WIDTH_DEFAULT:
      return 'd';
    case ITSET_WIDTH_INFERIOR:
      return 'i';
    case ITSET_WIDTH_THREAD:
      return 't';
    case ITSET_WIDTH_ADA_TASK:
      return 'k';
    default:
      gdb_assert_not_reached ("unhandled width");
    }
}

static char *
concat_printf (char *spec, const char *string, ...)
{
  const char *res;
  va_list ap;

  va_start (ap, string);
  res = xstrvprintf (string, ap);
  va_end (ap);

  return reconcat (spec, spec == NULL ? "" : spec, res, NULL);
}

static char *
range_concat_spec (char *res, struct spec_range *range)
{
  if (range->first == WILDCARD && range->last == WILDCARD)
    res = concat_printf (res, "*");
  else if (range->first == INT_MIN)
    res = concat_printf (res, ":%d", range->last);
  else if (range->last == INT_MAX)
    res = concat_printf (res, "%d:", range->first);
  else if (range->first != range->last)
    res = concat_printf (res, "%d:%d", range->first, range->last);
  else
    res = concat_printf (res, "%d", range->first);

  return res;
}

/* FIXME: doesn't really need to be a method.  */
char *
itset_elt_range::range_get_spec (int range_type_char)
{
  struct spec_range *range = &this->range;
  int w;
  char *res = NULL;

  w = range_width_char (this->width);

  if (this->is_current)
    return xstrprintf ("%c%c", w, toupper (range_type_char));

  res = concat_printf (res, "%c%c", w, range_type_char);

  res = range_concat_spec (res, range);

  return res;
}

static char *itset_get_spec (const itset *set);

static char *
double_range_get_spec (struct itset_elt *base,
		       int range_type_char, bool print_range_type_char,
		       struct spec_range *inf_range)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct spec_range *range = &range_elt->range;
  int w;
  char *res = NULL;

  w = range_width_char (range_elt->width);

  if (range_elt->width == ITSET_WIDTH_EXPLICIT)
    {
      char *explicit_spec;

      explicit_spec = itset_get_spec (range_elt->explicit_width);
      res = concat_printf (res, "%c(%s)", w, explicit_spec);
    }
  else
    res = concat_printf (res, "%c", w);

  if (range_elt->group != NULL)
    {
      char *group_spec;

      group_spec = range_elt->group->get_spec ();
      res = concat_printf (res, "/%s/", group_spec);
      xfree (group_spec);
    }

  if (range_elt->is_current)
    return concat_printf (res, "%c", toupper (range_type_char));

  if (print_range_type_char)
    res = concat_printf (res, "%c", range_type_char);
  res = range_concat_spec (res, inf_range);
  res = concat_printf (res, ".");
  res = range_concat_spec (res, range);

  return res;
}

/* An I/T set element representing a range of inferiors.  */

struct itset_elt_inferior_range : public itset_elt_range
{
  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);
  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);
  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual struct thread_info *get_toi ();
  virtual int has_fixed_toi ();
};

static int
inferior_range_contains_program_space (struct spec_range *range,
				       struct program_space *pspace)
{
  struct inferior *inf;

  ALL_INFERIORS (inf)
    {
      if (range->first == WILDCARD
	  || (range->first <= inf->num && inf->num <= range->last))
	{
	  if (inf->pspace == pspace)
	    return 1;
	}
    }

  return 0;
}

/* Implementation of `contains_program_space' method.  */

int
itset_elt_inferior_range::contains_program_space (enum itset_width default_width,
						  struct program_space *pspace)
{
  enum itset_width width = effective_width (this->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  return inferior_range_contains_program_space (&this->range, pspace);
}

static int
inferior_range_contains_inferior (struct spec_range *range,
				  struct inferior *inf)
{
  if (range->first == WILDCARD
      || (range->first <= inf->num && inf->num <= range->last))
    return 1;

  return 0;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_inferior_range::contains_inferior (enum itset_width default_width,
					     struct inferior *inf,
					     int including_width)
{
  enum itset_width width = effective_width (this->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  return inferior_range_contains_inferior (&this->range, inf);
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_inferior_range::contains_thread (enum itset_width default_width,
					   struct itset_elt_range *expanding,
					   struct thread_info *thr,
					   int including_width)
{
  enum itset_width width = effective_width (this->width, default_width);
  struct inferior *inf;

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (this->range.first == WILDCARD)
    return 1;

  if (this->is_current)
    {
      inf = get_thread_inferior (thr);

      return (inf == get_current_context ()->inf);
    }

  inf = get_thread_inferior (thr);
  return inferior_range_contains_inferior (&this->range, inf);
}

char *
itset_elt_inferior_range::get_spec ()
{
  return this->range_get_spec ('i');
}

struct thread_info *
itset_elt_inferior_range::get_toi ()
{
  struct spec_range *range = &this->range;
  struct inferior *inf;

  if (this->is_current)
    return get_current_context_thread ();

  ALL_INFERIORS (inf)
    {
      if (range->first == WILDCARD
	  || (range->first <= inf->num && inf->num <= range->last))
	{
	  struct thread_info *thr;

	  ALL_NON_EXITED_THREADS (thr)
	    {
	      if (ptid_get_pid (thr->ptid) == inf->pid)
		return thr;
	    }
	}
    }

  return NULL;
}

int
itset_elt_inferior_range::has_fixed_toi ()
{
  return !this->is_current;
}

/* Create a new `range' I/T set element.  */

static struct itset_elt_range *
create_inferior_range_itset (enum itset_width width,
			     int is_current,
			     struct spec_range *inf_range)
{
  struct itset_elt_inferior_range *elt;
  struct itset_elt_range *range_elt;

  elt = new itset_elt_inferior_range ();

  elt->range = *inf_range;
  elt->width = width;
  elt->is_current = is_current;
  elt->object_type = 'i';

  return elt;
}



/* An I/T set element representing a range of threads.  */

struct itset_elt_thread_range : public itset_elt_range
{
  struct spec_range inf_range;

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  /* Return true if the element contains the inferior.  The element
     and the inferior are passed as arguments.  */

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  /* Return true if the element contains the thread.  The element and
     the thread are passed as arguments.  */

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);

  virtual char *get_spec ();
  virtual struct thread_info *get_toi ();
  virtual int has_fixed_toi ();

  virtual struct itset_elt *clone ();
};

 /* Implementation of `contains_inferior' method.  */

int
itset_elt_thread_range::contains_program_space (enum itset_width default_width,
						struct program_space *pspace)
{
  enum itset_width width = effective_width (this->width, default_width);
  struct inferior *inf;
  struct thread_info *thr;

  if (width == ITSET_WIDTH_ALL)
    return 1;

  if (width == ITSET_WIDTH_EXPLICIT)
    {
      itset *ew = this->explicit_width;

      if (itset_contains_program_space (ew, default_width, pspace))
	return 1;
    }

  if (width == ITSET_WIDTH_GROUP)
    {
      if (this->group->contains_program_space (default_width, pspace))
	return 1;
    }

  if (this->is_current)
    return (get_current_context ()->inf->pspace == pspace);

  return inferior_range_contains_program_space (&this->inf_range,
						pspace);
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_thread_range::contains_inferior (enum itset_width default_width,
					   struct inferior *inf,
					   int including_width)
{
  enum itset_width width = effective_width (this->width, default_width);

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (including_width && width == ITSET_WIDTH_EXPLICIT)
    {
      itset *ew = this->explicit_width;

      if (itset_width_contains_inferior (ew, default_width, inf))
	return 1;
    }

  if (including_width && width == ITSET_WIDTH_GROUP)
    {
      if (this->group->contains_inferior (default_width,
					  inf, including_width))
	return 1;
    }

  if (this->is_current)
    return (get_current_context ()->inf == inf);

  return inferior_range_contains_inferior (&this->inf_range, inf);
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_thread_range::contains_thread (enum itset_width default_width,
					 struct itset_elt_range *expanding,
					 struct thread_info *thr,
					 int including_width)
{
  struct spec_range *range = &this->range;
  enum itset_width width = effective_width (this->width, default_width);
  struct inferior *inf;

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (including_width && width == ITSET_WIDTH_EXPLICIT)
    {
      itset *ew = this->explicit_width;

      if (itset_contains_thread (ew, thr))
	return 1;
    }

  if (including_width && this->width == ITSET_WIDTH_GROUP)
    {
      if (this->group->contains_thread (default_width, NULL, thr, 0))
	return 1;
    }

  if (this->is_current)
    {
      struct inferior *inf = get_current_context ()->inf;

      this->inf_range.first = inf->num;
      this->inf_range.last = inf->num;
    }

  if (including_width && width == ITSET_WIDTH_INFERIOR)
    {
      inf = get_thread_inferior (thr);
      return inferior_range_contains_inferior (&this->inf_range, inf);
    }

  if (this->is_current)
    {
      struct thread_info *tp;

      tp = get_current_context_thread ();
      if (tp == NULL)
	return 0;

      range->first = tp->per_inf_num;
      range->last = tp->per_inf_num;
    }

  inf = get_thread_inferior (thr);
  if (inferior_range_contains_inferior (&this->inf_range, inf)
      && (range->first == WILDCARD
	  || (range->first <= thr->per_inf_num
	      && thr->per_inf_num <= range->last)))
    return 1;

  /* This range does not select this thread.  Check if the expander
     does though.  */
  if (/* FIXME: If the expander is calling us again, don't re-expand,
	 leading to infinite recursion.  Maybe we should have a
	 separate flag for this?  */
      expanding != this
      && this->group != NULL)
    {
      if ((including_width || this->contains_thread (default_width,
						     NULL, thr, 1))
	  && this->group->contains_thread (default_width, this, thr, 0))
	return 1;
    }

  return 0;
}

char *
itset_elt_thread_range::get_spec ()
{
  return double_range_get_spec (this, 't', false, &this->inf_range);
}

struct thread_info *
itset_elt_thread_range::get_toi ()
{
  struct spec_range *range = &this->range;
  struct thread_info *thr;

  if (this->is_current)
    return get_current_context_thread ();

  ALL_NON_EXITED_THREADS (thr)
    {
      if (range->first == WILDCARD
	  || (range->first <= thr->per_inf_num
	      && thr->per_inf_num <= range->last))
	{
	  struct inferior *inf;

	  inf = get_thread_inferior (thr);
	  if (inferior_range_contains_inferior (&this->inf_range, inf))
	    return thr;
	}
    }

  return NULL;
}

int
itset_elt_thread_range::has_fixed_toi ()
{
  return !this->is_current;
}

static struct itset_elt_range *
  create_thread_range_itset (enum itset_width width,
			     int is_current,
			     struct spec_range *inf_range,
			     struct spec_range *thr_range);

struct itset_elt *
itset_elt_thread_range::clone ()
{
  struct itset_elt_range *clone;

  clone = create_thread_range_itset (this->width,
				     this->is_current,
				     &this->inf_range,
				     &this->range);

  if (this->explicit_width != NULL)
    clone->explicit_width
      = itset_reference (this->explicit_width);
  else
    clone->explicit_width = NULL;

  /* FIXME */
  clone->group = NULL;

  return clone;
}


/* Create a new `range' I/T set element.  */

static struct itset_elt_range *
create_thread_range_itset (enum itset_width width, int is_current,
			   struct spec_range *inf_range,
			   struct spec_range *thr_range)
{
  struct itset_elt_thread_range *elt;

  elt = new itset_elt_thread_range ();
  elt->inf_range = *inf_range;

  elt->range = *thr_range;
  elt->width = width;
  elt->explicit_width = NULL;
  elt->group = NULL;
  elt->is_current = is_current;
  elt->object_type = 't';

  return elt;
}



/* An I/T set element representing a range of cores.  */

struct itset_elt_core_range : public itset_elt_range
{
  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual struct thread_info *get_toi ();

  virtual int has_fixed_toi ();
};

 /* Implementation of `contains_inferior' method.  */

int
itset_elt_core_range::contains_program_space (enum itset_width default_width,
					      struct program_space *pspace)
{
  struct thread_info *thr;

  /* True if we find a thread of an inferior associated with PSPACE
     that is running on our core range.  */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the core range first, because looking
	 up the a thread's inferior is O(n).  */
      if (contains_thread (default_width, NULL, thr, 1))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf->pspace == pspace)
	    return 1;
	}
    }

  return 0;
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_core_range::contains_thread (enum itset_width default_width,
				       struct itset_elt_range *expanding,
				       struct thread_info *thr,
				       int including_width)
{
  struct spec_range *range = &this->range;
  int core;

  if (range->first == WILDCARD)
    return 1;

  core = target_core_of_thread (thr->ptid);
  if (range->first <= core && core <= range->last)
    return 1;

  return 0;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_core_range::contains_inferior (enum itset_width default_width,
					 struct inferior *inf,
					 int including_width)
{
  struct thread_info *thr;

  /* True if we find a thread of this inferior that is running on our
     core range.  */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the core range first, because looking
	 up the a thread's inferior is O(n).  */
      if (contains_thread (default_width, NULL, thr, 1))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf == inf)
	    return 1;
	}
    }

  return 0;
}

char *
itset_elt_core_range::get_spec ()
{
  return range_get_spec ('c');
}

struct thread_info *
itset_elt_core_range::get_toi ()
{
  struct thread_info *thr;

  if (this->is_current)
    return get_current_context_thread ();

  ALL_NON_EXITED_THREADS (thr)
    {
      if (contains_thread (ITSET_WIDTH_THREAD, NULL, thr, 0))
	return thr;
    }

  return NULL;
}

int
itset_elt_core_range::has_fixed_toi ()
{
  return !this->is_current;
}

/* Create a new `core_range' I/T set element.  */

struct itset_elt_range *
create_core_range_itset (enum itset_width width, int is_current,
			 struct spec_range *core_range)
{
  struct itset_elt_core_range *elt;

  elt = new itset_elt_core_range ();

  elt->range = *core_range;
  elt->width = width;
  elt->is_current = is_current;
  elt->object_type = 'c';

  return elt;
}


/* An I/T set element representing a range of Ada tasks.  */

struct itset_elt_ada_task_range : public itset_elt_range
{
  struct spec_range inf_range;

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual struct thread_info *get_toi ();

  virtual int has_fixed_toi ();
};

 /* Implementation of `contains_program_space' method.  */

int
itset_elt_ada_task_range::contains_program_space (enum itset_width default_width,
						  struct program_space *pspace)
{
  enum itset_width width = effective_width (this->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  if (this->is_current)
    return (get_current_context ()->inf->pspace == pspace);

  return inferior_range_contains_program_space (&this->inf_range, pspace);
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_ada_task_range::contains_inferior (enum itset_width default_width,
					     struct inferior *inf,
					     int including_width)
{
  enum itset_width width = effective_width (this->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  if (this->is_current)
    return (get_current_context ()->inf == inf);

  return inferior_range_contains_inferior (&this->inf_range, inf);
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_ada_task_range::contains_thread (enum itset_width default_width,
					   struct itset_elt_range *expanding,
					   struct thread_info *thr,
					   int including_width)
{
  enum itset_width width = effective_width (this->width, default_width);
  struct spec_range *range = &this->range;
  struct inferior *inf;
  int thr_task;

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (this->is_current)
    {
      struct execution_context *ctx = get_current_context ();

      this->inf_range.first = ctx->inf->num;
      this->inf_range.last = ctx->inf->num;
    }

  if (including_width && width == ITSET_WIDTH_INFERIOR)
    {
      inf = get_thread_inferior (thr);
      return inferior_range_contains_inferior (&this->inf_range, inf);
    }

  if (this->is_current)
    {
      int task;

      if (ptid_equal (inferior_ptid, null_ptid))
	return 0;

      task = ada_get_task_number (inferior_ptid);
      if (task == 0)
	return 0;

      range->first = task;
      range->last = task;
    }

  inf = get_thread_inferior (thr);
  if (!inferior_range_contains_inferior (&this->inf_range, inf))
    return 0;

  if (range->first == WILDCARD)
    return 1;

  thr_task = ada_get_task_number (thr->ptid);
  if (thr_task != 0
      && range->first <= thr_task && thr_task <= range->last)
    return 1;

  return 0;
}

char *
itset_elt_ada_task_range::get_spec ()
{
  return double_range_get_spec (this, 'k', true, &this->inf_range);
}

struct thread_info *
itset_elt_ada_task_range::get_toi ()
{
  struct spec_range *range = &this->range;
  struct inferior *inf;

  if (this->is_current)
    return get_current_context_thread ();

  ALL_INFERIORS (inf)
    {
      struct ada_task_info *task_info;
      VEC(ada_task_info_s) *task_list;
      struct thread_info *thr;

      if (!inferior_range_contains_inferior (&this->inf_range, inf))
	continue;

      task_list = get_ada_tasks (inf, 0);

      if (range->first == WILDCARD)
	task_info = VEC_index (ada_task_info_s, task_list, 0);
      else if (range->first > VEC_length (ada_task_info_s, task_list))
	continue;
      else
	task_info = VEC_index (ada_task_info_s, task_list, range->first - 1);

      thr = find_thread_ptid (task_info->ptid);
      gdb_assert (thr != NULL);
      return thr;
    }

  return NULL;
}

int
itset_elt_ada_task_range::has_fixed_toi ()
{
  return !this->is_current;
}

/* Create a new `range' I/T set element.  */

static struct itset_elt_range *
create_ada_task_range_itset (enum itset_width width, int is_current,
			     struct spec_range *inf_range,
			     struct spec_range *ada_range)
{
  struct itset_elt_ada_task_range *elt;

  elt = new itset_elt_ada_task_range ();
  elt->inf_range = *inf_range;

  elt->range = *ada_range;
  elt->width = width;
  elt->is_current = is_current;
  elt->object_type = 'k';

  return elt;
}

static const char *parse_range (const char *spec, struct spec_range *range);
static int looks_like_range (const char *spec);

typedef struct itset_elt_range *(*create_double_range_itset_func)
  (enum itset_width, int, struct spec_range *, struct spec_range *);

static struct itset_elt_range *
parse_double_range_itset (const char **spec, enum itset_width width,
			  int range_type_char,
			  int default_type_char,
			  create_double_range_itset_func create_func)
{
  struct spec_range ranges[2];
  const char *save_spec = *spec;
  char *end;
  int first_num;

  if (!default_type_char)
    {
      if (**spec == toupper (range_type_char))
	{
	  (*spec)++;
	  return create_func (width, 1, &ranges[0], &ranges[1]);
	}

      if ((*spec)[0] != range_type_char)
	return NULL;

      (*spec)++;
    }
  else if (default_type_char != range_type_char)
    return NULL;

  if (!looks_like_range (*spec))
    return NULL;

  *spec = parse_range (*spec, &ranges[0]);

  if ((*spec)[0] == '.')
    {
      (*spec)++;
      *spec = parse_range (*spec, &ranges[1]);
    }
  else
    {
      ranges[1] = ranges[0];
      ranges[0].first = ranges[0].last = get_current_context ()->inf->num;
    }

  return create_func (width, 0, &ranges[0], &ranges[1]);
}



/* An I/T set element representing an intersection of sets.  */

struct itset_elt_intersect : public itset_elt
{
  /* The elements that will be intersected.  */
  itset_elt_vector elements;

  virtual ~itset_elt_intersect ();

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual struct thread_info *get_toi ();

  virtual int has_fixed_toi ();

  virtual enum itset_width get_width ();

  void add (itset_elt *elt)
  {
    elements.push_back (elt);
  }
};

/* Implementation of `destroy' method.  */

itset_elt_intersect::~itset_elt_intersect ()
{
}

/* Implementation of `contains_program_space' method.  */

int
itset_elt_intersect::contains_program_space (enum itset_width default_width,
					     struct program_space *pspace)
{
  gdb_assert (!this->elements.empty ());

  for (itset_elt_vector::const_iterator it = this->elements.begin ();
       it != this->elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;

      if (!elt->contains_program_space (default_width, pspace))
	return 0;
    }

  return 1;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_intersect::contains_inferior (enum itset_width default_width,
					struct inferior *inf,
					int including_width)
{
  gdb_assert (!this->elements.empty ());

  for (itset_elt_vector::const_iterator it = this->elements.begin ();
       it != this->elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;

      if (!elt->contains_inferior (default_width, inf, including_width))
	return 0;
    }

  return 1;
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_intersect::contains_thread (enum itset_width default_width,
				      struct itset_elt_range *expanding,
				      struct thread_info *thr,
				      int including_width)
{
  gdb_assert (!this->elements.empty ());

  for (itset_elt_vector::const_iterator it = this->elements.begin ();
       it != this->elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;

      if (!elt->contains_thread (default_width, expanding,
				 thr, including_width))
	return 0;
    }

  return 1;
}

char *
itset_elt_intersect::get_spec ()
{
  char *ret = NULL;

  gdb_assert (!this->elements.empty ());

  for (itset_elt_vector::const_iterator it = this->elements.begin ();
       it != this->elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;
      const char *elt_spec = elt->get_spec ();

      ret = reconcat (ret, ret == NULL ? "" : ret,
		      it == this->elements.begin () ? "" : "&",
		      elt_spec, (char *) NULL);
    }

  return ret;
}

static enum itset_width set_get_width (const itset_elt_vector &elements);
static struct thread_info *set_get_toi (const itset_elt_vector &elements);
static int set_has_fixed_toi (const itset_elt_vector &elements);

enum itset_width
itset_elt_intersect::get_width ()
{
  return set_get_width (this->elements);
}

struct thread_info *
itset_elt_intersect::get_toi ()
{
  return set_get_toi (this->elements);
}

int
itset_elt_intersect::has_fixed_toi ()
{
  return set_has_fixed_toi (this->elements);
}

/* Create a new `intersect' I/T set element.  */

static struct itset_elt_intersect *
create_intersect_itset (void)
{
  struct itset_elt_intersect *elt;

  elt = new itset_elt_intersect ();

  return elt;
}



/* An I/T set element representing all inferiors.  */

struct itset_elt_all : public itset_elt
{
  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual int has_fixed_toi ();

  virtual enum itset_width get_width ();
};

/* Implementation of `contains_inferior' method.  */

int
itset_elt_all::contains_program_space (enum itset_width default_width,
				       struct program_space *pspace)
{
  return 1;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_all::contains_inferior (enum itset_width default_width,
				  struct inferior *inf,
				  int including_width)
{
  return 1;
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_all::contains_thread (enum itset_width default_width,
				struct itset_elt_range *expanding,
				struct thread_info *thr,
				int including_width)
{
  return 1;
}

char *
itset_elt_all::get_spec ()
{
  return xstrdup ("all");
}

enum itset_width
itset_elt_all::get_width ()
{
  return ITSET_WIDTH_ALL;
}

int
itset_elt_all::has_fixed_toi ()
{
  return 0;
}

static struct itset_elt *
create_all_itset (void)
{
  struct itset_elt_all *elt;

  elt = new itset_elt_all ();

  return elt;
}



/* An I/T set element representing no inferiors.  */

struct itset_elt_empty : public itset_elt
{
  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
};

/* Implementation of `contains_program_space' method.  */

int
itset_elt_empty::contains_program_space (enum itset_width default_width,
					 struct program_space *pspace)
{
  return 0;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_empty::contains_inferior (enum itset_width default_width,
				    struct inferior *inf,
				    int including_width)
{
  return 0;
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_empty::contains_thread (enum itset_width default_width,
				  struct itset_elt_range *expanding,
				  struct thread_info *thr,
				  int including_width)
{
  return 0;
}

static struct itset_elt *
create_empty_itset (void)
{
  struct itset_elt_empty *elt;

  elt = new itset_elt_empty ();

  return elt;
}



/* An I/T set element representing an itset.  */

struct itset_elt_itset : public itset_elt
{
  /* The I/T set this element wraps.  */
  itset *set;

  virtual ~itset_elt_itset ();

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual struct thread_info *get_toi ();

  virtual int has_fixed_toi ();

  virtual enum itset_width get_width ();
};

itset_elt_itset::~itset_elt_itset ()
{
  itset_free (this->set);
}

/* Implementation of `contains_program_space' method.  */

int
itset_elt_itset::contains_program_space (enum itset_width default_width,
					 struct program_space *pspace)
{
  return itset_contains_program_space (this->set, default_width, pspace);
}

static int
itset_contains_inferior_1 (itset *set,
			   enum itset_width default_width,
			   struct inferior *inf,
			   int including_width);

/* Implementation of `contains_inferior' method.  */

int
itset_elt_itset::contains_inferior (enum itset_width default_width,
				    struct inferior *inf,
				    int including_width)
{
  return itset_contains_inferior_1 (this->set, default_width,
				    inf, including_width);
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_itset::contains_thread (enum itset_width default_width,
				  struct itset_elt_range *expanding,
				  struct thread_info *thr,
				  int including_width)
{
  if (including_width)
    return itset_width_contains_thread (this->set, default_width,
					thr);
  else
    return itset_contains_thread (this->set, thr);
}

char *
itset_elt_itset::get_spec ()
{
  if (this->set->name != NULL)
    return xstrdup (this->set->name);

  return itset_get_spec (this->set);
}

enum itset_width
itset_elt_itset::get_width ()
{
  return itset_get_width (this->set);
}

struct thread_info *
itset_elt_itset::get_toi ()
{
  return itset_get_toi (this->set);
}

int
itset_elt_itset::has_fixed_toi ()
{
  return itset_has_fixed_toi (this->set);
}

static struct itset_elt_itset *
create_itset_elt_itset (itset *set)
{
  struct itset_elt_itset *elt;

  elt = new itset_elt_itset ();
  elt->set = itset_reference (set);

  return elt;
}

void
itset_add_set (itset *to, itset *addme)
{
  struct itset_elt *elt;

  elt = (struct itset_elt *) create_itset_elt_itset (addme);
  to->elements.push_back (elt);
}



/* An I/T set element representing a negated set.  */

struct itset_elt_negated : public itset_elt
{
  /* The negated element.  */
  struct itset_elt *negated;

  virtual ~itset_elt_negated ();

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual struct thread_info *get_toi ();

  virtual int has_fixed_toi ();

  virtual enum itset_width get_width ();
};

itset_elt_negated::~itset_elt_negated ()
{
  delete this->negated;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_negated::contains_program_space (enum itset_width default_width,
					   struct program_space *pspace)
{
  if (!this->negated->contains_program_space (default_width, pspace))
    return 0;

  /* See comment in contains_inferior below.  */
  return this->negated->contains_program_space (default_width, pspace);
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_negated::contains_inferior (enum itset_width default_width,
				      struct inferior *inf,
				      int including_width)
{
  if (including_width
      && !this->negated->contains_inferior (default_width, inf, 1))
    return 0;

  /* Hmm.  This doesn't actually negate on purpose.  Otherwise, what
     would:

       "itfocus ~at1.1 b main"

     mean?  But this looks odd.  FIXME.  Maybe we should think of a
     better design.  */
  return this->negated->contains_inferior (default_width, inf, 0);
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_negated::contains_thread (enum itset_width default_width,
				    struct itset_elt_range *expanding,
				    struct thread_info *thr,
				    int including_width)
{
  if (including_width && !this->negated->contains_thread (default_width,
							  NULL, thr, 1))
    return 0;

  return !this->negated->contains_thread (default_width, NULL, thr, 0);
}

char *
itset_elt_negated::get_spec ()
{
  return xstrprintf ("~%s", this->negated->get_spec ());
}

enum itset_width
itset_elt_negated::get_width ()
{
  return this->negated->get_width ();
}

struct thread_info *
itset_elt_negated::get_toi ()
{
  struct thread_info *thr;

  ALL_THREADS (thr)
    {
      if (contains_thread (ITSET_WIDTH_THREAD, NULL, thr, 0))
	return thr;
    }
  return NULL;
}

int
itset_elt_negated::has_fixed_toi ()
{
  return 0;
}

static struct itset_elt_negated *
create_itset_elt_negated (void)
{
  struct itset_elt_negated *elt;

  elt = new itset_elt_negated ();
  elt->negated = NULL;

  return elt;
}



/* An I/T set element representing all inferiors of a given state.  */

struct itset_elt_state : public itset_elt
{
  enum thread_state state;

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();

  virtual enum itset_width get_width ();
};

/* Implementation of `contains_thread' method.  */

int
itset_elt_state::contains_thread (enum itset_width default_width,
				  struct itset_elt_range *expanding,
				  struct thread_info *thr,
				  int including_width)
{
  return thr->state == this->state;
}

 /* Implementation of `contains_program_space' method.  */

int
itset_elt_state::contains_program_space (enum itset_width default_width,
					 struct program_space *pspace)
{
  struct thread_info *thr;
  /* FIXME: does this method need to take this as parameter?  */
  int including_width = 1;

  /* True if we find a thread that is in the state we're interested in
     of an inferior that is bound to PSPACE */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the state first, because looking up the
	 a thread's inferior is O(n).  */
      if (contains_thread (default_width, NULL, thr, including_width))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf->pspace == pspace)
	    return 1;
	}
    }

  return 0;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_state::contains_inferior (enum itset_width default_width,
				    struct inferior *inf,
				    int including_width)
{
  struct thread_info *thr;

  /* True if we find a thread of this inferior that is in the state
     we're interested in.  */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the state first, because looking up the
	 a thread's inferior is O(n).  */
      if (contains_thread (default_width, NULL, thr, 1))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf == inf)
	    return 1;
	}
    }

  return 0;
}

char *
itset_elt_state::get_spec ()
{
  switch (this->state)
    {
    case THREAD_RUNNING:
      return xstrdup ("running");
    case THREAD_STOPPED:
      return xstrdup ("stopped");
    }

  gdb_assert_not_reached ("unhandled state");
}

enum itset_width
itset_elt_state::get_width ()
{
  return ITSET_WIDTH_DEFAULT;
}

static struct itset_elt *
create_state_itset (enum thread_state thread_state)
{
  struct itset_elt_state *elt;

  elt = new itset_elt_state ();
  elt->state = thread_state;

  return elt;
}



struct curinf_itset_elt : public itset_elt
{
  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();
};

/* Implementation of `contains_program_space' method.  */

int
curinf_itset_elt::contains_program_space (enum itset_width default_width,
					  struct program_space *pspace)
{
  return current_inferior ()->pspace == pspace;
}

/* Implementation of `contains_inferior' method.  */

int
curinf_itset_elt::contains_inferior (enum itset_width default_width,
				     struct inferior *inf,
				     int including_width)
{
  return current_inferior () == inf;
}

/* Implementation of `contains_thread' method.  */

int
curinf_itset_elt::contains_thread (enum itset_width default_width,
				   struct itset_elt_range *expanding,
				   struct thread_info *thr,
				   int including_width)
{
  struct inferior *inf;

  inf = get_thread_inferior (thr);
  return current_inferior () == inf;
}

char *
curinf_itset_elt::get_spec ()
{
  return xstrdup ("current");
}

/* Create a new I/T set element representing just the current
   inferior.  */

static struct itset_elt *
create_curinf_itset (void)
{
  struct curinf_itset_elt *elt;

  elt = new curinf_itset_elt ();

  return elt;
}



struct curthr_itset_elt : public itset_elt
{
  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
};

/* Implementation of `contains_program_space' method.  */

int
curthr_itset_elt::contains_program_space (enum itset_width default_width,
					  struct program_space *pspace)
{
  return current_inferior ()->pspace == pspace;
}

/* Implementation of `contains_inferior' method.  */

int
curthr_itset_elt::contains_inferior (enum itset_width default_width,
				     struct inferior *inf,
				     int including_width)
{
  return current_inferior () == inf;
}

/* Implementation of `contains_thread' method.  */

int
curthr_itset_elt::contains_thread (enum itset_width default_width,
				   struct itset_elt_range *expanding,
				   struct thread_info *thr,
				   int including_width)
{
  return ptid_equal (inferior_ptid, thr->ptid);
}

/* Create a new I/T set element representing just the current
   inferior.  */

static struct itset_elt *
create_curthr_itset (void)
{
  struct curthr_itset_elt *elt;

  elt = new curthr_itset_elt ();

  return elt;
}



struct lockstep_itset_elt : public itset_elt
{
  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
  virtual char *get_spec ();
};


/* Implementation of `contains_program_space' method.  */

int
lockstep_itset_elt::contains_program_space (enum itset_width default_width,
					    struct program_space *pspace)
{
  return current_inferior ()->pspace == pspace;
}

/* Implementation of `contains_inferior' method.  */

int
lockstep_itset_elt::contains_inferior (enum itset_width default_width,
				       struct inferior *inf,
				       int including_width)
{
  return current_inferior () == inf;
}

/* Implementation of `contains_thread' method.  */

int
lockstep_itset_elt::contains_thread (enum itset_width default_width,
				     struct itset_elt_range *expanding,
				     struct thread_info *thr, int including_width)
{
  struct thread_info *iter;
  CORE_ADDR pc;

  gdb_assert (expanding != NULL);

  if (thr->state == THREAD_RUNNING)
    {
      pc = thr->reported_stop_pc;
    }
  else
    {
      struct regcache *regcache;

      regcache = get_thread_regcache (thr->ptid);
      pc = regcache_read_pc (regcache);
    }

  ALL_THREADS (iter)
    {
      if (expanding->contains_thread (default_width, expanding, iter, 0))
	{
	  CORE_ADDR iter_pc;

	  if (iter->state == THREAD_RUNNING)
	    {
	      iter_pc = iter->reported_stop_pc;
	    }
	  else
	    {
	      struct regcache *iter_regcache = get_thread_regcache (iter->ptid);
	      iter_pc = regcache_read_pc (iter_regcache);
	    }

	  if (iter_pc == pc)
	    return 1;
	}
    }

  return 0;
}

char *
lockstep_itset_elt::get_spec ()
{
  return xstrdup ("L");
}

/* Create a new I/T set element representing just the current
   inferior.  */

static struct itset_elt *
create_lockstep_itset (void)
{
  struct lockstep_itset_elt *elt;

  elt = new lockstep_itset_elt ();

  return elt;
}



/* An I/T set element representing a static list of inferiors.  */

struct itset_elt_static : public itset_elt
{
  /* The inferiors.  */
  std::set<int> inferiors;

  /* The threads.  */
  std::set<int> threads;

  virtual int contains_program_space (enum itset_width default_width,
				      struct program_space *pspace);

  virtual int contains_inferior (enum itset_width default_width,
				 struct inferior *inf,
				 int including_width);

  virtual int contains_thread (enum itset_width default_width,
			       struct itset_elt_range *expanding,
			       struct thread_info *thr,
			       int include_width);
};

/* Implementation of `contains_inferior' method.  */

int
itset_elt_static::contains_program_space (enum itset_width default_width,
					  struct program_space *pspace)
{
  for (std::set<int>::const_iterator it = this->inferiors.begin ();
       it != this->inferiors.end ();
       ++it)
    {
      struct inferior *inf = find_inferior_id (*it);

      if (inf->pspace == pspace)
	return 1;
    }

  return 0;
}

/* Implementation of `contains_inferior' method.  */

int
itset_elt_static::contains_inferior (enum itset_width default_width,
				     struct inferior *inf,
				     int including_width)
{
  return this->inferiors.find (inf->num) != this->inferiors.end ();
}

/* Implementation of `contains_thread' method.  */

int
itset_elt_static::contains_thread (enum itset_width default_width,
				   struct itset_elt_range *expanding,
				   struct thread_info *thr,
				   int including_width)
{
  return this->threads.find (thr->global_num) != this->threads.end ();
}



/* Create a new static I/T set from the list of elements.  */

static struct itset_elt *
create_static_itset (enum itset_width default_width,
		     const itset_elt_vector &elements)
{
  struct inferior *inf;
  struct thread_info *thr;
  struct itset_elt_static *elt = new itset_elt_static ();

  ALL_INFERIORS (inf)
    {
      if (set_contains_inferior (elements, default_width, inf, 1))
	elt->inferiors.insert (inf->num);
    }

  ALL_NON_EXITED_THREADS (thr)
    {
      if (set_contains_thread (elements, default_width, thr, 1))
	elt->threads.insert (thr->global_num);
    }

  return elt;
}



static int
looks_like_range (const char *spec)
{
  return isdigit (spec[0]) || spec[0] == '*' || spec[0] == ':';
}

/* Parse an I/T set range.  A range has the form F[:L][.T], where F is
   the starting inferior, L is the ending inferior, and T is the
   thread.  Updates RESULT with the new I/T set elements, and returns
   an updated pointer into the spec.  Throws an exception on
   error.  */

static const char *
parse_range (const char *spec, struct spec_range *range)
{
  struct itset_elt *elt;

  if (!looks_like_range (spec))
    error (_("Invalid I/T syntax at `%s'.  Expected '*', ':' or digit."),
	   spec);

  /*
      | *   | all                 |
      | :   | all                 |
      | 1:3 | 1 to 3              |
      | 1:  | 1 till end          |
      | :3  | 0 till 3            |
      | 3:2 | empty               |
  */

  if (spec[0] == '*'
      || (spec[0] == ':'
	  && (spec[1] == '\0' || isspace (spec[1]))))
    {
      range->first = WILDCARD;
      range->last = WILDCARD;
      ++spec;
    }
  else
    {
      char *end;

      if (spec[0] == ':')
	range->first = INT_MIN;
      else
	{
	  range->first = strtol (spec, &end, 10);
	  spec = end;
	}

      if (*spec == ':')
	{
	  ++spec;
	  if (isdigit (*spec))
	    {
	      range->last = strtol (spec, &end, 10);
	      spec = end;
	    }
	  else
	    range->last = INT_MAX;
	}
      else
	range->last = range->first;
    }
  return spec;
}

typedef struct itset_elt_range *(*create_range_itset_func)
  (enum itset_width, int, struct spec_range *range);

static struct itset_elt_range *
parse_range_itset (const char **spec, enum itset_width width,
		   int range_type_char, int default_type_char,
		   create_range_itset_func create_func)
{
  struct spec_range range = {0};

  if (!default_type_char)
    {
      if (**spec == toupper (range_type_char))
	{
	  (*spec)++;
	  return create_func (width, range_type_char, &range);
	}

      if ((*spec)[0] != range_type_char || !looks_like_range ((*spec) + 1))
	return NULL;

      (*spec)++;
    }
  else if (default_type_char != range_type_char)
    return NULL;

  *spec = parse_range (*spec, &range);
  return create_func (width, 0, &range);
}

static bool
parse_width (const char **spec, enum itset_width *width)
{
  const char *width_str = *spec;

  if (width_str[0] == 'e' && width_str[1] == '(')
    {
      /* Leave the '(' in place, to be consumed by the caller.  */
      (*spec)++;
      *width = ITSET_WIDTH_EXPLICIT;
      return true;
    }

  switch (width_str[0])
    {
    case 'a':
      *width = ITSET_WIDTH_ALL;
      break;
    case 'g':
      *width = ITSET_WIDTH_GROUP;
      break;
    case 'i':
      *width = ITSET_WIDTH_INFERIOR;
      break;
    case 't':
      *width = ITSET_WIDTH_THREAD;
      break;
    case 'k':
      *width = ITSET_WIDTH_ADA_TASK;
      break;
    case 'd':
      *width = ITSET_WIDTH_DEFAULT;
      break;
    default:
      return false;
    }

  (*spec)++;
  return true;
}



static int
is_internal_set (const char **text, const char *pattern)
{
  if (startswith (*text, pattern))
    {
      *text += strlen (pattern);
      return 1;
    }
  return 0;
}

/* Parse a named I/T set.  Return an I/T set element, and advances the
   in/out parameter past the named set.  Throws an exception on
   error.  */

static struct itset_elt *
parse_named_or_throw (const char **textp)
{
  struct itset_elt *elt;
  const char *text = *textp;
  const char *name = text;

  if (is_internal_set (&text, "all"))
    elt = create_all_itset ();
  else if (is_internal_set (&text, "empty"))
    elt = create_empty_itset ();
  else if (is_internal_set (&text, "stopped"))
    elt = create_state_itset (THREAD_STOPPED);
  else if (is_internal_set (&text, "running"))
    elt = create_state_itset (THREAD_RUNNING);
  else if (is_internal_set (&text, "I"))
    elt = create_curinf_itset ();
  else if (is_internal_set (&text, "T"))
    elt = create_curthr_itset ();
  else if (is_internal_set (&text, "L"))
    elt = create_lockstep_itset ();
  else if (is_internal_set (&text, "exec"))
    {
      const char *tem;
      char *arg;

      if (*text != '(')
	error (_("'(' expected in I/T set after `exec'"));
      text = skip_spaces_const (text + 1);
      tem = strchr (text, ')');
      if (!tem)
	error (_("No closing ')' in I/T set for `exec'"));
      if (tem - text == 0)
	error (_("Empty argument to `exec' in I/T set"));
      arg = xstrndup (text, tem - text);
      text = tem + 1;
      elt = create_exec_itset (arg);
    }
  else
    {
      struct named_itset *named_itset;
      char *tem;

      for (text = name; isalnum (*text) || *text == '_'; ++text)
	;

      if (text == name)
	error (_("Doesn't look like a valid spec."));

      tem = (char *) alloca (text - name + 1);

      memcpy (tem, name, text - name);
      tem[text - name] = '\0';

      named_itset = get_named_itset (tem);
      if (named_itset == NULL)
	error (_("Unknown named I/T set: `%s'"), tem);
      struct itset_elt *itset_elt = create_itset_elt_itset (named_itset->set);
      elt = (struct itset_elt *) create_itset_elt_itset (named_itset->set);
    }

  *textp = text;
  return elt;
}

/* A cleanup function that calls itset_free.  */

static void
itset_free_cleanup (void *arg)
{
  itset *set = (itset *) arg;

  itset_free (set);
}

struct cleanup *
make_cleanup_itset_free (itset *itset)
{
  return make_cleanup (itset_free_cleanup, itset);
}

/* Itset expressions:

  ',' (union) has precedence over '&' (intersect).

  ITSET = | ('!' ITSET_ONE) | ITSET_ONE
  ITSET_ONE = INTERS ('&' INTERS)*
  INTERS = ELEM ('&' ELEM)*
  ELEM = RANGE | NEG | PARENS_SET | '$' | NAME
  PARENS_SET = '(' ITSET_ONE ')'
  NEG = '~' ELEM

  E.g.,:

  c1-3&~i1&(t1,other),foo is transformed to a tree like:

   UNION
     INTERS
       c1-3
       NEG
         i1-1
       UNION
         t1-1
	 other
     foo

*/

/* An itset parser's state.  */

struct itset_parser
{
  int parens_level;
  const char *spec;

  /* The default width.  */
  enum itset_width default_width;
};

/* Skip spaces if parenthesis level is > 0.  That is, spaces are only
   allowed with parens:

     itfocus (t2 t3 & c0) print 1
        spec -----------/ \------ command

   but not without:

     itfocus t2 t3 & c0 print 1
        spec -/ \-------------- command

     itfocus t2,t3&c0 print 1
        spec -------/ \------ command
*/

static void
maybe_skip_spaces (struct itset_parser *self)
{
  if (self->parens_level > 0)
    self->spec = skip_spaces_const (self->spec);
}

/* Forward declare.  The parser is recursive.  */
static struct itset_elt *parse_neg (struct itset_parser *self);
static struct itset_elt *parse_parens_set (struct itset_parser *self);
static struct itset_elt *parse_itset_one (struct itset_parser *self);
static struct itset_elt *parse_current_focus (struct itset_parser *self);

static int
valid_spec_end (const char *spec)
{
  return *spec == '\0' || isspace (*spec);
}

static struct itset_elt_range *
parse_range_elem_1 (struct itset_parser *self, enum itset_width width,
		    int default_object_type)
{
  struct itset_elt_range *elt;

  elt = parse_range_itset (&self->spec, width, 'i',
			   default_object_type,
			   create_inferior_range_itset);
  if (elt != NULL)
    return elt;

  elt = parse_range_itset (&self->spec, width, 'c',
			   default_object_type,
			   create_core_range_itset);
  if (elt != NULL)
    return elt;

  elt = parse_double_range_itset (&self->spec, width, 't',
				  default_object_type,
				  create_thread_range_itset);
  if (elt != NULL)
    return elt;

  elt = parse_double_range_itset (&self->spec, width, 'k',
				  default_object_type,
				  create_ada_task_range_itset);
  if (elt != NULL)
    return elt;

  return NULL;
}

static struct itset_elt_range *
parse_range_elem (struct itset_parser *self, enum itset_width width)
{
  struct itset_elt_range *elt;
  int object_type;

  elt = parse_range_elem_1 (self, width, 0);
  if (elt != NULL)
    return elt;

#if 0
  object_type = itset_get_focus_object_type (current_itset);
#else
  object_type = 't';
#endif

  elt = parse_range_elem_1 (self, width, object_type);
  if (elt != NULL)
    return elt;

  return NULL;
}

static itset *
  itset_create_const_1 (const char **specp, enum itset_width default_width);

static struct itset_elt_range *
itset_get_range_elt_if_simple (itset *itset)
{
  if (itset->elements.size () == 1)
    {
      struct itset_elt *elt;

      elt = current_itset->elements[0];
      if (elt->is_range_type ())
	return (struct itset_elt_range *) elt;
    }

  return NULL;
}

static struct itset_elt *
parse_elem_1 (struct itset_parser *self)
{
  struct itset_elt_range *elt_range;
  enum itset_width width;
  const char *save_spec = self->spec;
  struct itset_elt *group = NULL;
  itset *explicit_width = NULL;

  maybe_skip_spaces (self);

  if (parse_width (&self->spec, &width))
    {
      if (width == ITSET_WIDTH_DEFAULT)
	width = self->default_width;
      else if (width == ITSET_WIDTH_EXPLICIT)
	{
	  /* FIXME: leak on error.  */
	  explicit_width = itset_create_const_1 (&self->spec,
						 self->default_width);
	}
    }
  else
    {
      /* FIXME: should probably error out if the current set has mixed
	 width.  If we do that, then probably the "current width"
	 cases here should probably return an ITSET_WIDTH_UNSPECIFIED,
	 in order to delay that error until the end of parsing, in
	 order to show parsing errors first.  */
      width = itset_get_width (current_itset);

      if (width == ITSET_WIDTH_DEFAULT)
	width = self->default_width;
      else if (width == ITSET_WIDTH_EXPLICIT)
	{
	  if (current_itset->elements.size () == 1)
	    {
	      struct itset_elt *elt = current_itset->elements [0];

	      if (elt->is_range_type ())
		{
		  struct itset_elt_range *range_elt
		    = (struct itset_elt_range *) elt;

		  explicit_width = itset_reference (range_elt->explicit_width);
		}
	    }

	  if (explicit_width == NULL)
	    error (_("Current focus is a complex set, "
		     "and no width specified."));
	}
    }

  if (*self->spec == '/')
    {
      self->spec++;
      /* FIXME: leak on error.  */
      group = parse_named_or_throw (&self->spec);

      if (*self->spec == '/')
	self->spec++;
    }

  if (*self->spec == ' '
      || *self->spec == '\0'
      || *self->spec == '&'
      || *self->spec == ','
      || *self->spec == '('
      || *self->spec == ')')
    {
      if (current_itset->elements.size () == 1)
	{
	  struct itset_elt *elt;

	  elt = current_itset->elements[0];

	  if (elt->is_range_type ())
	    {
	      struct itset_elt *clone_elt = elt->clone ();
	      struct itset_elt_range *range_elt = (struct itset_elt_range *) clone_elt;

	      range_elt->width = width;
	      if (explicit_width != NULL)
		range_elt->explicit_width = explicit_width;
	      if (group != NULL)
		range_elt->group = group;
	      return (struct itset_elt *) range_elt;
	    }
	}

      error (_("Current focus is a complex set, and no ID specified."));
    }

  elt_range = parse_range_elem (self, width);
  if (elt_range != NULL)
    {
      elt_range->explicit_width = explicit_width;

#if 0
      /* For now, an unspecified group name defaults to nothing.  */
      if (group == NULL)
	elt_range->group = create_empty_itset ();
      else
#endif
	elt_range->group = group;
      return elt_range;
    }

  return parse_named_or_throw (&self->spec);

  self->spec = save_spec;
  return NULL;
}

static struct itset_elt *
parse_elem (struct itset_parser *self)
{
  struct itset_elt *elt;

  maybe_skip_spaces (self);

  elt = parse_neg (self);
  if (elt != NULL)
    return elt;

  elt = parse_parens_set (self);
  if (elt != NULL)
    return elt;

  elt = parse_current_focus (self);
  if (elt != NULL)
    return elt;

  elt = parse_elem_1 (self);
  if (elt != NULL)
    return elt;

  error (_("Invalid I/T set spec: `%s'"), self->spec);
  //  return parse_named_or_throw (spec);
}

static struct itset_elt *
parse_neg (struct itset_parser *self)
{
  struct itset_elt_negated *neg_elt;
  struct itset_elt *elt;

  if (*self->spec != '~')
    return NULL;

  self->spec++;

  elt = parse_elem (self);

  neg_elt = create_itset_elt_negated ();
  neg_elt->negated = elt;

  return (struct itset_elt *) neg_elt;
}

static struct itset_elt *
parse_current_focus (struct itset_parser *self)
{
  struct itset_elt_itset *itset_elt;

  if (*self->spec != '$')
    return NULL;

  self->spec++;

  itset_elt = create_itset_elt_itset (itset_reference (current_itset));
  return (struct itset_elt *) itset_elt;
}

static struct itset_elt *
parse_parens_set (struct itset_parser *self)
{
  if (*self->spec != '(')
    return NULL;
  self->spec++;

  self->parens_level++;

  std::auto_ptr <itset_elt> elt (parse_itset_one (self));
  if (elt.get () == NULL)
    error (_("Invalid I/T syntax at `%s'"), self->spec);

  if (*self->spec != ')')
    error (_("Invalid I/T syntax at `%s'"), self->spec);

  self->spec++;
  self->parens_level--;
  gdb_assert (self->parens_level >= 0);

  return elt.release ();
}

static struct itset_elt *
parse_inters (struct itset_parser *self)
{
  std::auto_ptr <itset_elt> elt1 (parse_elem (self));
  if (elt1.get () == NULL)
    return NULL;

  maybe_skip_spaces (self);

  if (*self->spec != '&')
    {
      /* Not an intersect.  */
      return elt1.release ();
    }

  std::auto_ptr <itset_elt_intersect> intersect (create_intersect_itset ());
  intersect->add (elt1.release ());

  while (*self->spec == '&')
    {
      self->spec++;

      struct itset_elt *elt2 = parse_elem (self);
      if (elt2 == NULL)
	return NULL;
      intersect->add (elt2);
    }

  return intersect.release ();
}

class itset_ptr
{
public:
  explicit itset_ptr (itset *set)
    : m_itset (set)
  {}

  ~itset_ptr ()
  {
    if (m_itset != NULL)
      m_itset->decref ();
  }

  itset &operator* () const { return *m_itset; }

  itset *operator-> () const { return m_itset; }

  itset *get () const { return m_itset; }

  itset *release ()
  {
    itset *res = m_itset;
    m_itset = NULL;
    return res;
  }

private:
  itset *m_itset;
};

static struct itset_elt *
parse_itset_one (struct itset_parser *self)
{
  std::auto_ptr <itset_elt> elt1 (parse_elem (self));
  if (elt1.get () == NULL)
    return NULL;

  maybe_skip_spaces (self);

  if (*self->spec == ',' || (self->parens_level > 0 && *self->spec != ')'))
    ;
  else
    return elt1.release ();

  itset_ptr set (new itset ());
  std::auto_ptr <itset_elt_itset> un (create_itset_elt_itset (set.get ()));
  set->elements.push_back (elt1.release ());

  while (*self->spec == ',' || (self->parens_level > 0 && *self->spec != ')'))
    {
      if (*self->spec == ',')
	self->spec++;

      maybe_skip_spaces (self);

      if (*self->spec == '\0')
	error (_("Invalid I/T syntax: premature end"));

      struct itset_elt *inters2 = parse_inters (self);
      if (inters2 == NULL)
	return NULL;
      set->elements.push_back (inters2);

      maybe_skip_spaces (self);
    }

  return un.release ();
}

/* A helper function that returns true if the inferior INF is
   contained by the set ELEMENTS.  */

static char *
set_get_spec (const itset_elt_vector &elements)
{
  char *ret = xstrdup ("");

  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;
      const char *elt_spec = elt->get_spec ();

      ret = reconcat (ret, ret,
		      it == elements.begin () ? "" : ",",
		      elt_spec, (char *) NULL);
    }

  return ret;
}

static char *
itset_get_spec (const itset *set)
{
  return set_get_spec (set->elements);
}

/* FIXME: This only exists to cast result to const.  But then again,
   all callers are leaking the result.  */

const char *
itset_spec (const itset *set)
{
  return itset_get_spec (set);
}

static enum itset_width
set_get_width (const itset_elt_vector &elements)
{
  enum itset_width width = ITSET_WIDTH_DEFAULT;

  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;
      enum itset_width elt_width = elt->get_width ();

      if (elt_width > width)
	width = elt_width;
    }

  return width;
}

enum itset_width
itset_get_width (itset *set)
{
  return set_get_width (set->elements);
}


static struct thread_info *
set_get_toi (const itset_elt_vector &elements)
{
  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;
      struct thread_info *tp = elt->get_toi ();

      if (tp != NULL)
	return tp;
    }

  return NULL;
}

struct thread_info *
itset_get_toi (itset *set)
{
  return set_get_toi (set->elements);
}

static int
set_has_fixed_toi (const itset_elt_vector &elements)
{
  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;
      if (elt->has_fixed_toi ())
	return 1;
    }

  return 0;
}

int
itset_has_fixed_toi (itset *set)
{
  return set_has_fixed_toi (set->elements);
}

static char
set_get_focus_object_type (const itset_elt_vector &elements)
{
  for (itset_elt_vector::const_iterator it = elements.begin ();
       it != elements.end ();
       ++it)
    {
      struct itset_elt *elt = *it;
      char object_type_char = '\0';

      object_type_char = elt->get_focus_object_type ();
      if (object_type_char != '\0')
	return object_type_char;
    }

  return '\0';

  gdb_assert_not_reached ("set has no object type");
}

char
itset_get_focus_object_type (itset *set)
{
  return set_get_focus_object_type (set->elements);
}

/* Parse an I/T set specification and return a new I/T set.  Throws an
   exception on error.  */

static itset *
itset_create_const_1 (const char **specp, enum itset_width default_width)
{
  int is_static = 0;
  struct itset_elt *elt;
  struct cleanup *cleanups;
  const char *spec = *specp;
  const char *spec_start;

  itset_ptr result (new itset ());

  spec = skip_spaces_const (spec);
  spec_start = spec;

  if (*spec == '!')
    {
      is_static = 1;
      ++spec;
    }

  if (!valid_spec_end (spec))
    {
      struct itset_parser parser = {0};

      parser.default_width = default_width;
      parser.spec = spec;
      elt = parse_itset_one (&parser);
      result->elements.push_back (elt);

      spec = parser.spec;
#if 0
      if (!valid_spec_end (spec))
	error (_("Invalid I/T syntax at `%s'"), spec);
#endif
    }

  result->spec = xstrndup (spec_start, spec - spec_start);
  *specp = spec;

  if (is_static)
    {
      struct itset_elt *st = create_static_itset (ITSET_WIDTH_ALL,
						  result->elements);

      set_free (result->elements);
      result->elements.clear ();
      result->elements.push_back (st);
    }

  return result.release ();
}

itset *
itset_create_const (const char **specp, enum itset_width default_width)
{
  itset *set;

  set = itset_create_const_1 (specp, default_width);
  if (!valid_spec_end (*specp))
    {
      itset_free (set);
      error (_("Invalid I/T syntax at `%s'"), *specp);
    }
  return set;
}

static itset *
itset_create_spec_default_width (const char *spec,
				 enum itset_width default_width)
{
   return itset_create_const (&spec, default_width);
}

itset *
itset_create_spec (const char *spec)
{
  return itset_create_spec_default_width (spec, ITSET_WIDTH_DEFAULT);
}

itset *
itset_create (char **specp)
{
  const char *spec_const = *specp;
  itset *itset;

  itset = itset_create_const (&spec_const, ITSET_WIDTH_DEFAULT);
  *specp = (char *) spec_const;
  return itset;
}

itset *
itset_clone_replace_default_width (const itset *itset_template,
				   enum itset_width default_width)
{
  itset *result;
  char *spec;

  spec = itset_get_spec (itset_template);

  /* We're reparsing a spec we had previously parsed successfully, so
     this should never error out.  */
  result = itset_create_spec_default_width (spec, default_width);
  xfree (spec);

  return result;
}

itset *
itset_create_empty (void)
{
  return itset_create_spec ("");
}

/* Create a new I/T set which represents the current inferior and all
   its threads.  */

static itset *
itset_create_curinf (void)
{
  return itset_create_spec ("iI");
}

/* Create a new I/T set which represents the current thread.  */

static itset *
itset_create_curthr (void)
{
  return itset_create_spec ("tT");
}

/* Create a new I/T set which represents the current thread.  */

static itset *
itset_create_lockstep (void)
{
  return itset_create_spec ("t/L/t1.1");
}

static itset *itset_from_elt (struct itset_elt *elt);

static itset *
itset_create_all (void)
{
  return itset_from_elt (create_all_itset ());
}

static itset *
itset_create_running (void)
{
  return itset_from_elt (create_state_itset (THREAD_RUNNING));
}

static itset *
itset_create_stopped (void)
{
  return itset_from_elt (create_state_itset (THREAD_STOPPED));
}

static itset *
itset_create_default (void)
{
  return itset_create_spec ("dt1.1");
}

int
itset_contains_any_thread (itset *set)
{
  struct thread_info *thr;

  ALL_THREADS (thr)
    if (itset_contains_thread (set, thr))
      return 1;

  return 0;
}


/* Return 1 if SET contains INF, 0 otherwise.  */

int
itset_contains_program_space (itset *set,
			      enum itset_width default_width,
			      struct program_space *pspace)
{
  return set_contains_program_space (set->elements, default_width, pspace);
}

/* Return 1 if SET contains INF, 0 otherwise.  */

static int
itset_contains_inferior_1 (itset *set,
			   enum itset_width default_width,
			   struct inferior *inf,
			   int including_width)
{
  if (including_width)
    return set_contains_inferior (set->elements, default_width, inf, 1);
  else
    return set_contains_inferior (set->elements, ITSET_WIDTH_INFERIOR, inf, 0);
}

/* Return 1 if SET contains INF, 0 otherwise.  */

int
itset_width_contains_inferior (itset *set,
			       enum itset_width default_width,
			       struct inferior *inf)
{
  return itset_contains_inferior_1 (set, default_width, inf, 1);
}

/* Return 1 if SET contains INF, 0 otherwise.  */

int
itset_contains_inferior (itset *set,
			 struct inferior *inf)
{
  return itset_contains_inferior_1 (set, ITSET_WIDTH_INFERIOR, inf, 0);
}

int
itset_contains_thread_maybe_width (itset *set,
				   enum itset_width default_width,
				   struct thread_info *thr,
				   int including_width)
{
  if (including_width)
    return set_contains_thread (set->elements, default_width, thr, 1);
  else
    return set_contains_thread (set->elements, ITSET_WIDTH_THREAD, thr, 0);
}

/* Return 1 if SET contains THR, 0 otherwise.  */

int
itset_width_contains_thread (itset *set,
		       enum itset_width default_width,
		       struct thread_info *thr)
{
  return itset_contains_thread_maybe_width (set, default_width, thr, 1);
}

/* Return 1 if SET contains THR, 0 otherwise.  */

int
itset_contains_thread (itset *set,
		       struct thread_info *thr)
{
  return itset_contains_thread_maybe_width (set, ITSET_WIDTH_THREAD, thr, 0);
}

/* Return 1 if SET contains TASK, 0 otherwise.  */

int
itset_contains_ada_task (itset *set,
			 enum itset_width default_width,
			 const struct ada_task_info *task,
			 int including_width)
{
  struct thread_info *thr;

  thr = find_thread_ptid (task->ptid);
  if (thr == NULL)
    return 0;

  return itset_contains_thread_maybe_width (set, default_width,
					    thr, including_width);
}

/* Acquire a new reference to an I/T set.  */

itset *
itset_reference (itset *set)
{
  set->incref ();
  return set;
}

/* Destroy SET.  */

void
itset_free (itset *set)
{
  /* Like xfree, allow NULL.  */
  if (set == NULL)
    return;

  set->decref ();
}

/* Helper struct for iterate_over_itset.  */

struct iterate_data
{
  /* The I/T set we are using.  */
  itset *set;

  /* The original callback  */
  int (*callback) (struct inferior *, void *);

  /* The data passed in to iterate_over_itset.  */
  void *client_data;

  enum itset_width default_width;
};

/* Callback function for iterate_over_inferiors, used by
   iterate_over_itset.  */

static int
iter_callback (struct inferior *inf, void *d)
{
  struct iterate_data *data = (struct iterate_data *) d;

  if (itset_contains_inferior_1 (data->set, data->default_width, inf, 1))
    return data->callback (inf, data->client_data);

  /* Keep going.  */
  return 0;
}

/* Like iterate_over_inferiors, but iterate over only those inferiors
   in ITSET.  */

struct inferior *
iterate_over_itset_inferiors (itset *set,
			      enum itset_width default_width,
			      itset_inf_callback_func *callback,
			      void *datum)
{
  struct iterate_data data;

  data.set = set;
  data.callback = callback;
  data.client_data = datum;
  data.default_width = default_width;

  return iterate_over_inferiors (iter_callback, &data);
}

/* Helper struct for iterate_over_itset.  */

struct iterate_thr_data
{
  /* The I/T set we are using.  */
  itset *set;

  /* The original callback  */
  int (*callback) (struct thread_info *, void *);

  /* The data passed in to iterate_over_itset_threads.  */
  void *client_data;

  enum itset_width default_width;
};

/* Callback function for iterate_over_inferiors, used by
   iterate_over_itset.  */

static int
iter_thr_callback (struct thread_info *thr, void *d)
{
  struct iterate_thr_data *data = (struct iterate_thr_data *) d;

  if (itset_contains_thread_maybe_width (data->set, data->default_width,
					 thr, 1))
    return data->callback (thr, data->client_data);

  /* Keep going.  */
  return 0;
}

/* Like iterate_over_inferiors, but iterate over only those inferiors
   in ITSET.  */

static struct thread_info *
iterate_over_itset_threads (itset *set,
			    enum itset_width default_width,
			    int (*callback) (struct thread_info *, void *),
			    void *datum)
{
  struct iterate_thr_data data;

  data.set = set;
  data.callback = callback;
  data.client_data = datum;
  data.default_width = default_width;

  return iterate_over_threads (iter_thr_callback, &data);
}

itset *current_itset = NULL;

/* A cleanups callback, helper for save_current_itset
   below.  */

static void
restore_itset (void *arg)
{
  itset *saved_itset = (itset *) arg;

  current_itset = saved_itset;
  itset_free (current_itset);
}

/* Save the current itset so that it may be restored by a later call
   to do_cleanups.  Returns the struct cleanup pointer needed for
   later doing the cleanup.  */

static struct cleanup *
save_current_itset (void)
{
  struct cleanup *old_chain
    = make_cleanup (restore_itset,
		    itset_reference (current_itset));

  return old_chain;
}

static int
first_inferior (struct inferior *inf, void *data)
{
  return 1;
}

static int
count_inferiors (struct inferior *inf, void *data)
{
  int *count_p = (int *) data;
  (*count_p)++;
  return 0;
}

static int
first_thread_of (struct thread_info *thr, void *data)
{
  int inf_pid = * (int *) data;

  if (ptid_get_pid (thr->ptid) != inf_pid)
    return 0;

  if (thr->state != THREAD_EXITED)
    return 1;
  return 0;
}

struct count_threads_arg
{
  int pid;
  int count;
};

static int
count_threads_of (struct thread_info *thr, void *data)
{
  struct count_threads_arg *c = (struct count_threads_arg *) data;

  if (ptid_get_pid (thr->ptid) != c->pid)
    return 0;

  c->count++;
  return 0;
}

static void
switch_to_itset (itset *itset)
{
  struct inferior *inf;
  struct thread_info *tp;
  struct cleanup *old_chain;
  int inf_count;

#if 0
  char focus_type;
  focus_type = itset_get_focus_object_type (itset);
  /* FIXME: Focusing on a goroutine for example should walk
     goroutines, not threads.  */
  if (focus_type == 't' || focus_type == 'i')
#endif
    {
      struct thread_info *thr;

      ALL_THREADS (thr)
	{
	  if (itset_contains_thread (itset, thr))
	    {
	      switch_to_thread (thr->ptid);
	      set_current_context ();
	      return;
	    }
	}
    }

  ALL_INFERIORS (inf)
    {
      if (itset_contains_inferior (itset, inf))
	{
	  struct thread_info *thr = NULL;

#if 0
	  if (inf->pid != 0)
	    thr = first_thread_of_process (inf->pid);

	  if (thr != NULL)
	    {
	      switch_to_thread (thr->ptid);
	    }
	  else
#endif
	    {
	      switch_to_thread (null_ptid);
	      set_current_inferior (inf);
	      set_current_program_space (inf->pspace);
	    }
	  set_current_context ();
	  return;
	}
    }
  return;

  tp = itset_get_toi (itset);
  if (tp != NULL)
    {
      switch_to_thread (tp->ptid);
      set_current_context ();
      return;
    }

  /* For now, set a current inferior from the first element of the
     focus set.  */
  inf = iterate_over_itset_inferiors (itset, ITSET_WIDTH_ALL,
				      first_inferior, NULL);
  if (inf == NULL)
    {
      /* Empty set.  Switch to no thread selected.  There's no concept
	 of no inferior selected, so just leave the current
	 selected.  */
      switch_to_thread (null_ptid);
      set_current_program_space (current_inferior ()->pspace);
      set_current_context ();
      return;
    }

  set_current_inferior (inf);
  switch_to_thread (null_ptid);
  set_current_program_space (inf->pspace);
  set_current_context ();
  return;

#if 1
  inf_count = 0;
  iterate_over_itset_inferiors (itset, ITSET_WIDTH_ALL,
				count_inferiors, &inf_count);
  if (inf_count > 1)
    warning ("\
%d inferiors in the current i/t set, using inf %d to get current exec",
	     inf_count, inf->num);

  if (inf->pid != 0)
    {
      struct count_threads_arg count_threads_arg;

      count_threads_arg.pid = inf->pid;
      count_threads_arg.count = 0;
      iterate_over_itset_threads (itset, ITSET_WIDTH_ALL,
				  count_threads_of, &count_threads_arg);
      if (count_threads_arg.count != 0)
	{
	  struct thread_info *thr;

	  if (count_threads_arg.count > 1)
	    warning (_("\
%d threads for inferior %d in the current i/t set, switching to first"),
		     count_threads_arg.count, inf->num);
	  thr = iterate_over_itset_threads (itset, ITSET_WIDTH_ALL,
					    first_thread_of, &inf->pid);
	  switch_to_thread (thr->ptid);
	}
    }
  else
    {
      set_current_inferior (inf);
      switch_to_thread (null_ptid);
      set_current_program_space (inf->pspace);
    }
#endif
}

int
itfocus_should_follow_stop_event (void)
{
  struct itset_elt_range *cur_elt_range
    = itset_get_range_elt_if_simple (current_itset);

  return (cur_elt_range != NULL);
}

static itset *
itset_from_elt (struct itset_elt *elt)
{
  itset *set = new itset ();

  set->elements.push_back (elt);
  return set;
}

void
itfocus_from_thread_switch (void)
{
  struct itset_elt_range *new_elt_range;
  struct itset_elt_range *cur_elt_range
    = itset_get_range_elt_if_simple (current_itset);
  enum itset_width width = itset_get_width (current_itset);
  itset *new_itset;
  struct spec_range inf_range;
  struct spec_range thr_range;

  inf_range.first = current_inferior ()->num;
  inf_range.last = inf_range.first;

  if (ptid_equal (inferior_ptid, null_ptid))
    {
      thr_range.first = 0;
      thr_range.last = 0;
    }
  else
    {
      thr_range.first = inferior_thread ()->per_inf_num;
      thr_range.last = thr_range.first;
    }

  new_elt_range = create_thread_range_itset (width, 0, &inf_range, &thr_range);

  if (cur_elt_range != NULL && cur_elt_range->explicit_width != NULL)
    {
      new_elt_range->explicit_width
	= itset_reference (cur_elt_range->explicit_width);
    }

  new_itset = itset_from_elt (new_elt_range);
  itset_free (current_itset);
  current_itset = new_itset;
}

static void
restore_current_context_cleanup (void *data)
{
  struct execution_context *ctx = (struct execution_context *) data;

  *get_current_context () = *ctx;
}

static void
itfocus_command (char *spec, int from_tty)
{
  struct cleanup *old_chain;
  char *expanded_spec;

  if (spec != NULL)
    {
      itset *itset;

      itset = itset_create (&spec);
      old_chain = make_cleanup_itset_free (itset);

      spec = skip_spaces (spec);
      if (*spec != '\0')
	{
	  struct execution_context saved_ctx;

	  old_chain = save_current_itset ();
	  current_itset = itset;

	  saved_ctx = *get_current_context ();
	  make_cleanup (restore_current_context_cleanup, &saved_ctx);

	  make_cleanup_restore_current_thread ();

	  switch_to_itset (itset);

	  execute_command (spec, from_tty);

	  do_cleanups (old_chain);
	  return;
	}

      discard_cleanups (old_chain);

      itset_free (current_itset);
      current_itset = itset;

      switch_to_itset (itset);
    }

#if 0
  if (itset_is_empty (current_itset, ITSET_WIDTH_ALL))
    warning (_("focus set is empty"));
#endif

  /* Confirm the choice of focus.  */
  expanded_spec = itset_get_spec (current_itset);
  old_chain = make_cleanup (xfree, expanded_spec);

  printf_filtered (_("Focus is `%s'.\n"), expanded_spec);
  printf_filtered (_("Current inferior is %d.\n"), current_inferior ()->num);
  if (!ptid_equal (inferior_ptid, null_ptid))
    printf_filtered (_("Current thread is %s.\n"), print_thread_id (inferior_thread ()));
  else
    printf_filtered (_("No current thread.\n"));

  do_cleanups (old_chain);
}

static struct named_itset *
make_itset_named_itset (class itset *itset, char *name, int internal)
{
  named_itset *result;

  itset_reference (itset);
  itset->name = name;

  result = new named_itset (itset);

  if (internal)
    result->number = --internal_named_itset_count;
  else
    result->number = ++named_itset_count;

  return result;
}

#if 0
static int
itset_elt_is_static (struct itset_elt *elt)
{
  return elt->vtable == &static_vtable;
}

static int
itset_is_static (itset *itset)
{
  struct itset_elt *elt;
  int ix;

  /* True if all elements are static.  */

  if (VEC_empty (itset_elt_ptr, itset->elements))
    return 0;

  for (ix = 0; VEC_iterate (itset_elt_ptr, itset->elements, ix, elt); ++ix)
    if (!itset_elt_is_static (elt))
      return 0;

  return 1;
}

#endif

static void
itset_command (char *arg, int from_tty)
{
  char *endp;
  char *name;
  char *spec;
  class itset *itset;
  class named_itset *named_itset;
  struct cleanup *old_chain;

  if (arg == NULL || *arg == '\0')
    error_no_arg (_("no args"));

  arg = skip_spaces (arg);

  endp = skip_to_space (arg);
  spec = endp;

  name = xstrndup (arg, endp - arg);
  old_chain = make_cleanup (xfree, name);

  named_itset = get_named_itset (name);
  if (named_itset != NULL)
    error (_("itset %s already exists"), name);

  spec = skip_spaces (spec);

  itset = itset_create (&spec);
  make_cleanup_itset_free (itset);

#if 0
  if (itset_is_static (itset) && itset_is_empty (itset, ITSET_WIDTH_ALL))
    warning (_("static itset is empty"));
#endif

  named_itset = make_itset_named_itset (itset, name, 0);
  itset_free (itset);
  discard_cleanups (old_chain);
  add_to_named_itset_chain (named_itset);
}

static void
delete_itset_command (char *arg_mut, int from_tty)
{
  char *name;
  struct named_itset *it, **it_link;
  int found;
  struct get_number_or_range_state state;
  const char *arg = arg_mut;

  if (arg == NULL || *arg == '\0')
    {
      bool any_to_delete = false;
      struct named_itset *set;

      ALL_NAMED_ITSETS (set)
	{
	  if (set->number > 0)
	    {
	      any_to_delete = true;
	      break;
	    }
	}

      /* Ask user only if there are some itsets to delete.  */
      if (!from_tty
	  || (any_to_delete && query (_("Delete all named itsets? "))))
	{
	  ALL_NAMED_ITSETS_IT (it, set)
	    {
	      if (set->number > 0)
		{
		  delete set;
		  named_itsets.erase (it);

		  // iterator invalidated, or not?
		}
	    }
	}

      return;
    }

  while (*arg != '\0')
    {
      arg = skip_spaces_const (arg);

      if (isdigit (arg[0]))
	{
	  init_number_or_range (&state, arg);

	  while (!state.finished)
	    {
	      const char *p = state.string;

	      int num = get_number_or_range (&state);
	      if (num <= 0)
		{
		  warning (_("bad itset number at or near '%s'"), p);
		}
	      else
		{
		  struct named_itset *set;
		  bool match = false;

		  ALL_NAMED_ITSETS_IT (it, set)
		  {
		    if (set->number == num)
		      {
			match = true;
			named_itsets.erase (it);
			break;
		      }
		  }

		  if (!match)
		    printf_unfiltered (_("No itset number %d.\n"), num);
		}
	    }

	  arg = state.string;
	}
      else
	{
	  const char *name = arg;
	  const char *endname = skip_to_space_const (name);

	  bool found = false;
	  struct named_itset *set;

	  ALL_NAMED_ITSETS_IT (it, set)
	    {
	      if (strncmp (set->set->name, name, endname - name) == 0
		  && set->set->name[endname - name] == '\0')
		{
		  if (set->number < 0)
		    error (_("cannot delete builtin I/T set"));

		  delete set;
		  named_itsets.erase (it);
		  found = true;
		  break;
		}
	    }

	  arg = endname;

	  if (!found)
	    warning (_("itset %s does not exist"), name);
	}
    }
}

static void
itsets_info (char *arg, int allflag, int from_tty)
{
  struct named_itset *e;
  int num_printable_entries;
  struct cleanup *tbl_chain;

  /* Compute the number of rows in the table.  */
  num_printable_entries = 0;

  ALL_NAMED_ITSETS (e)
    if (allflag
	|| (e->number > 0
	    && (arg == NULL || number_is_in_list (arg, e->number))))
      num_printable_entries++;

  if (num_printable_entries == 0)
    {
      if (arg == NULL)
	ui_out_message (current_uiout, 0, _("No named itsets.\n"));
      else
	ui_out_message (current_uiout, 0,
			_("No named itset found with number %s.\n"), arg);

      return;
    }

  tbl_chain
    = make_cleanup_ui_out_table_begin_end (current_uiout, 3,
					   num_printable_entries,
					   "NamedItsetListTable");

  ui_out_table_header (current_uiout, 7, ui_left, "number", "Num");      /* 1 */
  ui_out_table_header (current_uiout, 14, ui_left, "name", "Name");      /* 2 */
  ui_out_table_header (current_uiout, 40, ui_noalign, "what", "What");   /* 3 */
  ui_out_table_body (current_uiout);

  ALL_NAMED_ITSETS (e)
    if (allflag
	|| (e->number > 0
	    && (arg == NULL || number_is_in_list (arg, e->number))))
      {
	struct cleanup *entry_chain;

	QUIT;

	entry_chain
	  = make_cleanup_ui_out_tuple_begin_end (current_uiout, "named-itset");
	ui_out_field_int (current_uiout, "number", e->number);             /* 1 */
	ui_out_field_string (current_uiout, "name", e->set->name);         /* 2 */
	ui_out_field_string (current_uiout, "what", e->set->spec);         /* 3 */
	ui_out_text (current_uiout, "\n");
	do_cleanups (entry_chain);
      }

  do_cleanups (tbl_chain);
}

static void
info_itsets_command (char *arg, int from_tty)
{
  itsets_info (arg, 0, from_tty);
}

static void
maintenance_info_itsets_command (char *arg, int from_tty)
{
  itsets_info (arg, 1, from_tty);
}

static int
whichsets_callback (struct thread_info *thr, void *data)
{
  struct named_itset *named_itset;
  struct inferior *inf = get_thread_inferior (thr);
  bool printed = false;

  ALL_NAMED_ITSETS (named_itset)
    {
      QUIT;

      if (itset_contains_thread (named_itset->set, thr))
	{
	  if (!printed)
	    {
	      printf_filtered (_("Thread %s (%s) is in:"),
			       print_thread_id (thr),
			       target_pid_to_str (thr->ptid));
	      printf_filtered (" %s", itset_name (named_itset->set));
	      printed = true;
	    }
	  else
	    printf_filtered (", %s", itset_name (named_itset->set));
	}
    }

  if (printed)
    printf_filtered ("\n");

  return 0;
}

static void
whichsets_command (char *arg, int from_tty)
{
  class named_itset *named_itset;
  class itset *itset;
  struct cleanup *old_chain;

  if (arg == NULL)
    {
      /* No arg means all threads.  */
      itset = itset_reference (current_itset);
    }
  else
    {
      arg = skip_spaces (arg);
      itset = itset_create (&arg);
    }

  old_chain = make_cleanup_itset_free (itset);
  iterate_over_itset_threads (itset, ITSET_WIDTH_ALL,
			      whichsets_callback, NULL);
  do_cleanups (old_chain);
}

static void
viewset (class itset *itset)
{
  struct inferior *inf;
  struct thread_info *thr;
  int printed;

  printf_filtered ("%s contains:\n",
		   (itset_name (itset) != NULL
		    ? itset_name (itset) : itset_spec (itset)));

  printed = 0;
  ALL_INFERIORS (inf)
    {
      if (itset_width_contains_inferior (itset, ITSET_WIDTH_ALL, inf))
	{
	  if (!printed)
	    {
	      printf_filtered (_("  inferiors: %d"), inf->num);
	      printed = 1;
	    }
	  else
	    printf_filtered (", %d", inf->num);

	}
    }
  if (printed)
    printf_filtered ("\n");

  printed = 0;
  ALL_THREADS (thr)
    {
      if (itset_width_contains_thread (itset, ITSET_WIDTH_ALL, thr))
	{
	  if (!printed)
	    {
	      printf_filtered (_("  threads: %s"), print_thread_id (thr));
	      printed = 1;
	    }
	  else
	    printf_filtered (", %s", print_thread_id (thr));
	}
    }
  if (printed)
    printf_filtered ("\n");

  printed = 0;
  ALL_THREADS (thr)
    {
      if (itset_width_contains_thread (itset, ITSET_WIDTH_ALL, thr))
	{
	  int core;

	  core = target_core_of_thread (thr->ptid);
	  if (core == -1)
	    break;

	  if (!printed)
	    {
	      printf_filtered (_("  cores: %d"), core);
	      printed = 1;
	    }
	  else
	    printf_filtered (", %d", core);
	}
    }
  if (printed)
    printf_filtered ("\n");
}

static void
viewset_command (char *arg, int from_tty)
{
  class named_itset *named_itset;

  if (arg == NULL)
    {
      struct named_itset *e;
      itset *set;

      /* No arg means all debugger- and user-defined sets.  */
      ALL_NAMED_ITSETS (named_itset)
	viewset (named_itset->set);
    }
  else
    {
      class itset *itset;
      struct cleanup *old_chain;

      arg = skip_spaces (arg);
      itset = itset_create (&arg);
      old_chain = make_cleanup_itset_free (itset);
      viewset (itset);
      do_cleanups (old_chain);
    }
}

static void
make_internal_itset (itset *set, const char *name)
{
  struct named_itset *named_set;

  named_set = make_itset_named_itset (set, xstrdup (name), 1);
  add_to_named_itset_chain (named_set);
}

static void
for_each_selected_thread_cmd_1 (cmd_cfunc_ftype cmd,
				char *args, int from_tty)
{
  struct cleanup *old_chain;
  struct inferior *inf;
  struct thread_info *tp;
  int count = 0;

  /* Don't use make_cleanup_restore_current_thread as CMD may want to
     change the user selected frame, e.g., up/down/frame, etc.  */
  old_chain = make_cleanup_restore_execution_context_thread ();

  /* Don't print anything about threads if only printing one
     thread.  */
  ALL_INFERIORS (inf)
    {
      if (inf->pid == 0)
	{
	  if (!itset_contains_inferior (current_itset, inf))
	    continue;
	  count++;
	  if (count > 1)
	    break;
	}
      else
	{
	  ALL_NON_EXITED_THREADS (tp)
	    {
	      if (inf->pid != ptid_get_pid (tp->ptid))
		continue;

	      if (!itset_contains_thread (current_itset, tp))
		continue;

	      count++;
	      if (count > 1)
		break;
	    }
	}
    }

  ALL_INFERIORS (inf)
    {
      if (inf->pid == 0)
	{
	  if (!itset_contains_inferior (current_itset, inf))
	    continue;

	  set_current_program_space (inf->pspace);
	  set_current_inferior (inf);
	  switch_to_thread (null_ptid);

	  if (count > 1)
	    {
	      printf_filtered (_("\nThread %d.0:\n"), inf->num);
	    }

	  TRY
	    {
	      (*cmd) (args, from_tty);
	    }
	  CATCH (ex, RETURN_MASK_ERROR)
	    {
	      if (count > 1)
		exception_print (gdb_stderr, ex);
	      else
		throw_exception (ex);
	    }
	  END_CATCH
	}
      else
	{
	  ALL_NON_EXITED_THREADS (tp)
	    {
	      if (inf->pid != ptid_get_pid (tp->ptid))
		continue;

	      if (!itset_contains_thread (current_itset, tp))
		continue;

	      switch_to_thread (tp->ptid);
	      if (count > 1)
		{
		  printf_filtered (_("\nThread %s (%s):\n"),
				   print_thread_id (tp),
				   target_pid_to_str (inferior_ptid));
		  if (tp->state == THREAD_RUNNING)
		    {
		      printf_filtered (_("\t(running)\n"));
		      continue;
		    }
		}

	      TRY
		{
		  (*cmd) (args, from_tty);
		}
	      CATCH (ex, RETURN_MASK_ERROR)
		{
		  if (count > 1)
		    exception_print (gdb_stderr, ex);
		  else
		    throw_exception (ex);
		}
	      END_CATCH
	    }
	}
    }

  do_cleanups (old_chain);
}

static void
for_each_selected_ada_task_cmd (cmd_cfunc_ftype cmd,
				char *args, int from_tty)
{
  struct cleanup *old_chain;
  int count = 0;
  struct inferior *inf;

  /* Don't use make_cleanup_restore_current_thread as CMD may want to
     change the user selected frame, e.g., up/down/frame, etc.  */
  old_chain = make_cleanup_restore_execution_context_thread ();

  /* Don't print anything about tasks if only focused on one task.  */
  ALL_INFERIORS (inf)
    {
      VEC(ada_task_info_s) *task_list;
      struct ada_task_info *task;
      int ix;

      task_list = get_ada_tasks (inf, 1);

      if (count > 1)
	break;

      for (ix = 0; VEC_iterate (ada_task_info_s, task_list, ix, task); ++ix)
	{
	  if (!itset_contains_ada_task (current_itset, ITSET_WIDTH_ADA_TASK,
					task, 0))
	    continue;
	  count++;
	  if (count > 1)
	    break;
	}
    }

  ALL_INFERIORS (inf)
    {
      VEC(ada_task_info_s) *task_list;
      struct ada_task_info *task;
      int ix;

      task_list = get_ada_tasks (inf, 0);

      for (ix = 0; VEC_iterate (ada_task_info_s, task_list, ix, task); ++ix)
	{
	  if (!itset_contains_ada_task (current_itset, ITSET_WIDTH_ADA_TASK,
					task, 0))
	    continue;

	  switch_to_thread (task->ptid);

	  if (count > 1)
	    printf_filtered (_("\nTask %d.%d:\n"), inf->num, ix + 1);

	  TRY
	    {
	      (*cmd) (args, from_tty);
	    }
	  CATCH (ex, RETURN_MASK_ERROR)
	    {
	      if (count > 1)
		exception_print (gdb_stderr, ex);
	      else
		throw_exception (ex);
	    }
	  END_CATCH
	}
    }

  do_cleanups (old_chain);
}

static int focus_mode;

void
for_each_selected_thread_cmd (cmd_cfunc_ftype cmd,
			      char *args, int from_tty)
{
  if (focus_mode == 0)
    for_each_selected_thread_cmd_1 (cmd, args, from_tty);
  else
    for_each_selected_ada_task_cmd (cmd, args, from_tty);
}

/* The "itfocus" completer.  Skips the itset, and if valid, completes
   on command names.  If invalid, completes nothing, which is a useful
   hint that tells that you need to go back and fix the itset
   spec.  */

static VEC (char_ptr) *
itfocus_completer (struct cmd_list_element *ignore,
		   const char *text, const char *word)
{
  TRY
    {
      itset *set;

      set = itset_create_const (&text, ITSET_WIDTH_DEFAULT);
      itset_free (set);
    }
  CATCH (e, RETURN_MASK_ERROR)
    {
      return NULL;
    }
  END_CATCH

  if (*text != ' ')
    return NULL;
  text++;

  return command_completer (ignore, text, word);
}

/* Provide a prototype to silence -Wmissing-prototypes.  */
extern initialize_file_ftype _initialize_itset;

/* Commands with a prefix of `itset'.  */
static struct cmd_list_element *itset_cmd_list = NULL;

void
_initialize_itset (void)
{
  struct cmd_list_element *c = NULL;

  all_itset = itset_create_all ();
  empty_itset = itset_create_empty ();
  running_itset = itset_create_running ();
  stopped_itset = itset_create_stopped ();
  curinf_itset = itset_create_curinf ();
  curthr_itset = itset_create_curthr ();
  lockstep_itset = itset_create_lockstep ();

  make_internal_itset (all_itset, "all");
  make_internal_itset (empty_itset, "empty");
  make_internal_itset (running_itset, "running");
  make_internal_itset (stopped_itset, "stopped");
  make_internal_itset (curinf_itset, "I");
  make_internal_itset (curthr_itset, "T");
  make_internal_itset (lockstep_itset, "L");

  current_itset = itset_reference (itset_create_default ());
  //  current_itset = itset_reference (all_itset);

  c = add_com ("itfocus", no_class, itfocus_command, _("\
Change the set of current inferiors/threads."));
  set_cmd_completer (c, itfocus_completer);
  add_com_alias ("a", "itfocus", class_alias, 0);

  add_prefix_cmd ("itset", class_run, itset_command, _("\
Define a new named set.\n\
Usage: itset NAME SPEC"),
		  &itset_cmd_list, "itset ", 1, &cmdlist);

  add_cmd ("itset", class_trace, delete_itset_command, _("\
Delete one or more named itsets.\n\
Arguments may be numbers, number ranges, or an itset name to delete.\n\
If no arguments are supplied, delete all named itsets."), &deletelist);

  add_com ("whichsets", no_class, whichsets_command, _("\
List all sets to which threads in a given set belong to.\n\
Usage: whichsets SET.\n\
Defaults to the current set."));

  add_cmd ("itset", class_run, viewset_command, _("\
List the members of a set.\n\
Usage: viewset SET.\n\
Defaults to all named sets."),
	   &showlist);

  add_info ("itsets", info_itsets_command, _("\
Display the list of defined named itsets.\n\
You can specify numbers (e.g. \"info itsets 1 3\"),\n\
ranges (e.g. \"info itsets 4-8\"), or both (e.g. \"info itsets 1 3 4-8\").\n\n\
If you don't specify any numbers or ranges, we'll show all itsets.\n\n\
Usage: info itsets [NUMBERS AND/OR RANGES]\n"));

  add_cmd ("itsets", class_maintenance, maintenance_info_itsets_command, _("\
Display the list of all defined named itsets, user-defined and built-in.\n"),
  &maintenanceinfolist);
}
