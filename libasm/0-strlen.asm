global asm_strlen           ; global declaration of function

section .text               ; code section

; asm_strlen: returns length of string = strlen (3)
; @str: rdi
;
; Return: rax (length of string)
;
; Prototype: size_t asm_strlen(const char *str);

asm_strlen:
	xor rax, rax            ; initialize rax to 0 (i = 0)

.loop:
	cmp byte [rdi + rax], 0 ; compare byte at rdi + rax (str + i) with 0
	je .return                ; once null terminated, jump to return
	inc rax                 ; increment i
	jmp .loop               ; rinse, repeat

.return:
	ret                     ; return i (rax) at end of string
