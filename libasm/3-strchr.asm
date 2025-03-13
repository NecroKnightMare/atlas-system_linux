BITS 64

; segmentation fault when trying to find 'z'

section .text
    global asm_strchr

asm_strchr:
    xor rax, rax
    mov al, sil              ;will add to load targeted character

.next_character:
    mov al, byte [rdi]    ; Load byte from string into rdx and zero-extend
    test al, al              ; Test if the byte is null
    je .not_found            ; If null, jump to not found

    cmp al, sil               ; Compare the byte with the target character
    je .found                ; If match, jump to found

    inc rdi                  ; Move to the next byte in the string
    jmp .next_character      ; Repeat the loop

.not_found:
    xor rax, rax             ; Clear rax to return NULL 0
    jmp .exit

.found:
    mov rax, rdi             ; Set rax to the address of the found character
	ret

.exit:
    pop rdi					; restore
	ret