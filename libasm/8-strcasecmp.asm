BITS 64

global asm_strcasecmp

asm_strcasecmp:
    test rdi, rdi             ; Check if the first string pointer is NULL
    jz .null                  ; Jump if NULL
    test rsi, rsi             ; Check if the second string pointer is NULL
    jz .null                  ; Jump if NULL

.next_character:
    mov al, byte [rdi]        ; Load the current character from the first string
    mov bl, byte [rsi]        ; Load the current character from the second string

    ; Convert AL to lowercase if it’s an uppercase letter
    cmp al, 'A'               ; Is AL >= 'A'?
    jb .check_second          ; If below, skip conversion
    cmp al, 'Z'               ; Is AL <= 'Z'?
    ja .check_second          ; If above, skip conversion
    add al, 32                ; Convert to lowercase by adding 32

.check_second:
    ; Convert BL to lowercase if it’s an uppercase letter
    cmp bl, 'A'               ; Is BL >= 'A'?
    jb .compare               ; If below, skip conversion
    cmp bl, 'Z'               ; Is BL <= 'Z'?
    ja .compare               ; If above, skip conversion
    add bl, 32                ; Convert to lowercase by adding 32

.compare:
    cmp al, bl                ; Compare the two characters
    jne .not_equal            ; If different, jump to not equal

    test al, al               ; Check if we’ve reached the null terminator
    je .equal                 ; If null terminator, strings are equal

    inc rdi                   ; Move to the next character in the first string
    inc rsi                   ; Move to the next character in the second string
    jmp .next_character

.not_equal:
    sub eax, ebx              ; Calculate and return the difference
    ret

.equal:
    xor eax, eax              ; Return 0
    ret

.null:
    xor eax, eax              ; For NULL pointers, behave as if strings are equal
    ret