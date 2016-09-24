/* EPIPHANY target configuration file.  -*- C -*- */

#ifndef EPIPHANY_TCONFIG_H
#define EPIPHANY_TCONFIG_H

/* Define this if the simulator can vary the size of memory.
   See the xxx simulator for an example.
   This enables the `-m size' option.
   The memory size is stored in STATE_MEM_SIZE.  */
/* Not used for EPIPHANY since we use the memory module.  */
/* #define SIM_HAVE_MEM_SIZE */

/* See sim-hload.c.  We properly handle LMA.  */
#define SIM_HANDLES_LMA 1

/* For MSPR support.  FIXME: revisit.  */
#define WITH_DEVICES 0

#if 0
/* Enable watchpoints.  */
#define WITH_WATCHPOINTS 1
#endif

/* Define this to enable the intrinsic breakpoint mechanism. */
#define SIM_HAVE_BREAKPOINTS
#define SIM_BREAKPOINT { 0x42, 0x00 }
#define SIM_BREAKPOINT_SIZE 2

/* This is a global setting.  Different cpu families can't mix-n-match -scache
   and -pbb.  However some cpu families may use -simple while others use
   one of -scache/-pbb.  */
#define WITH_SCACHE_PBB 0   /* cache + pseudo basic block */

#endif /* EPIPHANY_TCONFIG_H */
