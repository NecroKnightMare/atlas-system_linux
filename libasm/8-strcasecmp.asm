BITS 64

global asm_strcasecmp

asm_strcasecmp:
    test rdi, rdi             ; Check if the first string pointer is NULL
    jz .equal                 ; Treat NULL as equal return 0
    test rsi, rsi             ; Check if the second string pointer is NULL
    jz .equal                 ; Treat NULL as equal return 0

.next_character:
    mov al, byte [rdi]        ; Load the current character from the first string
    mov bl, byte [rsi]        ; Load the current character from the second string

    ; Convert AL to lowercase if it’s an uppercase letter
    
    cmp al, 'A'               ; Is AL >= 'A'?
    jb .check_second          ; If below 'A', skip conversion
    cmp al, 'Z'               ; Is AL <= 'Z'?
    ja .check_second          ; If above 'Z', skip conversion
    add al, 32                ; Convert to lowercase by adding 32

.check_second:
    cmp bl, 'A'               ; Is BL >= 'A'?
    jb .compare               ; If below 'A', skip conversion
    cmp bl, 'Z'               ; Is BL <= 'Z'?
    ja .compare               ; If above 'Z', skip conversion
    add bl, 32                ; Convert to lowercase by adding 32

.compare:
    cmp al, bl                ; Compare the two characters
    jne .not_equal            ; If different, jump to .not_equal

    test al, al               ; Check if reached null
    je .equal                 ; If null, strings are equal

    inc rdi                   ; Move to next character in first string
    inc rsi                   ; Move to next character in second string
    jmp .next_character

.not_equal:
    sub eax, ebx              ; return the difference
    ret

.equal:
    xor eax, eax              ; Return 0
    ret