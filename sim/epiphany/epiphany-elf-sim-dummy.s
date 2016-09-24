; Dummy binary used by epiphany-elf-sim.
;
; epiphany-elf-run requires a binary provided on the command line
; but when starting with --environment=operating that shouldn't be needed
; since then the user probably wants to interface with the simulator with a
; 'host' application, either through libesim.so or with libe-hal.so using the
; esim backend.

.set main_addr, 0x100

.type _main, %function
.global _main
.section .text

__ivt:
b _jump
.align 2
b _jump
.align 2
b _jump
.align 2
b _jump
.align 2
b _jump
.align 2
b _jump
.align 2
b _jump
.align 2
b _jump
.align 2
b _jump
.align 2
b _jump

_jump:
mov    r40, %low(#main_addr)
movt   r40, %high(#main_addr)
movts  iret, r40
rti

.org #main_addr
_main:
  gie
  idle

