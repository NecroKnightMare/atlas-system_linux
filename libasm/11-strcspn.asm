BITS 64

global asm_strcspn

asm_strcspn:
    xor rax, rax          ; Clear RAX

next_character:
    mov bl, byte [rdi + rax] ; Load the next character from the main string
    test bl, bl             ; Check if it’s the null
    je end

    mov rcx, rsi            ; Set RCX to the start of the character set

check_set:
    mov dl, byte [rcx]      ; Load the next character from the set
    test dl, dl             ; Check if it’s null
    je increment            ; If null is equal, jump to inc

    cmp bl, dl              ; Compare main string character with set character
    je found                ; If match, jump to found

    inc rcx                 ; Move to the next character in the set
    jmp check_set
increment:
    inc rax                 ; Increment index
    jmp next_character      ; Check the next character in the main string

found:
    ret

end:
    ret                     ; If no match, RAX holds the length of the string
