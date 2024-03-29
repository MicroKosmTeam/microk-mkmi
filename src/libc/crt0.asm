[bits 64]

section .text

extern Main 

; Global function declarations
global _start

_start:
	; Run module initialization code 
	call Main

	jmp $
