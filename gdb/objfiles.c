/* GDB routines for manipulating objfiles.

   Copyright (C) 1992-2016 Free Software Foundation, Inc.

   Contributed by Cygnus Support, using pieces from other GDB modules.

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

/* This file contains support routines for creating, manipulating, and
   destroying objfile structures.  */

#include "defs.h"
#include "bfd.h"		/* Binary File Description */
#include "symtab.h"
#include "symfile.h"
#include "objfiles.h"
#include "gdb-stabs.h"
#include "target.h"
#include "bcache.h"
#include "expression.h"
#include "parser-defs.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "gdb_obstack.h"
#include "hashtab.h"

#include "breakpoint.h"
#include "block.h"
#include "dictionary.h"
#include "source.h"
#include "addrmap.h"
#include "arch-utils.h"
#include "exec.h"
#include "observer.h"
#include "complaints.h"
#include "psymtab.h"
#include "solist.h"
#include "gdb_bfd.h"
#include "btrace.h"

static void add_tail_objfile (struct objfile *objfile);

/* Keep a registry of per-objfile data-pointers required by other GDB
   modules.  */

DEFINE_REGISTRY (objfile, REGISTRY_ACCESS_FIELD)

typedef struct obj_section *obj_section_p;
DEF_VEC_P (obj_section_p);

struct objfile_pspace_info
{
  struct obstack obj_section_map_obstack;
  struct addrmap *obj_section_map;
};

/* Per-program-space data key.  */
static const struct program_space_data *objfiles_pspace_data;

static void
objfiles_pspace_data_cleanup (struct program_space *pspace, void *arg)
{
  struct objfile_pspace_info *info = (struct objfile_pspace_info *) arg;

  obstack_free (&info->obj_section_map_obstack, NULL);
  xfree (info);
}

/* Get the current svr4 data.  If none is found yet, add it now.  This
   function always returns a valid object.  */

static struct objfile_pspace_info *
get_objfile_pspace_data (struct program_space *pspace)
{
  struct objfile_pspace_info *info;

  info = ((struct objfile_pspace_info *)
	  program_space_data (pspace, objfiles_pspace_data));
  if (info == NULL)
    {
      info = XCNEW (struct objfile_pspace_info);
      set_program_space_data (pspace, objfiles_pspace_data, info);

      obstack_init (&info->obj_section_map_obstack);
      info->obj_section_map
	= addrmap_create_mutable (&info->obj_section_map_obstack);
    }

  return info;
}



/* Per-BFD data key.  */

static const struct bfd_data *objfiles_bfd_data;

/* Create the per-BFD storage object for OBJFILE.  If ABFD is not
   NULL, and it already has a per-BFD storage object, use that.
   Otherwise, allocate a new per-BFD storage object.  If ABFD is not
   NULL, the object is allocated on the BFD; otherwise it is allocated
   on OBJFILE's obstack.  Note that it is not safe to call this
   multiple times for a given OBJFILE -- it can only be called when
   allocating or re-initializing OBJFILE.  */

static struct objfile_per_bfd_storage *
get_objfile_bfd_data (struct objfile *objfile, struct bfd *abfd)
{
  struct objfile_per_bfd_storage *storage = NULL;

  if (abfd != NULL)
    storage = ((struct objfile_per_bfd_storage *)
	       bfd_data (abfd, objfiles_bfd_data));

  if (storage == NULL)
    {
      /* If the object requires gdb to do relocations, we simply fall
	 back to not sharing data across users.  These cases are rare
	 enough that this seems reasonable.  */
      if (abfd != NULL && !gdb_bfd_requires_relocations (abfd))
	{
	  storage
	    = ((struct objfile_per_bfd_storage *)
	       bfd_zalloc (abfd, sizeof (struct objfile_per_bfd_storage)));
	  set_bfd_data (abfd, objfiles_bfd_data, storage);
	}
      else
	storage = OBSTACK_ZALLOC (&objfile->objfile_obstack,
				  struct objfile_per_bfd_storage);

      /* Look up the gdbarch associated with the BFD.  */
      if (abfd != NULL)
	storage->gdbarch = gdbarch_from_bfd (abfd);

      obstack_init (&storage->storage_obstack);
      storage->filename_cache = bcache_xmalloc (NULL, NULL);
      storage->macro_cache = bcache_xmalloc (NULL, NULL);
      storage->language_of_main = language_unknown;
    }

  return storage;
}

/* Free STORAGE.  */

static void
free_objfile_per_bfd_storage (struct objfile_per_bfd_storage *storage)
{
  bcache_xfree (storage->filename_cache);
  bcache_xfree (storage->macro_cache);
  if (storage->demangled_names_hash)
    htab_delete (storage->demangled_names_hash);
  obstack_free (&storage->storage_obstack, 0);
}

/* A wrapper for free_objfile_per_bfd_storage that can be passed as a
   cleanup function to the BFD registry.  */

static void
objfile_bfd_data_free (struct bfd *unused, void *d)
{
  free_objfile_per_bfd_storage ((struct objfile_per_bfd_storage *) d);
}

/* See objfiles.h.  */

void
set_objfile_per_bfd (struct objfile *objfile)
{
  objfile->per_bfd = get_objfile_bfd_data (objfile, objfile->obfd);
}

/* Set the objfile's per-BFD notion of the "main" name and
   language.  */

void
set_objfile_main_name (struct objfile *objfile,
		       const char *name, enum language lang)
{
  if (objfile->per_bfd->name_of_main == NULL
      || strcmp (objfile->per_bfd->name_of_main, name) != 0)
    objfile->per_bfd->name_of_main
      = (const char *) obstack_copy0 (&objfile->per_bfd->storage_obstack, name,
				      strlen (name));
  objfile->per_bfd->language_of_main = lang;
}

/* Helper structure to map blocks to static link properties in hash tables.  */

struct static_link_htab_entry
{
  const struct block *block;
  const struct dynamic_prop *static_link;
};

/* Return a hash code for struct static_link_htab_entry *P.  */

static hashval_t
static_link_htab_entry_hash (const void *p)
{
  const struct static_link_htab_entry *e
    = (const struct static_link_htab_entry *) p;

  return htab_hash_pointer (e->block);
}

/* Return whether P1 an P2 (pointers to struct static_link_htab_entry) are
   mappings for the same block.  */

static int
static_link_htab_entry_eq (const void *p1, const void *p2)
{
  const struct static_link_htab_entry *e1
    = (const struct static_link_htab_entry *) p1;
  const struct static_link_htab_entry *e2
    = (const struct static_link_htab_entry *) p2;

  return e1->block == e2->block;
}

/* Register STATIC_LINK as the static link for BLOCK, which is part of OBJFILE.
   Must not be called more than once for each BLOCK.  */

void
objfile_register_static_link (struct objfile *objfile,
			      const struct block *block,
			      const struct dynamic_prop *static_link)
{
  void **slot;
  struct static_link_htab_entry lookup_entry;
  struct static_link_htab_entry *entry;

  if (objfile->static_links == NULL)
    objfile->static_links = htab_create_alloc
      (1, &static_link_htab_entry_hash, static_link_htab_entry_eq, NULL,
       xcalloc, xfree);

  /* Create a slot for the mapping, make sure it's the first mapping for this
     block and then create the mapping itself.  */
  lookup_entry.block = block;
  slot = htab_find_slot (objfile->static_links, &lookup_entry, INSERT);
  gdb_assert (*slot == NULL);

  entry = (struct static_link_htab_entry *) obstack_alloc
	    (&objfile->objfile_obstack, sizeof (*entry));
  entry->block = block;
  entry->static_link = static_link;
  *slot = (void *) entry;
}

/* Look for a static link for BLOCK, which is part of OBJFILE.  Return NULL if
   none was found.  */

const struct dynamic_prop *
objfile_lookup_static_link (struct objfile *objfile,
			    const struct block *block)
{
  struct static_link_htab_entry *entry;
  struct static_link_htab_entry lookup_entry;

  if (objfile->static_links == NULL)
    return NULL;
  lookup_entry.block = block;
  entry
    = (struct static_link_htab_entry *) htab_find (objfile->static_links,
						   &lookup_entry);
  if (entry == NULL)
    return NULL;

  gdb_assert (entry->block == block);
  return entry->static_link;
}



/* Called via bfd_map_over_sections to build up the section table that
   the objfile references.  The objfile contains pointers to the start
   of the table (objfile->sections) and to the first location after
   the end of the table (objfile->sections_end).  */

static void
add_to_objfile_sections_full (struct bfd *abfd, struct bfd_section *asect,
			      struct objfile *objfile, int force)
{
  struct obj_section *section;

  if (!force)
    {
      flagword aflag;

      aflag = bfd_get_section_flags (abfd, asect);
      if (!(aflag & SEC_ALLOC))
	return;
    }

  section = &objfile->sections[gdb_bfd_section_index (abfd, asect)];
  section->objfile = objfile;
  section->the_bfd_section = asect;
  section->ovly_mapped = 0;
}

static void
add_to_objfile_sections (struct bfd *abfd, struct bfd_section *asect,
			 void *objfilep)
{
  add_to_objfile_sections_full (abfd, asect, (struct objfile *) objfilep, 0);
}

/* Builds a section table for OBJFILE.

   Note that the OFFSET and OVLY_MAPPED in each table entry are
   initialized to zero.  */

void
build_objfile_section_table (struct objfile *objfile)
{
  int count = gdb_bfd_count_sections (objfile->obfd);

  objfile->sections = OBSTACK_CALLOC (&objfile->objfile_obstack,
				      count,
				      struct obj_section);
  objfile->sections_end = (objfile->sections + count);
  bfd_map_over_sections (objfile->obfd,
			 add_to_objfile_sections, (void *) objfile);

  /* See gdb_bfd_section_index.  */
  add_to_objfile_sections_full (objfile->obfd, bfd_com_section_ptr, objfile, 1);
  add_to_objfile_sections_full (objfile->obfd, bfd_und_section_ptr, objfile, 1);
  add_to_objfile_sections_full (objfile->obfd, bfd_abs_section_ptr, objfile, 1);
  add_to_objfile_sections_full (objfile->obfd, bfd_ind_section_ptr, objfile, 1);
}

/* Given a pointer to an initialized bfd (ABFD) and some flag bits
   allocate a new objfile struct, fill it in as best we can, link it
   into the list of all known objfiles, and return a pointer to the
   new objfile struct.

   NAME should contain original non-canonicalized filename or other
   identifier as entered by user.  If there is no better source use
   bfd_get_filename (ABFD).  NAME may be NULL only if ABFD is NULL.
   NAME content is copied into returned objfile.

   The FLAGS word contains various bits (OBJF_*) that can be taken as
   requests for specific operations.  Other bits like OBJF_SHARED are
   simply copied through to the new objfile flags member.  */

/* NOTE: carlton/2003-02-04: This function is called with args NULL, 0
   by jv-lang.c, to create an artificial objfile used to hold
   information about dynamically-loaded Java classes.  Unfortunately,
   that branch of this function doesn't get tested very frequently, so
   it's prone to breakage.  (E.g. at one time the name was set to NULL
   in that situation, which broke a loop over all names in the dynamic
   library loader.)  If you change this function, please try to leave
   things in a consistent state even if abfd is NULL.  */

struct objfile *
allocate_objfile (bfd *abfd, const char *name, int flags)
{
  struct objfile *objfile;
  char *expanded_name;

  objfile = XCNEW (struct objfile);
  objfile->psymbol_cache = psymbol_bcache_init ();
  /* We could use obstack_specify_allocation here instead, but
     gdb_obstack.h specifies the alloc/dealloc functions.  */
  obstack_init (&objfile->objfile_obstack);

  objfile_alloc_data (objfile);

  if (name == NULL)
    {
      gdb_assert (abfd == NULL);
      gdb_assert ((flags & OBJF_NOT_FILENAME) != 0);
      expanded_name = xstrdup ("<<anonymous objfile>>");
    }
  else if ((flags & OBJF_NOT_FILENAME) != 0
	   || is_target_filename (name))
    expanded_name = xstrdup (name);
  else
    expanded_name = gdb_abspath (name);
  objfile->original_name
    = (char *) obstack_copy0 (&objfile->objfile_obstack,
			      expanded_name,
			      strlen (expanded_name));
  xfree (expanded_name);

  /* Update the per-objfile information that comes from the bfd, ensuring
     that any data that is reference is saved in the per-objfile data
     region.  */

  objfile->obfd = abfd;
  gdb_bfd_ref (abfd);
  if (abfd != NULL)
    {
      objfile->mtime = bfd_get_mtime (abfd);

      /* Build section table.  */
      build_objfile_section_table (objfile);
    }

  objfile->per_bfd = get_objfile_bfd_data (objfile, abfd);
  objfile->pspace = current_program_space;

  terminate_minimal_symbol_table (objfile);

  /* Initialize the section indexes for this objfile, so that we can
     later detect if they are used w/o being properly assigned to.  */

  objfile->sect_index_text = -1;
  objfile->sect_index_data = -1;
  objfile->sect_index_bss = -1;
  objfile->sect_index_rodata = -1;

  add_tail_objfile (objfile);

  /* Save passed in flag bits.  */
  objfile->flags |= flags;

  return objfile;
}

/* Retrieve the gdbarch associated with OBJFILE.  */

struct gdbarch *
get_objfile_arch (const struct objfile *objfile)
{
  return objfile->per_bfd->gdbarch;
}

/* If there is a valid and known entry point, function fills *ENTRY_P with it
   and returns non-zero; otherwise it returns zero.  */

int
entry_point_address_query (CORE_ADDR *entry_p)
{
  if (symfile_objfile == NULL || !symfile_objfile->per_bfd->ei.entry_point_p)
    return 0;

  *entry_p = (symfile_objfile->per_bfd->ei.entry_point
	      + ANOFFSET (symfile_objfile->section_offsets,
			  symfile_objfile->per_bfd->ei.the_bfd_section_index));

  return 1;
}

/* Get current entry point address.  Call error if it is not known.  */

CORE_ADDR
entry_point_address (void)
{
  CORE_ADDR retval;

  if (!entry_point_address_query (&retval))
    error (_("Entry point address is not known."));

  return retval;
}

/* Iterator on PARENT and every separate debug objfile of PARENT.
   The usage pattern is:
     for (objfile = parent;
          objfile;
          objfile = objfile_separate_debug_iterate (parent, objfile))
       ...
*/

struct objfile *
objfile_separate_debug_iterate (const struct objfile *parent,
                                const struct objfile *objfile)
{
  struct objfile *res;

  /* If any, return the first child.  */
  res = objfile->separate_debug_objfile;
  if (res)
    return res;

  /* Common case where there is no separate debug objfile.  */
  if (objfile == parent)
    return NULL;

  /* Return the brother if any.  Note that we don't iterate on brothers of
     the parents.  */
  res = objfile->separate_debug_objfile_link;
  if (res)
    return res;

  for (res = objfile->separate_debug_objfile_backlink;
       res != parent;
       res = res->separate_debug_objfile_backlink)
    {
      gdb_assert (res != NULL);
      if (res->separate_debug_objfile_link)
        return res->separate_debug_objfile_link;
    }
  return NULL;
}

/* Put one object file before a specified one in the global list.
   This can be used to make sure an object file is destroyed before
   another when using ALL_OBJFILES_SAFE to free all objfiles.  */

static void
put_objfile_before (struct objfile *objfile, struct objfile *before_this)
{
  struct objfile **objp;

  gdb_assert (objfile != NULL && before_this != NULL);
  gdb_assert (objfile != before_this);

  unlink_objfile (objfile);

  objfile->next = before_this;
  objfile->prev = before_this->prev;

  if (before_this == objfile->pspace->objfiles)
    objfile->pspace->objfiles = objfile;
  else
    before_this->prev->next = objfile;

  if (objfile == objfile->pspace->objfiles_tail)
    objfile->pspace->objfiles_tail = before_this;

  before_this->prev = objfile;
}

/* Add this file onto the tail of the linked list of other such
   files.  */

static void
add_tail_objfile (struct objfile *objfile)
{
  gdb_assert (objfile != NULL);

  if (objfile->pspace->objfiles == NULL)
    {
      objfile->pspace->objfiles = objfile;
      objfile->pspace->objfiles_tail = objfile;
    }
  else
    {
      struct objfile *last_one = objfile->pspace->objfiles_tail;

      gdb_assert (objfile != last_one);

      last_one->next = objfile;
      objfile->prev = last_one;

      objfile->pspace->objfiles_tail = objfile;
    }
}

/* Unlink OBJFILE from the list of known objfiles.  OBJFILE must be in
   the list.  */

void
unlink_objfile (struct objfile *objfile)
{
  if (objfile->prev == NULL)
    objfile->pspace->objfiles = objfile->next;
  else
    objfile->prev->next = objfile->next;

  if (objfile->next == NULL)
    objfile->pspace->objfiles_tail = objfile->prev;
  else
    objfile->next->prev = objfile->prev;

  objfile->prev = NULL;
  objfile->next = NULL;
}

/* Add OBJFILE as a separate debug objfile of PARENT.  */

void
add_separate_debug_objfile (struct objfile *objfile, struct objfile *parent)
{
  gdb_assert (objfile && parent);

  /* Must not be already in a list.  */
  gdb_assert (objfile->separate_debug_objfile_backlink == NULL);
  gdb_assert (objfile->separate_debug_objfile_link == NULL);
  gdb_assert (objfile->separate_debug_objfile == NULL);
  gdb_assert (parent->separate_debug_objfile_backlink == NULL);
  gdb_assert (parent->separate_debug_objfile_link == NULL);

  objfile->separate_debug_objfile_backlink = parent;
  objfile->separate_debug_objfile_link = parent->separate_debug_objfile;
  parent->separate_debug_objfile = objfile;

  /* Put the separate debug object before the normal one, this is so that
     usage of the ALL_OBJFILES_SAFE macro will stay safe.  */
  put_objfile_before (objfile, parent);
}

/* Free all separate debug objfile of OBJFILE, but don't free OBJFILE
   itself.  */

void
free_objfile_separate_debug (struct objfile *objfile)
{
  struct objfile *child;

  for (child = objfile->separate_debug_objfile; child;)
    {
      struct objfile *next_child = child->separate_debug_objfile_link;
      free_objfile (child);
      child = next_child;
    }
}

/* Destroy an objfile and all the symtabs and psymtabs under it.  */

void
free_objfile (struct objfile *objfile)
{
  /* First notify observers that this objfile is about to be freed.  */
  observer_notify_free_objfile (objfile);

  /* Do this before deleting the bfd, as this references the bfd
     sections.  */
  obj_section_map_remove_objfile (objfile);

  /* Free all separate debug objfiles.  */
  free_objfile_separate_debug (objfile);

  if (objfile->separate_debug_objfile_backlink)
    {
      /* We freed the separate debug file, make sure the base objfile
	 doesn't reference it.  */
      struct objfile *child;

      child = objfile->separate_debug_objfile_backlink->separate_debug_objfile;

      if (child == objfile)
        {
          /* OBJFILE is the first child.  */
          objfile->separate_debug_objfile_backlink->separate_debug_objfile =
            objfile->separate_debug_objfile_link;
        }
      else
        {
          /* Find OBJFILE in the list.  */
          while (1)
            {
              if (child->separate_debug_objfile_link == objfile)
                {
                  child->separate_debug_objfile_link =
                    objfile->separate_debug_objfile_link;
                  break;
                }
              child = child->separate_debug_objfile_link;
              gdb_assert (child);
            }
        }
    }
  
  /* Remove any references to this objfile in the global value
     lists.  */
  preserve_values (objfile);

  /* It still may reference data modules have associated with the objfile and
     the symbol file data.  */
  forget_cached_source_info_for_objfile (objfile);

  breakpoint_free_objfile (objfile);
  btrace_free_objfile (objfile);

  /* First do any symbol file specific actions required when we are
     finished with a particular symbol file.  Note that if the objfile
     is using reusable symbol information (via mmalloc) then each of
     these routines is responsible for doing the correct thing, either
     freeing things which are valid only during this particular gdb
     execution, or leaving them to be reused during the next one.  */

  if (objfile->sf != NULL)
    {
      (*objfile->sf->sym_finish) (objfile);
    }

  /* Discard any data modules have associated with the objfile.  The function
     still may reference objfile->obfd.  */
  objfile_free_data (objfile);

  if (objfile->obfd)
    gdb_bfd_unref (objfile->obfd);
  else
    free_objfile_per_bfd_storage (objfile->per_bfd);

  /* Remove it from the chain of all objfiles.  */

  unlink_objfile (objfile);

  if (objfile == symfile_objfile)
    symfile_objfile = NULL;

  /* Before the symbol table code was redone to make it easier to
     selectively load and remove information particular to a specific
     linkage unit, gdb used to do these things whenever the monolithic
     symbol table was blown away.  How much still needs to be done
     is unknown, but we play it safe for now and keep each action until
     it is shown to be no longer needed.  */

  /* Not all our callers call clear_symtab_users (objfile_purge_solibs,
     for example), so we need to call this here.  */
  clear_pc_function_cache ();

  /* Clear globals which might have pointed into a removed objfile.
     FIXME: It's not clear which of these are supposed to persist
     between expressions and which ought to be reset each time.  */
  expression_context_block = NULL;
  innermost_block = NULL;

  /* Check to see if the current_source_symtab belongs to this objfile,
     and if so, call clear_current_source_symtab_and_line.  */

  {
    struct symtab_and_line cursal = get_current_source_symtab_and_line ();

    if (cursal.symtab && SYMTAB_OBJFILE (cursal.symtab) == objfile)
      clear_current_source_symtab_and_line ();
  }

  if (objfile->global_psymbols.list)
    xfree (objfile->global_psymbols.list);
  if (objfile->static_psymbols.list)
    xfree (objfile->static_psymbols.list);
  /* Free the obstacks for non-reusable objfiles.  */
  psymbol_bcache_free (objfile->psymbol_cache);
  obstack_free (&objfile->objfile_obstack, 0);

  /* Free the map for static links.  There's no need to free static link
     themselves since they were allocated on the objstack.  */
  if (objfile->static_links != NULL)
    htab_delete (objfile->static_links);

  /* The last thing we do is free the objfile struct itself.  */
  xfree (objfile);
}

static void
do_free_objfile_cleanup (void *obj)
{
  free_objfile ((struct objfile *) obj);
}

struct cleanup *
make_cleanup_free_objfile (struct objfile *obj)
{
  return make_cleanup (do_free_objfile_cleanup, obj);
}

/* Free all the object files at once and clean up their users.  */

void
free_all_objfiles (void)
{
  struct objfile *objfile, *temp;
  struct so_list *so;

  /* Any objfile referencewould become stale.  */
  for (so = master_so_list (); so; so = so->next)
    gdb_assert (so->objfile == NULL);

  ALL_OBJFILES_SAFE (objfile, temp)
  {
    free_objfile (objfile);
  }
  clear_symtab_users (0);
}

/* A helper function for objfile_relocate1 that relocates a single
   symbol.  */

static void
relocate_one_symbol (struct symbol *sym, struct objfile *objfile,
		     struct section_offsets *delta)
{
  fixup_symbol_section (sym, objfile);

  /* The RS6000 code from which this was taken skipped
     any symbols in STRUCT_DOMAIN or UNDEF_DOMAIN.
     But I'm leaving out that test, on the theory that
     they can't possibly pass the tests below.  */
  if ((SYMBOL_CLASS (sym) == LOC_LABEL
       || SYMBOL_CLASS (sym) == LOC_STATIC)
      && SYMBOL_SECTION (sym) >= 0)
    {
      SYMBOL_VALUE_ADDRESS (sym) += ANOFFSET (delta, SYMBOL_SECTION (sym));
    }
}

/* Relocate OBJFILE to NEW_OFFSETS.  There should be OBJFILE->NUM_SECTIONS
   entries in new_offsets.  SEPARATE_DEBUG_OBJFILE is not touched here.
   Return non-zero iff any change happened.  */

static int
objfile_relocate1 (struct objfile *objfile, 
		   const struct section_offsets *new_offsets)
{
  struct obj_section *s;
  struct section_offsets *delta =
    ((struct section_offsets *) 
     alloca (SIZEOF_N_SECTION_OFFSETS (objfile->num_sections)));

  int i;
  int something_changed = 0;

  for (i = 0; i < objfile->num_sections; ++i)
    {
      delta->offsets[i] =
	ANOFFSET (new_offsets, i) - ANOFFSET (objfile->section_offsets, i);
      if (ANOFFSET (delta, i) != 0)
	something_changed = 1;
    }
  if (!something_changed)
    return 0;

  /* OK, get all the symtabs.  */
  {
    struct compunit_symtab *cust;
    struct symtab *s;

    ALL_OBJFILE_FILETABS (objfile, cust, s)
    {
      struct linetable *l;
      int i;

      /* First the line table.  */
      l = SYMTAB_LINETABLE (s);
      if (l)
	{
	  for (i = 0; i < l->nitems; ++i)
	    l->item[i].pc += ANOFFSET (delta,
				       COMPUNIT_BLOCK_LINE_SECTION
					 (cust));
	}
    }

    ALL_OBJFILE_COMPUNITS (objfile, cust)
    {
      const struct blockvector *bv = COMPUNIT_BLOCKVECTOR (cust);
      int block_line_section = COMPUNIT_BLOCK_LINE_SECTION (cust);

      if (BLOCKVECTOR_MAP (bv))
	addrmap_relocate (BLOCKVECTOR_MAP (bv),
			  ANOFFSET (delta, block_line_section));

      for (i = 0; i < BLOCKVECTOR_NBLOCKS (bv); ++i)
	{
	  struct block *b;
	  struct symbol *sym;
	  struct dict_iterator iter;

	  b = BLOCKVECTOR_BLOCK (bv, i);
	  BLOCK_START (b) += ANOFFSET (delta, block_line_section);
	  BLOCK_END (b) += ANOFFSET (delta, block_line_section);

	  /* We only want to iterate over the local symbols, not any
	     symbols in included symtabs.  */
	  ALL_DICT_SYMBOLS (BLOCK_DICT (b), iter, sym)
	    {
	      relocate_one_symbol (sym, objfile, delta);
	    }
	}
    }
  }

  /* Relocate isolated symbols.  */
  {
    struct symbol *iter;

    for (iter = objfile->template_symbols; iter; iter = iter->hash_next)
      relocate_one_symbol (iter, objfile, delta);
  }

  if (objfile->psymtabs_addrmap)
    addrmap_relocate (objfile->psymtabs_addrmap,
		      ANOFFSET (delta, SECT_OFF_TEXT (objfile)));

  if (objfile->sf)
    objfile->sf->qf->relocate (objfile, new_offsets, delta);

  obj_section_map_remove_objfile (objfile);

  {
    int i;

    for (i = 0; i < objfile->num_sections; ++i)
      (objfile->section_offsets)->offsets[i] = ANOFFSET (new_offsets, i);
  }

  obj_section_map_add_objfile (objfile);

  /* Update the table in exec_ops, used to read memory.  */
  ALL_OBJFILE_OSECTIONS (objfile, s)
    {
      int idx = s - objfile->sections;

      exec_set_section_address (bfd_get_filename (objfile->obfd), idx,
				obj_section_addr (s));
    }

  /* Data changed.  */
  return 1;
}

/* Relocate OBJFILE to NEW_OFFSETS.  There should be OBJFILE->NUM_SECTIONS
   entries in new_offsets.  Process also OBJFILE's SEPARATE_DEBUG_OBJFILEs.

   The number and ordering of sections does differ between the two objfiles.
   Only their names match.  Also the file offsets will differ (objfile being
   possibly prelinked but separate_debug_objfile is probably not prelinked) but
   the in-memory absolute address as specified by NEW_OFFSETS must match both
   files.  */

void
objfile_relocate (struct objfile *objfile,
		  const struct section_offsets *new_offsets)
{
  struct objfile *debug_objfile;
  int changed = 0;

  changed |= objfile_relocate1 (objfile, new_offsets);

  for (debug_objfile = objfile->separate_debug_objfile;
       debug_objfile;
       debug_objfile = objfile_separate_debug_iterate (objfile, debug_objfile))
    {
      struct section_addr_info *objfile_addrs;
      struct section_offsets *new_debug_offsets;
      struct cleanup *my_cleanups;

      objfile_addrs = build_section_addr_info_from_objfile (objfile);
      my_cleanups = make_cleanup (xfree, objfile_addrs);

      /* Here OBJFILE_ADDRS contain the correct absolute addresses, the
	 relative ones must be already created according to debug_objfile.  */

      addr_info_make_relative (objfile_addrs, debug_objfile->obfd);

      gdb_assert (debug_objfile->num_sections
		  == gdb_bfd_count_sections (debug_objfile->obfd));
      new_debug_offsets = 
	((struct section_offsets *)
	 xmalloc (SIZEOF_N_SECTION_OFFSETS (debug_objfile->num_sections)));
      make_cleanup (xfree, new_debug_offsets);
      relative_addr_info_to_section_offsets (new_debug_offsets,
					     debug_objfile->num_sections,
					     objfile_addrs);

      changed |= objfile_relocate1 (debug_objfile, new_debug_offsets);

      do_cleanups (my_cleanups);
    }

  /* Relocate breakpoints as necessary, after things are relocated.  */
  if (changed)
    breakpoint_re_set ();
}

/* Rebase (add to the offsets) OBJFILE by SLIDE.  SEPARATE_DEBUG_OBJFILE is
   not touched here.
   Return non-zero iff any change happened.  */

static int
objfile_rebase1 (struct objfile *objfile, CORE_ADDR slide)
{
  struct section_offsets *new_offsets =
    ((struct section_offsets *)
     alloca (SIZEOF_N_SECTION_OFFSETS (objfile->num_sections)));
  int i;

  for (i = 0; i < objfile->num_sections; ++i)
    new_offsets->offsets[i] = slide;

  return objfile_relocate1 (objfile, new_offsets);
}

/* Rebase (add to the offsets) OBJFILE by SLIDE.  Process also OBJFILE's
   SEPARATE_DEBUG_OBJFILEs.  */

void
objfile_rebase (struct objfile *objfile, CORE_ADDR slide)
{
  struct objfile *debug_objfile;
  int changed = 0;

  changed |= objfile_rebase1 (objfile, slide);

  for (debug_objfile = objfile->separate_debug_objfile;
       debug_objfile;
       debug_objfile = objfile_separate_debug_iterate (objfile, debug_objfile))
    changed |= objfile_rebase1 (debug_objfile, slide);

  /* Relocate breakpoints as necessary, after things are relocated.  */
  if (changed)
    breakpoint_re_set ();
}

/* Return non-zero if OBJFILE has partial symbols.  */

int
objfile_has_partial_symbols (struct objfile *objfile)
{
  if (!objfile->sf)
    return 0;

  /* If we have not read psymbols, but we have a function capable of reading
     them, then that is an indication that they are in fact available.  Without
     this function the symbols may have been already read in but they also may
     not be present in this objfile.  */
  if ((objfile->flags & OBJF_PSYMTABS_READ) == 0
      && objfile->sf->sym_read_psymbols != NULL)
    return 1;

  return objfile->sf->qf->has_symbols (objfile);
}

/* Return non-zero if OBJFILE has full symbols.  */

int
objfile_has_full_symbols (struct objfile *objfile)
{
  return objfile->compunit_symtabs != NULL;
}

/* Return non-zero if OBJFILE has full or partial symbols, either directly
   or through a separate debug file.  */

int
objfile_has_symbols (struct objfile *objfile)
{
  struct objfile *o;

  for (o = objfile; o; o = objfile_separate_debug_iterate (objfile, o))
    if (objfile_has_partial_symbols (o) || objfile_has_full_symbols (o))
      return 1;
  return 0;
}


/* Many places in gdb want to test just to see if we have any partial
   symbols available.  This function returns zero if none are currently
   available, nonzero otherwise.  */

int
have_partial_symbols (void)
{
  struct objfile *ofp;

  ALL_OBJFILES (ofp)
  {
    if (objfile_has_partial_symbols (ofp))
      return 1;
  }
  return 0;
}

/* Many places in gdb want to test just to see if we have any full
   symbols available.  This function returns zero if none are currently
   available, nonzero otherwise.  */

int
have_full_symbols (void)
{
  struct objfile *ofp;

  ALL_OBJFILES (ofp)
  {
    if (objfile_has_full_symbols (ofp))
      return 1;
  }
  return 0;
}


/* This operations deletes all objfile entries that represent solibs that
   weren't explicitly loaded by the user, via e.g., the add-symbol-file
   command.  */

void
objfile_purge_solibs (void)
{
  struct objfile *objf;
  struct objfile *temp;

  ALL_OBJFILES_SAFE (objf, temp)
  {
    /* We assume that the solib package has been purged already, or will
       be soon.  */

    if (!(objf->flags & OBJF_USERLOADED) && (objf->flags & OBJF_SHARED))
      free_objfile (objf);
  }
}


/* Many places in gdb want to test just to see if we have any minimal
   symbols available.  This function returns zero if none are currently
   available, nonzero otherwise.  */

int
have_minimal_symbols (void)
{
  struct objfile *ofp;

  ALL_OBJFILES (ofp)
  {
    if (ofp->per_bfd->minimal_symbol_count > 0)
      {
	return 1;
      }
  }
  return 0;
}

static struct obj_section *preferred_obj_section (struct obj_section *a,
						  struct obj_section *b);

/* Returns true if the first argument is strictly less than the
   second, useful for VEC_lower_bound.  We keep sections sorted by
   starting address.  */

static int
obj_section_lessthan (struct obj_section *sect1, struct obj_section *sect2)
{
  const struct objfile *const objfile1 = sect1->objfile;
  const struct objfile *const objfile2 = sect2->objfile;
  const CORE_ADDR sect1_addr = obj_section_addr (sect1);
  const CORE_ADDR sect2_addr = obj_section_addr (sect2);

  gdb_assert (objfile1->pspace == objfile2->pspace);

  /* We use VEC_lower_bound to find the element's index, in order to
     remove it.  Avoid falling into the degenerate/ slow "Case B"
     below.  */
  if (sect1 == sect2)
    return 0;

  if (sect1_addr == sect2_addr)
    {
      /* Sections are at the same address.  This could happen if
	 A) we have an objfile and a separate debuginfo.
	 B) we are confused, and have added sections without proper relocation,
	 or something like that.  */

      if (objfile1->separate_debug_objfile == objfile2
	  || objfile2->separate_debug_objfile == objfile1)
	{
	  /* Order "better" sections first.  We prefer the one that came
	     from the real object, rather than the one from separate
	     debuginfo.  */
	  return preferred_obj_section (sect1, sect2) == sect1;
	}

      /* Case B.  Maintain stable sort order, so bugs in GDB are easier to
	 triage.  This section could be slow (since we iterate over all
	 objfiles in each call to qsort_cmp), but this shouldn't happen
	 very often (GDB is already in a confused state; one hopes this
	 doesn't happen at all).  If you discover that significant time is
	 spent in the loops below, do 'set complaints 100' and examine the
	 resulting complaints.  */

      if (objfile1 == objfile2)
	{
	  /* Both sections came from the same objfile.  We are really confused.
	     Sort on sequence order of sections within the objfile.  */

	  const struct obj_section *osect;

	  ALL_OBJFILE_OSECTIONS (objfile1, osect)
	    if (osect == sect1)
	      return 1;
	    else if (osect == sect2)
	      return 0;

	  /* We should have found one of the sections before getting here.  */
	  gdb_assert_not_reached ("section not found");
	}
      else
	{
	  /* Sort on sequence number of the objfile in the chain.  */

	  const struct objfile *objfile;

	  ALL_PSPACE_OBJFILES (objfile1->pspace, objfile)
	    if (objfile == objfile1)
	      return 1;
	    else if (objfile == objfile2)
	      return 0;

	  /* We should have found one of the objfiles before getting here.  */
	  gdb_assert_not_reached ("objfile not found");
	}
    }

  return sect1_addr < sect2_addr;
}

/* Select which obj_section is "better".  We prefer the one that came
   from the real object, rather than the one from separate debuginfo.
   Most of the time the two sections are exactly identical, but with
   prelinking the .rel.dyn section in the real object may have different
   size.  */

static struct obj_section *
preferred_obj_section (struct obj_section *a, struct obj_section *b)
{
  gdb_assert (obj_section_addr (a) == obj_section_addr (b));
  gdb_assert ((a->objfile->separate_debug_objfile == b->objfile)
	      || (b->objfile->separate_debug_objfile == a->objfile));
  gdb_assert ((a->objfile->separate_debug_objfile_backlink == b->objfile)
	      || (b->objfile->separate_debug_objfile_backlink == a->objfile));

  if (a->objfile->separate_debug_objfile != NULL)
    return a;
  return b;
}

/* Return 1 if SECTION should be inserted into the section map.
   We want to insert only non-overlay and non-TLS section.  */

static int
insert_section_p (const struct bfd *abfd,
		  const struct bfd_section *section)
{
  const bfd_vma lma = bfd_section_lma (abfd, section);

  if (overlay_debugging && lma != 0 && lma != bfd_section_vma (abfd, section)
      && (bfd_get_file_flags (abfd) & BFD_IN_MEMORY) == 0)
    /* This is an overlay section.  IN_MEMORY check is needed to avoid
       discarding sections from the "system supplied DSO" (aka vdso)
       on some Linux systems (e.g. Fedora 11).  */
    return 0;
  if ((bfd_get_section_flags (abfd, section) & SEC_THREAD_LOCAL) != 0)
    /* This is a TLS section.  */
    return 0;

  return 1;
}


/*
| A                       |
               |  B |
                      |  C   |
*/

/* Issue a complaint about overlapping sections.  Overlapping sections
   could really be overlay sections which we didn't classify as such
   in insert_section_p, or we could be dealing with a corrupt
   binary.  */

static void
complaint_overlapping_sections (struct obj_section **map, int map_size)
{
  int i;

  for (i = 0; i < map_size - 1; )
    {
      int k;

      for (k = i + 1; k < map_size; k++)
	{
	  struct obj_section *const sect1 = map[i];
	  struct obj_section *const sect2 = map[k];
	  const struct objfile *const objfile1 = sect1->objfile;
	  const struct objfile *const objfile2 = sect2->objfile;
	  const CORE_ADDR sect1_addr = obj_section_addr (sect1);
	  const CORE_ADDR sect2_addr = obj_section_addr (sect2);
	  const CORE_ADDR sect1_endaddr = obj_section_endaddr (sect1);

	  gdb_assert (sect1_addr <= sect2_addr);

	  if (sect1_addr == sect2_addr
	      && (objfile1->separate_debug_objfile == objfile2
		  || objfile2->separate_debug_objfile == objfile1))
	    continue;

	  if (sect1_endaddr <= sect2_addr)
	    break;
	  else
	    {
	      /* We have an overlap.  Report it.  */

	      struct objfile *const objf1 = sect1->objfile;
	      struct objfile *const objf2 = sect2->objfile;

	      const struct bfd_section *const bfds1 = sect1->the_bfd_section;
	      const struct bfd_section *const bfds2 = sect2->the_bfd_section;

	      const CORE_ADDR sect2_endaddr = obj_section_endaddr (sect2);

	      struct gdbarch *const gdbarch = get_objfile_arch (objf1);

	      complaint (&symfile_complaints,
			 _("unexpected overlap between:\n"
			   " (A) section `%s' from `%s' [%s, %s)\n"
			   " (B) section `%s' from `%s' [%s, %s).\n"
			   "Will ignore section B"),
			 bfd_section_name (abfd1, bfds1), objfile_name (objf1),
			 paddress (gdbarch, sect1_addr),
			 paddress (gdbarch, sect1_endaddr),
			 bfd_section_name (abfd2, bfds2), objfile_name (objf2),
			 paddress (gdbarch, sect2_addr),
			 paddress (gdbarch, sect2_endaddr));
	    }
	}
      i = k;
    }
}

struct obj_section_map_addrmap_value
{
  VEC (obj_section_p) *sections;
};

static void *
obj_section_map_addrmap_remove_section_cb (void *cb_data, void *curr_val)
{
  struct obj_section_map_addrmap_value *sect_map_val = curr_val;
  struct obj_section *s = cb_data;
  struct obj_section *removed;
  int i;

  gdb_assert (sect_map_val != NULL);

  i = VEC_lower_bound (obj_section_p, sect_map_val->sections, s,
		       obj_section_lessthan);
  removed = VEC_ordered_remove (obj_section_p, sect_map_val->sections, i);
  gdb_assert (removed == s);

  if (VEC_empty (obj_section_p, sect_map_val->sections))
    {
      VEC_free (obj_section_p, sect_map_val->sections);
      return NULL;
    }
  return sect_map_val;
}

void
obj_section_map_remove_objfile (struct objfile *objfile)
{
  struct objfile_pspace_info *pspace_info;
  struct obj_section *s;

  if ((objfile->flags & OBJF_IN_SECTIONS_MAP) == 0)
    return;

  pspace_info = get_objfile_pspace_data (objfile->pspace);

  ALL_OBJFILE_OSECTIONS (objfile, s)
    if (insert_section_p (objfile->obfd, s->the_bfd_section))
      {
	CORE_ADDR addr = obj_section_addr (s);
	CORE_ADDR endaddr = obj_section_endaddr (s);

	if (addr != endaddr)
	  addrmap_subregion_update (pspace_info->obj_section_map,
				    addr, endaddr - 1,
				    obj_section_map_addrmap_remove_section_cb,
				    s);
      }
}

static void *
obj_section_map_addrmap_add_section_cb (void *cb_data, void *curr_val)
{
  struct obj_section_map_addrmap_value *sect_map_val = curr_val;
  struct obj_section *new_sect = cb_data;
  size_t sections_size;
  int i;

  if (sect_map_val == NULL)
    sect_map_val = XCNEW (struct obj_section_map_addrmap_value);

  i = VEC_lower_bound (obj_section_p, sect_map_val->sections,
		       new_sect, obj_section_lessthan);
  VEC_safe_insert (obj_section_p, sect_map_val->sections, i, new_sect);

  /* Check that looking up the obj_section with VEC_lower_bound finds
     it again correctly.  This is a debugging aid, disabled by
     default, because it isn't free.  */
  if (0)
    {
      struct obj_section *found;
      int j;

      j = VEC_lower_bound (obj_section_p, sect_map_val->sections, new_sect,
			   obj_section_lessthan);
      found = VEC_index (obj_section_p, sect_map_val->sections, j);
      gdb_assert (found == new_sect);
    }

  sections_size = VEC_length (obj_section_p, sect_map_val->sections);
  if (sections_size > 1)
    {
      struct obj_section **sections;

      sections = VEC_address (obj_section_p, sect_map_val->sections);
      complaint_overlapping_sections (sections, sections_size);
    }

  return sect_map_val;
}

void
obj_section_map_add_objfile (struct objfile *objfile)
{
  struct objfile_pspace_info *pspace_info;
  struct obj_section *s;

  pspace_info = get_objfile_pspace_data (objfile->pspace);

  objfile->flags |= OBJF_IN_SECTIONS_MAP;

  ALL_OBJFILE_OSECTIONS (objfile, s)
    if (insert_section_p (objfile->obfd, s->the_bfd_section))
      {
	CORE_ADDR addr = obj_section_addr (s);
	CORE_ADDR endaddr = obj_section_endaddr (s);

	if (addr != endaddr)
	  addrmap_subregion_update (pspace_info->obj_section_map,
				    addr, endaddr - 1,
				    obj_section_map_addrmap_add_section_cb,
				    s);
      }
}

/* Returns a section whose range includes PC or NULL if none found.   */

struct obj_section *
find_pc_section (CORE_ADDR pc)
{
  struct objfile_pspace_info *pspace_info;
  struct obj_section *s;
  struct obj_section_map_addrmap_value *sect_map_val;

  /* Check for mapped overlay section first.  */
  s = find_pc_mapped_section (pc);
  if (s)
    return s;

  pspace_info = get_objfile_pspace_data (current_program_space);

  sect_map_val = addrmap_find (pspace_info->obj_section_map, pc);
  if (sect_map_val != NULL)
    {
      int ix;

      for (ix = 0;
	   VEC_iterate (obj_section_p, sect_map_val->sections, ix, s);
	   ++ix)
	if (obj_section_addr (s) <= pc && pc < obj_section_endaddr (s))
	  return s;

      gdb_assert_not_reached ("section not found");
    }
  return NULL;
}


/* Return non-zero if PC is in a section called NAME.  */

int
pc_in_section (CORE_ADDR pc, char *name)
{
  struct obj_section *s;
  int retval = 0;

  s = find_pc_section (pc);

  retval = (s != NULL
	    && s->the_bfd_section->name != NULL
	    && strcmp (s->the_bfd_section->name, name) == 0);
  return (retval);
}


/* Return 1 if ADDR maps into one of the sections of OBJFILE and 0
   otherwise.  */

int
is_addr_in_objfile (CORE_ADDR addr, const struct objfile *objfile)
{
  struct obj_section *osect;

  if (objfile == NULL)
    return 0;

  ALL_OBJFILE_OSECTIONS (objfile, osect)
    {
      if (section_is_overlay (osect) && !section_is_mapped (osect))
	continue;

      if (obj_section_addr (osect) <= addr
	  && addr < obj_section_endaddr (osect))
	return 1;
    }
  return 0;
}

int
shared_objfile_contains_address_p (struct program_space *pspace,
				   CORE_ADDR address)
{
  struct objfile *objfile;

  ALL_PSPACE_OBJFILES (pspace, objfile)
    {
      if ((objfile->flags & OBJF_SHARED) != 0
	  && is_addr_in_objfile (address, objfile))
	return 1;
    }

  return 0;
}

/* The default implementation for the "iterate_over_objfiles_in_search_order"
   gdbarch method.  It is equivalent to use the ALL_OBJFILES macro,
   searching the objfiles in the order they are stored internally,
   ignoring CURRENT_OBJFILE.

   On most platorms, it should be close enough to doing the best
   we can without some knowledge specific to the architecture.  */

void
default_iterate_over_objfiles_in_search_order
  (struct gdbarch *gdbarch,
   iterate_over_objfiles_in_search_order_cb_ftype *cb,
   void *cb_data, struct objfile *current_objfile)
{
  int stop = 0;
  struct objfile *objfile;

  ALL_OBJFILES (objfile)
    {
       stop = cb (objfile, cb_data);
       if (stop)
	 return;
    }
}

/* See objfiles.h.  */

const char *
objfile_name (const struct objfile *objfile)
{
  if (objfile->obfd != NULL)
    return bfd_get_filename (objfile->obfd);

  return objfile->original_name;
}

/* See objfiles.h.  */

const char *
objfile_filename (const struct objfile *objfile)
{
  if (objfile->obfd != NULL)
    return bfd_get_filename (objfile->obfd);

  return NULL;
}

/* See objfiles.h.  */

const char *
objfile_debug_name (const struct objfile *objfile)
{
  return lbasename (objfile->original_name);
}

/* See objfiles.h.  */

const char *
objfile_flavour_name (struct objfile *objfile)
{
  if (objfile->obfd != NULL)
    return bfd_flavour_name (bfd_get_flavour (objfile->obfd));
  return NULL;
}

/* Provide a prototype to silence -Wmissing-prototypes.  */
extern initialize_file_ftype _initialize_objfiles;

void
_initialize_objfiles (void)
{
  objfiles_pspace_data
    = register_program_space_data_with_cleanup (NULL,
						objfiles_pspace_data_cleanup);

  objfiles_bfd_data = register_bfd_data_with_cleanup (NULL,
						      objfile_bfd_data_free);
}
