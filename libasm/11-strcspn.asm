BITS 64

global asm_strcspn

asm_strcspn:
    xor rax, rax          ; Clear RAX (index counter)

next_character:
    mov bl, byte [rdi + rax] ; Load the next character from the main string
    test bl, bl             ; Check if it’s the null
    je end                  ; If null, end

    mov rcx, rsi            ; Set RCX to the start of the character set

check_set:
    mov dl, byte [rcx]      ; Load the next character from the set
    test dl, dl             ; Check if it’s the null
    je increment            ; If null  equal to, jump to inc

    cmp bl, dl              ; Compare main string character with set character
    je found                ; If match, jump to found

    inc rcx                 ; Move to the next character in the set
    jmp check_set
increment:
    inc rax                 ; Increment index
    jmp next_character      ; Check the next character in the main string

found:
    ret                     ; RAX already holds the index of the match

end:
    ret                     ; If no match, RAX holds the length of the string
