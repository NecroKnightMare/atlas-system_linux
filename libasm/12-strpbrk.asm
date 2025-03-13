BITS 64

global asm_strpbrk

asm_strpbrk:
    mov r8, rdi             ; Save the original pointer to the haystack

main_loop:
    mov al, byte [rdi]      ; Load the next character from the haystack
    test al, al             ; Check if it’s the null terminator
    je not_found            ; If null, no match found

    mov r9, rsi             ; Set r9 to point to the charset

charset_loop:
    mov bl, byte [r9]       ; Load the next character from the charset
    test bl, bl             ; Check if it’s the null terminator
    je next_character       ; If null, move to the next character in haystack

    cmp al, bl              ; Compare the haystack character with the charset character
    je found                ; If match, jump to found

    inc r9                  ; Move to the next character in the charset
    jmp charset_loop

next_character:
    inc rdi                 ; Move to the next character in haystack
    jmp main_loop           ; Repeat the loop for haystack

found:
    mov rax, rdi            ; Set RAX to the current position in haystack
    ret

not_found:
    xor rax, rax            ; Set RAX to NULL 0
    ret
