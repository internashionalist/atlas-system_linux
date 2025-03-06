BITS 64

global asm_memcpy

section .text

; asm_memcpy:   copycat memcpy(3) function - copies n bytes from memory area
;               src => dest - memcpy(3)
;
; @dest:		rdi (pointer to destination)
; @src:			rsi (pointer to source)
; @n:			rdx (number of bytes to copy)
;
; Return:		rax (start of dest)
;
; Prototype:	void *asm_memcpy(void *dest, const void *src, size_t n);

asm_memcpy:
	mov 			rax, rdi		; save dest in rax
	test 			rdx, rdx		; test if n == 0 (no bytes to copy)
	je 				.fin			; if n == 0, jump to .fin

.copy_loop:
	mov 			bl, [rsi]		; load byte from src to bl
	mov 			[rdi], bl		; store byte from bl to dest
	inc 			rsi				; move to next byte in src
	inc 			rdi				; move to next byte in dest
	dec 			rdx				; n--
	jnz 			.copy_loop		; continue until n == 0

.fin:
	ret								; rax set to original dest already
