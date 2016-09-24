/* Target-dependent code for the Adapteva Epiphany architecture

   Copyright (C) 2011 Free Software Foundation, Inc.

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com> of behalf of
   Adapteva Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/*----------------------------------------------------------------------------*/
/* This GDB architecture specification for the Adapteva Epiphany was written by
   Jeremy Bennett on behalf of Adapteva Inc.

   Implementation follows the guidelines in the GNU Internals manual and
   Embecosm Application Note 3 "Howto: Porting the GNU Debugger: Practical
   Experience with the OpenRISC 1000 Architecture"
   (http://www.embecosm.com/download/ean3.html).

   Note that the Epiphany is a little endian architecture.

   Commenting is Doxygen compatible.                                          */
/*----------------------------------------------------------------------------*/


#include "defs.h"
#include "gdb_assert.h"
#include "frame.h"
#include "inferior.h"
#include "symtab.h"
#include "value.h"
#include "gdbcmd.h"
#include "language.h"
#include "gdbcore.h"
#include "symfile.h"
#include "objfiles.h"
#include "gdbtypes.h"
#include "target.h"
#include "regcache.h"
#include "remote.h"

#include "safe-ctype.h"
#include "block.h"
#include "reggroups.h"
#include "arch-utils.h"
#include "frame.h"
#include "frame-unwind.h"
#include "frame-base.h"
#include "dwarf2-frame.h"
#include "trad-frame.h"
#include "valprint.h"
#include "prologue-value.h"

#include "command.h"
#include "cli/cli-cmds.h"

#include "dis-asm.h"

#include <inttypes.h>

/* Offsets into the GPRs of various "special" registers */
#define EPIPHANY_GPR_FARG  0	/*!< Offset to first arg register */
#define EPIPHANY_GPR_LARG  3	/*!< Offset to last arg register */
#define EPIPHANY_GPR_FCS   4	/*!< Offset to first callee saved register */
#define EPIPHANY_GPR_LCS  10	/*!< Offset to last callee saved register */
#define EPIPHANY_GPR_SB    9	/*!< Offset to static base register */
#define EPIPHANY_GPR_SL   10	/*!< Offset to stack limit register */
#define EPIPHANY_GPR_IP   12	/*!< Offset to Inter-proc call scratch reg */
#define EPIPHANY_GPR_SP   13	/*!< Offset to stack pointer register */
#define EPIPHANY_GPR_LR   14	/*!< Offset to link register */
#define EPIPHANY_GPR_FP   15	/*!< Offset to frame pointer register */

/*! Number of general purpose registers (GPRs). */
#define EPIPHANY_NUM_GPRS         64

/* Offsets into SCRs (in GDB sequence) */
#define EPIPHANY_SCR_CONFIG       0 /*!< Offset to config register */
#define EPIPHANY_SCR_STATUS	  1 /*!< Offset to status register */
#define EPIPHANY_SCR_PC		  2 /*!< Offset to program counter register */
#define EPIPHANY_SCR_DEBUGSTATUS  3 /*!< Offset to debug register */
#define EPIPHANY_SCR_LC		  4 /*!< Offset to loop count register */
#define EPIPHANY_SCR_LS		  5 /*!< Offset to loop start register */
#define EPIPHANY_SCR_LE		  6 /*!< Offset to loop end register */
#define EPIPHANY_SCR_IRET	  7 /*!< Offset to interrupt return register */
#define EPIPHANY_SCR_IMASK	  8 /*!< Offset to interrupt mask register */
#define EPIPHANY_SCR_ILAT	  9 /*!< Offset to interrupt latch register */
#define EPIPHANY_SCR_ILATST	 10 /*!< Offset to interrupt set register */
#define EPIPHANY_SCR_ILATCL	 11 /*!< Offset to interrupt clear register */
#define EPIPHANY_SCR_IPEND	 12 /*!< Offset to interrupt status register */
#define EPIPHANY_SCR_FSTATUS	 13
#define EPIPHANY_SCR_DEBUGCMD	 14
#define EPIPHANY_SCR_RESETCORE	 15 /*!< Offset to core timer 0 register */
#define EPIPHANY_SCR_CTIMER0	 16 /*!< Offset to core timer 1 register */
#define EPIPHANY_SCR_CTIMER1	 17
#define EPIPHANY_SCR_MEMSTATUS	 18
#define EPIPHANY_SCR_MEMPROTECT	 19
#define EPIPHANY_SCR_DMA0CONFIG	 20
#define EPIPHANY_SCR_DMA0STRIDE	 21
#define EPIPHANY_SCR_DMA0COUNT	 22
#define EPIPHANY_SCR_DMA0SRCADDR 23
#define EPIPHANY_SCR_DMA0DSTADDR 24
#define EPIPHANY_SCR_DMA0AUTO0	 25
#define EPIPHANY_SCR_DMA0AUTO1	 26
#define EPIPHANY_SCR_DMA0STATUS	 27
#define EPIPHANY_SCR_DMA1CONFIG	 28
#define EPIPHANY_SCR_DMA1STRIDE	 29
#define EPIPHANY_SCR_DMA1COUNT	 30
#define EPIPHANY_SCR_DMA1SRCADDR 31
#define EPIPHANY_SCR_DMA1DSTADDR 32
#define EPIPHANY_SCR_DMA1AUTO0   33
#define EPIPHANY_SCR_DMA1AUTO1   34
#define EPIPHANY_SCR_DMA1STATUS  35
#define EPIPHANY_SCR_MESHCONFIG  36
#define EPIPHANY_SCR_COREID      37
#define EPIPHANY_SCR_MULTICAST   38
#define EPIPHANY_SCR_CMESHROUTE  39
#define EPIPHANY_SCR_XMESHROUTE  40
#define EPIPHANY_SCR_RMESHROUTE  41

/*! @todo What about the MEMPROTECT, COREID and SWRESET registers? */

/*! Number of Special Core Registers (SCRs). */
#define EPIPHANY_NUM_SCRS         (EPIPHANY_SCR_RMESHROUTE + 1)

/*! Number of raw registers used. */
#define EPIPHANY_NUM_REGS         (EPIPHANY_NUM_GPRS + EPIPHANY_NUM_SCRS)

/*! Total number of pseudo registers (none in this implementation). */
#define EPIPHANY_NUM_PSEUDO_REGS   0

/*! Total of registers used. */
#define EPIPHANY_TOTAL_NUM_REGS   (EPIPHANY_NUM_REGS + EPIPHANY_NUM_PSEUDO_REGS)

/*! GDB register number for the first arg register. */
#define EPIPHANY_FIRST_ARG_REGNUM (EPIPHANY_GPR_FARG)

/*! GDB register number for the first arg register. */
#define EPIPHANY_LAST_ARG_REGNUM  (EPIPHANY_GPR_LARG)

/*! GDB register number for a single word result or first word of multi-word
    result. */
#define EPIPHANY_RV_REGNUM        (EPIPHANY_FIRST_ARG_REGNUM)

/*! GDB register number for the stack pointer */
#define EPIPHANY_SP_REGNUM        (EPIPHANY_GPR_SP)

/*! GDB register number for the frame pointer */
#define EPIPHANY_FP_REGNUM        (EPIPHANY_GPR_FP)

/*! GDB register number for the link register */
#define EPIPHANY_LR_REGNUM        (EPIPHANY_GPR_LR)

/*! GDB register number for the first callee saved register */
#define EPIPHANY_FCS_REGNUM       (EPIPHANY_GPR_FCS)

/*! GDB register number for the last callee saved register */
#define EPIPHANY_LCS_REGNUM       (EPIPHANY_GPR_LCS)

/*! GDB register number for the static base register */
#define EPIPHANY_SB_REGNUM        (EPIPHANY_GPR_SB)

/*! GDB register number for the stack limit register */
#define EPIPHANY_SL_REGNUM        (EPIPHANY_GPR_SL)

/*! GDB register number for the status register */
#define EPIPHANY_SR_REGNUM        (EPIPHANY_NUM_GPRS + EPIPHANY_SCR_STATUS)

/*! GDB register number for the program counter */
#define EPIPHANY_PC_REGNUM        (EPIPHANY_NUM_GPRS + EPIPHANY_SCR_PC)

/*! GDB register number for the interrupt return register */
#define EPIPHANY_IRET_REGNUM      (EPIPHANY_NUM_GPRS + EPIPHANY_SCR_IRET)

/*! GDB register number for the interrupt latch register */
#define EPIPHANY_ILAT_REGNUM      (EPIPHANY_NUM_GPRS + EPIPHANY_SCR_ILAT)

/*! GDB register number for the interrupt pending status register */
#define EPIPHANY_IPEND_REGNUM      (EPIPHANY_NUM_GPRS + EPIPHANY_SCR_IPEND)

/*! Red Zone size

    This is the area beyond the end of the stack frame which may be used by
    exception handlers. The Epiphany does not use this concept, so the value is
    zero.                                                                   */
#define EPIPHANY_FRAME_RED_ZONE_SIZE  0

/*! Stack alignment

    This is for the stack pointer. The stack base and limit must be double
    word aligned.                                                            */
#define EPIPHANY_STACK_ALIGN  8

/* Argument handling. */
#define  PARM_BOUNDARY_BITS             32
#define  PARM_BOUNDARY_BYTES           (PARM_BOUNDARY_BITS / 8)
#define  MAX_AGGREGATE_BY_VALUE_BITS    64
#define  MAX_AGGREGATE_BY_VALUE_BYTES  (MAX_AGGREGATE_BY_VALUE_BITS / 8)

/*! The number of bytes of stack offset.
  @todo This really ought to be configurable, as it is in GCC. */
#define EPIPHANY_STACK_OFFSET  8

/*! BKPT instruction as a byte array.

    @note  Real hardware apparently needs the opposite endianness. This is
           almost certainly a bug in the remote serial protocol server. */
#define EPIPHANY_BKPT_INST_STRUCT      {0xc2, 0x01}

/*! Numeric value of frame pointer setup instruction (mov  fp,sp) */
#define EPIPHANY_MOV_FP_SP_INST  0x2402f4ef

/*! Size of the breakpoint instruction (in bytes) */
#define EPIPHANY_BKPT_INSTLEN  2

/*! Number of bytes in an Epiphany word */
#define EPIPHANY_BYTES_PER_WORD  4

/*! Epiphany size field values */
#define EPIPHANY_SIZE_BYTE  0
#define EPIPHANY_SIZE_HALF  1
#define EPIPHANY_SIZE_WORD  2

/*! Maximum instruction size */
#define EPIPHANY_MAX_INST_SIZE  EPIPHANY_SIZE_WORD

/*! Condition bits we care about in instructions */
#define UNCOND_BITS 0xe;

/*! Maximum number of cores */
#define MAX_CORES  4096

/* Macros for instruction analysis. Sign extension is from the Aggregate
   Magic algorithms (aggregate.org/MAGIC) by Joe Zbiciak. */
#define SUBMASK(x) ((1L << ((x) + 1)) - 1)
#define BIT(obj,st) (((obj) >> (st)) & 1)
#define BITS(obj,fn,st) (((obj) >> (st)) & SUBMASK ((fn) - (st)))
#define SEXTEND8(v) (((v) ^ (long int) 0x80) - (long int) 0x80)
#define SEXTEND16(v) (((v) ^ (long int) 0x8000) - (long int) 0x8000)
#define SEXTEND24(v) (((v) ^ (long int) 0x800000) - (long int) 0x800000)

/*! The type of instruction we might find when setting single step
    breakpoints. */
enum epiphany_ss_type {
  UNCOND_BRANCH,
  COND_BRANCH,
  JUMP,
  OTHER
};


/* External debug flags */
extern unsigned int frame_debug;		/*!< frame debugging flag */
extern unsigned int debug_infrun;		/*!< infrun debugging flag */


/*============================================================================*/
/* Support functions for the architecture definition                          */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*!Conditionally print out an Epiphany frame debug message.

   A convenience function to avoid bucket loads of conditionals.

   @param[in] fmt  The formatting string.
   @param[in] ...  The args (if any).                                         */
/*----------------------------------------------------------------------------*/
static void
epiphany_frame_debug (const char *fmt,
		      ...)
{
  if (frame_debug)
    {
      va_list  args;

      fprintf_unfiltered (gdb_stdlog, "frame-epiphany: ");
      va_start (args, fmt);
      vfprintf_unfiltered (gdb_stdlog, fmt, args);
      va_end (args);
    }
}	/* epiphany_frame_debug */


/*----------------------------------------------------------------------------*/
/*!Conditionally print out an Epiphany infrun debug message.

   A convenience function to avoid bucket loads of conditionals.

   @param[in] fmt  The formatting string.
   @param[in] ...  The args (if any).                                         */
/*----------------------------------------------------------------------------*/
static void
epiphany_debug_infrun (const char *fmt,
		      ...)
{
  if (debug_infrun)
    {
      va_list  args;

      fprintf_unfiltered (gdb_stdlog, "infrun-epiphany: ");
      va_start (args, fmt);
      vfprintf_unfiltered (gdb_stdlog, fmt, args);
      va_end (args);
    }
}	/* epiphany_debug_infrun () */


/*----------------------------------------------------------------------------*/
/*!Analyse the prologue

   Populate a cache with information about where registers in the PREVIOUS
   frame may be found from THIS frame.

   PROLOGUE STRUCTURE
   ==================

   Compiler optimization means there is considerable variation in how the
   prologue may look. As a heurstic we can treat any operation that stores
   the sp, lr, fp or callee saved registers (r4-r10) onto the stack or that
   moves a value into the frame pointer as being in the prologue. We deem any
   branch instruction as certainly marking the end of the prologue.

   Examples include

        str  rD,[sp],#-<stack_size>
        str  rD,[fp],#-<stack_size>
	add  sp,sp,#-<stack_size>
        mov  fp,sp
        strb rD,[sp,#<offset>]
        strb rD,[fp,#<offset>]
        strh rD,[sp,#<offset>]
        strh rD,[fp,#<offset>]
        str  rD,[sp,#<offset>]
        str  rD,[fp,#<offset>]
        strd rD,[sp,#<offset>]
        strd rD,[fp,#<offset>]

   The ordering of these instructions may vary and the locations for saving
   on the stack are not fixed. When optimizing, non-prologue instructions may
   be interspersed in the prologue.

   Note however, that since either the FP (r15) or SP (r13) is involved,
   these are always 32-bit instructions.

   ANALYSIS
   ========

   The approach is outlined in the GDB Internals Manual (see the section
   "Prologue Analysis" in the "Algorithms" chapter). The data-structures used
   are described in prologue-value.h

   We interpret instructions conservatively (i.e. if its too complex we just
   mark a value as "unknown"). we stop when we get to the end of the prologue
   (as determined by epiphany_skip_prologue) or when we meet an instruction
   that we do not recognize as potentially being part of the prologue (listed
   above). This does mean that we may fail on optimized code, but debugging
   optimized code without debug information is always difficult.

   We use the analysis to populate the prologue cache as best we may.

   We use a traditional frame cache to hold the information. If we do not
   have end of the prologue explicitly available, we assume it ends at the
   first instruction we find that cannot be in the prologue (in optimized
   code, this may be too cautious).

   We silently accept duplicate saving of callee saved registers to the
   stack. The final store will be the one that is used.

   All this analysis must allow for the possibility that the PC is in the
   middle of the prologue. Data should only be set up insofar as it has been
   computed.

   @param[in]  this_frame      The frame to analyse.
   @param[in]  prologue_start  Start of the prologue.
   @param[in]  prologue_end    Conservative estimate of the end of the
                               prologue.
   @param[out] cache           The prologue cache to populate.                */
/*----------------------------------------------------------------------------*/
static void
epiphany_analyse_prologue (struct frame_info       *this_frame,
			   CORE_ADDR                prologue_start,
			   CORE_ADDR                prologue_end,
			   struct trad_frame_cache *cache)
{
  struct gdbarch  *gdbarch             = get_frame_arch (this_frame);
  enum bfd_endian  byte_order          = gdbarch_byte_order (gdbarch);
  enum bfd_endian  byte_order_for_code = gdbarch_byte_order_for_code (gdbarch);
  unsigned int     bpw                 = EPIPHANY_BYTES_PER_WORD;

  int        regnum;
  CORE_ADDR  current_pc;
  CORE_ADDR  this_sp;
  int        framesize;

  pv_t            regs[EPIPHANY_NUM_REGS];
  struct pv_area *stack;
  struct cleanup *stack_cleanup;

  epiphany_frame_debug ("epiphany_analyse_prologue called\n");

  /* Initialize the register and stack records. */
  for (regnum = 0; regnum < EPIPHANY_NUM_GPRS; regnum++)
    {
      regs[regnum] = pv_register (regnum, 0);
    }

  stack         = make_pv_area (EPIPHANY_SP_REGNUM, gdbarch_addr_bit (gdbarch));
  stack_cleanup = make_cleanup_free_pv_area (stack);

  /* On entry, the value in the previous program counter is now found in the
     link register. */
  regs[EPIPHANY_PC_REGNUM] = regs[EPIPHANY_LR_REGNUM];

  /* Work through the prologue looking for instructions that set up the FP,
     adjust the SP and save callee-saved registers. */
  for (current_pc = prologue_start; current_pc < prologue_end;)
    {
      unsigned long int insn =
	read_memory_unsigned_integer (current_pc, 2, byte_order_for_code);
      unsigned int opc = BITS (insn, 3, 0);

      /* 16-bit instructions cannot be in the prologue. */
      if (   ( 0 == opc) || ( 1 == opc) || ( 2 == opc) || ( 3 == opc)
	  || ( 4 == opc) || ( 5 == opc) || ( 6 == opc) || ( 7 == opc)
	  || (10 == opc) || (14 == opc))
	{
	  epiphany_frame_debug ("PC %p: insn 0x%04x: 16-bit insn",
				(void *) current_pc, insn);
	  epiphany_frame_debug (" ** prologue ends **\n");
	  break;		/* End of prologue */
	}

      /* Get 32-bit instruction. */
      insn = read_memory_unsigned_integer (current_pc, 4, byte_order_for_code);

      if (   ((insn & 0xff00fc7f) == 0x2400b41b)
	  || ((insn & 0xff00fc7f) == 0x2400bc1b)
	  || ((insn & 0xff00fc7f) == 0x2400f41b)
	  || ((insn & 0xff00fc7f) == 0x2400fc1b))
	{
	  /*                    dddn nn             dddn nn
	     add sp,sp,#<simm>  0010 0100 ssss ssss 1011 01ss s001 1011.
	     add sp,fp,#<simm>  0010 0100 ssss ssss 1011 11ss s001 1011.
	     add fp,sp,#<simm>  0010 0100 ssss ssss 1111 01ss s001 1011.
	     add fp,fp,#<simm>  0010 0100 ssss ssss 1111 11ss s001 1011.

	     The constant should be a negative multiple of words (falling
	     stack). */
	  int simm = SEXTEND16 ((BITS (insn, 23, 16) << 3) | BITS (insn, 9, 7));
	  int rd = BITS (insn, 31, 29) << 3 | BITS (insn, 15, 13);
	  int rn = BITS (insn, 28, 26) << 3 | BITS (insn, 12, 10);

	  if (0 != (simm % bpw) || (simm >= 0))
	    {
	      epiphany_frame_debug (
		"PC %p: insn 0x%08x: add r%d,r%d,#%d ** prologue ends\n",
		(void *) current_pc, insn, rd, rn, simm);

	      /* Not word sized and negative, end of prologue */
	      break;
	    }
	  else
	    {
	      epiphany_frame_debug ("PC %p: insn 0x%08x: add r%d,r%d,#%d\n",
				    (void *) current_pc, insn, rd, rn, simm);
	      regs[rd] = pv_add_constant (regs[rn], (CORE_ADDR) simm);
	    }
	}
      else if ((insn & 0xffffffff) == 0x2402bcef)
	{
	  /* mov sp,fp. 0010 0100 0000 0010 1011 1100 1110 1111. */
	  epiphany_frame_debug ("PC %p: insn 0x%08x: mov sp,fp\n",
				(void *) current_pc, insn);

	  regs[EPIPHANY_SP_REGNUM] = regs[EPIPHANY_FP_REGNUM];
	}
      else if ((insn & 0xffffffff) == 0x2402f4ef)
	{
	  /* mov fp,sp. 0010 0100 0000 0010 1111 0100 1110 1111. */
	  epiphany_frame_debug ("PC %p: insn 0x%08x: mov fp,sp\n",
				(void *) current_pc, insn);

	  regs[EPIPHANY_FP_REGNUM] = regs[EPIPHANY_SP_REGNUM];
	}
      else if (   ((insn & 0x1e001c1f) == 0x0400141c)
	       || ((insn & 0x1e001c1f) == 0x04001c1c))
	{
	  /*                            dddn nn             dddn nn
	     str<sz> rD,[sp,#+/-<imm>]. ddd0 010+ iiii iiii ddd1 01ii izz1 1100
	     str<sz> rD,[fp,#+/-<imm>]. ddd0 010+ iiii iiii ddd1 11ii izz1 1100

	     Displacement addressing. Potentially this trashes the stack, in
	     which case we give up here. */
	  int  rd;
	  int  rn = BITS (insn, 28, 26) << 3 | BITS (insn, 12, 10);
	  int  sz;
	  int  imm;

	  if (pv_area_store_would_trash (stack, regs[rn]))
	    {
	      epiphany_frame_debug (
		"PC %p: insn 0x%08x: str<sz> rD,[r%d,#+/-<imm>] ** prologue ends **\n",
		(void *) current_pc, insn, rn);
	      break;		/* Jump out of the main loop */
	    }

	  rd  = (BITS (insn, 31, 29) << 3) | BITS (insn, 15, 13);
	  sz  =  BITS (insn, 6, 5);
	  imm = (BITS (insn, 23, 16) << 3) | BITS (insn, 9,7);
	  imm = (1 == BIT (insn, 24)) ? -imm : imm;

	  switch (sz)
	    {
	    case 0:
	      /* Byte sized store */
	      pv_area_store (stack, pv_add_constant (regs[rn], imm), 1,
			     regs[rd]);
	      epiphany_frame_debug ("PC %p: insn 0x%08x: strb r%d,[r%d,#%d]\n",
				    (void *) current_pc, insn, rd, rn, imm);
	      break;

	    case 1:
	      /* Half word sized store */
	      pv_area_store (stack, pv_add_constant (regs[rn], imm * 2), 2,
			     regs[rd]);
	      epiphany_frame_debug ("PC %p: insn 0x%08x: strh r%d,[r%d,#%d]\n",
				    (void *) current_pc, insn, rd, rn, imm);
	      break;

	    case 2:
	      /* Word sized store */
	      pv_area_store (stack, pv_add_constant (regs[rn], imm * 4), 4,
			     regs[rd]);
	      epiphany_frame_debug ("PC %p: insn 0x%08x: str r%d,[r%d,#%d]\n",
				    (void *) current_pc, insn, rd, rn, imm);
	      break;

	    case 3:
	      /* Double word sized store */
	      pv_area_store (stack, pv_add_constant (regs[rn], imm * 8), 4,
			     regs[rd]);
	      pv_area_store (stack, pv_add_constant (regs[rn], imm * 8 + 4), 4,
			     regs[rd + 1]);
	      epiphany_frame_debug ("PC %p: insn 0x%08x: strd r%d,[r%d,#%d]\n",
				    (void *) current_pc, insn, rd, rn, imm);

	      break;
	    }
	}
      else if (   ((insn & 0x1e001c7f) == 0x0600145c)
	       || ((insn & 0x1e001c7f) == 0x06001c5c))
	{
	  /*                        dddn nn             dddn nn
	     str rD,[sp],#+/-<imm>. ddd0 011+ iiii iiii ddd1 01ii i101 1100
	     str rD,[fp],#+/-<imm>. ddd0 011+ iiii iiii ddd1 11ii i101 1100

	     Displacement-postmodify. Potentially this trashes, the stack, in
	     which case we stop here. */

	  int  rd;
	  int  rn = BITS (insn, 28, 26) << 3 | BITS (insn, 12, 10);
	  int  imm;

	  if (pv_area_store_would_trash (stack, regs[rn]))
	    {
	      epiphany_frame_debug (
	        "PC %p: insn 0x%08x: str rD,[r%d,#+/-<imm>] ** prologue ends **\n",
		(void *) current_pc, insn, rn);
	      break;		/* Jump out of the main loop */
	    }

	  rd  = (BITS (insn, 31, 29) << 3) | BITS (insn, 15, 13);
	  imm = (BITS (insn, 23, 16) << 3) | BITS (insn, 9,7);
	  imm = (1 == BIT (insn, 24)) ? -imm : imm;

	  /* Word sized store */
	  pv_area_store (stack, pv_add_constant (regs[rn], imm * 4), 4,
			 regs[rd]);
	  regs[rn] = pv_add_constant (regs[rn], imm * 4);
	  epiphany_frame_debug ("PC %p: insn 0x%08x: str r%d,[r%d],#%d\n",
				(void *) current_pc, insn, rd, rn, imm);
	}
      else
	{
	  /* Any other instruction ends the prologue */
	  epiphany_frame_debug ("PC %p: insn 0x%08x: ** prologue ends **\n",
				(void *) current_pc, insn);
	  break;		/* Jump out of the main loop */
	}

      /* Advance the instruction pointer */
      current_pc += 4;
    }

  /* Frame size is the amount by which the SP has been advanced from its
     original value. */
  if (pv_is_register (regs[EPIPHANY_SP_REGNUM], EPIPHANY_SP_REGNUM))
    {
      framesize = -regs[EPIPHANY_SP_REGNUM].k;
    }
  else
    {
      framesize = 0;			/* Not set, or don;t know. */
    }

  epiphany_frame_debug ("framesize %d\n", framesize);

  /* Set up the frame ID and cache. Possibly we have a null frame, in which
     case we cannot set up a frame ID. */
  if (NULL != this_frame)
    {
      /* Frame cache is based on the SP *at entry*, which will be the SP minus
	 the framesize. */
      this_sp = get_frame_register_unsigned (this_frame, EPIPHANY_SP_REGNUM);
      epiphany_frame_debug ("stack pointer %p\n", (void *) this_sp);

      trad_frame_set_id (cache, frame_id_build (this_sp + framesize,
						prologue_start));
      epiphany_frame_debug ("frame_id (%p, %p)\n",
			    (void *) (this_sp + framesize), prologue_start);

      /* Populate the cache register data. Only meaningful if we have a
	 frame. */
      for (regnum = 0; regnum < EPIPHANY_NUM_GPRS; regnum++)
	{
	  CORE_ADDR  offset;

	  if (pv_area_find_reg (stack, gdbarch, regnum, &offset))
	    {
	      trad_frame_set_reg_addr (cache, regnum, offset);
	      epiphany_frame_debug ("r%d offset %d\n", regnum,
				    offset + this_sp);
	    }
	}
    }
  do_cleanups (stack_cleanup);

}	/* epiphany_analyse_prologue () */


/*----------------------------------------------------------------------------*/
/*!Scan the prologue to find the start and end

   There is huge variation in the Epiphany prologue, because of the potential
   for non-prologue instructions to be scheduled into the prologue.

   The SAL information for Epiphany can give ridiculous results. So instead we
   find the start and end of the whole function and let
   epiphany_analyse_prologue () get a more refined view.

   @param[in]  this_frame               The frame to analyse.
   @param[out] prologue_start_addr_ptr  The start addr of the prologue.
   @param[out] prologue_end_addr_ptr    The addr of the instruction
                                        immediately after the prologue.      */
/*----------------------------------------------------------------------------*/
static void
epiphany_scan_prologue (struct frame_info *this_frame,
			CORE_ADDR         *prologue_start_ptr,
			CORE_ADDR         *prologue_end_ptr)
{
  CORE_ADDR block_addr = get_frame_address_in_block (this_frame);

  /* If we have symtab and line data we have this in our hand. */
  if (find_pc_partial_function (block_addr, NULL, prologue_start_ptr,
				prologue_end_ptr))
    {
      /* Try to find the end using SAL. If not, then the function end address
	 will have to do. */
      struct gdbarch *gdbarch = get_frame_arch (this_frame);
      CORE_ADDR       new_end = skip_prologue_using_sal (gdbarch,
							 *prologue_start_ptr);
      if (new_end != 0)
	{
	  *prologue_end_ptr = new_end;
	}
    }
  else
    {
      /* Can't find the function. Give up. No point in using block_addr - not
	 likely to be in the prologue. */
      *prologue_start_ptr = 0;
      *prologue_end_ptr   = 0;
    }
}	/* epiphany_scan_prologue () */


/*----------------------------------------------------------------------------*/
/*!Can an aggregate argument be passed by value?

  The criteria for passing an aggregate argument by value are complex.
  - It must be no larger than MAX_AGGREGATE_BY_VALUE_BYTES
  - it must be of an integral type size
  - it's alignment must not be less than its size (can happen if packed for
  example)
  - it must not have a constructor

  @note At present some of these tests are beyond GDB. We may need additional
        DWARF2 information to resolve this. We pass plenty of information in
        case it helps (if it is available). For now we just look at the first
        two criteria, and only pass by value if its size is byte, word or
        double word.

  @todo More complete information on alignment and constructors is needed.

  @param[in] gdbarch   The architecture to use.
  @param[in] function  Pointer to the function that will be called (if
  available, else NULL).
  @param[in] argnum    The argument number (if available, else -1).
  @param[in] args      The argument list (if available, else NULL).
  @param[in] len       The length of the argument.

  @return  Non-zero if the argument can be passed by value, zero otherwise.   */
/*----------------------------------------------------------------------------*/
static int
epiphany_aggregate_by_value_p (struct gdbarch  *gdbarch,
			       struct value    *function,
			       int              argnum,
			       struct value   **args,
			       int              len)
{
  const int INTEGRAL_SIZES[] = {1, 4, 8, 0};

  if (len > MAX_AGGREGATE_BY_VALUE_BYTES)
    {
      return  0;		/* Can't pass by value */
    }
  else
    {
      int  i = 0;

      for (i = 0; 0 != INTEGRAL_SIZES[i]; i++)
	{
	  if (INTEGRAL_SIZES[i] == len)
	    {
	      return  1;	/* Can pass by value */
	    }
	}

      return  0;		/* Can't pass by value */
    }
}	/* epiphany_aggregate_by_value_p () */


/*----------------------------------------------------------------------------*/
/*!Work out the size of a parameter on the stack.

  Parameters occupy an integral mutliple of PARM_BOUNDARY_BYTES bytes on the
  stack.

  @param[in] len  The length of the argument.

  @return  The number of bytes the argument uses on the stack.               */
/*----------------------------------------------------------------------------*/
static int
epiphany_parm_size (int  len)
{
  return  (len + PARM_BOUNDARY_BYTES - 1) / PARM_BOUNDARY_BYTES
    * PARM_BOUNDARY_BYTES;

}	/* epiphany_parm_size () */


/*----------------------------------------------------------------------------*/
/*! Test if we have a 32-bit instruction in our hand.

    @param[in] instr  The instruction to test
    @return  Non-zero (TRUE) if this is a 32-bit instruction, zero (FALSE)
             otherwise.                                                       */
/*----------------------------------------------------------------------------*/
static int
epiphany_is_instr32 (uint32_t instr)
{
  return (BITS (instr, 3, 0) == 0xf)	/* Extended instr */
    || (BITS (instr, 3, 0) == 0xd)	/* Load/store */
    || (BITS (instr, 3, 0) == 0xc)	/* Load/store */
    || (BITS (instr, 3, 0) == 0x9)	/* Load/store */
    || (BITS (instr, 3, 0) == 0xb)	/* Immediate/register */
    || (BITS (instr, 3, 0) == 0x8);	/* Branch */

}	/* epiphany_is_instr32 () */


/*----------------------------------------------------------------------------*/
/*! Test if we have a branch in our hand

    @param[in] instr    The instruction to test
    @param[in] is32bit  Non-zero (TRUE) if this is a 32-bit instruction, zero
                        (FALSE) otherwise. Currently unused

    @return  Non-zero (TRUE) if this is a branch instruction, zero (FALSE)
             otherwise.                                                       */
/*----------------------------------------------------------------------------*/
static int
epiphany_is_branch (uint32_t  instr,
		    int       is32bit __attribute__ ((unused)) )
{
  return BITS (instr, 2, 0) == 0;

}	/* epiphany_is_branch () */


/*----------------------------------------------------------------------------*/
/*! Test if we have a jump in our hand

    @param[in] instr     The instruction to test
    @param[in] is32bit  Non-zero (TRUE) if this is a 32-bit instruction, zero
                        (FALSE) otherwise.

    @return TRUE if this is a 32-bit instruction, FALSE otherwise.            */
/*----------------------------------------------------------------------------*/
static int
epiphany_is_jump (uint32_t instr,
		  int       is32bit)
{
  if (is32bit)
    {
      return (BITS (instr, 19, 16) == 0x2)
	&& (BITS (instr, 9, 5) == 0xa)
	&& (BITS (instr, 3, 0) == 0xf);
    }
  else
    {
      return (BITS (instr, 9, 5) == 0xa)
	&& (BITS (instr, 3, 0) == 0x2);
    }
}	/* epiphany_is_jump () */


/*----------------------------------------------------------------------------*/
/*! Test if a branch is unconditional

    @param[in] br_instr  The branch instruction to test. NOTE we do not check
                         it really is a branch instruction.
    @param[in] is32bit   Non-zero (TRUE) if this is a 32-bit instruction, zero
                         (FALSE) otherwise. Currently unused

    @return  Non-zero (TRUE) if this is an unconditional branch instruction,
             zero (FALSE) otherwise.                                          */
/*----------------------------------------------------------------------------*/
static int
epiphany_is_uncond_branch (uint32_t  br_instr,
			   int       is32bit __attribute__ ((unused)) )
{
  return BITS (br_instr, 7, 4) == UNCOND_BITS;

}	/* epiphany_is_uncond_branch () */


/*----------------------------------------------------------------------------*/
/*! Get a branch offset in bytes

    Remember the offset in the instruction is a half-word offset and must be
    sign extended.

    @param[in] br_instr  The branch instruction to extract the offset
                         from. @note we do not check it really is a branch
                         instruction.
    @param[in] is32bit   Non-zero (TRUE) if this is a 32-bit instruction, zero
                         (FALSE) otherwise.

    @return  The byte offset                                                  */
/*----------------------------------------------------------------------------*/
static long int
epiphany_branch_offset (uint32_t  br_instr,
			int       is32bit)
{
  if (is32bit)
    return SEXTEND24 (BITS (br_instr, 31, 8)) << 1;
  else
    return SEXTEND8 (BITS (br_instr, 15, 8)) << 1;

}	/* epiphany_branch_offset () */


/*----------------------------------------------------------------------------*/
/*! Get a jump destination register

    For these instructions, the address is in a register, which we must
    extract.

    @param[in] jr_instr  The jump instruction to extract the offset
                         from. NOTE we do not check it really is a jump
                         instruction.
    @param[in] is32bit   Non-zero (TRUE) if this is a 32-bit instruction, zero
                         (FALSE) otherwise.

    @return  The register number                                              */
/*----------------------------------------------------------------------------*/
static unsigned int
epiphany_jump_register (uint32_t  jr_instr,
			int       is32bit)
{
  if (is32bit)
    return (BITS (jr_instr, 28, 26) << 3) | BITS (jr_instr, 12, 10);
  else
    return BITS (jr_instr, 12, 10);

}	/* epiphany_jump_register () */


/*----------------------------------------------------------------------------*/
/*! Determine the type of instruction at the PC for single stepping

    @param[in] instr  The instruction to analyse
    @param[in] is32bit   Non-zero (TRUE) if this is a 32-bit instruction, zero
                        (FALSE) otherwise.

    @return  The type of instruction we have                                  */
/*----------------------------------------------------------------------------*/
static enum epiphany_ss_type
epiphany_ss_instr_type (uint32_t  instr,
			int       is32bit)
{
  if (epiphany_is_branch (instr, is32bit))
    {
      int is_uncond = epiphany_is_uncond_branch (instr, is32bit);
      return  is_uncond  ? UNCOND_BRANCH : COND_BRANCH;
    }
  else if (epiphany_is_jump (instr, is32bit))
    return JUMP;
  else
    return OTHER;

}	/* epiphany_ss_instr_type () */


/*============================================================================*/
/* Functions defining the architecture                                        */
/*============================================================================*/


/*----------------------------------------------------------------------------*/
/*! Determine the virtual frame pointer.

  GDB is a bit ambivalent about what a frame pointer is, and quite often we
  generate code without one.

  We just use the SP with an offset of zero.

  @todo Should we use SP with an offset of the frame size? Or the actual FP
  if we know it is being used?

  @param[in]  gdbarch           The GDB architecture being used.
  @param[in]  pc                The current PC.
  @param[out] frame_regnum_ptr  Register number to use for the virtual FP.
  @param[out] frame_offset_ptr  Offset to use for the virtual FP.          */
/*----------------------------------------------------------------------------*/
static void
epiphany_virtual_frame_pointer (struct gdbarch *gdbarch,
				CORE_ADDR       pc,
				int            *frame_regnum_ptr,
				LONGEST        *frame_offset_ptr)
{
  *frame_regnum_ptr = EPIPHANY_SP_REGNUM;
  *frame_offset_ptr = 0;

}	/* epiphany_virtual_frame_pointer () */


/*----------------------------------------------------------------------------*/
/*! Read a pseudo register

  Since we have no pseudo registers this is a null function for now.

  @todo The floating point registers could be done as pseudo-registers.

  @param[in]  gdbarch   The GDB architecture to consider
  @param[in]  regcache  The cached register values as an array
  @param[in]  regnum    The register to read
  @param[out] buf       A buffer to put the result in

  @return  Status of the register read. We always return REG_UNAVAILABLE
  (since we should never be called).                              */
/*----------------------------------------------------------------------------*/
static enum register_status
epiphany_pseudo_register_read (struct gdbarch  *gdbarch,
			       struct regcache *regcache,
			       int              regnum,
			       gdb_byte        *buf)
{
  return  REG_UNAVAILABLE;

}	/* epiphany_pseudo_register_read() */


/*----------------------------------------------------------------------------*/
/*! Write a pseudo register

  Since we have no pseudo registers this is a null function for now.

  @todo The floating point registers could be done as pseudo-registers.

  @param[in] gdbarch   The GDB architecture to consider
  @param[in] regcache  The cached register values as an array
  @param[in] regnum    The register to read
  @param[in] buf       A buffer with the value to write                    */
/*----------------------------------------------------------------------------*/
static void
epiphany_pseudo_register_write (struct gdbarch  *gdbarch,
				struct regcache *regcache,
				int              regnum,
				const gdb_byte  *buf)
{
  return;

}	/* epiphany_pseudo_register_write() */


/*----------------------------------------------------------------------------*/
/*! Return the register name for the Epiphany architecture

  This version converted to ANSI C, made static and incorporates the static
  table of register names (this is the only place it is referenced).

  The architecture manual specifies MEMPROTECT, COREID and SWRESET
  registers, but they are not currently displayed by GDB as special
  registers.

  @todo Add MEMPROTECT, COREID and SWRESET. Needs a corresponding change to
  the Remote Serial Protocol server.

  @todo The floating point registers could be done as pseudo-registers.

  @param[in] gdbarch  The GDB architecture being used
  @param[in] regnum   The register number

  @return  The textual name of the register                                */
/*----------------------------------------------------------------------------*/
static const char *
epiphany_register_name (struct gdbarch *gdbarch,
			int             regnum)
{
  static char *epiphany_gdb_reg_names[EPIPHANY_TOTAL_NUM_REGS] =
    {
      /* general purpose registers */
      "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
      "r8",  "r9",  "r10", "r11",  "ip",  "sp",  "lr", "fp",
      "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
      "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
      "r32", "r33", "r34", "r35", "r36", "r37", "r38", "r39",
      "r40", "r41", "r42", "r43", "r44", "r45", "r46", "r47",
      "r48", "r49", "r50", "r51", "r52", "r53", "r54", "r55",
      "r56", "r57", "r58", "r59", "r60", "r61", "r62", "r63",

      /* All the SCRs */
      "config",       "status",       "pc",           "debugstatus",
      "lc",           "ls",           "le",           "iret",
      "imask",        "ilat",         "ilatst",       "ilatcl",
      "ipend",        "fstatus",      "debugcmd",     "resetcore",
      "ctimer0",      "ctimer1",      "memstatus",    "memprotect",
      "dma0config",   "dma0stride",   "dma0count",    "dma0srcaddr",
      "dma0dstaddr",  "dma0auto0",    "dma0auto1",    "dma0status",
      "dma1config",   "dma1stride",   "dma1count",    "dma1srcaddr",
      "dma1dstaddr",  "dma1auto0",    "dma1auto1",    "dma1status",
      "meshconfig",   "coreid",       "multicast",    "cmeshroute",
      "xmeshroute",   "rmeshroute"

      /* Floating point registers may appear as pseudo registers in the
	 future. */
    };

  if (regnum < EPIPHANY_TOTAL_NUM_REGS)
    return epiphany_gdb_reg_names[regnum];
  else
    internal_error (__FILE__, __LINE__,
		    _("epiphany_register_name: illegal register number %d"),
		    regnum);

}	/* epiphany_register_name() */


/*----------------------------------------------------------------------------*/
/*! Identify the type of a register

  @todo All the special core registers are shown as data, but some should
  really be addresses.

  @param[in] arch     The GDB architecture to consider
  @param[in] regnum   The register to identify

  @return  The type of the register  as a "type" struct                    */
/*----------------------------------------------------------------------------*/
static struct type *
epiphany_register_type (struct gdbarch *arch,
			int             regnum)
{
  static struct type *void_func_ptr = NULL;
  static struct type *void_ptr      = NULL;

  /* Set up the static pointers once for the function and pointer types, the
     first time*/
  if (NULL == void_func_ptr)
    {
      struct type *void_type = builtin_type (arch)->builtin_void;

      void_ptr      = lookup_pointer_type (void_type);
      void_func_ptr = lookup_pointer_type (lookup_function_type (void_type));
    }

  if((regnum >= 0) && (regnum < EPIPHANY_TOTAL_NUM_REGS))
    {
      switch (regnum)
	{
	case EPIPHANY_LR_REGNUM:
	case EPIPHANY_PC_REGNUM:
	case EPIPHANY_IRET_REGNUM:
	  return void_func_ptr;		/* Pointer to code */

	case EPIPHANY_SB_REGNUM:
	case EPIPHANY_SL_REGNUM:
	case EPIPHANY_FP_REGNUM:
	case EPIPHANY_SP_REGNUM:
	  return void_ptr;		/* Pointer to data */

	default:
	  return builtin_type (arch)->builtin_uint32;	/* Data */
	}
    }

  internal_error (__FILE__, __LINE__,
		  _("epiphany_register_type: illegal register number %d"),
		  regnum);

}	/* epiphany_register_type() */


/*----------------------------------------------------------------------------*/
/*!Return the frame ID for a dummy stack frame

  Tear down a dummy frame created by epiphany_push_dummy_call(). This data
  has to be constructed manually from the data in our hand.

  The stack pointer and program counter can be obtained from the frame info.

  @param[in] gdbarch     The architecture to use
  @param[in] this_frame  Information about this frame

  @return  Frame ID of this frame                                             */
/*----------------------------------------------------------------------------*/
static struct frame_id
epiphany_dummy_id (struct gdbarch    *gdbarch,
		   struct frame_info *this_frame)
{
  CORE_ADDR this_sp = get_frame_sp (this_frame);
  CORE_ADDR this_pc = get_frame_pc (this_frame);

  epiphany_debug_infrun ("dummy_id called.\n");
  epiphany_debug_infrun ("  SP = %p.\n", (void *) this_sp);
  epiphany_debug_infrun ("  PC = %p.\n", (void *) this_pc);

  return  frame_id_build (this_sp, this_pc);

}	/* epiphany_dummy_id() */


/*----------------------------------------------------------------------------*/
/*!Create a dummy stack frame

  The arguments are placed in registers and/or pushed on the stack as per the
  Epiphany ABI.

  @todo This is only a first approximation. For now we assume aggregates of
        size 1, 2, 4 or 8 bytes are passed by value and all others passed by
        reference. However it is more subtle than this, since any aggregate
        with a constructor, or with alignment less than its size (e.g. if
        packed) is also passed by reference. To fix that will require more
        debug information than we have in our hand - possibly DWARF2 can tell
        us about this in the future.

  @todo Put bpa and bpw in architectural dependency information.

  @param[in] gdbarch        The architecture to use
  @param[in] function       Pointer to the function that will be called
  @param[in] regcache       The register cache to use
  @param[in] bp_addr        Breakpoint address
  @param[in] nargs          Number of ags to push
  @param[in] args           The arguments
  @param[in] sp             The stack pointer
  @param[in] struct_return  True (1) if this returns a structure
  @param[in] struct_addr    Address for returning structures

  @return  The updated stack pointer                                          */
/*----------------------------------------------------------------------------*/
static CORE_ADDR
epiphany_push_dummy_call (struct gdbarch  *gdbarch,
			  struct value    *function,
			  struct regcache *regcache,
			  CORE_ADDR        bp_addr,
			  int              nargs,
			  struct value   **args,
			  CORE_ADDR        sp,
			  int              struct_return,
			  CORE_ADDR        struct_addr)
{
  enum bfd_endian byte_order = gdbarch_byte_order (gdbarch);

  int             argreg;		/* Number of arg reg to use. */
  int             argnum;		/* Arg being processed */
  int             first_stack_arg;	/* First arg to go on stack. */
  int             stack_offset = 0;

  /* These ought to be an architectural dependency (i.e. in gdbarch_tdep). But
     for now they are hand-coded. */
  unsigned int    bpa = EPIPHANY_BYTES_PER_WORD;
  unsigned int    bpw = EPIPHANY_BYTES_PER_WORD;

  epiphany_debug_infrun ("dummy frame sp on entry %p\n", (void *) sp);
  epiphany_debug_infrun ("  return address %p\n", (void *) bp_addr);

  /* Breakpoint address is where to return. */
  regcache_cooked_write_unsigned (regcache, EPIPHANY_LR_REGNUM, bp_addr);

  /* Start counting argument registers. */
  argreg = EPIPHANY_FIRST_ARG_REGNUM;

  /* Location for a returned structure. This is passed as a silent first
     argument. */
  if (struct_return)
    {
      regcache_cooked_write_unsigned (regcache, EPIPHANY_FIRST_ARG_REGNUM,
				      struct_addr);
      epiphany_debug_infrun ("dummy frame struct return\n");
      epiphany_debug_infrun ("  address 0x%p in r%d\n", struct_addr, argreg);

      argreg++;
    }

  /* Put as many args as possible in registers */
  for (argnum = 0; argnum < nargs; argnum++)
    {
      const gdb_byte *val;
      gdb_byte        valbuf[sizeof (ULONGEST)];

      struct value   *arg      = args[argnum];
      struct type    *arg_type = check_typedef (value_type (arg));
      int             len      = arg_type->length;
      enum type_code  typecode = arg_type->main_type->code;

      epiphany_debug_infrun ("dummy frame arg %d\n", argnum);
      epiphany_debug_infrun ("  typecode: %d\n", typecode);
      epiphany_debug_infrun ("  length:   %d\n", len);

      /* Handle the different argument types. */
      if((TYPE_CODE_STRUCT == typecode) || (TYPE_CODE_UNION == typecode))
	{
	  /* Not all aggregates can be passed by value. */
	  if (epiphany_aggregate_by_value_p (gdbarch, function, argnum,
					     args, len))
	    {
	      val = value_contents (arg);
	      epiphany_debug_infrun ("  aggregate passed by value\n");
	    }
	  else
	    {
	      /* Use the address of the argument as the value. */
	      store_unsigned_integer (valbuf, bpa, byte_order,
				      value_address (arg));
	      len = bpa;
	      val = valbuf;

	      epiphany_debug_infrun ("  aggregate passed by reference\n");
	      epiphany_debug_infrun ("    length now %d\n", len);
	    }
	}
      else
	{
	  /* Everything else, we just get the value. */
	  val = value_contents (arg);
	  epiphany_debug_infrun ("  scalar passed by value\n");
	}

      /* Stick the value in a register if possible. */
      if (len == 4 * bpw)
	{
	  /* quad-word values can go in 4 argument registers if possible. Must
	     be 4-register aligned. */
	  argreg = (argreg + 1) / 4 * 4;	/* Next aligned reg. */

	  if (argreg <= (EPIPHANY_LAST_ARG_REGNUM - 1))
	    {
	      /* We need to break out the two register values. The endianness
		 does not matter. Although Epiphany is little endian, a future
		 big-endian version would swap the order of reigister usage as
		 well as the order in memory. */
	      ULONGEST r0, r1, r2, r3;

	      r0 = extract_unsigned_integer (val,           bpw, byte_order);
	      r1 = extract_unsigned_integer (val + bpw,     bpw, byte_order);
	      r2 = extract_unsigned_integer (val + bpw * 2, bpw, byte_order);
	      r3 = extract_unsigned_integer (val + bpw * 3, bpw, byte_order);

	      epiphany_debug_infrun ("  stored in r%d, r%d, r%d and r%d\n",
				     argreg, argreg + 1, argreg + 2,
				     argreg + 3);

	      regcache_cooked_write_unsigned (regcache, argreg++, r0);
	      regcache_cooked_write_unsigned (regcache, argreg++, r1);
	      regcache_cooked_write_unsigned (regcache, argreg++, r2);
	      regcache_cooked_write_unsigned (regcache, argreg++, r3);
	    }
	  else
	    {
	      /* Run out of regs */
	      epiphany_debug_infrun ("  run out of registers\n");
	      break;
	    }
	}
      else if (len == 2 * bpw)
	{
	  /* double-word values can go in 2 argument registers if possible. Must
	     be 2-register aligned. */
	  argreg = (argreg + 1) / 2 * 2;	/* Next aligned reg. */

	  if (argreg <= (EPIPHANY_LAST_ARG_REGNUM - 1))
	    {
	      /* We need to break out the two register values. The endianness
		 does not matter. Although Epiphany is little endian, a future
		 big-endian version would swap the order of reigister usage as
		 well as the order in memory. */
	      ULONGEST r0, r1;

	      r0 = extract_unsigned_integer (val,           bpw, byte_order);
	      r1 = extract_unsigned_integer (val + bpw,     bpw, byte_order);

	      epiphany_debug_infrun ("  stored in r%d and r%d\n", argreg,
				     argreg + 1);

	      regcache_cooked_write_unsigned (regcache, argreg++, r0);
	      regcache_cooked_write_unsigned (regcache, argreg++, r1);
	    }
	  else
	    {
	      /* Run out of regs */
	      epiphany_debug_infrun ("  run out of registers\n");
	      break;
	    }
	}
      else if (len <= bpw)
	{
	  /* These values can go into a single register, so no alignment
	     needed. */

	  if (argreg <= EPIPHANY_LAST_ARG_REGNUM)
	    {
	      /* We need to break out the register values. */
	      ULONGEST r;

	      r = extract_unsigned_integer (val, len, byte_order);

	      epiphany_debug_infrun ("  stored in r%d\n", argreg);

	      regcache_cooked_write_unsigned (regcache, argreg++, r);
	    }
	  else
	    {
	      /* Run out of regs */
	      epiphany_debug_infrun ("  run out of registers\n");
	      break;
	    }
	}
      else
	{
	  /* This is an impossible length (longer arguments are passed by
	     reference, so by now len is just one word), so we have hit some
	     sort of problem. */
	  internal_error (__FILE__, __LINE__,
			  _("epiphany_push_dummy_call bad reg arg length"));
	  break;
	}
    }

  /* If we get here with argnum < nargs, then arguments remain to be placed on
     the stack. This is tricky, since they must be pushed in reverse order and
     the stack in the end must be aligned. The only solution is to do it in
     two stages, the first to compute the stack size, the second to save the
     args. */
  first_stack_arg = argnum;

  for (argnum = first_stack_arg; argnum < nargs; argnum++)
    {
      struct value   *arg      = args[argnum];
      struct type    *arg_type = check_typedef (value_type (arg));
      int             len      = arg_type->length;
      enum type_code  typecode = arg_type->main_type->code;

      if((TYPE_CODE_STRUCT == typecode) || (TYPE_CODE_UNION == typecode))
	{
	  if (epiphany_aggregate_by_value_p (gdbarch, function, argnum,
					     args, len))
	    {
	      /* Pass on the stack in multiples of PARM_BOUNDARY_BYTES.
		 Except that if we are a multiple of words in length, we must
		 align by that length. For now we only deal with 2 x words.*/
	      if (len == 2 * bpw)
		{
		  epiphany_debug_infrun ("  aligning aggregate stack arg %d\n",
					 argnum);
		  epiphany_debug_infrun ("    sp was 0x%p\n", (void *) sp);
		  sp -= sp % len;
		  epiphany_debug_infrun ("    sp now 0x%p\n", (void *) sp);
		}
	      else if (len > bpw)
		{
		  /* This should be an impossible length to get here. But for
		     safety throw an error. */
		  internal_error (__FILE__, __LINE__,
				  _("epiphany_push_dummy_call bad aggregate length"));
		}

	      sp -= epiphany_parm_size (len);
	    }
	  else
	    {
	      sp -= epiphany_parm_size (bpa);
	    }
	}
      else
	{
	  /* Allow space of scalars, keeping the stack aligned, but no more
	     than double word aligned */
	  if ((len == 4 * bpw) || (len == 2 * bpw))
	    {
	      epiphany_debug_infrun ("  aligning scalar stack arg %d\n",
				     argnum);
	      epiphany_debug_infrun ("    sp was 0x%p\n", (void *) sp);
	      sp -= sp % (2 * bpw);
	      epiphany_debug_infrun ("    sp now 0x%p\n", (void *) sp);
	    }
	  else if (len > bpw)
	    {
	      /* This should be an impossible length to get here. But for
		 safety throw an error. */
	      internal_error (__FILE__, __LINE__,
			      _("epiphany_push_dummy_call bad scalar length"));
	    }

	  sp -= epiphany_parm_size (len);
	}
    }

  /* The stack needs to be aligned before we start pushing arguments. */
  sp = gdbarch_frame_align (gdbarch, sp);

  /* The stack has a number of bytes pre-allocated for use by the callee. Any
     stack args go before that. This really ought to be configurable (as it is
     in GCC), and we assume it meets stack alignment restrictions. */
  stack_offset  = EPIPHANY_STACK_OFFSET;

  /* Push the remaining args on the stack */
  for (argnum = first_stack_arg; argnum < nargs; argnum++)
    {
      const gdb_byte *val;
      gdb_byte        valbuf[sizeof (ULONGEST)];

      struct value   *arg      = args[argnum];
      struct type    *arg_type = check_typedef (value_type (arg));
      int             len      = arg_type->length;
      enum type_code  typecode = arg_type->main_type->code;

      epiphany_debug_infrun ("dummy frame arg %d\n", argnum);
      epiphany_debug_infrun ("  typecode: %d\n", typecode);
      epiphany_debug_infrun ("  length:   %d\n", len);

      /* Handle the different argument types. */
      if((TYPE_CODE_STRUCT == typecode) || (TYPE_CODE_UNION == typecode))
	{
	  if (epiphany_aggregate_by_value_p (gdbarch, function, argnum,
					     args, len))
	    {
	      /* Get the value. */
	      val = value_contents (arg);
	      epiphany_debug_infrun ("  aggregate passed by value\n");
	    }
	  else
	    {
	      /* Use the address of the argument as the value. */
	      store_unsigned_integer (valbuf, bpa, byte_order,
				      value_address (arg));
	      val = valbuf;
	      len = bpa;

	      epiphany_debug_infrun ("  aggregate passed by reference\n");
	      epiphany_debug_infrun ("    length now %d\n", len);
	    }
	}
      else
	{
	  /* Get the value of a scalar. */
	  val = value_contents (arg);
	  epiphany_debug_infrun ("  scalar passed by value\n");
	}

      /* If we have a length longer than bpw (2 or 4 * bpw should be the only
	 one possible here), then align the stack offset to double word. */
      if ((len == 4 * bpw) || (len == 2 * bpw))
	{
	  stack_offset += stack_offset % (2 * bpw);
	}

      /* Write to stack and update the offset. */
      epiphany_debug_infrun ("  stored at 0x%p (SP + %d)\n",
			     (void *) (sp + stack_offset), stack_offset);

      write_memory (sp + stack_offset, val, len);
      stack_offset += epiphany_parm_size (len);
    }

  epiphany_debug_infrun ("dummy frame sp on exit %p\n", (void *) sp);

  /* Save and return the updated stack pointer */
  regcache_cooked_write_unsigned (regcache, EPIPHANY_SP_REGNUM, sp);
  return  sp;

}	/* epiphany_push_dummy_call() */


/*----------------------------------------------------------------------------*/
/*! Handle the "info register" command

  Print the identified register, unless it is -1, in which case print all
  the registers. If argument "all" is 1 means all registers, otherwise only
  the core GPRs.

  This code is derived from default_print_registers_info. It prints GPRs in
  float as well.

  @param[in] gdbarch    The GDB architecture being used
  @param[in] file       File handle for use with any custom I/O
  @param[in] frame      Frame info for use with custom output
  @param[in] regnum     Register of interest, or -1 if all registers
  @param[in] print_all  non-zero to print all registers, zero to print just
  GPRs.                                                */
/*----------------------------------------------------------------------------*/
static void
epiphany_print_registers_info (struct gdbarch    *gdbarch,
			       struct ui_file    *file,
			       struct frame_info *frame,
			       int                regnum,
			       int                print_all)
{
  int i;
  const int numregs = gdbarch_num_regs (gdbarch)
    + gdbarch_num_pseudo_regs (gdbarch);

  for (i = 0; i < numregs; i++)
    {
      struct type *regtype;
      struct value *val;
      struct value_print_options opts;

      /* Decide between printing all regs, non-float / vector regs, or
         specific reg.  */
      if (regnum == -1)
	{
	  if (print_all)
	    {
	      if (!gdbarch_register_reggroup_p (gdbarch, i, all_reggroup))
		continue;
	    }
	  else
	    {
	      if (!gdbarch_register_reggroup_p (gdbarch, i, general_reggroup))
		continue;
	    }
	}
      else
	{
	  if (i != regnum)
	    continue;
	}

      /* If the register name is empty, it is undefined for this
         processor, so don't display anything.  */
      if (gdbarch_register_name (gdbarch, i) == NULL
	  || *(gdbarch_register_name (gdbarch, i)) == '\0')
	continue;

      fputs_filtered (gdbarch_register_name (gdbarch, i), file);
      print_spaces_filtered (15 - strlen (gdbarch_register_name
					  (gdbarch, i)), file);

      regtype = register_type (gdbarch, i);
      val = allocate_value (regtype);

      /* Get the data in raw format.  */
      if (! deprecated_frame_register_read (frame, i, value_contents_raw (val)))
	{
	  fprintf_filtered (file, "*value not available*\n");
	  continue;
	}

      /* Print the register in hex.  */
      get_formatted_print_options (&opts, 'x');
      opts.deref_ref = 1;
      val_print (regtype,
		 value_contents_for_printing (val),
		 value_embedded_offset (val), 0,
		 file, 0, val, &opts, current_language);

      /* Print the register according to its natural format */
      get_user_print_options (&opts);
      opts.deref_ref = 1;
      fprintf_filtered (file, "\t");
      val_print (regtype,
		 value_contents_for_printing (val),
		 value_embedded_offset (val), 0,
		 file, 0, val, &opts, current_language);

      /* If it in the float group (i.e. a GPR), then print in FP format as
	 well. */
      if (gdbarch_register_reggroup_p (gdbarch, i, float_reggroup))
	{
	  struct type *float_type = builtin_type (gdbarch)->builtin_float;

	  get_user_print_options (&opts);
	  opts.deref_ref = 1;

	  print_spaces_filtered (4, file);
	  val_print (float_type,
		     value_contents_for_printing (val),
		     value_embedded_offset (val), 0,
		     file, 0, val, &opts, current_language);
	}

      fprintf_filtered (file, "\n");
    }
}	/* epiphany_print_registers_info() */


/*----------------------------------------------------------------------------*/
/*! Handle the "info float" command

  Print any regs in the float group (i.e. GPRs) as floating point
  values. For now we ignore the args. This just uses the standard
  epiphany_print_register_info, which will print the FP value.

  @todo: Should we use the args - for example to identify registers to print
  out?

  @param[in] gdbarch  The GDB architecture being used.
  @param[in] file     File handle for use with any custom I/O.
  @param[in] frame    Frame info for use with custom output.
  @param[in] args     Any supplementary arguments to info float.           */
/*----------------------------------------------------------------------------*/
static void
epiphany_print_float_info (struct gdbarch    *gdbarch,
			   struct ui_file    *file,
			   struct frame_info *frame,
			   const char        *args)
{
  int  regnum;
  const int numregs = gdbarch_num_regs (gdbarch)
    + gdbarch_num_pseudo_regs (gdbarch);

  /* Do all (valid) registers */
  for (regnum = 0; regnum < numregs; regnum++)
    {
      if (('\0' != *(epiphany_register_name (gdbarch, regnum))) &&
	  (gdbarch_register_reggroup_p (gdbarch, regnum, float_reggroup)))
	{
	  epiphany_print_registers_info (gdbarch, file, frame, regnum, 0);
	}
    }
}	/* epiphany_print_float_info() */


/*----------------------------------------------------------------------------*/
/*! Determine if a register is writable.

  Print the GPRS as floating point values. For now we ignore the args.

  @todo: Should we use the args - for example to identify registers to print
  out?

  @param[in] gdbarch  The GDB architecture being used.
  @param[in] regnum   The register to check.

  @return  Non-zero if the register cannot be written, zero otherwise.     */
/*----------------------------------------------------------------------------*/
static int
epiphany_cannot_store_register (struct gdbarch    *gdbarch,
				int                regnum)
{
  switch (regnum)
    {
    case EPIPHANY_ILAT_REGNUM:
    case EPIPHANY_IPEND_REGNUM:
      /* These are non-writable */
      return  1;

    default:
      /* These are writable */
      return  0;
    }
}	/* epiphany_cannot_store_register() */


/*----------------------------------------------------------------------------*/
/*! Determine where longjmp will land.

  We have breakpointed at the start of a longjmp, so the jmp_buf ought to be
  in the first argument (i.e. r0).

  @todo  Needs writing.

  @param[in]  frame   Information about THIS frame.
  @param[out] pc_ptr  The PC where the longjmp will land.

  @return  Non-zero if we could determine where the longjmp will land
            (address returned via pc_ptr, zero otherwise.                     */
/*----------------------------------------------------------------------------*/
static int
epiphany_get_longjmp_target (struct frame_info *frame,
			     CORE_ADDR         *pc_ptr)
{
  fprintf_unfiltered (gdb_stdlog,
		      "no support for breakpoint at the start of longjmp.\n");
  return  0;

}	/* epiphany_get_longjmp_target () */


/*----------------------------------------------------------------------------*/
/*! Determine the return convention used for a given type

  The Epiphany returns character, half and single word scalars in RV_REGNUM,
  double word scalars in RV_REGNUM and RV_REGNUM + 1 and quad-word scalars in
  RV_REGNUM thru RV_REGNUM + 3.

  Aligned composite values of integral size up to two words are returned in
  RV_REGNUM and if required RV_REGNUM + 1. Larger values are returned by
  reference, with a pointer to the result in RV_REGNUM.

  @note There is a problem, in that the debug information does not generally
        tell us whether a composite value is aligned. For now we assume this
        is only the case for composites of byte, word and double-word size.

  If the result is returned by register, optionally, fetch or set the return
  value via "readbuf" or "writebuf" respectively using "regcache" for the
  register values. If "writebuf" is non-NULL, copy the value in "writebuf"
  into the register in "regcache". If "readbuf" is non-NULL, copy the value
  in the register in "regcache" into "readbuf".

  Throughout use read_memory(), not target_read_memory(), since the address
  may be invalid and we want an error reported (read_memory() is
  target_read_memory() with error reporting).

  @param[in]  gdbarch   The GDB architecture being used
  @param[in]  function  The function
  @param[in]  valtype   The type of the entity to be returned
  @param[in]  regcache  The register cache
  @param[in]  readbuf   Buffer into which the return value should be written
  @param[out] writebuf  Buffer from which the return value should be written

  @return  The type of return value                                        */
/*----------------------------------------------------------------------------*/
static enum return_value_convention
epiphany_return_value (struct gdbarch  *gdbarch,
		       struct value    *function,
		       struct type     *valtype,
		       struct regcache *regcache,
		       gdb_byte        *readbuf,
		       const gdb_byte  *writebuf)
{
  /* This ought to be an architectural dependency (i.e. in gdbarch_tdep). But
     for now it is hand-coded. */
  unsigned int    bpw = EPIPHANY_BYTES_PER_WORD;

  enum type_code  rv_type    = TYPE_CODE (valtype);
  unsigned int    rv_size    = TYPE_LENGTH (valtype);
  enum bfd_endian byte_order = gdbarch_byte_order (gdbarch);

  epiphany_debug_infrun ("Return value rv_size %d\n", rv_size);
  epiphany_debug_infrun ("  readbuf 0x%p, writebuf 0x%p\n", readbuf, writebuf);

  /* Deal with aggregates passed by reference */
  if (((TYPE_CODE_STRUCT == rv_type) || (TYPE_CODE_UNION  == rv_type))
      && (rv_size != 1) && (rv_size != 4) && (rv_size != 8))
    {
      /* Ignore buffers when returning by reference. */
      epiphany_debug_infrun ("  returning value by struct\n");
      return  RETURN_VALUE_STRUCT_CONVENTION;
    }

  /* How small structs and scalars are dealt with depends on the size. We
     allow for up to 4 words here, although there may not be a 4 word scalar
     type in use. */
  if (rv_size <= bpw)
    {
      /* Single word, use RV_REGNUM. Using extract_unsigned_integer should
	 sort out any endianness padding issues. */
      if (readbuf)
	{
	  ULONGEST  r;

	  regcache_cooked_read_unsigned (regcache, EPIPHANY_RV_REGNUM, &r);
	  store_unsigned_integer (readbuf, rv_size, byte_order, r);

	  epiphany_debug_infrun ("  word from register 0x%08llx\n", r);
	}
      if (writebuf)
	{
	  ULONGEST  r;

	  r = extract_unsigned_integer (writebuf, rv_size, byte_order);
	  regcache_cooked_write_unsigned (regcache, EPIPHANY_RV_REGNUM, r);

	  epiphany_debug_infrun ("  word from memory 0x%08llx\n", r);
	}
    }
  else if ((bpw * 2) == rv_size)
    {
      /* Double word, use RV_REGNUM and RV_REGNUM + 1. Endianness sorts
	 itself out (it will matche the order of registers). */
      if (readbuf)
	{
	  ULONGEST  r0, r1;

	  regcache_cooked_read_unsigned (regcache, EPIPHANY_RV_REGNUM,     &r0);
	  regcache_cooked_read_unsigned (regcache, EPIPHANY_RV_REGNUM + 1, &r1);

	  store_unsigned_integer (readbuf,       bpw, byte_order, r0);
	  store_unsigned_integer (readbuf + bpw, bpw, byte_order, r1);

	  epiphany_debug_infrun ("  word from register 0x%08llx%08llx\n", r0,
				 r1);
	}
      if (writebuf)
	{
	  ULONGEST  r0, r1;

	  r0 = extract_unsigned_integer (writebuf,       bpw, byte_order);
	  r1 = extract_unsigned_integer (writebuf + bpw, bpw, byte_order);

	  regcache_cooked_write_unsigned (regcache, EPIPHANY_RV_REGNUM,     r0);
	  regcache_cooked_write_unsigned (regcache, EPIPHANY_RV_REGNUM + 1, r1);

	  epiphany_debug_infrun ("  word from memory 0x%08llx%08llx\n", r0,
				 r1);
	}
    }
  else if ((bpw * 4) == rv_size)
    {
      /* Quad word, use RV_REGNUM thru RV_REGNUM + 3. Endianness sorts
	 itself out (it will matche the order of registers). */
      if (readbuf)
	{
	  ULONGEST  r0, r1, r2, r3;

	  regcache_cooked_read_unsigned (regcache, EPIPHANY_RV_REGNUM,     &r0);
	  regcache_cooked_read_unsigned (regcache, EPIPHANY_RV_REGNUM + 1, &r1);
	  regcache_cooked_read_unsigned (regcache, EPIPHANY_RV_REGNUM + 2, &r2);
	  regcache_cooked_read_unsigned (regcache, EPIPHANY_RV_REGNUM + 3, &r3);

	  store_unsigned_integer (readbuf,           bpw, byte_order, r0);
	  store_unsigned_integer (readbuf + bpw,     bpw, byte_order, r1);
	  store_unsigned_integer (readbuf + bpw * 2, bpw, byte_order, r2);
	  store_unsigned_integer (readbuf + bpw * 3, bpw, byte_order, r3);

	  epiphany_debug_infrun ("  word from register 0x%08llx%08llx%08llx%08llx\n",
				 r0, r1, r2, r3);
	}
      if (writebuf)
	{
	  ULONGEST  r0, r1, r2, r3;

	  r0 = extract_unsigned_integer (writebuf,           bpw, byte_order);
	  r1 = extract_unsigned_integer (writebuf + bpw,     bpw, byte_order);
	  r2 = extract_unsigned_integer (writebuf + bpw * 2, bpw, byte_order);
	  r3 = extract_unsigned_integer (writebuf + bpw * 3, bpw, byte_order);

	  regcache_cooked_write_unsigned (regcache, EPIPHANY_RV_REGNUM,     r0);
	  regcache_cooked_write_unsigned (regcache, EPIPHANY_RV_REGNUM + 1, r1);
	  regcache_cooked_write_unsigned (regcache, EPIPHANY_RV_REGNUM + 2, r2);
	  regcache_cooked_write_unsigned (regcache, EPIPHANY_RV_REGNUM + 3, r3);

	  epiphany_debug_infrun ("  word from memory 0x%08llx%08llx%08llx%08llx\n",
				 r0, r1, r2, r3);	}
    }
  else
    {
      /* We really shouldn't get here. This is a safety catch for a bad
	 size. */
      internal_error (__FILE__, __LINE__,
		      _("epiphany_return_value bad size"));
    }

  return  RETURN_VALUE_REGISTER_CONVENTION;

}	/* epiphany_return_value() */


/*----------------------------------------------------------------------------*/
/*!Skip a function prologue

  If the input address, PC, is in a function prologue, return the address of
  the end of the prologue, otherwise return the input address.

  We attempt to use the source and line data from the symtab and line data.

  @note Currently epiphany seems to include some content in the prologue that
        is not reasonable. In particular code to copy structs passed by
        reference to the stack is included in the prologue. However attempting
        to do something more clever breaks more than it fixes!

  @param[in] gdbarch  The GDB architecture being used
  @param[in] pc       Current program counter

  @return  The address of the end of the prologue if the PC is in a function
           prologue, otherwise the input  address.                            */
/*----------------------------------------------------------------------------*/
static CORE_ADDR
epiphany_skip_prologue (struct gdbarch *gdbarch,
			CORE_ADDR       pc)
{
  CORE_ADDR  func_start, func_end;

  if (find_pc_partial_function (pc, NULL, &func_start, &func_end))
    {
      /* Can we find the prologue end using SAL? */
      CORE_ADDR  prologue_end = skip_prologue_using_sal (gdbarch, func_start);

      return  (0 == prologue_end) ? pc : prologue_end;
    }
  else
    {
      /* Can't find the function. Give up. */
      return  pc;
    }

}	/* epiphany_skip_prologue() */


/*----------------------------------------------------------------------------*/
/*! Determine the instruction to use for a breakpoint.

    Given the address at which to insert a breakpoint (bp_addr), what will
    that breakpoint be?

    For Epiphany, we have a breakpoint instruction, BKPT, which is 16 bits long,
    so will fit any other instruction.

    @todo There is apparently a problem with the breakpoint instruction in the
          real hardware needing opposite endianness. This is almost certainly
          a bug in the remote protocol server.

    @param[in]  gdbarch  The GDB architecture being used
    @param[in]  bp_addr  The breakpoint address in question
    @param[out] bp_size  The size of instruction selected

    @return  The chosen breakpoint instruction                               */
/*----------------------------------------------------------------------------*/
static const gdb_byte *
epiphany_breakpoint_from_pc (struct gdbarch *gdbarch,
			     CORE_ADDR      *bp_addr,
			     int            *bp_size)
{
  static  const gdb_byte breakpoint[] = EPIPHANY_BKPT_INST_STRUCT;

  *bp_size = EPIPHANY_BKPT_INSTLEN;
  return breakpoint;

}	/* epiphany_breakpoint_from_pc() */


/*----------------------------------------------------------------------------*/
/*! Unwind the program counter from a stack frame

    This just uses the built in frame unwinder

    @param[in] gdbarch     The GDB architecture being used
    @param[in] next_frame  Frame info for THIS frame

    @return  The program counter for THE PREVIOUS frame                       */
/*----------------------------------------------------------------------------*/
static CORE_ADDR
epiphany_unwind_pc (struct gdbarch    *gdbarch,
		    struct frame_info *this_frame)
{
  return frame_unwind_register_unsigned (this_frame, EPIPHANY_PC_REGNUM);

}	/* epiphany_unwind_pc() */


/*----------------------------------------------------------------------------*/
/*! Unwind the stack pointer from a stack frame

    This just uses the built in frame unwinder

    @param[in] gdbarch     The GDB architecture being used
    @param[in] next_frame  Frame info for THIS frame

    @return  The stack pointer for the PREVIOUS frame                         */
/*----------------------------------------------------------------------------*/
static CORE_ADDR
epiphany_unwind_sp (struct gdbarch    *gdbarch,
		    struct frame_info *this_frame)
{
  return frame_unwind_register_unsigned (this_frame, EPIPHANY_SP_REGNUM);

}	/* epiphany_unwind_sp() */


/*----------------------------------------------------------------------------*/
/*! Align the stack frame

    Epiphany uses a falling stack frame, so this aligns down to the nearest
    EPIPHANY_STACK_ALIGN bytes. Useful when we'be building a dummy frame.

    Not sure if its actually needed if you don't support dummy frames.

    @param[in] gdbarch  The GDB architecture being used
    @param[in] sp       Current stack pointer

    @return  The aligned stack frame address                                 */
/*----------------------------------------------------------------------------*/
static CORE_ADDR
epiphany_frame_align (struct gdbarch *gdbarch,
		      CORE_ADDR       sp)
{
  return align_down (sp, EPIPHANY_STACK_ALIGN);

}	/* epiphany_frame_align() */


/*----------------------------------------------------------------------------*/
/*! Set up single step breakpoints

    Epiphany does not have a hardware single step, so we can ask GDB to do it
    for us using software breakpoints.

    For unconditional branches of all sorts we put a temporary breakpoint on
    the branch destination. This may mean getting the value in a register if
    it is an indirect jump.

    For conditional branches of all sorts we put a temporary breakpoint on the
    branch destination and one on the next instruction.

    For all other instructions, we put a temporary breakpoint on the next
    instruction, and on the branch destination if we have a branch
    instruction.

    We don't have to do anything special about single step and the interrupt
    vector. These are unconditional branches, so the next instruction will be
    elsewhere in memory.

    @param[in] frame  The frame for which we want to insert single step
                      breakpoint(s).

    @return  Non-zero (TRUE) if we successfully insert single step
             breakpoints, zero (FALSE) otherwise.                            */
/*----------------------------------------------------------------------------*/
static int
epiphany_software_single_step (struct frame_info *frame)
{
  struct gdbarch *gdbarch = get_frame_arch (frame);
  enum bfd_endian  byte_order_for_code = gdbarch_byte_order_for_code (gdbarch);
  struct address_space *aspace = get_frame_address_space (frame);
  CORE_ADDR pc, next_pc, branch_dest;
  int branch_reg;
  uint32_t instr;
  int is32bit;

  pc = get_frame_pc (frame);
  instr = read_memory_unsigned_integer (pc, 4, byte_order_for_code);
  is32bit = epiphany_is_instr32 (instr);

  next_pc = is32bit ? pc + 4 : pc + 2;

  switch (epiphany_ss_instr_type (instr, is32bit))
    {
    case UNCOND_BRANCH:
      branch_dest = pc + epiphany_branch_offset (instr, is32bit);
      insert_single_step_breakpoint (gdbarch, aspace, branch_dest);
      return  1;

    case COND_BRANCH:
      branch_dest = pc + epiphany_branch_offset (instr, is32bit);
      insert_single_step_breakpoint (gdbarch, aspace, next_pc);
      insert_single_step_breakpoint (gdbarch, aspace, branch_dest);
      return  1;

    case JUMP:
      branch_reg = epiphany_jump_register (instr, is32bit);
      branch_dest = get_frame_register_unsigned (frame, branch_reg);
      insert_single_step_breakpoint (gdbarch, aspace, branch_dest);
      return  1;

    case OTHER:
      insert_single_step_breakpoint (gdbarch, aspace, next_pc);
      return  1;

    default:
      /* We should never get here. */
      gdb_assert (1);
    }

  return 0;
}	/* epiphany_software_single_step () */



/*----------------------------------------------------------------------------*/
/*! Skip trampoline code.

    If we are in trampoline code that sits between callers and a function
    being called, then return a new PC that is at the start of the real
    function.

    @todo Needs writing

    @param[in] frame  Current frame.
    @param[in] pc     Current stack pointer.

    @return  The PC of the real function being called.                       */
/*----------------------------------------------------------------------------*/
static CORE_ADDR
epiphany_skip_trampoline_code (struct frame_info *frame,
			       CORE_ADDR          pc)
{
  fprintf_unfiltered (gdb_stdlog,
		      "No support for debugging in trampoline code at 0x%p.\n",
		      (void *) pc);
  return pc;

}	/* epiphany_skip_trampoline_code () */


/*----------------------------------------------------------------------------*/
/*! Are we in a function epilogue?

    Are we in a function epilogue, i.e. part of a function where the stack
    frame of the function already has been destroyed up to the final ‘return
    from function call’ instruction.

    @note There is a trap here, because as far as GDB is concerned, the
          register defining the stack frame is not the SP, but the register
          against which the CFA is calculated, which may be the FP.

    Epiphany has quite a flexible function epilogue. The simplest version
    just restores the FP, adds a value to the SP and then returns. More
    complicated versions, with large stack frames need more complex operations
    to restore the SP, and where sibcalls are used, may exit with jr rather
    than rts (which is itself an alias for "jr lr". Other instructions may be
    interspersed when optimized. For good measure there may be multiple
    epilogues in the code.

    Our algorithm is to start from the beginning of the function looking for
    epilogue instruction sequences. These are start when the SP of FP is
    incremented either by addition, or by post increment or by loading from
    the stack frame and end with a jr instruction (including rts), with no
    intervening branch instructions.

    @note This is not perfect, but is a good approximation in most
          cases. Really we will only get this completely right if the compiler
          generates DWARF2 to identify the location of epilogues.

    @param[in] gdbarch  The GDB architecture being used.
    @param[in] pc       The address to check.

    @return  Non-zero if the address concerned is in a function epilogue, zero
             otherwise.                                                      */
/*----------------------------------------------------------------------------*/
static int
epiphany_stack_frame_destroyed_p (struct gdbarch *gdbarch,
				 CORE_ADDR       pc)
{
  enum bfd_endian  byte_order_fc = gdbarch_byte_order_for_code (gdbarch);
  unsigned int     bpw           = EPIPHANY_BYTES_PER_WORD;

  CORE_ADDR func_start = 0;
  CORE_ADDR func_end   = 0;

  CORE_ADDR epc;
  CORE_ADDR ep_start;			/* Start of epilogue. */
  int  in_epilogue;			/* True when we are in an epilogue. */

  epiphany_frame_debug ("epilog_p PC 0x%p\n", (void *) pc);

  /* If we can't locate the function, give up */
  if (!find_pc_partial_function (pc, NULL, &func_start, &func_end))
    {
      return  0;
    }

  epiphany_frame_debug ("  func_start 0x%p, func_end 0x%p\n",
			(void *) func_start, (void *) func_end);

  /* Loop looking for epilogue sequences. */
  in_epilogue = 0;
  ep_start    = func_start;

  for (epc = func_start; epc < func_end;)
    {
      unsigned long int insn = read_memory_unsigned_integer (epc, 2,
							     byte_order_fc);
      unsigned int opc = BITS (insn, 3, 0);

      /* 16-bit instructions do not start epilogues (since setting SP or FP is
	 always 32-bit). However a 16-bit jr could be the end of an epilogue
	 with sibcall in action. Other flow of control instructions (other
	 than l.nop) mean we cannot be in an epilogue. */
      if (0 == opc)
	{
	  /* Branch instruction */
	  epiphany_frame_debug ("  PC %p: insn 0x%04x: 16-bit branch\n",
				(void *) epc, insn);
	  epiphany_frame_debug ("    not epilogue\n");
	  in_epilogue = 0;
	  epc += 2;
	  continue;
	}
      else if (2 == opc)
	{
	  /* Flow of control instruction, including jr and nop */
	  if ((insn & 0xe3ff) == 0x0142)
	    {
	      epiphany_frame_debug ("  PC %p: insn 0x%04x: jr\n",
				    (void *) epc, insn);
	      /* jr ends an epilogue if we are in one, so check the PC */
	      if (in_epilogue && ((pc > ep_start) && (pc <= epc)))
		{
		  epiphany_frame_debug ("    PC in epilogue\n");
		  return  1;
		}
	      else
		{
		  epiphany_frame_debug ("    PC not in epilogue\n");
		}

	      in_epilogue = 0;
	    }
	  else if (0x01a2 != insn)
	    {
	      /* Any other flow of control apart from nop */
	      epiphany_frame_debug ("  PC %p: insn 0x%04x: 16-bit flow\n",
				    (void *) epc, insn);
	      epiphany_frame_debug ("    not epilogue\n");
	      in_epilogue = 0;
	    }
	  else
	    {
	      /* nop */
	      epiphany_frame_debug ("  PC %p: insn 0x%04x: nop\n",
				    (void *) epc, insn);
	    }

	  epc += 2;
	  continue;
	}
      else if ((1 == opc) || (3 == opc) || ( 4 == opc) || ( 5 == opc) ||
	       (6 == opc) || (7 == opc) || (10 == opc) || (14 == opc))
	{
	  /* Other 16-bit instruction */
	  epiphany_frame_debug ("  PC %p: insn 0x%04x: other 16-bit\n",
				(void *) epc, insn);
	  epc += 2;
	  continue;
	}

      /* We have a 32-bit instruction */
      insn = read_memory_unsigned_integer (epc, 4, byte_order_fc);

      if (   ((insn & 0xe300e07f) == 0x2000a01b)
	  || ((insn & 0xe300e07f) == 0x2000601b))
	{
	  /* add sp,rN,#<simm>  001nnn00ssssssss101nnnsss0011011.
             add fp,rN,#<simm>  001nnn00ssssssss011nnnsss0011011.

	     Starts an epilogue if the offset is positive and a multiple of
	     bpw. If we are already in an epilogue, just stay in it. */
	  int  simm =
	    SEXTEND16 ((BITS (insn, 23, 16) << 3) | BITS (insn, 9, 7));

	  epiphany_frame_debug ("  PC %p: insn 0x%08x: 32-bit add SP\n",
				(void *) epc, insn);
	  if ((simm > 0) && ((simm % bpw) == 0))
	    {
	      epiphany_frame_debug ("    start epilogue\n");
	      ep_start = in_epilogue ? ep_start : epc;
	      in_epilogue = 1;
	    }
	}
      else if (   ((insn & 0xfe00fc7f) == 0x2400ac4c)
	       || ((insn & 0xfe00fc7f) == 0x2400b44c)
               || ((insn & 0xfe00fc7f) == 0x24006c4c)
	       || ((insn & 0xfe00fc7f) == 0x2400744c)

	       || ((insn & 0xfc7ffc7f) == 0x2400ac49)
	       || ((insn & 0xfc7ffc7f) == 0x2400b449)
	       || ((insn & 0xfc7ffc7f) == 0x24006c49)
	       || ((insn & 0xfc7ffc7f) == 0x24007449)

               || ((insn & 0xfc7ffc7f) == 0x2400ac4d)
	       || ((insn & 0x1c7f1c7f) == 0x0400144d)
               || ((insn & 0xfc7ffc7f) == 0x2400744d)
	       || ((insn & 0x1c7f1c7f) == 0x04000c4d))
	{
	  /* ldr sp,[fp,#+/-<imm>]. 0010010+iiiiiiii101011iii1001100
             ldr sp,[sp,#+/-<imm>]. 0010010+iiiiiiii101101iii1001100
	     ldr fp,[fp,#+/-<imm>]. 0010010+iiiiiiii011011iii1001100
             ldr fp,[sp,#+/-<imm>]. 0010010+iiiiiiii011101iii1001100

	     Displacement load of SP/FP from the stack.

	     ldr sp,[fp,+/-rM].     001001mmm000000+101011mmm1001001
             ldr sp,[sp,+/-rM].     001001mmm000000+101101mmm1001001
	     ldr fp,[fp,+/-rM].     001001mmm000000+011011mmm1001001
             ldr fp,[sp,+/-rM].     001001mmm000000+011101mmm1001001

	     Indexed load of SP/FP, but we are only interested if it is from
	     the stack.

	     @todo Should we consider the case where rM is FP or SP?

	     ldr sp,[fp],+/-rM.     001001mmm000000+101011mmm1001101
	     ldr rD,[sp],+/-rM.     ddd001mmm000000+ddd101mmm1001101
	     ldr fp,[sp],+/-rM.     001001mmm000000+011101mmm1001101
	     ldr rD,[fp],+/-rM.     ddd001mmm000000+ddd011mmm1001101

	     Postmodified load which affects SP/FP.

	     Starts an epilogue. If we are already in an epilogue, just stay
	     in it. */
	  epiphany_frame_debug ("  PC %p: insn 0x%08x: 32-bit SP load\n",
				(void *) epc, insn);
	  epiphany_frame_debug ("    start epilogue\n");
	  ep_start = in_epilogue ? ep_start : epc;
	  in_epilogue = 1;
	}
      else if (   ((insn & 0xfe00fc7f) == 0x2600ac4c)
	       || ((insn & 0x1e001c7f) == 0x0600144c)
               || ((insn & 0xfe00fc7f) == 0x2600744c)
	       || ((insn & 0x1e001c7f) == 0x06000c4c))
	{
	  /* ldr sp,[fp],+<imm>. 00100110iiiiiiii101011iii1001100
	     ldr rD,[sp],+<imm>. ddd00110iiiiiiiiddd101iii1001100
             ldr fp,[sp],+<imm>. 00100110iiiiiiii011101iii1001100
	     ldr rD,[fp],+<imm>. ddd00110iiiiiiiiddd011iii1001100

	     Indexed load with postmodify which affects SP/FP. Only of
	     interest if the postmodify is adding a multiple of words.

	     Starts an epilogue. If we are already in an epilogue, just stay
	     in it. */
	  int  imm = (BITS (insn, 23, 16) << 3) | BITS (insn, 9, 7);

	  epiphany_frame_debug ("  PC %p: insn 0x%08x: 32-bit SP load\n",
				(void *) epc, insn);
	  if ((imm % bpw) == 0)
	    {
	      epiphany_frame_debug ("    start epilogue\n");
	      if (!in_epilogue)
		{
		  ep_start    = epc;
		  in_epilogue = 1;
		}
	    }
	}
      else if (   ((insn & 0x0000000f) == 0x00000008)
	       || ((insn & 0xe3ffe3ff) == 0x0002015f))
	{
	  /* b<cond>  <soff>
	     jalr     rN

	     Flow of control, which can't appear in an epilogue. */
	  epiphany_frame_debug ("  PC %p: insn 0x%08x: 32-bit branch/jalr\n",
				(void *) epc, insn);
	  epiphany_frame_debug ("    not epilogue\n");
	  in_epilogue = 0;
	}
      else if ((insn & 0xe3ffe3ff) == 0x0002014f)
	{
	  /* jr rN
	     End of the epilogue if we are in one. */
	  epiphany_frame_debug ("  PC %p: insn 0x%08x: 32-bit jr\n",
				(void *) epc, insn);
	  if (in_epilogue && ((pc > ep_start) && (pc <= epc)))
	    {
	      epiphany_frame_debug ("    PC in epilogue\n");
	      return  1;
	    }
	  else
	    {
	      epiphany_frame_debug ("    PC not in epilogue\n");
	    }

	  in_epilogue = 0;
	}

      epc += 4;
    }

  return  0;

}	/* epiphany_stack_frame_destroyed_p () */


/*----------------------------------------------------------------------------*/
/*! Identify if a register belongs to a specified group

    Return true if the specified register is a member of the specified
    register group.

    These are the groups of registers that can be displayed via "info reg".

    @param[in] gdbarch  The GDB architecture to consider
    @param[in] regnum   The register to consider
    @param[in] group    The group to consider

   @return  1 (true) if regnum is a member of group, else zero.            */
/*----------------------------------------------------------------------------*/
static int
epiphany_register_reggroup_p (struct gdbarch  *gdbarch,
			      int               regnum,
			      struct reggroup  *group)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* All register group includes everything (GPR or SCR). Is the register in
     the number range of all registers and does it have a non-empty name. */
  if (group == all_reggroup)
    {
      return ((regnum >= 0) &&
	      (regnum < EPIPHANY_TOTAL_NUM_REGS) &&
	      (epiphany_register_name (gdbarch, regnum)[0] != '\0'));
    }

  /* Default is all the GPRs which have printable names. */
  if (group == general_reggroup)
    {
      return ((regnum >= 0) && (regnum <  EPIPHANY_NUM_GPRS) &&
	      (epiphany_register_name (gdbarch, regnum)[0] != '\0'));
    }

  /* The float group has all the GPRs, except those which have a special
     meaning as addresses (SP and LR). Since the FP may be used as a data
     register, we include it in this group. */
  if (group == float_reggroup)
    {
      return ((regnum >= 0) && (regnum <  EPIPHANY_NUM_GPRS) &&
	      (regnum != EPIPHANY_SP_REGNUM) &&
	      (regnum != EPIPHANY_LR_REGNUM) &&
	      (epiphany_register_name (gdbarch, regnum)[0] != '\0'));
    }

  /* We don't currently have a vector register group */
  if (group == vector_reggroup)
    {
      return 0;			/* No vector regs.  */
    }

  /* For any that are not handled above.  */
  return default_register_reggroup_p (gdbarch, regnum, group);

}	/* epiphany_register_reggroup_p() */


/* Support functions for frame handling */

/*----------------------------------------------------------------------------*/
/*!Populate a frame prologue cache for THIS frame.

   Build up the information (saved registers etc) for the given frame from
   its prologue if it does not already exist.

   The prologue cache holds information about where registers in the PREVIOUS
   frame can be found from the data in THIS frame's prologue.

   We break it down into three activities

   1. Allocating a new cache

   2. Scanning the prologue to find where it starts and ends.

   3. Step through the prologue, using the information to populate the cache.

   At least one of gdbarch or this_frame must be supplied. This allows the
   function to be used for skipping the prologue, independent of a frame.

   Each frame has a unique ID, based on both the program counter and
   stack addresses (the former is needed to deal with functions which allocate
   no stack, and the latter to deal with recursive functions). If this_frame
   is supplied, then the frame_id will be set in the cache.

   The simplest stack address to use is the value of the stack pointer at the
   very start of the function, which is actually the value of the SP in the
   previous function. We can find the value in this function by subtracting
   the frame size from the current stack pointer (at the end of the prologue).

   STACK FRAME FORMAT
   ==================

   The Epiphany has a falling stack frame. On entry to a new function, the SP
   points to the end of the old stack frame, but the last 4 words of that
   frame are pre-allocated for use by the new function. There are no fixed
   uses of these 4 words.

   Epiphany always maintains a stack pointer, pointing to the end of
   stack. An frame pointer may be present. It points to the local variables
   (the SP points to local variables *and* outgoing arguments. The FP is
   eliminated in optimized code.

   PREV    |
   stack  <           .
   frame   |          .
           |          .
            - +================+                        -
           |  |                | <- PREV SP + 3 (words)  |
           |  +----------------+                         |
           |  |                | <- PREV SP + 2 (words)  |  pre-allocated
           |  +----------------+                          > save area for
           |  |                | <- PREV SP + 1 (words)  |  use by caller
           |  +----------------+                         |
   THIS    |  |                | <- PREV SP              |
   stack  <   +----------------+                        -
   frame   |  |                |
           |  +----------------+
           |  |                |
           |          .
           |          .
           |          .
           |  |                |
            - +================+                        -
           |  |                | <- THIS SP + 3 (words)  |
           |  +----------------+                         |
           |  |                | <- THIS SP + 2 (words)  |  pre-allocated
           |  +----------------+                          > for use by
           |  |                | <- THIS SP + 1 (words)  |  next function
           |  +----------------+                         |
   NEXT    |  |                | <- THIS SP              |
   stack  <           .                                 -
   frame   |          .
           |          .


    @param[in]     this_frame  THIS frame.
    @param[in,out] cache_ptr   The prologue cache. If not supplied, we build
     it.                                                                      */
/*----------------------------------------------------------------------------*/
static void
epiphany_frame_cache (struct frame_info  *this_frame,
		      struct trad_frame_cache **cache_ptr)
{
  epiphany_frame_debug ("epiphany_frame_cache called\n");

  /* Create the cache if we don't have one. */
  if (NULL == *cache_ptr)
    {
      struct trad_frame_cache *cache = trad_frame_cache_zalloc (this_frame);

      CORE_ADDR  prologue_start;
      CORE_ADDR  prologue_end;

      epiphany_scan_prologue (this_frame, &prologue_start, &prologue_end);
      epiphany_frame_debug (" prologue start %p, end %p\n", prologue_start,
			    prologue_end);
      epiphany_analyse_prologue (this_frame, prologue_start, prologue_end,
				 cache);
      *cache_ptr = cache;
    }
}	/* epiphany_frame_cache() */


/*----------------------------------------------------------------------------*/
/*! Find the frame ID of this frame

    Given a GDB frame (called by THIS frame), determine the address of our
    frame and from this create a new GDB frame struct. The info required is
    obtained from the prologue cache for THIS frame.

    @param[in]     this_frame   THIS frame
    @param[in,out] cache_ptr    Any cached prologue for THIS function.
    @param[out]    this_id_ptr  Frame ID of our own frame.

    @return  Frame ID for THIS frame                                         */
/*----------------------------------------------------------------------------*/
static void
epiphany_frame_this_id (struct frame_info  *this_frame,
			void              **cache_ptr,
			struct frame_id    *this_id_ptr)
{
  struct trad_frame_cache **this_cache = (struct trad_frame_cache **) cache_ptr;

  epiphany_frame_cache (this_frame, this_cache);
  trad_frame_get_id (*this_cache, this_id_ptr);

}	/* epiphany_frame_this_id() */


/*----------------------------------------------------------------------------*/
/*! Get a register from THIS frame

    Given a pointer to the NEXT frame, return the details of a register in the
    PREVIOUS frame.

    @param[in]     this_frame  THIS frame.
    @param[in,out] cache_ptr   Any cached prologue associated with THIS frame,
                               which  may therefore tell us about registers in
                               the PREVIOUS frame.
    @param[in]     regnum      The register of interest in the PREVIOUS frame.

    @return  The value of the register in the previous frame.                */
/*----------------------------------------------------------------------------*/
static struct value *
epiphany_frame_prev_register (struct frame_info  *this_frame,
			      void              **cache_ptr,
			      int                 regnum)
{
  struct trad_frame_cache **this_cache = (struct trad_frame_cache **) cache_ptr;

  epiphany_frame_cache (this_frame, this_cache);

  return  trad_frame_get_register (*this_cache, this_frame, regnum);

}	/* epiphany_frame_prev_register() */


/*----------------------------------------------------------------------------*/
/*! The Epiphany frame sniffer function

    See if this is a frame that we can sniff a base of.

    @param[in]     self        A struct of frame base sniffing functions.
    @param[in]     this_frame  THIS frame we are sniffing.
    @param[in,out] this_cache  A cache of any previous results.

    @return  Non-zero if this is a frame our sniffer/unwinder functions will
             work on, zero otherwise.                                        */
/*----------------------------------------------------------------------------*/
static int
epiphany_frame_sniffer (const struct frame_unwind  *self,
			struct frame_info          *this_frame,
			void                      **this_cache)
{
  /* A trivial function for now. We assume we can sniff any code. */
  return 1;

}	/* epiphany_frame_sniffer () */


/*----------------------------------------------------------------------------*/
/*! The Epiphany frame unwinder/sniffer data structure.

    This struct identifies our family of frame sniffing functions.           */
/*----------------------------------------------------------------------------*/
static struct frame_unwind epiphany_frame_unwind =
{
  .type          = NORMAL_FRAME,
  .stop_reason   = default_frame_unwind_stop_reason,
  .this_id       = epiphany_frame_this_id,
  .prev_register = epiphany_frame_prev_register,
  .unwind_data   = NULL,
  .sniffer       = epiphany_frame_sniffer,
  .dealloc_cache = NULL,
  .prev_arch     = NULL
};


/*----------------------------------------------------------------------------*/
/*! Return the base address of the frame

    For the Epiphany variables are referenced from the frame pointer if we
    have one, otherwise the stack pointer.

    @param[in]     this_frame  THIS frame
    @param[in,out] cache_ptr   Any cached prologue for THIS frame.

    @return  The frame base address                                          */
/*----------------------------------------------------------------------------*/
static CORE_ADDR
epiphany_frame_base_address (struct frame_info  *this_frame,
			     void              **cache_ptr)
{
  struct trad_frame_cache **this_cache = (struct trad_frame_cache **) cache_ptr;

  epiphany_frame_cache (this_frame, this_cache);

  return trad_frame_get_this_base (*this_cache);

}	/* epiphany_frame_base_address() */


/*----------------------------------------------------------------------------*/
/*! The Epiphany frame base sniffer data structure.

    This struct identifies our family of frame base sniffing functions.      */
/*----------------------------------------------------------------------------*/
static const struct frame_base epiphany_frame_base =
{
  .unwind      = &epiphany_frame_unwind,
  .this_base   = epiphany_frame_base_address,
  .this_locals = epiphany_frame_base_address,
  .this_args   = epiphany_frame_base_address
};


/*----------------------------------------------------------------------------*/
/*! The Epiphany frame base sniffer function

    See if we are suitable for sniffing frame bases.

    @param[in] this_frame  THIS frame we are sniffing.

    @return  Pointer to a frame base sniffer data structure if we are
             suitable, or NULL otherwise.                                    */
/*----------------------------------------------------------------------------*/
static const struct frame_base *
epiphany_frame_base_sniffer (struct frame_info *this_frame)
{
  if (epiphany_frame_sniffer (&epiphany_frame_unwind, this_frame, NULL))
    {
      return &epiphany_frame_base;
    }
  else
    {
      return NULL;
    }
}	/* epiphany_frame_base_sniffer () */


/*----------------------------------------------------------------------------*/
/*! Architecture initialization for Epiphany

    Looks for a candidate architecture in the list of architectures supplied
    using the info supplied. If none match, create a new architecture.

    @param[in] info    Information about the target architecture
    @param[in] arches  The list of currently know architectures

    @return  A structure describing the target architecture                  */
/*----------------------------------------------------------------------------*/
static struct gdbarch *
epiphany_gdbarch_init (struct gdbarch_info  info,
		       struct gdbarch_list *arches)
{
  static struct frame_base     epiphany_frame_base;
  struct        gdbarch       *gdbarch;
  const struct  bfd_arch_info *binfo;

  /* Find a candidate among the list of pre-declared architectures.  */
  arches = gdbarch_list_lookup_by_info (arches, &info);
  if (NULL != arches)
    {
      return arches->gdbarch;
    }

  /* None found, create a new architecture from the information provided. In
     this version there is no architecture dependent info, so we set the
     second argument to gdbarch_alloc to NULL. Nor is there any architecture
     dependent data, so we make no use of the various gdbarch_data
     functions. */
  binfo   = info.bfd_arch_info;
  gdbarch = gdbarch_alloc (&info, NULL);

  /* Specify architecture in the sequence given in the definition of
     gdbarch.c */
  set_gdbarch_short_bit              (gdbarch, 16);
  set_gdbarch_int_bit                (gdbarch, 32);
  set_gdbarch_long_bit               (gdbarch, 32);
  set_gdbarch_long_long_bit          (gdbarch, 64);
  set_gdbarch_float_bit              (gdbarch, 32);
  set_gdbarch_float_format           (gdbarch, floatformats_ieee_single);
  set_gdbarch_double_bit             (gdbarch, 64);
  set_gdbarch_double_format          (gdbarch, floatformats_ieee_double);
  set_gdbarch_long_double_bit        (gdbarch, 64);
  set_gdbarch_long_double_format     (gdbarch, floatformats_ieee_double);
  set_gdbarch_ptr_bit                (gdbarch, binfo->bits_per_address);
  set_gdbarch_addr_bit               (gdbarch, binfo->bits_per_address);
  set_gdbarch_char_signed            (gdbarch, 0);
  /* No need for custom read_pc or write_pc */
  set_gdbarch_virtual_frame_pointer  (gdbarch, epiphany_virtual_frame_pointer);
  set_gdbarch_pseudo_register_read   (gdbarch, epiphany_pseudo_register_read);
  set_gdbarch_pseudo_register_write  (gdbarch, epiphany_pseudo_register_write);
  set_gdbarch_num_regs               (gdbarch, EPIPHANY_NUM_REGS);
  set_gdbarch_num_pseudo_regs        (gdbarch, EPIPHANY_NUM_PSEUDO_REGS);
  /* No need for ax_pseudo_register_collect or ax_pseudo_register_push_stack */
  set_gdbarch_sp_regnum              (gdbarch, EPIPHANY_SP_REGNUM);
  set_gdbarch_pc_regnum              (gdbarch, EPIPHANY_PC_REGNUM);
  set_gdbarch_ps_regnum              (gdbarch, EPIPHANY_SR_REGNUM);
  /* No need for fp0_regnum (we don't have separate FP regs */
  /* No need for stab_reg_to_regnum, ecoff_reg_to_regnum, sdb_reg_to_regnum,
     dwarf2_reg_to_regnum. Default mappings are sufficient. */
  set_gdbarch_register_name          (gdbarch, epiphany_register_name);
  set_gdbarch_register_type          (gdbarch, epiphany_register_type);
  set_gdbarch_dummy_id               (gdbarch, epiphany_dummy_id);
  /* deprecated_fp_regnum is no longer used. */
  set_gdbarch_push_dummy_call        (gdbarch, epiphany_push_dummy_call);
  /* call_dummy_location is now superceded by push_dummy_code */
  /* We don't need push_dummy_code, since we are always debugging writable
     code (i.e., not in ROM). */
  set_gdbarch_print_registers_info   (gdbarch, epiphany_print_registers_info);
  set_gdbarch_print_float_info       (gdbarch, epiphany_print_float_info);
  /* No need for print_vector_info (no vector ops) */
  /* No need for register_sim_regno (default mapping suffices). */
  /* No need for cannot_fetch_register (all registers readable by GDB. */
  set_gdbarch_cannot_store_register  (gdbarch, epiphany_cannot_store_register);
  set_gdbarch_get_longjmp_target     (gdbarch, epiphany_get_longjmp_target);
  set_gdbarch_believe_pcc_promotion  (gdbarch, 1);
  /* No need for convert_register_p, register_to_value or value_to_register,
     since values always have the same representation in memory as regs. */
  /* No need for pointer_to_address or address_to_pointer, since pointers and
     addresses have the same representation. */
  /* No need for integer_to_address, since there is no special conversion
     between values as integers and pointers. */
  set_gdbarch_return_value           (gdbarch, epiphany_return_value);
  set_gdbarch_skip_prologue          (gdbarch, epiphany_skip_prologue);
  /* We don't implement skip_main_prologue. It is not documented, and few
     architectures implement it. */
  set_gdbarch_inner_than             (gdbarch, core_addr_lessthan);
  set_gdbarch_breakpoint_from_pc     (gdbarch, epiphany_breakpoint_from_pc);
  /* We don't have to adjust breakpoint addresses for remote targets, so don't
     need remote_breakpoint_from_pc. */
  /* No need for adjust_breakpoint_address, since breakpoints can safely be
     placed anywhere. */
  /* Default implementations of memory_insert_breakpoint and
     memory_remove_breakpoint are sufficient. */
  set_gdbarch_decr_pc_after_break (gdbarch, EPIPHANY_BKPT_INSTLEN);
  /* No gdbarch_deprecated_function_start_offset for since we fully support
     function pointers and entry points (they are the same at present */
  /* No need for remote_register_number, default identity mapping suffices. */
  /* No need for fetch_tls_load_module_address with a bare metal target. */
  set_gdbarch_frame_args_skip        (gdbarch, 0);
  set_gdbarch_unwind_pc              (gdbarch, epiphany_unwind_pc);
  set_gdbarch_unwind_sp              (gdbarch, epiphany_unwind_sp);
  /* No need for frame_num_args, default (unknown number) suffices. */
  set_gdbarch_frame_align            (gdbarch, epiphany_frame_align);
  /* We don't implement gdbarch_stabs_argument_has_addr, since composite types
     are passed by value if small and by reference if large of undefined in
     size. This function can only give a per-type answer, so we'll have to
     leave it as it is (treat them all as call-by-value).

     @todo Fix this upstream with a more nuanced version of this function. */
  set_gdbarch_frame_red_zone_size    (gdbarch, EPIPHANY_FRAME_RED_ZONE_SIZE);
  /* No need for convert_from_func_ptr_addr - they are the same thing. */
  /* No need for addr_bits_remove or smash_text_address. All bits are used. */
  set_gdbarch_software_single_step   (gdbarch, epiphany_software_single_step);
  /* No need for single_step_through_delay with no delayed branches. */
  set_gdbarch_print_insn             (gdbarch, print_insn_epiphany);
  set_gdbarch_skip_trampoline_code   (gdbarch, epiphany_skip_trampoline_code);
  /* No need for skip_solib_resolver or in_solib_return_trampoline, since no
     shared objects. */
  set_gdbarch_stack_frame_destroyed_p (gdbarch, epiphany_stack_frame_destroyed_p);
  /* No need for elf_make_msymbol_special or coff_make_msymbol_special, since
     we have no special symbols. */
  /* No need for cannot_step_breakpoint, since we can step breakpoints. */
  /* No need for have_nonsteppable_watchpoint, since we only have software
     (write) watchpoints in Epiphany. */
  /* We don't implement address_class_type_flags,
     address_class_type_flags_to_name or address_class_name_to_type_flags,
     since we have no address classes.

     @todo This might be a useful mechanism for distinquishing between on-chip
           and off-chip memory in the future. */
  set_gdbarch_register_reggroup_p    (gdbarch, epiphany_register_reggroup_p);
  /* No need for fetch_pointer_argument, since args are not passed by ref. */
  /* No need for regset_from_core_section, core_regset_sections,
     core_xfer_shared_libraries, core_pid_to_str or gcore_bfd_target, since
     core debugging is not supported. */
  /* No need for vtable_function_descriptors, since C++ vtable elements are
     normal function pointers. */
  /* No need for vbit_in_delta, since we can us the LS bit of th pfn. */
  /* We think can get away without skip_permanent_breakpoint.

     @todo We need to check this. If a user has BKPT in their program, will we
           do the right thing? */
  set_gdbarch_max_insn_length        (gdbarch, EPIPHANY_MAX_INST_SIZE);
  /* For now we don't support displaced stepping, so we don't implement
     displaced_step_copy_insn, displaced_step_hw_singlestep,
     displaced_step_fixup, displaced_step_free_closure,
     displaced_step_location or relocate_instruction. However we may need
     non-stop mode in the future, which will require implementing this.

     @todo Consider implementing displaced stepping. */
  /* No need for overlay_update, since we don't support overlays. */
  /* No need for core_read_description, since we don't support cores. */
  /* No need for static_transform_name, since we don't have a special
     encoding of static variables in STABS. */
  /* No need for sofun_address_maybe_missing, since we do not have zero
     addresses in N_SO or N_FUN in STABS. */
  /* For now we do not support process recording (and hence reverse
     execution), so we do not implement process_record or
     process_record_signal.

     @todo Consider implementing process recording in the future. */
  /* No need for target_signal_from_host or target_signal_to_host, since the
     default signal mapping is suitable. */
  /* No need for get_siginfo_type, since no additional signal info. */
  /* We haven't implemented record_special_symbol. Its purpose is not
     documented, and it is only used in one architecture (ARM). */
  /* No need for get_syscall_number in the absence of special syscalls. */
  /* No need for has_global_solist in the absence of shared object libraries. */
  /* No need for has_global_breakpoints, since we don't have multiple address
     spaces. */
  /* We don't implement has_shared_address_space, since no other architecture
     does. However it might be useful if we use multiple inferiors to address
     different cores.

     @todo Consider using has_shared_address_space. */
  /* No need for fast_tracepoint_valid_at, since we have no tracepoints. */
  /* No need for auto_charset and auto_wide_charset, since these only really
     have any implication in cygwin specific worlds. */
  /* No need for solib_symbols_extension, since we have no shared objects. */
  /* No need for has_dos_based_file_system, since we don't. */

  /* Functions to unwind frames and sniff for frame bases. We try DWARF2
     first, then our hand-written tool. We'd like a STABS one, but no one has
     written one. */
  dwarf2_append_unwinders (gdbarch);
  frame_unwind_append_unwinder (gdbarch, &epiphany_frame_unwind);
  frame_base_append_sniffer (gdbarch, dwarf2_frame_base_sniffer);
  frame_base_append_sniffer (gdbarch, epiphany_frame_base_sniffer);

  return gdbarch;

}	/* epiphany_gdbarch_init() */


/*----------------------------------------------------------------------------*/
/*! Dump the target specific data for this architecture

    The current implementation has no target specific architectural
    information (it does not set the tdep field of gdbarch). For now just
    print out a message.

    @todo  We may wish to used the function gdbarch_tdep () to get a copy of
           the target dependent data.

   @param[in] gdbarch  The architecture of interest
   @param[in] file     Where to dump the data */
/*----------------------------------------------------------------------------*/
static void
epiphany_dump_tdep (struct gdbarch *gdbarch,
		    struct ui_file *file)
{
  fprintf_unfiltered (file, "The Epiphany has no target specific data\n");

}	/* epiphany_dump_tdep() */


/*! Value of the core ID requested by "set coreid" */
static unsigned  epiphany_tmp_coreid;

/* Value of the core ID that will actually be used. Values out of range are
   ignored. */
static unsigned  epiphany_coreid;


/*----------------------------------------------------------------------------*/
/*! Set the Epiphany coreID.

    The value passed should be an unsigned integer less than MAX_CORES.

    @param[in] args      The arguments to the command
    @param[in] from_tty  Non-zero if we are connected to a TTY.
    @param[in] c         The command structure

    Register commands to set and show the coreid.                             */
/*----------------------------------------------------------------------------*/
static void
epiphany_set_coreid (char                    *args,
		     int                      from_tty,
		     struct cmd_list_element *c)
{
  /* Ensure the value is valid. */
  if (epiphany_tmp_coreid >= MAX_CORES)
    {
      /* Invalid values are ignored. We set the value to the previous value,
	 so the default "show" function will work cleanly. */
      epiphany_tmp_coreid = epiphany_coreid;
      error (_("Core ID too large - ignored"));
    }
  else if (epiphany_tmp_coreid != epiphany_coreid)
    {
      /* Only set a valid core ID if it has changed. Copy it to the actual
	 value. */
      char *coreid_str = (char *) xmalloc (strlen ("coreid:") + 9);

      epiphany_coreid = epiphany_tmp_coreid;
      sprintf (coreid_str, "coreid:%d", epiphany_coreid);
      register_remote_client_data (coreid_str);

      xfree (coreid_str);
    }
}	/* epiphany_set_coreid () */

extern initialize_file_ftype _initialize_epiphany_tdep; /*-Wmissing-prototypes*/

/*----------------------------------------------------------------------------*/
/*! Main entry point for target architecture initialization

    Initializes the architecture via registers_gdbarch_init().

    Register commands to set and show the core ID to be used in the remote
    target.                                                                   */
/*----------------------------------------------------------------------------*/
void
_initialize_epiphany_tdep (void)
{
  /* Register this architecture. Uses the BFD defined for this architecture. */
  gdbarch_register (bfd_arch_epiphany, epiphany_gdbarch_init,
		    epiphany_dump_tdep);

  /* Allow "set coreid" and "show coreid". Zero means zero (rather than
     unlimited), and the value must be positive. Default "show" function will
     suffice, but we must control the setting.*/
  add_setshow_zuinteger_cmd ("coreid", class_obscure, &epiphany_tmp_coreid,
			     _("Set target coreid."),
			     _("Show target coreid."),
			     _("Specify the core to use in the target."),
			     epiphany_set_coreid, NULL,
			     &setlist, &showlist);
  /* Set the coreID defaults. */
  epiphany_coreid = 0;
  register_remote_client_data ("coreid:0");

}	/* _initialize_epiphany_tdep() */
