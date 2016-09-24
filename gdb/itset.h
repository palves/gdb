/* itset.h - Inferior/Thread sets.
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

#ifndef ITSET_H
#define ITSET_H

struct inferior;
struct thread_info;
struct cleanup;

/* This is an opaque type representing an I/T set.  An I/T set is
   simply a set of inferiors and/or threads.  A set may be dynamic
   (the members are enumerated at the time of use) or static (the
   members are enumerated at the time of construction); but this
   distinction is hidden from the callers.  An I/T set object is
   reference counted.  */

struct itset;

/* Create a new I/T set from a user specification.  The valid forms of
   a specification are documented in the manual.  *SPEC is the input
   specification, and it is updated to point to the first non-space
   character after the end of the specification.  */

struct itset *itset_create (char **spec);

/* Add ADDME to the I/T set TO.  In other words, after the call, TO
   will be the union set of TO at entry, and ADDME.  */

void itset_add_set (struct itset *to, struct itset *addme);

/* Create an empty I/T set.  Usually, an empty set is the set that
   matches nothing.  In some contexts, though, an empty set represents
   some default.  */

struct itset *itset_create_empty (void);

/* Returns true if SET is the empty set.  That is a set whose spec is
   either "" or "empty".  */

int itset_is_empty_set (struct itset *set);

/* Returns true if ITSET is empty.  That is, the set contains no
   inferiors, threads, etc.  */

int itset_is_empty (const struct itset *itset);

/* Create a new dynamic I/T set which represents the current inferior,
   at the time the I/T set if consulted.  */

struct itset *itset_create_current (void);

/* Like itset_create, but if *SPEC does not appear to be the start of
   an I/T set, it will call itset_create_current and return the
   result.  */

struct itset *itset_create_or_default (char **spec);

/* Return true if the inferior is contained in the I/T set.  */

int itset_contains_inferior (struct itset *itset, struct inferior *inf);

/* Return true if the thread is contained in the I/T set.  */

int itset_contains_thread (struct itset *itset, struct thread_info *inf);

/* Return true if the inferior is contained in the I/T set.  */

int itset_member (struct itset *itset, int inf_id, int thread_id);

/* Return a pointer to the I/T set's name.  Unnamed I/T sets have a
   NULL name.  */

const char *itset_name (const struct itset *itset);

/* Return a pointer to the I/T set's spec.  */

const char *itset_spec (const struct itset *itset);

/* Acquire a new reference to an I/T set.  Returns the I/T set, for
   convenience.  */

struct itset *itset_reference (struct itset *itset);

/* Release a reference to an I/T set.  */

void itset_free (struct itset *itset);

struct cleanup *make_cleanup_itset_free (struct itset *itset);

/* A cleanup function that calls itset_free.  */

void itset_cleanup (void *itset);

/* Like iterate_over_inferiors, but iterate over only those inferiors
   in ITSET.  */

typedef int (itset_inf_callback_func) (struct inferior *, void *);
struct inferior *iterate_over_itset_inferiors (struct itset *itset,
					       itset_inf_callback_func *callback,
					       void *data);

/* The current I/T set.  */

extern struct itset *current_itset;

#endif /* ITSET_H */
