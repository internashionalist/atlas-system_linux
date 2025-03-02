BITS 64

global asm_strstr

section .text

; asm_strstr:		locates first occurrence of needle in haystack - strstr(3)
; @haystack:		rdi (pointer to searched string)
; @needle:			rsi (pointer to substring for which to search)
;
; Return:			rax (pointer to first occurrence of needle in haystack)
;					or NULL if needle not found
;
; Prototype:		char *asm_strstr(const char *haystack, const char *needle);

asm_strstr:
	mov			al, [rsi]		; load first byte of needle
	test		al, al			; check if byte is null
	jne			.init			; if not null, jump to .notEmpty
	mov			rax, rdi		; return haystack if needle is empty
	ret

.init:
	mov			rax, rdi		; save haystack pointer in rax
	xor			r8, r8			; r8 tracks number of bytes matched, init to 0

.loop:
	mov			dl, [rsi + r8]	; load byte from needle
	test		dl, dl			; check for end of needle
	je			.found			; if end of needle, jump to .found

	mov			bl, [rax]		; load byte from haystack
	test		bl, bl			; check for end of haystack
	je			.no_dice		; if end of haystack, jump to .no_dice

	cmp			bl, dl			; compare current bytes
	jne			.different		; if different, jump to .different

	inc			r8				; increment matched byte counter
	inc			rax				; move to next byte in haystack
	jmp			.loop			; repeat loop for next byte

.different:
	sub			rax, r8			; backtrack to start of current match
	inc			rax				; move to next byte in haystack
	xor			r8, r8			; reset matched byte counter
	jmp			.loop			; repeat loop for next byte

.found:
	sub			rax, r8			; backtrack to start of current match
	ret							; return pointer to first needle occurrence

.no_dice:
	xor			rax, rax		; needle not found
	ret							; return NULL

