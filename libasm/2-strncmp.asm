BITS 64

global asm_strncmp

section .text

; asm_strncmp: 		copies strncmp (3) - compares up to n characters
;					of two strings
; @str1:			rdi
; @str2:			rsi
; @n:				rdx
;
; Return:			difference between first mismatched bytes
;					or 0 if strings match up to n or \0
;
; Prototype:		int asm_strncmp(
;						const char *str1, const char *str2, size_t n);

asm_strncmp:
	test 			rdx, rdx		; test if n == 0
	je 				.done		; if n == 0, return 0

.loop:
	mov 			al, [rdi]		; load byte from str1
	mov 			bl, [rsi]		; load byte from str2
	cmp 			al, bl			; compare bytes
	jne 			.different		; if bytes differ, jump to .different
	test 			al, al			; test for end of strings (\0)
	je				.done			; if yes, jump to .equal
	inc 			rdi				; move to next byte in str1
	inc 			rsi				; move to next byte in str2
	dec 			rdx				; n--
	jnz 			.loop			; continue unless n == 0
	jmp				.done			; if n bytes compared, return 0

.different:
	movzx 			eax, byte [rdi]	; zero-extend byte from str1
	movzx 			ebx, byte [rsi]	; zero-extend byte from str2
	sub 			eax, ebx		; return actual integer difference
	ret

.done:
	xor 			eax, eax		; indicates match up to n or \0
	ret
