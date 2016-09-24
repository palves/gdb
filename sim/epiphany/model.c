/* Simulator model support for epiphanybf.

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

/* The profiling data is recorded here, but is accessed via the profiling
   mechanism.  After all, this is information for profiling.  */

#if WITH_PROFILE_MODEL_P

/* Model handlers for each insn.  */

static int
model_epiphany32_beq16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_beq (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bne16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bne (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgtu16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgtu (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgteu16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgteu (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_blteu16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_blteu (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bltu16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bltu (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgt16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgt (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgte16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bgte (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_blt16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_blt (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_blte16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_blte (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bbeq16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bbeq (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bbne16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bbne (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bblt16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bblt (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bblte16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bblte (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_b16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_b (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bl16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bl (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_bl.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_jr16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_jr (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_jalr16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_jalr (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_jalr.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrbx16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrbp16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrbx_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrbp_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrbd16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrbd_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrbdpm_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrhx16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrhp16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrhx_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrhp_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrhd16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrhd_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrhdpm_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrx16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrp16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrx_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrp_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrd16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrd_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrdpm_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrdx16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrdp16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrdx_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrdp_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrdd16_s (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrdd_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_ldrddpm_l (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_testsetbt (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_testsetht (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_testsett (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strbx16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strbx (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strbp16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strbp (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strbd16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strbd (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strbdpm (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strhx16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strhx (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strhp16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strhp (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strhd16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strhd (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strhdpm (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strx16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strx (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strp16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strp (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strd16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strd (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strdpm (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strdx16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strdx (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strdp16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strdp (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdp.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strdd16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strdd16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strdd (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_strddpm (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_strddpm.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16EQ (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovEQ (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16NE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovNE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16GTU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovGTU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16GTEU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovGTEU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16LTEU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovLTEU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16LTU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovLTU (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16GT (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovGT (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16GTE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovGTE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16LT (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovLT (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16LTE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovLTE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16B (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovB (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16BEQ (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovBEQ (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16BNE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovBNE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16BLT (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovBLT (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmov16BLTE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_cmovBLTE (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movts16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movts6 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movtsdma (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movtsmem (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movtsmesh (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movfs16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movfs6 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movfsdma (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movfsmem (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movfsmesh (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movfs6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_nop (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_snop (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_unimpl (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_idle (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bkpt (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_mbkpt (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_rti (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_wand (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_sync (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_gien (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_gidis (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_swi_num (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_empty.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_trap16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_trap16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_add16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_add (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_sub16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_sub (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_and16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_and (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_orr16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_orr (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_eor16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_eor (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_addi16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_addi (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_subi16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_subi (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_addi.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_asr16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_asr (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsr16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsr (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsl16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsl (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsri16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsri32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsli16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lsli32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_asri16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_asri32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bitr16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_bitr (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_fext (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_fdep (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_lfsr (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movts6.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_mov8 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_mov8.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_mov16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_movt (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_movt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_addf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_addf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_subf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_subf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_mulf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_mulf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_maddf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_maddf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_msubf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_add16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_msubf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_absf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_absf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_loatf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_loatf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_lsri32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_ixf16 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_f_ixf16.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_ixf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_testsetbt.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_recipf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_f_recipf32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

static int
model_epiphany32_f_sqrtf32 (SIM_CPU *current_cpu, void *sem_arg)
{
#define FLD(f) abuf->fields.sfmt_f_recipf32.f
  const ARGBUF * UNUSED abuf = SEM_ARGBUF ((SEM_ARG) sem_arg);
  const IDESC * UNUSED idesc = abuf->idesc;
  int cycles = 0;
  {
    int referenced = 0;
    int UNUSED insn_referenced = abuf->written;
    cycles += epiphanybf_model_epiphany32_u_exec (current_cpu, idesc, 0, referenced);
  }
  return cycles;
#undef FLD
}

/* We assume UNIT_NONE == 0 because the tables don't always terminate
   entries with it.  */

/* Model timing data for `epiphany32'.  */

static const INSN_TIMING epiphany32_timing[] = {
  { EPIPHANYBF_INSN_X_INVALID, 0, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_X_AFTER, 0, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_X_BEFORE, 0, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_X_CTI_CHAIN, 0, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_X_CHAIN, 0, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_X_BEGIN, 0, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BEQ16, model_epiphany32_beq16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BEQ, model_epiphany32_beq, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BNE16, model_epiphany32_bne16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BNE, model_epiphany32_bne, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGTU16, model_epiphany32_bgtu16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGTU, model_epiphany32_bgtu, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGTEU16, model_epiphany32_bgteu16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGTEU, model_epiphany32_bgteu, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLTEU16, model_epiphany32_blteu16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLTEU, model_epiphany32_blteu, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLTU16, model_epiphany32_bltu16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLTU, model_epiphany32_bltu, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGT16, model_epiphany32_bgt16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGT, model_epiphany32_bgt, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGTE16, model_epiphany32_bgte16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BGTE, model_epiphany32_bgte, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLT16, model_epiphany32_blt16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLT, model_epiphany32_blt, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLTE16, model_epiphany32_blte16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BLTE, model_epiphany32_blte, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBEQ16, model_epiphany32_bbeq16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBEQ, model_epiphany32_bbeq, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBNE16, model_epiphany32_bbne16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBNE, model_epiphany32_bbne, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBLT16, model_epiphany32_bblt16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBLT, model_epiphany32_bblt, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBLTE16, model_epiphany32_bblte16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BBLTE, model_epiphany32_bblte, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_B16, model_epiphany32_b16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_B, model_epiphany32_b, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BL16, model_epiphany32_bl16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BL, model_epiphany32_bl, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_JR16, model_epiphany32_jr16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_JR, model_epiphany32_jr, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_JALR16, model_epiphany32_jalr16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_JALR, model_epiphany32_jalr, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRBX16_S, model_epiphany32_ldrbx16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRBP16_S, model_epiphany32_ldrbp16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRBX_L, model_epiphany32_ldrbx_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRBP_L, model_epiphany32_ldrbp_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRBD16_S, model_epiphany32_ldrbd16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRBD_L, model_epiphany32_ldrbd_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRBDPM_L, model_epiphany32_ldrbdpm_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRHX16_S, model_epiphany32_ldrhx16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRHP16_S, model_epiphany32_ldrhp16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRHX_L, model_epiphany32_ldrhx_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRHP_L, model_epiphany32_ldrhp_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRHD16_S, model_epiphany32_ldrhd16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRHD_L, model_epiphany32_ldrhd_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRHDPM_L, model_epiphany32_ldrhdpm_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRX16_S, model_epiphany32_ldrx16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRP16_S, model_epiphany32_ldrp16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRX_L, model_epiphany32_ldrx_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRP_L, model_epiphany32_ldrp_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRD16_S, model_epiphany32_ldrd16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRD_L, model_epiphany32_ldrd_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDPM_L, model_epiphany32_ldrdpm_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDX16_S, model_epiphany32_ldrdx16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDP16_S, model_epiphany32_ldrdp16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDX_L, model_epiphany32_ldrdx_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDP_L, model_epiphany32_ldrdp_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDD16_S, model_epiphany32_ldrdd16_s, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDD_L, model_epiphany32_ldrdd_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LDRDDPM_L, model_epiphany32_ldrddpm_l, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_TESTSETBT, model_epiphany32_testsetbt, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_TESTSETHT, model_epiphany32_testsetht, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_TESTSETT, model_epiphany32_testsett, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRBX16, model_epiphany32_strbx16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRBX, model_epiphany32_strbx, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRBP16, model_epiphany32_strbp16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRBP, model_epiphany32_strbp, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRBD16, model_epiphany32_strbd16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRBD, model_epiphany32_strbd, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRBDPM, model_epiphany32_strbdpm, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRHX16, model_epiphany32_strhx16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRHX, model_epiphany32_strhx, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRHP16, model_epiphany32_strhp16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRHP, model_epiphany32_strhp, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRHD16, model_epiphany32_strhd16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRHD, model_epiphany32_strhd, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRHDPM, model_epiphany32_strhdpm, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRX16, model_epiphany32_strx16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRX, model_epiphany32_strx, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRP16, model_epiphany32_strp16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRP, model_epiphany32_strp, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRD16, model_epiphany32_strd16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRD, model_epiphany32_strd, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDPM, model_epiphany32_strdpm, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDX16, model_epiphany32_strdx16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDX, model_epiphany32_strdx, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDP16, model_epiphany32_strdp16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDP, model_epiphany32_strdp, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDD16, model_epiphany32_strdd16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDD, model_epiphany32_strdd, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_STRDDPM, model_epiphany32_strddpm, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16EQ, model_epiphany32_cmov16EQ, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVEQ, model_epiphany32_cmovEQ, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16NE, model_epiphany32_cmov16NE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVNE, model_epiphany32_cmovNE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16GTU, model_epiphany32_cmov16GTU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVGTU, model_epiphany32_cmovGTU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16GTEU, model_epiphany32_cmov16GTEU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVGTEU, model_epiphany32_cmovGTEU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16LTEU, model_epiphany32_cmov16LTEU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVLTEU, model_epiphany32_cmovLTEU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16LTU, model_epiphany32_cmov16LTU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVLTU, model_epiphany32_cmovLTU, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16GT, model_epiphany32_cmov16GT, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVGT, model_epiphany32_cmovGT, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16GTE, model_epiphany32_cmov16GTE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVGTE, model_epiphany32_cmovGTE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16LT, model_epiphany32_cmov16LT, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVLT, model_epiphany32_cmovLT, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16LTE, model_epiphany32_cmov16LTE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVLTE, model_epiphany32_cmovLTE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16B, model_epiphany32_cmov16B, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVB, model_epiphany32_cmovB, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16BEQ, model_epiphany32_cmov16BEQ, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVBEQ, model_epiphany32_cmovBEQ, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16BNE, model_epiphany32_cmov16BNE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVBNE, model_epiphany32_cmovBNE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16BLT, model_epiphany32_cmov16BLT, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVBLT, model_epiphany32_cmovBLT, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOV16BLTE, model_epiphany32_cmov16BLTE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_CMOVBLTE, model_epiphany32_cmovBLTE, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVTS16, model_epiphany32_movts16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVTS6, model_epiphany32_movts6, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVTSDMA, model_epiphany32_movtsdma, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVTSMEM, model_epiphany32_movtsmem, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVTSMESH, model_epiphany32_movtsmesh, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVFS16, model_epiphany32_movfs16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVFS6, model_epiphany32_movfs6, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVFSDMA, model_epiphany32_movfsdma, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVFSMEM, model_epiphany32_movfsmem, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVFSMESH, model_epiphany32_movfsmesh, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_NOP, model_epiphany32_nop, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_SNOP, model_epiphany32_snop, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_UNIMPL, model_epiphany32_unimpl, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_IDLE, model_epiphany32_idle, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BKPT, model_epiphany32_bkpt, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MBKPT, model_epiphany32_mbkpt, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_RTI, model_epiphany32_rti, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_WAND, model_epiphany32_wand, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_SYNC, model_epiphany32_sync, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_GIEN, model_epiphany32_gien, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_GIDIS, model_epiphany32_gidis, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_SWI_NUM, model_epiphany32_swi_num, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_TRAP16, model_epiphany32_trap16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ADD16, model_epiphany32_add16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ADD, model_epiphany32_add, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_SUB16, model_epiphany32_sub16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_SUB, model_epiphany32_sub, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_AND16, model_epiphany32_and16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_AND, model_epiphany32_and, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ORR16, model_epiphany32_orr16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ORR, model_epiphany32_orr, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_EOR16, model_epiphany32_eor16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_EOR, model_epiphany32_eor, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ADDI16, model_epiphany32_addi16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ADDI, model_epiphany32_addi, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_SUBI16, model_epiphany32_subi16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_SUBI, model_epiphany32_subi, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ASR16, model_epiphany32_asr16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ASR, model_epiphany32_asr, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSR16, model_epiphany32_lsr16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSR, model_epiphany32_lsr, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSL16, model_epiphany32_lsl16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSL, model_epiphany32_lsl, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSRI16, model_epiphany32_lsri16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSRI32, model_epiphany32_lsri32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSLI16, model_epiphany32_lsli16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LSLI32, model_epiphany32_lsli32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ASRI16, model_epiphany32_asri16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_ASRI32, model_epiphany32_asri32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BITR16, model_epiphany32_bitr16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_BITR, model_epiphany32_bitr, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_FEXT, model_epiphany32_fext, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_FDEP, model_epiphany32_fdep, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_LFSR, model_epiphany32_lfsr, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOV8, model_epiphany32_mov8, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOV16, model_epiphany32_mov16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_MOVT, model_epiphany32_movt, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_ADDF16, model_epiphany32_f_addf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_ADDF32, model_epiphany32_f_addf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_SUBF16, model_epiphany32_f_subf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_SUBF32, model_epiphany32_f_subf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_MULF16, model_epiphany32_f_mulf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_MULF32, model_epiphany32_f_mulf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_MADDF16, model_epiphany32_f_maddf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_MADDF32, model_epiphany32_f_maddf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_MSUBF16, model_epiphany32_f_msubf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_MSUBF32, model_epiphany32_f_msubf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_ABSF16, model_epiphany32_f_absf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_ABSF32, model_epiphany32_f_absf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_LOATF16, model_epiphany32_f_loatf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_LOATF32, model_epiphany32_f_loatf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_IXF16, model_epiphany32_f_ixf16, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_IXF32, model_epiphany32_f_ixf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_RECIPF32, model_epiphany32_f_recipf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
  { EPIPHANYBF_INSN_F_SQRTF32, model_epiphany32_f_sqrtf32, { { (int) UNIT_EPIPHANY32_U_EXEC, 1, 1 } } },
};

#endif /* WITH_PROFILE_MODEL_P */

static void
epiphany32_model_init (SIM_CPU *cpu)
{
  CPU_MODEL_DATA (cpu) = (void *) zalloc (sizeof (MODEL_EPIPHANY32_DATA));
}

#if WITH_PROFILE_MODEL_P
#define TIMING_DATA(td) td
#else
#define TIMING_DATA(td) 0
#endif

static const MODEL epiphany32_models[] =
{
  { "epiphany32", & epiphany32_mach, MODEL_EPIPHANY32, TIMING_DATA (& epiphany32_timing[0]), epiphany32_model_init },
  { 0 }
};

/* The properties of this cpu's implementation.  */

static const MACH_IMP_PROPERTIES epiphanybf_imp_properties =
{
  sizeof (SIM_CPU),
#if WITH_SCACHE
  sizeof (SCACHE)
#else
  0
#endif
};


static void
epiphanybf_prepare_run (SIM_CPU *cpu)
{
  if (CPU_IDESC (cpu) == NULL)
    epiphanybf_init_idesc_table (cpu);
}

static const CGEN_INSN *
epiphanybf_get_idata (SIM_CPU *cpu, int inum)
{
  return CPU_IDESC (cpu) [inum].idata;
}

static void
epiphany32_init_cpu (SIM_CPU *cpu)
{
  CPU_REG_FETCH (cpu) = epiphanybf_fetch_register;
  CPU_REG_STORE (cpu) = epiphanybf_store_register;
  CPU_PC_FETCH (cpu) = epiphanybf_h_pc_get;
  CPU_PC_STORE (cpu) = epiphanybf_h_pc_set;
  CPU_GET_IDATA (cpu) = epiphanybf_get_idata;
  CPU_MAX_INSNS (cpu) = EPIPHANYBF_INSN__MAX;
  CPU_INSN_NAME (cpu) = cgen_insn_name;
  CPU_FULL_ENGINE_FN (cpu) = epiphanybf_engine_run_full;
#if WITH_FAST
  CPU_FAST_ENGINE_FN (cpu) = epiphanybf_engine_run_fast;
#else
  CPU_FAST_ENGINE_FN (cpu) = epiphanybf_engine_run_full;
#endif
}

const MACH epiphany32_mach =
{
  "epiphany32", "epiphany32", MACH_EPIPHANY32,
  32, 32, & epiphany32_models[0], & epiphanybf_imp_properties,
  epiphany32_init_cpu,
  epiphanybf_prepare_run
};

