[bits 64]

section .text

; Functions from MKMI
extern __mkmi_init
extern __mkmi_deinit
extern _exit
extern _return

; Functions found in the module
extern OnInit
extern OnExit 

; Global function declarations
global _start
global _end

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
	call OnInit 

	; Yeild back to the kernel
	mov rdi, rax ; Exit code
	call _return

	; If we fail, we go through to _end
	jmp _end

_end:
	; Run module deinitialization code
	call OnExit 
	
	; Make sure to save the exit code
	push rax
	
	; Deinit the MKMI library
	call __mkmi_deinit

	; Restore the exit code
	pop rax

	; Destroy the current process
	mov rdi, rax ; Exit code
	call _exit

	int 14 ; Just in case
