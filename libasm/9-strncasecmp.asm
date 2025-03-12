BITS 64

section .text
    global asm_strncasecmp

asm_strncasecmp:
    xor rax, rax          ; Clear rax, used to return result
    test rdx, rdx         ; Check if n == 0
    jz .end               ; If n == 0, return 0, strings are equal

.compare_loop:
    mov al, byte [rdi]    ; Load current character from s1 into al
    mov bl, byte [rsi]    ; Load current character from s2 into bl

    cmp al, 'A'
    jb .skip_case_s1       ; Skip if al < 'A'
    cmp al, 'Z'
    ja .skip_case_s1       ; Skip if al > 'Z'
    add al, 32             ; Convert to lowercase by adding 32

.skip_case_s1:
    cmp bl, 'A'
    jb .skip_case_s2       ; Skip if bl < 'A'
    cmp bl, 'Z'
    ja .skip_case_s2       ; Skip if bl > 'Z'
    add bl, 32             ; Convert to lowercase by adding 32

.skip_case_s2:
    sub al, bl             ; al - bl 
    jne .result     ; If characters differ, return result

    test al, al            ; Check if al == 0
    jz .end                ; If null terminator, strings are equal so far

    inc rdi                ; Advance s1 pointer
    inc rsi                ; Advance s2 pointer
    dec rdx                ; Decrement max character count (n)
    jnz .compare_loop      ; Continue loop if n > 0

.end:
    xor rax, rax           ; Strings are equal, return 0
    ret

.result:
    movsx rax, al          ; Sign-extend comparison
    ret
