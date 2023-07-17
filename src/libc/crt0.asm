[bits 64]

section .text

extern __mkmi_init
extern __mkmi_deinit

extern _exit
extern _return

extern OnInit
extern OnExit 
extern OnMessage
extern OnSignal

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
	call OnInit 

	; Return control to the kernel
	mov rdi, rax ; Exit code
	mov rsi, rsp ; Current stack
	call _return

	int 14 ; Just in case

global __message_handler
__message_handler:
	call OnMessage 

	; Return control to the kernel
	mov rdi, rax ; Exit code
	mov rsi, rsp ; Current stack
	call _return

	int 14 ; Just in case

global __signal_handler
__signal_handler:
	call OnSignal

	; Return control to the kernel
	mov rdi, rax ; Exit code
	mov rsi, rsp ; Current stack
	call _return

	int 14 ; Just in case
global _end
_end:
	; Run module deinitialization code
	call OnExit 
	
	; Make sure to save the exit code
	push rax
	
	; Deinit the MKMI library
	call __mkmi_deinit

	pop rax

	; Destroy the current process
	mov rdi, rax ; Exit code
	mov rsi, rsp ; Current stack
	call _exit

	int 14 ; Just in case
