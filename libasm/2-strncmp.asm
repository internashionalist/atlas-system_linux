BITS 64

global asm_strncmp

section .text

; asm_strncmp: 		compares up to n characters of two strings
; @str1:			rdi
; @str2:			rsi
; @n:				rdx
;
; Return:			rax (0 if str1 == str2, -1 if str1 < str2,
;						1 if str1 > str2)
;
; Prototype:		int asm_strncmp(
;						const char *str1, const char *str2, size_t n);

asm_strncmp:
	test 			rdx, rdx		; test if n == 0
	je 				.equal			; if n == 0, return 0

.loop:
	mov 			al, [rdi]		; load byte from str1
	mov 			bl, [rsi]		; load byte from str2
	cmp 			al, bl			; compare bytes
	jne 			.different		; if bytes differ, jump to .different
	test 			al, al			; if same, test if null terminator reached
	je				.equal			; if yes, jump to .equal
	inc 			rdi				; str1 pointer++
	inc 			rsi				; str2 pointer++
	dec 			rdx				; n--
	jnz 			.loop			; repeat loop until n == 0, then stop

.different:
	movzx 			eax, byte [rdi]	; zero-extend byte from str1
	movzx 			ebx, byte [rsi]	; zero-extend byte from str2
	sub 			eax, ebx		; (unsigned char)str1 - (unsigned char)str2
	cmp 			eax, 0			; check if difference is 0
	jg 				.positive		; if difference > 0, jump to .positive
	jl 				.negative		; if difference < 0, jump to .negative

.positive:
	mov 			eax, 1			; set return value to 1
	ret

.negative:
	mov 			eax, -1			; set return value to -1
	ret

.equal:
	xor 			eax, eax		; set return value to 0
	ret
