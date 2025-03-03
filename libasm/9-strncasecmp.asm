BITS 64

global asm_strncasecmp

section .text

; asm_strncasecmp:		compares the first n bytes of two strings
; @str1:			rdi
; @str2:			rsi
; @n:				rdx
;
; Return:			eax (0 if str1 == str2 | n == 0, -1 if str1 < str2,
;						1 if str1 > str2)
;
; Prototype:		int asm_strncasecmp(
;						const char *str1, const char *str2, size_t n);

asm_strncasecmp:
	; null check
	test	rdx, rdx		; if n == 0, no need to compare
	je		.done

.loop:
	; loading screen
	mov		al, [rdi]		; load byte from s1
	mov		bl, [rsi]		; load byte from s2

	; s1 conversion
	cmp		al, 'A'			; check if s1 byte is uppercase
	jb		.notUpper_s1	; if al < 'A' (not uppercase), skip conversion
	cmp		al, 'Z'			; continue if al <= 'Z'
	ja		.notUpper_s1
	add		al, 0x20		; convert uppercase in s1 to lowercase

.notUpper_s1:
	; s2 conversion
	cmp		bl, 'A'			; check if s2 byte is uppercase
	jb		.notUpper_s2	; if bl < 'A', skip conversion
	cmp		bl, 'Z'			; continue if bl <= 'Z'
	ja		.notUpper_s2	; if bl > 'Z', skip conversion
	add		bl, 0x20		; convert uppercase in s2 to lowercase

.notUpper_s2:
	; compare the now lowercase characters in al and bl
	cmp		al, bl
	jne		.different		; if bytes differ, jump to .different
	test	al, al			; if bytes match, check if \0 reached
	je		.done			; if \0 reached && bytes match, return 0
	inc		rdi				; s1 pointer++
	inc		rsi				; s2 pointer++
	dec		rdx				; n--
	jnz		.loop			; rinse, repeat until n == 0

	jmp		.done			; if n == 0 and no \0 reached, return 0

.different:
	; find raw difference (al - bl) in eax
	movzx	eax, byte [rdi]	; zero-extend byte from s1
	cmp		eax, 'A'		; check if null terminator reached
	jb		.final_s1		; if al < 'A', jump to .final_s1
	cmp		eax, 'Z'		; check if null terminator reached
	ja		.final_s1		; if al > 'Z', jump to .final_s1
	add		eax, 0x20		; convert uppercase in s1 to lowercase

.final_s1:
	; find raw difference (al - bl) in ebx
	movzx	ebx, byte [rsi]	; zero-extend byte from s2
	cmp		ebx, 'A'		; check if null terminator reached
	jb		.final_s2		; if bl < 'A', jump to .final_s2
	cmp		ebx, 'Z'		; check if null terminator reached
	ja		.final_s2		; if bl > 'Z', jump to .final_s2
	add		ebx, 0x20		; convert uppercase in s2 to lowercase

.final_s2:
	; compute difference
	sub		eax, ebx		; (unsigned char)s1 - (unsigned char)s2
	ret

.done:
	; set return value to 0 if strings match or n == 0
	xor		eax, eax
	ret
