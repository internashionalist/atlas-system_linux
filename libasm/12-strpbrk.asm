BITS 64

global asm_strpbrk

section .text

; asm_strpbrk:		copycat strpbrk(3) - locates first occurrence in the string s of
;		   			any character from the string accept
;
; @s:				rdi (pointer to string to be searched)
; @accept:			rsi (pointer to string containing characters to match)
;
; Return:			rax (pointer to the character in s that matches one of the
;					characters in accept) or NULL if no match is found
;

asm_strpbrk:
	; init return value
	xor		rax, rax			; init rax (pointer) to NULL