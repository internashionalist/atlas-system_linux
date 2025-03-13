BITS 64

global asm_strcasecmp

section .text

; asm_strcasecmp: 	copycat strcasecmp(3) - compares two strings,
;                   ignoring case
;
; @s1:		    	rdi (pointer to string 1)
; @s2:		    	rsi (pointer to string 2)
;
; Return:			rax (0 if strings are equal, otherwise raw difference)
;
; Prototype:		int asm_strcasecmp(const char *s1, const char *s2);

asm_strcasecmp:
	; save rdi and rsi on the stack
	push        rdi
	push        rsi

.loop:
	; loading screen
	mov			al, [rdi]		; load byte from s1
	mov			bl, [rsi]		; load byte from s2

	; convert al (str1) to lowercase
	cmp			al, 'A'			; 'A' = 0x41
	jb			.notUpper_s1		; if al < 'A', jump to .skip_s1
	cmp			al, 'Z'			; 'Z' = 0x5A
	ja			.notUpper_s1  	; if al > 'Z', jump to .skip_s1
	add			al, 0x20		; convert uppercase in s1 to lowercase

.notUpper_s1:
	; convert bl (str2) to lowercase
	cmp			bl, 'A'			; 'A' = 0x41
	jb			.notUpper_s2		; if bl < 'A', jump to .skip_s2
	cmp			bl, 'Z'			; 'Z' = 0x5A
	ja			.notUpper_s2	; if bl > 'Z', jump to .skip_s2
	add			bl, 0x20		; convert uppercase in s2 to lowercase

.notUpper_s2:
	; compare lowercase characters in al and bl
	cmp			al, bl			; compare bytes
	jne			.different		; if bytes differ, jump to .different
	test		al, al			; if same, test if null terminator reached
	je			.equal			; if yes, jump to .equal

	; otherwise, increment pointers and repeat loop
	inc			rdi				; s1 pointer++
	inc			rsi				; s2 pointer++
	jmp			.loop			; rinse, repeat

.different:
	; find raw difference (al - bl) in eax
	movzx       eax, al         ; zero-extend byte from s1
	movzx       ebx, bl         ; zero-extend byte from s2
	sub         eax, ebx        ; (unsigned char)str1 - (unsigned char)str2
	jmp         .final

.equal:
	; set return value to 0 if strings are equal
	xor			eax, eax		; set return value to 0

.final:
	; restore rdi and rsi from the stack
	pop			rsi				; restore rsi
	pop			rdi				; restore rdi
	ret							; return result
