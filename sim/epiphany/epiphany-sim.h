/* EPIPHANY simulator support code
   Copyright (C) 2011 Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva, Inc.

This file is part of the GNU simulators.

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

#ifndef EPIPHANY_SIM_H
#define EPIPHANY_SIM_H

#include "cgen-atomic.h"

/* GDB register numbers.  */
/* TBS */

extern int epiphany_decode_gdb_ctrl_regnum (int);

/* Cover macros for hardware accesses.
   FIXME: Eventually move to cgen.  */
#define GET_H_SM() ((CPU (h_psw) & 0x80) != 0)

#ifndef GET_H_CR
extern USI  epiphanybf_h_cr_get_handler (SIM_CPU *, UINT);
extern void epiphanybf_h_cr_set_handler (SIM_CPU *, UINT, USI);

#define GET_H_CR(regno) \
  XCONCAT2 (WANT_CPU,_h_cr_get_handler) (current_cpu, (regno))
#define SET_H_CR(regno, val) \
  XCONCAT2 (WANT_CPU,_h_cr_set_handler) (current_cpu, (regno), (val))
#endif

#ifndef  GET_H_PSW
extern UQI  epiphanybf_h_psw_get_handler (SIM_CPU *);
extern void epiphanybf_h_psw_set_handler (SIM_CPU *, UQI);

#define GET_H_PSW() \
  XCONCAT2 (WANT_CPU,_h_psw_get_handler) (current_cpu)
#define SET_H_PSW(val) \
  XCONCAT2 (WANT_CPU,_h_psw_set_handler) (current_cpu, (val))
#endif

#ifndef  GET_H_ACCUM
extern DI   epiphanybf_h_accum_get_handler (SIM_CPU *);
extern void epiphanybf_h_accum_set_handler (SIM_CPU *, DI);

#define GET_H_ACCUM() \
  XCONCAT2 (WANT_CPU,_h_accum_get_handler) (current_cpu)
#define SET_H_ACCUM(val) \
  XCONCAT2 (WANT_CPU,_h_accum_set_handler) (current_cpu, (val))
#endif

/* Custom reg getters/setters */
void epiphanybf_set_config(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_status(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_ilatst(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_ilatcl(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_debugcmd(SIM_CPU *current_cpu, USI val);
void epiphanybf_set_resetcore(SIM_CPU *current_cpu, USI val);

/* Misc. profile data.  */

typedef struct 
{
  /* nop insn slot filler count.  */
  unsigned int fillnop_count;
  /* Number of parallel insns.  */
  unsigned int parallel_count;

  /* FIXME: generalize this to handle all insn lengths, move to common.  */
  /* Number of short insns, not including parallel ones.  */
  unsigned int short_count;
  /* Number of long insns.  */
  unsigned int long_count;

  /* Working area for computing cycle counts.  */
  unsigned long insn_cycles; /* FIXME: delete */
  unsigned long cti_stall;
  unsigned long load_stall;
  unsigned long biggest_cycles;

  /* Bitmask of registers loaded by previous insn.  */
  unsigned int load_regs;
  /* Bitmask of registers loaded by current insn.  */
  unsigned int load_regs_pending;
} EPIPHANY_MISC_PROFILE;

/* Initialize the working area.  */
extern void epiphany_init_insn_cycles (SIM_CPU *, int);
/* Update the totals for the insn.  */
extern void epiphany_record_insn_cycles (SIM_CPU *, int);

/* This is invoked by the nop pattern in the .cpu file.  */
#define PROFILE_COUNT_FILLNOPS(cpu, addr) \
do { \
  if (PROFILE_INSN_P (cpu) \
      && (addr & 3) != 0) \
    ++ CPU_EPIPHANY_MISC_PROFILE (cpu)->fillnop_count; \
} while (0)

/* This is invoked by the execute section of mloop{,x}.in.  */

/* This is invoked by the execute section of mloop{,x}.in.  */
#define PROFILE_COUNT_SHORTINSNS(cpu) \
do { \
  if (PROFILE_INSN_P (cpu)) \
    ++ CPU_EPIPHANY_MISC_PROFILE (cpu)->short_count; \
} while (0)

/* This is invoked by the execute section of mloop{,x}.in.  */
#define PROFILE_COUNT_LONGINSNS(cpu) \
do { \
  if (PROFILE_INSN_P (cpu)) \
    ++ CPU_EPIPHANY_MISC_PROFILE (cpu)->long_count; \
} while (0)

#define GETTWI GETTSI
#define SETTWI SETTSI

/* Additional execution support.  */


/* Hardware/device support.
   ??? Will eventually want to move device stuff to config files.  */

/* Exception, Interrupt, and Trap addresses.  */
#define EIT_RESET_ADDR		0x40
#define EIT_SW_EXCEPTION_ADDR	0x44
#define EIT_INTERRUPT_HIGH_ADDR	0x48
#define EIT_INTERRUPT_LOW_ADDR	0x4C


/* Special purpose traps.  */
#define TRAP_SYSCALL	0
#define TRAP_BREAKPOINT	1

#define EPIPHANY_DEVICE_ADDR  0x0
#define EPIPHANY_DEVICE_LEN   0x2040

/* Handle the trap insn.  */
extern USI epiphany_trap (SIM_CPU *, PCADDR, int);

/* Handle the bkpt insn.  */
extern void epiphany_break( SIM_CPU *,PCADDR );

/* Handle a fp error.  */
extern void epiphany_fpu_error (CGEN_FPU *, int);

/* Handle ipend on rti call.  */
extern USI epiphany_rti (SIM_CPU *);

/* Handle the gie insn.  */
extern void epiphany_gie( SIM_CPU * );

/* Call back after every instruction.  */
extern USI epiphany_post_isn_callback (SIM_CPU *cpu , USI pc) ;

/* Check if core is active */
extern int epiphany_cpu_is_active(SIM_CPU *current_cpu);

#if WITH_SCACHE
extern void epiphanybf_scache_invalidate(SIM_CPU *current_cpu, PCADDR vpc);
#endif

void
epiphanybf_h_all_registers_set_raw (SIM_CPU *current_cpu, UINT regno,
				    SI newval);

SI epiphany_testset(SIM_CPU *, USI, SI, int);
SI epiphany_testset_SI(SIM_CPU *, USI, SI);
SI epiphany_testset_HI(SIM_CPU *, USI, HI);
SI epiphany_testset_QI(SIM_CPU *, USI, QI);


#endif /* EPIPHANY_SIM_H */
