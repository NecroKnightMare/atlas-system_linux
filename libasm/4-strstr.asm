BITS 64

global asm_strstr

asm_strstr:
    test rsi, rsi            ; Check if needle is NULL
    jz return_haystack       ; If needle is NULL, return haystack

    test rdi, rdi            ; Check if haystack is NULL
    jz return_null           ; If haystack is NULL, return NULL

next_character:
    mov r8, rdi              ; Save the current haystack pointer
    mov r9, rsi              ; Save the needle pointer

compare_loop:
    mov al, byte [r8]        ; Load the current character of haystack
    mov bl, byte [r9]        ; Load the current character of needle
    test al, al              ; Check if haystack is at null
    je return_null           ; If null, no match found

    cmp bl, 0                ; Check if needle is at null
    je match_found           ; If null terminator, match is found

    cmp al, bl               ; Compare the characters
    jne next_haystack        ; If they don't match, try the next position in haystack

    inc r8                   ; increment haystack pointer
    inc r9                   ; increment needle pointer
    jmp compare_loop

next_haystack:
    inc rdi                  ; Move to the next character in haystack
    cmp byte [rdi], 0        ; Check if the end of haystack is reached
    je return_null           ; If end of haystack, return NULL
    jmp next_character

return_null:
    xor rax, rax             ; Set RAX to NULL (0)
    ret

match_found:
    mov rax, rdi             ; Return the current haystack pointer
    ret

return_haystack:
    mov rax, rdi             ; Return the haystack pointer
    ret
