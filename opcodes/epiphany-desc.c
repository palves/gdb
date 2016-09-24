/* CPU data for epiphany.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright (C) 1996-2016 Free Software Foundation, Inc.

This file is part of the GNU Binutils and/or GDB, the GNU debugger.

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

#include "sysdep.h"
#include <stdio.h>
#include <stdarg.h>
#include "ansidecl.h"
#include "bfd.h"
#include "symcat.h"
#include "epiphany-desc.h"
#include "epiphany-opc.h"
#include "opintl.h"
#include "libiberty.h"
#include "xregex.h"

/* Attributes.  */

static const CGEN_ATTR_ENTRY bool_attr[] =
{
  { "#f", 0 },
  { "#t", 1 },
  { 0, 0 }
};

static const CGEN_ATTR_ENTRY MACH_attr[] ATTRIBUTE_UNUSED =
{
  { "base", MACH_BASE },
  { "epiphany32", MACH_EPIPHANY32 },
  { "max", MACH_MAX },
  { 0, 0 }
};

static const CGEN_ATTR_ENTRY ISA_attr[] ATTRIBUTE_UNUSED =
{
  { "epiphany", ISA_EPIPHANY },
  { "max", ISA_MAX },
  { 0, 0 }
};

const CGEN_ATTR_TABLE epiphany_cgen_ifield_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "PCREL-ADDR", &bool_attr[0], &bool_attr[0] },
  { "ABS-ADDR", &bool_attr[0], &bool_attr[0] },
  { "RESERVED", &bool_attr[0], &bool_attr[0] },
  { "SIGN-OPT", &bool_attr[0], &bool_attr[0] },
  { "SIGNED", &bool_attr[0], &bool_attr[0] },
  { "RELOC", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE epiphany_cgen_hardware_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "CACHE-ADDR", &bool_attr[0], &bool_attr[0] },
  { "PC", &bool_attr[0], &bool_attr[0] },
  { "PROFILE", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE epiphany_cgen_operand_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "PCREL-ADDR", &bool_attr[0], &bool_attr[0] },
  { "ABS-ADDR", &bool_attr[0], &bool_attr[0] },
  { "SIGN-OPT", &bool_attr[0], &bool_attr[0] },
  { "SIGNED", &bool_attr[0], &bool_attr[0] },
  { "NEGATIVE", &bool_attr[0], &bool_attr[0] },
  { "RELAX", &bool_attr[0], &bool_attr[0] },
  { "SEM-ONLY", &bool_attr[0], &bool_attr[0] },
  { "RELOC", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE epiphany_cgen_insn_attr_table[] =
{
  { "MACH", & MACH_attr[0], & MACH_attr[0] },
  { "ALIAS", &bool_attr[0], &bool_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "UNCOND-CTI", &bool_attr[0], &bool_attr[0] },
  { "COND-CTI", &bool_attr[0], &bool_attr[0] },
  { "SKIP-CTI", &bool_attr[0], &bool_attr[0] },
  { "DELAY-SLOT", &bool_attr[0], &bool_attr[0] },
  { "RELAXABLE", &bool_attr[0], &bool_attr[0] },
  { "RELAXED", &bool_attr[0], &bool_attr[0] },
  { "NO-DIS", &bool_attr[0], &bool_attr[0] },
  { "PBB", &bool_attr[0], &bool_attr[0] },
  { "SHORT-INSN", &bool_attr[0], &bool_attr[0] },
  { "IMM3", &bool_attr[0], &bool_attr[0] },
  { "IMM8", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

/* Instruction set variants.  */

static const CGEN_ISA epiphany_cgen_isa_table[] = {
  { "epiphany", 32, 32, 16, 32 },
  { 0, 0, 0, 0, 0 }
};

/* Machine variants.  */

static const CGEN_MACH epiphany_cgen_mach_table[] = {
  { "epiphany32", "epiphany32", MACH_EPIPHANY32, 0 },
  { 0, 0, 0, 0 }
};

static CGEN_KEYWORD_ENTRY epiphany_cgen_opval_all_reg_names_entries[] =
{
  { "NUM-REGS", 512, {0, {{{0, 0}}}}, 0, 0 },
  { "SP", 13, {0, {{{0, 0}}}}, 0, 0 },
  { "LR", 14, {0, {{{0, 0}}}}, 0, 0 },
  { "FP", 15, {0, {{{0, 0}}}}, 0, 0 },
  { "R0", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "R1", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "R2", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "R3", 3, {0, {{{0, 0}}}}, 0, 0 },
  { "R4", 4, {0, {{{0, 0}}}}, 0, 0 },
  { "R5", 5, {0, {{{0, 0}}}}, 0, 0 },
  { "R6", 6, {0, {{{0, 0}}}}, 0, 0 },
  { "R7", 7, {0, {{{0, 0}}}}, 0, 0 },
  { "R8", 8, {0, {{{0, 0}}}}, 0, 0 },
  { "R9", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "R10", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "R11", 11, {0, {{{0, 0}}}}, 0, 0 },
  { "R12", 12, {0, {{{0, 0}}}}, 0, 0 },
  { "R13", 13, {0, {{{0, 0}}}}, 0, 0 },
  { "R14", 14, {0, {{{0, 0}}}}, 0, 0 },
  { "R15", 15, {0, {{{0, 0}}}}, 0, 0 },
  { "R16", 16, {0, {{{0, 0}}}}, 0, 0 },
  { "R17", 17, {0, {{{0, 0}}}}, 0, 0 },
  { "R18", 18, {0, {{{0, 0}}}}, 0, 0 },
  { "R19", 19, {0, {{{0, 0}}}}, 0, 0 },
  { "R20", 20, {0, {{{0, 0}}}}, 0, 0 },
  { "R21", 21, {0, {{{0, 0}}}}, 0, 0 },
  { "R22", 22, {0, {{{0, 0}}}}, 0, 0 },
  { "R23", 23, {0, {{{0, 0}}}}, 0, 0 },
  { "R24", 24, {0, {{{0, 0}}}}, 0, 0 },
  { "R25", 25, {0, {{{0, 0}}}}, 0, 0 },
  { "R26", 26, {0, {{{0, 0}}}}, 0, 0 },
  { "R27", 27, {0, {{{0, 0}}}}, 0, 0 },
  { "R28", 28, {0, {{{0, 0}}}}, 0, 0 },
  { "R29", 29, {0, {{{0, 0}}}}, 0, 0 },
  { "R30", 30, {0, {{{0, 0}}}}, 0, 0 },
  { "R31", 31, {0, {{{0, 0}}}}, 0, 0 },
  { "R32", 32, {0, {{{0, 0}}}}, 0, 0 },
  { "R33", 33, {0, {{{0, 0}}}}, 0, 0 },
  { "R34", 34, {0, {{{0, 0}}}}, 0, 0 },
  { "R35", 35, {0, {{{0, 0}}}}, 0, 0 },
  { "R36", 36, {0, {{{0, 0}}}}, 0, 0 },
  { "R37", 37, {0, {{{0, 0}}}}, 0, 0 },
  { "R38", 38, {0, {{{0, 0}}}}, 0, 0 },
  { "R39", 39, {0, {{{0, 0}}}}, 0, 0 },
  { "R40", 40, {0, {{{0, 0}}}}, 0, 0 },
  { "R41", 41, {0, {{{0, 0}}}}, 0, 0 },
  { "R42", 42, {0, {{{0, 0}}}}, 0, 0 },
  { "R43", 43, {0, {{{0, 0}}}}, 0, 0 },
  { "R44", 44, {0, {{{0, 0}}}}, 0, 0 },
  { "R45", 45, {0, {{{0, 0}}}}, 0, 0 },
  { "R46", 46, {0, {{{0, 0}}}}, 0, 0 },
  { "R47", 47, {0, {{{0, 0}}}}, 0, 0 },
  { "R48", 48, {0, {{{0, 0}}}}, 0, 0 },
  { "R49", 49, {0, {{{0, 0}}}}, 0, 0 },
  { "R50", 50, {0, {{{0, 0}}}}, 0, 0 },
  { "R51", 51, {0, {{{0, 0}}}}, 0, 0 },
  { "R52", 52, {0, {{{0, 0}}}}, 0, 0 },
  { "R53", 53, {0, {{{0, 0}}}}, 0, 0 },
  { "R54", 54, {0, {{{0, 0}}}}, 0, 0 },
  { "R55", 55, {0, {{{0, 0}}}}, 0, 0 },
  { "R56", 56, {0, {{{0, 0}}}}, 0, 0 },
  { "R57", 57, {0, {{{0, 0}}}}, 0, 0 },
  { "R58", 58, {0, {{{0, 0}}}}, 0, 0 },
  { "R59", 59, {0, {{{0, 0}}}}, 0, 0 },
  { "R60", 60, {0, {{{0, 0}}}}, 0, 0 },
  { "R61", 61, {0, {{{0, 0}}}}, 0, 0 },
  { "R62", 62, {0, {{{0, 0}}}}, 0, 0 },
  { "R63", 63, {0, {{{0, 0}}}}, 0, 0 },
  { "A1", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "A2", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "A3", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "A4", 3, {0, {{{0, 0}}}}, 0, 0 },
  { "V1", 4, {0, {{{0, 0}}}}, 0, 0 },
  { "V2", 5, {0, {{{0, 0}}}}, 0, 0 },
  { "V3", 6, {0, {{{0, 0}}}}, 0, 0 },
  { "V4", 7, {0, {{{0, 0}}}}, 0, 0 },
  { "V5", 8, {0, {{{0, 0}}}}, 0, 0 },
  { "V6", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "V7", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "V8", 11, {0, {{{0, 0}}}}, 0, 0 },
  { "SB", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "SL", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "IP", 12, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-CONFIG", 256, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-STATUS", 257, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-PC", 258, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-DEBUGSTATUS", 259, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-IAB", 260, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-LC", 261, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-LS", 262, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-LE", 263, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-IRET", 264, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-IMASK", 265, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-ILAT", 266, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-ILATST", 267, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-ILATCL", 268, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-IPEND", 269, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-CTIMER0", 270, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-CTIMER1", 271, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-FSTATUS", 272, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-FCONFIG", 273, {0, {{{0, 0}}}}, 0, 0 },
  { "SCR-DEBUGCMD", 274, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-CONFIG", 320, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-STRIDE", 321, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-COUNT", 322, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-SRCADDR", 323, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-DSTADDR", 324, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-AUTO0", 325, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-AUTO1", 326, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA0-STATUS", 327, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-CONFIG", 328, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-STRIDE", 329, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-COUNT", 330, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-SRCADDR", 331, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-DSTADDR", 332, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-AUTO0", 333, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-AUTO1", 334, {0, {{{0, 0}}}}, 0, 0 },
  { "DMA1-STATUS", 335, {0, {{{0, 0}}}}, 0, 0 },
  { "MEM-CONFIG", 384, {0, {{{0, 0}}}}, 0, 0 },
  { "MEM-STATUS", 385, {0, {{{0, 0}}}}, 0, 0 },
  { "MEM-PROTECT", 386, {0, {{{0, 0}}}}, 0, 0 },
  { "MEM-RESERVE", 387, {0, {{{0, 0}}}}, 0, 0 },
  { "MESH-CONFIG", 448, {0, {{{0, 0}}}}, 0, 0 },
  { "MESH-COREID", 449, {0, {{{0, 0}}}}, 0, 0 },
  { "MESH-MULTICAST", 450, {0, {{{0, 0}}}}, 0, 0 },
  { "MESH-RESETCORE", 451, {0, {{{0, 0}}}}, 0, 0 },
  { "MESH-CMESHROUTE", 452, {0, {{{0, 0}}}}, 0, 0 },
  { "MESH-XMESHROUTE", 453, {0, {{{0, 0}}}}, 0, 0 },
  { "MESH-RMESHROUTE", 454, {0, {{{0, 0}}}}, 0, 0 }
};

CGEN_KEYWORD epiphany_cgen_opval_all_reg_names =
{
  & epiphany_cgen_opval_all_reg_names_entries[0],
  129,
  0, 0, 0, 0, ""
};

static CGEN_KEYWORD_ENTRY epiphany_cgen_opval_gr_names_entries[] =
{
  { "sp", 13, {0, {{{0, 0}}}}, 0, 0 },
  { "lr", 14, {0, {{{0, 0}}}}, 0, 0 },
  { "fp", 15, {0, {{{0, 0}}}}, 0, 0 },
  { "r0", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "r1", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "r2", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "r3", 3, {0, {{{0, 0}}}}, 0, 0 },
  { "r4", 4, {0, {{{0, 0}}}}, 0, 0 },
  { "r5", 5, {0, {{{0, 0}}}}, 0, 0 },
  { "r6", 6, {0, {{{0, 0}}}}, 0, 0 },
  { "r7", 7, {0, {{{0, 0}}}}, 0, 0 },
  { "r8", 8, {0, {{{0, 0}}}}, 0, 0 },
  { "r9", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "r10", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "r11", 11, {0, {{{0, 0}}}}, 0, 0 },
  { "r12", 12, {0, {{{0, 0}}}}, 0, 0 },
  { "r13", 13, {0, {{{0, 0}}}}, 0, 0 },
  { "r14", 14, {0, {{{0, 0}}}}, 0, 0 },
  { "r15", 15, {0, {{{0, 0}}}}, 0, 0 },
  { "r16", 16, {0, {{{0, 0}}}}, 0, 0 },
  { "r17", 17, {0, {{{0, 0}}}}, 0, 0 },
  { "r18", 18, {0, {{{0, 0}}}}, 0, 0 },
  { "r19", 19, {0, {{{0, 0}}}}, 0, 0 },
  { "r20", 20, {0, {{{0, 0}}}}, 0, 0 },
  { "r21", 21, {0, {{{0, 0}}}}, 0, 0 },
  { "r22", 22, {0, {{{0, 0}}}}, 0, 0 },
  { "r23", 23, {0, {{{0, 0}}}}, 0, 0 },
  { "r24", 24, {0, {{{0, 0}}}}, 0, 0 },
  { "r25", 25, {0, {{{0, 0}}}}, 0, 0 },
  { "r26", 26, {0, {{{0, 0}}}}, 0, 0 },
  { "r27", 27, {0, {{{0, 0}}}}, 0, 0 },
  { "r28", 28, {0, {{{0, 0}}}}, 0, 0 },
  { "r29", 29, {0, {{{0, 0}}}}, 0, 0 },
  { "r30", 30, {0, {{{0, 0}}}}, 0, 0 },
  { "r31", 31, {0, {{{0, 0}}}}, 0, 0 },
  { "r32", 32, {0, {{{0, 0}}}}, 0, 0 },
  { "r33", 33, {0, {{{0, 0}}}}, 0, 0 },
  { "r34", 34, {0, {{{0, 0}}}}, 0, 0 },
  { "r35", 35, {0, {{{0, 0}}}}, 0, 0 },
  { "r36", 36, {0, {{{0, 0}}}}, 0, 0 },
  { "r37", 37, {0, {{{0, 0}}}}, 0, 0 },
  { "r38", 38, {0, {{{0, 0}}}}, 0, 0 },
  { "r39", 39, {0, {{{0, 0}}}}, 0, 0 },
  { "r40", 40, {0, {{{0, 0}}}}, 0, 0 },
  { "r41", 41, {0, {{{0, 0}}}}, 0, 0 },
  { "r42", 42, {0, {{{0, 0}}}}, 0, 0 },
  { "r43", 43, {0, {{{0, 0}}}}, 0, 0 },
  { "r44", 44, {0, {{{0, 0}}}}, 0, 0 },
  { "r45", 45, {0, {{{0, 0}}}}, 0, 0 },
  { "r46", 46, {0, {{{0, 0}}}}, 0, 0 },
  { "r47", 47, {0, {{{0, 0}}}}, 0, 0 },
  { "r48", 48, {0, {{{0, 0}}}}, 0, 0 },
  { "r49", 49, {0, {{{0, 0}}}}, 0, 0 },
  { "r50", 50, {0, {{{0, 0}}}}, 0, 0 },
  { "r51", 51, {0, {{{0, 0}}}}, 0, 0 },
  { "r52", 52, {0, {{{0, 0}}}}, 0, 0 },
  { "r53", 53, {0, {{{0, 0}}}}, 0, 0 },
  { "r54", 54, {0, {{{0, 0}}}}, 0, 0 },
  { "r55", 55, {0, {{{0, 0}}}}, 0, 0 },
  { "r56", 56, {0, {{{0, 0}}}}, 0, 0 },
  { "r57", 57, {0, {{{0, 0}}}}, 0, 0 },
  { "r58", 58, {0, {{{0, 0}}}}, 0, 0 },
  { "r59", 59, {0, {{{0, 0}}}}, 0, 0 },
  { "r60", 60, {0, {{{0, 0}}}}, 0, 0 },
  { "r61", 61, {0, {{{0, 0}}}}, 0, 0 },
  { "r62", 62, {0, {{{0, 0}}}}, 0, 0 },
  { "r63", 63, {0, {{{0, 0}}}}, 0, 0 },
  { "a1", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "a2", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "a3", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "a4", 3, {0, {{{0, 0}}}}, 0, 0 },
  { "v1", 4, {0, {{{0, 0}}}}, 0, 0 },
  { "v2", 5, {0, {{{0, 0}}}}, 0, 0 },
  { "v3", 6, {0, {{{0, 0}}}}, 0, 0 },
  { "v4", 7, {0, {{{0, 0}}}}, 0, 0 },
  { "v5", 8, {0, {{{0, 0}}}}, 0, 0 },
  { "v6", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "v7", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "v8", 11, {0, {{{0, 0}}}}, 0, 0 },
  { "sb", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "sl", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "ip", 12, {0, {{{0, 0}}}}, 0, 0 }
};

CGEN_KEYWORD epiphany_cgen_opval_gr_names =
{
  & epiphany_cgen_opval_gr_names_entries[0],
  82,
  0, 0, 0, 0, ""
};

static CGEN_KEYWORD_ENTRY epiphany_cgen_opval_cr_names_entries[] =
{
  { "config", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "status", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "pc", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "debugstatus", 3, {0, {{{0, 0}}}}, 0, 0 },
  { "iab", 4, {0, {{{0, 0}}}}, 0, 0 },
  { "lc", 5, {0, {{{0, 0}}}}, 0, 0 },
  { "ls", 6, {0, {{{0, 0}}}}, 0, 0 },
  { "le", 7, {0, {{{0, 0}}}}, 0, 0 },
  { "iret", 8, {0, {{{0, 0}}}}, 0, 0 },
  { "imask", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "ilat", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "ilatst", 11, {0, {{{0, 0}}}}, 0, 0 },
  { "ilatcl", 12, {0, {{{0, 0}}}}, 0, 0 },
  { "ipend", 13, {0, {{{0, 0}}}}, 0, 0 },
  { "ctimer0", 14, {0, {{{0, 0}}}}, 0, 0 },
  { "ctimer1", 15, {0, {{{0, 0}}}}, 0, 0 },
  { "fstatus", 16, {0, {{{0, 0}}}}, 0, 0 }
};

CGEN_KEYWORD epiphany_cgen_opval_cr_names =
{
  & epiphany_cgen_opval_cr_names_entries[0],
  17,
  0, 0, 0, 0, ""
};

static CGEN_KEYWORD_ENTRY epiphany_cgen_opval_crdma_names_entries[] =
{
  { "dma0config", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "dma0stride", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "dma0count", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "dma0srcaddr", 3, {0, {{{0, 0}}}}, 0, 0 },
  { "dma0dstaddr", 4, {0, {{{0, 0}}}}, 0, 0 },
  { "dma0auto0", 5, {0, {{{0, 0}}}}, 0, 0 },
  { "dma0auto1", 6, {0, {{{0, 0}}}}, 0, 0 },
  { "dma0status", 7, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1config", 8, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1stride", 9, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1count", 10, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1srcaddr", 11, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1dstaddr", 12, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1auto0", 13, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1auto1", 14, {0, {{{0, 0}}}}, 0, 0 },
  { "dma1status", 15, {0, {{{0, 0}}}}, 0, 0 }
};

CGEN_KEYWORD epiphany_cgen_opval_crdma_names =
{
  & epiphany_cgen_opval_crdma_names_entries[0],
  16,
  0, 0, 0, 0, ""
};

static CGEN_KEYWORD_ENTRY epiphany_cgen_opval_crmem_names_entries[] =
{
  { "memconfig", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "memstatus", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "memprotect", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "memreserve", 3, {0, {{{0, 0}}}}, 0, 0 }
};

CGEN_KEYWORD epiphany_cgen_opval_crmem_names =
{
  & epiphany_cgen_opval_crmem_names_entries[0],
  4,
  0, 0, 0, 0, ""
};

static CGEN_KEYWORD_ENTRY epiphany_cgen_opval_crmesh_names_entries[] =
{
  { "meshconfig", 0, {0, {{{0, 0}}}}, 0, 0 },
  { "coreid", 1, {0, {{{0, 0}}}}, 0, 0 },
  { "meshmulticast", 2, {0, {{{0, 0}}}}, 0, 0 },
  { "resetcore", 3, {0, {{{0, 0}}}}, 0, 0 }
};

CGEN_KEYWORD epiphany_cgen_opval_crmesh_names =
{
  & epiphany_cgen_opval_crmesh_names_entries[0],
  4,
  0, 0, 0, 0, ""
};


/* The hardware table.  */

#define A(a) (1 << CGEN_HW_##a)

const CGEN_HW_ENTRY epiphany_cgen_hw_table[] =
{
  { "h-memory", HW_H_MEMORY, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-sint", HW_H_SINT, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-uint", HW_H_UINT, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-addr", HW_H_ADDR, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-iaddr", HW_H_IADDR, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
  { "h-all-registers", HW_H_ALL_REGISTERS, CGEN_ASM_KEYWORD, (PTR) & epiphany_cgen_opval_all_reg_names, { 0|A(PROFILE), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-registers", HW_H_REGISTERS, CGEN_ASM_KEYWORD, (PTR) & epiphany_cgen_opval_gr_names, { 0|A(VIRTUAL)|A(PROFILE), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-fpregisters", HW_H_FPREGISTERS, CGEN_ASM_KEYWORD, (PTR) & epiphany_cgen_opval_gr_names, { 0|A(VIRTUAL)|A(PROFILE), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-pc", HW_H_PC, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL)|A(PROFILE)|A(PC), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-memaddr", HW_H_MEMADDR, CGEN_ASM_NONE, 0, { 0|A(PROFILE), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-core-registers", HW_H_CORE_REGISTERS, CGEN_ASM_KEYWORD, (PTR) & epiphany_cgen_opval_cr_names, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-caibit", HW_H_CAIBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-gidisablebit", HW_H_GIDISABLEBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-kmbit", HW_H_KMBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-sflagbit", HW_H_SFLAGBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-zbit", HW_H_ZBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-nbit", HW_H_NBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-cbit", HW_H_CBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-vbit", HW_H_VBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-bzbit", HW_H_BZBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-bnbit", HW_H_BNBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-bvbit", HW_H_BVBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-bcbit", HW_H_BCBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-vsbit", HW_H_VSBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-bisbit", HW_H_BISBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-bvsbit", HW_H_BVSBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-busbit", HW_H_BUSBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-excause0bit", HW_H_EXCAUSE0BIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-excause1bit", HW_H_EXCAUSE1BIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-excause2bit", HW_H_EXCAUSE2BIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-excause3bit", HW_H_EXCAUSE3BIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-scr-status-excause", HW_H_SCR_STATUS_EXCAUSE, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-trmbit", HW_H_TRMBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-invexcenbit", HW_H_INVEXCENBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-ovfexcenbit", HW_H_OVFEXCENBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-unexcenbit", HW_H_UNEXCENBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer0bit0", HW_H_TIMER0BIT0, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer0bit1", HW_H_TIMER0BIT1, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer0bit2", HW_H_TIMER0BIT2, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer0bit3", HW_H_TIMER0BIT3, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer1bit0", HW_H_TIMER1BIT0, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer1bit1", HW_H_TIMER1BIT1, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer1bit2", HW_H_TIMER1BIT2, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-timer1bit3", HW_H_TIMER1BIT3, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-arithmetic-modebit0", HW_H_ARITHMETIC_MODEBIT0, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-arithmetic-modebit1", HW_H_ARITHMETIC_MODEBIT1, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-arithmetic-modebit2", HW_H_ARITHMETIC_MODEBIT2, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-clockgateenbit", HW_H_CLOCKGATEENBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-mbkptenbit", HW_H_MBKPTENBIT, CGEN_ASM_NONE, 0, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-coredma-registers", HW_H_COREDMA_REGISTERS, CGEN_ASM_KEYWORD, (PTR) & epiphany_cgen_opval_crdma_names, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-coremem-registers", HW_H_COREMEM_REGISTERS, CGEN_ASM_KEYWORD, (PTR) & epiphany_cgen_opval_crmem_names, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { "h-coremesh-registers", HW_H_COREMESH_REGISTERS, CGEN_ASM_KEYWORD, (PTR) & epiphany_cgen_opval_crmesh_names, { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } } },
  { 0, 0, CGEN_ASM_NONE, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } }
};

#undef A


/* The instruction field table.  */

#define A(a) (1 << CGEN_IFLD_##a)

const CGEN_IFLD epiphany_cgen_ifld_table[] =
{
  { EPIPHANY_F_NIL, "f-nil", 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_ANYOF, "f-anyof", 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_OPC, "f-opc", 0, 32, 3, 4, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_OPC_4_1, "f-opc-4-1", 0, 32, 4, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_OPC_6_3, "f-opc-6-3", 0, 32, 6, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_OPC_8_5, "f-opc-8-5", 0, 32, 8, 5, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_OPC_19_4, "f-opc-19-4", 0, 32, 19, 4, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_CONDCODE, "f-condcode", 0, 32, 7, 4, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SECONDARY_CCS, "f-secondary-ccs", 0, 32, 7, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SHIFT, "f-shift", 0, 32, 9, 5, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_WORDSIZE, "f-wordsize", 0, 32, 6, 2, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_STORE, "f-store", 0, 32, 4, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_OPC_8_1, "f-opc-8-1", 0, 32, 8, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_OPC_31_32, "f-opc-31-32", 0, 32, 31, 32, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SIMM8, "f-simm8", 0, 32, 15, 8, { 0|A(RELOC)|A(PCREL_ADDR), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SIMM24, "f-simm24", 0, 32, 31, 24, { 0|A(RELOC)|A(PCREL_ADDR), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SDISP3, "f-sdisp3", 0, 32, 9, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DISP3, "f-disp3", 0, 32, 9, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DISP8, "f-disp8", 0, 32, 23, 8, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_IMM8, "f-imm8", 0, 32, 12, 8, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_IMM_27_8, "f-imm-27-8", 0, 32, 27, 8, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_ADDSUBX, "f-addsubx", 0, 32, 20, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SUBD, "f-subd", 0, 32, 24, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_PM, "f-pm", 0, 32, 25, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RM, "f-rm", 0, 32, 9, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RN, "f-rn", 0, 32, 12, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RD, "f-rd", 0, 32, 15, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RM_X, "f-rm-x", 0, 32, 25, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RN_X, "f-rn-x", 0, 32, 28, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RD_X, "f-rd-x", 0, 32, 31, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_9_1, "f-dc-9-1", 0, 32, 9, 1, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SN, "f-sn", 0, 32, 12, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SD, "f-sd", 0, 32, 15, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SN_X, "f-sn-x", 0, 32, 28, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SD_X, "f-sd-x", 0, 32, 31, 3, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_7_4, "f-dc-7-4", 0, 32, 7, 4, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_TRAP_SWI_9_1, "f-trap-swi-9-1", 0, 32, 9, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_GIEN_GIDIS_9_1, "f-gien-gidis-9-1", 0, 32, 9, 1, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_15_3, "f-dc-15-3", 0, 32, 15, 3, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_15_7, "f-dc-15-7", 0, 32, 15, 7, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_15_6, "f-dc-15-6", 0, 32, 15, 6, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_TRAP_NUM, "f-trap-num", 0, 32, 15, 6, { 0, { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_20_1, "f-dc-20-1", 0, 32, 20, 1, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_21_1, "f-dc-21-1", 0, 32, 21, 1, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_21_2, "f-dc-21-2", 0, 32, 21, 2, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_22_3, "f-dc-22-3", 0, 32, 22, 3, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_22_2, "f-dc-22-2", 0, 32, 22, 2, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_22_1, "f-dc-22-1", 0, 32, 22, 1, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_25_6, "f-dc-25-6", 0, 32, 25, 6, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_25_4, "f-dc-25-4", 0, 32, 25, 4, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_25_2, "f-dc-25-2", 0, 32, 25, 2, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_25_1, "f-dc-25-1", 0, 32, 25, 1, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_28_1, "f-dc-28-1", 0, 32, 28, 1, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DC_31_3, "f-dc-31-3", 0, 32, 31, 3, { 0|A(RESERVED), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_DISP11, "f-disp11", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SDISP11, "f-sdisp11", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_IMM16, "f-imm16", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RD6, "f-rd6", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RN6, "f-rn6", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_RM6, "f-rm6", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SD6, "f-sd6", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { EPIPHANY_F_SN6, "f-sn6", 0, 0, 0, 0,{ 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
  { 0, 0, 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } }
};

#undef A



/* multi ifield declarations */

const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_DISP11_MULTI_IFIELD [];
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_SDISP11_MULTI_IFIELD [];
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_IMM16_MULTI_IFIELD [];
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_RD6_MULTI_IFIELD [];
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_RN6_MULTI_IFIELD [];
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_RM6_MULTI_IFIELD [];
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_SD6_MULTI_IFIELD [];
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_SN6_MULTI_IFIELD [];


/* multi ifield definitions */

const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_DISP11_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_DISP3] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_DISP8] } },
    { 0, { (const PTR) 0 } }
};
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_SDISP11_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_DISP3] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_DISP8] } },
    { 0, { (const PTR) 0 } }
};
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_IMM16_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_IMM8] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_IMM_27_8] } },
    { 0, { (const PTR) 0 } }
};
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_RD6_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RD_X] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RD] } },
    { 0, { (const PTR) 0 } }
};
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_RN6_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RN_X] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RN] } },
    { 0, { (const PTR) 0 } }
};
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_RM6_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RM_X] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RM] } },
    { 0, { (const PTR) 0 } }
};
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_SD6_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SD_X] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SD] } },
    { 0, { (const PTR) 0 } }
};
const CGEN_MAYBE_MULTI_IFLD EPIPHANY_F_SN6_MULTI_IFIELD [] =
{
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SN_X] } },
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SN] } },
    { 0, { (const PTR) 0 } }
};

/* The operand table.  */

#define A(a) (1 << CGEN_OPERAND_##a)
#define OPERAND(op) EPIPHANY_OPERAND_##op

const CGEN_OPERAND epiphany_cgen_operand_table[] =
{
/* pc: program counter */
  { "pc", EPIPHANY_OPERAND_PC, HW_H_PC, 0, 0,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_NIL] } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* memaddr: memory effective address */
  { "memaddr", EPIPHANY_OPERAND_MEMADDR, HW_H_MEMADDR, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* caibit: cmt */
  { "caibit", EPIPHANY_OPERAND_CAIBIT, HW_H_CAIBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* gidisablebit: cmt */
  { "gidisablebit", EPIPHANY_OPERAND_GIDISABLEBIT, HW_H_GIDISABLEBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* kmbit: cmt */
  { "kmbit", EPIPHANY_OPERAND_KMBIT, HW_H_KMBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* sflagbit: cmt */
  { "sflagbit", EPIPHANY_OPERAND_SFLAGBIT, HW_H_SFLAGBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* zbit: cmt */
  { "zbit", EPIPHANY_OPERAND_ZBIT, HW_H_ZBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* nbit: cmt */
  { "nbit", EPIPHANY_OPERAND_NBIT, HW_H_NBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* cbit: cmt */
  { "cbit", EPIPHANY_OPERAND_CBIT, HW_H_CBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* vbit: cmt */
  { "vbit", EPIPHANY_OPERAND_VBIT, HW_H_VBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* bzbit: cmt */
  { "bzbit", EPIPHANY_OPERAND_BZBIT, HW_H_BZBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* bnbit: cmt */
  { "bnbit", EPIPHANY_OPERAND_BNBIT, HW_H_BNBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* bvbit: cmt */
  { "bvbit", EPIPHANY_OPERAND_BVBIT, HW_H_BVBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* bcbit: cmt */
  { "bcbit", EPIPHANY_OPERAND_BCBIT, HW_H_BCBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* vsbit: cmt */
  { "vsbit", EPIPHANY_OPERAND_VSBIT, HW_H_VSBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* bisbit: cmt */
  { "bisbit", EPIPHANY_OPERAND_BISBIT, HW_H_BISBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* bvsbit: cmt */
  { "bvsbit", EPIPHANY_OPERAND_BVSBIT, HW_H_BVSBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* busbit: cmt */
  { "busbit", EPIPHANY_OPERAND_BUSBIT, HW_H_BUSBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* excause0bit: cmt */
  { "excause0bit", EPIPHANY_OPERAND_EXCAUSE0BIT, HW_H_EXCAUSE0BIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* excause1bit: cmt */
  { "excause1bit", EPIPHANY_OPERAND_EXCAUSE1BIT, HW_H_EXCAUSE1BIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* excause2bit: cmt */
  { "excause2bit", EPIPHANY_OPERAND_EXCAUSE2BIT, HW_H_EXCAUSE2BIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* excause3bit: cmt */
  { "excause3bit", EPIPHANY_OPERAND_EXCAUSE3BIT, HW_H_EXCAUSE3BIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* trmbit: cmt */
  { "trmbit", EPIPHANY_OPERAND_TRMBIT, HW_H_TRMBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* invexcenbit: cmt */
  { "invexcenbit", EPIPHANY_OPERAND_INVEXCENBIT, HW_H_INVEXCENBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* ovfexcenbit: cmt */
  { "ovfexcenbit", EPIPHANY_OPERAND_OVFEXCENBIT, HW_H_OVFEXCENBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* unexcenbit: cmt */
  { "unexcenbit", EPIPHANY_OPERAND_UNEXCENBIT, HW_H_UNEXCENBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer0bit0: cmt */
  { "timer0bit0", EPIPHANY_OPERAND_TIMER0BIT0, HW_H_TIMER0BIT0, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer0bit1: cmt */
  { "timer0bit1", EPIPHANY_OPERAND_TIMER0BIT1, HW_H_TIMER0BIT1, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer0bit2: cmt */
  { "timer0bit2", EPIPHANY_OPERAND_TIMER0BIT2, HW_H_TIMER0BIT2, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer0bit3: cmt */
  { "timer0bit3", EPIPHANY_OPERAND_TIMER0BIT3, HW_H_TIMER0BIT3, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer1bit0: cmt */
  { "timer1bit0", EPIPHANY_OPERAND_TIMER1BIT0, HW_H_TIMER1BIT0, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer1bit1: cmt */
  { "timer1bit1", EPIPHANY_OPERAND_TIMER1BIT1, HW_H_TIMER1BIT1, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer1bit2: cmt */
  { "timer1bit2", EPIPHANY_OPERAND_TIMER1BIT2, HW_H_TIMER1BIT2, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* timer1bit3: cmt */
  { "timer1bit3", EPIPHANY_OPERAND_TIMER1BIT3, HW_H_TIMER1BIT3, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* arithmetic-modebit0: cmt */
  { "arithmetic-modebit0", EPIPHANY_OPERAND_ARITHMETIC_MODEBIT0, HW_H_ARITHMETIC_MODEBIT0, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* arithmetic-modebit1: cmt */
  { "arithmetic-modebit1", EPIPHANY_OPERAND_ARITHMETIC_MODEBIT1, HW_H_ARITHMETIC_MODEBIT1, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* arithmetic-modebit2: cmt */
  { "arithmetic-modebit2", EPIPHANY_OPERAND_ARITHMETIC_MODEBIT2, HW_H_ARITHMETIC_MODEBIT2, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* clockgateenbit: cmt */
  { "clockgateenbit", EPIPHANY_OPERAND_CLOCKGATEENBIT, HW_H_CLOCKGATEENBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* mbkptenbit: cmt */
  { "mbkptenbit", EPIPHANY_OPERAND_MBKPTENBIT, HW_H_MBKPTENBIT, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0|A(SEM_ONLY), { { { (1<<MACH_BASE), 0 } } } }  },
/* simm24: branch address pc-relative */
  { "simm24", EPIPHANY_OPERAND_SIMM24, HW_H_IADDR, 31, 24,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SIMM24] } },
    { 0|A(RELAX)|A(RELOC)|A(PCREL_ADDR), { { { (1<<MACH_BASE), 0 } } } }  },
/* simm8: branch address pc-relative */
  { "simm8", EPIPHANY_OPERAND_SIMM8, HW_H_IADDR, 15, 8,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SIMM8] } },
    { 0|A(RELAX)|A(RELOC)|A(PCREL_ADDR), { { { (1<<MACH_BASE), 0 } } } }  },
/* rd: destination register */
  { "rd", EPIPHANY_OPERAND_RD, HW_H_REGISTERS, 15, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RD] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* rn: source register */
  { "rn", EPIPHANY_OPERAND_RN, HW_H_REGISTERS, 12, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RN] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* rm: source register */
  { "rm", EPIPHANY_OPERAND_RM, HW_H_REGISTERS, 9, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RM] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* frd: fp destination register */
  { "frd", EPIPHANY_OPERAND_FRD, HW_H_FPREGISTERS, 15, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RD] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* frn: fp source register */
  { "frn", EPIPHANY_OPERAND_FRN, HW_H_FPREGISTERS, 12, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RN] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* frm: fp source register */
  { "frm", EPIPHANY_OPERAND_FRM, HW_H_FPREGISTERS, 9, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_RM] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* rd6: destination register */
  { "rd6", EPIPHANY_OPERAND_RD6, HW_H_REGISTERS, 15, 6,
    { 2, { (const PTR) &EPIPHANY_F_RD6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* rn6: source register */
  { "rn6", EPIPHANY_OPERAND_RN6, HW_H_REGISTERS, 12, 6,
    { 2, { (const PTR) &EPIPHANY_F_RN6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* rm6: source register */
  { "rm6", EPIPHANY_OPERAND_RM6, HW_H_REGISTERS, 9, 6,
    { 2, { (const PTR) &EPIPHANY_F_RM6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* frd6: fp destination register */
  { "frd6", EPIPHANY_OPERAND_FRD6, HW_H_FPREGISTERS, 15, 6,
    { 2, { (const PTR) &EPIPHANY_F_RD6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* frn6: fp source register */
  { "frn6", EPIPHANY_OPERAND_FRN6, HW_H_FPREGISTERS, 12, 6,
    { 2, { (const PTR) &EPIPHANY_F_RN6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* frm6: fp source register */
  { "frm6", EPIPHANY_OPERAND_FRM6, HW_H_FPREGISTERS, 9, 6,
    { 2, { (const PTR) &EPIPHANY_F_RM6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* sd: special destination */
  { "sd", EPIPHANY_OPERAND_SD, HW_H_CORE_REGISTERS, 15, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SD] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* sn: special source */
  { "sn", EPIPHANY_OPERAND_SN, HW_H_CORE_REGISTERS, 12, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SN] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* sd6: special destination register */
  { "sd6", EPIPHANY_OPERAND_SD6, HW_H_CORE_REGISTERS, 15, 6,
    { 2, { (const PTR) &EPIPHANY_F_SD6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* sn6: special source register */
  { "sn6", EPIPHANY_OPERAND_SN6, HW_H_CORE_REGISTERS, 12, 6,
    { 2, { (const PTR) &EPIPHANY_F_SN6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* sddma: dma register */
  { "sddma", EPIPHANY_OPERAND_SDDMA, HW_H_COREDMA_REGISTERS, 15, 6,
    { 2, { (const PTR) &EPIPHANY_F_SD6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* sndma: dma register */
  { "sndma", EPIPHANY_OPERAND_SNDMA, HW_H_COREDMA_REGISTERS, 12, 6,
    { 2, { (const PTR) &EPIPHANY_F_SN6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* sdmem: mem register */
  { "sdmem", EPIPHANY_OPERAND_SDMEM, HW_H_COREMEM_REGISTERS, 15, 6,
    { 2, { (const PTR) &EPIPHANY_F_SD6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* snmem: mem register */
  { "snmem", EPIPHANY_OPERAND_SNMEM, HW_H_COREMEM_REGISTERS, 12, 6,
    { 2, { (const PTR) &EPIPHANY_F_SN6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* sdmesh: mesh register */
  { "sdmesh", EPIPHANY_OPERAND_SDMESH, HW_H_COREMESH_REGISTERS, 15, 6,
    { 2, { (const PTR) &EPIPHANY_F_SD6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* snmesh: mesh register */
  { "snmesh", EPIPHANY_OPERAND_SNMESH, HW_H_COREMESH_REGISTERS, 12, 6,
    { 2, { (const PTR) &EPIPHANY_F_SN6_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* simm3: signed 3-bit literal */
  { "simm3", EPIPHANY_OPERAND_SIMM3, HW_H_SINT, 9, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SDISP3] } },
    { 0|A(RELAX), { { { (1<<MACH_BASE), 0 } } } }  },
/* simm11: signed 11-bit literal */
  { "simm11", EPIPHANY_OPERAND_SIMM11, HW_H_SINT, 9, 11,
    { 2, { (const PTR) &EPIPHANY_F_SDISP11_MULTI_IFIELD[0] } },
    { 0|A(RELAX)|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* disp3: short data displacement */
  { "disp3", EPIPHANY_OPERAND_DISP3, HW_H_UINT, 9, 3,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_DISP3] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* trapnum6: parameter for swi or trap */
  { "trapnum6", EPIPHANY_OPERAND_TRAPNUM6, HW_H_UINT, 15, 6,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_TRAP_NUM] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* swi_num: unsigned 6-bit swi# */
  { "swi_num", EPIPHANY_OPERAND_SWI_NUM, HW_H_UINT, 15, 6,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_TRAP_NUM] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* disp11: sign-magnitude data displacement */
  { "disp11", EPIPHANY_OPERAND_DISP11, HW_H_UINT, 9, 11,
    { 2, { (const PTR) &EPIPHANY_F_DISP11_MULTI_IFIELD[0] } },
    { 0|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* shift: immediate shift amount */
  { "shift", EPIPHANY_OPERAND_SHIFT, HW_H_UINT, 9, 5,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SHIFT] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* imm16: 16-bit unsigned literal */
  { "imm16", EPIPHANY_OPERAND_IMM16, HW_H_ADDR, 12, 16,
    { 2, { (const PTR) &EPIPHANY_F_IMM16_MULTI_IFIELD[0] } },
    { 0|A(RELAX)|A(VIRTUAL), { { { (1<<MACH_BASE), 0 } } } }  },
/* imm8: 8-bit unsigned literal */
  { "imm8", EPIPHANY_OPERAND_IMM8, HW_H_ADDR, 12, 8,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_IMM8] } },
    { 0|A(RELAX), { { { (1<<MACH_BASE), 0 } } } }  },
/* direction: +/- indexing */
  { "direction", EPIPHANY_OPERAND_DIRECTION, HW_H_UINT, 20, 1,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_ADDSUBX] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* dpmi: +/- magnitude immediate displacement */
  { "dpmi", EPIPHANY_OPERAND_DPMI, HW_H_UINT, 24, 1,
    { 0, { (const PTR) &epiphany_cgen_ifld_table[EPIPHANY_F_SUBD] } },
    { 0, { { { (1<<MACH_BASE), 0 } } } }  },
/* sentinel */
  { 0, 0, 0, 0, 0,
    { 0, { (const PTR) 0 } },
    { 0, { { { (1<<MACH_BASE), 0 } } } } }
};

#undef A


/* The instruction table.  */

#define OP(field) CGEN_SYNTAX_MAKE_FIELD (OPERAND (field))
#define A(a) (1 << CGEN_INSN_##a)

static const CGEN_IBASE epiphany_cgen_insn_table[MAX_INSNS] =
{
  /* Special null first entry.
     A `num' value of zero is thus invalid.
     Also, the special `invalid' insn resides here.  */
  { 0, 0, 0, 0, { 0, { { { (1<<MACH_BASE), 0 } } } } },
/* beq.s $simm8 */
  {
    EPIPHANY_INSN_BEQ16, "beq16", "beq.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* beq.l $simm24 */
  {
    EPIPHANY_INSN_BEQ, "beq", "beq.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bne.s $simm8 */
  {
    EPIPHANY_INSN_BNE16, "bne16", "bne.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bne.l $simm24 */
  {
    EPIPHANY_INSN_BNE, "bne", "bne.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgtu.s $simm8 */
  {
    EPIPHANY_INSN_BGTU16, "bgtu16", "bgtu.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgtu.l $simm24 */
  {
    EPIPHANY_INSN_BGTU, "bgtu", "bgtu.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgteu.s $simm8 */
  {
    EPIPHANY_INSN_BGTEU16, "bgteu16", "bgteu.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgteu.l $simm24 */
  {
    EPIPHANY_INSN_BGTEU, "bgteu", "bgteu.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* blteu.s $simm8 */
  {
    EPIPHANY_INSN_BLTEU16, "blteu16", "blteu.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* blteu.l $simm24 */
  {
    EPIPHANY_INSN_BLTEU, "blteu", "blteu.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bltu.s $simm8 */
  {
    EPIPHANY_INSN_BLTU16, "bltu16", "bltu.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bltu.l $simm24 */
  {
    EPIPHANY_INSN_BLTU, "bltu", "bltu.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgt.s $simm8 */
  {
    EPIPHANY_INSN_BGT16, "bgt16", "bgt.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgt.l $simm24 */
  {
    EPIPHANY_INSN_BGT, "bgt", "bgt.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgte.s $simm8 */
  {
    EPIPHANY_INSN_BGTE16, "bgte16", "bgte.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bgte.l $simm24 */
  {
    EPIPHANY_INSN_BGTE, "bgte", "bgte.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* blt.s $simm8 */
  {
    EPIPHANY_INSN_BLT16, "blt16", "blt.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* blt.l $simm24 */
  {
    EPIPHANY_INSN_BLT, "blt", "blt.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* blte.s $simm8 */
  {
    EPIPHANY_INSN_BLTE16, "blte16", "blte.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* blte.l $simm24 */
  {
    EPIPHANY_INSN_BLTE, "blte", "blte.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bbeq.s $simm8 */
  {
    EPIPHANY_INSN_BBEQ16, "bbeq16", "bbeq.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bbeq.l $simm24 */
  {
    EPIPHANY_INSN_BBEQ, "bbeq", "bbeq.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bbne.s $simm8 */
  {
    EPIPHANY_INSN_BBNE16, "bbne16", "bbne.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bbne.l $simm24 */
  {
    EPIPHANY_INSN_BBNE, "bbne", "bbne.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bblt.s $simm8 */
  {
    EPIPHANY_INSN_BBLT16, "bblt16", "bblt.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bblt.l $simm24 */
  {
    EPIPHANY_INSN_BBLT, "bblt", "bblt.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bblte.s $simm8 */
  {
    EPIPHANY_INSN_BBLTE16, "bblte16", "bblte.s", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bblte.l $simm24 */
  {
    EPIPHANY_INSN_BBLTE, "bblte", "bblte.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* b.s $simm8 */
  {
    EPIPHANY_INSN_B16, "b16", "b.s", 16,
    { 0|A(SHORT_INSN)|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* b.l $simm24 */
  {
    EPIPHANY_INSN_B, "b", "b.l", 32,
    { 0|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bl.s $simm8 */
  {
    EPIPHANY_INSN_BL16, "bl16", "bl.s", 16,
    { 0|A(SHORT_INSN)|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bl.l $simm24 */
  {
    EPIPHANY_INSN_BL, "bl", "bl.l", 32,
    { 0|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* jr $rn */
  {
    EPIPHANY_INSN_JR16, "jr16", "jr", 16,
    { 0|A(SHORT_INSN)|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* rts */
  {
    -1, "rts", "rts", 32,
    { 0|A(UNCOND_CTI)|A(ALIAS), { { { (1<<MACH_BASE), 0 } } } }
  },
/* jr $rn6 */
  {
    EPIPHANY_INSN_JR, "jr", "jr", 32,
    { 0|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* jalr $rn */
  {
    EPIPHANY_INSN_JALR16, "jalr16", "jalr", 16,
    { 0|A(SHORT_INSN)|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* jalr $rn6 */
  {
    EPIPHANY_INSN_JALR, "jalr", "jalr", 32,
    { 0|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrb $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_LDRBX16_S, "ldrbx16.s", "ldrb", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrb $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_LDRBP16_S, "ldrbp16.s", "ldrb", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrb $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_LDRBX_L, "ldrbx.l", "ldrb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrb $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_LDRBP_L, "ldrbp.l", "ldrb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrb $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_LDRBD16_S, "ldrbd16.s", "ldrb", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrb $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_LDRBD_L, "ldrbd.l", "ldrb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrb $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_LDRBDPM_L, "ldrbdpm.l", "ldrb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrh $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_LDRHX16_S, "ldrhx16.s", "ldrh", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrh $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_LDRHP16_S, "ldrhp16.s", "ldrh", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrh $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_LDRHX_L, "ldrhx.l", "ldrh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrh $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_LDRHP_L, "ldrhp.l", "ldrh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrh $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_LDRHD16_S, "ldrhd16.s", "ldrh", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrh $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_LDRHD_L, "ldrhd.l", "ldrh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrh $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_LDRHDPM_L, "ldrhdpm.l", "ldrh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldr $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_LDRX16_S, "ldrx16.s", "ldr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldr $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_LDRP16_S, "ldrp16.s", "ldr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldr $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_LDRX_L, "ldrx.l", "ldr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldr $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_LDRP_L, "ldrp.l", "ldr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldr $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_LDRD16_S, "ldrd16.s", "ldr", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldr $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_LDRD_L, "ldrd.l", "ldr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldr $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_LDRDPM_L, "ldrdpm.l", "ldr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrd $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_LDRDX16_S, "ldrdx16.s", "ldrd", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrd $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_LDRDP16_S, "ldrdp16.s", "ldrd", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrd $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_LDRDX_L, "ldrdx.l", "ldrd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrd $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_LDRDP_L, "ldrdp.l", "ldrd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrd $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_LDRDD16_S, "ldrdd16.s", "ldrd", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrd $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_LDRDD_L, "ldrdd.l", "ldrd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* ldrd $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_LDRDDPM_L, "ldrddpm.l", "ldrd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* testsetb $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_TESTSETBT, "testsetbt", "testsetb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* testseth $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_TESTSETHT, "testsetht", "testseth", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* testset $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_TESTSETT, "testsett", "testset", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strb $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_STRBX16, "strbx16", "strb", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strb $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_STRBX, "strbx", "strb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strb $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_STRBP16, "strbp16", "strb", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strb $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_STRBP, "strbp", "strb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strb $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_STRBD16, "strbd16", "strb", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strb $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_STRBD, "strbd", "strb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strb $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_STRBDPM, "strbdpm", "strb", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strh $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_STRHX16, "strhx16", "strh", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strh $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_STRHX, "strhx", "strh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strh $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_STRHP16, "strhp16", "strh", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strh $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_STRHP, "strhp", "strh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strh $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_STRHD16, "strhd16", "strh", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strh $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_STRHD, "strhd", "strh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strh $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_STRHDPM, "strhdpm", "strh", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* str $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_STRX16, "strx16", "str", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* str $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_STRX, "strx", "str", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* str $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_STRP16, "strp16", "str", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* str $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_STRP, "strp", "str", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* str $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_STRD16, "strd16", "str", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* str $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_STRD, "strd", "str", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* str $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_STRDPM, "strdpm", "str", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strd $rd,[$rn,$rm] */
  {
    EPIPHANY_INSN_STRDX16, "strdx16", "strd", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strd $rd6,[$rn6,$direction$rm6] */
  {
    EPIPHANY_INSN_STRDX, "strdx", "strd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strd $rd,[$rn],$rm */
  {
    EPIPHANY_INSN_STRDP16, "strdp16", "strd", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strd $rd6,[$rn6],$direction$rm6 */
  {
    EPIPHANY_INSN_STRDP, "strdp", "strd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strd $rd,[$rn,$disp3] */
  {
    EPIPHANY_INSN_STRDD16, "strdd16", "strd", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strd $rd6,[$rn6,$dpmi$disp11] */
  {
    EPIPHANY_INSN_STRDD, "strdd", "strd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* strd $rd6,[$rn6],$dpmi$disp11 */
  {
    EPIPHANY_INSN_STRDDPM, "strddpm", "strd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* moveq $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16EQ, "cmov16EQ", "moveq", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* moveq $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVEQ, "cmovEQ", "moveq", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movne $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16NE, "cmov16NE", "movne", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movne $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVNE, "cmovNE", "movne", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgtu $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16GTU, "cmov16GTU", "movgtu", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgtu $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVGTU, "cmovGTU", "movgtu", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgteu $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16GTEU, "cmov16GTEU", "movgteu", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgteu $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVGTEU, "cmovGTEU", "movgteu", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movlteu $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16LTEU, "cmov16LTEU", "movlteu", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movlteu $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVLTEU, "cmovLTEU", "movlteu", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movltu $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16LTU, "cmov16LTU", "movltu", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movltu $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVLTU, "cmovLTU", "movltu", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgt $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16GT, "cmov16GT", "movgt", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgt $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVGT, "cmovGT", "movgt", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgte $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16GTE, "cmov16GTE", "movgte", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movgte $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVGTE, "cmovGTE", "movgte", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movlt $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16LT, "cmov16LT", "movlt", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movlt $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVLT, "cmovLT", "movlt", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movlte $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16LTE, "cmov16LTE", "movlte", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movlte $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVLTE, "cmovLTE", "movlte", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16B, "cmov16B", "mov", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVB, "cmovB", "mov", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movbeq $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16BEQ, "cmov16BEQ", "movbeq", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movbeq $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVBEQ, "cmovBEQ", "movbeq", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movbne $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16BNE, "cmov16BNE", "movbne", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movbne $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVBNE, "cmovBNE", "movbne", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movblt $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16BLT, "cmov16BLT", "movblt", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movblt $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVBLT, "cmovBLT", "movblt", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movblte $rd,$rn */
  {
    EPIPHANY_INSN_CMOV16BLTE, "cmov16BLTE", "movblte", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movblte $rd6,$rn6 */
  {
    EPIPHANY_INSN_CMOVBLTE, "cmovBLTE", "movblte", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movts $sn,$rd */
  {
    EPIPHANY_INSN_MOVTS16, "movts16", "movts", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movts $sn6,$rd6 */
  {
    EPIPHANY_INSN_MOVTS6, "movts6", "movts", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movts $sndma,$rd6 */
  {
    EPIPHANY_INSN_MOVTSDMA, "movtsdma", "movts", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movts $snmem,$rd6 */
  {
    EPIPHANY_INSN_MOVTSMEM, "movtsmem", "movts", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movts $snmesh,$rd6 */
  {
    EPIPHANY_INSN_MOVTSMESH, "movtsmesh", "movts", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movfs $rd,$sn */
  {
    EPIPHANY_INSN_MOVFS16, "movfs16", "movfs", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movfs $rd6,$sn6 */
  {
    EPIPHANY_INSN_MOVFS6, "movfs6", "movfs", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movfs $rd6,$sndma */
  {
    EPIPHANY_INSN_MOVFSDMA, "movfsdma", "movfs", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movfs $rd6,$snmem */
  {
    EPIPHANY_INSN_MOVFSMEM, "movfsmem", "movfs", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movfs $rd6,$snmesh */
  {
    EPIPHANY_INSN_MOVFSMESH, "movfsmesh", "movfs", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* nop */
  {
    EPIPHANY_INSN_NOP, "nop", "nop", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* snop */
  {
    EPIPHANY_INSN_SNOP, "snop", "snop", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* unimpl */
  {
    EPIPHANY_INSN_UNIMPL, "unimpl", "unimpl", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* idle */
  {
    EPIPHANY_INSN_IDLE, "idle", "idle", 16,
    { 0|A(SHORT_INSN)|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bkpt */
  {
    EPIPHANY_INSN_BKPT, "bkpt", "bkpt", 16,
    { 0|A(SHORT_INSN)|A(UNCOND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* mbkpt */
  {
    EPIPHANY_INSN_MBKPT, "mbkpt", "mbkpt", 16,
    { 0|A(SHORT_INSN), { { { (1<<MACH_BASE), 0 } } } }
  },
/* rti */
  {
    EPIPHANY_INSN_RTI, "rti", "rti", 16,
    { 0|A(UNCOND_CTI)|A(SHORT_INSN), { { { (1<<MACH_BASE), 0 } } } }
  },
/* wand */
  {
    EPIPHANY_INSN_WAND, "wand", "wand", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* sync */
  {
    EPIPHANY_INSN_SYNC, "sync", "sync", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* gie */
  {
    EPIPHANY_INSN_GIEN, "gien", "gie", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* gid */
  {
    EPIPHANY_INSN_GIDIS, "gidis", "gid", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* swi $swi_num */
  {
    EPIPHANY_INSN_SWI_NUM, "swi_num", "swi", 16,
    { 0|A(UNCOND_CTI)|A(SHORT_INSN), { { { (1<<MACH_BASE), 0 } } } }
  },
/* swi */
  {
    -1, "swi", "swi", 16,
    { 0|A(UNCOND_CTI)|A(SHORT_INSN)|A(ALIAS), { { { (1<<MACH_BASE), 0 } } } }
  },
/* trap $trapnum6 */
  {
    EPIPHANY_INSN_TRAP16, "trap16", "trap", 16,
    { 0|A(UNCOND_CTI)|A(SHORT_INSN), { { { (1<<MACH_BASE), 0 } } } }
  },
/* add $rd,$rn,$rm */
  {
    EPIPHANY_INSN_ADD16, "add16", "add", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* add $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_ADD, "add", "add", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub $rd,$rn,$rm */
  {
    EPIPHANY_INSN_SUB16, "sub16", "sub", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_SUB, "sub", "sub", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* and $rd,$rn,$rm */
  {
    EPIPHANY_INSN_AND16, "and16", "and", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* and $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_AND, "and", "and", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* orr $rd,$rn,$rm */
  {
    EPIPHANY_INSN_ORR16, "orr16", "orr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* orr $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_ORR, "orr", "orr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* eor $rd,$rn,$rm */
  {
    EPIPHANY_INSN_EOR16, "eor16", "eor", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* eor $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_EOR, "eor", "eor", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* add.s $rd,$rn,$simm3 */
  {
    EPIPHANY_INSN_ADDI16, "addi16", "add.s", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* add.l $rd6,$rn6,$simm11 */
  {
    EPIPHANY_INSN_ADDI, "addi", "add.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub.s $rd,$rn,$simm3 */
  {
    EPIPHANY_INSN_SUBI16, "subi16", "sub.s", 16,
    { 0|A(IMM3)|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* sub.l $rd6,$rn6,$simm11 */
  {
    EPIPHANY_INSN_SUBI, "subi", "sub.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* asr $rd,$rn,$rm */
  {
    EPIPHANY_INSN_ASR16, "asr16", "asr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* asr $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_ASR, "asr", "asr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsr $rd,$rn,$rm */
  {
    EPIPHANY_INSN_LSR16, "lsr16", "lsr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsr $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_LSR, "lsr", "lsr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsl $rd,$rn,$rm */
  {
    EPIPHANY_INSN_LSL16, "lsl16", "lsl", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsl $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_LSL, "lsl", "lsl", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsr $rd,$rn,$shift */
  {
    EPIPHANY_INSN_LSRI16, "lsri16", "lsr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsr $rd6,$rn6,$shift */
  {
    EPIPHANY_INSN_LSRI32, "lsri32", "lsr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsl $rd,$rn,$shift */
  {
    EPIPHANY_INSN_LSLI16, "lsli16", "lsl", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lsl $rd6,$rn6,$shift */
  {
    EPIPHANY_INSN_LSLI32, "lsli32", "lsl", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* asr $rd,$rn,$shift */
  {
    EPIPHANY_INSN_ASRI16, "asri16", "asr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* asr $rd6,$rn6,$shift */
  {
    EPIPHANY_INSN_ASRI32, "asri32", "asr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bitr $rd,$rn */
  {
    EPIPHANY_INSN_BITR16, "bitr16", "bitr", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* bitr $rd6,$rn6 */
  {
    EPIPHANY_INSN_BITR, "bitr", "bitr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fext $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_FEXT, "fext", "fext", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fdep $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_FDEP, "fdep", "fdep", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* lfsr $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_LFSR, "lfsr", "lfsr", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov.b $rd,$imm8 */
  {
    EPIPHANY_INSN_MOV8, "mov8", "mov.b", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* mov.l $rd6,$imm16 */
  {
    EPIPHANY_INSN_MOV16, "mov16", "mov.l", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* movt $rd6,$imm16 */
  {
    EPIPHANY_INSN_MOVT, "movt", "movt", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fadd $rd,$rn,$rm */
  {
    EPIPHANY_INSN_F_ADDF16, "f_addf16", "fadd", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fadd $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_F_ADDF32, "f_addf32", "fadd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fsub $rd,$rn,$rm */
  {
    EPIPHANY_INSN_F_SUBF16, "f_subf16", "fsub", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fsub $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_F_SUBF32, "f_subf32", "fsub", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fmul $rd,$rn,$rm */
  {
    EPIPHANY_INSN_F_MULF16, "f_mulf16", "fmul", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fmul $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_F_MULF32, "f_mulf32", "fmul", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fmadd $rd,$rn,$rm */
  {
    EPIPHANY_INSN_F_MADDF16, "f_maddf16", "fmadd", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fmadd $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_F_MADDF32, "f_maddf32", "fmadd", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fmsub $rd,$rn,$rm */
  {
    EPIPHANY_INSN_F_MSUBF16, "f_msubf16", "fmsub", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fmsub $rd6,$rn6,$rm6 */
  {
    EPIPHANY_INSN_F_MSUBF32, "f_msubf32", "fmsub", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fabs rd,rn */
  {
    EPIPHANY_INSN_F_ABSF16, "f_absf16", "fabs", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fabs $rd6,$rn6 */
  {
    EPIPHANY_INSN_F_ABSF32, "f_absf32", "fabs", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* float $rd,$rn */
  {
    EPIPHANY_INSN_F_LOATF16, "f_loatf16", "float", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* float $rd6,$rn6 */
  {
    EPIPHANY_INSN_F_LOATF32, "f_loatf32", "float", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fix $rd,$rn */
  {
    EPIPHANY_INSN_F_IXF16, "f_ixf16", "fix", 16,
    { 0|A(SHORT_INSN)|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fix $rd6,$rn6 */
  {
    EPIPHANY_INSN_F_IXF32, "f_ixf32", "fix", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* frecip $frd6,$frn6 */
  {
    EPIPHANY_INSN_F_RECIPF32, "f_recipf32", "frecip", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
/* fsqrt $frd6,$frn6 */
  {
    EPIPHANY_INSN_F_SQRTF32, "f_sqrtf32", "fsqrt", 32,
    { 0|A(COND_CTI), { { { (1<<MACH_BASE), 0 } } } }
  },
};

#undef OP
#undef A

/* Initialize anything needed to be done once, before any cpu_open call.  */

static void
init_tables (void)
{
}

static const CGEN_MACH * lookup_mach_via_bfd_name (const CGEN_MACH *, const char *);
static void build_hw_table      (CGEN_CPU_TABLE *);
static void build_ifield_table  (CGEN_CPU_TABLE *);
static void build_operand_table (CGEN_CPU_TABLE *);
static void build_insn_table    (CGEN_CPU_TABLE *);
static void epiphany_cgen_rebuild_tables (CGEN_CPU_TABLE *);

/* Subroutine of epiphany_cgen_cpu_open to look up a mach via its bfd name.  */

static const CGEN_MACH *
lookup_mach_via_bfd_name (const CGEN_MACH *table, const char *name)
{
  while (table->name)
    {
      if (strcmp (name, table->bfd_name) == 0)
	return table;
      ++table;
    }
  abort ();
}

/* Subroutine of epiphany_cgen_cpu_open to build the hardware table.  */

static void
build_hw_table (CGEN_CPU_TABLE *cd)
{
  int i;
  int machs = cd->machs;
  const CGEN_HW_ENTRY *init = & epiphany_cgen_hw_table[0];
  /* MAX_HW is only an upper bound on the number of selected entries.
     However each entry is indexed by it's enum so there can be holes in
     the table.  */
  const CGEN_HW_ENTRY **selected =
    (const CGEN_HW_ENTRY **) xmalloc (MAX_HW * sizeof (CGEN_HW_ENTRY *));

  cd->hw_table.init_entries = init;
  cd->hw_table.entry_size = sizeof (CGEN_HW_ENTRY);
  memset (selected, 0, MAX_HW * sizeof (CGEN_HW_ENTRY *));
  /* ??? For now we just use machs to determine which ones we want.  */
  for (i = 0; init[i].name != NULL; ++i)
    if (CGEN_HW_ATTR_VALUE (&init[i], CGEN_HW_MACH)
	& machs)
      selected[init[i].type] = &init[i];
  cd->hw_table.entries = selected;
  cd->hw_table.num_entries = MAX_HW;
}

/* Subroutine of epiphany_cgen_cpu_open to build the hardware table.  */

static void
build_ifield_table (CGEN_CPU_TABLE *cd)
{
  cd->ifld_table = & epiphany_cgen_ifld_table[0];
}

/* Subroutine of epiphany_cgen_cpu_open to build the hardware table.  */

static void
build_operand_table (CGEN_CPU_TABLE *cd)
{
  int i;
  int machs = cd->machs;
  const CGEN_OPERAND *init = & epiphany_cgen_operand_table[0];
  /* MAX_OPERANDS is only an upper bound on the number of selected entries.
     However each entry is indexed by it's enum so there can be holes in
     the table.  */
  const CGEN_OPERAND **selected = xmalloc (MAX_OPERANDS * sizeof (* selected));

  cd->operand_table.init_entries = init;
  cd->operand_table.entry_size = sizeof (CGEN_OPERAND);
  memset (selected, 0, MAX_OPERANDS * sizeof (CGEN_OPERAND *));
  /* ??? For now we just use mach to determine which ones we want.  */
  for (i = 0; init[i].name != NULL; ++i)
    if (CGEN_OPERAND_ATTR_VALUE (&init[i], CGEN_OPERAND_MACH)
	& machs)
      selected[init[i].type] = &init[i];
  cd->operand_table.entries = selected;
  cd->operand_table.num_entries = MAX_OPERANDS;
}

/* Subroutine of epiphany_cgen_cpu_open to build the hardware table.
   ??? This could leave out insns not supported by the specified mach/isa,
   but that would cause errors like "foo only supported by bar" to become
   "unknown insn", so for now we include all insns and require the app to
   do the checking later.
   ??? On the other hand, parsing of such insns may require their hardware or
   operand elements to be in the table [which they mightn't be].  */

static void
build_insn_table (CGEN_CPU_TABLE *cd)
{
  int i;
  const CGEN_IBASE *ib = & epiphany_cgen_insn_table[0];
  CGEN_INSN *insns = xmalloc (MAX_INSNS * sizeof (CGEN_INSN));

  memset (insns, 0, MAX_INSNS * sizeof (CGEN_INSN));
  for (i = 0; i < MAX_INSNS; ++i)
    insns[i].base = &ib[i];
  cd->insn_table.init_entries = insns;
  cd->insn_table.entry_size = sizeof (CGEN_IBASE);
  cd->insn_table.num_init_entries = MAX_INSNS;
}

/* Subroutine of epiphany_cgen_cpu_open to rebuild the tables.  */

static void
epiphany_cgen_rebuild_tables (CGEN_CPU_TABLE *cd)
{
  int i;
  CGEN_BITSET *isas = cd->isas;
  unsigned int machs = cd->machs;

  cd->int_insn_p = CGEN_INT_INSN_P;

  /* Data derived from the isa spec.  */
#define UNSET (CGEN_SIZE_UNKNOWN + 1)
  cd->default_insn_bitsize = UNSET;
  cd->base_insn_bitsize = UNSET;
  cd->min_insn_bitsize = 65535; /* Some ridiculously big number.  */
  cd->max_insn_bitsize = 0;
  for (i = 0; i < MAX_ISAS; ++i)
    if (cgen_bitset_contains (isas, i))
      {
	const CGEN_ISA *isa = & epiphany_cgen_isa_table[i];

	/* Default insn sizes of all selected isas must be
	   equal or we set the result to 0, meaning "unknown".  */
	if (cd->default_insn_bitsize == UNSET)
	  cd->default_insn_bitsize = isa->default_insn_bitsize;
	else if (isa->default_insn_bitsize == cd->default_insn_bitsize)
	  ; /* This is ok.  */
	else
	  cd->default_insn_bitsize = CGEN_SIZE_UNKNOWN;

	/* Base insn sizes of all selected isas must be equal
	   or we set the result to 0, meaning "unknown".  */
	if (cd->base_insn_bitsize == UNSET)
	  cd->base_insn_bitsize = isa->base_insn_bitsize;
	else if (isa->base_insn_bitsize == cd->base_insn_bitsize)
	  ; /* This is ok.  */
	else
	  cd->base_insn_bitsize = CGEN_SIZE_UNKNOWN;

	/* Set min,max insn sizes.  */
	if (isa->min_insn_bitsize < cd->min_insn_bitsize)
	  cd->min_insn_bitsize = isa->min_insn_bitsize;
	if (isa->max_insn_bitsize > cd->max_insn_bitsize)
	  cd->max_insn_bitsize = isa->max_insn_bitsize;
      }

  /* Data derived from the mach spec.  */
  for (i = 0; i < MAX_MACHS; ++i)
    if (((1 << i) & machs) != 0)
      {
	const CGEN_MACH *mach = & epiphany_cgen_mach_table[i];

	if (mach->insn_chunk_bitsize != 0)
	{
	  if (cd->insn_chunk_bitsize != 0 && cd->insn_chunk_bitsize != mach->insn_chunk_bitsize)
	    {
	      fprintf (stderr, "epiphany_cgen_rebuild_tables: conflicting insn-chunk-bitsize values: `%d' vs. `%d'\n",
		       cd->insn_chunk_bitsize, mach->insn_chunk_bitsize);
	      abort ();
	    }

 	  cd->insn_chunk_bitsize = mach->insn_chunk_bitsize;
	}
      }

  /* Determine which hw elements are used by MACH.  */
  build_hw_table (cd);

  /* Build the ifield table.  */
  build_ifield_table (cd);

  /* Determine which operands are used by MACH/ISA.  */
  build_operand_table (cd);

  /* Build the instruction table.  */
  build_insn_table (cd);
}

/* Initialize a cpu table and return a descriptor.
   It's much like opening a file, and must be the first function called.
   The arguments are a set of (type/value) pairs, terminated with
   CGEN_CPU_OPEN_END.

   Currently supported values:
   CGEN_CPU_OPEN_ISAS:    bitmap of values in enum isa_attr
   CGEN_CPU_OPEN_MACHS:   bitmap of values in enum mach_attr
   CGEN_CPU_OPEN_BFDMACH: specify 1 mach using bfd name
   CGEN_CPU_OPEN_ENDIAN:  specify endian choice
   CGEN_CPU_OPEN_END:     terminates arguments

   ??? Simultaneous multiple isas might not make sense, but it's not (yet)
   precluded.  */

CGEN_CPU_DESC
epiphany_cgen_cpu_open (enum cgen_cpu_open_arg arg_type, ...)
{
  CGEN_CPU_TABLE *cd = (CGEN_CPU_TABLE *) xmalloc (sizeof (CGEN_CPU_TABLE));
  static int init_p;
  CGEN_BITSET *isas = 0;  /* 0 = "unspecified" */
  unsigned int machs = 0; /* 0 = "unspecified" */
  enum cgen_endian endian = CGEN_ENDIAN_UNKNOWN;
  va_list ap;

  if (! init_p)
    {
      init_tables ();
      init_p = 1;
    }

  memset (cd, 0, sizeof (*cd));

  va_start (ap, arg_type);
  while (arg_type != CGEN_CPU_OPEN_END)
    {
      switch (arg_type)
	{
	case CGEN_CPU_OPEN_ISAS :
	  isas = va_arg (ap, CGEN_BITSET *);
	  break;
	case CGEN_CPU_OPEN_MACHS :
	  machs = va_arg (ap, unsigned int);
	  break;
	case CGEN_CPU_OPEN_BFDMACH :
	  {
	    const char *name = va_arg (ap, const char *);
	    const CGEN_MACH *mach =
	      lookup_mach_via_bfd_name (epiphany_cgen_mach_table, name);

	    machs |= 1 << mach->num;
	    break;
	  }
	case CGEN_CPU_OPEN_ENDIAN :
	  endian = va_arg (ap, enum cgen_endian);
	  break;
	default :
	  fprintf (stderr, "epiphany_cgen_cpu_open: unsupported argument `%d'\n",
		   arg_type);
	  abort (); /* ??? return NULL? */
	}
      arg_type = va_arg (ap, enum cgen_cpu_open_arg);
    }
  va_end (ap);

  /* Mach unspecified means "all".  */
  if (machs == 0)
    machs = (1 << MAX_MACHS) - 1;
  /* Base mach is always selected.  */
  machs |= 1;
  if (endian == CGEN_ENDIAN_UNKNOWN)
    {
      /* ??? If target has only one, could have a default.  */
      fprintf (stderr, "epiphany_cgen_cpu_open: no endianness specified\n");
      abort ();
    }

  cd->isas = cgen_bitset_copy (isas);
  cd->machs = machs;
  cd->endian = endian;
  /* FIXME: for the sparc case we can determine insn-endianness statically.
     The worry here is where both data and insn endian can be independently
     chosen, in which case this function will need another argument.
     Actually, will want to allow for more arguments in the future anyway.  */
  cd->insn_endian = endian;

  /* Table (re)builder.  */
  cd->rebuild_tables = epiphany_cgen_rebuild_tables;
  epiphany_cgen_rebuild_tables (cd);

  /* Default to not allowing signed overflow.  */
  cd->signed_overflow_ok_p = 0;

  return (CGEN_CPU_DESC) cd;
}

/* Cover fn to epiphany_cgen_cpu_open to handle the simple case of 1 isa, 1 mach.
   MACH_NAME is the bfd name of the mach.  */

CGEN_CPU_DESC
epiphany_cgen_cpu_open_1 (const char *mach_name, enum cgen_endian endian)
{
  return epiphany_cgen_cpu_open (CGEN_CPU_OPEN_BFDMACH, mach_name,
			       CGEN_CPU_OPEN_ENDIAN, endian,
			       CGEN_CPU_OPEN_END);
}

/* Close a cpu table.
   ??? This can live in a machine independent file, but there's currently
   no place to put this file (there's no libcgen).  libopcodes is the wrong
   place as some simulator ports use this but they don't use libopcodes.  */

void
epiphany_cgen_cpu_close (CGEN_CPU_DESC cd)
{
  unsigned int i;
  const CGEN_INSN *insns;

  if (cd->macro_insn_table.init_entries)
    {
      insns = cd->macro_insn_table.init_entries;
      for (i = 0; i < cd->macro_insn_table.num_init_entries; ++i, ++insns)
	if (CGEN_INSN_RX ((insns)))
	  regfree (CGEN_INSN_RX (insns));
    }

  if (cd->insn_table.init_entries)
    {
      insns = cd->insn_table.init_entries;
      for (i = 0; i < cd->insn_table.num_init_entries; ++i, ++insns)
	if (CGEN_INSN_RX (insns))
	  regfree (CGEN_INSN_RX (insns));
    }

  if (cd->macro_insn_table.init_entries)
    free ((CGEN_INSN *) cd->macro_insn_table.init_entries);

  if (cd->insn_table.init_entries)
    free ((CGEN_INSN *) cd->insn_table.init_entries);

  if (cd->hw_table.entries)
    free ((CGEN_HW_ENTRY *) cd->hw_table.entries);

  if (cd->operand_table.entries)
    free ((CGEN_HW_ENTRY *) cd->operand_table.entries);

  free (cd);
}

