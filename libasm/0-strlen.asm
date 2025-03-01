global asm_strlen           ; global declaration of function

section .text               ; code section

; int asm_strlen(const char *str);
; @str: rdi
; Description: returns length of string = strlen (3)
;
; Return: rax (length of string)

asm_strlen:
	xor rax, rax            ; initialize rax to 0 (i = 0)

.loop:
	cmp byte [rdi + rax], 0 ; compare byte at rdi + rax (str + i) with 0
	je .done                ; once null terminated, jump to done
	inc rax                 ; increment i
	jmp .loop               ; rinse, repeat

.done:
	ret                     ; return i (rax) at end of string
