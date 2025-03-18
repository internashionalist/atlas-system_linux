BITS 64

global asm_strncasecmp

section .text

; asm_strncasecmp:		copycat strncasecmp(3) - compares the first
;						n bytes of two strings, ignoring case
;
; @s1:					rdi (pointer to current byte in s1)
; @s2:					rsi (pointer to current byte in s2)
; @n:					rdx (number of bytes to compare)
;
; Return:				eax (raw difference between first differing bytes,
;						or 0 if s1 == s2 | n == 0)
;
; Prototype:			int asm_strncasecmp(
;						    const char *s1, const char *s2, size_t n);

asm_strncasecmp:
	; save rdi and rsi to stack
	push	rdi
	push	rsi

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

	; otherwise, increment pointers, decrement n, and continue
	inc		rdi				; s1 pointer++
	inc		rsi				; s2 pointer++
	dec		rdx				; n--
	jnz		.loop			; rinse, repeat until n == 0

	; no more n == 0 return
	jmp		.done			; if n is exhausted, return 0

.different:
	; reread mismatched bytes from memory
	movzx	eax, al			; zero-extend byte from s1
	movzx	ebx, bl			; zero-extend byte from s2
	sub		eax, ebx		; compute difference (s1 - s2)
	jmp		.final			; return raw difference of first differing bytes

.done:
	; return 0 if strings are equal or n == 0
	xor     eax, eax		; return 0

.final:
	; restore rdi and rsi from the stack and return 
	pop		rsi
	pop		rdi
	ret
