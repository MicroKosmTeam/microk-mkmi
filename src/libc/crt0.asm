[bits 64]

section .text

extern Main 

; Global function declarations
global _start

_start:
	; We get the virtual registers in RSI and their size in RDI
	call Main

	jmp $
