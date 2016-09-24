/* Main header for the epiphany.  */

#ifndef SIM_MAIN_H
#define SIM_MAIN_H

#ifndef WITH_TARGET_FLOATING_POINT_BITSIZE
#define WITH_TARGET_FLOATING_POINT_BITSIZE 32
#endif

/* sim-basics.h includes config.h but cgen-types.h must be included before
   sim-basics.h and cgen-types.h needs config.h.  */
#include "config.h"

#include <stdint.h>

#include "symcat.h"
#include "sim-basics.h"
#include "cgen-types.h"
#include "epiphany-desc.h"
#include "epiphany-opc.h"
#include "arch.h"

#if WITH_EMESH_SIM
#include <pthread.h>
#include "esim/esim.h"
#endif

/* These must be defined before sim-base.h.  */
typedef USI sim_cia;

#define SIM_ENGINE_HALT_HOOK(sd, cpu, cia) \
do { \
  if (cpu) /* null if ctrl-c.  */ \
    sim_pc_set ((cpu), (cia)); \
} while (0)
#define SIM_ENGINE_RESTART_HOOK(sd, cpu, cia) \
do { \
  sim_pc_set ((cpu), (cia)); \
} while (0)

#include "sim-base.h"
#include "sim-fpu.h"
#include "cgen-sim.h"
#include "epiphany-sim.h"
#include "opcode/cgen.h"
#include "epiphany-fp.h"
/*#include "cpu.h"*/


/* Out of band events */
#include "oob-events.h"

#include "mem-barrier.h"

/* The _sim_cpu struct.  */

struct _sim_cpu {
  /* sim/common cpu base.  */
  sim_cpu_base base;

  sim_fpu_round round;          /* Current rounding mode of processor.  */
  /* Static parts of cgen.  */
  CGEN_CPU cgen_cpu;

#if WITH_EMESH_SIM
  /* Write (Set) lock for Special Core Registers. Since readers don't take the
  lock, updates must be done in one step for consistency. */
  /*!  @todo Most of this should be moved to esim */
  pthread_mutex_t scr_lock;
  pthread_cond_t scr_wakeup_cond;    /* When someone writes to a SCR */
  pthread_cond_t scr_writeslot_cond; /* When core acks SCR write (and write slot becomes free) */
  volatile int scr_remote_write_reg; /* Set to -1 by core when a write is acked */
  volatile uint32_t scr_remote_write_val;
#define CPU_SCR_WRITESLOT_LOCK() pthread_mutex_lock(&current_cpu->scr_lock)
#define CPU_SCR_WRITESLOT_RELEASE() pthread_mutex_unlock(&current_cpu->scr_lock)
#define CPU_WAKEUP_WAIT() \
  pthread_cond_wait(&current_cpu->scr_wakeup_cond, &current_cpu->scr_lock)
#define CPU_SCR_WAKEUP_SIGNAL() \
  pthread_cond_signal(&current_cpu->scr_wakeup_cond)
#define CPU_SCR_WRITESLOT_EMPTY() (current_cpu->scr_remote_write_reg == -1)
#define CPU_SCR_WRITESLOT_WAIT() \
  pthread_cond_wait(&current_cpu->scr_writeslot_cond, &current_cpu->scr_lock)
#define CPU_SCR_WRITESLOT_SIGNAL() \
  pthread_cond_signal(&current_cpu->scr_writeslot_cond)
#else
#define CPU_SCR_WRITESLOT_LOCK()
#define CPU_SCR_WRITESLOT_RELEASE()
#define CPU_SCR_WAKEUP_SIGNAL()
#define CPU_SCR_WAKEUP_WAIT()\
      sim_engine_halt (current_state, current_cpu, NULL, \
		       sim_pc_get(current_cpu), sim_stopped, SIM_SIGTRAP)
#define CPU_SCR_WRITESLOT_EMPTY() (1)
#define CPU_SCR_WRITESLOT_WAIT()
#define CPU_SCR_WRITESLOT_SIGNAL()
#endif

  oob_event_t oob_event; /* Out of band event (There can be only one) */

  volatile unsigned external_write; /* Write from other core (for scache) */

  EPIPHANY_MISC_PROFILE epiphany_misc_profile;
#define CPU_EPIPHANY_MISC_PROFILE(cpu) (& (cpu)->epiphany_misc_profile)

  /* CPU specific parts go here.
     Note that in files that don't need to access these pieces WANT_CPU_FOO
     won't be defined and thus these parts won't appear.  This is ok in the
     sense that things work.  It is a source of bugs though.
     One has to of course be careful to not take the size of this
     struct and no structure members accessed in non-cpu specific files can
     go after here.  Oh for a better language.  */
#if defined (WANT_CPU_EPIPHANYBF)
  EPIPHANYBF_CPU_DATA cpu_data;
#endif
};




/* The sim_state struct.  */

struct sim_state {
  sim_cpu *cpu[MAX_NR_PROCESSORS];

  CGEN_STATE cgen_state;

  sim_state_base base;

#if WITH_EMESH_SIM
  es_state *esim;
#define STATE_ESIM(sd) (sd->esim)
#endif
};

/* Misc.  */

/* Catch address exceptions.  */
extern SIM_CORE_SIGNAL_FN epiphany_core_signal;
#define SIM_CORE_SIGNAL(SD,CPU,CIA,MAP,NR_BYTES,ADDR,TRANSFER,ERROR) \
epiphany_core_signal ((SD), (CPU), (CIA), (MAP), (NR_BYTES), (ADDR), \
		  (TRANSFER), (ERROR))

/* Default memory size.  */
#define EPIPHANY_DEFAULT_MEM_SIZE 0x100000 /* 1M */

#define EPIPHANY_DEFAULT_EXT_MEM_BANK_SIZE    0x1000000
#define EPIPHANY_DEFAULT_EXT_MEM_BANK0_START 0x80000000
#define EPIPHANY_DEFAULT_EXT_MEM_BANK1_START 0x81000000

#endif /* SIM_MAIN_H */
