global asm_strcmp

section .text

; asm_strcmp: compares two strings
; @str1:				rdi
; @str2:				rsi
;
; Return:				rax (0 if strings are equal, otherwise difference
;						between first two different characters)
;
; Prototype:			int asm_strcmp(const char *str1, const char *str2);

asm_strcmp:
.loop:						; compares str1 and str2
	mov 	al, [rdi]		; load byte from str1 into al
	mov 	bl, [rsi]		; load byte from str2 into bl
	cmp 	al, bl			; compare bytes
	jne 	.different		; if different, jump to .different
	cmp 	al, 0			; check if null terminator
	je 		.equal			; if yes, jump to .equal
	inc 	rdi				; increment str1 pointers
	inc 	rsi				; increment str2 pointers
	jmp 	.loop			; rinse, repeat

.different:
	movzx 	eax, byte [rdi]	; zero-extend byte from str1 into eax
	movzx 	ebx, byte [rsi]	; zero-extend byte from str2 into ebx
	sub 	eax, ebx		; compute difference (str1 - str2)
	cmp 	eax, 0			; check if difference is 0
	jg 		.positive		; if positive, jump to .positive
	jl 		.negative		; if negative, jump to .negative

.positive:
	mov 	eax, 1			; set eax to 1 (str1 > str2)
	ret						; return 1

.negative:
	mov 	eax, -1			; set eax to -1 (str1 < str2)
	ret						; return -1

.equal:
	xor 	eax, eax		; set eax to 0 (str1 == str2)
	ret						; return 0
