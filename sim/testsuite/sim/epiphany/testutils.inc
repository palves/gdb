# utility support for instruction testing -*- Asm -*-
# r0, r63 are used as tmps, consider them call clobbered by these macros.

        .set bvbit,1<<11
        .set bcbit,1<<10
        .set bnbit,1<<9
        .set bzbit,1<<8
        .set vbit,1<<7
        .set cbit,1<<6
        .set nbit,1<<5	
        .set zbit,1<<4
	
	.macro start
	.data
failmsg:
	.ascii "fail\n"
passmsg:
	.ascii "pass\n"
	.text
	.global _start
_start:
	.endm

	.macro exit rc
	mov	r0,\rc
	trap	#3
	.endm

	.macro pass
	trap	#4
	.endm

	
	.macro fail
	trap	#5
	.endm

	;; load 32-bit address
	.macro mova reg,addr
	mov	\reg,%low(\addr)
	movt	\reg,%high(\addr)
	.endm

	;; check that REG is zero
	.macro check reg
	add \reg,\reg,0		;set ccs
	bne  1f
	pass
1:	fail
	.endm

	;; Check that REG is equal to 16 bit literal VAL
	;;  (clobbers r63,r0)
	.macro compare reg,val
	mov    r63,\val
	sub    r0,\reg,r63      ; set ccs
	bne  1f
	pass
1:	fail
	.endm

