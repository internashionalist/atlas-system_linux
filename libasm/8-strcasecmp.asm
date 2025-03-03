BITS 64

global asm_strcasecmp

section .text

; asm_strcasecmp: 	compares two strings, ignoring case - strcasecmp(3)
; @str1:			rdi
; @str2:			rsi
;
; Return:			rax (0 if strings are equal, otherwise raw difference)
;
; Prototype:		int asm_strcasecmp(const char *s1, const char *s2);

asm_strcasecmp:
.loop:
	; loading screen
	mov			al, [rdi]		; load byte from s1
	mov			bl, [rsi]		; load byte from s2

	; convert al (str1) to lowercase
	cmp			al, 'A'			; 'A' = 0x41
	jb			.skip_s1		; if al < 'A', jump to .skip_s1
	cmp			al, 'Z'			; 'Z' = 0x5A
	ja			.skip_s1		; if al > 'Z', jump to .skip_s1
	add			al, 0x20		; convert uppercase in s1 to lowercase

.skip_s1:
	; convert bl (str2) to lowercase
	cmp			bl, 'A'			; 'A' = 0x41
	jb			.skip_s2		; if bl < 'A', jump to .skip_s2
	cmp			bl, 'Z'			; 'Z' = 0x5A
	ja			.skip_s2		; if bl > 'Z', jump to .skip_s2
	add			bl, 0x20		; convert uppercase in s2 to lowercase

.skip_s2:
	; compare lowercase characters in al and bl
	cmp			al, bl			; compare bytes
	jne			.different		; if bytes differ, jump to .different
	test		al, al			; if same, test if null terminator reached
	je			.equal			; if yes, jump to .equal
	inc			rdi				; s1 pointer++
	inc			rsi				; s2 pointer++
	jmp			.loop			; rinse, repeat

.different:
	; find raw difference (al - bl) in eax
	movzx		eax, byte [rdi]	; zero-extend byte from str1
	cmp			eax, 'A'		; check if null terminator reached
	jb			.skip1			; if al < 'A', jump to .skip1
	cmp			eax, 'Z'		; check if null terminator reached
	ja			.skip1			; if al > 'Z', jump to .skip1
	add			eax, 0x20		; convert uppercase in s1 to lowercase

.skip1:
	; find raw difference (al - bl) in ebx
	movzx		ebx, byte [rsi]	; zero-extend byte from s2
	cmp			ebx, 'A'		; check if null terminator reached
	jb			.skip2			; if bl < 'A', jump to .skip2
	cmp			ebx, 'Z'		; check if null terminator reached
	ja			.skip2			; if bl > 'Z', jump to .skip2
	add			ebx, 0x20		; convert uppercase in s2 to lowercase

.skip2:
	; compute difference
	sub			eax, ebx		; (unsigned char)s1 - (unsigned char)s2
	ret
	
.equal:
	; set return value to 0 if strings are equal
	xor			eax, eax		; set return value to 0
	ret
