/* Misc. support for CPU family epiphanybf.

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
#include "cgen-ops.h"

/* Get the value of h-all-registers.  */

SI
epiphanybf_h_all_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return CPU (h_all_registers[regno]);
}

/* Set a value for h-all-registers.  */

void
epiphanybf_h_all_registers_set (SIM_CPU *current_cpu, UINT regno, SI newval)
{
  SET_H_ALL_REGISTERS (regno, newval);
}

/* Get the value of h-registers.  */

SI
epiphanybf_h_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_REGISTERS (regno);
}

/* Set a value for h-registers.  */

void
epiphanybf_h_registers_set (SIM_CPU *current_cpu, UINT regno, SI newval)
{
  SET_H_REGISTERS (regno, newval);
}

/* Get the value of h-fpregisters.  */

SF
epiphanybf_h_fpregisters_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_FPREGISTERS (regno);
}

/* Set a value for h-fpregisters.  */

void
epiphanybf_h_fpregisters_set (SIM_CPU *current_cpu, UINT regno, SF newval)
{
  SET_H_FPREGISTERS (regno, newval);
}

/* Get the value of h-pc.  */

USI
epiphanybf_h_pc_get (SIM_CPU *current_cpu)
{
  return GET_H_PC ();
}

/* Set a value for h-pc.  */

void
epiphanybf_h_pc_set (SIM_CPU *current_cpu, USI newval)
{
  SET_H_PC (newval);
}

/* Get the value of h-memaddr.  */

SI
epiphanybf_h_memaddr_get (SIM_CPU *current_cpu)
{
  return CPU (h_memaddr);
}

/* Set a value for h-memaddr.  */

void
epiphanybf_h_memaddr_set (SIM_CPU *current_cpu, SI newval)
{
  CPU (h_memaddr) = newval;
}

/* Get the value of h-core-registers.  */

USI
epiphanybf_h_core_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_CORE_REGISTERS (regno);
}

/* Set a value for h-core-registers.  */

void
epiphanybf_h_core_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  SET_H_CORE_REGISTERS (regno, newval);
}

/* Get the value of h-caibit.  */

BI
epiphanybf_h_caibit_get (SIM_CPU *current_cpu)
{
  return GET_H_CAIBIT ();
}

/* Set a value for h-caibit.  */

void
epiphanybf_h_caibit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_CAIBIT (newval);
}

/* Get the value of h-gidisablebit.  */

BI
epiphanybf_h_gidisablebit_get (SIM_CPU *current_cpu)
{
  return GET_H_GIDISABLEBIT ();
}

/* Set a value for h-gidisablebit.  */

void
epiphanybf_h_gidisablebit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_GIDISABLEBIT (newval);
}

/* Get the value of h-kmbit.  */

BI
epiphanybf_h_kmbit_get (SIM_CPU *current_cpu)
{
  return GET_H_KMBIT ();
}

/* Set a value for h-kmbit.  */

void
epiphanybf_h_kmbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_KMBIT (newval);
}

/* Get the value of h-sflagbit.  */

BI
epiphanybf_h_sflagbit_get (SIM_CPU *current_cpu)
{
  return GET_H_SFLAGBIT ();
}

/* Set a value for h-sflagbit.  */

void
epiphanybf_h_sflagbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_SFLAGBIT (newval);
}

/* Get the value of h-zbit.  */

BI
epiphanybf_h_zbit_get (SIM_CPU *current_cpu)
{
  return GET_H_ZBIT ();
}

/* Set a value for h-zbit.  */

void
epiphanybf_h_zbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_ZBIT (newval);
}

/* Get the value of h-nbit.  */

BI
epiphanybf_h_nbit_get (SIM_CPU *current_cpu)
{
  return GET_H_NBIT ();
}

/* Set a value for h-nbit.  */

void
epiphanybf_h_nbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_NBIT (newval);
}

/* Get the value of h-cbit.  */

BI
epiphanybf_h_cbit_get (SIM_CPU *current_cpu)
{
  return GET_H_CBIT ();
}

/* Set a value for h-cbit.  */

void
epiphanybf_h_cbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_CBIT (newval);
}

/* Get the value of h-vbit.  */

BI
epiphanybf_h_vbit_get (SIM_CPU *current_cpu)
{
  return GET_H_VBIT ();
}

/* Set a value for h-vbit.  */

void
epiphanybf_h_vbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_VBIT (newval);
}

/* Get the value of h-bzbit.  */

BI
epiphanybf_h_bzbit_get (SIM_CPU *current_cpu)
{
  return GET_H_BZBIT ();
}

/* Set a value for h-bzbit.  */

void
epiphanybf_h_bzbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_BZBIT (newval);
}

/* Get the value of h-bnbit.  */

BI
epiphanybf_h_bnbit_get (SIM_CPU *current_cpu)
{
  return GET_H_BNBIT ();
}

/* Set a value for h-bnbit.  */

void
epiphanybf_h_bnbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_BNBIT (newval);
}

/* Get the value of h-bvbit.  */

BI
epiphanybf_h_bvbit_get (SIM_CPU *current_cpu)
{
  return GET_H_BVBIT ();
}

/* Set a value for h-bvbit.  */

void
epiphanybf_h_bvbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_BVBIT (newval);
}

/* Get the value of h-bcbit.  */

BI
epiphanybf_h_bcbit_get (SIM_CPU *current_cpu)
{
  return GET_H_BCBIT ();
}

/* Set a value for h-bcbit.  */

void
epiphanybf_h_bcbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_BCBIT (newval);
}

/* Get the value of h-vsbit.  */

BI
epiphanybf_h_vsbit_get (SIM_CPU *current_cpu)
{
  return GET_H_VSBIT ();
}

/* Set a value for h-vsbit.  */

void
epiphanybf_h_vsbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_VSBIT (newval);
}

/* Get the value of h-bisbit.  */

BI
epiphanybf_h_bisbit_get (SIM_CPU *current_cpu)
{
  return GET_H_BISBIT ();
}

/* Set a value for h-bisbit.  */

void
epiphanybf_h_bisbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_BISBIT (newval);
}

/* Get the value of h-bvsbit.  */

BI
epiphanybf_h_bvsbit_get (SIM_CPU *current_cpu)
{
  return GET_H_BVSBIT ();
}

/* Set a value for h-bvsbit.  */

void
epiphanybf_h_bvsbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_BVSBIT (newval);
}

/* Get the value of h-busbit.  */

BI
epiphanybf_h_busbit_get (SIM_CPU *current_cpu)
{
  return GET_H_BUSBIT ();
}

/* Set a value for h-busbit.  */

void
epiphanybf_h_busbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_BUSBIT (newval);
}

/* Get the value of h-excause0bit.  */

BI
epiphanybf_h_excause0bit_get (SIM_CPU *current_cpu)
{
  return GET_H_EXCAUSE0BIT ();
}

/* Set a value for h-excause0bit.  */

void
epiphanybf_h_excause0bit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_EXCAUSE0BIT (newval);
}

/* Get the value of h-excause1bit.  */

BI
epiphanybf_h_excause1bit_get (SIM_CPU *current_cpu)
{
  return GET_H_EXCAUSE1BIT ();
}

/* Set a value for h-excause1bit.  */

void
epiphanybf_h_excause1bit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_EXCAUSE1BIT (newval);
}

/* Get the value of h-excause2bit.  */

BI
epiphanybf_h_excause2bit_get (SIM_CPU *current_cpu)
{
  return GET_H_EXCAUSE2BIT ();
}

/* Set a value for h-excause2bit.  */

void
epiphanybf_h_excause2bit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_EXCAUSE2BIT (newval);
}

/* Get the value of h-excause3bit.  */

BI
epiphanybf_h_excause3bit_get (SIM_CPU *current_cpu)
{
  return GET_H_EXCAUSE3BIT ();
}

/* Set a value for h-excause3bit.  */

void
epiphanybf_h_excause3bit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_EXCAUSE3BIT (newval);
}

/* Get the value of h-scr-status-excause.  */

UQI
epiphanybf_h_scr_status_excause_get (SIM_CPU *current_cpu)
{
  return GET_H_SCR_STATUS_EXCAUSE ();
}

/* Set a value for h-scr-status-excause.  */

void
epiphanybf_h_scr_status_excause_set (SIM_CPU *current_cpu, UQI newval)
{
  SET_H_SCR_STATUS_EXCAUSE (newval);
}

/* Get the value of h-trmbit.  */

BI
epiphanybf_h_trmbit_get (SIM_CPU *current_cpu)
{
  return GET_H_TRMBIT ();
}

/* Set a value for h-trmbit.  */

void
epiphanybf_h_trmbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TRMBIT (newval);
}

/* Get the value of h-invexcenbit.  */

BI
epiphanybf_h_invexcenbit_get (SIM_CPU *current_cpu)
{
  return GET_H_INVEXCENBIT ();
}

/* Set a value for h-invexcenbit.  */

void
epiphanybf_h_invexcenbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_INVEXCENBIT (newval);
}

/* Get the value of h-ovfexcenbit.  */

BI
epiphanybf_h_ovfexcenbit_get (SIM_CPU *current_cpu)
{
  return GET_H_OVFEXCENBIT ();
}

/* Set a value for h-ovfexcenbit.  */

void
epiphanybf_h_ovfexcenbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_OVFEXCENBIT (newval);
}

/* Get the value of h-unexcenbit.  */

BI
epiphanybf_h_unexcenbit_get (SIM_CPU *current_cpu)
{
  return GET_H_UNEXCENBIT ();
}

/* Set a value for h-unexcenbit.  */

void
epiphanybf_h_unexcenbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_UNEXCENBIT (newval);
}

/* Get the value of h-timer0bit0.  */

BI
epiphanybf_h_timer0bit0_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER0BIT0 ();
}

/* Set a value for h-timer0bit0.  */

void
epiphanybf_h_timer0bit0_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER0BIT0 (newval);
}

/* Get the value of h-timer0bit1.  */

BI
epiphanybf_h_timer0bit1_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER0BIT1 ();
}

/* Set a value for h-timer0bit1.  */

void
epiphanybf_h_timer0bit1_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER0BIT1 (newval);
}

/* Get the value of h-timer0bit2.  */

BI
epiphanybf_h_timer0bit2_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER0BIT2 ();
}

/* Set a value for h-timer0bit2.  */

void
epiphanybf_h_timer0bit2_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER0BIT2 (newval);
}

/* Get the value of h-timer0bit3.  */

BI
epiphanybf_h_timer0bit3_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER0BIT3 ();
}

/* Set a value for h-timer0bit3.  */

void
epiphanybf_h_timer0bit3_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER0BIT3 (newval);
}

/* Get the value of h-timer1bit0.  */

BI
epiphanybf_h_timer1bit0_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER1BIT0 ();
}

/* Set a value for h-timer1bit0.  */

void
epiphanybf_h_timer1bit0_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER1BIT0 (newval);
}

/* Get the value of h-timer1bit1.  */

BI
epiphanybf_h_timer1bit1_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER1BIT1 ();
}

/* Set a value for h-timer1bit1.  */

void
epiphanybf_h_timer1bit1_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER1BIT1 (newval);
}

/* Get the value of h-timer1bit2.  */

BI
epiphanybf_h_timer1bit2_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER1BIT2 ();
}

/* Set a value for h-timer1bit2.  */

void
epiphanybf_h_timer1bit2_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER1BIT2 (newval);
}

/* Get the value of h-timer1bit3.  */

BI
epiphanybf_h_timer1bit3_get (SIM_CPU *current_cpu)
{
  return GET_H_TIMER1BIT3 ();
}

/* Set a value for h-timer1bit3.  */

void
epiphanybf_h_timer1bit3_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_TIMER1BIT3 (newval);
}

/* Get the value of h-arithmetic-modebit0.  */

BI
epiphanybf_h_arithmetic_modebit0_get (SIM_CPU *current_cpu)
{
  return GET_H_ARITHMETIC_MODEBIT0 ();
}

/* Set a value for h-arithmetic-modebit0.  */

void
epiphanybf_h_arithmetic_modebit0_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_ARITHMETIC_MODEBIT0 (newval);
}

/* Get the value of h-arithmetic-modebit1.  */

BI
epiphanybf_h_arithmetic_modebit1_get (SIM_CPU *current_cpu)
{
  return GET_H_ARITHMETIC_MODEBIT1 ();
}

/* Set a value for h-arithmetic-modebit1.  */

void
epiphanybf_h_arithmetic_modebit1_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_ARITHMETIC_MODEBIT1 (newval);
}

/* Get the value of h-arithmetic-modebit2.  */

BI
epiphanybf_h_arithmetic_modebit2_get (SIM_CPU *current_cpu)
{
  return GET_H_ARITHMETIC_MODEBIT2 ();
}

/* Set a value for h-arithmetic-modebit2.  */

void
epiphanybf_h_arithmetic_modebit2_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_ARITHMETIC_MODEBIT2 (newval);
}

/* Get the value of h-clockgateenbit.  */

BI
epiphanybf_h_clockgateenbit_get (SIM_CPU *current_cpu)
{
  return GET_H_CLOCKGATEENBIT ();
}

/* Set a value for h-clockgateenbit.  */

void
epiphanybf_h_clockgateenbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_CLOCKGATEENBIT (newval);
}

/* Get the value of h-mbkptenbit.  */

BI
epiphanybf_h_mbkptenbit_get (SIM_CPU *current_cpu)
{
  return GET_H_MBKPTENBIT ();
}

/* Set a value for h-mbkptenbit.  */

void
epiphanybf_h_mbkptenbit_set (SIM_CPU *current_cpu, BI newval)
{
  SET_H_MBKPTENBIT (newval);
}

/* Get the value of h-coredma-registers.  */

USI
epiphanybf_h_coredma_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_COREDMA_REGISTERS (regno);
}

/* Set a value for h-coredma-registers.  */

void
epiphanybf_h_coredma_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  SET_H_COREDMA_REGISTERS (regno, newval);
}

/* Get the value of h-coremem-registers.  */

USI
epiphanybf_h_coremem_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_COREMEM_REGISTERS (regno);
}

/* Set a value for h-coremem-registers.  */

void
epiphanybf_h_coremem_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  SET_H_COREMEM_REGISTERS (regno, newval);
}

/* Get the value of h-coremesh-registers.  */

USI
epiphanybf_h_coremesh_registers_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_COREMESH_REGISTERS (regno);
}

/* Set a value for h-coremesh-registers.  */

void
epiphanybf_h_coremesh_registers_set (SIM_CPU *current_cpu, UINT regno, USI newval)
{
  SET_H_COREMESH_REGISTERS (regno, newval);
}

/* Record trace results for INSN.  */

void
epiphanybf_record_trace_results (SIM_CPU *current_cpu, CGEN_INSN *insn,
			    int *indices, TRACE_RECORD *tr)
{
}
