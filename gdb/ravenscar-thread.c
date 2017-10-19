/* Ada Ravenscar thread support.

   Copyright (C) 2004-2017 Free Software Foundation, Inc.

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
#include "gdbcore.h"
#include "gdbthread.h"
#include "ada-lang.h"
#include "target.h"
#include "inferior.h"
#include "command.h"
#include "ravenscar-thread.h"
#include "observer.h"
#include "gdbcmd.h"
#include "top.h"
#include "regcache.h"
#include "objfiles.h"

/* If non-null, ravenscar task support is enabled.  */
static int ravenscar_task_support = 1;

/* Some base target uses a special value for the null PID (exempli gratia
   remote).  */
static ptid_t base_magic_null_ptid;

/* Ptid of the inferior as seen by the process stratum.  */
static ptid_t base_ptid;

static const char running_thread_name[] = "__gnat_running_thread_table";

static const char known_tasks_name[] = "system__tasking__debug__known_tasks";
static const char first_task_name[] = "system__tasking__debug__first_task";

static const char ravenscar_runtime_initializer[] =
  "system__bb__threads__initialize";

struct ravenscar_thread_target : public target_ops
{
  ravenscar_thread_target ()
  { to_stratum = thread_stratum; }

  const char *shortname () override
  { return "ravenscar"; }

  const char *longname () override
  { return _("Ravenscar tasks."); }

  const char *doc () override
  { return _("Ravenscar tasks support."); }

  ptid_t wait (ptid_t, struct target_waitstatus *, int) override;
  void resume (ptid_t, int, enum gdb_signal) override;

  void fetch_registers (struct regcache *, int) override;
  void store_registers (struct regcache *, int) override;

  void prepare_to_store (struct regcache *) override;

  int thread_alive (ptid_t ptid) override;

  void update_thread_list () override;

  char *extra_thread_info (struct thread_info *) override;

  char *pid_to_str (ptid_t) override;

  ptid_t get_ada_task_ptid (long lwp, long thread) override;

  void mourn_inferior () override;

  int has_all_memory ()  override { return default_child_has_all_memory (); }
  int has_memory ()  override { return default_child_has_memory (); }
  int has_stack ()  override { return default_child_has_stack (); }
  int has_registers ()  override { return default_child_has_registers (); }
  int has_execution (ptid_t ptid)  override{ return default_child_has_execution (ptid); }
};

/* This module's target-specific operations.  */
static ravenscar_thread_target ravenscar_ops;

static ptid_t ravenscar_running_thread (void);
static void ravenscar_update_inferior_ptid (void);
static int has_ravenscar_runtime (void);
static int ravenscar_runtime_initialized (void);
static void ravenscar_inferior_created (struct target_ops *target,
					int from_tty);

/* Fetch the ravenscar running thread from target memory and
   update inferior_ptid accordingly.  */

static void
ravenscar_update_inferior_ptid (void)
{
  base_ptid = inferior_ptid;

  /* If the runtime has not been initialized yet, the inferior_ptid is
     the only ptid that there is.  */
  if (!ravenscar_runtime_initialized ())
    return;

  /* Make sure we set base_ptid before calling ravenscar_running_thread
     as the latter relies on it.  */
  inferior_ptid = ravenscar_running_thread ();
  gdb_assert (!ptid_equal (inferior_ptid, null_ptid));

  /* The running thread may not have been added to
     system.tasking.debug's list yet; so ravenscar_update_thread_list
     may not always add it to the thread list.  Add it here.  */
  if (!find_thread_ptid (inferior_ptid))
    add_thread (inferior_ptid);
}

/* The Ravenscar Runtime exports a symbol which contains the ID of
   the thread that is currently running.  Try to locate that symbol
   and return its associated minimal symbol.
   Return NULL if not found.  */

static struct bound_minimal_symbol
get_running_thread_msymbol (void)
{
  struct bound_minimal_symbol msym;

  msym = lookup_minimal_symbol (running_thread_name, NULL, NULL);
  if (!msym.minsym)
    /* Older versions of the GNAT runtime were using a different
       (less ideal) name for the symbol where the active thread ID
       is stored.  If we couldn't find the symbol using the latest
       name, then try the old one.  */
    msym = lookup_minimal_symbol ("running_thread", NULL, NULL);

  return msym;
}

/* Return True if the Ada Ravenscar run-time can be found in the
   application.  */

static int
has_ravenscar_runtime (void)
{
  struct bound_minimal_symbol msym_ravenscar_runtime_initializer =
    lookup_minimal_symbol (ravenscar_runtime_initializer, NULL, NULL);
  struct bound_minimal_symbol msym_known_tasks =
    lookup_minimal_symbol (known_tasks_name, NULL, NULL);
  struct bound_minimal_symbol msym_first_task =
    lookup_minimal_symbol (first_task_name, NULL, NULL);
  struct bound_minimal_symbol msym_running_thread
    = get_running_thread_msymbol ();

  return (msym_ravenscar_runtime_initializer.minsym
	  && (msym_known_tasks.minsym || msym_first_task.minsym)
	  && msym_running_thread.minsym);
}

/* Return True if the Ada Ravenscar run-time can be found in the
   application, and if it has been initialized on target.  */

static int
ravenscar_runtime_initialized (void)
{
  return (!(ptid_equal (ravenscar_running_thread (), null_ptid)));
}

/* Return the ID of the thread that is currently running.
   Return 0 if the ID could not be determined.  */

static CORE_ADDR
get_running_thread_id (void)
{
  struct bound_minimal_symbol object_msym = get_running_thread_msymbol ();
  int object_size;
  int buf_size;
  gdb_byte *buf;
  CORE_ADDR object_addr;
  struct type *builtin_type_void_data_ptr =
    builtin_type (target_gdbarch ())->builtin_data_ptr;

  if (!object_msym.minsym)
    return 0;

  object_addr = BMSYMBOL_VALUE_ADDRESS (object_msym);
  object_size = TYPE_LENGTH (builtin_type_void_data_ptr);
  buf_size = object_size;
  buf = (gdb_byte *) alloca (buf_size);
  read_memory (object_addr, buf, buf_size);
  return extract_typed_address (buf, builtin_type_void_data_ptr);
}

void
ravenscar_thread_target::resume (ptid_t ptid, int step, enum gdb_signal siggnal)
{
  struct target_ops *beneath = find_target_beneath (this);

  inferior_ptid = base_ptid;
  beneath->resume (base_ptid, step, siggnal);
}

ptid_t
ravenscar_thread_target::wait (ptid_t ptid,
			       struct target_waitstatus *status,
			       int options)
{
  struct target_ops *beneath = find_target_beneath (this);

  inferior_ptid = base_ptid;
  beneath->wait (base_ptid, status, 0);
  /* Find any new threads that might have been created, and update
     inferior_ptid to the active thread.

     Only do it if the program is still alive, though.  Otherwise,
     this causes problems when debugging through the remote protocol,
     because we might try switching threads (and thus sending packets)
     after the remote has disconnected.  */
  if (status->kind != TARGET_WAITKIND_EXITED
      && status->kind != TARGET_WAITKIND_SIGNALLED)
    {
      this->update_thread_list ();
      ravenscar_update_inferior_ptid ();
    }
  return inferior_ptid;
}

/* Add the thread associated to the given TASK to the thread list
   (if the thread has already been added, this is a no-op).  */

static void
ravenscar_add_thread (struct ada_task_info *task)
{
  if (find_thread_ptid (task->ptid) == NULL)
    add_thread (task->ptid);
}

void
ravenscar_thread_target::update_thread_list ()
{
  ada_build_task_list ();

  /* Do not clear the thread list before adding the Ada task, to keep
     the thread that the process stratum has included into it
     (base_ptid) and the running thread, that may not have been included
     to system.tasking.debug's list yet.  */

  iterate_over_live_ada_tasks (ravenscar_add_thread);
}

static ptid_t
ravenscar_running_thread (void)
{
  CORE_ADDR tid = get_running_thread_id ();

  if (tid == 0)
    return null_ptid;
  else
    return ptid_build (ptid_get_pid (base_ptid), 0, tid);
}

const char *
ravenscar_thread_target::extra_thread_info (thread_info *tp)
{
  return "Ravenscar task";
}

int
ravenscar_thread_target::thread_alive (ptid_t ptid)
{
  /* Ravenscar tasks are non-terminating.  */
  return 1;
}

const char *
ravenscar_thread_target::pid_to_str (ptid_t ptid)
{
  static char buf[30];

  snprintf (buf, sizeof (buf), "Thread %#x", (int) ptid_get_tid (ptid));
  return buf;
}

void
ravenscar_thread_target::fetch_registers (struct regcache *regcache, int regnum)
{
  struct target_ops *beneath = find_target_beneath (this);
  ptid_t ptid = regcache_get_ptid (regcache);

  if (!ravenscar_runtime_initialized ()
      || ptid_equal (ptid, base_magic_null_ptid)
      || ptid_equal (ptid, ravenscar_running_thread ()))
    beneath->fetch_registers (regcache, regnum);
  else
    {
      struct gdbarch *gdbarch = get_regcache_arch (regcache);
      struct ravenscar_arch_ops *arch_ops
	= gdbarch_ravenscar_ops (gdbarch);

      arch_ops->to_fetch_registers (regcache, regnum);
    }
}

void
ravenscar_thread_target::store_registers (struct regcache *regcache,
					  int regnum)
{
  target_ops *beneath = find_target_beneath (this);
  ptid_t ptid = regcache_get_ptid (regcache);

  if (!ravenscar_runtime_initialized ()
      || ptid_equal (ptid, base_magic_null_ptid)
      || ptid_equal (ptid, ravenscar_running_thread ()))
    beneath->store_registers (regcache, regnum);
  else
    {
      struct gdbarch *gdbarch = get_regcache_arch (regcache);
      struct ravenscar_arch_ops *arch_ops
	= gdbarch_ravenscar_ops (gdbarch);

      arch_ops->to_store_registers (regcache, regnum);
    }
}

void
ravenscar_thread_target::prepare_to_store (struct regcache *regcache)
{
  target_ops *beneath = find_target_beneath (this);
  ptid_t ptid = regcache_get_ptid (regcache);

  if (!ravenscar_runtime_initialized ()
      || ptid_equal (ptid, base_magic_null_ptid)
      || ptid_equal (ptid, ravenscar_running_thread ()))
    beneath->prepare_to_store (regcache);
  else
    {
      struct gdbarch *gdbarch = get_regcache_arch (regcache);
      struct ravenscar_arch_ops *arch_ops
	= gdbarch_ravenscar_ops (gdbarch);

      arch_ops->to_prepare_to_store (regcache);
    }
}

void
ravenscar_thread_target::mourn_inferior ()
{
  struct target_ops *beneath = find_target_beneath (this);

  base_ptid = null_ptid;
  beneath->mourn_inferior ();
  unpush_target (&ravenscar_ops);
}

/* Observer on inferior_created: push ravenscar thread stratum if needed.  */

static void
ravenscar_inferior_created (struct target_ops *target, int from_tty)
{

  if (!ravenscar_task_support
      || gdbarch_ravenscar_ops (target_gdbarch ()) == NULL
      || !has_ravenscar_runtime ())
    return;

  base_magic_null_ptid = inferior_ptid;
  ravenscar_update_inferior_ptid ();
  push_target (&ravenscar_ops);
}

ptid_t
ravenscar_thread_target::get_ada_task_ptid (long lwp, long thread)
{
  return ptid_build (ptid_get_pid (base_ptid), 0, thread);
}

/* Command-list for the "set/show ravenscar" prefix command.  */
static struct cmd_list_element *set_ravenscar_list;
static struct cmd_list_element *show_ravenscar_list;

/* Implement the "set ravenscar" prefix command.  */

static void
set_ravenscar_command (const char *arg, int from_tty)
{
  printf_unfiltered (_(\
"\"set ravenscar\" must be followed by the name of a setting.\n"));
  help_list (set_ravenscar_list, "set ravenscar ", all_commands, gdb_stdout);
}

/* Implement the "show ravenscar" prefix command.  */

static void
show_ravenscar_command (const char *args, int from_tty)
{
  cmd_show_list (show_ravenscar_list, from_tty, "");
}

/* Implement the "show ravenscar task-switching" command.  */

static void
show_ravenscar_task_switching_command (struct ui_file *file, int from_tty,
				       struct cmd_list_element *c,
				       const char *value)
{
  if (ravenscar_task_support)
    fprintf_filtered (file, _("\
Support for Ravenscar task/thread switching is enabled\n"));
  else
    fprintf_filtered (file, _("\
Support for Ravenscar task/thread switching is disabled\n"));
}

/* Module startup initialization function, automagically called by
   init.c.  */

void
_initialize_ravenscar (void)
{
  base_ptid = null_ptid;

  /* Notice when the inferior is created in order to push the
     ravenscar ops if needed.  */
  observer_attach_inferior_created (ravenscar_inferior_created);

  add_prefix_cmd ("ravenscar", no_class, set_ravenscar_command,
                  _("Prefix command for changing Ravenscar-specific settings"),
                  &set_ravenscar_list, "set ravenscar ", 0, &setlist);

  add_prefix_cmd ("ravenscar", no_class, show_ravenscar_command,
                  _("Prefix command for showing Ravenscar-specific settings"),
                  &show_ravenscar_list, "show ravenscar ", 0, &showlist);

  add_setshow_boolean_cmd ("task-switching", class_obscure,
                           &ravenscar_task_support, _("\
Enable or disable support for GNAT Ravenscar tasks"), _("\
Show whether support for GNAT Ravenscar tasks is enabled"),
                           _("\
Enable or disable support for task/thread switching with the GNAT\n\
Ravenscar run-time library for bareboard configuration."),
			   NULL, show_ravenscar_task_switching_command,
			   &set_ravenscar_list, &show_ravenscar_list);
}
