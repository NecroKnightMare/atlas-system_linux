section .data
section .text
global asm_strchr

asm_strchr:
    ; Arguments:
    ; rdi -> const char *s
    ; esi -> int c

    ; Save the registers we will use
    push rdi
    push rsi

    ; Load the character to search for into al
    mov al, byte [rsi]
    
    ; Iterate over the string
.loop:
    movzx rdx, byte [rdi]    ; Load byte from string into rdx and zero-extend
    test dl, dl              ; Test if the byte is null terminator
    je .not_found            ; If null terminator, jump to not found

    cmp dl, al               ; Compare the byte with the target character
    je .found                ; If match, jump to found

    inc rdi                  ; Move to the next byte in the string
    jmp .loop                ; Repeat the loop

.not_found:
    xor rax, rax             ; Clear rax to return NULL (0)
    jmp .exit

.found:
    mov rax, rdi             ; Set rax to the address of the found character

.exit:
    pop rsi                 ;take rsi off the stack
    pop rdi                 ;take rdi off of the stack
    ret
