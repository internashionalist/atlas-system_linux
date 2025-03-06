BITS 64

global asm_strcspn

section .text

; asm_strcspn: 	    copycat strcspn(3) - calculate the length of the
;					initial segment of s (str)
; @s:				rdi (pointer to string to be searched)
; @reject:			rsi (pointer to string of characters to reject)
;
; Return:			rax (length of initial non-rejected segment of s)
;
; Prototype:		size_t asm_strcspn(const char *s, const char *reject);

asm_strcspn:
	; init return value
	xor		rax, rax			; init rax (count) to 0

.loopOuter:
	; iterate through s, checking each char against reject
	movzx	rcx, byte [rdi]		; load zero-extended current s char into rcx
	test	cl, cl				; check if s char is \0
	jz		.done				; if end of s, return count (rax)

	mov		rdx, rsi			; set rdx (inner ptr) to beginning of reject

.loopInner:
	; scan reject for current s char
	movzx	r8, byte [rdx]		; load zero-extended current reject char into r8
	test	r8b, r8b			; check if reject char is \0
	jz		.increment			; if end of reject, increment count (rax)
	cmp		cl, r8b				; compare current s char with current reject char
	je		.done				; if match, exit outer loop and return count
	inc		rdx					; move to next reject char
	jmp		.loopInner			; continue scanning reject

.increment:
	; current s char not found in reject, increment count and move to next s char
	inc		rax					; count++
	inc		rdi					; move to next s char
	jmp		.loopOuter			; continue scanning s

.done:
	; return count (rax)
	ret
