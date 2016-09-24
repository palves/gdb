
	.globl _start
_start:

; write (hello world)
	mov	r0,1		; stdout
	
        mov	r1,HIGH(hello)
	lsl	r1,r1,16
	mov	v1,LOW(hello)
	add	r1,r1,v1	; form 32 bit address (yuck!)

	mov	r2,14		; len
	trap 	#0		; write
	
; exit (return status)
	trap	#3
	bpt			;should never get here.

length:	.long 14
hello:	.ascii "Hello World!\r\n"
