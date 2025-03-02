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
	jb			.skip_s1			; if al < 'A', jump to .skip_s1
	cmp			al, 'Z'			; 'Z' = 0x5A
	ja			.skip_s1			; if al > 'Z', jump to .skip_s1
	add			al, 0x20		; convert uppercase in str1 to lowercase

.skip_s1:
	; convert bl (str2) to lowercase
	cmp			bl, 'A'			; 'A' = 0x41
	jb			.skip_s2			; if bl < 'A', jump to .skip_s2
	cmp			bl, 'Z'			; 'Z' = 0x5A
	ja			.skip_s2			; if bl > 'Z', jump to .skip_s2
	add			bl, 0x20		; convert uppercase in str2 to lowercase

.skip_s2:
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
	cmp			eax, 'A'		; check if null terminator reached
	jb			.skip1		; if al < 'A', jump to .notupper1
	cmp			eax, 'Z'		; check if null terminator reached
	ja			.skip1		; if al > 'Z', jump to .notupper1
	add			eax, 0x20		; convert uppercase in str1 to lowercase

.skip1:
	; find raw difference (al - bl) in ebx
	movzx		ebx, byte [rsi]	; zero-extend byte from str2
	cmp			ebx, 'A'		; check if null terminator reached
	jb			.skip2			; if bl < 'A', jump to .skip2
	cmp			ebx, 'Z'		; check if null terminator reached
	ja			.skip2			; if bl > 'Z', jump to .skip2
	add			ebx, 0x20		; convert uppercase in str2 to lowercase

.skip2:
	; compute difference
	sub			eax, ebx		; (unsigned char)str1 - (unsigned char)str2
	ret
	
.equal:
	; set return value to 0 if strings are equal
	xor			eax, eax		; set return value to 0
	ret
