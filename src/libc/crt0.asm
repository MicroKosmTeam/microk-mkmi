[bits 64]

section .text

; Module functions
extern Main 

; MKMI functions
extern __mkmi_init
extern __mkmi_deinit

; Global function declarations
global _start

_start:
	; We get the virtual registers in RSI and their size in RDI

	; Save them
	push rdi
	push rsi

	; Initialize MKMI
	call __mkmi_init

	; Restore them
	pop rsi
	pop rdi

	; Call main
	call Main

	; Move the return code as the first argument
	mov rdi, rax

	; Deinitialize MKMI
	call __mkmi_deinit

	jmp $
