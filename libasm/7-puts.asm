BITS 64

extern asm_strlen
global asm_puts

section .text

; asm_puts:		prints a string to stdout - puts(3)
; @str:			rdi (pointer to string to print)
;
; Return:		rax (number of bytes written to stdout or -1 on error)
;
; Prototype:	void asm_puts(const char *str);

asm_puts:
	call	asm_strlen			; returns length of string in rax

	mov		rsi, rdi			; copy str to rsi
	mov		rdx, rax			; copy length of str to rdx
	mov		edi, 1				; file descriptor for stdout (1)
	mov		eax, 1				; syscall number for sys_write

	syscall						; write string to stdout

	ret							; number of bytes written or -1 on error
