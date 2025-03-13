BITS 64
;still not getting 0 return

section .text
    global asm_strchr

asm_strchr:
    xor rax, rax
    mov al, sil              ;will add to load targeted character

	test rdi, rdi            ; Check if the string pointer is NULL
    jz .return               ; If NULL, return NULL

.next_character:
    mov al, byte [rdi]    ; Load byte from string into rdx and zero-extend
    test al, al              ; Test if the byte is null
    je .not_found            ; If null, jump to not found

    cmp al, sil               ; Compare the byte with the target character
    je .found                ; If match, jump to found

    inc rdi                  ; Move to the next byte in the string
    jmp .next_character

.not_found:
    xor rax, rax             ; Clear rax to return NULL 0
    ret

.found:
    mov rax, rdi             ; Set rax to the address of the found character
	ret

.return:
    xor rax, rax             ; Set RAX to NULL 0
    ret