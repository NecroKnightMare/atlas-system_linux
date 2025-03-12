BITS 64

;got it to output an error instead of just dump
;failing at s1, s2 == s1, s2

global asm_strstr

asm_strstr:
    mov al, byte [rsi]    ; Load the first byte of needle into rax
    test al, al              ; Test if the first byte is null
    jz .return_haystack      ; If null, return haystack pointer
    mov rax, rdi             ; if empty return
    ret

.inner_loop:                 
    mov dl, [rsi + rbx]     ; Load a byte from needle
    test dl, dl              ; Check if it's null terminator
    jz .found_match          ; If null, full match found

    mov bl, byte [rax]    ; Load a byte from haystack
    test bl, bl              ; Check if it's null terminator
    jz .not_found            ; If null, no match

    cmp bl, [rax]               ; Compare needle byte with haystack byte
    jne .next_haystack       ; If not equal, move to next character in haystack

    inc rbx 
    inc rax  
    jmp .inner_loop 

.next_haystack:
    sub rax, rbx 
    inc rax                  ; Move to the next character in haystack
    movzx rax, byte [rdi]    ; Check if end of haystack is reached
    xor rbx, rbx
    jne .inner_loop          ; Continue outer loop if not null terminator

.not_found:
    xor rax, rax             ; Return NULL (0)
    ret

.found_match:
    mov rax, rdi             ; Return pointer to the start of the match
    ret

.return_haystack:
    mov rax, rdi             ; If needle is empty, return haystack pointer
    xor rbx, rbx             ;resets
