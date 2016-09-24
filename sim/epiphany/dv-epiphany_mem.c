/*  This file is part of the program GDB, the GNU debugger.

    Copyright (C) 2014 Adapteva
    Contributed by Ola Jeppsson

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    */


#include "sim-main.h"
#include "hw-main.h"

#include "sim-types.h"

#if WITH_EMESH_SIM
#include "esim/esim.h"
#else
#error "I need WITH_EMESH_SIM. Enable with --enable-emesh-sim"
#endif

/* DEVICE


   epiphany_mem - epiphany memory virtual device


   DESCRIPTION


   Implements memory m
   @todo Make more fine-grained so e.g., local mem accesses don't have to go
   through this device.


   PROPERTIES

   none
   @todo
   Properties needed:
       coreid       - so we can calculate local memory address.
       mem_per_core - so we can experiment with different memory sizes.



   PORTS

   none
   @todo investigate which ports are needed

   */




/* Finish off the partially created hw device.  Attach our local
   callbacks.  Wire up our port names etc */

static hw_io_read_buffer_method epiphany_mem_io_read_buffer;
static hw_io_write_buffer_method epiphany_mem_io_write_buffer;
static hw_port_event_method epiphany_mem_port_event;

static const struct hw_port_descriptor epiphany_mem_ports[] = {
  { NULL, },
};


static void
epiphany_mem_finish (struct hw *me)
{
  HW_TRACE ((me, "epiphany_mem_finish"));
  set_hw_data (me, NULL);
  set_hw_io_read_buffer (me, epiphany_mem_io_read_buffer);
  set_hw_io_write_buffer (me, epiphany_mem_io_write_buffer);
  set_hw_ports (me, epiphany_mem_ports);
  set_hw_port_event (me, epiphany_mem_port_event);

  /* Map full address space (except core local memory) */
  /* Need to do two calls since address size param is target word size and
     full size cannot be expressed with one call */
  hw_attach_address (hw_parent (me), 0, 0, 0, 0x80000000, me);
  hw_attach_address (hw_parent (me), 0, 0, 0x80000000, 0x80000000, me);
}

static void
epiphany_mem_port_event (struct hw *me,
		     int my_port,
		     struct hw *source,
		     int source_port,
		     int level)
{
  struct epiphany_mem *controller = hw_data (me);
  hw_abort (me, "epiphany_mem_port_event: not implemented");
}

static void epiphany_mem_signal(struct hw *me, unsigned_word addr,
			   unsigned nr_bytes, char *transfer, int sigrc)
{
  SIM_CPU *current_cpu;
  sim_cia cia;
  address_word ip;

  current_cpu = hw_system_cpu(me);
  cia = current_cpu ? CPU_PC_GET (current_cpu) : NULL_CIA;
  ip = CIA_ADDR (cia);

  switch (sigrc)
    {
    case SIM_SIGSEGV:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte %s at unmapped address 0x%lx at 0x%lx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (unsigned long) addr, (unsigned long) ip);
      break;
    case SIM_SIGBUS:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte misaligned %s at unmapped address 0x%lx at "
		     "0x%lx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (unsigned long) addr, (unsigned long) ip);
      break;
    default:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte %s at address 0x%lx at 0x%lx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (unsigned long) addr, (unsigned long) ip);
      break;
    }

    hw_halt(me, sim_stopped, sigrc);
}

static unsigned
epiphany_mem_io_read_buffer (struct hw *me,
			 void *dest,
			 int space,
			 unsigned_word base,
			 unsigned nr_bytes)
{
  es_state *esim;

  esim = STATE_ESIM(hw_system(me));
  HW_TRACE ((me, "read 0x%08lx %d", (long) base, (int) nr_bytes));
  if (es_mem_load(esim, base, nr_bytes, (uint8_t *) dest) != ES_OK)
    {
      /** @todo What about SIGBUS (unaligned access) */
      epiphany_mem_signal(me, base, nr_bytes, "read", SIM_SIGSEGV);
      return 0;
    }
  else
    return nr_bytes;
}

static unsigned
epiphany_mem_io_write_buffer (struct hw *me,
			  const void *source,
			  int space,
			  unsigned_word base,
			  unsigned nr_bytes)
{
  es_state *esim;

  esim = STATE_ESIM(hw_system(me));
  HW_TRACE ((me, "write 0x%08lx %d", (long) base, (int) nr_bytes));
  if (es_mem_store(esim, base, nr_bytes, (uint8_t *) source) != ES_OK)
    {
      /** @todo What about SIGBUS (unaligned access) */
      epiphany_mem_signal(me, base, nr_bytes, "write", SIM_SIGSEGV);
      return 0;
    }
  else
    return nr_bytes;
}


const struct hw_descriptor dv_epiphany_mem_descriptor[] = {
  { "epiphany_mem", epiphany_mem_finish, },
  { NULL },
};

