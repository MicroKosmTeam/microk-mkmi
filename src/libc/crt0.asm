[bits 64]

section .text

extern __mkmi_init
extern __mkmi_deinit

; Functions found in the module
extern Main 

global _start
_start:
	; We need those in a moment when we call Main
	push rdi ; argc
	push rsi ; argv

	; Initialize the MKMI library
	call __mkmi_init

	; Restore argc and argv.
	pop rsi
	pop rdi

	; Run module initialization code 
	call Main

	; Yeild back to the kernel
	mov rdi, rax ; Exit code
	call __mkmi_deinit

	; We're done
	jmp $
