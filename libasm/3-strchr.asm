BITS 64

section .text
    global asm_strchr

asm_strchr:
    xor rax, rax
    mov al, sil              ;will add to load targeted character
    
.next_character:
    movzx rdx, byte [rdi]    ; Load byte from string into rdx and zero-extend
    test dl, dl              ; Test if the byte is null terminator
    je .not_found            ; If null terminator, jump to not found

    cmp dl, sil               ; Compare the byte with the target character
    je .found                ; If match, jump to found

    inc rdi                  ; Move to the next byte in the string
    jmp .next_character      ; Repeat the loop

.not_found:
    xor rax, rax             ; Clear rax to return NULL (0)
    ret

.found:
    mov rax, rdi             ; Set rax to the address of the found character
