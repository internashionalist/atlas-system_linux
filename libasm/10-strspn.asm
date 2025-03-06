BITS 64

global asm_strspn

section .text

; asm_strspn:		copycat strspn(3) - calculates the length of the
;                   initial segment of s (str) which consists only of
;                   characters in 'accept' - strspn(3)
;
; @s:				rdi (pointer to string to be searched)
; @accept:			rsi (pointer to string containing characters to match)
;
; Return:			rax (count of initial bytes in s that are in accept)
;
; Prototype:		size_t asm_strspn(const char *s, const char *accept);

asm_strspn:
	; init return value
	xor		rax, rax			; init rax (count) to 0

.loopOuter:
	; scan accept for current s char
	movzx	r8, byte [rdi]		; load current s char into r8 (zero-extended)
	test	r8b, r8b			; test for null terminator (end of s)
	jz		.done				; if end of s, jump to .done

	mov		rdx, rsi			; set rdx to beginning of accept

.loopInner:
	; scan s for current accept char
	movzx	rcx, byte [rdx]		; load current accept char into rcx
	test	cl, cl				; test for null terminator (end of accept)
	jz		.not_found			; current s char not found in accept
	cmp		r8b, cl				; compare current s char w current accept char
	je		.found				; if match, char is in accept
	inc		rdx					; move to next accept char
	jmp		.loopInner			; rinse, repeat

.found:
	; increment count and move to next s char
	inc		rax					; count++
	inc		rdi					; s++
	jmp		.loopOuter			; rinse, repeat (for next s char)

.not_found:
	; current s char not found in accept => return count
	jmp		.done

.done:
	; return count (rax)
	ret
