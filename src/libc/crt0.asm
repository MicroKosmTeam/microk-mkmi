[bits 64]

section .text

extern __mkmi_init
extern _return

extern ModuleInit

global _start
_start:
	; We need those in a moment when we call ModuleInit
	push rdi ; argc
	push rsi ; argv

	; Initialize the MKMI library
	call __mkmi_init

	; Restore argc and argv.
	pop rsi
	pop rdi

	; Run module initialization code 
	call ModuleInit

	; Return control to the kernel
	mov rdi, rax ; Exit code
	mov rsi, rsp ; Current stack
	call _return

	jmp $ ; Just in case


extern __mkmi_deinit
extern _exit

extern ModuleDeinit

global _end
_end:
	; Run module deinitialization code
	call ModuleDeinit
	
	; Make sure to save the exit code
	push rax
	
	; Deinit the MKMI library
	call __mkmi_deinit

	pop rax

	; Destroy the current process
	mov rdi, rax ; Exit code
	mov rsi, rsp ; Current stack
	call _exit

	jmp $ ; Just in case
