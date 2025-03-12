BITS 64

global asm_strcasecmp

asm_strcasecmp:

.compare_loop:
    mov al, byte [rdi]        ; Load current character of s1
    mov bl, byte [rsi]        ; Load current character of s2


    cmp al, 0x41               ; Check if al >= 'A'
    jb .skip_case_s1          ; Skip if less than 'A'
    cmp al, 0x7A               ; Check if al <= 'Z'
    ja .skip_case_s1          ; Skip if greater than 'Z'
    add al, 32                ; Convert to lowercase by adding 32

.skip_case_s1:
    cmp bl, 0x41               ; Check if bl >= 'A'
    jb .skip_case_s2          ; Skip if less than 'A'
    cmp bl, 0x7A               ; Check if bl <= 'Z'
    ja .skip_case_s2          ; Skip if greater than 'Z'
    add bl, 32                ; Convert to lowercase by adding 32

.skip_case_s2:
    sub al, bl                ; Compare al and bl (al - bl)
    jne .result               ; If not equal, return the result

    test al, al               ; Is al (or bl) == 0 (null terminator)?
    jz .equal                 ; If null, strings are equal so far

    inc rdi                   ; Increment pointer to s1
    inc rsi                   ; Increment pointer to s2
    jmp .compare_loop         ; Continue the loop

.equal:
    xor rax, rax              ; Return 0 (strings are equal)
    ret

.result:
    movsx rax, al             ; Sign-extend the result of al - bl into rax
    ret
;error in gdb ->__strcasecmp_l_avx () at ../sysdeps/x86_64/multiarch/strcmp-sse42.S:128
;128     in ../sysdeps/x86_64/multiarch/strcmp-sse42.S