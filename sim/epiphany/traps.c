/* epiphany exception, interrupt, and trap (EIT) support
   based on m32r

   Copyright (C) 1998, 2003, 2007, 2008, 2011 Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva, Inc.

   This file is part of GDB, the GNU debugger.

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

#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "targ-vals.h"
#include "cgen-engine.h"
#include "cgen-par.h"
#include "sim-fpu.h"

#include "cgen-ops.h"
#include "cpu.h"

/* The semantic code invokes this for invalid (unrecognized) instructions.  */

SEM_PC
sim_engine_invalid_insn (SIM_CPU *current_cpu, IADDR cia, SEM_PC pc)
{
  SIM_DESC sd = CPU_STATE (current_cpu);

  fprintf(stderr, "----------- sim_engine_invalid_insn at pc 0x%p\n", pc);

  sim_engine_halt (sd, current_cpu, NULL, cia, sim_stopped, SIM_SIGILL);

  return pc;
}

/* Process an address exception.  */

void
epiphany_core_signal (SIM_DESC sd, SIM_CPU *current_cpu, sim_cia cia,
		      unsigned int map, int nr_bytes, address_word addr,
		      transfer_type transfer, sim_core_signals sig)
{
  sim_core_signal (sd, current_cpu, cia, map, nr_bytes, addr,
		   transfer, sig);
}

/* Read/write functions for system call interface.  */

static int
syscall_read_mem (host_callback *cb, struct cb_syscall *sc,
		  unsigned long taddr, char *buf, int bytes)
{
  SIM_DESC sd = (SIM_DESC) sc->p1;
  SIM_CPU *cpu = (SIM_CPU *) sc->p2;

  return sim_core_read_buffer (sd, cpu, read_map, buf, taddr, bytes);
}

static int
syscall_write_mem (host_callback *cb, struct cb_syscall *sc,
		   unsigned long taddr, const char *buf, int bytes)
{

  SIM_DESC sd = (SIM_DESC) sc->p1;
  SIM_CPU *cpu = (SIM_CPU *) sc->p2;

  return sim_core_write_buffer (sd, cpu, write_map, buf, taddr, bytes);
}


/*! @todo Rewrite this and interrupt_handler in oob_events */
USI epiphany_rti(SIM_CPU *current_cpu)
{
  USI ipend, ilat, iret, imask;
  int serviced, next;

  ipend = GET_H_ALL_REGISTERS(H_REG_SCR_IPEND);
  ilat  = GET_H_ALL_REGISTERS(H_REG_SCR_ILAT);
  iret  = GET_H_ALL_REGISTERS(H_REG_SCR_IRET);
  imask = GET_H_ALL_REGISTERS(H_REG_SCR_IMASK);

  serviced = ffs(ipend) - 1 ;

  /* Clear serviced interrupt */
  if (serviced > -1)
    ipend = ipend & (~(1 << serviced));
  SET_H_ALL_REGISTERS(H_REG_SCR_IPEND, ipend);

  /* Check if there are pending non-masked interrupts */
  /* @todo We should check IPEND??? Need to rewrite interrupt_handler() too */
  next = ffs(ilat & ~imask) - 1;
  if (next > -1)
    {
      /* Set cai, gidisable, and km-bit */
      OR_REG_ATOMIC(H_REG_SCR_STATUS, (( 1 << H_SCR_STATUS_CAIBIT)
				       |(1 << H_SCR_STATUS_GIDISABLEBIT)
				       |(1 << H_SCR_STATUS_KMBIT)));

      /* Set ipend */
      OR_REG_ATOMIC(H_REG_SCR_IPEND, (1 << next));

      /* Clear current interrupt from ILAT */
      AND_REG_ATOMIC(H_REG_SCR_ILAT, (~(1 << next)));

      return (next << 2);
    }
  else
    {
      SET_H_GIDISABLEBIT(0);
      SET_H_KMBIT(0);
      return iret;
    }
}

void
epiphany_fpu_error (CGEN_FPU* fpu, int status)
{
}
