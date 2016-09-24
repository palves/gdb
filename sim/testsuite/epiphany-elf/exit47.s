	;; Return with exit code 47.

	.globl _start
_start:
	mov r0,#47
	trap   3		; exit
        rts

