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

/* FIXME */
char itset_get_focus_object_type (struct itset *set);

/* Rather than creating/destroying these dynamic itsets when
   necessary, keep global copies around (itsets are refcounted).  */
static struct itset *all_itset;
static struct itset *empty_itset;
static struct itset *running_itset;
static struct itset *stopped_itset;
static struct itset *curinf_itset;
static struct itset *curthr_itset;
static struct itset *lockstep_itset;

/* Forward declaration of the base class.  */
struct itset_elt;

/* Forward declaration of the base class for object ranges.  */
struct itset_elt_range;

/* An element of an I/T set is a class with some virtual methods,
   defined here.  */

struct itset_elt_vtable
{
  /* Destroy the contents of this element.  If the element does not
     require any special cleanup, this can be NULL.  This should not
     free the element itself; that is done by the caller.  */

  void (*destroy) (struct itset_elt *);

  /* Returns true if this is an itset_elt_range.  */

  int (*is_range_type) (struct itset_elt *);

  /* Return true if the element contains the program space.  The
     element and the program space are passed as arguments.  */

  int (*contains_program_space) (struct itset_elt *elt,
				 enum itset_width default_width,
				 struct program_space *pspace);

  /* Return true if the element contains the inferior.  The element
     and the inferior are passed as arguments.  */

  int (*contains_inferior) (struct itset_elt *elt,
			    enum itset_width default_width,
			    struct inferior *inf,
			    int including_width);

  /* Return true if the element contains the thread.  The element and
     the thread are passed as arguments.  */

  int (*contains_thread) (struct itset_elt *elt,
			  enum itset_width default_width,
			  struct itset_elt_range *expanding,
			  struct thread_info *thr,
			  int include_width);

  /* Return true if the element is empty.  */

  char *(*get_spec) (struct itset_elt *elt);

  /* Return true if the element is empty.  */

  enum itset_width (*get_width) (struct itset_elt *elt);

  /* Return the element's TOI.  */

  struct thread_info *(*get_toi) (struct itset_elt *elt);

  /* Return true if the element's TOI is fixed.  */

  int (*has_fixed_toi) (struct itset_elt *elt);

  /* Return the element's execution object type.  */

  char (*get_focus_object_type) (struct itset_elt *elt);

  /* Return a clone of ELT.  */

  struct itset_elt *(*clone) (struct itset_elt *elt);
};

/* The base class of all I/T set elements.  */

struct itset_elt
{
  const struct itset_elt_vtable *vtable;
};

static void
itset_elt_free (struct itset_elt *elt)
{
  if (elt->vtable->destroy != NULL)
    elt->vtable->destroy (elt);
  xfree (elt);
}

static void
itset_elt_free_cleanup (void *arg)
{
  struct itset_elt *elt = arg;

  itset_elt_free (elt);
}

static struct cleanup *
make_cleanup_itset_elt_free (struct itset_elt *elt)
{
  return make_cleanup (itset_elt_free_cleanup, elt);
}

typedef struct itset_elt *itset_elt_ptr;
DEF_VEC_P (itset_elt_ptr);

struct itset
{
  /* The itset's name.  May be NULL.  */
  char *name;

  /* The original specification of the set.  */
  char *spec;

  /* The reference count.  */
  int refc;

  /* The elements making up the set.  */
  VEC (itset_elt_ptr) *elements;
};

const char *
itset_name (const struct itset *itset)
{
  return itset->name;
}

int
itset_is_empty_set (struct itset *set)
{
  return VEC_empty (itset_elt_ptr, set->elements);
}



/* An element in the list of named itsets, which can be either
   debugger built-in (all, stopped, running, etc.), or user
   defined.  */

struct named_itset
{
  /* Pointer to next in linked list.  */
  struct named_itset *next;

  /* Unique identifier.  Positive if user defined, negative if
     internal and built-in.  */
  int number;

  /* The I/T set.  */
  struct itset *set;
};

/* The head of the list of named I/T sets.  */

static struct named_itset *named_itsets;

/* Number of last named itset made.  */

static int named_itset_count;

/* Number of last internal named itset made.  */

static int internal_named_itset_count;

/* Traverse all named itsets.  */

#define ALL_NAMED_ITSETS(E) \
  for ((E) = named_itsets; (E); (E) = (E)->next)

/* Add IT at the end of the named itset chain.  */

static void
add_to_named_itset_chain (struct named_itset *it)
{
  struct named_itset *it1;

  /* Add this itset to the end of the chain so that a list of itsets
     will come out in order of increasing numbers.  */

  it1 = named_itsets;
  if (it1 == 0)
    named_itsets = it;
  else
    {
      while (it1->next)
	it1 = it1->next;
      it1->next = it;
    }
}

static struct named_itset *
get_named_itset (char *name)
{
  struct named_itset *it;

  for (it = named_itsets; it != NULL; it = it->next)
    if (strcmp (it->set->name, name) == 0)
      return it;
  return NULL;
}



/* A helper function that returns true if the inferior INF is
   contained by the set ELEMENTS.  */

static int
set_contains_program_space (VEC (itset_elt_ptr) *elements,
			    enum itset_width default_width,
			    struct program_space *pspace)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      if (elt->vtable->contains_program_space (elt, default_width, pspace))
	return 1;
    }

  return 0;
}

/* A helper function that returns true if the inferior INF is
   contained by the set ELEMENTS.  */

static int
set_contains_inferior (VEC (itset_elt_ptr) *elements,
		       enum itset_width default_width,
		       struct inferior *inf,
		       int including_width)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      if (elt->vtable->contains_inferior (elt, default_width,
					  inf, including_width))
	return 1;
    }

  return 0;
}

/* A helper function that returns true if the thread THR is contained
   by the set ELEMENTS.  */

static int
set_contains_thread (VEC (itset_elt_ptr) *elements,
		     enum itset_width default_width,
		     struct thread_info *thr,
		     int including_width)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      if (elt->vtable->contains_thread (elt, default_width,
					NULL, thr, including_width))
	return 1;
    }

  return 0;
}

/* A helper function to destroy all the elements in the set ELEMENTS.
   This also destroys ELEMENTS itself.  */

static void
set_free (VEC (itset_elt_ptr) *elements)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    itset_elt_free (elt);

  VEC_free (itset_elt_ptr, elements);
}



/* An I/T set element representing all inferiors using a certain
   executable.  */

struct itset_elt_exec
{
  struct itset_elt base;

  /* The name of the executable.  */
  char *exec_name;
};

/* Implementation of `destroy' method.  */

static void
exec_destroy (struct itset_elt *base)
{
  struct itset_elt_exec *exec = (struct itset_elt_exec *) base;

  xfree (exec->exec_name);
}

/* Implementation of `contains_inferior' method.  */

static int
exec_contains_inferior (struct itset_elt *base,
			enum itset_width default_width,
			struct inferior *inf,
			int including_width)
{
  struct itset_elt_exec *exec = (struct itset_elt_exec *) base;

  /* FIXME: smarter compare.  */
  return (inf->pspace->ebfd != NULL
	  && strcmp (exec->exec_name,
		     bfd_get_filename (inf->pspace->ebfd)) == 0);
}

/* Implementation of `contains_thread' method.  */

static int
exec_contains_thread (struct itset_elt *base,
		      enum itset_width default_width,
		      struct itset_elt_range *expanding,
		      struct thread_info *thr,
		      int including_width)
{
  struct itset_elt_exec *exec = (struct itset_elt_exec *) base;
  struct inferior *inf = get_thread_inferior (thr);

  /* FIXME: smarter compare.  */
  return (inf->pspace->ebfd != NULL
	  && strcmp (exec->exec_name,
		     bfd_get_filename (inf->pspace->ebfd)) == 0);
}

static const struct itset_elt_vtable exec_vtable =
{
  exec_destroy,
  NULL, /* is_range_type */
  NULL, /* contains_program_space */
  exec_contains_inferior,
  exec_contains_thread,
  NULL,
};

/* Create a new `exec' I/T set element.  */

static struct itset_elt *
create_exec_itset (char *arg)
{
  struct itset_elt_exec *elt;

  elt = XNEW (struct itset_elt_exec);
  elt->base.vtable = &exec_vtable;
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

struct itset_elt_range
{
  struct itset_elt base;
  char object_type;
  enum itset_width width;

  /* If WIDTH is explicit, this is the width set, otherwise NULL.  */
  struct itset *explicit_width;

  /* The selected group, otherwise NULL.  */
  struct itset_elt *group;

  int is_current;
  /* The first and last in this range.  If FIRST is WILDCARD, then
     LAST is unused.  */
  struct spec_range range;
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

static void
range_elt_destroy (struct itset_elt *elt)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) elt;

  itset_free (range_elt->explicit_width);
}

static int
range_elt_is_range_type (struct itset_elt *elt)
{
  return 1;
}

static enum itset_width
range_get_width (struct itset_elt *base)
{
  struct itset_elt_range *range = (struct itset_elt_range *) base;

  return range->width;
}

static char
range_get_focus_object_type (struct itset_elt *base)
{
  struct itset_elt_range *range = (struct itset_elt_range *) base;

  return range->object_type;
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

static char *
range_elt_get_spec (struct itset_elt *base, int range_type_char)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct spec_range *range = &range_elt->range;
  int w;
  char *res = NULL;

  w = range_width_char (range_elt->width);

  if (range_elt->is_current)
    return xstrprintf ("%c%c", w, toupper (range_type_char));

  res = concat_printf (res, "%c%c", w, range_type_char);

  res = range_concat_spec (res, range);

  return res;
}

static char *itset_get_spec (const struct itset *set);

static char *
double_range_get_spec (struct itset_elt *base, int range_type_char,
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

      group_spec = range_elt->group->vtable->get_spec (range_elt->group);
      res = concat_printf (res, "/%s/", group_spec);
      xfree (group_spec);
    }

  if (range_elt->is_current)
    return concat_printf (res, "%c", toupper (range_type_char));

  res = concat_printf (res, "%c", range_type_char);
  res = range_concat_spec (res, inf_range);
  res = concat_printf (res, ".");
  res = range_concat_spec (res, range);

  return res;
}

/* An I/T set element representing a range of inferiors.  */

struct itset_elt_inferior_range
{
  struct itset_elt_range base;
};

/* Implementation of `contains_program_space' method.  */

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

static int
inferior_range_elt_contains_program_space (struct itset_elt *base,
					   enum itset_width default_width,
					   struct program_space *pspace)
{
  struct itset_elt_range *elt_range = (struct itset_elt_range *) base;
  enum itset_width width = effective_width (elt_range->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  return inferior_range_contains_program_space (&elt_range->range, pspace);
}

/* Implementation of `contains_inferior' method.  */

static int
inferior_range_contains_inferior (struct spec_range *range,
				  struct inferior *inf)
{
  if (range->first == WILDCARD
      || (range->first <= inf->num && inf->num <= range->last))
    return 1;

  return 0;
}

static int
inferior_range_elt_contains_inferior (struct itset_elt *base,
				      enum itset_width default_width,
				      struct inferior *inf,
				      int including_width)
{
  struct itset_elt_range *elt_range = (struct itset_elt_range *) base;
  enum itset_width width = effective_width (elt_range->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  return inferior_range_contains_inferior (&elt_range->range, inf);
}

/* Implementation of `contains_thread' method.  */

static int
inferior_range_elt_contains_thread (struct itset_elt *base,
				    enum itset_width default_width,
				    struct itset_elt_range *expanding,
				    struct thread_info *thr,
				    int including_width)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  enum itset_width width = effective_width (range_elt->width, default_width);
  struct inferior *inf;

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (range_elt->range.first == WILDCARD)
    return 1;

  if (range_elt->is_current)
    {
      inf = get_thread_inferior (thr);

      return (inf == get_current_context ()->inf);
    }

  inf = get_thread_inferior (thr);
  return inferior_range_contains_inferior (&range_elt->range, inf);
}

static char *
inferior_range_elt_get_spec (struct itset_elt *base)
{
  return range_elt_get_spec (base, 'i');
}

static struct thread_info *
inferior_range_elt_get_toi (struct itset_elt *base)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct spec_range *range = &range_elt->range;
  struct inferior *inf;

  if (range_elt->is_current)
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

static int
inferior_range_elt_has_fixed_toi (struct itset_elt *base)
{
  struct itset_elt_range *range = (struct itset_elt_range *) base;

  return !range->is_current;
}

static const struct itset_elt_vtable inferior_range_vtable =
{
  range_elt_destroy,
  range_elt_is_range_type,
  inferior_range_elt_contains_program_space,
  inferior_range_elt_contains_inferior,
  inferior_range_elt_contains_thread,
  inferior_range_elt_get_spec,
  range_get_width,
  inferior_range_elt_get_toi,
  inferior_range_elt_has_fixed_toi,
  range_get_focus_object_type,
};

/* Create a new `range' I/T set element.  */

static struct itset_elt_range *
create_inferior_range_itset (enum itset_width width,
			     int is_current,
			     struct spec_range *inf_range)
{
  struct itset_elt_inferior_range *inf_range_elt;
  struct itset_elt_range *range_elt;
  struct itset_elt *elt;

  inf_range_elt = XNEW (struct itset_elt_inferior_range);

  range_elt = &inf_range_elt->base;
  range_elt->range = *inf_range;
  range_elt->width = width;
  range_elt->is_current = is_current;
  range_elt->object_type = 'i';

  elt = &range_elt->base;
  elt->vtable = &inferior_range_vtable;

  return range_elt;
}



/* An I/T set element representing a range of threads.  */

struct itset_elt_thread_range
{
  struct itset_elt_range base;
  struct spec_range inf_range;
};

 /* Implementation of `contains_inferior' method.  */

static int
thread_range_contains_program_space (struct itset_elt *base,
				     enum itset_width default_width,
				     struct program_space *pspace)
{
  struct itset_elt_thread_range *thread_range
    = (struct itset_elt_thread_range *) base;
  struct itset_elt_range *range = (struct itset_elt_range *) base;
  enum itset_width width = effective_width (range->width, default_width);
  struct inferior *inf;
  struct thread_info *thr;

  if (width == ITSET_WIDTH_ALL)
    return 1;

  if (width == ITSET_WIDTH_EXPLICIT)
    {
      struct itset *ew = range->explicit_width;

      if (itset_contains_program_space (ew, default_width, pspace))
	return 1;
    }

  if (width == ITSET_WIDTH_GROUP)
    {
      if (range->group->vtable->contains_program_space (range->group,
							default_width, pspace))
	return 1;
    }

  if (range->is_current)
    return (get_current_context ()->inf->pspace == pspace);

  return inferior_range_contains_program_space (&thread_range->inf_range,
						pspace);
}

/* Implementation of `contains_inferior' method.  */

static int
thread_range_contains_inferior (struct itset_elt *base,
				enum itset_width default_width,
				struct inferior *inf,
				int including_width)
{
  struct itset_elt_thread_range *thread_range
    = (struct itset_elt_thread_range *) base;
  struct itset_elt_range *range = (struct itset_elt_range *) base;
  enum itset_width width = effective_width (range->width, default_width);

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (including_width && width == ITSET_WIDTH_EXPLICIT)
    {
      struct itset *ew = range->explicit_width;

      if (itset_width_contains_inferior (ew, default_width, inf))
	return 1;
    }

  if (including_width && width == ITSET_WIDTH_GROUP)
    {
      if (range->group->vtable->contains_inferior (range->group, default_width,
						   inf, including_width))
	return 1;
    }

  if (range->is_current)
    return (get_current_context ()->inf == inf);

  return inferior_range_contains_inferior (&thread_range->inf_range, inf);
}

/* Implementation of `contains_thread' method.  */

static int
thread_range_contains_thread (struct itset_elt *base,
			      enum itset_width default_width,
			      struct itset_elt_range *expanding,
			      struct thread_info *thr,
			      int including_width)
{
  struct itset_elt_thread_range *thread_range_elt
    = (struct itset_elt_thread_range *) base;
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct spec_range *range = &range_elt->range;
  enum itset_width width = effective_width (range_elt->width, default_width);
  struct inferior *inf;

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (including_width && width == ITSET_WIDTH_EXPLICIT)
    {
      struct itset *ew = range_elt->explicit_width;

      if (itset_contains_thread (ew, thr))
	return 1;
    }

  if (including_width && range_elt->width == ITSET_WIDTH_GROUP)
    {
      if (range_elt->group->vtable->contains_thread (range_elt->group,
						     default_width,
						     NULL, thr, 0))
	return 1;
    }

  if (range_elt->is_current)
    {
      struct inferior *inf = get_current_context ()->inf;

      thread_range_elt->inf_range.first = inf->num;
      thread_range_elt->inf_range.last = inf->num;
    }

  if (including_width && width == ITSET_WIDTH_INFERIOR)
    {
      inf = get_thread_inferior (thr);
      return inferior_range_contains_inferior (&thread_range_elt->inf_range,
					       inf);
    }

  if (range_elt->is_current)
    {
      struct thread_info *tp;

      tp = get_current_context_thread ();
      if (tp == NULL)
	return 0;

      range->first = tp->num;
      range->last = tp->num;
    }

  inf = get_thread_inferior (thr);
  if (inferior_range_contains_inferior (&thread_range_elt->inf_range, inf)
      && (range->first == WILDCARD
	  || (range->first <= thr->num_inf && thr->num_inf <= range->last)))
    return 1;

  /* This range does not select this thread.  Check if the expander
     does though.  */
  if (/* FIXME: If the expander is calling us again, don't re-expand,
	 leading to infinite recursion.  Maybe we should have a
	 separate flag for this?  */
      expanding != range_elt
      && range_elt->group != NULL)
    {
      if ((including_width || base->vtable->contains_thread (base,
							     default_width,
							     NULL, thr, 1))
	  && range_elt->group->vtable->contains_thread (range_elt->group,
							default_width,
							range_elt,
							thr, 0))
	return 1;
    }

  return 0;
}

static char *
thread_range_get_spec (struct itset_elt *base)
{
  struct itset_elt_thread_range *thread_range
    = (struct itset_elt_thread_range *) base;

  return double_range_get_spec (base, 't', &thread_range->inf_range);
}

static struct thread_info *
thread_range_get_toi (struct itset_elt *base)
{
  struct itset_elt_thread_range *thread_range_elt
    = (struct itset_elt_thread_range *) base;
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct spec_range *range = &range_elt->range;
  struct thread_info *thr;

  if (range_elt->is_current)
    return get_current_context_thread ();

  ALL_NON_EXITED_THREADS (thr)
    {
      if (range->first == WILDCARD
	  || (range->first <= thr->num && thr->num <= range->last))
	{
	  struct inferior *inf;

	  inf = get_thread_inferior (thr);
	  if (inferior_range_contains_inferior (&thread_range_elt->inf_range,
						inf))
	    return thr;
	}
    }

  return NULL;
}

static int
thread_range_has_fixed_toi (struct itset_elt *base)
{
  struct itset_elt_range *range = (struct itset_elt_range *) base;

  return !range->is_current;
}

static struct itset_elt_range *
  create_thread_range_itset (enum itset_width width,
			     int is_current,
			     struct spec_range *inf_range,
			     struct spec_range *thr_range);

static struct itset_elt *
thread_range_clone (struct itset_elt *base)
{
  struct itset_elt_thread_range *thread_range_elt
    = (struct itset_elt_thread_range *) base;
  struct itset_elt_range *range = (struct itset_elt_range *) base;
  struct itset_elt_range *clone;

  clone = create_thread_range_itset (range->width,
				     range->is_current,
				     &thread_range_elt->inf_range,
				     &range->range);

  if (range->explicit_width != NULL)
    clone->explicit_width
      = itset_reference (range->explicit_width);
  else
    clone->explicit_width = NULL;

  /* FIXME */
  clone->group = NULL;

  return &clone->base;
}

static const struct itset_elt_vtable thread_range_vtable =
{
  NULL,
  range_elt_is_range_type,
  thread_range_contains_program_space,
  thread_range_contains_inferior,
  thread_range_contains_thread,
  thread_range_get_spec,
  range_get_width,
  thread_range_get_toi,
  thread_range_has_fixed_toi,
  range_get_focus_object_type,
  thread_range_clone,
};

/* Create a new `range' I/T set element.  */

static struct itset_elt_range *
create_thread_range_itset (enum itset_width width, int is_current,
			   struct spec_range *inf_range,
			   struct spec_range *thr_range)
{
  struct itset_elt_thread_range *thr_range_elt;
  struct itset_elt_range *range_elt;
  struct itset_elt *elt;

  thr_range_elt = XNEW (struct itset_elt_thread_range);
  thr_range_elt->inf_range = *inf_range;

  range_elt = &thr_range_elt->base;
  range_elt->range = *thr_range;
  range_elt->width = width;
  range_elt->explicit_width = NULL;
  range_elt->group = NULL;
  range_elt->is_current = is_current;
  range_elt->object_type = 't';

  elt = &range_elt->base;
  elt->vtable = &thread_range_vtable;

  return range_elt;
}



/* An I/T set element representing a range of cores.  */

struct itset_elt_core_range
{
  struct itset_elt_range base;
};

static int core_range_contains_thread (struct itset_elt *base,
				       enum itset_width default_width,
				       struct itset_elt_range *expanding,
				       struct thread_info *thr,
				       int including_width);

 /* Implementation of `contains_inferior' method.  */

static int
core_range_contains_program_space (struct itset_elt *base,
				   enum itset_width default_width,
				   struct program_space *pspace)
{
  struct thread_info *thr;

  /* True if we find a thread of an inferior associated with PSPACE
     that is running on our core range.  */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the core range first, because looking
	 up the a thread's inferior is O(n).  */
      if (core_range_contains_thread (base, default_width, NULL, thr, 1))
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

static int
core_range_contains_thread (struct itset_elt *base,
			    enum itset_width default_width,
			    struct itset_elt_range *expanding,
			    struct thread_info *thr,
			    int including_width)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct spec_range *range = &range_elt->range;
  int core;

  if (range->first == WILDCARD)
    return 1;

  core = target_core_of_thread (thr->ptid);
  if (range->first <= core && core <= range->last)
    return 1;

  return 0;
}

/* Implementation of `contains_inferior' method.  */

static int
core_range_contains_inferior (struct itset_elt *base,
			      enum itset_width default_width,
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
      if (core_range_contains_thread (base, default_width, NULL, thr, 1))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf == inf)
	    return 1;
	}
    }

  return 0;
}

static char *
core_range_get_spec (struct itset_elt *base)
{
  return range_elt_get_spec (base, 'c');
}

static struct thread_info *
core_range_get_toi (struct itset_elt *base)
{
  struct itset_elt_range *range = (struct itset_elt_range *) base;
  struct thread_info *thr;

  if (range->is_current)
    return get_current_context_thread ();

  ALL_NON_EXITED_THREADS (thr)
    {
      if (core_range_contains_thread (base, ITSET_WIDTH_THREAD, NULL, thr, 0))
	return thr;
    }

  return NULL;
}

static int
core_range_has_fixed_toi (struct itset_elt *base)
{
  struct itset_elt_range *range = (struct itset_elt_range *) base;

  return !range->is_current;
}


static const struct itset_elt_vtable core_range_vtable =
{
  NULL,
  range_elt_is_range_type,
  core_range_contains_program_space,
  core_range_contains_inferior,
  core_range_contains_thread,
  core_range_get_spec,
  range_get_width,
  core_range_get_toi,
  core_range_has_fixed_toi,
  range_get_focus_object_type,
};

/* Create a new `core_range' I/T set element.  */

static struct itset_elt_range *
create_core_range_itset (enum itset_width width, int is_current,
			 struct spec_range *core_range)
{
  struct itset_elt_core_range *core_range_elt;
  struct itset_elt_range *range_elt;
  struct itset_elt *elt;

  core_range_elt = XNEW (struct itset_elt_core_range);

  range_elt = &core_range_elt->base;
  range_elt->range = *core_range;
  range_elt->width = width;
  range_elt->is_current = is_current;
  range_elt->object_type = 'c';

  elt = &range_elt->base;
  elt->vtable = &core_range_vtable;

  return range_elt;
}


/* An I/T set element representing a range of Ada tasks.  */

struct itset_elt_ada_task_range
{
  struct itset_elt_range base;
  struct spec_range inf_range;
};

 /* Implementation of `contains_program_space' method.  */

static int
ada_task_range_contains_program_space (struct itset_elt *base,
				       enum itset_width default_width,
				       struct program_space *pspace)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct itset_elt_ada_task_range *ada_task_range_elt
    = (struct itset_elt_ada_task_range *) base;
  enum itset_width width = effective_width (range_elt->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  if (range_elt->is_current)
    return (get_current_context ()->inf->pspace == pspace);

  return inferior_range_contains_program_space (&ada_task_range_elt->inf_range,
						pspace);
}

/* Implementation of `contains_inferior' method.  */

static int
ada_task_range_contains_inferior (struct itset_elt *base,
				  enum itset_width default_width,
				  struct inferior *inf,
				  int including_width)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct itset_elt_ada_task_range *ada_task_range_elt
    = (struct itset_elt_ada_task_range *) base;
  enum itset_width width = effective_width (range_elt->width, default_width);

  if (width == ITSET_WIDTH_ALL)
    return 1;

  if (range_elt->is_current)
    return (get_current_context ()->inf == inf);

  return inferior_range_contains_inferior (&ada_task_range_elt->inf_range,
					   inf);
}

/* Implementation of `contains_thread' method.  */

static int
ada_task_range_contains_thread (struct itset_elt *base,
				enum itset_width default_width,
				struct itset_elt_range *expanding,
				struct thread_info *thr,
				int including_width)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct itset_elt_ada_task_range *ada_task_range_elt
    = (struct itset_elt_ada_task_range *) base;
  enum itset_width width = effective_width (range_elt->width, default_width);
  struct spec_range *range = &range_elt->range;
  struct inferior *inf;
  int thr_task;

  if (including_width && width == ITSET_WIDTH_ALL)
    return 1;

  if (range_elt->is_current)
    {
      struct execution_context *ctx = get_current_context ();

      ada_task_range_elt->inf_range.first = ctx->inf->num;
      ada_task_range_elt->inf_range.last = ctx->inf->num;
    }

  if (including_width && width == ITSET_WIDTH_INFERIOR)
    {
      inf = get_thread_inferior (thr);
      return inferior_range_contains_inferior (&ada_task_range_elt->inf_range,
					       inf);
    }

  if (range_elt->is_current)
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
  if (!inferior_range_contains_inferior (&ada_task_range_elt->inf_range, inf))
    return 0;

  if (range->first == WILDCARD)
    return 1;

  thr_task = ada_get_task_number (thr->ptid);
  if (thr_task != 0
      && range->first <= thr_task && thr_task <= range->last)
    return 1;

  return 0;
}

static char *
ada_task_range_get_spec (struct itset_elt *base)
{
  struct itset_elt_ada_task_range *ada_task_range_elt
    = (struct itset_elt_ada_task_range *) base;

  return double_range_get_spec (base, 'k', &ada_task_range_elt->inf_range);
}

static struct thread_info *
ada_task_range_get_toi (struct itset_elt *base)
{
  struct itset_elt_range *range_elt = (struct itset_elt_range *) base;
  struct itset_elt_ada_task_range *ada_task_range_elt
    = (struct itset_elt_ada_task_range *) base;
  struct spec_range *range = &range_elt->range;
  struct inferior *inf;

  if (range_elt->is_current)
    return get_current_context_thread ();

  ALL_INFERIORS (inf)
    {
      struct ada_task_info *task_info;
      VEC(ada_task_info_s) *task_list;
      struct thread_info *thr;

      if (!inferior_range_contains_inferior (&ada_task_range_elt->inf_range,
					     inf))
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

static int
ada_task_range_has_fixed_toi (struct itset_elt *base)
{
  struct itset_elt_range *range = (struct itset_elt_range *) base;

  return !range->is_current;
}

static const struct itset_elt_vtable ada_task_range_vtable =
{
  NULL,
  range_elt_is_range_type,
  ada_task_range_contains_program_space,
  ada_task_range_contains_inferior,
  ada_task_range_contains_thread,
  ada_task_range_get_spec,
  range_get_width,
  ada_task_range_get_toi,
  ada_task_range_has_fixed_toi,
  range_get_focus_object_type,
};

/* Create a new `range' I/T set element.  */

static struct itset_elt_range *
create_ada_task_range_itset (enum itset_width width, int is_current,
			     struct spec_range *inf_range,
			     struct spec_range *ada_range)
{
  struct itset_elt_ada_task_range *ada_range_elt;
  struct itset_elt_range *range_elt;
  struct itset_elt *elt;

  ada_range_elt = XNEW (struct itset_elt_ada_task_range);
  ada_range_elt->inf_range = *inf_range;

  range_elt = &ada_range_elt->base;
  range_elt->range = *ada_range;
  range_elt->width = width;
  range_elt->is_current = is_current;
  range_elt->object_type = 'k';

  elt = &range_elt->base;
  elt->vtable = &ada_task_range_vtable;

  return range_elt;
}

static const char *parse_range (const char *spec, struct spec_range *range);

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

struct itset_elt_intersect
{
  struct itset_elt base;

  /* The elements that will be intersected.  */
  VEC (itset_elt_ptr) *elements;
};

/* Implementation of `destroy' method.  */

static void
intersect_destroy (struct itset_elt *base)
{
  struct itset_elt_intersect *set = (struct itset_elt_intersect *) base;

  VEC_free (itset_elt_ptr, set->elements);
}

/* Implementation of `contains_inferior' method.  */

static int
intersect_contains_inferior (struct itset_elt *base,
			     enum itset_width default_width,
			     struct inferior *inf,
			     int including_width)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;
  struct itset_elt *elt;
  int ix;

  gdb_assert (!VEC_empty (itset_elt_ptr, intersect->elements));

  for (ix = 0; VEC_iterate (itset_elt_ptr, intersect->elements, ix, elt); ++ix)
    {
      if (!elt->vtable->contains_inferior (elt, default_width,
					   inf, including_width))
	return 0;
    }

  return 1;
}

/* Implementation of `contains_thread' method.  */

static int
intersect_contains_thread (struct itset_elt *base,
			   enum itset_width default_width,
			   struct itset_elt_range *expanding,
			   struct thread_info *thr,
			   int including_width)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;
  struct itset_elt *elt;
  int ix;

  gdb_assert (!VEC_empty (itset_elt_ptr, intersect->elements));

  for (ix = 0; VEC_iterate (itset_elt_ptr, intersect->elements, ix, elt); ++ix)
    {
      if (!elt->vtable->contains_thread (elt, default_width,
					 expanding, thr, including_width))
	return 0;
    }

  return 1;
}

static char *
intersect_get_spec (struct itset_elt *base)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;
  struct itset_elt *elt;
  int ix;
  char *ret = NULL;

  gdb_assert (!VEC_empty (itset_elt_ptr, intersect->elements));

  for (ix = 0; VEC_iterate (itset_elt_ptr, intersect->elements, ix, elt); ++ix)
    {
      const char *elt_spec = elt->vtable->get_spec (elt);

      ret = reconcat (ret, ret == NULL ? "" : ret,
		      ix == 0 ? "" : "&", elt_spec, (char *) NULL);
    }

  return ret;
}

static enum itset_width set_get_width (VEC (itset_elt_ptr) *elements);
static struct thread_info *set_get_toi (VEC (itset_elt_ptr) *elements);
static int set_has_fixed_toi (VEC (itset_elt_ptr) *elements);

static enum itset_width
intersect_get_width (struct itset_elt *base)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;

  return set_get_width (intersect->elements);
}

static struct thread_info *
intersect_get_toi (struct itset_elt *base)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;

  return set_get_toi (intersect->elements);
}

static int
intersect_has_fixed_toi (struct itset_elt *base)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;

  return set_has_fixed_toi (intersect->elements);
}

static const struct itset_elt_vtable intersect_vtable =
{
  intersect_destroy,
  NULL, /* is_range_type */
  NULL, /* contains_program_space */
  intersect_contains_inferior,
  intersect_contains_thread,
  intersect_get_spec,
  intersect_get_width,
  intersect_get_toi,
  intersect_has_fixed_toi,
};

/* Create a new `intersect' I/T set element.  */

static struct itset_elt_intersect *
create_intersect_itset (void)
{
  struct itset_elt_intersect *elt;

  elt = XNEW (struct itset_elt_intersect);
  elt->base.vtable = &intersect_vtable;
  elt->elements = NULL;

  return elt;
}



/* An I/T set element representing all inferiors.  */

struct itset_elt_all
{
  struct itset_elt base;
};

/* Implementation of `contains_inferior' method.  */

static int
all_contains_program_space (struct itset_elt *base,
			    enum itset_width default_width,
			    struct program_space *pspace)
{
  return 1;
}

/* Implementation of `contains_inferior' method.  */

static int
all_contains_inferior (struct itset_elt *base,
		       enum itset_width default_width,
		       struct inferior *inf,
		       int including_width)
{
  return 1;
}

/* Implementation of `contains_thread' method.  */

static int
all_contains_thread (struct itset_elt *base,
		     enum itset_width default_width,
		     struct itset_elt_range *expanding,
		     struct thread_info *thr,
		     int including_width)
{
  return 1;
}

static char *
all_get_spec (struct itset_elt *base)
{
  return xstrdup ("all");
}

static enum itset_width
all_get_width (struct itset_elt *base)
{
  return ITSET_WIDTH_ALL;
}

static int
has_fixed_toi_false (struct itset_elt *base)
{
  return 0;
}

static const struct itset_elt_vtable all_vtable =
{
  NULL,
  NULL, /* is_range_type */
  all_contains_program_space,
  all_contains_inferior,
  all_contains_thread,
  all_get_spec,
  all_get_width,
  NULL,
  has_fixed_toi_false
};

static struct itset_elt *
create_all_itset (void)
{
  struct itset_elt_all *elt;

  elt = XNEW (struct itset_elt_all);
  elt->base.vtable = &all_vtable;

  return (struct itset_elt *) elt;
}



/* An I/T set element representing no inferiors.  */

struct itset_elt_empty
{
  struct itset_elt base;
};

/* Implementation of `contains_program_space' method.  */

static int
empty_contains_program_space (struct itset_elt *base,
			      enum itset_width default_width,
			      struct program_space *pspace)
{
  return 0;
}

/* Implementation of `contains_inferior' method.  */

static int
empty_contains_inferior (struct itset_elt *base,
			 enum itset_width default_width,
			 struct inferior *inf,
			 int including_width)
{
  return 0;
}

/* Implementation of `contains_thread' method.  */

static int
empty_contains_thread (struct itset_elt *base,
		       enum itset_width default_width,
		       struct itset_elt_range *expanding,
		       struct thread_info *thr,
		       int including_width)
{
  return 0;
}

static const struct itset_elt_vtable empty_vtable =
{
  NULL,
  NULL, /* is_range_type */
  empty_contains_program_space,
  empty_contains_inferior,
  empty_contains_thread,
};

static struct itset_elt *
create_empty_itset (void)
{
  struct itset_elt_empty *elt;

  elt = XNEW (struct itset_elt_empty);
  elt->base.vtable = &empty_vtable;

  return (struct itset_elt *) elt;
}



/* An I/T set element representing an itset.  */

struct itset_elt_itset
{
  struct itset_elt base;

  /* The I/T set this element wraps.  */
  struct itset *set;
};

static void
itset_elt_itset_destroy (struct itset_elt *base)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  itset_free (iiset->set);
}

/* Implementation of `contains_program_space' method.  */

static int
itset_elt_itset_contains_program_space (struct itset_elt *base,
					enum itset_width default_width,
					struct program_space *pspace)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  return itset_contains_program_space (iiset->set, default_width, pspace);
}

static int
itset_contains_inferior_1 (struct itset *set,
			   enum itset_width default_width,
			   struct inferior *inf,
			   int including_width);

/* Implementation of `contains_inferior' method.  */

static int
itset_elt_itset_contains_inferior (struct itset_elt *base,
				   enum itset_width default_width,
				   struct inferior *inf,
				   int including_width)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  return itset_contains_inferior_1 (iiset->set, default_width,
				    inf, including_width);
}

/* Implementation of `contains_thread' method.  */

static int
itset_elt_itset_contains_thread (struct itset_elt *base,
				 enum itset_width default_width,
				 struct itset_elt_range *expanding,
				 struct thread_info *thr,
				 int including_width)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  if (including_width)
    return itset_width_contains_thread (iiset->set, default_width,
					thr);
  else
    return itset_contains_thread (iiset->set, thr);
}

static char *
itset_elt_itset_get_spec (struct itset_elt *base)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  if (iiset->set->name != NULL)
    return xstrdup (iiset->set->name);

  return itset_get_spec (iiset->set);
}

static enum itset_width
itset_elt_itset_get_width (struct itset_elt *base)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  return itset_get_width (iiset->set);
}

static struct thread_info *
itset_elt_itset_get_toi (struct itset_elt *base)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  return itset_get_toi (iiset->set);
}

static int
itset_elt_itset_has_fixed_toi (struct itset_elt *base)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;

  return itset_has_fixed_toi (iiset->set);
}

static const struct itset_elt_vtable itset_elt_itset_vtable =
{
  itset_elt_itset_destroy,
  NULL, /* is_range_type */
  itset_elt_itset_contains_program_space,
  itset_elt_itset_contains_inferior,
  itset_elt_itset_contains_thread,
  itset_elt_itset_get_spec,
  itset_elt_itset_get_width,
  itset_elt_itset_get_toi,
  itset_elt_itset_has_fixed_toi,
};

static struct itset_elt_itset *
create_itset_elt_itset (struct itset *set)
{
  struct itset_elt_itset *elt;

  elt = XNEW (struct itset_elt_itset);
  elt->base.vtable = &itset_elt_itset_vtable;
  elt->set = itset_reference (set);

  return elt;
}

void
itset_add_set (struct itset *to, struct itset *addme)
{
  struct itset_elt *elt;

  elt = (struct itset_elt *) create_itset_elt_itset (addme);
  VEC_safe_push (itset_elt_ptr, to->elements, elt);
}



/* An I/T set element representing a negated set.  */

struct itset_elt_negated
{
  struct itset_elt base;

  /* The negated element.  */
  struct itset_elt *negated;
};

static void
itset_elt_negated_destroy (struct itset_elt *base)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;

  itset_elt_free (elt->negated);
}

/* Implementation of `contains_inferior' method.  */

static int
itset_elt_negated_contains_inferior (struct itset_elt *base,
				     enum itset_width default_width,
				     struct inferior *inf,
				     int including_width)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;
  return !elt->negated->vtable->contains_inferior (elt->negated, default_width,
						   inf, including_width);
}

/* Implementation of `contains_thread' method.  */

static int
itset_elt_negated_contains_thread (struct itset_elt *base,
				   enum itset_width default_width,
				   struct itset_elt_range *expanding,
				   struct thread_info *thr,
				   int including_width)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;

  if (elt->negated->vtable->contains_thread (elt->negated, default_width,
					     NULL, thr, 1))
    {
      return !elt->negated->vtable->contains_thread (elt->negated,
						     default_width,
						     NULL, thr,
						     including_width);
    }
  return 0;

  if (!including_width)
    return !elt->negated->vtable->contains_thread (elt->negated, default_width,
						   NULL, thr, 0);
  else
    return (elt->negated->vtable->contains_thread (elt->negated, default_width,
						   NULL, thr, 1)
	    && !elt->negated->vtable->contains_thread (elt->negated,
						       default_width,
						       NULL, thr,
						       including_width));
}

static char *
itset_elt_negated_get_spec (struct itset_elt *base)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;

  return xstrprintf ("~%s", elt->negated->vtable->get_spec (elt->negated));
}

static enum itset_width
itset_elt_negated_get_width (struct itset_elt *base)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;

  return elt->negated->vtable->get_width (elt->negated);
}

static struct thread_info *
itset_elt_negated_get_toi (struct itset_elt *base)
{
  struct thread_info *thr;

  ALL_THREADS (thr)
    {
      if (itset_elt_negated_contains_thread (base, ITSET_WIDTH_THREAD,
					     NULL, thr, 0))
	return thr;
    }
  return NULL;
}

static int
itset_elt_negated_has_fixed_toi (struct itset_elt *base)
{
  return 0;
}

static const struct itset_elt_vtable itset_elt_negated_vtable =
{
  itset_elt_negated_destroy,
  NULL, /* is_range_type */
  NULL, /* contains_program_space */
  itset_elt_negated_contains_inferior,
  itset_elt_negated_contains_thread,
  itset_elt_negated_get_spec,
  itset_elt_negated_get_width,
  itset_elt_negated_get_toi,
  itset_elt_negated_has_fixed_toi,
};

static struct itset_elt_negated *
create_itset_elt_negated (void)
{
  struct itset_elt_negated *elt;

  elt = XNEW (struct itset_elt_negated);
  elt->base.vtable = &itset_elt_negated_vtable;
  elt->negated = NULL;

  return elt;
}



/* An I/T set element representing all inferiors of a given state.  */

struct itset_elt_state
{
  struct itset_elt base;

  enum thread_state state;
};

/* Implementation of `contains_thread' method.  */

static int
state_contains_thread (struct itset_elt *base,
		       enum itset_width default_width,
		       struct itset_elt_range *expanding,
		       struct thread_info *thr,
		       int including_width)
{
  struct itset_elt_state *state = (struct itset_elt_state *) base;

  return thr->state == state->state;
}

#if 0
 /* Implementation of `contains_inferior' method.  */

static int
state_contains_program_space (struct itset_elt *base,
			      struct program_space *pspace)
{
  struct itset_elt_state *state = (struct itset_elt_state *) base;
  struct thread_info *thr;

  /* True if we find a thread of this inferior that is in the state
     we're interested in.  */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the state first, because looking up the
	 a thread's inferior is O(n).  */
      if (state_contains_thread (base, thr))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf == inf)
	    return 1;
	}
    }

  return 0;
}
#endif

/* Implementation of `contains_inferior' method.  */

static int
state_contains_inferior (struct itset_elt *base,
			 enum itset_width default_width,
			 struct inferior *inf,
			 int including_width)
{
  struct itset_elt_state *state = (struct itset_elt_state *) base;
  struct thread_info *thr;

  /* True if we find a thread of this inferior that is in the state
     we're interested in.  */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the state first, because looking up the
	 a thread's inferior is O(n).  */
      if (state_contains_thread (base, default_width, NULL, thr, 1))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf == inf)
	    return 1;
	}
    }

  return 0;
}

static char *
state_get_spec (struct itset_elt *base)
{
  struct itset_elt_state *state = (struct itset_elt_state *) base;

  switch (state->state)
    {
    case THREAD_RUNNING:
      return xstrdup ("running");
    case THREAD_STOPPED:
      return xstrdup ("stopped");
    }

  gdb_assert_not_reached ("unhandled state");
}

static const struct itset_elt_vtable state_vtable =
{
  NULL,
  NULL, /* is_range_type */
  NULL, /* contains_program_space */
  state_contains_inferior,
  state_contains_thread,
  state_get_spec
};

static struct itset_elt *
create_state_itset (enum thread_state thread_state)
{
  struct itset_elt_state *elt;

  elt = XNEW (struct itset_elt_state);
  elt->base.vtable = &state_vtable;
  elt->state = thread_state;

  return (struct itset_elt *) elt;
}



/* Implementation of `contains_program_space' method.  */

static int
curinf_contains_program_space (struct itset_elt *base,
			       enum itset_width default_width,
			       struct program_space *pspace)
{
  return current_inferior ()->pspace == pspace;
}

/* Implementation of `contains_inferior' method.  */

static int
curinf_contains_inferior (struct itset_elt *base,
			  enum itset_width default_width,
			  struct inferior *inf,
			  int including_width)
{
  return current_inferior () == inf;
}

/* Implementation of `contains_thread' method.  */

static int
curinf_contains_thread (struct itset_elt *base,
			enum itset_width default_width,
			struct itset_elt_range *expanding,
			struct thread_info *thr,
			int including_width)
{
  struct inferior *inf;

  inf = get_thread_inferior (thr);
  return current_inferior () == inf;
}

static char *
curinf_get_spec (struct itset_elt *base)
{
  return xstrdup ("current");
}

static const struct itset_elt_vtable curinf_vtable =
{
  NULL,
  NULL, /* is_range_type */
  curinf_contains_program_space,
  curinf_contains_inferior,
  curinf_contains_thread,
  curinf_get_spec
};

/* Create a new I/T set element representing just the current
   inferior.  */

static struct itset_elt *
create_curinf_itset (void)
{
  struct itset_elt *elt;

  elt = XNEW (struct itset_elt);
  elt->vtable = &curinf_vtable;

  return elt;
}



/* Implementation of `contains_program_space' method.  */

static int
curthr_contains_program_space (struct itset_elt *base,
			       enum itset_width default_width,
			       struct program_space *pspace)
{
  return current_inferior ()->pspace == pspace;
}

/* Implementation of `contains_inferior' method.  */

static int
curthr_contains_inferior (struct itset_elt *base,
			  enum itset_width default_width,
			  struct inferior *inf,
			  int including_width)
{
  return current_inferior () == inf;
}

/* Implementation of `contains_thread' method.  */

static int
curthr_contains_thread (struct itset_elt *base,
			enum itset_width default_width,
			struct itset_elt_range *expanding,
			struct thread_info *thr,
			int including_width)
{
  return ptid_equal (inferior_ptid, thr->ptid);
}

static const struct itset_elt_vtable curthr_vtable =
{
  NULL,
  NULL, /* is_range_type */
  curthr_contains_program_space,
  curthr_contains_inferior,
  curthr_contains_thread,
};

/* Create a new I/T set element representing just the current
   inferior.  */

static struct itset_elt *
create_curthr_itset (void)
{
  struct itset_elt *elt;

  elt = XNEW (struct itset_elt);
  elt->vtable = &curthr_vtable;

  return elt;
}




/* Implementation of `contains_program_space' method.  */

static int
lockstep_contains_program_space (struct itset_elt *base,
				 enum itset_width default_width,
				 struct program_space *pspace)
{
  return current_inferior ()->pspace == pspace;
}

/* Implementation of `contains_inferior' method.  */

static int
lockstep_contains_inferior (struct itset_elt *base,
			    enum itset_width default_width,
			    struct inferior *inf,
			    int including_width)
{
  return current_inferior () == inf;
}

/* Implementation of `contains_thread' method.  */

static int
lockstep_contains_thread (struct itset_elt *base,
			  enum itset_width default_width,
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
      if (expanding->base.vtable->contains_thread (&expanding->base,
						   default_width,
						   expanding, iter, 0))
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

static char *
lockstep_get_spec (struct itset_elt *base)
{
  return xstrdup ("L");
}

static const struct itset_elt_vtable lockstep_vtable =
{
  NULL,
  NULL, /* is_range_type */
  lockstep_contains_program_space,
  lockstep_contains_inferior,
  lockstep_contains_thread,
  lockstep_get_spec,
  NULL, /* get_width */
  NULL, /* get_toi */
  NULL, /* has_fixed_toi */
  NULL, /* get_focus_object_type */
  NULL, /* clone */
};

/* Create a new I/T set element representing just the current
   inferior.  */

static struct itset_elt *
create_lockstep_itset (void)
{
  struct itset_elt *elt;

  elt = XNEW (struct itset_elt);
  elt->vtable = &lockstep_vtable;

  return elt;
}



/* An I/T set element representing a static list of inferiors.  */

struct itset_elt_static
{
  struct itset_elt base;

  /* The inferiors.  */
  VEC (int) *inferiors;

  /* The threads.  */
  VEC (int) *threads;
};

/* Implementation of `destroy' method.  */

static void
static_destroy (struct itset_elt *base)
{
  struct itset_elt_static *st = (struct itset_elt_static *) base;

  VEC_free (int, st->inferiors);
  VEC_free (int, st->threads);
}

/* Helper function to compare two ints.  Returns true if the first
   argument is strictly less than the second, useful for
   VEC_lower_bound.  */

static int
static_lessthan (const int a, const int b)
{
  return a < b;
}

/* Implementation of `contains_inferior' method.  */

static int
static_contains_program_space (struct itset_elt *base,
			       enum itset_width default_width,
			       struct program_space *pspace)
{
  struct itset_elt_static *st = (struct itset_elt_static *) base;
  int idx, inf_num;

  for (idx = 0; VEC_iterate (int, st->inferiors, idx, inf_num); ++idx)
    {
      struct inferior *inf = find_inferior_id (inf_num);

      if (inf->pspace == pspace)
	return 1;
    }

  return 0;
}

/* Implementation of `contains_inferior' method.  */

static int
static_contains_inferior (struct itset_elt *base,
			  enum itset_width default_width,
			  struct inferior *inf,
			  int including_width)
{
  struct itset_elt_static *st = (struct itset_elt_static *) base;
  int idx;

  idx = VEC_lower_bound (int, st->inferiors, inf->num, static_lessthan);
  if (idx < VEC_length (int, st->inferiors)
      && VEC_index (int, st->inferiors, idx) == inf->num)
    return 1;
  return 0;
}

/* Implementation of `contains_thread' method.  */

static int
static_contains_thread (struct itset_elt *base,
			enum itset_width default_width,
			struct itset_elt_range *expanding,
			struct thread_info *thr,
			int including_width)
{
  struct itset_elt_static *st = (struct itset_elt_static *) base;
  int idx;

  idx = VEC_lower_bound (int, st->threads, thr->num, static_lessthan);
  if (idx < VEC_length (int, st->threads)
      && VEC_index (int, st->threads, idx) == thr->num)
    return 1;
  return 0;
}

static const struct itset_elt_vtable static_vtable =
{
  static_destroy,
  NULL, /* is_range_type */
  static_contains_program_space,
  static_contains_inferior,
  static_contains_thread,
};



/* Helper struct used to pass data through iterate_over_inferiors.  */

struct iter_data
{
  /* The I/T set we are constructing.  */

  struct itset_elt_static *st;

  /* The elements of the original (dynamic) I/T set.  */

  VEC (itset_elt_ptr) *elements;

  /* The default width.  */
  enum itset_width default_width;
};

/* A callback for iterate_over_inferiors that adds an inferior to the
   result set, if it is in the source set.  */

static int
check_one_inferior (struct inferior *inf, void *datum)
{
  struct iter_data *id = datum;

  if (set_contains_inferior (id->elements, id->default_width, inf, 1))
    VEC_safe_push (int, id->st->inferiors, inf->num);

  /* Keep going.  */
  return 0;
}

/* A callback for iterate_over_threads that adds a thread to the
   result set, if it is in the source set.  */

static int
check_one_thread (struct thread_info *thr, void *datum)
{
  struct iter_data *id = datum;

  if (set_contains_thread (id->elements, id->default_width, thr, 1))
    VEC_safe_push (int, id->st->threads, thr->num);

  /* Keep going.  */
  return 0;
}

/* Create a new static I/T set from the list of elements.  */

static struct itset_elt *
create_static_itset (VEC (itset_elt_ptr) *elements)
{
  struct itset_elt_static *elt;
  struct iter_data datum;

  elt = XNEW (struct itset_elt_static);
  elt->base.vtable = &static_vtable;
  elt->inferiors = NULL;
  elt->threads = NULL;

  datum.st = elt;
  datum.elements = elements;

  iterate_over_inferiors (check_one_inferior, &datum);
  if (VEC_length (int, elt->inferiors) > 1)
    qsort (VEC_address (int, elt->inferiors),
	   VEC_length (int, elt->inferiors),
	   sizeof (int), compare_positive_ints);

  iterate_over_threads (check_one_thread, &datum);
  if (VEC_length (int, elt->threads) > 1)
    qsort (VEC_address (int, elt->threads),
	   VEC_length (int, elt->threads),
	   sizeof (int), compare_positive_ints);

  return (struct itset_elt *) elt;
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

static int
parse_width (const char **spec, enum itset_width *width)
{
  const char *width_str = *spec;

  if (!isalpha (width_str[0])
      || width_str[1] == ':'
      || width_str[1] == '*'
      || isdigit (width_str[1]))
    return 0;

  if (width_str[0] == 'e' && width_str[1] == '(')
    {
      /* Leave the '(' in place, to be consumed by the caller.  */
      (*spec)++;
      *width = ITSET_WIDTH_EXPLICIT;
      return 1;
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
      return 0;
    }

  (*spec)++;
  return 1;
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
      char *tem;
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
      struct itset_elt_itset *itset_elt;

      for (text = name; isalnum (*text) || *text == '_'; ++text)
	;

      if (text == name)
	error (_("Doesn't look like a valid spec."));

      tem = alloca (text - name + 1);

      memcpy (tem, name, text - name);
      tem[text - name] = '\0';

      named_itset = get_named_itset (tem);
      if (named_itset == NULL)
	error (_("Unknown named I/T set: `%s'"), tem);
      itset_elt = create_itset_elt_itset (named_itset->set);
      elt = (struct itset_elt *) create_itset_elt_itset (named_itset->set);
    }

  *textp = text;
  return elt;
}

/* A cleanup function that calls itset_free.  */

static void
itset_free_cleanup (void *arg)
{
  struct itset *itset = arg;
  itset_free (itset);
}

struct cleanup *
make_cleanup_itset_free (struct itset *itset)
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

  object_type = itset_get_focus_object_type (current_itset);

  elt = parse_range_elem_1 (self, width, object_type);
  if (elt != NULL)
    return elt;

  return NULL;
}

static struct itset *
  itset_create_const_1 (const char **specp, enum itset_width default_width);

static struct itset_elt_range *
itset_get_range_elt_if_simple (struct itset *itset)
{
  if (VEC_length (itset_elt_ptr, itset->elements) == 1)
    {
      struct itset_elt *elt;

      elt = VEC_index (itset_elt_ptr, current_itset->elements, 0);
      if (elt->vtable->is_range_type != NULL
	  && elt->vtable->is_range_type (elt))
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
  struct itset *explicit_width = NULL;

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
	  if (VEC_length (itset_elt_ptr, current_itset->elements) == 1)
	    {
	      struct itset_elt *elt;

	      elt = VEC_index (itset_elt_ptr, current_itset->elements, 0);

	      if (elt->vtable->is_range_type != NULL
		  && elt->vtable->is_range_type (elt))
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
      || *self->spec == '|'
      || *self->spec == ','
      || *self->spec == '('
      || *self->spec == ')')
    {
      if (VEC_length (itset_elt_ptr, current_itset->elements) == 1)
	{
	  struct itset_elt *elt;

	  elt = VEC_index (itset_elt_ptr, current_itset->elements, 0);

	  if (elt->vtable->is_range_type != NULL
	      && elt->vtable->is_range_type (elt))
	    {
	      struct itset_elt *clone_elt = elt->vtable->clone (elt);
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
      return &elt_range->base;
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
  struct cleanup *old_chain;
  struct itset_elt *elt;

  if (*self->spec != '(')
    return NULL;
  self->spec++;

  self->parens_level++;

  elt = parse_itset_one (self);
  if (elt == NULL)
    error (_("Invalid I/T syntax at `%s'"), self->spec);

  old_chain = make_cleanup_itset_elt_free (elt);
  if (*self->spec != ')')
    error (_("Invalid I/T syntax at `%s'"), self->spec);

  self->spec++;
  self->parens_level--;
  gdb_assert (self->parens_level >= 0);

  discard_cleanups (old_chain);

  return (struct itset_elt *) elt;
}

static struct itset_elt *
parse_inters (struct itset_parser *self)
{
  struct itset_elt *elt1, *elt2 = NULL;
  struct itset_elt_intersect *intersect = NULL;
  struct cleanup *old_chain;

  elt1 = parse_elem (self);
  if (elt1 == NULL)
    return NULL;

  old_chain = make_cleanup_itset_elt_free (elt1);

  maybe_skip_spaces (self);

  if (*self->spec == '&')
    {
      intersect = create_intersect_itset ();
      VEC_safe_push (itset_elt_ptr, intersect->elements, elt1);
      elt1 = (struct itset_elt *) intersect;

      discard_cleanups (old_chain);
      old_chain = make_cleanup_itset_elt_free (elt1);
    }

  while (*self->spec == '&')
    {
      self->spec++;

      elt2 = parse_elem (self);
      if (elt2 == NULL)
	{
	  do_cleanups (old_chain);
	  return NULL;
	}
      VEC_safe_push (itset_elt_ptr, intersect->elements, elt2);
    }

  discard_cleanups (old_chain);
  return elt1;
}

static struct itset_elt *
parse_itset_one (struct itset_parser *self)
{
  struct itset_elt *inters1, *inters2 = NULL;
  struct itset_elt_itset *un = NULL;
  struct cleanup *old_chain;

  inters1 = parse_inters (self);
  if (inters1 == NULL)
    return NULL;
  old_chain = make_cleanup_itset_elt_free (inters1);

  maybe_skip_spaces (self);

  if (*self->spec == ',' || (self->parens_level > 0 && *self->spec != ')'))
    {
      struct itset *set;

      set = XCNEW (struct itset);
      set->refc = 1;

      un = create_itset_elt_itset (set);

      VEC_safe_push (itset_elt_ptr, set->elements, inters1);
      inters1 = (struct itset_elt *) un;

      discard_cleanups (old_chain);
      old_chain = make_cleanup_itset_elt_free (inters1);
    }

  while (*self->spec == ',' || (self->parens_level > 0 && *self->spec != ')'))
    {
      if (*self->spec == ',')
	self->spec++;

      maybe_skip_spaces (self);

      if (*self->spec == '\0')
	error (_("Invalid I/T syntax: premature end"));

      inters2 = parse_inters (self);
      if (inters2 == NULL)
	{
	  do_cleanups (old_chain);
	  return NULL;
	}
      VEC_safe_push (itset_elt_ptr, un->set->elements, inters2);

      maybe_skip_spaces (self);
    }

  discard_cleanups (old_chain);
  return inters1;
}

/* A helper function that returns true if the inferior INF is
   contained by the set ELEMENTS.  */

static char *
set_get_spec (VEC (itset_elt_ptr) *elements)
{
  int ix;
  struct itset_elt *elt;
  char *ret = xstrdup ("");

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      const char *elt_spec = elt->vtable->get_spec (elt);

      ret = reconcat (ret, ret, ix == 0 ? "" : ",", elt_spec, (char *) NULL);
    }

  return ret;
}

static char *
itset_get_spec (const struct itset *set)
{
  return set_get_spec (set->elements);
}

/* FIXME: This only exists to cast result to const.  But then again,
   all callers are leaking the result.  */

const char *
itset_spec (const struct itset *set)
{
  return itset_get_spec (set);
}

static enum itset_width
set_get_width (VEC (itset_elt_ptr) *elements)
{
  int ix;
  struct itset_elt *elt;
  enum itset_width width = ITSET_WIDTH_DEFAULT;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      enum itset_width elt_width = elt->vtable->get_width (elt);

      if (elt_width > width)
	width = elt_width;
    }

  return width;
}

enum itset_width
itset_get_width (struct itset *set)
{
  return set_get_width (set->elements);
}


static struct thread_info *
set_get_toi (VEC (itset_elt_ptr) *elements)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      struct thread_info *tp = elt->vtable->get_toi (elt);

      if (tp != NULL)
	return tp;
    }

  return NULL;
}

struct thread_info *
itset_get_toi (struct itset *set)
{
  return set_get_toi (set->elements);
}

static int
set_has_fixed_toi (VEC (itset_elt_ptr) *elements)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      if (elt->vtable->has_fixed_toi (elt))
	return 1;
    }

  return 0;
}

int
itset_has_fixed_toi (struct itset *set)
{
  return set_has_fixed_toi (set->elements);
}

static char
set_get_focus_object_type (VEC (itset_elt_ptr) *elements)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      char object_type_char;

      object_type_char = elt->vtable->get_focus_object_type (elt);
      if (object_type_char != '\0')
	return object_type_char;
    }

  gdb_assert_not_reached ("set has no object type");
}

char
itset_get_focus_object_type (struct itset *set)
{
  return set_get_focus_object_type (set->elements);
}

/* Parse an I/T set specification and return a new I/T set.  Throws an
   exception on error.  */

static struct itset *
itset_create_const_1 (const char **specp, enum itset_width default_width)
{
  int is_static = 0;
  struct itset *result;
  struct itset_elt *elt;
  struct cleanup *cleanups;
  const char *spec = *specp;
  const char *spec_start;

  result = XCNEW (struct itset);
  result->refc = 1;

  cleanups = make_cleanup_itset_free (result);

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
      VEC_safe_push (itset_elt_ptr, result->elements, elt);

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
      struct itset_elt *st = create_static_itset (result->elements);

      set_free (result->elements);
      result->elements = NULL;
      VEC_safe_push (itset_elt_ptr, result->elements, st);
    }

  discard_cleanups (cleanups);

  return result;
}

struct itset *
itset_create_const (const char **specp, enum itset_width default_width)
{
  struct itset *set;

  set = itset_create_const_1 (specp, default_width);
  if (!valid_spec_end (*specp))
    {
      itset_free (set);
      error (_("Invalid I/T syntax at `%s'"), *specp);
    }
  return set;
}

static struct itset *
itset_create_spec_default_width (const char *spec,
				 enum itset_width default_width)
{
   return itset_create_const (&spec, default_width);
}

struct itset *
itset_create_spec (const char *spec)
{
  return itset_create_spec_default_width (spec, ITSET_WIDTH_DEFAULT);
}

struct itset *
itset_create (char **specp)
{
  const char *spec_const = *specp;
  struct itset *itset;

  itset = itset_create_const (&spec_const, ITSET_WIDTH_DEFAULT);
  *specp = (char *) spec_const;
  return itset;
}

struct itset *
itset_clone_replace_default_width (const struct itset *template,
				   enum itset_width default_width)
{
  struct itset *result;
  char *spec;

  spec = itset_get_spec (template);

  /* We're reparsing a spec we had previously parsed successfully, so
     this should never error out.  */
  result = itset_create_spec_default_width (spec, default_width);
  xfree (spec);

  return result;
}

struct itset *
itset_create_empty (void)
{
  return itset_create_spec ("");
}

/* Create a new I/T set which represents the current inferior and all
   its threads.  */

static struct itset *
itset_create_curinf (void)
{
  return itset_create_spec ("iI");
}

/* Create a new I/T set which represents the current thread.  */

static struct itset *
itset_create_curthr (void)
{
  return itset_create_spec ("tT");
}

/* Create a new I/T set which represents the current thread.  */

static struct itset *
itset_create_lockstep (void)
{
  return itset_create_spec ("t/L/t1.1");
}

static struct itset *
itset_create_all (void)
{
  return itset_create_spec ("g/all/t1.1");
}

static struct itset *
itset_create_running (void)
{
  return itset_create_spec ("g/running/t1.1");
}

static struct itset *
itset_create_stopped (void)
{
  return itset_create_spec ("g/stopped/t1.1");
}

static struct itset *
itset_create_default (void)
{
  return itset_create_spec ("dt1.1");
}

int
itset_contains_any_thread (struct itset *itset)
{
  struct thread_info *thr;

  ALL_THREADS (thr)
    if (itset_contains_thread (itset, thr))
      return 1;

  return 0;
}


/* Return 1 if SET contains INF, 0 otherwise.  */

int
itset_contains_program_space (struct itset *set,
			      enum itset_width default_width,
			      struct program_space *pspace)
{
  return set_contains_program_space (set->elements, default_width, pspace);
}

/* Return 1 if SET contains INF, 0 otherwise.  */

static int
itset_contains_inferior_1 (struct itset *set,
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
itset_width_contains_inferior (struct itset *set,
			       enum itset_width default_width,
			       struct inferior *inf)
{
  return itset_contains_inferior_1 (set, default_width, inf, 1);
}

/* Return 1 if SET contains INF, 0 otherwise.  */

int
itset_contains_inferior (struct itset *set,
			 struct inferior *inf)
{
  return itset_contains_inferior_1 (set, ITSET_WIDTH_INFERIOR, inf, 0);
}

static int
itset_contains_thread_1 (struct itset *set,
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
itset_width_contains_thread (struct itset *set,
		       enum itset_width default_width,
		       struct thread_info *thr)
{
  return itset_contains_thread_1 (set, default_width, thr, 1);
}

/* Return 1 if SET contains THR, 0 otherwise.  */

int
itset_contains_thread (struct itset *set,
		       struct thread_info *thr)
{
  return itset_contains_thread_1 (set, ITSET_WIDTH_THREAD, thr, 0);
}

/* Return 1 if SET contains TASK, 0 otherwise.  */

int
itset_contains_ada_task (struct itset *set,
			 enum itset_width default_width,
			 const struct ada_task_info *task,
			 int including_width)
{
  struct thread_info *thr;

  thr = find_thread_ptid (task->ptid);
  if (thr == NULL)
    return 0;

  return itset_contains_thread_1 (set, default_width,
				  thr, including_width);
}

/* Acquire a new reference to an I/T set.  */

struct itset *
itset_reference (struct itset *itset)
{
  ++itset->refc;
  return itset;
}

/* Destroy SET.  */

void
itset_free (struct itset *set)
{
  /* Like xfree, allow NULL.  */
  if (set == NULL)
    return;

  if (--set->refc == 0)
    {
      set_free (set->elements);
      xfree (set->name);
      xfree (set->spec);
      xfree (set);
    }
}

/* Helper struct for iterate_over_itset.  */

struct iterate_data
{
  /* The I/T set we are using.  */
  struct itset *itset;

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
  struct iterate_data *data = d;

  if (itset_contains_inferior_1 (data->itset, data->default_width, inf, 1))
    return data->callback (inf, data->client_data);

  /* Keep going.  */
  return 0;
}

/* Like iterate_over_inferiors, but iterate over only those inferiors
   in ITSET.  */

struct inferior *
iterate_over_itset_inferiors (struct itset *itset,
			      enum itset_width default_width,
			      itset_inf_callback_func *callback,
			      void *datum)
{
  struct iterate_data data;

  data.itset = itset;
  data.callback = callback;
  data.client_data = datum;
  data.default_width = default_width;

  return iterate_over_inferiors (iter_callback, &data);
}

/* Helper struct for iterate_over_itset.  */

struct iterate_thr_data
{
  /* The I/T set we are using.  */
  struct itset *itset;

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
  struct iterate_thr_data *data = d;

  if (itset_contains_thread_1 (data->itset, data->default_width, thr, 1))
    return data->callback (thr, data->client_data);

  /* Keep going.  */
  return 0;
}

/* Like iterate_over_inferiors, but iterate over only those inferiors
   in ITSET.  */

static struct thread_info *
iterate_over_itset_threads (struct itset *itset,
			    enum itset_width default_width,
			    int (*callback) (struct thread_info *, void *),
			    void *datum)
{
  struct iterate_thr_data data;

  data.itset = itset;
  data.callback = callback;
  data.client_data = datum;
  data.default_width = default_width;

  return iterate_over_threads (iter_thr_callback, &data);
}

struct itset *current_itset = NULL;

/* A cleanups callback, helper for save_current_itset
   below.  */

static void
restore_itset (void *arg)
{
  struct itset *saved_itset = arg;

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
  struct count_threads_arg *c = data;

  if (ptid_get_pid (thr->ptid) != c->pid)
    return 0;

  c->count++;
  return 0;
}

static void
switch_to_itset (struct itset *itset)
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

int itfocus_should_follow_stop_event (void);

int
itfocus_should_follow_stop_event (void)
{
  struct itset_elt_range *cur_elt_range
    = itset_get_range_elt_if_simple (current_itset);

  return (cur_elt_range != NULL);
}

static struct itset *
itset_from_elt (struct itset_elt *elt)
{
  struct itset *itset;

  itset = XCNEW (struct itset);
  itset->refc = 1;

  VEC_safe_push (itset_elt_ptr, itset->elements, elt);
  return itset;
}

void
itfocus_from_thread_switch (void)
{
  struct itset_elt_range *new_elt_range;
  struct itset_elt_range *cur_elt_range
    = itset_get_range_elt_if_simple (current_itset);
  enum itset_width width = itset_get_width (current_itset);
  struct itset *new_itset;
  struct spec_range inf_range;
  struct spec_range thr_range;

  inf_range.first = current_inferior ()->num;
  inf_range.last = inf_range.first;

  thr_range.first = inferior_thread ()->num_inf;
  thr_range.last = thr_range.first;

  new_elt_range = create_thread_range_itset (width, 0,
					     &inf_range,
					     &thr_range);

  if (cur_elt_range != NULL && cur_elt_range->explicit_width != NULL)
    {
      new_elt_range->explicit_width
	= itset_reference (cur_elt_range->explicit_width);
    }

  new_itset = itset_from_elt (&new_elt_range->base);
  itset_free (current_itset);
  current_itset = new_itset;
}

static void
restore_current_context_cleanup (void *data)
{
  struct execution_context *ctx = data;

  *get_current_context () = *ctx;
}

static void
itfocus_command (char *spec, int from_tty)
{
  struct itset *itset;
  struct cleanup *old_chain;

  if (spec == NULL)
    {
      if (current_itset)
	printf_filtered (_("Focus is `%s' (current inferior is %d)"),
			 current_itset->spec,
			 current_inferior ()->num);
      else
	printf_filtered (_("No focus has been set. (current inferior is %d)"),
			 current_inferior ()->num);
      printf_filtered ("\n");
      return;
    }

  itset = itset_create (&spec);
  old_chain = make_cleanup_itset_free (itset);

  spec = skip_spaces (spec);
  if (*spec != '\0')
    {
      struct execution_context saved_ctx;

      save_current_itset ();
      current_itset = itset;

      saved_ctx = *get_current_context ();
      make_cleanup (restore_current_context_cleanup, &saved_ctx);

      old_chain = make_cleanup_restore_current_thread ();

      switch_to_itset (itset);

      execute_command (spec, from_tty);

      do_cleanups (old_chain);
      return;
    }

#if 0
  if (itset_is_empty (itset, ITSET_WIDTH_ALL))
    warning (_("focus set is empty"));
#endif

  discard_cleanups (old_chain);

  itset_free (current_itset);
  current_itset = itset;

  switch_to_itset (itset);

  /* Confirm the choice of focus.  */
  printf_filtered (_("Current inferior is %d.\n"), current_inferior ()->num);
  if (!ptid_equal (inferior_ptid, null_ptid))
    printf_filtered (_("Current thread is %d.\n"), inferior_thread ()->num);
  else
    printf_filtered (_("No current thread.\n"));
}

static struct named_itset *
make_itset_named_itset (struct itset *set, char *name, int internal)
{
  struct named_itset *named_itset;

  itset_reference (set);
  set->name = name;

  named_itset = XCNEW (struct named_itset);
  named_itset->set = set;

  if (internal)
    named_itset->number = --internal_named_itset_count;
  else
    named_itset->number = ++named_itset_count;

  return named_itset;
}

#if 0
static int
itset_elt_is_static (struct itset_elt *elt)
{
  return elt->vtable == &static_vtable;
}

static int
itset_is_static (struct itset *itset)
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
defset_command (char *arg, int from_tty)
{
  char *endp;
  char *name;
  char *spec;
  struct itset *itset;
  struct named_itset *named_itset;
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
free_named_itset (struct named_itset *it)
{
  itset_free (it->set);
  xfree (it);
}

static void
undefset_command (char *arg, int from_tty)
{
  char *name;
  struct named_itset *it, **it_link;
  int found;

  if (arg == NULL || *arg == '\0')
    error_no_arg (_("no args"));

  name = skip_spaces (arg);

  if (strcmp (name, "-all") == 0)
    {
      it = named_itsets;
      it_link = &named_itsets;
      while (it != NULL)
	{
	  if (it->number > 0)
	    {
	      *it_link = it->next;
	      free_named_itset (it);
	    }
	  else
	    it_link = &it->next;
	  it = *it_link;
	}
      return;
    }

  found = 0;
  it = named_itsets;
  it_link = &named_itsets;
  while (it != NULL)
    {
      if (strcmp (it->set->name, name) == 0)
	{
	  if (it->number < 0)
	    error (_("cannot delete builtin I/T set"));

	  *it_link = it->next;
	  free_named_itset (it);
	  found = 1;
	  break;
	}

      it_link = &it->next;
      it = *it_link;
    }

  if (!found)
    warning (_("itset %s does not exist"), name);
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
  int printed = 0;

  ALL_NAMED_ITSETS(named_itset)
    {
      QUIT;

      if (itset_width_contains_thread (named_itset->set, ITSET_WIDTH_ALL, thr))
	{
	  if (!printed)
	    {
	      printf_filtered (_("i%d.t%d (%s) is in:"),
			       inf->num, thr->num,
			       target_pid_to_str (thr->ptid));
	      printf_filtered (" %s", itset_name (named_itset->set));
	      printed = 1;
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
  struct named_itset *named_itset;
  struct itset *itset;
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
viewset (struct itset *itset)
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
	      printf_filtered (_("  threads: %d"), thr->num);
	      printed = 1;
	    }
	  else
	    printf_filtered (", %d", thr->num);
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
  struct named_itset *named_itset;

  if (arg == NULL)
    {
      struct named_itset *e;
      struct itset *itset;

      /* No arg means all debugger- and user-defined sets.  */
      ALL_NAMED_ITSETS (named_itset)
	viewset (named_itset->set);
    }
  else
    {
      struct itset *itset;
      struct cleanup *old_chain;

      arg = skip_spaces (arg);
      itset = itset_create (&arg);
      old_chain = make_cleanup_itset_free (itset);
      viewset (itset);
      do_cleanups (old_chain);
    }
}

static void
make_internal_itset (struct itset *itset, const char *name)
{
  struct named_itset *named_itset;

  named_itset = make_itset_named_itset (itset, xstrdup (name), 1);
  add_to_named_itset_chain (named_itset);
}

static void
restore_execution_context_thread (void *arg)
{
  struct execution_context *ctx = get_current_context ();
  struct thread_info *thr;

  thr = find_thread_id (ctx->thread_gnum);
  if (thr != NULL)
    {
      switch_to_thread (thr->ptid);
    }
  else
    {
      ctx->thread_gnum = 0;
      set_current_program_space (ctx->inf->pspace);
      set_current_inferior (ctx->inf);
      switch_to_thread (null_ptid);
    }
}

extern struct cleanup *make_cleanup_restore_execution_context_thread (void);

struct cleanup *
make_cleanup_restore_execution_context_thread (void)
{
  /* Don't use make_cleanup_restore_current_thread as CMD may want to
     change the user selected thread or frame.  E.g., run, etc.  */
  return make_cleanup (restore_execution_context_thread, NULL);
}

extern void for_each_selected_thread_cmd (cmd_cfunc_ftype cmd,
					  char *args, int from_tty);

static void
for_each_selected_thread_cmd_1 (cmd_cfunc_ftype cmd,
				char *args, int from_tty)
{
  struct cleanup *old_chain;
  struct inferior *inf;
  struct thread_info *tp;
  int count = 0;
  ptid_t selected_ptid = inferior_ptid;

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
		  printf_filtered (_("\nThread %d.%d (%s):\n"),
				   inf->num, tp->num_inf,
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
  ptid_t saved_inferior_ptid = inferior_ptid;

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

extern void for_each_selected_thread_cmd (cmd_cfunc_ftype cmd,
					  char *args, int from_tty);

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
      struct itset *itset;

      itset = itset_create_const (&text, ITSET_WIDTH_DEFAULT);
      itset_free (itset);
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

  add_com ("defset", no_class, defset_command, _("\
Define a new named set.\n\
Usage: defset NAME SPEC"));

  add_com ("undefset", no_class, undefset_command, _("\
Undefine an existing named set.\n\
Usage: undefset NAME | -all"));

  add_com ("whichsets", no_class, whichsets_command, _("\
List all sets to which threads in a given set belong to.\n\
Usage: whichsets SET.\n\
Defaults to the current set."));

  add_com ("viewset", no_class, viewset_command, _("\
List the members of a set.\n\
Usage: viewset SET.\n\
Defaults to all named sets."));

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
