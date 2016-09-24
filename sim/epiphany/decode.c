/* Simulator instruction decoder for epiphanybf.

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
#include "sim-assert.h"

/* The instruction descriptor array.
   This is computed at runtime.  Space for it is not malloc'd to save a
   teensy bit of cpu in the decoder.  Moving it to malloc space is trivial
   but won't be done until necessary (we don't currently support the runtime
   addition of instructions nor an SMP machine with different cpus).  */
static IDESC epiphanybf_insn_data[EPIPHANYBF_INSN__MAX];

/* Commas between elements are contained in the macros.
   Some of these are conditionally compiled out.  */

static const struct insn_sem epiphanybf_insn_sem[] =
{
  { VIRTUAL_INSN_X_INVALID, EPIPHANYBF_INSN_X_INVALID, EPIPHANYBF_SFMT_EMPTY },
  { VIRTUAL_INSN_X_AFTER, EPIPHANYBF_INSN_X_AFTER, EPIPHANYBF_SFMT_EMPTY },
  { VIRTUAL_INSN_X_BEFORE, EPIPHANYBF_INSN_X_BEFORE, EPIPHANYBF_SFMT_EMPTY },
  { VIRTUAL_INSN_X_CTI_CHAIN, EPIPHANYBF_INSN_X_CTI_CHAIN, EPIPHANYBF_SFMT_EMPTY },
  { VIRTUAL_INSN_X_CHAIN, EPIPHANYBF_INSN_X_CHAIN, EPIPHANYBF_SFMT_EMPTY },
  { VIRTUAL_INSN_X_BEGIN, EPIPHANYBF_INSN_X_BEGIN, EPIPHANYBF_SFMT_EMPTY },
  { EPIPHANY_INSN_BEQ16, EPIPHANYBF_INSN_BEQ16, EPIPHANYBF_SFMT_BEQ16 },
  { EPIPHANY_INSN_BEQ, EPIPHANYBF_INSN_BEQ, EPIPHANYBF_SFMT_BEQ },
  { EPIPHANY_INSN_BNE16, EPIPHANYBF_INSN_BNE16, EPIPHANYBF_SFMT_BEQ16 },
  { EPIPHANY_INSN_BNE, EPIPHANYBF_INSN_BNE, EPIPHANYBF_SFMT_BEQ },
  { EPIPHANY_INSN_BGTU16, EPIPHANYBF_INSN_BGTU16, EPIPHANYBF_SFMT_BGTU16 },
  { EPIPHANY_INSN_BGTU, EPIPHANYBF_INSN_BGTU, EPIPHANYBF_SFMT_BGTU },
  { EPIPHANY_INSN_BGTEU16, EPIPHANYBF_INSN_BGTEU16, EPIPHANYBF_SFMT_BGTEU16 },
  { EPIPHANY_INSN_BGTEU, EPIPHANYBF_INSN_BGTEU, EPIPHANYBF_SFMT_BGTEU },
  { EPIPHANY_INSN_BLTEU16, EPIPHANYBF_INSN_BLTEU16, EPIPHANYBF_SFMT_BGTU16 },
  { EPIPHANY_INSN_BLTEU, EPIPHANYBF_INSN_BLTEU, EPIPHANYBF_SFMT_BGTU },
  { EPIPHANY_INSN_BLTU16, EPIPHANYBF_INSN_BLTU16, EPIPHANYBF_SFMT_BGTEU16 },
  { EPIPHANY_INSN_BLTU, EPIPHANYBF_INSN_BLTU, EPIPHANYBF_SFMT_BGTEU },
  { EPIPHANY_INSN_BGT16, EPIPHANYBF_INSN_BGT16, EPIPHANYBF_SFMT_BGT16 },
  { EPIPHANY_INSN_BGT, EPIPHANYBF_INSN_BGT, EPIPHANYBF_SFMT_BGT },
  { EPIPHANY_INSN_BGTE16, EPIPHANYBF_INSN_BGTE16, EPIPHANYBF_SFMT_BGTE16 },
  { EPIPHANY_INSN_BGTE, EPIPHANYBF_INSN_BGTE, EPIPHANYBF_SFMT_BGTE },
  { EPIPHANY_INSN_BLT16, EPIPHANYBF_INSN_BLT16, EPIPHANYBF_SFMT_BGTE16 },
  { EPIPHANY_INSN_BLT, EPIPHANYBF_INSN_BLT, EPIPHANYBF_SFMT_BGTE },
  { EPIPHANY_INSN_BLTE16, EPIPHANYBF_INSN_BLTE16, EPIPHANYBF_SFMT_BGT16 },
  { EPIPHANY_INSN_BLTE, EPIPHANYBF_INSN_BLTE, EPIPHANYBF_SFMT_BGT },
  { EPIPHANY_INSN_BBEQ16, EPIPHANYBF_INSN_BBEQ16, EPIPHANYBF_SFMT_BBEQ16 },
  { EPIPHANY_INSN_BBEQ, EPIPHANYBF_INSN_BBEQ, EPIPHANYBF_SFMT_BBEQ },
  { EPIPHANY_INSN_BBNE16, EPIPHANYBF_INSN_BBNE16, EPIPHANYBF_SFMT_BBEQ16 },
  { EPIPHANY_INSN_BBNE, EPIPHANYBF_INSN_BBNE, EPIPHANYBF_SFMT_BBEQ },
  { EPIPHANY_INSN_BBLT16, EPIPHANYBF_INSN_BBLT16, EPIPHANYBF_SFMT_BBLT16 },
  { EPIPHANY_INSN_BBLT, EPIPHANYBF_INSN_BBLT, EPIPHANYBF_SFMT_BBLT },
  { EPIPHANY_INSN_BBLTE16, EPIPHANYBF_INSN_BBLTE16, EPIPHANYBF_SFMT_BBLT16 },
  { EPIPHANY_INSN_BBLTE, EPIPHANYBF_INSN_BBLTE, EPIPHANYBF_SFMT_BBLT },
  { EPIPHANY_INSN_B16, EPIPHANYBF_INSN_B16, EPIPHANYBF_SFMT_B16 },
  { EPIPHANY_INSN_B, EPIPHANYBF_INSN_B, EPIPHANYBF_SFMT_B },
  { EPIPHANY_INSN_BL16, EPIPHANYBF_INSN_BL16, EPIPHANYBF_SFMT_BL16 },
  { EPIPHANY_INSN_BL, EPIPHANYBF_INSN_BL, EPIPHANYBF_SFMT_BL },
  { EPIPHANY_INSN_JR16, EPIPHANYBF_INSN_JR16, EPIPHANYBF_SFMT_JR16 },
  { EPIPHANY_INSN_JR, EPIPHANYBF_INSN_JR, EPIPHANYBF_SFMT_JR },
  { EPIPHANY_INSN_JALR16, EPIPHANYBF_INSN_JALR16, EPIPHANYBF_SFMT_JALR16 },
  { EPIPHANY_INSN_JALR, EPIPHANYBF_INSN_JALR, EPIPHANYBF_SFMT_JALR },
  { EPIPHANY_INSN_LDRBX16_S, EPIPHANYBF_INSN_LDRBX16_S, EPIPHANYBF_SFMT_LDRBX16_S },
  { EPIPHANY_INSN_LDRBP16_S, EPIPHANYBF_INSN_LDRBP16_S, EPIPHANYBF_SFMT_LDRBP16_S },
  { EPIPHANY_INSN_LDRBX_L, EPIPHANYBF_INSN_LDRBX_L, EPIPHANYBF_SFMT_LDRBX_L },
  { EPIPHANY_INSN_LDRBP_L, EPIPHANYBF_INSN_LDRBP_L, EPIPHANYBF_SFMT_LDRBP_L },
  { EPIPHANY_INSN_LDRBD16_S, EPIPHANYBF_INSN_LDRBD16_S, EPIPHANYBF_SFMT_LDRBD16_S },
  { EPIPHANY_INSN_LDRBD_L, EPIPHANYBF_INSN_LDRBD_L, EPIPHANYBF_SFMT_LDRBD_L },
  { EPIPHANY_INSN_LDRBDPM_L, EPIPHANYBF_INSN_LDRBDPM_L, EPIPHANYBF_SFMT_LDRBDPM_L },
  { EPIPHANY_INSN_LDRHX16_S, EPIPHANYBF_INSN_LDRHX16_S, EPIPHANYBF_SFMT_LDRHX16_S },
  { EPIPHANY_INSN_LDRHP16_S, EPIPHANYBF_INSN_LDRHP16_S, EPIPHANYBF_SFMT_LDRHP16_S },
  { EPIPHANY_INSN_LDRHX_L, EPIPHANYBF_INSN_LDRHX_L, EPIPHANYBF_SFMT_LDRHX_L },
  { EPIPHANY_INSN_LDRHP_L, EPIPHANYBF_INSN_LDRHP_L, EPIPHANYBF_SFMT_LDRHP_L },
  { EPIPHANY_INSN_LDRHD16_S, EPIPHANYBF_INSN_LDRHD16_S, EPIPHANYBF_SFMT_LDRHD16_S },
  { EPIPHANY_INSN_LDRHD_L, EPIPHANYBF_INSN_LDRHD_L, EPIPHANYBF_SFMT_LDRHD_L },
  { EPIPHANY_INSN_LDRHDPM_L, EPIPHANYBF_INSN_LDRHDPM_L, EPIPHANYBF_SFMT_LDRHDPM_L },
  { EPIPHANY_INSN_LDRX16_S, EPIPHANYBF_INSN_LDRX16_S, EPIPHANYBF_SFMT_LDRX16_S },
  { EPIPHANY_INSN_LDRP16_S, EPIPHANYBF_INSN_LDRP16_S, EPIPHANYBF_SFMT_LDRP16_S },
  { EPIPHANY_INSN_LDRX_L, EPIPHANYBF_INSN_LDRX_L, EPIPHANYBF_SFMT_LDRX_L },
  { EPIPHANY_INSN_LDRP_L, EPIPHANYBF_INSN_LDRP_L, EPIPHANYBF_SFMT_LDRP_L },
  { EPIPHANY_INSN_LDRD16_S, EPIPHANYBF_INSN_LDRD16_S, EPIPHANYBF_SFMT_LDRD16_S },
  { EPIPHANY_INSN_LDRD_L, EPIPHANYBF_INSN_LDRD_L, EPIPHANYBF_SFMT_LDRD_L },
  { EPIPHANY_INSN_LDRDPM_L, EPIPHANYBF_INSN_LDRDPM_L, EPIPHANYBF_SFMT_LDRDPM_L },
  { EPIPHANY_INSN_LDRDX16_S, EPIPHANYBF_INSN_LDRDX16_S, EPIPHANYBF_SFMT_LDRDX16_S },
  { EPIPHANY_INSN_LDRDP16_S, EPIPHANYBF_INSN_LDRDP16_S, EPIPHANYBF_SFMT_LDRDP16_S },
  { EPIPHANY_INSN_LDRDX_L, EPIPHANYBF_INSN_LDRDX_L, EPIPHANYBF_SFMT_LDRDX_L },
  { EPIPHANY_INSN_LDRDP_L, EPIPHANYBF_INSN_LDRDP_L, EPIPHANYBF_SFMT_LDRDP_L },
  { EPIPHANY_INSN_LDRDD16_S, EPIPHANYBF_INSN_LDRDD16_S, EPIPHANYBF_SFMT_LDRDD16_S },
  { EPIPHANY_INSN_LDRDD_L, EPIPHANYBF_INSN_LDRDD_L, EPIPHANYBF_SFMT_LDRDD_L },
  { EPIPHANY_INSN_LDRDDPM_L, EPIPHANYBF_INSN_LDRDDPM_L, EPIPHANYBF_SFMT_LDRDDPM_L },
  { EPIPHANY_INSN_TESTSETBT, EPIPHANYBF_INSN_TESTSETBT, EPIPHANYBF_SFMT_TESTSETBT },
  { EPIPHANY_INSN_TESTSETHT, EPIPHANYBF_INSN_TESTSETHT, EPIPHANYBF_SFMT_TESTSETBT },
  { EPIPHANY_INSN_TESTSETT, EPIPHANYBF_INSN_TESTSETT, EPIPHANYBF_SFMT_TESTSETBT },
  { EPIPHANY_INSN_STRBX16, EPIPHANYBF_INSN_STRBX16, EPIPHANYBF_SFMT_STRBX16 },
  { EPIPHANY_INSN_STRBX, EPIPHANYBF_INSN_STRBX, EPIPHANYBF_SFMT_STRBX },
  { EPIPHANY_INSN_STRBP16, EPIPHANYBF_INSN_STRBP16, EPIPHANYBF_SFMT_STRBP16 },
  { EPIPHANY_INSN_STRBP, EPIPHANYBF_INSN_STRBP, EPIPHANYBF_SFMT_STRBP },
  { EPIPHANY_INSN_STRBD16, EPIPHANYBF_INSN_STRBD16, EPIPHANYBF_SFMT_STRBD16 },
  { EPIPHANY_INSN_STRBD, EPIPHANYBF_INSN_STRBD, EPIPHANYBF_SFMT_STRBD },
  { EPIPHANY_INSN_STRBDPM, EPIPHANYBF_INSN_STRBDPM, EPIPHANYBF_SFMT_STRBDPM },
  { EPIPHANY_INSN_STRHX16, EPIPHANYBF_INSN_STRHX16, EPIPHANYBF_SFMT_STRHX16 },
  { EPIPHANY_INSN_STRHX, EPIPHANYBF_INSN_STRHX, EPIPHANYBF_SFMT_STRHX },
  { EPIPHANY_INSN_STRHP16, EPIPHANYBF_INSN_STRHP16, EPIPHANYBF_SFMT_STRHP16 },
  { EPIPHANY_INSN_STRHP, EPIPHANYBF_INSN_STRHP, EPIPHANYBF_SFMT_STRHP },
  { EPIPHANY_INSN_STRHD16, EPIPHANYBF_INSN_STRHD16, EPIPHANYBF_SFMT_STRHD16 },
  { EPIPHANY_INSN_STRHD, EPIPHANYBF_INSN_STRHD, EPIPHANYBF_SFMT_STRHD },
  { EPIPHANY_INSN_STRHDPM, EPIPHANYBF_INSN_STRHDPM, EPIPHANYBF_SFMT_STRHDPM },
  { EPIPHANY_INSN_STRX16, EPIPHANYBF_INSN_STRX16, EPIPHANYBF_SFMT_STRX16 },
  { EPIPHANY_INSN_STRX, EPIPHANYBF_INSN_STRX, EPIPHANYBF_SFMT_STRX },
  { EPIPHANY_INSN_STRP16, EPIPHANYBF_INSN_STRP16, EPIPHANYBF_SFMT_STRP16 },
  { EPIPHANY_INSN_STRP, EPIPHANYBF_INSN_STRP, EPIPHANYBF_SFMT_STRP },
  { EPIPHANY_INSN_STRD16, EPIPHANYBF_INSN_STRD16, EPIPHANYBF_SFMT_STRD16 },
  { EPIPHANY_INSN_STRD, EPIPHANYBF_INSN_STRD, EPIPHANYBF_SFMT_STRD },
  { EPIPHANY_INSN_STRDPM, EPIPHANYBF_INSN_STRDPM, EPIPHANYBF_SFMT_STRDPM },
  { EPIPHANY_INSN_STRDX16, EPIPHANYBF_INSN_STRDX16, EPIPHANYBF_SFMT_STRDX16 },
  { EPIPHANY_INSN_STRDX, EPIPHANYBF_INSN_STRDX, EPIPHANYBF_SFMT_STRDX },
  { EPIPHANY_INSN_STRDP16, EPIPHANYBF_INSN_STRDP16, EPIPHANYBF_SFMT_STRDP16 },
  { EPIPHANY_INSN_STRDP, EPIPHANYBF_INSN_STRDP, EPIPHANYBF_SFMT_STRDP },
  { EPIPHANY_INSN_STRDD16, EPIPHANYBF_INSN_STRDD16, EPIPHANYBF_SFMT_STRDD16 },
  { EPIPHANY_INSN_STRDD, EPIPHANYBF_INSN_STRDD, EPIPHANYBF_SFMT_STRDD },
  { EPIPHANY_INSN_STRDDPM, EPIPHANYBF_INSN_STRDDPM, EPIPHANYBF_SFMT_STRDDPM },
  { EPIPHANY_INSN_CMOV16EQ, EPIPHANYBF_INSN_CMOV16EQ, EPIPHANYBF_SFMT_CMOV16EQ },
  { EPIPHANY_INSN_CMOVEQ, EPIPHANYBF_INSN_CMOVEQ, EPIPHANYBF_SFMT_CMOVEQ },
  { EPIPHANY_INSN_CMOV16NE, EPIPHANYBF_INSN_CMOV16NE, EPIPHANYBF_SFMT_CMOV16EQ },
  { EPIPHANY_INSN_CMOVNE, EPIPHANYBF_INSN_CMOVNE, EPIPHANYBF_SFMT_CMOVEQ },
  { EPIPHANY_INSN_CMOV16GTU, EPIPHANYBF_INSN_CMOV16GTU, EPIPHANYBF_SFMT_CMOV16GTU },
  { EPIPHANY_INSN_CMOVGTU, EPIPHANYBF_INSN_CMOVGTU, EPIPHANYBF_SFMT_CMOVGTU },
  { EPIPHANY_INSN_CMOV16GTEU, EPIPHANYBF_INSN_CMOV16GTEU, EPIPHANYBF_SFMT_CMOV16GTEU },
  { EPIPHANY_INSN_CMOVGTEU, EPIPHANYBF_INSN_CMOVGTEU, EPIPHANYBF_SFMT_CMOVGTEU },
  { EPIPHANY_INSN_CMOV16LTEU, EPIPHANYBF_INSN_CMOV16LTEU, EPIPHANYBF_SFMT_CMOV16GTU },
  { EPIPHANY_INSN_CMOVLTEU, EPIPHANYBF_INSN_CMOVLTEU, EPIPHANYBF_SFMT_CMOVGTU },
  { EPIPHANY_INSN_CMOV16LTU, EPIPHANYBF_INSN_CMOV16LTU, EPIPHANYBF_SFMT_CMOV16GTEU },
  { EPIPHANY_INSN_CMOVLTU, EPIPHANYBF_INSN_CMOVLTU, EPIPHANYBF_SFMT_CMOVGTEU },
  { EPIPHANY_INSN_CMOV16GT, EPIPHANYBF_INSN_CMOV16GT, EPIPHANYBF_SFMT_CMOV16GT },
  { EPIPHANY_INSN_CMOVGT, EPIPHANYBF_INSN_CMOVGT, EPIPHANYBF_SFMT_CMOVGT },
  { EPIPHANY_INSN_CMOV16GTE, EPIPHANYBF_INSN_CMOV16GTE, EPIPHANYBF_SFMT_CMOV16GTE },
  { EPIPHANY_INSN_CMOVGTE, EPIPHANYBF_INSN_CMOVGTE, EPIPHANYBF_SFMT_CMOVGTE },
  { EPIPHANY_INSN_CMOV16LT, EPIPHANYBF_INSN_CMOV16LT, EPIPHANYBF_SFMT_CMOV16GTE },
  { EPIPHANY_INSN_CMOVLT, EPIPHANYBF_INSN_CMOVLT, EPIPHANYBF_SFMT_CMOVGTE },
  { EPIPHANY_INSN_CMOV16LTE, EPIPHANYBF_INSN_CMOV16LTE, EPIPHANYBF_SFMT_CMOV16GT },
  { EPIPHANY_INSN_CMOVLTE, EPIPHANYBF_INSN_CMOVLTE, EPIPHANYBF_SFMT_CMOVGT },
  { EPIPHANY_INSN_CMOV16B, EPIPHANYBF_INSN_CMOV16B, EPIPHANYBF_SFMT_CMOV16B },
  { EPIPHANY_INSN_CMOVB, EPIPHANYBF_INSN_CMOVB, EPIPHANYBF_SFMT_CMOVB },
  { EPIPHANY_INSN_CMOV16BEQ, EPIPHANYBF_INSN_CMOV16BEQ, EPIPHANYBF_SFMT_CMOV16BEQ },
  { EPIPHANY_INSN_CMOVBEQ, EPIPHANYBF_INSN_CMOVBEQ, EPIPHANYBF_SFMT_CMOVBEQ },
  { EPIPHANY_INSN_CMOV16BNE, EPIPHANYBF_INSN_CMOV16BNE, EPIPHANYBF_SFMT_CMOV16BEQ },
  { EPIPHANY_INSN_CMOVBNE, EPIPHANYBF_INSN_CMOVBNE, EPIPHANYBF_SFMT_CMOVBEQ },
  { EPIPHANY_INSN_CMOV16BLT, EPIPHANYBF_INSN_CMOV16BLT, EPIPHANYBF_SFMT_CMOV16BLT },
  { EPIPHANY_INSN_CMOVBLT, EPIPHANYBF_INSN_CMOVBLT, EPIPHANYBF_SFMT_CMOVBLT },
  { EPIPHANY_INSN_CMOV16BLTE, EPIPHANYBF_INSN_CMOV16BLTE, EPIPHANYBF_SFMT_CMOV16BLT },
  { EPIPHANY_INSN_CMOVBLTE, EPIPHANYBF_INSN_CMOVBLTE, EPIPHANYBF_SFMT_CMOVBLT },
  { EPIPHANY_INSN_MOVTS16, EPIPHANYBF_INSN_MOVTS16, EPIPHANYBF_SFMT_MOVTS16 },
  { EPIPHANY_INSN_MOVTS6, EPIPHANYBF_INSN_MOVTS6, EPIPHANYBF_SFMT_MOVTS6 },
  { EPIPHANY_INSN_MOVTSDMA, EPIPHANYBF_INSN_MOVTSDMA, EPIPHANYBF_SFMT_MOVTSDMA },
  { EPIPHANY_INSN_MOVTSMEM, EPIPHANYBF_INSN_MOVTSMEM, EPIPHANYBF_SFMT_MOVTSMEM },
  { EPIPHANY_INSN_MOVTSMESH, EPIPHANYBF_INSN_MOVTSMESH, EPIPHANYBF_SFMT_MOVTSMESH },
  { EPIPHANY_INSN_MOVFS16, EPIPHANYBF_INSN_MOVFS16, EPIPHANYBF_SFMT_MOVFS16 },
  { EPIPHANY_INSN_MOVFS6, EPIPHANYBF_INSN_MOVFS6, EPIPHANYBF_SFMT_MOVFS6 },
  { EPIPHANY_INSN_MOVFSDMA, EPIPHANYBF_INSN_MOVFSDMA, EPIPHANYBF_SFMT_MOVFSDMA },
  { EPIPHANY_INSN_MOVFSMEM, EPIPHANYBF_INSN_MOVFSMEM, EPIPHANYBF_SFMT_MOVFSMEM },
  { EPIPHANY_INSN_MOVFSMESH, EPIPHANYBF_INSN_MOVFSMESH, EPIPHANYBF_SFMT_MOVFSMESH },
  { EPIPHANY_INSN_NOP, EPIPHANYBF_INSN_NOP, EPIPHANYBF_SFMT_NOP },
  { EPIPHANY_INSN_SNOP, EPIPHANYBF_INSN_SNOP, EPIPHANYBF_SFMT_NOP },
  { EPIPHANY_INSN_UNIMPL, EPIPHANYBF_INSN_UNIMPL, EPIPHANYBF_SFMT_NOP },
  { EPIPHANY_INSN_IDLE, EPIPHANYBF_INSN_IDLE, EPIPHANYBF_SFMT_IDLE },
  { EPIPHANY_INSN_BKPT, EPIPHANYBF_INSN_BKPT, EPIPHANYBF_SFMT_BKPT },
  { EPIPHANY_INSN_MBKPT, EPIPHANYBF_INSN_MBKPT, EPIPHANYBF_SFMT_MBKPT },
  { EPIPHANY_INSN_RTI, EPIPHANYBF_INSN_RTI, EPIPHANYBF_SFMT_RTI },
  { EPIPHANY_INSN_WAND, EPIPHANYBF_INSN_WAND, EPIPHANYBF_SFMT_WAND },
  { EPIPHANY_INSN_SYNC, EPIPHANYBF_INSN_SYNC, EPIPHANYBF_SFMT_NOP },
  { EPIPHANY_INSN_GIEN, EPIPHANYBF_INSN_GIEN, EPIPHANYBF_SFMT_NOP },
  { EPIPHANY_INSN_GIDIS, EPIPHANYBF_INSN_GIDIS, EPIPHANYBF_SFMT_GIDIS },
  { EPIPHANY_INSN_SWI_NUM, EPIPHANYBF_INSN_SWI_NUM, EPIPHANYBF_SFMT_SWI_NUM },
  { EPIPHANY_INSN_TRAP16, EPIPHANYBF_INSN_TRAP16, EPIPHANYBF_SFMT_TRAP16 },
  { EPIPHANY_INSN_ADD16, EPIPHANYBF_INSN_ADD16, EPIPHANYBF_SFMT_ADD16 },
  { EPIPHANY_INSN_ADD, EPIPHANYBF_INSN_ADD, EPIPHANYBF_SFMT_ADD },
  { EPIPHANY_INSN_SUB16, EPIPHANYBF_INSN_SUB16, EPIPHANYBF_SFMT_ADD16 },
  { EPIPHANY_INSN_SUB, EPIPHANYBF_INSN_SUB, EPIPHANYBF_SFMT_ADD },
  { EPIPHANY_INSN_AND16, EPIPHANYBF_INSN_AND16, EPIPHANYBF_SFMT_AND16 },
  { EPIPHANY_INSN_AND, EPIPHANYBF_INSN_AND, EPIPHANYBF_SFMT_AND },
  { EPIPHANY_INSN_ORR16, EPIPHANYBF_INSN_ORR16, EPIPHANYBF_SFMT_AND16 },
  { EPIPHANY_INSN_ORR, EPIPHANYBF_INSN_ORR, EPIPHANYBF_SFMT_AND },
  { EPIPHANY_INSN_EOR16, EPIPHANYBF_INSN_EOR16, EPIPHANYBF_SFMT_AND16 },
  { EPIPHANY_INSN_EOR, EPIPHANYBF_INSN_EOR, EPIPHANYBF_SFMT_AND },
  { EPIPHANY_INSN_ADDI16, EPIPHANYBF_INSN_ADDI16, EPIPHANYBF_SFMT_ADDI16 },
  { EPIPHANY_INSN_ADDI, EPIPHANYBF_INSN_ADDI, EPIPHANYBF_SFMT_ADDI },
  { EPIPHANY_INSN_SUBI16, EPIPHANYBF_INSN_SUBI16, EPIPHANYBF_SFMT_ADDI16 },
  { EPIPHANY_INSN_SUBI, EPIPHANYBF_INSN_SUBI, EPIPHANYBF_SFMT_ADDI },
  { EPIPHANY_INSN_ASR16, EPIPHANYBF_INSN_ASR16, EPIPHANYBF_SFMT_AND16 },
  { EPIPHANY_INSN_ASR, EPIPHANYBF_INSN_ASR, EPIPHANYBF_SFMT_AND },
  { EPIPHANY_INSN_LSR16, EPIPHANYBF_INSN_LSR16, EPIPHANYBF_SFMT_AND16 },
  { EPIPHANY_INSN_LSR, EPIPHANYBF_INSN_LSR, EPIPHANYBF_SFMT_AND },
  { EPIPHANY_INSN_LSL16, EPIPHANYBF_INSN_LSL16, EPIPHANYBF_SFMT_AND16 },
  { EPIPHANY_INSN_LSL, EPIPHANYBF_INSN_LSL, EPIPHANYBF_SFMT_AND },
  { EPIPHANY_INSN_LSRI16, EPIPHANYBF_INSN_LSRI16, EPIPHANYBF_SFMT_LSRI16 },
  { EPIPHANY_INSN_LSRI32, EPIPHANYBF_INSN_LSRI32, EPIPHANYBF_SFMT_LSRI32 },
  { EPIPHANY_INSN_LSLI16, EPIPHANYBF_INSN_LSLI16, EPIPHANYBF_SFMT_LSRI16 },
  { EPIPHANY_INSN_LSLI32, EPIPHANYBF_INSN_LSLI32, EPIPHANYBF_SFMT_LSRI32 },
  { EPIPHANY_INSN_ASRI16, EPIPHANYBF_INSN_ASRI16, EPIPHANYBF_SFMT_LSRI16 },
  { EPIPHANY_INSN_ASRI32, EPIPHANYBF_INSN_ASRI32, EPIPHANYBF_SFMT_LSRI32 },
  { EPIPHANY_INSN_BITR16, EPIPHANYBF_INSN_BITR16, EPIPHANYBF_SFMT_BITR16 },
  { EPIPHANY_INSN_BITR, EPIPHANYBF_INSN_BITR, EPIPHANYBF_SFMT_BITR },
  { EPIPHANY_INSN_FEXT, EPIPHANYBF_INSN_FEXT, EPIPHANYBF_SFMT_FEXT },
  { EPIPHANY_INSN_FDEP, EPIPHANYBF_INSN_FDEP, EPIPHANYBF_SFMT_FEXT },
  { EPIPHANY_INSN_LFSR, EPIPHANYBF_INSN_LFSR, EPIPHANYBF_SFMT_FEXT },
  { EPIPHANY_INSN_MOV8, EPIPHANYBF_INSN_MOV8, EPIPHANYBF_SFMT_MOV8 },
  { EPIPHANY_INSN_MOV16, EPIPHANYBF_INSN_MOV16, EPIPHANYBF_SFMT_MOV16 },
  { EPIPHANY_INSN_MOVT, EPIPHANYBF_INSN_MOVT, EPIPHANYBF_SFMT_MOVT },
  { EPIPHANY_INSN_F_ADDF16, EPIPHANYBF_INSN_F_ADDF16, EPIPHANYBF_SFMT_F_ADDF16 },
  { EPIPHANY_INSN_F_ADDF32, EPIPHANYBF_INSN_F_ADDF32, EPIPHANYBF_SFMT_F_ADDF32 },
  { EPIPHANY_INSN_F_SUBF16, EPIPHANYBF_INSN_F_SUBF16, EPIPHANYBF_SFMT_F_ADDF16 },
  { EPIPHANY_INSN_F_SUBF32, EPIPHANYBF_INSN_F_SUBF32, EPIPHANYBF_SFMT_F_ADDF32 },
  { EPIPHANY_INSN_F_MULF16, EPIPHANYBF_INSN_F_MULF16, EPIPHANYBF_SFMT_F_ADDF16 },
  { EPIPHANY_INSN_F_MULF32, EPIPHANYBF_INSN_F_MULF32, EPIPHANYBF_SFMT_F_ADDF32 },
  { EPIPHANY_INSN_F_MADDF16, EPIPHANYBF_INSN_F_MADDF16, EPIPHANYBF_SFMT_F_ADDF16 },
  { EPIPHANY_INSN_F_MADDF32, EPIPHANYBF_INSN_F_MADDF32, EPIPHANYBF_SFMT_F_ADDF32 },
  { EPIPHANY_INSN_F_MSUBF16, EPIPHANYBF_INSN_F_MSUBF16, EPIPHANYBF_SFMT_F_ADDF16 },
  { EPIPHANY_INSN_F_MSUBF32, EPIPHANYBF_INSN_F_MSUBF32, EPIPHANYBF_SFMT_F_ADDF32 },
  { EPIPHANY_INSN_F_ABSF16, EPIPHANYBF_INSN_F_ABSF16, EPIPHANYBF_SFMT_F_ABSF16 },
  { EPIPHANY_INSN_F_ABSF32, EPIPHANYBF_INSN_F_ABSF32, EPIPHANYBF_SFMT_F_ABSF32 },
  { EPIPHANY_INSN_F_LOATF16, EPIPHANYBF_INSN_F_LOATF16, EPIPHANYBF_SFMT_F_LOATF16 },
  { EPIPHANY_INSN_F_LOATF32, EPIPHANYBF_INSN_F_LOATF32, EPIPHANYBF_SFMT_F_ABSF32 },
  { EPIPHANY_INSN_F_IXF16, EPIPHANYBF_INSN_F_IXF16, EPIPHANYBF_SFMT_F_IXF16 },
  { EPIPHANY_INSN_F_IXF32, EPIPHANYBF_INSN_F_IXF32, EPIPHANYBF_SFMT_F_IXF32 },
  { EPIPHANY_INSN_F_RECIPF32, EPIPHANYBF_INSN_F_RECIPF32, EPIPHANYBF_SFMT_F_RECIPF32 },
  { EPIPHANY_INSN_F_SQRTF32, EPIPHANYBF_INSN_F_SQRTF32, EPIPHANYBF_SFMT_F_RECIPF32 },
};

static const struct insn_sem epiphanybf_insn_sem_invalid =
{
  VIRTUAL_INSN_X_INVALID, EPIPHANYBF_INSN_X_INVALID, EPIPHANYBF_SFMT_EMPTY
};

/* Initialize an IDESC from the compile-time computable parts.  */

static INLINE void
init_idesc (SIM_CPU *cpu, IDESC *id, const struct insn_sem *t)
{
  const CGEN_INSN *insn_table = CGEN_CPU_INSN_TABLE (CPU_CPU_DESC (cpu))->init_entries;

  id->num = t->index;
  id->sfmt = t->sfmt;
  if ((int) t->type <= 0)
    id->idata = & cgen_virtual_insn_table[- (int) t->type];
  else
    id->idata = & insn_table[t->type];
  id->attrs = CGEN_INSN_ATTRS (id->idata);
  /* Oh my god, a magic number.  */
  id->length = CGEN_INSN_BITSIZE (id->idata) / 8;

#if WITH_PROFILE_MODEL_P
  id->timing = & MODEL_TIMING (CPU_MODEL (cpu)) [t->index];
  {
    SIM_DESC sd = CPU_STATE (cpu);
    SIM_ASSERT (t->index == id->timing->num);
  }
#endif

  /* Semantic pointers are initialized elsewhere.  */
}

/* Initialize the instruction descriptor table.  */

void
epiphanybf_init_idesc_table (SIM_CPU *cpu)
{
  IDESC *id,*tabend;
  const struct insn_sem *t,*tend;
  int tabsize = EPIPHANYBF_INSN__MAX;
  IDESC *table = epiphanybf_insn_data;

  memset (table, 0, tabsize * sizeof (IDESC));

  /* First set all entries to the `invalid insn'.  */
  t = & epiphanybf_insn_sem_invalid;
  for (id = table, tabend = table + tabsize; id < tabend; ++id)
    init_idesc (cpu, id, t);

  /* Now fill in the values for the chosen cpu.  */
  for (t = epiphanybf_insn_sem, tend = t + sizeof (epiphanybf_insn_sem) / sizeof (*t);
       t != tend; ++t)
    {
      init_idesc (cpu, & table[t->index], t);
    }

  /* Link the IDESC table into the cpu.  */
  CPU_IDESC (cpu) = table;
}

/* Given an instruction, return a pointer to its IDESC entry.  */

const IDESC *
epiphanybf_decode (SIM_CPU *current_cpu, IADDR pc,
              CGEN_INSN_WORD base_insn, CGEN_INSN_WORD entire_insn,
              ARGBUF *abuf)
{
  /* Result of decoder.  */
  EPIPHANYBF_INSN_TYPE itype;

  {
    CGEN_INSN_WORD insn = base_insn;

    {
      unsigned int val = (((insn >> 0) & (15 << 0)));
      switch (val)
      {
      case 0 :
        {
          unsigned int val = (((insn >> 4) & (15 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_BEQ16; goto extract_sfmt_beq16;
          case 1 : itype = EPIPHANYBF_INSN_BNE16; goto extract_sfmt_beq16;
          case 2 : itype = EPIPHANYBF_INSN_BGTU16; goto extract_sfmt_bgtu16;
          case 3 : itype = EPIPHANYBF_INSN_BGTEU16; goto extract_sfmt_bgteu16;
          case 4 : itype = EPIPHANYBF_INSN_BLTEU16; goto extract_sfmt_bgtu16;
          case 5 : itype = EPIPHANYBF_INSN_BLTU16; goto extract_sfmt_bgteu16;
          case 6 : itype = EPIPHANYBF_INSN_BGT16; goto extract_sfmt_bgt16;
          case 7 : itype = EPIPHANYBF_INSN_BGTE16; goto extract_sfmt_bgte16;
          case 8 : itype = EPIPHANYBF_INSN_BLT16; goto extract_sfmt_bgte16;
          case 9 : itype = EPIPHANYBF_INSN_BLTE16; goto extract_sfmt_bgt16;
          case 10 : itype = EPIPHANYBF_INSN_BBEQ16; goto extract_sfmt_bbeq16;
          case 11 : itype = EPIPHANYBF_INSN_BBNE16; goto extract_sfmt_bbeq16;
          case 12 : itype = EPIPHANYBF_INSN_BBLT16; goto extract_sfmt_bblt16;
          case 13 : itype = EPIPHANYBF_INSN_BBLTE16; goto extract_sfmt_bblt16;
          case 14 : itype = EPIPHANYBF_INSN_B16; goto extract_sfmt_b16;
          case 15 : itype = EPIPHANYBF_INSN_BL16; goto extract_sfmt_bl16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 1 :
        {
          unsigned int val = (((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_LDRBX16_S; goto extract_sfmt_ldrbx16_s;
          case 1 : itype = EPIPHANYBF_INSN_STRBX16; goto extract_sfmt_strbx16;
          case 2 : itype = EPIPHANYBF_INSN_LDRHX16_S; goto extract_sfmt_ldrhx16_s;
          case 3 : itype = EPIPHANYBF_INSN_STRHX16; goto extract_sfmt_strhx16;
          case 4 : itype = EPIPHANYBF_INSN_LDRX16_S; goto extract_sfmt_ldrx16_s;
          case 5 : itype = EPIPHANYBF_INSN_STRX16; goto extract_sfmt_strx16;
          case 6 : itype = EPIPHANYBF_INSN_LDRDX16_S; goto extract_sfmt_ldrdx16_s;
          case 7 : itype = EPIPHANYBF_INSN_STRDX16; goto extract_sfmt_strdx16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 2 :
        {
          unsigned int val = (((insn >> 4) & (63 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_CMOV16EQ; goto extract_sfmt_cmov16EQ;
          case 1 : itype = EPIPHANYBF_INSN_CMOV16NE; goto extract_sfmt_cmov16EQ;
          case 2 : itype = EPIPHANYBF_INSN_CMOV16GTU; goto extract_sfmt_cmov16GTU;
          case 3 : itype = EPIPHANYBF_INSN_CMOV16GTEU; goto extract_sfmt_cmov16GTEU;
          case 4 : itype = EPIPHANYBF_INSN_CMOV16LTEU; goto extract_sfmt_cmov16GTU;
          case 5 : itype = EPIPHANYBF_INSN_CMOV16LTU; goto extract_sfmt_cmov16GTEU;
          case 6 : itype = EPIPHANYBF_INSN_CMOV16GT; goto extract_sfmt_cmov16GT;
          case 7 : itype = EPIPHANYBF_INSN_CMOV16GTE; goto extract_sfmt_cmov16GTE;
          case 8 : itype = EPIPHANYBF_INSN_CMOV16LT; goto extract_sfmt_cmov16GTE;
          case 9 : itype = EPIPHANYBF_INSN_CMOV16LTE; goto extract_sfmt_cmov16GT;
          case 10 : itype = EPIPHANYBF_INSN_CMOV16BEQ; goto extract_sfmt_cmov16BEQ;
          case 11 : itype = EPIPHANYBF_INSN_CMOV16BNE; goto extract_sfmt_cmov16BEQ;
          case 12 : itype = EPIPHANYBF_INSN_CMOV16BLT; goto extract_sfmt_cmov16BLT;
          case 13 : itype = EPIPHANYBF_INSN_CMOV16BLTE; goto extract_sfmt_cmov16BLT;
          case 14 : itype = EPIPHANYBF_INSN_CMOV16B; goto extract_sfmt_cmov16B;
          case 16 : itype = EPIPHANYBF_INSN_MOVTS16; goto extract_sfmt_movts16;
          case 17 : itype = EPIPHANYBF_INSN_MOVFS16; goto extract_sfmt_movfs16;
          case 20 :
            if ((entire_insn & 0xe3ff) == 0x142)
              { itype = EPIPHANYBF_INSN_JR16; goto extract_sfmt_jr16; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 21 :
            if ((entire_insn & 0xe3ff) == 0x152)
              { itype = EPIPHANYBF_INSN_JALR16; goto extract_sfmt_jalr16; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 24 :
            if ((entire_insn & 0xffff) == 0x182)
              { itype = EPIPHANYBF_INSN_WAND; goto extract_sfmt_wand; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 25 :
            if ((entire_insn & 0xffff) == 0x192)
              { itype = EPIPHANYBF_INSN_GIEN; goto extract_sfmt_nop; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 26 :
            if ((entire_insn & 0xffff) == 0x1a2)
              { itype = EPIPHANYBF_INSN_NOP; goto extract_sfmt_nop; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 27 :
            if ((entire_insn & 0xffff) == 0x1b2)
              { itype = EPIPHANYBF_INSN_IDLE; goto extract_sfmt_idle; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 28 :
            if ((entire_insn & 0xffff) == 0x1c2)
              { itype = EPIPHANYBF_INSN_BKPT; goto extract_sfmt_bkpt; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 29 :
            if ((entire_insn & 0xffff) == 0x1d2)
              { itype = EPIPHANYBF_INSN_RTI; goto extract_sfmt_rti; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 30 : itype = EPIPHANYBF_INSN_SWI_NUM; goto extract_sfmt_swi_num;
          case 31 :
            if ((entire_insn & 0xffff) == 0x1f2)
              { itype = EPIPHANYBF_INSN_SYNC; goto extract_sfmt_nop; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 57 :
            if ((entire_insn & 0xffff) == 0x392)
              { itype = EPIPHANYBF_INSN_GIDIS; goto extract_sfmt_gidis; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 58 :
            if ((entire_insn & 0xffff) == 0x3a2)
              { itype = EPIPHANYBF_INSN_SNOP; goto extract_sfmt_nop; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 60 :
            if ((entire_insn & 0xffff) == 0x3c2)
              { itype = EPIPHANYBF_INSN_MBKPT; goto extract_sfmt_mbkpt; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 62 : itype = EPIPHANYBF_INSN_TRAP16; goto extract_sfmt_trap16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 3 :
        {
          unsigned int val = (((insn >> 4) & (3 << 0)));
          switch (val)
          {
          case 0 : /* fall through */
          case 2 : itype = EPIPHANYBF_INSN_MOV8; goto extract_sfmt_mov8;
          case 1 :
            if ((entire_insn & 0x7f) == 0x13)
              { itype = EPIPHANYBF_INSN_ADDI16; goto extract_sfmt_addi16; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 3 :
            if ((entire_insn & 0x7f) == 0x33)
              { itype = EPIPHANYBF_INSN_SUBI16; goto extract_sfmt_addi16; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 4 :
        {
          unsigned int val = (((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_LDRBD16_S; goto extract_sfmt_ldrbd16_s;
          case 1 : itype = EPIPHANYBF_INSN_STRBD16; goto extract_sfmt_strbd16;
          case 2 : itype = EPIPHANYBF_INSN_LDRHD16_S; goto extract_sfmt_ldrhd16_s;
          case 3 : itype = EPIPHANYBF_INSN_STRHD16; goto extract_sfmt_strhd16;
          case 4 : itype = EPIPHANYBF_INSN_LDRD16_S; goto extract_sfmt_ldrd16_s;
          case 5 : itype = EPIPHANYBF_INSN_STRD16; goto extract_sfmt_strd16;
          case 6 : itype = EPIPHANYBF_INSN_LDRDD16_S; goto extract_sfmt_ldrdd16_s;
          case 7 : itype = EPIPHANYBF_INSN_STRDD16; goto extract_sfmt_strdd16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 5 :
        {
          unsigned int val = (((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_LDRBP16_S; goto extract_sfmt_ldrbp16_s;
          case 1 : itype = EPIPHANYBF_INSN_STRBP16; goto extract_sfmt_strbp16;
          case 2 : itype = EPIPHANYBF_INSN_LDRHP16_S; goto extract_sfmt_ldrhp16_s;
          case 3 : itype = EPIPHANYBF_INSN_STRHP16; goto extract_sfmt_strhp16;
          case 4 : itype = EPIPHANYBF_INSN_LDRP16_S; goto extract_sfmt_ldrp16_s;
          case 5 : itype = EPIPHANYBF_INSN_STRP16; goto extract_sfmt_strp16;
          case 6 : itype = EPIPHANYBF_INSN_LDRDP16_S; goto extract_sfmt_ldrdp16_s;
          case 7 : itype = EPIPHANYBF_INSN_STRDP16; goto extract_sfmt_strdp16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 6 :
        {
          unsigned int val = (((insn >> 4) & (1 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_LSRI16; goto extract_sfmt_lsri16;
          case 1 : itype = EPIPHANYBF_INSN_LSLI16; goto extract_sfmt_lsri16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 7 :
        {
          unsigned int val = (((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_F_ADDF16; goto extract_sfmt_f_addf16;
          case 1 : itype = EPIPHANYBF_INSN_F_SUBF16; goto extract_sfmt_f_addf16;
          case 2 : itype = EPIPHANYBF_INSN_F_MULF16; goto extract_sfmt_f_addf16;
          case 3 : itype = EPIPHANYBF_INSN_F_MADDF16; goto extract_sfmt_f_addf16;
          case 4 : itype = EPIPHANYBF_INSN_F_MSUBF16; goto extract_sfmt_f_addf16;
          case 5 : itype = EPIPHANYBF_INSN_F_LOATF16; goto extract_sfmt_f_loatf16;
          case 6 : itype = EPIPHANYBF_INSN_F_IXF16; goto extract_sfmt_f_ixf16;
          case 7 : itype = EPIPHANYBF_INSN_F_ABSF16; goto extract_sfmt_f_absf16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 8 :
        {
          unsigned int val = (((insn >> 4) & (15 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_BEQ; goto extract_sfmt_beq;
          case 1 : itype = EPIPHANYBF_INSN_BNE; goto extract_sfmt_beq;
          case 2 : itype = EPIPHANYBF_INSN_BGTU; goto extract_sfmt_bgtu;
          case 3 : itype = EPIPHANYBF_INSN_BGTEU; goto extract_sfmt_bgteu;
          case 4 : itype = EPIPHANYBF_INSN_BLTEU; goto extract_sfmt_bgtu;
          case 5 : itype = EPIPHANYBF_INSN_BLTU; goto extract_sfmt_bgteu;
          case 6 : itype = EPIPHANYBF_INSN_BGT; goto extract_sfmt_bgt;
          case 7 : itype = EPIPHANYBF_INSN_BGTE; goto extract_sfmt_bgte;
          case 8 : itype = EPIPHANYBF_INSN_BLT; goto extract_sfmt_bgte;
          case 9 : itype = EPIPHANYBF_INSN_BLTE; goto extract_sfmt_bgt;
          case 10 : itype = EPIPHANYBF_INSN_BBEQ; goto extract_sfmt_bbeq;
          case 11 : itype = EPIPHANYBF_INSN_BBNE; goto extract_sfmt_bbeq;
          case 12 : itype = EPIPHANYBF_INSN_BBLT; goto extract_sfmt_bblt;
          case 13 : itype = EPIPHANYBF_INSN_BBLTE; goto extract_sfmt_bblt;
          case 14 : itype = EPIPHANYBF_INSN_B; goto extract_sfmt_b;
          case 15 : itype = EPIPHANYBF_INSN_BL; goto extract_sfmt_bl;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 9 :
        {
          unsigned int val = (((insn >> 18) & (1 << 3)) | ((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 :
            if ((entire_insn & 0x6f007f) == 0x9)
              { itype = EPIPHANYBF_INSN_LDRBX_L; goto extract_sfmt_ldrbx_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 1 :
            if ((entire_insn & 0x6f007f) == 0x19)
              { itype = EPIPHANYBF_INSN_STRBX; goto extract_sfmt_strbx; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 2 :
            if ((entire_insn & 0x6f007f) == 0x29)
              { itype = EPIPHANYBF_INSN_LDRHX_L; goto extract_sfmt_ldrhx_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 3 :
            if ((entire_insn & 0x6f007f) == 0x39)
              { itype = EPIPHANYBF_INSN_STRHX; goto extract_sfmt_strhx; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 4 :
            if ((entire_insn & 0x6f007f) == 0x49)
              { itype = EPIPHANYBF_INSN_LDRX_L; goto extract_sfmt_ldrx_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 5 :
            if ((entire_insn & 0x6f007f) == 0x59)
              { itype = EPIPHANYBF_INSN_STRX; goto extract_sfmt_strx; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 6 :
            if ((entire_insn & 0x6f007f) == 0x69)
              { itype = EPIPHANYBF_INSN_LDRDX_L; goto extract_sfmt_ldrdx_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 7 :
            if ((entire_insn & 0x6f007f) == 0x79)
              { itype = EPIPHANYBF_INSN_STRDX; goto extract_sfmt_strdx; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 8 :
            if ((entire_insn & 0x6f007f) == 0x200009)
              { itype = EPIPHANYBF_INSN_TESTSETBT; goto extract_sfmt_testsetbt; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 10 :
            if ((entire_insn & 0x6f007f) == 0x200029)
              { itype = EPIPHANYBF_INSN_TESTSETHT; goto extract_sfmt_testsetbt; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 12 :
            if ((entire_insn & 0x6f007f) == 0x200049)
              { itype = EPIPHANYBF_INSN_TESTSETT; goto extract_sfmt_testsetbt; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 10 :
        {
          unsigned int val = (((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_EOR16; goto extract_sfmt_and16;
          case 1 : itype = EPIPHANYBF_INSN_ADD16; goto extract_sfmt_add16;
          case 2 : itype = EPIPHANYBF_INSN_LSL16; goto extract_sfmt_and16;
          case 3 : itype = EPIPHANYBF_INSN_SUB16; goto extract_sfmt_add16;
          case 4 : itype = EPIPHANYBF_INSN_LSR16; goto extract_sfmt_and16;
          case 5 : itype = EPIPHANYBF_INSN_AND16; goto extract_sfmt_and16;
          case 6 : itype = EPIPHANYBF_INSN_ASR16; goto extract_sfmt_and16;
          case 7 : itype = EPIPHANYBF_INSN_ORR16; goto extract_sfmt_and16;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 11 :
        {
          unsigned int val = (((insn >> 26) & (1 << 2)) | ((insn >> 4) & (3 << 0)));
          switch (val)
          {
          case 0 : /* fall through */
          case 2 :
            if ((entire_insn & 0x100f001f) == 0x2000b)
              { itype = EPIPHANYBF_INSN_MOV16; goto extract_sfmt_mov16; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 1 : /* fall through */
          case 5 :
            if ((entire_insn & 0x300007f) == 0x1b)
              { itype = EPIPHANYBF_INSN_ADDI; goto extract_sfmt_addi; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 3 : /* fall through */
          case 7 :
            if ((entire_insn & 0x300007f) == 0x3b)
              { itype = EPIPHANYBF_INSN_SUBI; goto extract_sfmt_addi; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 4 : /* fall through */
          case 6 :
            if ((entire_insn & 0x100f001f) == 0x1002000b)
              { itype = EPIPHANYBF_INSN_MOVT; goto extract_sfmt_movt; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 12 :
        {
          unsigned int val = (((insn >> 22) & (1 << 3)) | ((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_LDRBD_L; goto extract_sfmt_ldrbd_l;
          case 1 : itype = EPIPHANYBF_INSN_STRBD; goto extract_sfmt_strbd;
          case 2 : itype = EPIPHANYBF_INSN_LDRHD_L; goto extract_sfmt_ldrhd_l;
          case 3 : itype = EPIPHANYBF_INSN_STRHD; goto extract_sfmt_strhd;
          case 4 : itype = EPIPHANYBF_INSN_LDRD_L; goto extract_sfmt_ldrd_l;
          case 5 : itype = EPIPHANYBF_INSN_STRD; goto extract_sfmt_strd;
          case 6 : itype = EPIPHANYBF_INSN_LDRDD_L; goto extract_sfmt_ldrdd_l;
          case 7 : itype = EPIPHANYBF_INSN_STRDD; goto extract_sfmt_strdd;
          case 8 : itype = EPIPHANYBF_INSN_LDRBDPM_L; goto extract_sfmt_ldrbdpm_l;
          case 9 : itype = EPIPHANYBF_INSN_STRBDPM; goto extract_sfmt_strbdpm;
          case 10 : itype = EPIPHANYBF_INSN_LDRHDPM_L; goto extract_sfmt_ldrhdpm_l;
          case 11 : itype = EPIPHANYBF_INSN_STRHDPM; goto extract_sfmt_strhdpm;
          case 12 : itype = EPIPHANYBF_INSN_LDRDPM_L; goto extract_sfmt_ldrdpm_l;
          case 13 : itype = EPIPHANYBF_INSN_STRDPM; goto extract_sfmt_strdpm;
          case 14 : itype = EPIPHANYBF_INSN_LDRDDPM_L; goto extract_sfmt_ldrddpm_l;
          case 15 : itype = EPIPHANYBF_INSN_STRDDPM; goto extract_sfmt_strddpm;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 13 :
        {
          unsigned int val = (((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 :
            if ((entire_insn & 0x6f007f) == 0xd)
              { itype = EPIPHANYBF_INSN_LDRBP_L; goto extract_sfmt_ldrbp_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 1 :
            if ((entire_insn & 0x6f007f) == 0x1d)
              { itype = EPIPHANYBF_INSN_STRBP; goto extract_sfmt_strbp; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 2 :
            if ((entire_insn & 0x6f007f) == 0x2d)
              { itype = EPIPHANYBF_INSN_LDRHP_L; goto extract_sfmt_ldrhp_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 3 :
            if ((entire_insn & 0x6f007f) == 0x3d)
              { itype = EPIPHANYBF_INSN_STRHP; goto extract_sfmt_strhp; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 4 :
            if ((entire_insn & 0x6f007f) == 0x4d)
              { itype = EPIPHANYBF_INSN_LDRP_L; goto extract_sfmt_ldrp_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 5 :
            if ((entire_insn & 0x6f007f) == 0x5d)
              { itype = EPIPHANYBF_INSN_STRP; goto extract_sfmt_strp; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 6 :
            if ((entire_insn & 0x6f007f) == 0x6d)
              { itype = EPIPHANYBF_INSN_LDRDP_L; goto extract_sfmt_ldrdp_l; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 7 :
            if ((entire_insn & 0x6f007f) == 0x7d)
              { itype = EPIPHANYBF_INSN_STRDP; goto extract_sfmt_strdp; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 14 :
        {
          unsigned int val = (((insn >> 4) & (1 << 0)));
          switch (val)
          {
          case 0 : itype = EPIPHANYBF_INSN_ASRI16; goto extract_sfmt_lsri16;
          case 1 :
            if ((entire_insn & 0x3ff) == 0x1e)
              { itype = EPIPHANYBF_INSN_BITR16; goto extract_sfmt_bitr16; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      case 15 :
        {
          unsigned int val = (((insn >> 14) & (7 << 4)) | ((insn >> 13) & (1 << 3)) | ((insn >> 4) & (7 << 0)));
          switch (val)
          {
          case 0 :
            {
              unsigned int val = (((insn >> 19) & (1 << 2)) | ((insn >> 7) & (3 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x2000f)
                  { itype = EPIPHANYBF_INSN_CMOVEQ; goto extract_sfmt_cmovEQ; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x2008f)
                  { itype = EPIPHANYBF_INSN_CMOVLT; goto extract_sfmt_cmovGTE; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 2 :
                if ((entire_insn & 0x3ff03ff) == 0x2010f)
                  { itype = EPIPHANYBF_INSN_MOVTS6; goto extract_sfmt_movts6; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 6 :
                if ((entire_insn & 0x3ff03ff) == 0x22010f)
                  { itype = EPIPHANYBF_INSN_MOVTSMEM; goto extract_sfmt_movtsmem; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 1 :
            {
              unsigned int val = (((insn >> 19) & (1 << 2)) | ((insn >> 7) & (3 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x2001f)
                  { itype = EPIPHANYBF_INSN_CMOVNE; goto extract_sfmt_cmovEQ; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x2009f)
                  { itype = EPIPHANYBF_INSN_CMOVLTE; goto extract_sfmt_cmovGT; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 2 :
                if ((entire_insn & 0x3ff03ff) == 0x2011f)
                  { itype = EPIPHANYBF_INSN_MOVFS6; goto extract_sfmt_movfs6; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 6 :
                if ((entire_insn & 0x3ff03ff) == 0x22011f)
                  { itype = EPIPHANYBF_INSN_MOVFSMEM; goto extract_sfmt_movfsmem; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 2 :
            {
              unsigned int val = (((insn >> 7) & (1 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x2002f)
                  { itype = EPIPHANYBF_INSN_CMOVGTU; goto extract_sfmt_cmovGTU; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x200af)
                  { itype = EPIPHANYBF_INSN_CMOVBEQ; goto extract_sfmt_cmovBEQ; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 3 :
            {
              unsigned int val = (((insn >> 7) & (1 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x2003f)
                  { itype = EPIPHANYBF_INSN_CMOVGTEU; goto extract_sfmt_cmovGTEU; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x200bf)
                  { itype = EPIPHANYBF_INSN_CMOVBNE; goto extract_sfmt_cmovBEQ; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 4 :
            {
              unsigned int val = (((insn >> 7) & (3 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x2004f)
                  { itype = EPIPHANYBF_INSN_CMOVLTEU; goto extract_sfmt_cmovGTU; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x200cf)
                  { itype = EPIPHANYBF_INSN_CMOVBLT; goto extract_sfmt_cmovBLT; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 2 :
                if ((entire_insn & 0xe3ffe3ff) == 0x2014f)
                  { itype = EPIPHANYBF_INSN_JR; goto extract_sfmt_jr; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 5 :
            {
              unsigned int val = (((insn >> 7) & (3 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x2005f)
                  { itype = EPIPHANYBF_INSN_CMOVLTU; goto extract_sfmt_cmovGTEU; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x200df)
                  { itype = EPIPHANYBF_INSN_CMOVBLTE; goto extract_sfmt_cmovBLT; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 2 :
                if ((entire_insn & 0xe3ffe3ff) == 0x2015f)
                  { itype = EPIPHANYBF_INSN_JALR; goto extract_sfmt_jalr; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 6 :
            {
              unsigned int val = (((insn >> 7) & (1 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x2006f)
                  { itype = EPIPHANYBF_INSN_CMOVGT; goto extract_sfmt_cmovGT; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x200ef)
                  { itype = EPIPHANYBF_INSN_CMOVB; goto extract_sfmt_cmovB; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 7 :
            if ((entire_insn & 0x3ff03ff) == 0x2007f)
              { itype = EPIPHANYBF_INSN_CMOVGTE; goto extract_sfmt_cmovGTE; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 16 : /* fall through */
          case 18 : /* fall through */
          case 20 : /* fall through */
          case 22 :
            if ((entire_insn & 0x3ff001f) == 0x6000f)
              { itype = EPIPHANYBF_INSN_LSRI32; goto extract_sfmt_lsri32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 17 : /* fall through */
          case 19 : /* fall through */
          case 21 : /* fall through */
          case 23 :
            if ((entire_insn & 0x3ff001f) == 0x6001f)
              { itype = EPIPHANYBF_INSN_LSLI32; goto extract_sfmt_lsri32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 24 :
            if ((entire_insn & 0x7f007f) == 0x7000f)
              { itype = EPIPHANYBF_INSN_F_ADDF32; goto extract_sfmt_f_addf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 25 :
            if ((entire_insn & 0x7f007f) == 0x7001f)
              { itype = EPIPHANYBF_INSN_F_SUBF32; goto extract_sfmt_f_addf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 26 :
            if ((entire_insn & 0x7f007f) == 0x7002f)
              { itype = EPIPHANYBF_INSN_F_MULF32; goto extract_sfmt_f_addf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 27 :
            if ((entire_insn & 0x7f007f) == 0x7003f)
              { itype = EPIPHANYBF_INSN_F_MADDF32; goto extract_sfmt_f_addf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 28 :
            if ((entire_insn & 0x7f007f) == 0x7004f)
              { itype = EPIPHANYBF_INSN_F_MSUBF32; goto extract_sfmt_f_addf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 29 :
            if ((entire_insn & 0x7f007f) == 0x7005f)
              { itype = EPIPHANYBF_INSN_F_LOATF32; goto extract_sfmt_f_absf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 30 :
            if ((entire_insn & 0x7f007f) == 0x7006f)
              { itype = EPIPHANYBF_INSN_F_IXF32; goto extract_sfmt_f_ixf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 31 :
            if ((entire_insn & 0x7f007f) == 0x7007f)
              { itype = EPIPHANYBF_INSN_F_ABSF32; goto extract_sfmt_f_absf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 32 :
            if ((entire_insn & 0x7f007f) == 0xa000f)
              { itype = EPIPHANYBF_INSN_EOR; goto extract_sfmt_and; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 33 :
            if ((entire_insn & 0x7f007f) == 0xa001f)
              { itype = EPIPHANYBF_INSN_ADD; goto extract_sfmt_add; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 34 :
            if ((entire_insn & 0x7f007f) == 0xa002f)
              { itype = EPIPHANYBF_INSN_LSL; goto extract_sfmt_and; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 35 :
            if ((entire_insn & 0x7f007f) == 0xa003f)
              { itype = EPIPHANYBF_INSN_SUB; goto extract_sfmt_add; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 36 :
            if ((entire_insn & 0x7f007f) == 0xa004f)
              { itype = EPIPHANYBF_INSN_LSR; goto extract_sfmt_and; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 37 :
            if ((entire_insn & 0x7f007f) == 0xa005f)
              { itype = EPIPHANYBF_INSN_AND; goto extract_sfmt_and; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 38 :
            if ((entire_insn & 0x7f007f) == 0xa006f)
              { itype = EPIPHANYBF_INSN_ASR; goto extract_sfmt_and; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 39 :
            if ((entire_insn & 0x7f007f) == 0xa007f)
              { itype = EPIPHANYBF_INSN_ORR; goto extract_sfmt_and; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 48 : /* fall through */
          case 50 : /* fall through */
          case 52 : /* fall through */
          case 54 :
            if ((entire_insn & 0x3ff001f) == 0xe000f)
              { itype = EPIPHANYBF_INSN_ASRI32; goto extract_sfmt_lsri32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 49 :
            if ((entire_insn & 0x3ff03ff) == 0xe001f)
              { itype = EPIPHANYBF_INSN_BITR; goto extract_sfmt_bitr; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 56 :
            if ((entire_insn & 0xffffffff) == 0xf000f)
              { itype = EPIPHANYBF_INSN_UNIMPL; goto extract_sfmt_nop; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 64 :
            {
              unsigned int val = (((insn >> 21) & (1 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x12010f)
                  { itype = EPIPHANYBF_INSN_MOVTSDMA; goto extract_sfmt_movtsdma; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x32010f)
                  { itype = EPIPHANYBF_INSN_MOVTSMESH; goto extract_sfmt_movtsmesh; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 65 :
            {
              unsigned int val = (((insn >> 21) & (1 << 0)));
              switch (val)
              {
              case 0 :
                if ((entire_insn & 0x3ff03ff) == 0x12011f)
                  { itype = EPIPHANYBF_INSN_MOVFSDMA; goto extract_sfmt_movfsdma; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              case 1 :
                if ((entire_insn & 0x3ff03ff) == 0x32011f)
                  { itype = EPIPHANYBF_INSN_MOVFSMESH; goto extract_sfmt_movfsmesh; }
                itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
              }
            }
          case 88 :
            if ((entire_insn & 0x7f007f) == 0x17000f)
              { itype = EPIPHANYBF_INSN_F_RECIPF32; goto extract_sfmt_f_recipf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 89 :
            if ((entire_insn & 0x7f007f) == 0x17001f)
              { itype = EPIPHANYBF_INSN_F_SQRTF32; goto extract_sfmt_f_recipf32; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 96 :
            if ((entire_insn & 0x7f007f) == 0x1a000f)
              { itype = EPIPHANYBF_INSN_FEXT; goto extract_sfmt_fext; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 97 :
            if ((entire_insn & 0x7f007f) == 0x1a001f)
              { itype = EPIPHANYBF_INSN_FDEP; goto extract_sfmt_fext; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          case 98 :
            if ((entire_insn & 0x7f007f) == 0x1a002f)
              { itype = EPIPHANYBF_INSN_LFSR; goto extract_sfmt_fext; }
            itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
          }
        }
      default : itype = EPIPHANYBF_INSN_X_INVALID; goto extract_sfmt_empty;
      }
    }
  }

  /* The instruction has been decoded, now extract the fields.  */

 extract_sfmt_empty:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_empty", (char *) 0));

#undef FLD
    return idesc;
  }

 extract_sfmt_beq16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_beq16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_beq:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_beq", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgtu16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgtu16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgtu:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgtu", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgteu16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgteu16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgteu:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgteu", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgt16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgt16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgt:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgt", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgte16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgte16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bgte:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bgte", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bbeq16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bbeq16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bbeq:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bbeq", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bblt16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bblt16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bblt:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bblt", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_b16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_b16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_b:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_b", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bl16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl16.f
    SI f_simm8;

    f_simm8 = ((((EXTRACT_LSB0_SINT (insn, 16, 15, 8)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm8) = f_simm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bl16", "simm8 0x%x", 'x', f_simm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_h_registers_SI_14) = 14;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bl:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_bl.f
    SI f_simm24;

    f_simm24 = ((((EXTRACT_LSB0_SINT (insn, 32, 31, 24)) << (1))) + (pc));

  /* Record the fields for the semantic handler.  */
  FLD (i_simm24) = f_simm24;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bl", "simm24 0x%x", 'x', f_simm24, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_h_registers_SI_14) = 14;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_jr16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_jalr16.f
    UINT f_rn;

    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_jr16", "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_jr:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_jalr.f
    UINT f_rn_x;
    UINT f_rn;
    UINT f_rn6;

    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_jr", "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_jalr16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_jalr16.f
    UINT f_rn;

    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_jalr16", "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_h_registers_SI_14) = 14;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_jalr:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_jalr.f
    UINT f_rn_x;
    UINT f_rn;
    UINT f_rn6;

    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_jalr", "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_h_registers_SI_14) = 14;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrbx16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrbx16_s", "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrbp16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrbp16_s", "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrbx_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrbx_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrbp_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrbp_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrbd16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrbd16_s", "f_disp3 0x%x", 'x', f_disp3, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrbd_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrbd_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrbdpm_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrbdpm_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrhx16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrhx16_s", "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrhp16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrhp16_s", "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrhx_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrhx_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrhp_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrhp_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrhd16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrhd16_s", "f_disp3 0x%x", 'x', f_disp3, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrhd_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrhd_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrhdpm_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrhdpm_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrx16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrx16_s", "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrp16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrp16_s", "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrx_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrx_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrp_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrp_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrd16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrd16_s", "f_disp3 0x%x", 'x', f_disp3, "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrd_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrd_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrdpm_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrdpm_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrdx16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrdx16_s", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_h_registers_SI_add__INT_index_of__INT_rd_1) = ((FLD (f_rd)) + (1));
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrdp16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrdp16_s", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_h_registers_SI_add__INT_index_of__INT_rd_1) = ((FLD (f_rd)) + (1));
      FLD (out_rd) = f_rd;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrdx_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrdx_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrdp_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdp_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrdp_l", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrdd16_s:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrdd16_s.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrdd16_s", "f_disp3 0x%x", 'x', f_disp3, "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_h_registers_SI_add__INT_index_of__INT_rd_1) = ((FLD (f_rd)) + (1));
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrdd_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrdd_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_ldrddpm_l:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_ldrddpm_l.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_ldrddpm_l", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (out_rd6) = f_rd6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_testsetbt:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_testsetbt", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strbx16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strbx16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strbx:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strbx", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strbp16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strbp16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strbp:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strbp", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strbd16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdd16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strbd16", "f_disp3 0x%x", 'x', f_disp3, "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strbd:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strbd", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strbdpm:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strbdpm", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strhx16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strhx16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strhx:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strhx", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strhp16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strhp16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strhp:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strhp", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strhd16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdd16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strhd16", "f_disp3 0x%x", 'x', f_disp3, "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strhd:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strhd", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strhdpm:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strhdpm", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strx16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strx16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strx:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strx", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strp16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strp16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strp:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strp", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strd16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdd16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strd16", "f_disp3 0x%x", 'x', f_disp3, "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strd:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strd", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strdpm:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strdpm", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strdx16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strdx16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_h_registers_SI_add__INT_index_of__INT_rd_1) = ((FLD (f_rd)) + (1));
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strdx:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strdx", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strdp16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strdp16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_h_registers_SI_add__INT_index_of__INT_rd_1) = ((FLD (f_rd)) + (1));
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strdp:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdp.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_addsubx;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_addsubx = EXTRACT_LSB0_UINT (insn, 32, 20, 1);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_addsubx) = f_addsubx;
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strdp", "f_addsubx 0x%x", 'x', f_addsubx, "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strdd16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strdd16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_disp3) = f_disp3;
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strdd16", "f_disp3 0x%x", 'x', f_disp3, "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_h_registers_SI_add__INT_index_of__INT_rd_1) = ((FLD (f_rd)) + (1));
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strdd:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strdd", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_strddpm:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_strddpm.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_subd;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_disp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_subd = EXTRACT_LSB0_UINT (insn, 32, 24, 1);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_disp11 = ((((f_disp8) << (3))) | (f_disp3));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_disp11) = f_disp11;
  FLD (f_subd) = f_subd;
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_strddpm", "f_disp11 0x%x", 'x', f_disp11, "f_subd 0x%x", 'x', f_subd, "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_h_registers_SI_add__INT_index_of__INT_rd6_1) = ((FLD (f_rd6)) + (1));
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rn6) = f_rn6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16EQ:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16EQ", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovEQ:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovEQ", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16GTU:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16GTU", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovGTU:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovGTU", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16GTEU:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16GTEU", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovGTEU:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovGTEU", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16GT:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16GT", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovGT:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovGT", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16GTE:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16GTE", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovGTE:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovGTE", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16B:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16B", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovB:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovB", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16BEQ:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16BEQ", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovBEQ:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovBEQ", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmov16BLT:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rn) = f_rn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmov16BLT", "f_rn 0x%x", 'x', f_rn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_cmovBLT:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_cmovBLT", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movts16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movts16.f
    UINT f_rd;
    UINT f_sn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_sn) = f_sn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movts16", "f_rd 0x%x", 'x', f_rd, "f_sn 0x%x", 'x', f_sn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movts6:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movts6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_sn6) = f_sn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movts6", "f_rd6 0x%x", 'x', f_rd6, "f_sn6 0x%x", 'x', f_sn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movtsdma:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movts6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_sn6) = f_sn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movtsdma", "f_rd6 0x%x", 'x', f_rd6, "f_sn6 0x%x", 'x', f_sn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movtsmem:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movts6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_sn6) = f_sn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movtsmem", "f_rd6 0x%x", 'x', f_rd6, "f_sn6 0x%x", 'x', f_sn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movtsmesh:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movts6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_sn6) = f_sn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movtsmesh", "f_rd6 0x%x", 'x', f_rd6, "f_sn6 0x%x", 'x', f_sn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movfs16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movfs16.f
    UINT f_rd;
    UINT f_sn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_sn) = f_sn;
  FLD (f_rd) = f_rd;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movfs16", "f_sn 0x%x", 'x', f_sn, "f_rd 0x%x", 'x', f_rd, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movfs6:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movfs6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_sn6) = f_sn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movfs6", "f_sn6 0x%x", 'x', f_sn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movfsdma:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movfs6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_sn6) = f_sn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movfsdma", "f_sn6 0x%x", 'x', f_sn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movfsmem:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movfs6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_sn6) = f_sn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movfsmem", "f_sn6 0x%x", 'x', f_sn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movfsmesh:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movfs6.f
    UINT f_rd_x;
    UINT f_sn_x;
    UINT f_rd;
    UINT f_sn;
    UINT f_rd6;
    UINT f_sn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_sn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_sn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_sn6 = ((((f_sn_x) << (3))) | (f_sn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_sn6) = f_sn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movfsmesh", "f_sn6 0x%x", 'x', f_sn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_nop:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_nop", (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_idle:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_idle", (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bkpt:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bkpt", (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_mbkpt:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_mbkpt", (char *) 0));

#undef FLD
    return idesc;
  }

 extract_sfmt_rti:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_rti", (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_wand:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_wand", (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_gidis:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_gidis", (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_swi_num:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
#define FLD(f) abuf->fields.sfmt_empty.f


  /* Record the fields for the semantic handler.  */
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_swi_num", (char *) 0));

#undef FLD
    return idesc;
  }

 extract_sfmt_trap16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_trap16.f
    UINT f_trap_num;

    f_trap_num = EXTRACT_LSB0_UINT (insn, 16, 15, 6);

  /* Record the fields for the semantic handler.  */
  FLD (f_trap_num) = f_trap_num;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_trap16", "f_trap_num 0x%x", 'x', f_trap_num, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_h_registers_SI_0) = 0;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_add16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_add16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_add:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_add", "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_and16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_and16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_and:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_and", "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_addi16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_addi16.f
    UINT f_rd;
    UINT f_rn;
    INT f_sdisp3;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_sdisp3 = EXTRACT_LSB0_SINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  FLD (f_sdisp3) = f_sdisp3;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_addi16", "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, "f_sdisp3 0x%x", 'x', f_sdisp3, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_addi:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_addi.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_disp8;
    UINT f_rd;
    UINT f_rn;
    UINT f_disp3;
    UINT f_rd6;
    UINT f_rn6;
    INT f_sdisp11;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_disp8 = EXTRACT_LSB0_UINT (insn, 32, 23, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_disp3 = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_sdisp11 = ((SI) (((((((f_disp8) << (3))) | (f_disp3))) << (21))) >> (21));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  FLD (f_sdisp11) = f_sdisp11;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_addi", "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, "f_sdisp11 0x%x", 'x', f_sdisp11, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_lsri16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_shift;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_shift = EXTRACT_LSB0_UINT (insn, 16, 9, 5);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  FLD (f_shift) = f_shift;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_lsri16", "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, "f_shift 0x%x", 'x', f_shift, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_lsri32:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_shift;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_shift = EXTRACT_LSB0_UINT (insn, 32, 9, 5);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  FLD (f_shift) = f_shift;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_lsri32", "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, "f_shift 0x%x", 'x', f_shift, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bitr16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bitr16", "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_bitr:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_bitr", "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_fext:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movts6.f
    UINT f_rd_x;
    UINT f_rd;
    UINT f_rd6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_fext", "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_mov8:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_mov8.f
    UINT f_rd;
    UINT f_imm8;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_imm8 = EXTRACT_LSB0_UINT (insn, 16, 12, 8);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (i_imm8) = f_imm8;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_mov8", "f_rd 0x%x", 'x', f_rd, "imm8 0x%x", 'x', f_imm8, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_mov16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movt.f
    UINT f_rd_x;
    UINT f_imm_27_8;
    UINT f_rd;
    UINT f_imm8;
    UINT f_rd6;
    UINT f_imm16;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_imm_27_8 = EXTRACT_LSB0_UINT (insn, 32, 27, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_imm8 = EXTRACT_LSB0_UINT (insn, 32, 12, 8);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_imm16 = ((((f_imm_27_8) << (8))) | (f_imm8));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (i_imm16) = f_imm16;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_mov16", "f_rd6 0x%x", 'x', f_rd6, "imm16 0x%x", 'x', f_imm16, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_movt:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_movt.f
    UINT f_rd_x;
    UINT f_imm_27_8;
    UINT f_rd;
    UINT f_imm8;
    UINT f_rd6;
    UINT f_imm16;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_imm_27_8 = EXTRACT_LSB0_UINT (insn, 32, 27, 8);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_imm8 = EXTRACT_LSB0_UINT (insn, 32, 12, 8);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_imm16 = ((((f_imm_27_8) << (8))) | (f_imm8));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (i_imm16) = f_imm16;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_movt", "f_rd6 0x%x", 'x', f_rd6, "imm16 0x%x", 'x', f_imm16, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_addf16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_add16.f
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 16, 9, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rm) = f_rm;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_addf16", "f_rd 0x%x", 'x', f_rd, "f_rm 0x%x", 'x', f_rm, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rm) = f_rm;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_addf32:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_addf32", "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_absf16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_absf16", "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_absf32:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_absf32", "f_rd6 0x%x", 'x', f_rd6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_loatf16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_lsri16.f
    UINT f_rd;
    UINT f_rn;

    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_loatf16", "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_ixf16:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_f_ixf16.f
    UINT f_rd_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 16, 31, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 16, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 16, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd) = f_rd;
  FLD (f_rn) = f_rn;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_ixf16", "f_rd 0x%x", 'x', f_rd, "f_rn 0x%x", 'x', f_rn, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd) = f_rd;
      FLD (in_rn) = f_rn;
      FLD (out_rd) = f_rd;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_ixf32:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_testsetbt.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rm_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rm;
    UINT f_rd6;
    UINT f_rn6;
    UINT f_rm6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rm_x = EXTRACT_LSB0_UINT (insn, 32, 25, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
    f_rm = EXTRACT_LSB0_UINT (insn, 32, 9, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}
{
  f_rm6 = ((((f_rm_x) << (3))) | (f_rm));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rd6) = f_rd6;
  FLD (f_rm6) = f_rm6;
  FLD (f_rn6) = f_rn6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_ixf32", "f_rd6 0x%x", 'x', f_rd6, "f_rm6 0x%x", 'x', f_rm6, "f_rn6 0x%x", 'x', f_rn6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_rd6) = f_rd6;
      FLD (in_rm6) = f_rm6;
      FLD (in_rn6) = f_rn6;
      FLD (out_rd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

 extract_sfmt_f_recipf32:
  {
    const IDESC *idesc = &epiphanybf_insn_data[itype];
    CGEN_INSN_WORD insn = entire_insn;
#define FLD(f) abuf->fields.sfmt_f_recipf32.f
    UINT f_rd_x;
    UINT f_rn_x;
    UINT f_rd;
    UINT f_rn;
    UINT f_rd6;
    UINT f_rn6;

    f_rd_x = EXTRACT_LSB0_UINT (insn, 32, 31, 3);
    f_rn_x = EXTRACT_LSB0_UINT (insn, 32, 28, 3);
    f_rd = EXTRACT_LSB0_UINT (insn, 32, 15, 3);
    f_rn = EXTRACT_LSB0_UINT (insn, 32, 12, 3);
{
  f_rd6 = ((((f_rd_x) << (3))) | (f_rd));
}
{
  f_rn6 = ((((f_rn_x) << (3))) | (f_rn));
}

  /* Record the fields for the semantic handler.  */
  FLD (f_rn6) = f_rn6;
  FLD (f_rd6) = f_rd6;
  CGEN_TRACE_EXTRACT (current_cpu, abuf, (current_cpu, pc, "sfmt_f_recipf32", "f_rn6 0x%x", 'x', f_rn6, "f_rd6 0x%x", 'x', f_rd6, (char *) 0));

#if WITH_PROFILE_MODEL_P
  /* Record the fields for profiling.  */
  if (PROFILE_MODEL_P (current_cpu))
    {
      FLD (in_frn6) = f_rn6;
      FLD (out_frd6) = f_rd6;
    }
#endif
#undef FLD
    return idesc;
  }

}
