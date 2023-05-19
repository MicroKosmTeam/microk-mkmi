[bits 64]

section .text

extern _init
extern ModuleInit

global _start
_start:
	; We need those in a moment when we call main.
	push rsi
	push rdi

	; Prepare signals, memory allocation, stdio and such.
	;call initialize_standard_library

	; Run the global constructors.
	;call _init

	; Restore argc and argv.
	pop rdi
	pop rsi

	; Run main
	call ModuleInit 

	; Terminate the process with the exit code.
	mov rdi, rax
	call exit

exit:
	jmp $
