/* Simulator instruction semantics for epiphanybf.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright 1996-2010 Free Software Foundation, Inc.

This file is part of the GNU simulators.

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.

*/

#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "cgen-mem.h"
#include "cgen-ops.h"

#undef GET_ATTR
#define GET_ATTR(cpu, num, attr) CGEN_ATTR_VALUE (NULL, abuf->idesc->attrs, CGEN_INSN_##attr)

/* This is used so that we can compile two copies of the semantic code,
   one with full feature support and one without that runs fast(er).
   FAST_P, when desired, is defined on the command line, -DFAST_P=1.  */
#if FAST_P
#define SEM_FN_NAME(cpu,fn) XCONCAT3 (cpu,_semf_,fn)
#undef CGEN_TRACE_RESULT
#define CGEN_TRACE_RESULT(cpu, abuf, name, type, val)
#else
#define SEM_FN_NAME(cpu,fn) XCONCAT3 (cpu,_sem_,fn)
#endif

/* x-invalid: --invalid-- */

static SEM_PC
SEM_FN_NAME (epiphanybf,x_invalid) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
    /* Update the recorded pc in the cpu state struct.
       Only necessary for WITH_SCACHE case, but to avoid the
       conditional compilation ....  */
    SET_H_PC (pc);
    /* Virtual insns have zero size.  Overwrite vpc with address of next insn
       using the default-insn-bitsize spec.  When executing insns in parallel
       we may want to queue the fault and continue execution.  */
    vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
    vpc = sim_engine_invalid_insn (current_cpu, pc, vpc);
  }

  return vpc;
#undef FLD
}

/* x-after: --after-- */

static SEM_PC
SEM_FN_NAME (epiphanybf,x_after) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
    epiphanybf_pbb_after (current_cpu, sem_arg);
#endif
  }

  return vpc;
#undef FLD
}

/* x-before: --before-- */

static SEM_PC
SEM_FN_NAME (epiphanybf,x_before) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
    epiphanybf_pbb_before (current_cpu, sem_arg);
#endif
  }

  return vpc;
#undef FLD
}

/* x-cti-chain: --cti-chain-- */

static SEM_PC
SEM_FN_NAME (epiphanybf,x_cti_chain) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
#ifdef DEFINE_SWITCH
    vpc = epiphanybf_pbb_cti_chain (current_cpu, sem_arg,
			       pbb_br_type, pbb_br_npc);
    BREAK (sem);
#else
    /* FIXME: Allow provision of explicit ifmt spec in insn spec.  */
    vpc = epiphanybf_pbb_cti_chain (current_cpu, sem_arg,
			       CPU_PBB_BR_TYPE (current_cpu),
			       CPU_PBB_BR_NPC (current_cpu));
#endif
#endif
  }

  return vpc;
#undef FLD
}

/* x-chain: --chain-- */

static SEM_PC
SEM_FN_NAME (epiphanybf,x_chain) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
    vpc = epiphanybf_pbb_chain (current_cpu, sem_arg);
#ifdef DEFINE_SWITCH
    BREAK (sem);
#endif
#endif
  }

  return vpc;
#undef FLD
}

/* x-begin: --begin-- */

static SEM_PC
SEM_FN_NAME (epiphanybf,x_begin) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);

  {
#if WITH_SCACHE_PBB_EPIPHANYBF
#if defined DEFINE_SWITCH || defined FAST_P
    /* In the switch case FAST_P is a constant, allowing several optimizations
       in any called inline functions.  */
    vpc = epiphanybf_pbb_begin (current_cpu, FAST_P);
#else
#if 0 /* cgen engine can't handle dynamic fast/full switching yet.  */
    vpc = epiphanybf_pbb_begin (current_cpu, STATE_RUN_FAST_P (CPU_STATE (current_cpu)));
#else
    vpc = epiphanybf_pbb_begin (current_cpu, 0);
#endif
#endif
#endif
  }

  return vpc;
#undef FLD
}

/* beq16: beq.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,beq16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_ZBIT (), 1)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* beq: beq.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,beq) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_ZBIT (), 1)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bne16: bne.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bne16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_ZBIT (), 0)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bne: bne.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bne) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_ZBIT (), 0)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgtu16: bgtu.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgtu16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgtu: bgtu.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgtu) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgteu16: bgteu.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgteu16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_CBIT (), 1)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgteu: bgteu.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgteu) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_CBIT (), 1)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* blteu16: blteu.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,blteu16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* blteu: blteu.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,blteu) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bltu16: bltu.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bltu16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_CBIT (), 0)) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bltu: bltu.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bltu) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_CBIT (), 0)) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgt16: bgt.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgt16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgt: bgt.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgt) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgte16: bgte.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgte16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bgte: bgte.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bgte) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* blt16: blt.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,blt16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* blt: blt.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,blt) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* blte16: blte.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,blte16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* blte: blte.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,blte) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bbeq16: bbeq.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bbeq16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bbeq: bbeq.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bbeq) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bbne16: bbne.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bbne16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (NOTBI (GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bbne: bbne.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bbne) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (NOTBI (GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 2);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bblt16: bblt.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bblt16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bblt: bblt.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bblt) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bblte16: bblte.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bblte16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bblte: bblte.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bblte) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 3);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* b16: b.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,b16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* b: b.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,b) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bl16: bl.s $simm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bl16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    SI opval = ADDSI (pc, 2);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = FLD (i_simm8);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bl: bl.l $simm24 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bl) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = ADDSI (pc, 4);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = FLD (i_simm24);
    SEM_BRANCH_VIA_CACHE (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* jr16: jr $rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,jr16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* jr: jr $rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,jr) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* jalr16: jalr $rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,jalr16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    SI opval = ADDSI (pc, 2);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* jalr: jalr $rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,jalr) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = ADDSI (pc, 4);
    SET_H_REGISTERS (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    USI opval = GET_H_REGISTERS (FLD (f_rn6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrbx16.s: ldrb $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrbx16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrbp16.s: ldrb $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrbp16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrbx.l: ldrb $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrbx_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrbp.l: ldrb $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrbp_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrbd16.s: ldrb $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrbd16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, tmp_effa));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrbd.l: ldrb $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrbd_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, tmp_effa));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrbdpm.l: ldrb $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrbdpm_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTQISI (GETMEMQI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrhx16.s: ldrh $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrhx16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrhp16.s: ldrh $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrhp16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrhx.l: ldrh $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrhx_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrhp.l: ldrh $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrhp_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrhd16.s: ldrh $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrhd16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, tmp_effa));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrhd.l: ldrh $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrhd_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, tmp_effa));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrhdpm.l: ldrh $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrhdpm_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTHISI (GETMEMHI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrx16.s: ldr $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrx16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrp16.s: ldr $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrp16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn))));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrx.l: ldr $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrx_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrp.l: ldr $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrp_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm6));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrd16.s: ldr $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrd16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, tmp_effa));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrd.l: ldr $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrd_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, tmp_effa));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrdpm.l: ldr $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrdpm_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = ZEXTSISI (GETMEMSI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6))));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrdx16.s: ldrd $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrdx16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd), 1), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrdp16.s: ldrd $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrdp16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm));
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = GET_H_REGISTERS (FLD (f_rn));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd), 1), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrdx.l: ldrd $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrdx_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd6), 1), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
} else {
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd6), 1), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrdp.l: ldrd $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrdp_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_tmprm;
  tmp_tmprm = GET_H_REGISTERS (FLD (f_rm6));
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = GET_H_REGISTERS (FLD (f_rn6));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd6), 1), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), tmp_tmprm);
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrdd16.s: ldrd $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrdd16_s) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = tmp_effa;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd), 1), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrdd.l: ldrd $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrdd_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = tmp_effa;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd6), 1), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* ldrddpm.l: ldrd $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,ldrddpm_l) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
{
  SI tmp_loadaddr;
  BI tmp_isAlignmentAccess;
  tmp_loadaddr = GET_H_REGISTERS (FLD (f_rn6));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_loadaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_loadaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_loadaddr, 3), 0)) : (EQSI (ANDSI (tmp_loadaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  tmp_loadaddr = ADDSI (tmp_loadaddr, 4);
  {
    SI opval = tmp_loadaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GETMEMSI (current_cpu, pc, tmp_loadaddr);
    SET_H_REGISTERS (ADDSI (FLD (f_rd6), 1), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* testsetbt: testsetb $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,testsetbt) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_eff_addr;
  BI tmp_isAlignmentAccess;
if (FLD (f_addsubx)) {
  tmp_eff_addr = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
} else {
  tmp_eff_addr = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
}
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (tmp_eff_addr, 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (tmp_eff_addr, 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (tmp_eff_addr, 3), 0)) : (EQSI (ANDSI (tmp_eff_addr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
  {
    SI opval = epiphany_testset_QI (current_cpu, tmp_eff_addr, GET_H_REGISTERS (FLD (f_rd6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* testsetht: testseth $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,testsetht) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_eff_addr;
  BI tmp_isAlignmentAccess;
if (FLD (f_addsubx)) {
  tmp_eff_addr = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
} else {
  tmp_eff_addr = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
}
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (tmp_eff_addr, 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (tmp_eff_addr, 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (tmp_eff_addr, 3), 0)) : (EQSI (ANDSI (tmp_eff_addr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
  {
    SI opval = epiphany_testset_HI (current_cpu, tmp_eff_addr, GET_H_REGISTERS (FLD (f_rd6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* testsett: testset $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,testsett) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_eff_addr;
  BI tmp_isAlignmentAccess;
if (FLD (f_addsubx)) {
  tmp_eff_addr = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
} else {
  tmp_eff_addr = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
}
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (tmp_eff_addr, 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (tmp_eff_addr, 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (tmp_eff_addr, 3), 0)) : (EQSI (ANDSI (tmp_eff_addr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
  {
    SI opval = epiphany_testset_SI (current_cpu, tmp_eff_addr, GET_H_REGISTERS (FLD (f_rd6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strbx16: strb $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strbx16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMQI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strbx: strb $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strbx) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMQI (current_cpu, pc, SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMQI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strbp16: strb $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,strbp16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMQI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn)), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strbp: strb $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strbp) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMQI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6)), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strbd16: strb $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strbd16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMQI (current_cpu, pc, tmp_effa, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strbd: strb $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strbd) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMQI (current_cpu, pc, tmp_effa, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strbdpm: strb $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strbdpm) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_BYTE == OPW_BYTE) ? (0) : (OPW_BYTE == OPW_SHORT) ? (1) : (OPW_BYTE == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_BYTE == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_BYTE == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_BYTE == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    QI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMQI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6)), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strhx16: strh $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strhx16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMHI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strhx: strh $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strhx) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMHI (current_cpu, pc, SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMHI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strhp16: strh $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,strhp16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMHI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn)), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strhp: strh $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strhp) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMHI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6)), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strhd16: strh $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strhd16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMHI (current_cpu, pc, tmp_effa, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strhd: strh $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strhd) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMHI (current_cpu, pc, tmp_effa, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strhdpm: strh $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strhdpm) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_SHORT == OPW_BYTE) ? (0) : (OPW_SHORT == OPW_SHORT) ? (1) : (OPW_SHORT == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_SHORT == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_SHORT == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_SHORT == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    HI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMHI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6)), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strx16: str $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strx16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMSI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm))), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strx: str $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strx) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
} else {
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 3), 0)) : (EQSI (ANDSI (ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6))), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strp16: str $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,strp16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMSI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn)), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strp: str $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strp) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6)), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strd16: str $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strd16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMSI (current_cpu, pc, tmp_effa, opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strd: str $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strd) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (tmp_effa, 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (tmp_effa, 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (tmp_effa, 3), 0)) : (EQSI (ANDSI (tmp_effa, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_effa;
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, tmp_effa, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strdpm: str $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strdpm) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_WORD == OPW_BYTE) ? (0) : (OPW_WORD == OPW_SHORT) ? (1) : (OPW_WORD == OPW_WORD) ? (2) : (3);
{
  BI tmp_isAlignmentAccess;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_WORD == OPW_BYTE) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 0), 0)) : (OPW_WORD == OPW_SHORT) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 1), 0)) : (OPW_WORD == OPW_WORD) ? (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 3), 0)) : (EQSI (ANDSI (GET_H_REGISTERS (FLD (f_rn6)), 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    CPU (h_memaddr) = opval;
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, GET_H_REGISTERS (FLD (f_rn6)), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strdx16: strd $rd,[$rn,$rm] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strdx16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strdx: strd $rd6,[$rn6,$direction$rm6] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strdx) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (FLD (f_addsubx)) {
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
} else {
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strdp16: strd $rd,[$rn],$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,strdp16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = GET_H_REGISTERS (FLD (f_rn));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strdp: strd $rd6,[$rn6],$direction$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strdp) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = GET_H_REGISTERS (FLD (f_rn6));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_addsubx)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strdd16: strd $rd,[$rn,$disp3] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strdd16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn)), SLLSI (FLD (f_disp3), tmp_scale));
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = tmp_effa;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strdd: strd $rd6,[$rn6,$dpmi$disp11] */

static SEM_PC
SEM_FN_NAME (epiphanybf,strdd) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_effa;
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
if (FLD (f_subd)) {
  tmp_effa = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
} else {
  tmp_effa = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
}
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = tmp_effa;
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* strddpm: strd $rd6,[$rn6],$dpmi$disp11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,strddpm) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SI tmp_scale;
  tmp_scale = (OPW_DOUBLE == OPW_BYTE) ? (0) : (OPW_DOUBLE == OPW_SHORT) ? (1) : (OPW_DOUBLE == OPW_WORD) ? (2) : (3);
{
  SI tmp_storeaddr;
  BI tmp_isAlignmentAccess;
  tmp_storeaddr = GET_H_REGISTERS (FLD (f_rn6));
{
  BI tmp_scale;
  tmp_isAlignmentAccess = (OPW_DOUBLE == OPW_BYTE) ? (EQSI (ANDSI (tmp_storeaddr, 0), 0)) : (OPW_DOUBLE == OPW_SHORT) ? (EQSI (ANDSI (tmp_storeaddr, 1), 0)) : (OPW_DOUBLE == OPW_WORD) ? (EQSI (ANDSI (tmp_storeaddr, 3), 0)) : (EQSI (ANDSI (tmp_storeaddr, 7), 0));
if (NOTBI (tmp_isAlignmentAccess)) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_UNALIGNED;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
if (NOTBI (NOTBI (tmp_isAlignmentAccess))) {
{
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (FLD (f_rd6));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  tmp_storeaddr = ADDSI (tmp_storeaddr, 4);
  {
    SI opval = tmp_storeaddr;
    CPU (h_memaddr) = opval;
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memaddr", 'x', opval);
  }
  {
    SI opval = GET_H_REGISTERS (ADDSI (FLD (f_rd6), 1));
    SETMEMSI (current_cpu, pc, tmp_storeaddr, opval);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}
}
if (FLD (f_subd)) {
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
} else {
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), SLLSI (FLD (f_disp11), tmp_scale));
    SET_H_REGISTERS (FLD (f_rn6), opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16EQ: moveq $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16EQ) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (EQBI (GET_H_ZBIT (), 1)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovEQ: moveq $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovEQ) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (EQBI (GET_H_ZBIT (), 1)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16NE: movne $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16NE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (EQBI (GET_H_ZBIT (), 0)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovNE: movne $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovNE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (EQBI (GET_H_ZBIT (), 0)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16GTU: movgtu $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16GTU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovGTU: movgtu $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovGTU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (ANDBI (GET_H_CBIT (), NOTBI (GET_H_ZBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16GTEU: movgteu $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16GTEU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (EQBI (GET_H_CBIT (), 1)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovGTEU: movgteu $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovGTEU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (EQBI (GET_H_CBIT (), 1)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16LTEU: movlteu $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16LTEU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovLTEU: movlteu $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovLTEU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (ORBI (NOTBI (GET_H_CBIT ()), GET_H_ZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16LTU: movltu $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16LTU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (EQBI (GET_H_CBIT (), 0)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovLTU: movltu $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovLTU) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (EQBI (GET_H_CBIT (), 0)) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16GT: movgt $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16GT) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovGT: movgt $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovGT) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (ANDBI (NOTBI (GET_H_ZBIT ()), EQBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16GTE: movgte $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16GTE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovGTE: movgte $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovGTE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (EQBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16LT: movlt $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16LT) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovLT: movlt $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovLT) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (XORBI (GET_H_VBIT (), GET_H_NBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16LTE: movlte $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16LTE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovLTE: movlte $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovLTE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (ORBI (GET_H_ZBIT (), XORBI (GET_H_VBIT (), GET_H_NBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16B: mov $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16B) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovB: mov $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovB) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16BEQ: movbeq $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16BEQ) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovBEQ: movbeq $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovBEQ) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (ORBI (GET_H_BZBIT (), GET_H_BZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16BNE: movbne $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16BNE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (NOTBI (GET_H_BZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovBNE: movbne $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovBNE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (NOTBI (GET_H_BZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16BLT: movblt $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16BLT) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovBLT: movblt $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovBLT) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (ANDBI (GET_H_BNBIT (), NOTBI (GET_H_BZBIT ()))) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmov16BLTE: movblte $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmov16BLTE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* cmovBLTE: movblte $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,cmovBLTE) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
if (ORBI (GET_H_BNBIT (), GET_H_BZBIT ())) {
  {
    SI opval = GET_H_REGISTERS (FLD (f_rn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movts16: movts $sn,$rd */

static SEM_PC
SEM_FN_NAME (epiphanybf,movts16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    USI opval = GET_H_REGISTERS (FLD (f_rd));
    SET_H_CORE_REGISTERS (FLD (f_sn), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movts6: movts $sn6,$rd6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,movts6) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_CORE_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movtsdma: movts $sndma,$rd6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,movtsdma) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_COREDMA_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "coredma-registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movtsmem: movts $snmem,$rd6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,movtsmem) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_COREMEM_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "coremem-registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movtsmesh: movts $snmesh,$rd6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,movtsmesh) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    USI opval = GET_H_REGISTERS (FLD (f_rd6));
    SET_H_COREMESH_REGISTERS (FLD (f_sn6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "coremesh-registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movfs16: movfs $rd,$sn */

static SEM_PC
SEM_FN_NAME (epiphanybf,movfs16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    SI opval = GET_H_CORE_REGISTERS (FLD (f_sn));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movfs6: movfs $rd6,$sn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,movfs6) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = GET_H_CORE_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movfsdma: movfs $rd6,$sndma */

static SEM_PC
SEM_FN_NAME (epiphanybf,movfsdma) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = GET_H_COREDMA_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movfsmem: movfs $rd6,$snmem */

static SEM_PC
SEM_FN_NAME (epiphanybf,movfsmem) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = GET_H_COREMEM_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movfsmesh: movfs $rd6,$snmesh */

static SEM_PC
SEM_FN_NAME (epiphanybf,movfsmesh) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = GET_H_COREMESH_REGISTERS (FLD (f_sn6));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* nop: nop */

static SEM_PC
SEM_FN_NAME (epiphanybf,nop) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
((void) 0); /*nop*/
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* snop: snop */

static SEM_PC
SEM_FN_NAME (epiphanybf,snop) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
((void) 0); /*nop*/
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* unimpl: unimpl */

static SEM_PC
SEM_FN_NAME (epiphanybf,unimpl) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
((void) 0); /*nop*/
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* idle: idle */

static SEM_PC
SEM_FN_NAME (epiphanybf,idle) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  USI tmp_tmpPC;
  {
    BI opval = 0;
    SET_H_CAIBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "caibit", 'x', opval);
  }
  tmp_tmpPC = pc;
  {
    USI opval = tmp_tmpPC;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bkpt: bkpt */

static SEM_PC
SEM_FN_NAME (epiphanybf,bkpt) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
epiphany_break (current_cpu, pc);
  {
    USI opval = pc;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* mbkpt: mbkpt */

static SEM_PC
SEM_FN_NAME (epiphanybf,mbkpt) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

((void) 0); /*nop*/

  return vpc;
#undef FLD
}

/* rti: rti */

static SEM_PC
SEM_FN_NAME (epiphanybf,rti) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    USI opval = epiphany_rti (current_cpu);
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* wand: wand */

static SEM_PC
SEM_FN_NAME (epiphanybf,wand) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    BI opval = 1;
    SET_H_SFLAGBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "sflagbit", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* sync: sync */

static SEM_PC
SEM_FN_NAME (epiphanybf,sync) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
((void) 0); /*nop*/
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* gien: gie */

static SEM_PC
SEM_FN_NAME (epiphanybf,gien) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
epiphany_gie (current_cpu);
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* gidis: gid */

static SEM_PC
SEM_FN_NAME (epiphanybf,gidis) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    BI opval = 1;
    SET_H_GIDISABLEBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gidisablebit", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* swi_num: swi $swi_num */

static SEM_PC
SEM_FN_NAME (epiphanybf,swi_num) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_SWI;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* trap16: trap $trapnum6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,trap16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_trap16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

  {
    SI opval = epiphany_trap (current_cpu, pc, FLD (f_trap_num));
    SET_H_REGISTERS (((UINT) 0), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* add16: add $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,add16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* add: add $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,add) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* sub16: sub $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,sub16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* sub: sub $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,sub) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* and16: and $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,and16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = ANDSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* and: and $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,and) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = ANDSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* orr16: orr $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,orr16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = ORSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* orr: orr $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,orr) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = ORSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* eor16: eor $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,eor16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = XORSI (GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* eor: eor $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,eor) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = XORSI (GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* addi16: add.s $rd,$rn,$simm3 */

static SEM_PC
SEM_FN_NAME (epiphanybf,addi16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* addi: add.l $rd6,$rn6,$simm11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,addi) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = ADDCFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0);
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = ADDOFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* subi16: sub.s $rd,$rn,$simm3 */

static SEM_PC
SEM_FN_NAME (epiphanybf,subi16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_sdisp3));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* subi: sub.l $rd6,$rn6,$simm11 */

static SEM_PC
SEM_FN_NAME (epiphanybf,subi) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = NOTBI (SUBCFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0));
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = SUBOFSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11), 0);
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_VSBIT (), GET_H_VBIT ());
    SET_H_VSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vsbit", 'x', opval);
  }
}
  {
    SI opval = SUBSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_sdisp11));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* asr16: asr $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,asr16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRASI (GET_H_REGISTERS (FLD (f_rn)), ANDSI (GET_H_REGISTERS (FLD (f_rm)), 31));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* asr: asr $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,asr) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRASI (GET_H_REGISTERS (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 31));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsr16: lsr $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsr16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn)), ANDSI (GET_H_REGISTERS (FLD (f_rm)), 31));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsr: lsr $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsr) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 31));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsl16: lsl $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsl16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn)), ANDSI (GET_H_REGISTERS (FLD (f_rm)), 31));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsl: lsl $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsl) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn6)), ANDSI (GET_H_REGISTERS (FLD (f_rm6)), 31));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsri16: lsr $rd,$rn,$shift */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsri16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsri32: lsr $rd6,$rn6,$shift */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsri32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRLSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsli16: lsl $rd,$rn,$shift */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsli16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lsli32: lsl $rd6,$rn6,$shift */

static SEM_PC
SEM_FN_NAME (epiphanybf,lsli32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SLLSI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* asri16: asr $rd,$rn,$shift */

static SEM_PC
SEM_FN_NAME (epiphanybf,asri16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRASI (GET_H_REGISTERS (FLD (f_rn)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* asri32: asr $rd6,$rn6,$shift */

static SEM_PC
SEM_FN_NAME (epiphanybf,asri32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
  {
    SI opval = SRASI (GET_H_REGISTERS (FLD (f_rn6)), FLD (f_shift));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bitr16: bitr $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,bitr16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
{
  SI tmp_v;
  tmp_v = GET_H_REGISTERS (FLD (f_rn));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 1), 1431655765), SLLSI (ANDSI (tmp_v, 1431655765), 1));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 2), 858993459), SLLSI (ANDSI (tmp_v, 858993459), 2));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 4), 252645135), SLLSI (ANDSI (tmp_v, 252645135), 4));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 8), 16711935), SLLSI (ANDSI (tmp_v, 16711935), 8));
  tmp_v = ORSI (SRLSI (tmp_v, 16), SLLSI (tmp_v, 16));
  {
    SI opval = tmp_v;
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* bitr: bitr $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,bitr) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
{
  SI tmp_v;
  tmp_v = GET_H_REGISTERS (FLD (f_rn6));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 1), 1431655765), SLLSI (ANDSI (tmp_v, 1431655765), 1));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 2), 858993459), SLLSI (ANDSI (tmp_v, 858993459), 2));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 4), 252645135), SLLSI (ANDSI (tmp_v, 252645135), 4));
  tmp_v = ORSI (ANDSI (SRLSI (tmp_v, 8), 16711935), SLLSI (ANDSI (tmp_v, 16711935), 8));
  tmp_v = ORSI (SRLSI (tmp_v, 16), SLLSI (tmp_v, 16));
  {
    SI opval = tmp_v;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_CBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "cbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_VBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "vbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* fext: fext $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,fext) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* fdep: fdep $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,fdep) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* lfsr: lfsr $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,lfsr) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  {
    BI opval = EQSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_ZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "zbit", 'x', opval);
  }
  {
    BI opval = LTSI (GET_H_REGISTERS (FLD (f_rd6)), 0);
    SET_H_NBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "nbit", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* mov8: mov.b $rd,$imm8 */

static SEM_PC
SEM_FN_NAME (epiphanybf,mov8) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_mov8.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
  {
    SI opval = ZEXTSISI (FLD (i_imm8));
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* mov16: mov.l $rd6,$imm16 */

static SEM_PC
SEM_FN_NAME (epiphanybf,mov16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = ZEXTSISI (FLD (i_imm16));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* movt: movt $rd6,$imm16 */

static SEM_PC
SEM_FN_NAME (epiphanybf,movt) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
  {
    SI opval = ORSI (ANDSI (GET_H_REGISTERS (FLD (f_rd6)), 65535), SLLSI (FLD (i_imm16), 16));
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_addf16: fadd $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_addf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_iadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_addf32: fadd $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_addf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_iadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_subf16: fsub $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_subf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_isub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_subf32: fsub $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_subf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_isub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_mulf16: fmul $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_mulf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imul (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_mulf32: fmul $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_mulf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmul (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imul (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_maddf16: fmadd $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_maddf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imadd (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_maddf32: fmadd $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_maddf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imadd (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_msubf16: fmsub $rd,$rn,$rm */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_msubf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imsub (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rm)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_msubf32: fmsub $rd6,$rn6,$rm6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_msubf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 0)) {
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fmsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = get_epiphany_fzeroflag (current_cpu, tmp_sdtmp);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_fnegativeflag (current_cpu, tmp_sdtmp);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    written |= (1 << 18);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    written |= (1 << 17);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    written |= (1 << 15);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BVSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BUSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
}
if (EQBI (GET_H_ARITHMETIC_MODEBIT2 (), 1)) {
{
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_imsub (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    written |= (1 << 16);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    written |= (1 << 25);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 24);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_absf16: fabs rd,rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_absf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_fabs (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rn)));
  {
    BI opval = 0;
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_absf32: fabs $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_absf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_fabs (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rn6)));
  {
    BI opval = 0;
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_loatf16: float $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_loatf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_float (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rn)));
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_loatf32: float $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_loatf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  tmp_sdtmp = epiphany_float (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rn6)));
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 12);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_ixf16: fix $rd,$rn */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_ixf16) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_f_ixf16.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);

{
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fix (current_cpu, GET_H_REGISTERS (FLD (f_rd)), GET_H_REGISTERS (FLD (f_rn)), GET_H_REGISTERS (FLD (f_rn)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BUSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BVSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 19);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_ixf32: fix $rd6,$rn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_ixf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SF tmp_fptemp;
  SI tmp_sdtmp;
  BI tmp_bubit;
  BI tmp_bibit;
  tmp_sdtmp = epiphany_fix (current_cpu, GET_H_REGISTERS (FLD (f_rd6)), GET_H_REGISTERS (FLD (f_rn6)), GET_H_REGISTERS (FLD (f_rm6)));
  {
    BI opval = EQSI (tmp_sdtmp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = LTSI (tmp_sdtmp, 0);
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = get_epiphany_foverflowflag (current_cpu, tmp_sdtmp);
    SET_H_BVBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  tmp_bubit = get_epiphany_funderflowflag (current_cpu, tmp_sdtmp);
  tmp_bibit = get_epiphany_finvalidflag (current_cpu, tmp_sdtmp);
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BUSBIT (), tmp_bubit);
    SET_H_BUSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BISBIT (), tmp_bibit);
    SET_H_BISBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bisbit", 'x', opval);
  }
  {
    SI opval = tmp_sdtmp;
    SET_H_REGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "registers", 'x', opval);
  }
if (ORBI (ANDBI (GET_H_INVEXCENBIT (), GET_H_BISBIT ()), ORBI (ANDBI (GET_H_OVFEXCENBIT (), GET_H_BUSBIT ()), ANDBI (GET_H_UNEXCENBIT (), GET_H_BVSBIT ())))) {
{
  {
    UQI opval = H_SCR_STATUS_EXCAUSE_FPU;
    SET_H_SCR_STATUS_EXCAUSE (opval);
    written |= (1 << 22);
    CGEN_TRACE_RESULT (current_cpu, abuf, "scr-status-excause", 'x', opval);
  }
  {
    USI opval = 2;
    SET_H_CORE_REGISTERS (((UINT) 11), opval);
    written |= (1 << 20);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
}
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 21);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 23);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_recipf32: frecip $frd6,$frn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_recipf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_f_recipf32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SF tmp_fptemp;
  {
    BI opval = 0;
    SET_H_BVBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_BUSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  tmp_fptemp = epiphany_frecip (current_cpu, GET_H_FPREGISTERS (FLD (f_rn6)));
  {
    BI opval = CGEN_CPU_FPU (current_cpu)->ops->ltsf (CGEN_CPU_FPU (current_cpu), tmp_fptemp, 0);
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = CGEN_CPU_FPU (current_cpu)->ops->eqsf (CGEN_CPU_FPU (current_cpu), tmp_fptemp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    SF opval = tmp_fptemp;
    SET_H_FPREGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "fpregisters", 'f', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* f_sqrtf32: fsqrt $frd6,$frn6 */

static SEM_PC
SEM_FN_NAME (epiphanybf,f_sqrtf32) (SIM_CPU *current_cpu, SEM_ARG sem_arg)
{
#define FLD(f) abuf->fields.sfmt_f_recipf32.f
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
  int UNUSED written = 0;
  IADDR UNUSED pc = abuf->addr;
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);

{
{
  SF tmp_fptemp;
  {
    BI opval = 0;
    SET_H_BVBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvbit", 'x', opval);
  }
  {
    BI opval = 0;
    SET_H_BUSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "busbit", 'x', opval);
  }
  tmp_fptemp = epiphany_fsqrt (current_cpu, GET_H_FPREGISTERS (FLD (f_rn6)));
  {
    BI opval = CGEN_CPU_FPU (current_cpu)->ops->ltsf (CGEN_CPU_FPU (current_cpu), tmp_fptemp, 0);
    SET_H_BNBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bnbit", 'x', opval);
  }
  {
    BI opval = CGEN_CPU_FPU (current_cpu)->ops->eqsf (CGEN_CPU_FPU (current_cpu), tmp_fptemp, 0);
    SET_H_BZBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bzbit", 'x', opval);
  }
  {
    BI opval = ORBI (GET_H_BVSBIT (), GET_H_BVBIT ());
    SET_H_BVSBIT (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "bvsbit", 'x', opval);
  }
  {
    SF opval = tmp_fptemp;
    SET_H_FPREGISTERS (FLD (f_rd6), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "fpregisters", 'f', opval);
  }
}
{
  USI tmp_tmpPC;
if (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7)))) {
  {
    USI opval = SUBSI (GET_H_CORE_REGISTERS (((UINT) 5)), 1);
    SET_H_CORE_REGISTERS (((UINT) 5), opval);
    written |= (1 << 13);
    CGEN_TRACE_RESULT (current_cpu, abuf, "core-registers", 'x', opval);
  }
}
if (ANDBI (EQSI (pc, GET_H_CORE_REGISTERS (((UINT) 7))), NOTBI (EQSI (GET_H_CORE_REGISTERS (((UINT) 5)), 0)))) {
  {
    USI opval = GET_H_CORE_REGISTERS (((UINT) 6));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 14);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc);
  return vpc;
#undef FLD
}

/* Table of all semantic fns.  */

static const struct sem_fn_desc sem_fns[] = {
  { EPIPHANYBF_INSN_X_INVALID, SEM_FN_NAME (epiphanybf,x_invalid) },
  { EPIPHANYBF_INSN_X_AFTER, SEM_FN_NAME (epiphanybf,x_after) },
  { EPIPHANYBF_INSN_X_BEFORE, SEM_FN_NAME (epiphanybf,x_before) },
  { EPIPHANYBF_INSN_X_CTI_CHAIN, SEM_FN_NAME (epiphanybf,x_cti_chain) },
  { EPIPHANYBF_INSN_X_CHAIN, SEM_FN_NAME (epiphanybf,x_chain) },
  { EPIPHANYBF_INSN_X_BEGIN, SEM_FN_NAME (epiphanybf,x_begin) },
  { EPIPHANYBF_INSN_BEQ16, SEM_FN_NAME (epiphanybf,beq16) },
  { EPIPHANYBF_INSN_BEQ, SEM_FN_NAME (epiphanybf,beq) },
  { EPIPHANYBF_INSN_BNE16, SEM_FN_NAME (epiphanybf,bne16) },
  { EPIPHANYBF_INSN_BNE, SEM_FN_NAME (epiphanybf,bne) },
  { EPIPHANYBF_INSN_BGTU16, SEM_FN_NAME (epiphanybf,bgtu16) },
  { EPIPHANYBF_INSN_BGTU, SEM_FN_NAME (epiphanybf,bgtu) },
  { EPIPHANYBF_INSN_BGTEU16, SEM_FN_NAME (epiphanybf,bgteu16) },
  { EPIPHANYBF_INSN_BGTEU, SEM_FN_NAME (epiphanybf,bgteu) },
  { EPIPHANYBF_INSN_BLTEU16, SEM_FN_NAME (epiphanybf,blteu16) },
  { EPIPHANYBF_INSN_BLTEU, SEM_FN_NAME (epiphanybf,blteu) },
  { EPIPHANYBF_INSN_BLTU16, SEM_FN_NAME (epiphanybf,bltu16) },
  { EPIPHANYBF_INSN_BLTU, SEM_FN_NAME (epiphanybf,bltu) },
  { EPIPHANYBF_INSN_BGT16, SEM_FN_NAME (epiphanybf,bgt16) },
  { EPIPHANYBF_INSN_BGT, SEM_FN_NAME (epiphanybf,bgt) },
  { EPIPHANYBF_INSN_BGTE16, SEM_FN_NAME (epiphanybf,bgte16) },
  { EPIPHANYBF_INSN_BGTE, SEM_FN_NAME (epiphanybf,bgte) },
  { EPIPHANYBF_INSN_BLT16, SEM_FN_NAME (epiphanybf,blt16) },
  { EPIPHANYBF_INSN_BLT, SEM_FN_NAME (epiphanybf,blt) },
  { EPIPHANYBF_INSN_BLTE16, SEM_FN_NAME (epiphanybf,blte16) },
  { EPIPHANYBF_INSN_BLTE, SEM_FN_NAME (epiphanybf,blte) },
  { EPIPHANYBF_INSN_BBEQ16, SEM_FN_NAME (epiphanybf,bbeq16) },
  { EPIPHANYBF_INSN_BBEQ, SEM_FN_NAME (epiphanybf,bbeq) },
  { EPIPHANYBF_INSN_BBNE16, SEM_FN_NAME (epiphanybf,bbne16) },
  { EPIPHANYBF_INSN_BBNE, SEM_FN_NAME (epiphanybf,bbne) },
  { EPIPHANYBF_INSN_BBLT16, SEM_FN_NAME (epiphanybf,bblt16) },
  { EPIPHANYBF_INSN_BBLT, SEM_FN_NAME (epiphanybf,bblt) },
  { EPIPHANYBF_INSN_BBLTE16, SEM_FN_NAME (epiphanybf,bblte16) },
  { EPIPHANYBF_INSN_BBLTE, SEM_FN_NAME (epiphanybf,bblte) },
  { EPIPHANYBF_INSN_B16, SEM_FN_NAME (epiphanybf,b16) },
  { EPIPHANYBF_INSN_B, SEM_FN_NAME (epiphanybf,b) },
  { EPIPHANYBF_INSN_BL16, SEM_FN_NAME (epiphanybf,bl16) },
  { EPIPHANYBF_INSN_BL, SEM_FN_NAME (epiphanybf,bl) },
  { EPIPHANYBF_INSN_JR16, SEM_FN_NAME (epiphanybf,jr16) },
  { EPIPHANYBF_INSN_JR, SEM_FN_NAME (epiphanybf,jr) },
  { EPIPHANYBF_INSN_JALR16, SEM_FN_NAME (epiphanybf,jalr16) },
  { EPIPHANYBF_INSN_JALR, SEM_FN_NAME (epiphanybf,jalr) },
  { EPIPHANYBF_INSN_LDRBX16_S, SEM_FN_NAME (epiphanybf,ldrbx16_s) },
  { EPIPHANYBF_INSN_LDRBP16_S, SEM_FN_NAME (epiphanybf,ldrbp16_s) },
  { EPIPHANYBF_INSN_LDRBX_L, SEM_FN_NAME (epiphanybf,ldrbx_l) },
  { EPIPHANYBF_INSN_LDRBP_L, SEM_FN_NAME (epiphanybf,ldrbp_l) },
  { EPIPHANYBF_INSN_LDRBD16_S, SEM_FN_NAME (epiphanybf,ldrbd16_s) },
  { EPIPHANYBF_INSN_LDRBD_L, SEM_FN_NAME (epiphanybf,ldrbd_l) },
  { EPIPHANYBF_INSN_LDRBDPM_L, SEM_FN_NAME (epiphanybf,ldrbdpm_l) },
  { EPIPHANYBF_INSN_LDRHX16_S, SEM_FN_NAME (epiphanybf,ldrhx16_s) },
  { EPIPHANYBF_INSN_LDRHP16_S, SEM_FN_NAME (epiphanybf,ldrhp16_s) },
  { EPIPHANYBF_INSN_LDRHX_L, SEM_FN_NAME (epiphanybf,ldrhx_l) },
  { EPIPHANYBF_INSN_LDRHP_L, SEM_FN_NAME (epiphanybf,ldrhp_l) },
  { EPIPHANYBF_INSN_LDRHD16_S, SEM_FN_NAME (epiphanybf,ldrhd16_s) },
  { EPIPHANYBF_INSN_LDRHD_L, SEM_FN_NAME (epiphanybf,ldrhd_l) },
  { EPIPHANYBF_INSN_LDRHDPM_L, SEM_FN_NAME (epiphanybf,ldrhdpm_l) },
  { EPIPHANYBF_INSN_LDRX16_S, SEM_FN_NAME (epiphanybf,ldrx16_s) },
  { EPIPHANYBF_INSN_LDRP16_S, SEM_FN_NAME (epiphanybf,ldrp16_s) },
  { EPIPHANYBF_INSN_LDRX_L, SEM_FN_NAME (epiphanybf,ldrx_l) },
  { EPIPHANYBF_INSN_LDRP_L, SEM_FN_NAME (epiphanybf,ldrp_l) },
  { EPIPHANYBF_INSN_LDRD16_S, SEM_FN_NAME (epiphanybf,ldrd16_s) },
  { EPIPHANYBF_INSN_LDRD_L, SEM_FN_NAME (epiphanybf,ldrd_l) },
  { EPIPHANYBF_INSN_LDRDPM_L, SEM_FN_NAME (epiphanybf,ldrdpm_l) },
  { EPIPHANYBF_INSN_LDRDX16_S, SEM_FN_NAME (epiphanybf,ldrdx16_s) },
  { EPIPHANYBF_INSN_LDRDP16_S, SEM_FN_NAME (epiphanybf,ldrdp16_s) },
  { EPIPHANYBF_INSN_LDRDX_L, SEM_FN_NAME (epiphanybf,ldrdx_l) },
  { EPIPHANYBF_INSN_LDRDP_L, SEM_FN_NAME (epiphanybf,ldrdp_l) },
  { EPIPHANYBF_INSN_LDRDD16_S, SEM_FN_NAME (epiphanybf,ldrdd16_s) },
  { EPIPHANYBF_INSN_LDRDD_L, SEM_FN_NAME (epiphanybf,ldrdd_l) },
  { EPIPHANYBF_INSN_LDRDDPM_L, SEM_FN_NAME (epiphanybf,ldrddpm_l) },
  { EPIPHANYBF_INSN_TESTSETBT, SEM_FN_NAME (epiphanybf,testsetbt) },
  { EPIPHANYBF_INSN_TESTSETHT, SEM_FN_NAME (epiphanybf,testsetht) },
  { EPIPHANYBF_INSN_TESTSETT, SEM_FN_NAME (epiphanybf,testsett) },
  { EPIPHANYBF_INSN_STRBX16, SEM_FN_NAME (epiphanybf,strbx16) },
  { EPIPHANYBF_INSN_STRBX, SEM_FN_NAME (epiphanybf,strbx) },
  { EPIPHANYBF_INSN_STRBP16, SEM_FN_NAME (epiphanybf,strbp16) },
  { EPIPHANYBF_INSN_STRBP, SEM_FN_NAME (epiphanybf,strbp) },
  { EPIPHANYBF_INSN_STRBD16, SEM_FN_NAME (epiphanybf,strbd16) },
  { EPIPHANYBF_INSN_STRBD, SEM_FN_NAME (epiphanybf,strbd) },
  { EPIPHANYBF_INSN_STRBDPM, SEM_FN_NAME (epiphanybf,strbdpm) },
  { EPIPHANYBF_INSN_STRHX16, SEM_FN_NAME (epiphanybf,strhx16) },
  { EPIPHANYBF_INSN_STRHX, SEM_FN_NAME (epiphanybf,strhx) },
  { EPIPHANYBF_INSN_STRHP16, SEM_FN_NAME (epiphanybf,strhp16) },
  { EPIPHANYBF_INSN_STRHP, SEM_FN_NAME (epiphanybf,strhp) },
  { EPIPHANYBF_INSN_STRHD16, SEM_FN_NAME (epiphanybf,strhd16) },
  { EPIPHANYBF_INSN_STRHD, SEM_FN_NAME (epiphanybf,strhd) },
  { EPIPHANYBF_INSN_STRHDPM, SEM_FN_NAME (epiphanybf,strhdpm) },
  { EPIPHANYBF_INSN_STRX16, SEM_FN_NAME (epiphanybf,strx16) },
  { EPIPHANYBF_INSN_STRX, SEM_FN_NAME (epiphanybf,strx) },
  { EPIPHANYBF_INSN_STRP16, SEM_FN_NAME (epiphanybf,strp16) },
  { EPIPHANYBF_INSN_STRP, SEM_FN_NAME (epiphanybf,strp) },
  { EPIPHANYBF_INSN_STRD16, SEM_FN_NAME (epiphanybf,strd16) },
  { EPIPHANYBF_INSN_STRD, SEM_FN_NAME (epiphanybf,strd) },
  { EPIPHANYBF_INSN_STRDPM, SEM_FN_NAME (epiphanybf,strdpm) },
  { EPIPHANYBF_INSN_STRDX16, SEM_FN_NAME (epiphanybf,strdx16) },
  { EPIPHANYBF_INSN_STRDX, SEM_FN_NAME (epiphanybf,strdx) },
  { EPIPHANYBF_INSN_STRDP16, SEM_FN_NAME (epiphanybf,strdp16) },
  { EPIPHANYBF_INSN_STRDP, SEM_FN_NAME (epiphanybf,strdp) },
  { EPIPHANYBF_INSN_STRDD16, SEM_FN_NAME (epiphanybf,strdd16) },
  { EPIPHANYBF_INSN_STRDD, SEM_FN_NAME (epiphanybf,strdd) },
  { EPIPHANYBF_INSN_STRDDPM, SEM_FN_NAME (epiphanybf,strddpm) },
  { EPIPHANYBF_INSN_CMOV16EQ, SEM_FN_NAME (epiphanybf,cmov16EQ) },
  { EPIPHANYBF_INSN_CMOVEQ, SEM_FN_NAME (epiphanybf,cmovEQ) },
  { EPIPHANYBF_INSN_CMOV16NE, SEM_FN_NAME (epiphanybf,cmov16NE) },
  { EPIPHANYBF_INSN_CMOVNE, SEM_FN_NAME (epiphanybf,cmovNE) },
  { EPIPHANYBF_INSN_CMOV16GTU, SEM_FN_NAME (epiphanybf,cmov16GTU) },
  { EPIPHANYBF_INSN_CMOVGTU, SEM_FN_NAME (epiphanybf,cmovGTU) },
  { EPIPHANYBF_INSN_CMOV16GTEU, SEM_FN_NAME (epiphanybf,cmov16GTEU) },
  { EPIPHANYBF_INSN_CMOVGTEU, SEM_FN_NAME (epiphanybf,cmovGTEU) },
  { EPIPHANYBF_INSN_CMOV16LTEU, SEM_FN_NAME (epiphanybf,cmov16LTEU) },
  { EPIPHANYBF_INSN_CMOVLTEU, SEM_FN_NAME (epiphanybf,cmovLTEU) },
  { EPIPHANYBF_INSN_CMOV16LTU, SEM_FN_NAME (epiphanybf,cmov16LTU) },
  { EPIPHANYBF_INSN_CMOVLTU, SEM_FN_NAME (epiphanybf,cmovLTU) },
  { EPIPHANYBF_INSN_CMOV16GT, SEM_FN_NAME (epiphanybf,cmov16GT) },
  { EPIPHANYBF_INSN_CMOVGT, SEM_FN_NAME (epiphanybf,cmovGT) },
  { EPIPHANYBF_INSN_CMOV16GTE, SEM_FN_NAME (epiphanybf,cmov16GTE) },
  { EPIPHANYBF_INSN_CMOVGTE, SEM_FN_NAME (epiphanybf,cmovGTE) },
  { EPIPHANYBF_INSN_CMOV16LT, SEM_FN_NAME (epiphanybf,cmov16LT) },
  { EPIPHANYBF_INSN_CMOVLT, SEM_FN_NAME (epiphanybf,cmovLT) },
  { EPIPHANYBF_INSN_CMOV16LTE, SEM_FN_NAME (epiphanybf,cmov16LTE) },
  { EPIPHANYBF_INSN_CMOVLTE, SEM_FN_NAME (epiphanybf,cmovLTE) },
  { EPIPHANYBF_INSN_CMOV16B, SEM_FN_NAME (epiphanybf,cmov16B) },
  { EPIPHANYBF_INSN_CMOVB, SEM_FN_NAME (epiphanybf,cmovB) },
  { EPIPHANYBF_INSN_CMOV16BEQ, SEM_FN_NAME (epiphanybf,cmov16BEQ) },
  { EPIPHANYBF_INSN_CMOVBEQ, SEM_FN_NAME (epiphanybf,cmovBEQ) },
  { EPIPHANYBF_INSN_CMOV16BNE, SEM_FN_NAME (epiphanybf,cmov16BNE) },
  { EPIPHANYBF_INSN_CMOVBNE, SEM_FN_NAME (epiphanybf,cmovBNE) },
  { EPIPHANYBF_INSN_CMOV16BLT, SEM_FN_NAME (epiphanybf,cmov16BLT) },
  { EPIPHANYBF_INSN_CMOVBLT, SEM_FN_NAME (epiphanybf,cmovBLT) },
  { EPIPHANYBF_INSN_CMOV16BLTE, SEM_FN_NAME (epiphanybf,cmov16BLTE) },
  { EPIPHANYBF_INSN_CMOVBLTE, SEM_FN_NAME (epiphanybf,cmovBLTE) },
  { EPIPHANYBF_INSN_MOVTS16, SEM_FN_NAME (epiphanybf,movts16) },
  { EPIPHANYBF_INSN_MOVTS6, SEM_FN_NAME (epiphanybf,movts6) },
  { EPIPHANYBF_INSN_MOVTSDMA, SEM_FN_NAME (epiphanybf,movtsdma) },
  { EPIPHANYBF_INSN_MOVTSMEM, SEM_FN_NAME (epiphanybf,movtsmem) },
  { EPIPHANYBF_INSN_MOVTSMESH, SEM_FN_NAME (epiphanybf,movtsmesh) },
  { EPIPHANYBF_INSN_MOVFS16, SEM_FN_NAME (epiphanybf,movfs16) },
  { EPIPHANYBF_INSN_MOVFS6, SEM_FN_NAME (epiphanybf,movfs6) },
  { EPIPHANYBF_INSN_MOVFSDMA, SEM_FN_NAME (epiphanybf,movfsdma) },
  { EPIPHANYBF_INSN_MOVFSMEM, SEM_FN_NAME (epiphanybf,movfsmem) },
  { EPIPHANYBF_INSN_MOVFSMESH, SEM_FN_NAME (epiphanybf,movfsmesh) },
  { EPIPHANYBF_INSN_NOP, SEM_FN_NAME (epiphanybf,nop) },
  { EPIPHANYBF_INSN_SNOP, SEM_FN_NAME (epiphanybf,snop) },
  { EPIPHANYBF_INSN_UNIMPL, SEM_FN_NAME (epiphanybf,unimpl) },
  { EPIPHANYBF_INSN_IDLE, SEM_FN_NAME (epiphanybf,idle) },
  { EPIPHANYBF_INSN_BKPT, SEM_FN_NAME (epiphanybf,bkpt) },
  { EPIPHANYBF_INSN_MBKPT, SEM_FN_NAME (epiphanybf,mbkpt) },
  { EPIPHANYBF_INSN_RTI, SEM_FN_NAME (epiphanybf,rti) },
  { EPIPHANYBF_INSN_WAND, SEM_FN_NAME (epiphanybf,wand) },
  { EPIPHANYBF_INSN_SYNC, SEM_FN_NAME (epiphanybf,sync) },
  { EPIPHANYBF_INSN_GIEN, SEM_FN_NAME (epiphanybf,gien) },
  { EPIPHANYBF_INSN_GIDIS, SEM_FN_NAME (epiphanybf,gidis) },
  { EPIPHANYBF_INSN_SWI_NUM, SEM_FN_NAME (epiphanybf,swi_num) },
  { EPIPHANYBF_INSN_TRAP16, SEM_FN_NAME (epiphanybf,trap16) },
  { EPIPHANYBF_INSN_ADD16, SEM_FN_NAME (epiphanybf,add16) },
  { EPIPHANYBF_INSN_ADD, SEM_FN_NAME (epiphanybf,add) },
  { EPIPHANYBF_INSN_SUB16, SEM_FN_NAME (epiphanybf,sub16) },
  { EPIPHANYBF_INSN_SUB, SEM_FN_NAME (epiphanybf,sub) },
  { EPIPHANYBF_INSN_AND16, SEM_FN_NAME (epiphanybf,and16) },
  { EPIPHANYBF_INSN_AND, SEM_FN_NAME (epiphanybf,and) },
  { EPIPHANYBF_INSN_ORR16, SEM_FN_NAME (epiphanybf,orr16) },
  { EPIPHANYBF_INSN_ORR, SEM_FN_NAME (epiphanybf,orr) },
  { EPIPHANYBF_INSN_EOR16, SEM_FN_NAME (epiphanybf,eor16) },
  { EPIPHANYBF_INSN_EOR, SEM_FN_NAME (epiphanybf,eor) },
  { EPIPHANYBF_INSN_ADDI16, SEM_FN_NAME (epiphanybf,addi16) },
  { EPIPHANYBF_INSN_ADDI, SEM_FN_NAME (epiphanybf,addi) },
  { EPIPHANYBF_INSN_SUBI16, SEM_FN_NAME (epiphanybf,subi16) },
  { EPIPHANYBF_INSN_SUBI, SEM_FN_NAME (epiphanybf,subi) },
  { EPIPHANYBF_INSN_ASR16, SEM_FN_NAME (epiphanybf,asr16) },
  { EPIPHANYBF_INSN_ASR, SEM_FN_NAME (epiphanybf,asr) },
  { EPIPHANYBF_INSN_LSR16, SEM_FN_NAME (epiphanybf,lsr16) },
  { EPIPHANYBF_INSN_LSR, SEM_FN_NAME (epiphanybf,lsr) },
  { EPIPHANYBF_INSN_LSL16, SEM_FN_NAME (epiphanybf,lsl16) },
  { EPIPHANYBF_INSN_LSL, SEM_FN_NAME (epiphanybf,lsl) },
  { EPIPHANYBF_INSN_LSRI16, SEM_FN_NAME (epiphanybf,lsri16) },
  { EPIPHANYBF_INSN_LSRI32, SEM_FN_NAME (epiphanybf,lsri32) },
  { EPIPHANYBF_INSN_LSLI16, SEM_FN_NAME (epiphanybf,lsli16) },
  { EPIPHANYBF_INSN_LSLI32, SEM_FN_NAME (epiphanybf,lsli32) },
  { EPIPHANYBF_INSN_ASRI16, SEM_FN_NAME (epiphanybf,asri16) },
  { EPIPHANYBF_INSN_ASRI32, SEM_FN_NAME (epiphanybf,asri32) },
  { EPIPHANYBF_INSN_BITR16, SEM_FN_NAME (epiphanybf,bitr16) },
  { EPIPHANYBF_INSN_BITR, SEM_FN_NAME (epiphanybf,bitr) },
  { EPIPHANYBF_INSN_FEXT, SEM_FN_NAME (epiphanybf,fext) },
  { EPIPHANYBF_INSN_FDEP, SEM_FN_NAME (epiphanybf,fdep) },
  { EPIPHANYBF_INSN_LFSR, SEM_FN_NAME (epiphanybf,lfsr) },
  { EPIPHANYBF_INSN_MOV8, SEM_FN_NAME (epiphanybf,mov8) },
  { EPIPHANYBF_INSN_MOV16, SEM_FN_NAME (epiphanybf,mov16) },
  { EPIPHANYBF_INSN_MOVT, SEM_FN_NAME (epiphanybf,movt) },
  { EPIPHANYBF_INSN_F_ADDF16, SEM_FN_NAME (epiphanybf,f_addf16) },
  { EPIPHANYBF_INSN_F_ADDF32, SEM_FN_NAME (epiphanybf,f_addf32) },
  { EPIPHANYBF_INSN_F_SUBF16, SEM_FN_NAME (epiphanybf,f_subf16) },
  { EPIPHANYBF_INSN_F_SUBF32, SEM_FN_NAME (epiphanybf,f_subf32) },
  { EPIPHANYBF_INSN_F_MULF16, SEM_FN_NAME (epiphanybf,f_mulf16) },
  { EPIPHANYBF_INSN_F_MULF32, SEM_FN_NAME (epiphanybf,f_mulf32) },
  { EPIPHANYBF_INSN_F_MADDF16, SEM_FN_NAME (epiphanybf,f_maddf16) },
  { EPIPHANYBF_INSN_F_MADDF32, SEM_FN_NAME (epiphanybf,f_maddf32) },
  { EPIPHANYBF_INSN_F_MSUBF16, SEM_FN_NAME (epiphanybf,f_msubf16) },
  { EPIPHANYBF_INSN_F_MSUBF32, SEM_FN_NAME (epiphanybf,f_msubf32) },
  { EPIPHANYBF_INSN_F_ABSF16, SEM_FN_NAME (epiphanybf,f_absf16) },
  { EPIPHANYBF_INSN_F_ABSF32, SEM_FN_NAME (epiphanybf,f_absf32) },
  { EPIPHANYBF_INSN_F_LOATF16, SEM_FN_NAME (epiphanybf,f_loatf16) },
  { EPIPHANYBF_INSN_F_LOATF32, SEM_FN_NAME (epiphanybf,f_loatf32) },
  { EPIPHANYBF_INSN_F_IXF16, SEM_FN_NAME (epiphanybf,f_ixf16) },
  { EPIPHANYBF_INSN_F_IXF32, SEM_FN_NAME (epiphanybf,f_ixf32) },
  { EPIPHANYBF_INSN_F_RECIPF32, SEM_FN_NAME (epiphanybf,f_recipf32) },
  { EPIPHANYBF_INSN_F_SQRTF32, SEM_FN_NAME (epiphanybf,f_sqrtf32) },
  { 0, 0 }
};

/* Add the semantic fns to IDESC_TABLE.  */

void
SEM_FN_NAME (epiphanybf,init_idesc_table) (SIM_CPU *current_cpu)
{
  IDESC *idesc_table = CPU_IDESC (current_cpu);
  const struct sem_fn_desc *sf;
  int mach_num = MACH_NUM (CPU_MACH (current_cpu));

  for (sf = &sem_fns[0]; sf->fn != 0; ++sf)
    {
      const CGEN_INSN *insn = idesc_table[sf->index].idata;
      int valid_p = (CGEN_INSN_VIRTUAL_P (insn)
		     || CGEN_INSN_MACH_HAS_P (insn, mach_num));
#if FAST_P
      if (valid_p)
	idesc_table[sf->index].sem_fast = sf->fn;
      else
	idesc_table[sf->index].sem_fast = SEM_FN_NAME (epiphanybf,x_invalid);
#else
      if (valid_p)
	idesc_table[sf->index].sem_full = sf->fn;
      else
	idesc_table[sf->index].sem_full = SEM_FN_NAME (epiphanybf,x_invalid);
#endif
    }
}

