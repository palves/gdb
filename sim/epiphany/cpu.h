/* CPU family header for epiphanybf.

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

#ifndef CPU_EPIPHANYBF_H
#define CPU_EPIPHANYBF_H

/* Maximum number of instructions that are fetched at a time.
   This is for LIW type instructions sets (e.g. m32r).  */
#define MAX_LIW_INSNS 1

/* Maximum number of instructions that can be executed in parallel.  */
#define MAX_PARALLEL_INSNS 1

/* The size of an "int" needed to hold an instruction word.
   This is usually 32 bits, but some architectures needs 64 bits.  */
typedef CGEN_INSN_INT CGEN_INSN_WORD;

#include "cgen-engine.h"

/* CPU state information.  */
typedef struct {
  /* Hardware elements.  */
  struct {
  /* all addressable registers */
  SI h_all_registers[512];
#define GET_H_ALL_REGISTERS(a1) CPU (h_all_registers)[a1]
#define SET_H_ALL_REGISTERS(index, x) \
do { \
{\
if ((((index)) == (H_REG_SCR_CONFIG))) {\
epiphanybf_set_config (current_cpu, (x));\
}\
 else if ((((index)) == (H_REG_SCR_STATUS))) {\
epiphanybf_set_status (current_cpu, (x));\
}\
 else if ((((index)) == (H_REG_SCR_IMASK))) {\
epiphanybf_set_imask (current_cpu, (x));\
}\
 else if ((((index)) == (H_REG_SCR_ILATST))) {\
epiphanybf_set_ilatst (current_cpu, (x));\
}\
 else if ((((index)) == (H_REG_SCR_ILATCL))) {\
epiphanybf_set_ilatcl (current_cpu, (x));\
}\
 else if ((((index)) == (H_REG_MESH_RESETCORE))) {\
epiphanybf_set_resetcore (current_cpu, (x));\
}\
 else {\
CPU (h_all_registers[(index)]) = (x);\
}\
}\
;} while (0)
  /* memory effective address */
  SI h_memaddr;
#define GET_H_MEMADDR() CPU (h_memaddr)
#define SET_H_MEMADDR(x) (CPU (h_memaddr) = (x))
  } hardware;
#define CPU_CGEN_HW(cpu) (& (cpu)->cpu_data.hardware)
} EPIPHANYBF_CPU_DATA;

/* Virtual regs.  */

#define GET_H_REGISTERS(index) CPU (h_all_registers[index])
#define SET_H_REGISTERS(index, x) \
do { \
SET_H_ALL_REGISTERS ((index), (x));\
;} while (0)
#define GET_H_FPREGISTERS(index) SUBWORDSISF (CPU (h_all_registers[index]))
#define SET_H_FPREGISTERS(index, x) \
do { \
SET_H_ALL_REGISTERS ((index), SUBWORDSFSI ((x)));\
;} while (0)
#define GET_H_PC() CPU (h_all_registers[H_REG_SCR_PC])
#define SET_H_PC(x) \
do { \
SET_H_ALL_REGISTERS (H_REG_SCR_PC, (x));\
;} while (0)
#define GET_H_CORE_REGISTERS(index) CPU (h_all_registers[ADDSI (H_REG_GRP_SCR_OFFSET, index)])
#define SET_H_CORE_REGISTERS(index, x) \
do { \
SET_H_ALL_REGISTERS (ADDSI (H_REG_GRP_SCR_OFFSET, (index)), (x));\
;} while (0)
#define GET_H_CAIBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_CAIBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_CAIBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_CAIBIT, (x));\
;} while (0)
#define GET_H_GIDISABLEBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_GIDISABLEBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_GIDISABLEBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_GIDISABLEBIT, (x));\
;} while (0)
#define GET_H_KMBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_KMBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_KMBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_KMBIT, (x));\
;} while (0)
#define GET_H_SFLAGBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_SFLAGBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_SFLAGBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_SFLAGBIT, (x));\
;} while (0)
#define GET_H_ZBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_ZBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_ZBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_ZBIT, (x));\
;} while (0)
#define GET_H_NBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_NBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_NBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_NBIT, (x));\
;} while (0)
#define GET_H_CBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_CBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_CBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_CBIT, (x));\
;} while (0)
#define GET_H_VBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_VBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_VBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_VBIT, (x));\
;} while (0)
#define GET_H_BZBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_BZBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_BZBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_BZBIT, (x));\
;} while (0)
#define GET_H_BNBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_BNBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_BNBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_BNBIT, (x));\
;} while (0)
#define GET_H_BVBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_BVBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_BVBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_BVBIT, (x));\
;} while (0)
#define GET_H_BCBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_BCBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_BCBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_BCBIT, (x));\
;} while (0)
#define GET_H_VSBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_VSBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_VSBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_VSBIT, (x));\
;} while (0)
#define GET_H_BISBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_BISBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_BISBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_BISBIT, (x));\
;} while (0)
#define GET_H_BVSBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_BVSBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_BVSBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_BVSBIT, (x));\
;} while (0)
#define GET_H_BUSBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_BUSBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_BUSBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_BUSBIT, (x));\
;} while (0)
#define GET_H_EXCAUSE0BIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_EXCAUSE0BIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_EXCAUSE0BIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_EXCAUSE0BIT, (x));\
;} while (0)
#define GET_H_EXCAUSE1BIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_EXCAUSE1BIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_EXCAUSE1BIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_EXCAUSE1BIT, (x));\
;} while (0)
#define GET_H_EXCAUSE2BIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_EXCAUSE2BIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_EXCAUSE2BIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_EXCAUSE2BIT, (x));\
;} while (0)
#define GET_H_EXCAUSE3BIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_STATUS]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_STATUS_EXCAUSE3BIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_EXCAUSE3BIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_STATUS, H_SCR_STATUS_EXCAUSE3BIT, (x));\
;} while (0)
#define GET_H_SCR_STATUS_EXCAUSE() ({   USI tmp_status;\
  tmp_status = CPU (h_all_registers[H_REG_SCR_STATUS]);\
; ANDSI (SRLSI (tmp_status, H_SCR_STATUS_EXCAUSE0BIT), 15); })
#define SET_H_SCR_STATUS_EXCAUSE(x) \
do { \
{\
  USI tmp_mask;\
  USI tmp_shifted;\
  tmp_mask = 0xfff0ffff;\
  tmp_shifted = SLLQI (ANDQI ((x), 15), H_SCR_STATUS_EXCAUSE0BIT);\
AND_REG_ATOMIC (H_REG_SCR_STATUS, tmp_mask);\
OR_REG_ATOMIC (H_REG_SCR_STATUS, tmp_shifted);\
}\
;} while (0)
#define GET_H_TRMBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TRMBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TRMBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TRMBIT, (x));\
;} while (0)
#define GET_H_INVEXCENBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_INVEXCENBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_INVEXCENBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_INVEXCENBIT, (x));\
;} while (0)
#define GET_H_OVFEXCENBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_OVFEXCENBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_OVFEXCENBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_OVFEXCENBIT, (x));\
;} while (0)
#define GET_H_UNEXCENBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_UNEXCENBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_UNEXCENBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_UNEXCENBIT, (x));\
;} while (0)
#define GET_H_TIMER0BIT0() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER0BIT0), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER0BIT0(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER0BIT0, (x));\
;} while (0)
#define GET_H_TIMER0BIT1() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER0BIT1), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER0BIT1(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER0BIT1, (x));\
;} while (0)
#define GET_H_TIMER0BIT2() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER0BIT2), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER0BIT2(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER0BIT2, (x));\
;} while (0)
#define GET_H_TIMER0BIT3() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER0BIT3), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER0BIT3(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER0BIT3, (x));\
;} while (0)
#define GET_H_TIMER1BIT0() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER1BIT0), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER1BIT0(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER1BIT0, (x));\
;} while (0)
#define GET_H_TIMER1BIT1() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER1BIT1), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER1BIT1(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER1BIT1, (x));\
;} while (0)
#define GET_H_TIMER1BIT2() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER1BIT2), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER1BIT2(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER1BIT2, (x));\
;} while (0)
#define GET_H_TIMER1BIT3() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_TIMER1BIT3), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_TIMER1BIT3(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_TIMER1BIT3, (x));\
;} while (0)
#define GET_H_ARITHMETIC_MODEBIT0() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_ARITHMETIC_MODEBIT0), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_ARITHMETIC_MODEBIT0(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_ARITHMETIC_MODEBIT0, (x));\
;} while (0)
#define GET_H_ARITHMETIC_MODEBIT1() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_ARITHMETIC_MODEBIT1), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_ARITHMETIC_MODEBIT1(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_ARITHMETIC_MODEBIT1, (x));\
;} while (0)
#define GET_H_ARITHMETIC_MODEBIT2() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_ARITHMETIC_MODEBIT2), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_ARITHMETIC_MODEBIT2(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_ARITHMETIC_MODEBIT2, (x));\
;} while (0)
#define GET_H_CLOCKGATEENBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_CLOCKGATEENBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_CLOCKGATEENBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_CLOCKGATEENBIT, (x));\
;} while (0)
#define GET_H_MBKPTENBIT() ({   USI tmp_regval;\
  USI tmp_bitval;\
  tmp_regval = CPU (h_all_registers[H_REG_SCR_CONFIG]);\
;   tmp_bitval = ANDSI (SRLSI (tmp_regval, H_SCR_CONFIG_MBKPTENBIT), 1);\
; TRUNCSIBI (tmp_bitval); })
#define SET_H_MBKPTENBIT(x) \
do { \
SET_REG_BIT_ATOMIC (H_REG_SCR_CONFIG, H_SCR_CONFIG_MBKPTENBIT, (x));\
;} while (0)
#define GET_H_COREDMA_REGISTERS(index) CPU (h_all_registers[ADDSI (H_REG_GRP_DMA_OFFSET, index)])
#define SET_H_COREDMA_REGISTERS(index, x) \
do { \
SET_H_ALL_REGISTERS (ADDSI (H_REG_GRP_DMA_OFFSET, (index)), (x));\
;} while (0)
#define GET_H_COREMEM_REGISTERS(index) CPU (h_all_registers[ADDSI (H_REG_GRP_MEM_OFFSET, index)])
#define SET_H_COREMEM_REGISTERS(index, x) \
do { \
SET_H_ALL_REGISTERS (ADDSI (H_REG_GRP_MEM_OFFSET, (index)), (x));\
;} while (0)
#define GET_H_COREMESH_REGISTERS(index) CPU (h_all_registers[ADDSI (H_REG_GRP_MESH_OFFSET, index)])
#define SET_H_COREMESH_REGISTERS(index, x) \
do { \
SET_H_ALL_REGISTERS (ADDSI (H_REG_GRP_MESH_OFFSET, (index)), (x));\
;} while (0)

/* Cover fns for register access.  */
SI epiphanybf_h_all_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_all_registers_set (SIM_CPU *, UINT, SI);
SI epiphanybf_h_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_registers_set (SIM_CPU *, UINT, SI);
SF epiphanybf_h_fpregisters_get (SIM_CPU *, UINT);
void epiphanybf_h_fpregisters_set (SIM_CPU *, UINT, SF);
USI epiphanybf_h_pc_get (SIM_CPU *);
void epiphanybf_h_pc_set (SIM_CPU *, USI);
SI epiphanybf_h_memaddr_get (SIM_CPU *);
void epiphanybf_h_memaddr_set (SIM_CPU *, SI);
USI epiphanybf_h_core_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_core_registers_set (SIM_CPU *, UINT, USI);
BI epiphanybf_h_caibit_get (SIM_CPU *);
void epiphanybf_h_caibit_set (SIM_CPU *, BI);
BI epiphanybf_h_gidisablebit_get (SIM_CPU *);
void epiphanybf_h_gidisablebit_set (SIM_CPU *, BI);
BI epiphanybf_h_kmbit_get (SIM_CPU *);
void epiphanybf_h_kmbit_set (SIM_CPU *, BI);
BI epiphanybf_h_sflagbit_get (SIM_CPU *);
void epiphanybf_h_sflagbit_set (SIM_CPU *, BI);
BI epiphanybf_h_zbit_get (SIM_CPU *);
void epiphanybf_h_zbit_set (SIM_CPU *, BI);
BI epiphanybf_h_nbit_get (SIM_CPU *);
void epiphanybf_h_nbit_set (SIM_CPU *, BI);
BI epiphanybf_h_cbit_get (SIM_CPU *);
void epiphanybf_h_cbit_set (SIM_CPU *, BI);
BI epiphanybf_h_vbit_get (SIM_CPU *);
void epiphanybf_h_vbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bzbit_get (SIM_CPU *);
void epiphanybf_h_bzbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bnbit_get (SIM_CPU *);
void epiphanybf_h_bnbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bvbit_get (SIM_CPU *);
void epiphanybf_h_bvbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bcbit_get (SIM_CPU *);
void epiphanybf_h_bcbit_set (SIM_CPU *, BI);
BI epiphanybf_h_vsbit_get (SIM_CPU *);
void epiphanybf_h_vsbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bisbit_get (SIM_CPU *);
void epiphanybf_h_bisbit_set (SIM_CPU *, BI);
BI epiphanybf_h_bvsbit_get (SIM_CPU *);
void epiphanybf_h_bvsbit_set (SIM_CPU *, BI);
BI epiphanybf_h_busbit_get (SIM_CPU *);
void epiphanybf_h_busbit_set (SIM_CPU *, BI);
BI epiphanybf_h_excause0bit_get (SIM_CPU *);
void epiphanybf_h_excause0bit_set (SIM_CPU *, BI);
BI epiphanybf_h_excause1bit_get (SIM_CPU *);
void epiphanybf_h_excause1bit_set (SIM_CPU *, BI);
BI epiphanybf_h_excause2bit_get (SIM_CPU *);
void epiphanybf_h_excause2bit_set (SIM_CPU *, BI);
BI epiphanybf_h_excause3bit_get (SIM_CPU *);
void epiphanybf_h_excause3bit_set (SIM_CPU *, BI);
UQI epiphanybf_h_scr_status_excause_get (SIM_CPU *);
void epiphanybf_h_scr_status_excause_set (SIM_CPU *, UQI);
BI epiphanybf_h_trmbit_get (SIM_CPU *);
void epiphanybf_h_trmbit_set (SIM_CPU *, BI);
BI epiphanybf_h_invexcenbit_get (SIM_CPU *);
void epiphanybf_h_invexcenbit_set (SIM_CPU *, BI);
BI epiphanybf_h_ovfexcenbit_get (SIM_CPU *);
void epiphanybf_h_ovfexcenbit_set (SIM_CPU *, BI);
BI epiphanybf_h_unexcenbit_get (SIM_CPU *);
void epiphanybf_h_unexcenbit_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit0_get (SIM_CPU *);
void epiphanybf_h_timer0bit0_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit1_get (SIM_CPU *);
void epiphanybf_h_timer0bit1_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit2_get (SIM_CPU *);
void epiphanybf_h_timer0bit2_set (SIM_CPU *, BI);
BI epiphanybf_h_timer0bit3_get (SIM_CPU *);
void epiphanybf_h_timer0bit3_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit0_get (SIM_CPU *);
void epiphanybf_h_timer1bit0_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit1_get (SIM_CPU *);
void epiphanybf_h_timer1bit1_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit2_get (SIM_CPU *);
void epiphanybf_h_timer1bit2_set (SIM_CPU *, BI);
BI epiphanybf_h_timer1bit3_get (SIM_CPU *);
void epiphanybf_h_timer1bit3_set (SIM_CPU *, BI);
BI epiphanybf_h_arithmetic_modebit0_get (SIM_CPU *);
void epiphanybf_h_arithmetic_modebit0_set (SIM_CPU *, BI);
BI epiphanybf_h_arithmetic_modebit1_get (SIM_CPU *);
void epiphanybf_h_arithmetic_modebit1_set (SIM_CPU *, BI);
BI epiphanybf_h_arithmetic_modebit2_get (SIM_CPU *);
void epiphanybf_h_arithmetic_modebit2_set (SIM_CPU *, BI);
BI epiphanybf_h_clockgateenbit_get (SIM_CPU *);
void epiphanybf_h_clockgateenbit_set (SIM_CPU *, BI);
BI epiphanybf_h_mbkptenbit_get (SIM_CPU *);
void epiphanybf_h_mbkptenbit_set (SIM_CPU *, BI);
USI epiphanybf_h_coredma_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_coredma_registers_set (SIM_CPU *, UINT, USI);
USI epiphanybf_h_coremem_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_coremem_registers_set (SIM_CPU *, UINT, USI);
USI epiphanybf_h_coremesh_registers_get (SIM_CPU *, UINT);
void epiphanybf_h_coremesh_registers_set (SIM_CPU *, UINT, USI);

/* These must be hand-written.  */
extern CPUREG_FETCH_FN epiphanybf_fetch_register;
extern CPUREG_STORE_FN epiphanybf_store_register;

typedef struct {
  int empty;
} MODEL_EPIPHANY32_DATA;

/* Instruction argument buffer.  */

union sem_fields {
  struct { /* no operands */
    int empty;
  } sfmt_empty;
  struct { /*  */
    UINT f_trap_num;
    unsigned char out_h_registers_SI_0;
  } sfmt_trap16;
  struct { /*  */
    IADDR i_simm24;
    unsigned char out_h_registers_SI_14;
  } sfmt_bl;
  struct { /*  */
    IADDR i_simm8;
    unsigned char out_h_registers_SI_14;
  } sfmt_bl16;
  struct { /*  */
    ADDR i_imm8;
    UINT f_rd;
    unsigned char out_rd;
  } sfmt_mov8;
  struct { /*  */
    UINT f_rd6;
    UINT f_sn6;
    unsigned char out_rd6;
  } sfmt_movfs6;
  struct { /*  */
    UINT f_rd;
    UINT f_sn;
    unsigned char out_rd;
  } sfmt_movfs16;
  struct { /*  */
    UINT f_rd6;
    UINT f_sn6;
    unsigned char in_rd6;
  } sfmt_movts6;
  struct { /*  */
    UINT f_rd;
    UINT f_sn;
    unsigned char in_rd;
  } sfmt_movts16;
  struct { /*  */
    UINT f_rn6;
    unsigned char in_rn6;
    unsigned char out_h_registers_SI_14;
  } sfmt_jalr;
  struct { /*  */
    UINT f_rn;
    unsigned char in_rn;
    unsigned char out_h_registers_SI_14;
  } sfmt_jalr16;
  struct { /*  */
    UINT f_rd6;
    UINT f_rn6;
    unsigned char in_frn6;
    unsigned char out_frd6;
  } sfmt_f_recipf32;
  struct { /*  */
    ADDR i_imm16;
    UINT f_rd6;
    unsigned char in_rd6;
    unsigned char out_rd6;
  } sfmt_movt;
  struct { /*  */
    UINT f_rd6;
    UINT f_rn6;
    UINT f_shift;
    unsigned char in_rd6;
    unsigned char in_rn6;
    unsigned char out_rd6;
  } sfmt_lsri32;
  struct { /*  */
    UINT f_rd;
    UINT f_rn;
    UINT f_shift;
    unsigned char in_rd;
    unsigned char in_rn;
    unsigned char out_rd;
  } sfmt_lsri16;
  struct { /*  */
    INT f_sdisp11;
    UINT f_rd6;
    UINT f_rn6;
    unsigned char in_rd6;
    unsigned char in_rn6;
    unsigned char out_rd6;
  } sfmt_addi;
  struct { /*  */
    INT f_sdisp3;
    UINT f_rd;
    UINT f_rn;
    unsigned char in_rd;
    unsigned char in_rn;
    unsigned char out_rd;
  } sfmt_addi16;
  struct { /*  */
    UINT f_disp3;
    UINT f_rd;
    UINT f_rn;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char in_rd;
    unsigned char in_rn;
  } sfmt_strdd16;
  struct { /*  */
    UINT f_disp3;
    UINT f_rd;
    UINT f_rn;
    unsigned char in_rn;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char out_rd;
  } sfmt_ldrdd16_s;
  struct { /*  */
    UINT f_rd;
    UINT f_rd6;
    UINT f_rn;
    unsigned char in_rd;
    unsigned char in_rn;
    unsigned char out_rd;
    unsigned char out_rd6;
  } sfmt_f_ixf16;
  struct { /*  */
    UINT f_rd;
    UINT f_rm;
    UINT f_rn;
    unsigned char in_rd;
    unsigned char in_rm;
    unsigned char in_rn;
    unsigned char out_rd;
  } sfmt_add16;
  struct { /*  */
    UINT f_disp11;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_subd;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char in_rd6;
    unsigned char in_rn6;
    unsigned char out_rn6;
  } sfmt_strddpm;
  struct { /*  */
    UINT f_rd;
    UINT f_rm;
    UINT f_rn;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char in_rd;
    unsigned char in_rm;
    unsigned char in_rn;
    unsigned char out_rn;
  } sfmt_strdp16;
  struct { /*  */
    UINT f_addsubx;
    UINT f_rd6;
    UINT f_rm6;
    UINT f_rn6;
    unsigned char in_rd6;
    unsigned char in_rm6;
    unsigned char in_rn6;
    unsigned char out_rd6;
  } sfmt_testsetbt;
  struct { /*  */
    UINT f_disp11;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_subd;
    unsigned char in_rn6;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char out_rd6;
    unsigned char out_rn6;
  } sfmt_ldrddpm_l;
  struct { /*  */
    UINT f_rd;
    UINT f_rm;
    UINT f_rn;
    unsigned char in_rm;
    unsigned char in_rn;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd_1;
    unsigned char out_rd;
    unsigned char out_rn;
  } sfmt_ldrdp16_s;
  struct { /*  */
    UINT f_addsubx;
    UINT f_rd6;
    UINT f_rm6;
    UINT f_rn6;
    unsigned char in_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char in_rd6;
    unsigned char in_rm6;
    unsigned char in_rn6;
    unsigned char out_rn6;
  } sfmt_strdp;
  struct { /*  */
    UINT f_addsubx;
    UINT f_rd6;
    UINT f_rm6;
    UINT f_rn6;
    unsigned char in_rm6;
    unsigned char in_rn6;
    unsigned char out_h_registers_SI_add__INT_index_of__INT_rd6_1;
    unsigned char out_rd6;
    unsigned char out_rn6;
  } sfmt_ldrdp_l;
#if WITH_SCACHE_PBB
  /* Writeback handler.  */
  struct {
    /* Pointer to argbuf entry for insn whose results need writing back.  */
    const struct argbuf *abuf;
  } write;
  /* x-before handler */
  struct {
    /*const SCACHE *insns[MAX_PARALLEL_INSNS];*/
    int first_p;
  } before;
  /* x-after handler */
  struct {
    int empty;
  } after;
  /* This entry is used to terminate each pbb.  */
  struct {
    /* Number of insns in pbb.  */
    int insn_count;
    /* Next pbb to execute.  */
    SCACHE *next;
    SCACHE *branch_target;
  } chain;
#endif
};

/* The ARGBUF struct.  */
struct argbuf {
  /* These are the baseclass definitions.  */
  IADDR addr;
  const IDESC *idesc;
  char trace_p;
  char profile_p;
  /* ??? Temporary hack for skip insns.  */
  char skip_count;
  char unused;
  /* cpu specific data follows */
  union sem semantic;
  int written;
  union sem_fields fields;
};

/* A cached insn.

   ??? SCACHE used to contain more than just argbuf.  We could delete the
   type entirely and always just use ARGBUF, but for future concerns and as
   a level of abstraction it is left in.  */

struct scache {
  struct argbuf argbuf;
};

/* Macros to simplify extraction, reading and semantic code.
   These define and assign the local vars that contain the insn's fields.  */

#define EXTRACT_IFMT_EMPTY_VARS \
  unsigned int length;
#define EXTRACT_IFMT_EMPTY_CODE \
  length = 0; \

#define EXTRACT_IFMT_BEQ16_VARS \
  SI f_simm8; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BEQ16_CODE \
  length = 2; \
  f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc)); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 16, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_BEQ_VARS \
  SI f_simm24; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BEQ_CODE \
  length = 4; \
  f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc)); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_JR16_VARS \
  UINT f_dc_15_3; \
  UINT f_rn; \
  UINT f_dc_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_JR16_CODE \
  length = 2; \
  f_dc_15_3 = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_JR_VARS \
  UINT f_dc_31_3; \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_dc_15_3; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_JR_CODE \
  length = 4; \
  f_dc_31_3 = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_dc_15_3 = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 32, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LDRBX16_S_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rm; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBX16_S_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3); \
  f_wordsize = EXTRACT_LSB0_UINT (insn, 16, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_LDRBX_L_VARS \
  UINT f_dc_22_1; \
  UINT f_dc_21_1; \
  UINT f_addsubx; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBX_L_CODE \
  length = 4; \
  f_dc_22_1 = EXTRACT_LSB0_UINT (insn, 32, 22, 1); \
  f_dc_21_1 = EXTRACT_LSB0_UINT (insn, 32, 21, 1); \
  f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_wordsize = EXTRACT_LSB0_UINT (insn, 32, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LDRBP_L_VARS \
  UINT f_dc_22_2; \
  UINT f_addsubx; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBP_L_CODE \
  length = 4; \
  f_dc_22_2 = EXTRACT_LSB0_UINT (insn, 32, 22, 2); \
  f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_wordsize = EXTRACT_LSB0_UINT (insn, 32, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LDRBD16_S_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_disp3; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBD16_S_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3); \
  f_wordsize = EXTRACT_LSB0_UINT (insn, 16, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_LDRBD_L_VARS \
  UINT f_pm; \
  UINT f_subd; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_disp3; \
  UINT f_disp8; \
  UINT f_disp11; \
  UINT f_wordsize; \
  UINT f_store; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LDRBD_L_CODE \
  length = 4; \
  f_pm = EXTRACT_LSB0_UINT (insn, 32, 25, 1); \
  f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
  f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8); \
{\
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));\
}\
  f_wordsize = EXTRACT_LSB0_UINT (insn, 32, 6, 2); \
  f_store = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_CMOV16EQ_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_CMOV16EQ_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 16, 8, 1); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 16, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_CMOVEQ_VARS \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_condcode; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_CMOVEQ_CODE \
  length = 4; \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_condcode = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTS16_VARS \
  UINT f_rd; \
  UINT f_sn; \
  UINT f_dc_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTS16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_MOVTS6_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTS6_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTSDMA_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTSDMA_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTSMEM_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTSMEM_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOVTSMESH_VARS \
  UINT f_dc_25_4; \
  UINT f_dc_21_2; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_sn_x; \
  UINT f_sn; \
  UINT f_sn6; \
  UINT f_dc_9_1; \
  UINT f_opc_8_1; \
  UINT f_dc_7_4; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOVTSMESH_CODE \
  length = 4; \
  f_dc_25_4 = EXTRACT_LSB0_UINT (insn, 32, 25, 4); \
  f_dc_21_2 = EXTRACT_LSB0_UINT (insn, 32, 21, 2); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));\
}\
  f_dc_9_1 = EXTRACT_LSB0_UINT (insn, 32, 9, 1); \
  f_opc_8_1 = EXTRACT_LSB0_UINT (insn, 32, 8, 1); \
  f_dc_7_4 = EXTRACT_LSB0_UINT (insn, 32, 7, 4); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_NOP_VARS \
  UINT f_dc_15_7; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_NOP_CODE \
  length = 2; \
  f_dc_15_7 = EXTRACT_LSB0_UINT (insn, 16, 15, 7); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_UNIMPL_VARS \
  UINT f_opc_31_32; \
  unsigned int length;
#define EXTRACT_IFMT_UNIMPL_CODE \
  length = 4; \
  f_opc_31_32 = EXTRACT_LSB0_UINT (insn, 32, 31, 32); \

#define EXTRACT_IFMT_GIEN_VARS \
  UINT f_dc_15_6; \
  UINT f_gien_gidis_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_GIEN_CODE \
  length = 2; \
  f_dc_15_6 = EXTRACT_LSB0_UINT (insn, 16, 15, 6); \
  f_gien_gidis_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_SWI_NUM_VARS \
  UINT f_trap_num; \
  UINT f_trap_swi_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_SWI_NUM_CODE \
  length = 2; \
  f_trap_num = EXTRACT_LSB0_UINT (insn, 16, 15, 6); \
  f_trap_swi_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_TRAP16_VARS \
  UINT f_trap_num; \
  UINT f_trap_swi_9_1; \
  UINT f_opc_8_5; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_TRAP16_CODE \
  length = 2; \
  f_trap_num = EXTRACT_LSB0_UINT (insn, 16, 15, 6); \
  f_trap_swi_9_1 = EXTRACT_LSB0_UINT (insn, 16, 9, 1); \
  f_opc_8_5 = EXTRACT_LSB0_UINT (insn, 16, 8, 5); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_ADD16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rm; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADD16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_ADD_VARS \
  UINT f_dc_22_3; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADD_CODE \
  length = 4; \
  f_dc_22_3 = EXTRACT_LSB0_UINT (insn, 32, 22, 3); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_ADDI16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  INT f_sdisp3; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADDI16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_sdisp3 = EXTRACT_LSB0_SINT (insn, 16, 9, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_ADDI_VARS \
  UINT f_dc_25_2; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_disp3; \
  UINT f_disp8; \
  INT f_sdisp11; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_ADDI_CODE \
  length = 4; \
  f_dc_25_2 = EXTRACT_LSB0_UINT (insn, 32, 25, 2); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
  f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8); \
{\
  f_sdisp11 = ((SI) (((((((f_disp8) << (3))) | (f_disp3))) << (21))) >> (21));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_LSRI16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LSRI16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_shift = EXTRACT_LSB0_UINT (insn, 16, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_LSRI32_VARS \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_LSRI32_CODE \
  length = 4; \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_shift = EXTRACT_LSB0_UINT (insn, 32, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_BITR16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BITR16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_shift = EXTRACT_LSB0_UINT (insn, 16, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_BITR_VARS \
  UINT f_dc_25_6; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_shift; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_BITR_CODE \
  length = 4; \
  f_dc_25_6 = EXTRACT_LSB0_UINT (insn, 32, 25, 6); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_shift = EXTRACT_LSB0_UINT (insn, 32, 9, 5); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_FEXT_VARS \
  UINT f_dc_22_2; \
  UINT f_dc_20_1; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rm_x; \
  UINT f_rm; \
  UINT f_rm6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_FEXT_CODE \
  length = 4; \
  f_dc_22_2 = EXTRACT_LSB0_UINT (insn, 32, 22, 2); \
  f_dc_20_1 = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3); \
  f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3); \
{\
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_MOV8_VARS \
  UINT f_rd; \
  UINT f_imm8; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOV8_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_imm8 = EXTRACT_LSB0_UINT (insn, 16, 12, 8); \
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 16, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_MOV16_VARS \
  UINT f_dc_28_1; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_imm8; \
  UINT f_imm_27_8; \
  UINT f_imm16; \
  UINT f_opc_4_1; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_MOV16_CODE \
  length = 4; \
  f_dc_28_1 = EXTRACT_LSB0_UINT (insn, 32, 28, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_imm8 = EXTRACT_LSB0_UINT (insn, 32, 12, 8); \
  f_imm_27_8 = EXTRACT_LSB0_UINT (insn, 32, 27, 8); \
{\
  f_imm16 = ((((f_imm_27_8) << (8))) | (f_imm8));\
}\
  f_opc_4_1 = EXTRACT_LSB0_UINT (insn, 32, 4, 1); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_F_ABSF16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rn; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_ABSF16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_F_ABSF32_VARS \
  UINT f_dc_22_3; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_ABSF32_CODE \
  length = 4; \
  f_dc_22_3 = EXTRACT_LSB0_UINT (insn, 32, 22, 3); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

#define EXTRACT_IFMT_F_LOATF16_VARS \
  UINT f_rd; \
  UINT f_rn; \
  UINT f_rn; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_LOATF16_CODE \
  length = 2; \
  f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3); \
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 16, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 16, 3, 4); \

#define EXTRACT_IFMT_F_RECIPF32_VARS \
  UINT f_dc_22_2; \
  UINT f_dc_20_1; \
  UINT f_opc_19_4; \
  UINT f_rd_x; \
  UINT f_rd; \
  UINT f_rd6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_rn_x; \
  UINT f_rn; \
  UINT f_rn6; \
  UINT f_opc_6_3; \
  UINT f_opc; \
  unsigned int length;
#define EXTRACT_IFMT_F_RECIPF32_CODE \
  length = 4; \
  f_dc_22_2 = EXTRACT_LSB0_UINT (insn, 32, 22, 2); \
  f_dc_20_1 = EXTRACT_LSB0_UINT (insn, 32, 20, 1); \
  f_opc_19_4 = EXTRACT_LSB0_UINT (insn, 32, 19, 4); \
  f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3); \
  f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3); \
{\
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3); \
  f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3); \
{\
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));\
}\
  f_opc_6_3 = EXTRACT_LSB0_UINT (insn, 32, 6, 3); \
  f_opc = EXTRACT_LSB0_UINT (insn, 32, 3, 4); \

/* Collection of various things for the trace handler to use.  */

typedef struct trace_record {
  IADDR pc;
  /* FIXME:wip */
} TRACE_RECORD;

#endif /* CPU_EPIPHANYBF_H */
