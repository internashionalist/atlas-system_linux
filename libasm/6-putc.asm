BITS 64

global asm_putc

section .text

; asm_putc: 	copycat putc(3) function - writes a character to stdout
;
; @c:			rdi (character to write)
;
; Return:		number of bytes written or -1 on error
;
; Prototype:	void asm_putc(int c);

asm_putc:
	sub			rsp, 8			; align stack
	mov			[rsp], dil		; save c to stack (lower 8 bits)

	mov		eax, 1			; syscall number for sys_write
	mov		edi, 1			; file descriptor for stdout
	mov		rsi, rsp		; pointer to c (on the stack)
	mov		rdx, 1			; length of c (1 byte)

	syscall					; write character to stdout

	add			rsp, 8		; restore stack pointer
	ret						; bytes written or -1 on error
