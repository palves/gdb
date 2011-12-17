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
#include "gdb_string.h"
#include "cli/cli-utils.h"
#include "gdbthread.h"
#include "command.h"
#include <ctype.h>
#include "gdbcmd.h"

/* Rather than creating/destroying these dynamic itsets when
   necessary, keep global copies around (itsets are refcounted).  */
static struct itset *all_itset;
static struct itset *empty_itset;
static struct itset *running_itset;
static struct itset *stopped_itset;
static struct itset *curinf_itset;

/* Forward declaration of the base class.  */

struct itset_elt;

/* An element of an I/T set is a class with some virtual methods,
   defined here.  */

struct itset_elt_vtable
{
  /* Destroy the contents of this element.  If the element does not
     require any special cleanup, this can be NULL.  This should not
     free the element itself; that is done by the caller.  */

  void (*destroy) (struct itset_elt *);

  /* Return true if the element contains the inferior.  The element
     and the inferior are passed as arguments.  */

  int (*contains_inferior) (struct itset_elt *elt, struct inferior *inf);

  /* Return true if the element contains the thread.  The element and
     the thread are passed as arguments.  */

  int (*contains_thread) (struct itset_elt *elt, struct thread_info *thr);

  /* Return true if the element is empty.  */

  int (*is_empty) (struct itset_elt *elt);
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

struct cleanup *
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

const char *
itset_spec (const struct itset *itset)
{
  return itset->spec;
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



/* A helper function that returns true if all elements in the ELEMENTS
   set are empty.  */

static int
set_is_empty (VEC (itset_elt_ptr) *elements)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    if (!elt->vtable->is_empty (elt))
      return 0;

  return 1;
}

/* A helper function that returns true if the inferior INF is
   contained by the set ELEMENTS.  */

static int
set_contains_inferior (VEC (itset_elt_ptr) *elements, struct inferior *inf)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      if (elt->vtable->contains_inferior (elt, inf))
	return 1;
    }

  return 0;
}

/* A helper function that returns true if the thread THR is contained
   by the set ELEMENTS.  */

static int
set_contains_thread (VEC (itset_elt_ptr) *elements, struct thread_info *thr)
{
  int ix;
  struct itset_elt *elt;

  for (ix = 0; VEC_iterate (itset_elt_ptr, elements, ix, elt); ++ix)
    {
      if (elt->vtable->contains_thread (elt, thr))
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
exec_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  struct itset_elt_exec *exec = (struct itset_elt_exec *) base;

  /* FIXME: smarter compare.  */
  return (inf->pspace->ebfd != NULL
	  && strcmp (exec->exec_name,
		     bfd_get_filename (inf->pspace->ebfd)) == 0);
}

/* Implementation of `contains_thread' method.  */

static int
exec_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_exec *exec = (struct itset_elt_exec *) base;
  struct inferior *inf = get_thread_inferior (thr);

  /* FIXME: smarter compare.  */
  return (inf->pspace->ebfd != NULL
	  && strcmp (exec->exec_name,
		     bfd_get_filename (inf->pspace->ebfd)) == 0);
}

/* Implementation of `is_empty' method.  */

static int
exec_is_empty (struct itset_elt *base)
{
  struct itset_elt_exec *exec = (struct itset_elt_exec *) base;
  struct inferior *inf;

  ALL_INFERIORS (inf)
    if (exec_contains_inferior (base, inf))
      return 0;

  return 1;
}

static const struct itset_elt_vtable exec_vtable =
{
  exec_destroy,
  exec_contains_inferior,
  exec_contains_thread,
  exec_is_empty
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



/* The value representing any inferior or thread.  */

#define WILDCARD -1

/* An I/T set element representing a range of inferiors.  */

struct itset_elt_inferior_range
{
  struct itset_elt base;

  /* The first and last inferiors in this range.  If FIRST is
     WILDCARD, then LAST is unused.  */
  int inf_first, inf_last;
};

/* Implementation of `contains_inferior' method.  */

static int
inferior_range_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  struct itset_elt_inferior_range *range
    = (struct itset_elt_inferior_range *) base;

  if (range->inf_first == WILDCARD
      || (range->inf_first <= inf->num && inf->num <= range->inf_last))
    return 1;

  return 0;
}

/* Implementation of `contains_thread' method.  */

static int
inferior_range_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_inferior_range *range
    = (struct itset_elt_inferior_range *) base;
  struct inferior *inf;

  if (range->inf_first == WILDCARD)
    return 1;

  inf = get_thread_inferior (thr);
  return range->inf_first <= inf->num && inf->num <= range->inf_last;
}

/* Implementation of `is_empty' method.  */

static int
inferior_range_is_empty (struct itset_elt *base)
{
  struct itset_elt_inferior_range *range
    = (struct itset_elt_inferior_range *) base;
  struct inferior *inf;
  struct thread_info *thr;

  ALL_INFERIORS (inf)
    {
      if (inferior_range_contains_inferior (base, inf))
	return 0;
    }

  ALL_THREADS (thr)
    {
      if (inferior_range_contains_thread (base, thr))
	return 0;
    }

  return 1;
}

static const struct itset_elt_vtable inferior_range_vtable =
{
  NULL,
  inferior_range_contains_inferior,
  inferior_range_contains_thread,
  inferior_range_is_empty
};

/* Create a new `range' I/T set element.  */

static struct itset_elt *
create_inferior_range_itset (int inf_first, int inf_last)
{
  struct itset_elt_inferior_range *elt;

  elt = XNEW (struct itset_elt_inferior_range);
  elt->base.vtable = &inferior_range_vtable;
  elt->inf_first = inf_first;
  elt->inf_last = inf_last;

  return (struct itset_elt *) elt;
}



/* An I/T set element representing a range of threads.  */

struct itset_elt_thread_range
{
  struct itset_elt base;

  /* The first and last threads in this range.  If FIRST is WILDCARD,
     then LAST is unused.  */
  int thr_first, thr_last;
};

/* Implementation of `contains_inferior' method.  */

static int
thread_range_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  struct itset_elt_thread_range *range
    = (struct itset_elt_thread_range *) base;
  struct thread_info *thr;
  int pid;

  /* If there are no threads in the inferior, INF can't be part of any
     thread range.  */
  if (inf->pid == 0)
    return 0;

  /* If range is a wildcard, this inferior is part of the range, given
     that it must have at least one thread.  */
  if (range->thr_first == WILDCARD)
    return 1;

  /* Walk threads of INF, check if the range contains any of those.
     If so, then the range contains the inferior.  */
  ALL_THREADS (thr)
    if (ptid_get_pid (thr->ptid) == inf->pid)
      {
	if (range->thr_first <= thr->num && thr->num <= range->thr_last)
	  return 1;
      }

  return 0;
}

/* Implementation of `contains_thread' method.  */

static int
thread_range_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_thread_range *range
    = (struct itset_elt_thread_range *) base;

  if (range->thr_first == WILDCARD
      || (range->thr_first <= thr->num && thr->num <= range->thr_last))
    return 1;

  return 0;
}

/* Implementation of `is_empty' method.  */

static int
thread_range_is_empty (struct itset_elt *base)
{
  struct itset_elt_inferior_range *range
    = (struct itset_elt_inferior_range *) base;
  struct inferior *inf;
  struct thread_info *thr;

  ALL_INFERIORS (inf)
    {
      if (thread_range_contains_inferior (base, inf))
	return 0;
    }

  ALL_THREADS (thr)
    {
      if (thread_range_contains_thread (base, thr))
	return 0;
    }

  return 1;
}

static const struct itset_elt_vtable thread_range_vtable =
{
  NULL,
  thread_range_contains_inferior,
  thread_range_contains_thread,
  thread_range_is_empty
};

/* Create a new `range' I/T set element.  */

static struct itset_elt *
create_thread_range_itset (int thr_first, int thr_last)
{
  struct itset_elt_thread_range *elt;

  elt = XNEW (struct itset_elt_thread_range);
  elt->base.vtable = &thread_range_vtable;
  elt->thr_first = thr_first;
  elt->thr_last = thr_last;

  return (struct itset_elt *) elt;
}



/* An I/T set element representing a range of cores.  */

struct itset_elt_core_range
{
  struct itset_elt base;

  /* The first and last cores in this range.  If CORE_FIRST is
     WILDCARD, then CORE_LAST is unused.  */
  int core_first, core_last;
};

/* Implementation of `contains_thread' method.  */

static int
core_range_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_core_range *core_range = (struct itset_elt_core_range *) base;
  int core;

  if (core_range->core_first == WILDCARD)
    return 1;

  core = target_core_of_thread (thr->ptid);
  if (core_range->core_first <= core && core <= core_range->core_last)
    return 1;

  return 0;
}

/* Implementation of `contains_inferior' method.  */

static int
core_range_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  struct itset_elt_core_range *core_range = (struct itset_elt_core_range *) base;
  struct thread_info *thr;

  /* True if we find a thread of this inferior that is running on our
     core range.  */
  ALL_THREADS (thr)
    {
      /* It's cheaper to check the core range first, because looking
	 up the a thread's inferior is O(n).  */
      if (core_range_contains_thread (base, thr))
	{
	  struct inferior *thr_inf;

	  thr_inf = get_thread_inferior (thr);
	  if (thr_inf == inf)
	    return 1;
	}
    }

  return 0;
}

/* Implementation of `is_empty' method.  */

static int
core_range_is_empty (struct itset_elt *base)
{
  struct itset_elt_core_range *core_range = (struct itset_elt_core_range *) base;
  struct inferior *inf;
  struct thread_info *thr;

  ALL_THREADS (thr)
    {
      if (core_range_contains_thread (base, thr))
	return 0;
    }

  return 1;
}

static const struct itset_elt_vtable core_range_vtable =
{
  NULL,
  core_range_contains_inferior,
  core_range_contains_thread,
  core_range_is_empty
};

/* Create a new `core_range' I/T set element.  */

static struct itset_elt *
create_core_range_itset (int core_first, int core_last)
{
  struct itset_elt_core_range *elt;

  elt = XNEW (struct itset_elt_core_range);
  elt->base.vtable = &core_range_vtable;
  elt->core_first = core_first;
  elt->core_last = core_last;

  return (struct itset_elt *) elt;
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
intersect_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;
  struct itset_elt *elt;
  int ix;

  gdb_assert (!VEC_empty (itset_elt_ptr, intersect->elements));

  for (ix = 0; VEC_iterate (itset_elt_ptr, intersect->elements, ix, elt); ++ix)
    {
      if (!elt->vtable->contains_inferior (elt, inf))
	return 0;
    }

  return 1;
}

/* Implementation of `contains_thread' method.  */

static int
intersect_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;
  struct itset_elt *elt;
  int ix;

  gdb_assert (!VEC_empty (itset_elt_ptr, intersect->elements));

  for (ix = 0; VEC_iterate (itset_elt_ptr, intersect->elements, ix, elt); ++ix)
    {
      if (!elt->vtable->contains_thread (elt, thr))
	return 0;
    }

  return 1;
}

/* Implementation of `is_empty' method.  */

static int
intersect_is_empty (struct itset_elt *base)
{
  struct itset_elt_intersect *intersect = (struct itset_elt_intersect *) base;
  struct inferior *inf;
  struct thread_info *thr;

  ALL_INFERIORS (inf)
    {
      if (intersect_contains_inferior (base, inf))
	return 0;
    }

  ALL_THREADS (thr)
    {
      if (intersect_contains_thread (base, thr))
	return 0;
    }

  return 1;
}

static const struct itset_elt_vtable intersect_vtable =
{
  intersect_destroy,
  intersect_contains_inferior,
  intersect_contains_thread,
  intersect_is_empty
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
all_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  return 1;
}

/* Implementation of `contains_thread' method.  */

static int
all_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  return 1;
}

/* Implementation of `is_empty' method.  */

static int
all_is_empty (struct itset_elt *base)
{
  /* There's always at least one inferior.  */
  return 0;
}

static const struct itset_elt_vtable all_vtable =
{
  NULL,
  all_contains_inferior,
  all_contains_thread,
  all_is_empty
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

/* Implementation of `contains_inferior' method.  */

static int
empty_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  return 0;
}

/* Implementation of `contains_thread' method.  */

static int
empty_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  return 0;
}

/* Implementation of `is_empty' method.  */

static int
empty_is_empty (struct itset_elt *base)
{
  /* Always empty.  */
  return 1;
}

static const struct itset_elt_vtable empty_vtable =
{
  NULL,
  empty_contains_inferior,
  empty_contains_thread,
  empty_is_empty
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

/* Implementation of `contains_inferior' method.  */

static int
itset_elt_itset_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;
  return itset_contains_inferior (iiset->set, inf);
}

/* Implementation of `contains_thread' method.  */

static int
itset_elt_itset_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;
  return itset_contains_thread (iiset->set, thr);
}

/* Implementation of `is_empty' method.  */

static int
itset_elt_itset_is_empty (struct itset_elt *base)
{
  struct itset_elt_itset *iiset = (struct itset_elt_itset *) base;
  return itset_is_empty (iiset->set);
}

static const struct itset_elt_vtable itset_elt_itset_vtable =
{
  itset_elt_itset_destroy,
  itset_elt_itset_contains_inferior,
  itset_elt_itset_contains_thread,
  itset_elt_itset_is_empty
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

  if (elt->negated->vtable->destroy != NULL)
    elt->negated->vtable->destroy (elt->negated);
  xfree (elt->negated);
}

/* Implementation of `contains_inferior' method.  */

static int
itset_elt_negated_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;
  return !elt->negated->vtable->contains_inferior (elt->negated, inf);
}

/* Implementation of `contains_thread' method.  */

static int
itset_elt_negated_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;
  return !elt->negated->vtable->contains_thread (elt->negated, thr);
}

/* Implementation of `is_empty' method.  */

static int
itset_elt_negated_is_empty (struct itset_elt *base)
{
  struct itset_elt_negated *elt = (struct itset_elt_negated *) base;
  struct inferior *inf;
  struct thread_info *thr;

  ALL_INFERIORS (inf)
    {
      if (itset_elt_negated_contains_inferior (base, inf))
	return 0;
    }

  ALL_THREADS (thr)
    {
      if (itset_elt_negated_contains_thread (base, thr))
	return 0;
    }

  return 1;
}

static const struct itset_elt_vtable itset_elt_negated_vtable =
{
  itset_elt_negated_destroy,
  itset_elt_negated_contains_inferior,
  itset_elt_negated_contains_thread,
  itset_elt_negated_is_empty
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

  int state;
};

/* Implementation of `contains_thread' method.  */

static int
state_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_state *state = (struct itset_elt_state *) base;

  return thr->state == state->state;
}

/* Implementation of `contains_inferior' method.  */

static int
state_contains_inferior (struct itset_elt *base, struct inferior *inf)
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

/* Implementation of `is_empty' method.  */

static int
state_is_empty (struct itset_elt *base)
{
  struct thread_info *thr;

  ALL_THREADS (thr)
    if (state_contains_thread (base, thr))
      return 0;

  return 1;
}

static const struct itset_elt_vtable state_vtable =
{
  NULL,
  state_contains_inferior,
  state_contains_thread,
  state_is_empty
};

static struct itset_elt *
create_state_itset (int thread_state)
{
  struct itset_elt_state *elt;

  elt = XNEW (struct itset_elt_state);
  elt->base.vtable = &state_vtable;
  elt->state = thread_state;

  return (struct itset_elt *) elt;
}



/* Implementation of `contains_inferior' method.  */

static int
current_contains_inferior (struct itset_elt *base, struct inferior *inf)
{
  return current_inferior () == inf;
}

/* Implementation of `contains_thread' method.  */

static int
current_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct inferior *inf;

  inf = get_thread_inferior (thr);
  return current_inferior () == inf;
}

/* Implementation of `is_empty' method.  */

static int
current_is_empty (struct itset_elt *base)
{
  /* There's always a current inferior.  */
  return 0;
}

static const struct itset_elt_vtable current_vtable =
{
  NULL,
  current_contains_inferior,
  current_contains_thread,
  current_is_empty
};

/* Create a new I/T set element representing just the current
   inferior.  */

static struct itset_elt *
create_current_itset (void)
{
  struct itset_elt *elt;

  elt = XNEW (struct itset_elt);
  elt->vtable = &current_vtable;

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
static_contains_inferior (struct itset_elt *base, struct inferior *inf)
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
static_contains_thread (struct itset_elt *base, struct thread_info *thr)
{
  struct itset_elt_static *st = (struct itset_elt_static *) base;
  int idx;

  idx = VEC_lower_bound (int, st->threads, thr->num, static_lessthan);
  if (idx < VEC_length (int, st->threads)
      && VEC_index (int, st->threads, idx) == thr->num)
    return 1;
  return 0;
}

/* Implementation of `is_empty' method.  */

static int
static_is_empty (struct itset_elt *base)
{
  struct itset_elt_static *st = (struct itset_elt_static *) base;
  int idx;

  return VEC_empty (int, st->inferiors);
}

static const struct itset_elt_vtable static_vtable =
{
  static_destroy,
  static_contains_inferior,
  static_contains_thread,
  static_is_empty
};



/* Helper struct used to pass data through iterate_over_inferiors.  */

struct iter_data
{
  /* The I/T set we are constructing.  */

  struct itset_elt_static *st;

  /* The elements of the original (dynamic) I/T set.  */

  VEC (itset_elt_ptr) *elements;
};

/* A callback for iterate_over_inferiors that adds an inferior to the
   result set, if it is in the source set.  */

static int
check_one_inferior (struct inferior *inf, void *datum)
{
  struct iter_data *id = datum;

  if (set_contains_inferior (id->elements, inf))
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

  if (set_contains_thread (id->elements, thr))
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
looks_like_range (char *spec)
{
  return isdigit (spec[0]) || spec[0] == '*';
}

/* Parse an I/T set range.  A range has the form F[:L][.T], where F is
   the starting inferior, L is the ending inferior, and T is the
   thread.  Updates RESULT with the new I/T set elements, and returns
   an updated pointer into the spec.  Throws an exception on
   error.  */

static char *
parse_range (char *spec, int *first, int *last)
{
  struct itset_elt *elt;

  if (!looks_like_range (spec))
    error (_("Invalid I/T syntax at `%s'.  Expected '*' or digit."), spec);

  if (*spec == '*')
    {
      *first = WILDCARD;
      *last = WILDCARD;
      ++spec;
    }
  else
    {
      *first = strtol (spec, &spec, 10);
      if (*spec == '-')
	{
	  ++spec;
	  if (!isdigit (*spec))
	    error (_("Expected digit in I/T set, at `%s'"), spec);
	  *last = strtol (spec, &spec, 10);
	}
      else
	*last = *first;
    }
  return spec;
}

static struct itset_elt *
parse_inferior_range (char **spec)
{
  int first, last;

  if ((*spec)[0] != 'i' || !looks_like_range ((*spec) + 1))
    return NULL;

  (*spec)++;
  *spec = parse_range (*spec, &first, &last);
  return create_inferior_range_itset (first, last);
}

static struct itset_elt *
parse_thread_range (char **spec)
{
  int first, last;

  if ((*spec)[0] != 't' || !looks_like_range ((*spec) + 1))
    return NULL;

  (*spec)++;
  *spec = parse_range (*spec, &first, &last);
  return create_thread_range_itset (first, last);
}

static struct itset_elt *
parse_core_range (char **spec)
{
  int first, last;

  if ((*spec)[0] != 'c' || !looks_like_range ((*spec) + 1))
    return NULL;

  (*spec)++;
  *spec = parse_range (*spec, &first, &last);
  return create_core_range_itset (first, last);
}



/* Parse a named I/T set.  Currently the only named sets which are
   recognized are `exec (NAME)', and `current'.  Updates RESULT with
   the new I/T set elements, and returns an updated pointer into the
   spec.  Throws an exception on error.  */

struct itset_elt *
parse_named_or_throw (char **textp)
{
  struct itset_elt *elt;
  char *text = *textp;
  char *name = text;

  for (text = name + 1; isalnum (*text) || *text == '_'; ++text)
    ;

  if (strncmp ("all", name, text - name) == 0)
    elt = create_all_itset ();
  else if (strncmp ("empty", name, text - name) == 0)
    elt = create_empty_itset ();
  else if (strncmp ("stopped", name, text - name) == 0)
    elt = create_state_itset (THREAD_STOPPED);
  else if (strncmp ("running", name, text - name) == 0)
    elt = create_state_itset (THREAD_RUNNING);
  else if (strncmp ("curinf", name, text - name) == 0)
    elt = create_current_itset ();
  else if (strncmp ("exec", name, text - name) == 0)
    {
      char *tem;
      char *arg;

      if (*text != '(')
	error (_("'(' expected in I/T set after `exec'"));
      text = skip_spaces (text + 1);
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

      tem = alloca (text - name + 1);

      memcpy (tem, name, text - name);
      tem[text - name] = '\0';

      named_itset = get_named_itset (tem);
      if (named_itset == NULL)
	error (_("Unknown named I/T set: `%s'"), tem);
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

/*

  ',' (union) has precedence over '.' (intersect).

  ELEM = RANGE | NEG | PARENS_SET | '$' | NAME
  NEG = '~' ELEM
  PARENS_SET = '(' ITSET_ONE ')'
  INTERS = ELEM ('.' ELEM)*
  ITSET_ONE = INTERS (',' INTERS)*
  ITSET = | ('!' ITSET_ONE) | ITSET_ONE

  E.g.,:

  c1-3.~i1.(t1,other),foo is transformed to a tree like:

   UNION
     foo
     INTERS
       c1-3
       NEG
         i1-1
       UNION
         t1-1
	 other

*/

/* Forward declare.  The parser is recursive.  */
static struct itset_elt *parse_neg (char **spec);
static struct itset_elt *parse_parens_set (char **spec);
static struct itset_elt *parse_itset_one (char **spec);
static struct itset_elt *parse_current_focus (char **spec);

static int
valid_spec_end (char *spec)
{
  return *spec == '\0' || isspace (*spec);
}

static struct itset_elt *
parse_elem (char **spec)
{
  struct itset_elt *elt;

  elt = parse_inferior_range (spec);
  if (elt != NULL)
    return elt;

  elt = parse_thread_range (spec);
  if (elt != NULL)
    return elt;

  elt = parse_core_range (spec);
  if (elt != NULL)
    return elt;

  elt = parse_neg (spec);
  if (elt != NULL)
    return elt;

  elt = parse_parens_set (spec);
  if (elt != NULL)
    return elt;

  elt = parse_current_focus (spec);
  if (elt != NULL)
    return elt;

  return parse_named_or_throw (spec);
}

static struct itset_elt *
parse_neg (char **spec)
{
  struct itset_elt_negated *neg_elt;
  struct itset_elt *elt;

  if (**spec != '~')
    return NULL;

  (*spec)++;

  elt = parse_elem (spec);

  neg_elt = create_itset_elt_negated ();
  neg_elt->negated = elt;

  return (struct itset_elt *) neg_elt;
}

static struct itset_elt *
parse_current_focus (char **spec)
{
  struct itset_elt_itset *itset_elt;

  if (**spec != '$')
    return NULL;

  (*spec)++;

  itset_elt = create_itset_elt_itset (itset_reference (current_itset));
  return (struct itset_elt *) itset_elt;
}

static struct itset_elt *
parse_parens_set (char **spec)
{
  struct itset_elt_negated *neg_elt;
  struct itset_elt *elt;
  struct cleanup *old_chain;

  if (**spec != '(')
    return NULL;
  (*spec)++;

  elt = parse_itset_one (spec);
  if (elt == NULL)
    error (_("Invalid I/T syntax at `%s'"), *spec);

  old_chain = make_cleanup_itset_elt_free (elt);
  if (**spec != ')')
    error (_("Invalid I/T syntax at `%s'"), *spec);

  neg_elt = create_itset_elt_negated ();
  neg_elt->negated = elt;

  discard_cleanups (old_chain);

  return (struct itset_elt *) neg_elt;
}

static struct itset_elt *
parse_inters (char **spec)
{
  struct itset_elt *elt1, *elt2 = NULL;
  struct itset_elt_intersect *intersect = NULL;
  struct cleanup *old_chain;

  elt1 = parse_elem (spec);
  if (elt1 == NULL)
    return NULL;

  old_chain = make_cleanup_itset_elt_free (elt1);

  if (**spec == '.')
    {
      intersect = create_intersect_itset ();
      VEC_safe_push (itset_elt_ptr, intersect->elements, elt1);
      elt1 = (struct itset_elt *) intersect;

      discard_cleanups (old_chain);
      old_chain = make_cleanup_itset_elt_free (elt1);
    }

  while (**spec == '.')
    {
      (*spec)++;

      elt2 = parse_elem (spec);
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
parse_itset_one (char **spec)
{
  struct itset_elt *inters1, *inters2 = NULL;
  struct itset_elt_itset *un = NULL;
  struct cleanup *old_chain;

  inters1 = parse_inters (spec);
  if (inters1 == NULL)
    return NULL;
  old_chain = make_cleanup_itset_elt_free (inters1);

  if (**spec == ',')
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

  while (**spec == ',')
    {
      (*spec)++;

      inters2 = parse_inters (spec);
      if (inters2 == NULL)
	{
	  do_cleanups (old_chain);
	  return NULL;
	}
      VEC_safe_push (itset_elt_ptr, un->set->elements, inters2);
    }

  discard_cleanups (old_chain);
  return inters1;
}

/* Parse an I/T set specification and return a new I/T set.  Throws an
   exception on error.  */

struct itset *
itset_create (char **specp)
{
  int is_static = 0;
  struct itset *result;
  struct itset_elt *elt;
  struct cleanup *cleanups;
  char *spec = *specp;
  char *spec_start;

  result = XCNEW (struct itset);
  result->refc = 1;

  cleanups = make_cleanup_itset_free (result);

  spec = skip_spaces (spec);
  spec_start = spec;

  if (*spec == '!')
    {
      is_static = 1;
      ++spec;
    }

  if (!valid_spec_end (spec))
    {
      elt = parse_itset_one (&spec);
      VEC_safe_push (itset_elt_ptr, result->elements, elt);

      if (!valid_spec_end (spec))
	error (_("Invalid I/T syntax at `%s'"), spec);
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
itset_create_empty (void)
{
  char *spec = "";

  return itset_create (&spec);
}

/* Create a new I/T set which represents the current inferior and all
   its threads.  */

static struct itset *
itset_create_curinf (void)
{
  char *spec = "curinf";

  return itset_create (&spec);
}

static struct itset *
itset_create_all (void)
{
  char *spec = "all";

  return itset_create (&spec);
}

static struct itset *
itset_create_running (void)
{
  char *spec = "running";

  return itset_create (&spec);
}

static struct itset *
itset_create_stopped (void)
{
  char *spec = "stopped";

  return itset_create (&spec);
}

/* Return 1 if SET contains INF, 0 otherwise.  */

int
itset_is_empty (const struct itset *set)
{
  return set_is_empty (set->elements);
}

/* Return 1 if SET contains INF, 0 otherwise.  */

int
itset_contains_inferior (struct itset *set, struct inferior *inf)
{
  return set_contains_inferior (set->elements, inf);
}

/* Return 1 if SET contains THR, 0 otherwise.  */

int
itset_contains_thread (struct itset *set, struct thread_info *thr)
{
  return set_contains_thread (set->elements, thr);
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
};

/* Callback function for iterate_over_inferiors, used by
   iterate_over_itset.  */

static int
iter_callback (struct inferior *inf, void *d)
{
  struct iterate_data *data = d;

  if (itset_contains_inferior (data->itset, inf))
    return data->callback (inf, data->client_data);

  /* Keep going.  */
  return 0;
}

/* Like iterate_over_inferiors, but iterate over only those inferiors
   in ITSET.  */

struct inferior *
iterate_over_itset_inferiors (struct itset *itset,
			      itset_inf_callback_func *callback,
			      void *datum)
{
  struct iterate_data data;

  data.itset = itset;
  data.callback = callback;
  data.client_data = datum;

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
};

/* Callback function for iterate_over_inferiors, used by
   iterate_over_itset.  */

static int
iter_thr_callback (struct thread_info *thr, void *d)
{
  struct iterate_thr_data *data = d;

  if (itset_contains_thread (data->itset, thr))
    return data->callback (thr, data->client_data);

  /* Keep going.  */
  return 0;
}

/* Like iterate_over_inferiors, but iterate over only those inferiors
   in ITSET.  */

struct thread_info *
iterate_over_itset_threads (struct itset *itset,
			    int (*callback) (struct thread_info *, void *),
			    void *datum)
{
  struct iterate_thr_data data;

  data.itset = itset;
  data.callback = callback;
  data.client_data = datum;

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
  struct cleanup *old_chain;
  int inf_count;

  /* For now, set a current inferior from the first element of the
     focus set.  */
  inf = iterate_over_itset_inferiors (itset, first_inferior, NULL);
  if (inf == NULL)
    {
      /* Empty set.  Switch to no thread selected.  There's no concept
	 of no inferior selected, so just leave the current
	 selected.  */
      switch_to_thread (null_ptid);
      set_current_program_space (current_inferior ()->pspace);
      return;
    }

  inf_count = 0;
  iterate_over_itset_inferiors (itset, count_inferiors, &inf_count);
  if (inf_count > 1)
    warning ("\
%d inferiors in the current i/t set, using inf %d to get current exec",
	     inf_count, inf->num);

  if (inf->pid != 0)
    {
      struct count_threads_arg count_threads_arg;

      count_threads_arg.pid = inf->pid;
      count_threads_arg.count = 0;
      iterate_over_itset_threads (itset, count_threads_of, &count_threads_arg);
      if (count_threads_arg.count != 0)
	{
	  struct thread_info *thr;

	  if (count_threads_arg.count > 1)
	    warning (_("\
%d threads for inferior %d in the current i/t set, switching to first"),
		     count_threads_arg.count, inf->num);
	  thr = iterate_over_itset_threads (itset, first_thread_of, &inf->pid);
	  switch_to_thread (thr->ptid);
	}
    }
  else
    {
      set_current_inferior (inf);
      switch_to_thread (null_ptid);
      set_current_program_space (inf->pspace);
    }
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
      save_current_itset ();
      current_itset = itset;

      old_chain = make_cleanup_restore_current_thread ();

      switch_to_itset (itset);

      execute_command (spec, from_tty);

      do_cleanups (old_chain);
      return;
    }

  if (itset_is_empty (itset))
    warning (_("focus set is empty"));

  discard_cleanups (old_chain);

  itset_free (current_itset);
  current_itset = itset;

  switch_to_itset (itset);

  /* Confirm the choice of focus.  */
  printf_filtered (_("Current inferior is %d.\n"), current_inferior ()->num);
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

  if (itset_is_static (itset) && itset_is_empty (itset))
    warning (_("static itset is empty"));

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

      if (itset_contains_thread (named_itset->set, thr))
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
  iterate_over_itset_threads (itset, whichsets_callback, NULL);
  do_cleanups (old_chain);
}

static void
viewset (struct itset *itset)
{
  struct inferior *inf;
  struct thread_info *thr;
  int printed;

  printf_filtered ("%s contains:\n",
		   itset_name (itset) ? itset_name (itset) : itset_spec (itset));

  printed = 0;
  ALL_INFERIORS (inf)
    {
      if (itset_contains_inferior (itset, inf))
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
      if (itset_contains_thread (itset, thr))
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
      if (itset_contains_thread (itset, thr))
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

void
_initialize_itset (void)
{
  struct cmd_list_element *c = NULL;

  all_itset = itset_create_all ();
  empty_itset = itset_create_empty ();
  running_itset = itset_create_running ();
  stopped_itset = itset_create_stopped ();
  curinf_itset = itset_create_curinf ();

  make_internal_itset (all_itset, "all");
  make_internal_itset (empty_itset, "empty");
  make_internal_itset (running_itset, "running");
  make_internal_itset (stopped_itset, "stopped");
  make_internal_itset (curinf_itset, "curinf");

  current_itset = itset_reference (all_itset);

  add_com ("itfocus", no_class, itfocus_command, _("\
Change the set of current inferiors/threads."));

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
