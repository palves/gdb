/* EPIPHANY simulator support code - derived from SH64
   Copyright (C) 2000, 2001, 2006, 2008, 2011 Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva, Inc.

This file is part of the GNU simulators.

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

#ifndef EPIPHANY_FP_H
#define EPIPHANY_FP_H

extern SI epiphany_iadd(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_imul(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_isub(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_imadd(SIM_CPU *current_cpu, SI , SI , SI );
extern SI epiphany_imsub(SIM_CPU *current_cpu, SI , SI , SI );


extern SI epiphany_fadd(SIM_CPU *current_cpu, SI fr0, SI frg, SI frh);
extern SI epiphany_fmul(SIM_CPU *current_cpu, SI fr0, SI frg, SI frh);
extern SI epiphany_fsub(SIM_CPU *current_cpu, SI fr0, SI frg, SI frh);
extern SI epiphany_fmadd(SIM_CPU *current_cpu, SI fr0, SI frm, SI frn);
extern SI epiphany_fmsub(SIM_CPU *current_cpu, SI fr0, SI frm, SI frn);
extern SI epiphany_fix(SIM_CPU *current_cpu,  SI fr0, SI frm, SI frn);
extern SI epiphany_float(SIM_CPU *current_cpu, SI fr0, SI frm, SI frn);
extern SI epiphany_fabs(SIM_CPU *current_cpu,  SI fr0, SI frm, SI frn);

extern SF epiphany_frecip(SIM_CPU *current_cpu, SF frg);

extern SF epiphany_fsqrt(SIM_CPU *current_cpu, SF frg);



extern BI get_epiphany_fzeroflag(SIM_CPU *current_cpu, unsigned res) ;
extern BI get_epiphany_fnegativeflag(SIM_CPU *current_cpu, unsigned res) ;
extern BI get_epiphany_funderflowflag(SIM_CPU *current_cpu, unsigned ) ;
extern BI get_epiphany_foverflowflag(SIM_CPU *current_cpu, unsigned ) ;
extern BI get_epiphany_finvalidflag(SIM_CPU *current_cpu, unsigned ) ;


/* Record changes to the CONFIG register in the CPU structure.  */
extern void epiphany_set_rounding_mode(SIM_CPU *cpu, int config);

#endif
