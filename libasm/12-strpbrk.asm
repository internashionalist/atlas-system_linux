BITS 64

global asm_strpbrk

section .text

; asm_strpbrk:		copycat strpbrk(3) - locates first occurrence in the
;					string s of any character from the string accept
;
; @s:				rdi (pointer to string to be searched)
; @accept:			rsi (pointer to string containing characters to match)
;
; Return:			rax (pointer to the character in s that matches one of the
;					characters in accept) or NULL if no match is found
;
; Prototype:		char *asm_strpbrk(const char *s, const char *accept);

asm_strpbrk:
.outerLoop:
	; iterate over each char in s
	mov		al, [rdi]		; load current s char into al
	test	al, al			; test for null terminator (end of s)
	jz		.notFound		; if end of s, no match found => return NULL
	mov		rcx, rsi		; set rcx to beginning of accept

.innerLoop:
	; compare current s char with each char in accept
	mov		bl, [rcx]		; load current accept char into bl
	test	bl, bl			; test for null terminator (end of accept)
	jz		.nextChar		; if end of accept, move to next s char
	cmp		al, bl			; compare current s char with current accept char
	je		.Found			; if match, return pointer to current s char
	inc		rcx				; otherwise, move to next accept char
	jmp		.innerLoop		; rinse, repeat

.nextChar:
	; advance s pointer
	inc		rdi				; rdi++
	jmp		.outerLoop		; repeat outer loop

.Found:
	; return pointer to current s char
	mov		rax, rdi		; move current s char pointer to rax
	ret

.notFound:
	; return NULL
	xor		rax, rax		; set rax to NULL
	ret
