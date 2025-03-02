BITS 64

global asm_strcasecmp

section .text

; asm_strcasecmp: compares two strings, ignoring case - strcasecmp(3)
; @str1:			rdi
; @str2:			rsi
;
; Return:			rax (0 if str1 == str2, -1 if str1 < str2,
;					1 if str1 > str2)
;
; Prototype:		int asm_strcasecmp(const char *str1, const char *str2);

asm_strcasecmp:
.loop:
	; loading screen
	mov			al, [rdi]		; load byte from str1
	mov			bl, [rsi]		; load byte from str2

	; convert al (str1) to lowercase
	cmp			al, 'A'			; 'A' = 0x41
	jb			.not_upper1		; if al < 'A', jump to .not_upper1
	cmp			al, 'Z'			; 'Z' = 0x5A
	ja			.not_upper1		; if al > 'Z', jump to .not_upper1
	add			al, 0x20		; convert uppercase in str1 to lowercase

.not_upper1:
	; convert bl (str2) to lowercase
	cmp			bl, 'A'			; 'A' = 0x41
	jb			.not_upper2		; if bl < 'A', jump to .not_upper2
	cmp			bl, 'Z'			; 'Z' = 0x5A
	ja			.not_upper2		; if bl > 'Z', jump to .not_upper2
	add			bl, 0x20		; convert uppercase in str2 to lowercase

.not_upper2:
	; compare lowercase characters in al and bl
	cmp			al, bl			; compare bytes
	jne			.different		; if bytes differ, jump to .different
	test		al, al			; if same, test if null terminator reached
	je			.equal			; if yes, jump to .equal
	inc			rdi				; str1 pointer++
	inc			rsi				; str2 pointer++
	jmp			.loop			; rinse, repeat

.different:
	; find raw difference (al - bl) in eax
	movzx		eax, byte [rdi]	; zero-extend byte from str1
	movzx		ebx, byte [rsi]	; zero-extend byte from str2
	sub			eax, ebx		; (unsigned char)str1 - (unsigned char)str2
	cmp			eax, 0			; check if difference is 0
	jg			.positive		; if difference > 0, jump to .positive
	jl			.negative		; if difference < 0, jump to .negative
	xor			eax, eax		; if difference == 0, set return value to 0
	ret

.positive:
	mov			eax, 1			; difference > 0, set return value to 1
	ret

.negative:
	mov			eax, -1			; difference < 0, set return value to -1
	ret

.equal:
	; set return value to 0 if strings are equal
	xor			eax, eax		; set return value to 0
	ret
