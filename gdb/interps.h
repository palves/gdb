/* Manages interpreters for GDB, the GNU debugger.

   Copyright (C) 2000-2015 Free Software Foundation, Inc.

   Written by Jim Ingham <jingham@apple.com> of Apple Computer, Inc.

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

#ifndef INTERPS_H
#define INTERPS_H

struct interp;
struct ui_out;
struct thread_info;
struct inferior;
struct trace_state_variable;
struct bpstats;
struct breakpoint;
struct so_list;
struct terminal;

typedef struct interp *(*interp_factory_func) (const char *interp,
					       struct terminal *terminal);

extern void interp_factory_register (const char *name,
				     interp_factory_func func);
extern struct interp *interp_create (const char *name,
				     struct terminal *terminal);

extern int interp_resume (struct interp *interp);
extern int interp_suspend (struct interp *interp);
extern struct gdb_exception interp_exec (struct interp *interp,
					 const char *command);
extern int interp_quiet_p (struct interp *interp);

typedef void *(interp_init_ftype) (struct interp *self, int top_level);
typedef int (interp_resume_ftype) (struct interp *self);
typedef int (interp_suspend_ftype) (struct interp *self);
typedef struct gdb_exception (interp_exec_ftype) (struct interp *self,
						  const char *command);
typedef void (interp_command_loop_ftype) (struct interp *self);
typedef struct ui_out *(interp_ui_out_ftype) (struct interp *self);

typedef int (interp_set_logging_ftype) (struct interp *self, int start_log,
					struct ui_file *out,
					struct ui_file *logfile);

typedef void (interp_on_normal_stop_ftype) (struct bpstats *bs, int print_frame);
typedef void (interp_on_signal_received_ftype) (enum gdb_signal siggnal);
typedef void (interp_on_end_stepping_range_ftype) (void);
typedef void (interp_on_signal_exited_ftype) (enum gdb_signal siggnal);
typedef void (interp_on_exited_ftype) (int exitstatus);
typedef void (interp_on_no_history_ftype) (void);
typedef void (interp_on_sync_execution_done_ftype) (void);
typedef void (interp_on_new_thread_ftype) (struct thread_info *t);
typedef void (interp_on_thread_exit_ftype) (struct thread_info *t, int silent);
typedef void (interp_on_target_resumed_ftype) (ptid_t ptid);
typedef void (interp_on_about_to_proceed_ftype) (void);
typedef void (interp_on_breakpoint_created_ftype) (struct breakpoint *b);
typedef void (interp_on_breakpoint_deleted_ftype) (struct breakpoint *b);
typedef void (interp_on_breakpoint_modified_ftype) (struct breakpoint *b);
typedef void (interp_on_inferior_added_ftype) (struct inferior *inf);
typedef void (interp_on_inferior_appeared_ftype) (struct inferior *inf);
typedef void (interp_on_inferior_exit_ftype) (struct inferior *inf);
typedef void (interp_on_inferior_removed_ftype) (struct inferior *inf);
typedef void (interp_on_tsv_created_ftype) (const struct trace_state_variable *tsv);
typedef void (interp_on_tsv_deleted_ftype) (const struct trace_state_variable *tsv);
typedef void (interp_on_tsv_modified_ftype) (const struct trace_state_variable *tsv);
typedef void (interp_on_record_changed_ftype) (struct inferior *inferior, int started);
typedef void (interp_on_solib_loaded_ftype) (struct so_list *solib);
typedef void (interp_on_solib_unloaded_ftype) (struct so_list *solib);
typedef void (interp_on_traceframe_changed_ftype) (int tfnum, int tpnum);
typedef void (interp_on_command_param_changed_ftype) (const char *param, const char *value);
typedef void (interp_on_command_error_ftype) (void);
typedef void (interp_on_memory_changed_ftype) (struct inferior *inferior,
					       CORE_ADDR addr, ssize_t len,
					       const bfd_byte *data);

struct interp_procs
{
  interp_init_ftype *init_proc;
  interp_resume_ftype *resume_proc;
  interp_suspend_ftype *suspend_proc;
  interp_exec_ftype *exec_proc;

  /* Returns the ui_out currently used to collect results for this
     interpreter.  It can be a formatter for stdout, as is the case
     for the console & mi outputs, or it might be a result
     formatter.  */
  interp_ui_out_ftype *ui_out_proc;

  /* Provides a hook for interpreters to do any additional
     setup/cleanup that they might need when logging is enabled or
     disabled.  */
  interp_set_logging_ftype *set_logging_proc;

  interp_command_loop_ftype *command_loop_proc;

  interp_on_normal_stop_ftype *on_normal_stop;
  interp_on_signal_received_ftype *on_signal_received;
  interp_on_end_stepping_range_ftype *on_end_stepping_range;
  interp_on_signal_exited_ftype *on_signal_exited;
  interp_on_exited_ftype *on_exited;
  interp_on_no_history_ftype *on_no_history;
  interp_on_sync_execution_done_ftype *on_sync_execution_done;
  interp_on_new_thread_ftype *on_new_thread;
  interp_on_thread_exit_ftype *on_thread_exit;
  interp_on_target_resumed_ftype *on_target_resumed;
  interp_on_about_to_proceed_ftype *on_about_to_proceed;
  interp_on_breakpoint_created_ftype *on_breakpoint_created;
  interp_on_breakpoint_deleted_ftype *on_breakpoint_deleted;
  interp_on_breakpoint_modified_ftype *on_breakpoint_modified;
  interp_on_inferior_added_ftype *on_inferior_added;
  interp_on_inferior_appeared_ftype *on_inferior_appeared;
  interp_on_inferior_exit_ftype *on_inferior_exit;
  interp_on_inferior_removed_ftype *on_inferior_removed;
  interp_on_tsv_created_ftype *on_tsv_created;
  interp_on_tsv_deleted_ftype *on_tsv_deleted;
  interp_on_tsv_modified_ftype *on_tsv_modified;
  interp_on_record_changed_ftype *on_record_changed;
  interp_on_solib_loaded_ftype *on_solib_loaded;
  interp_on_solib_unloaded_ftype *on_solib_unloaded;
  interp_on_traceframe_changed_ftype *on_traceframe_changed;
  interp_on_command_param_changed_ftype *on_command_param_changed;
  interp_on_command_error_ftype *on_command_error;
  interp_on_memory_changed_ftype *on_memory_changed;
};

struct interp
{
  /* This is the name in "-i=" and set interpreter.  */
  const char *name;

  /* Interpreters are stored in a linked list, this is the next
     one...  */
  struct interp *next;

  /* This is a cookie that an instance of the interpreter can use.
     This is a bit confused right now as the exact initialization
     sequence for it, and how it relates to the interpreter's uiout
     object is a bit confused.  */
  void *data;

  /* Has the init_proc been run?  */
  int inited;

  const struct interp_procs *procs;
  int quiet_p;

  /* The terminal this interpreter is attached to.  */
  struct terminal *terminal;
};

extern struct interp *interp_new (const char *name,
				  const struct interp_procs *procs,
				  struct terminal *terminal);
extern void interp_ctor (struct interp *self, const char *name,
			 const struct interp_procs *procs,
			 struct terminal *terminal);
extern int interp_set (struct interp *interp, int top_level);
extern struct ui_out *interp_ui_out (struct interp *interp);
extern void *interp_data (struct interp *interp);
extern const char *interp_name (struct interp *interp);

extern int current_interp_named_p (const char *name);

extern void current_interp_command_loop (void);

/* Call this function to give the current interpreter an opportunity
   to do any special handling of streams when logging is enabled or
   disabled.  START_LOG is 1 when logging is starting, 0 when it ends,
   and OUT is the stream for the log file; it will be NULL when
   logging is ending.  LOGFILE is non-NULL if the output streams
   are to be tees, with the log file as one of the outputs.  */

extern int current_interp_set_logging (int start_log, struct ui_file *out,
				       struct ui_file *logfile);

/* Returns opaque data associated with the top-level interpreter.  */
extern void *top_level_interpreter_data (void);
extern struct interp *top_level_interpreter (void);

extern struct interp *command_interp (void);

extern struct interp *current_interpreter;
extern struct interp *interp_list;
extern struct interp *top_level_interpreter_ptr;

#define ALL_INTERPS(INTERP)				\
  for (INTERP = interp_list; INTERP; INTERP = INTERP->next)

/* True if the current interpreter is in async mode, false if in sync
   mode.  If in sync mode, running a synchronous execution command
   (with execute_command, e.g, "next") will not return until the
   command is finished.  If in async mode, then running a synchronous
   command returns right after resuming the target.  Waiting for the
   command's completion is later done on the top event loop (using
   continuations).  */
extern int interpreter_async;

extern void clear_interpreter_hooks (void);

/* well-known interpreters */
#define INTERP_CONSOLE		"console"
#define INTERP_MI1             "mi1"
#define INTERP_MI2             "mi2"
#define INTERP_MI3             "mi3"
#define INTERP_MI		"mi"
#define INTERP_TUI		"tui"
#define INTERP_INSIGHT		"insight"

#endif
