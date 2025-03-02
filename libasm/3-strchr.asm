BITS 64

global asm_strchr

section .text

; asm_strchr:		locates first occurrence of c in str
; @str:				rdi
; @c:				esi (char passed as int)
;
; Return:			rax (pointer first c in str) or NULL if c not found
;
; Prototype:		char *asm_strchr(const char *str, int c);

asm_strchr:
	and		esi, 0xFF			; only lower 8 bits of c are relevant

.loop:
	mov		al, [rdi]			; load current byte from str
	cmp		al, sil				; compare byte with c (as char)
	je		.found				; if match found, jump to .found
	test	al, al				; check if current byte is \0
	je		.no_dice;			; if end of string, jump to .no_dice
	inc		rdi					; move to next byte
	jmp		.loop				; repeat loop until match or \0

.found:
	mov		rax, rdi			; move pointer to rax (first c in str)
	ret

.no_dice:
	xor		rax, rax			; return NULL in rax (c not found)
	ret
