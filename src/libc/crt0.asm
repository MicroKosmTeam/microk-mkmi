[bits 64]

section .text

extern __mkmi_init
extern __mkmi_deinit

; Functions found in the module
extern Main 

global _start
_start:
	; We need this in a moment when we call Main
	push rdi ; Parent information

	; Initialize the MKMI library
	call __mkmi_init

	; Restore parent information
	pop rdi

	; Run module initialization code 
	call Main

	; Yeild back to the kernel
	mov rdi, rax ; Exit code
	call __mkmi_deinit

	; We're done
	jmp $
