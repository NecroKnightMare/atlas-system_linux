BITS 64                             ;For RSI and RDI- they hold 64 bits

section .text
    global asm_strncmp

asm_strncmp:
    push rbp                ;base pointer - 8 bit
    mov rbp, rsp            ;move stack* to base* - 8 bit
    ;xor rax, rax
    mov rdi, [rbp + 16]     ;address of s1 - 8 bit
    mov rsi, [rbp + 24]     ;address of s2 - 8 bit
    mov rcx, [rbp + 32]     ;counter of n or size_t - 8 bit

    test rcx, rcx           ;if rcx == rcx
    je .equal               ;jump to condition

.next_character:
    mov al, byte [rdi]      ;Load byte from first string
    mov bl, byte [rsi]      ;Load byte to second string
    
    cmp al, bl
    jne .difference
    test al, al             ;Check if \0
    jz .equal                ;IF \0 strings are ==

    dec rcx                 ;decrement n
    jz .equal               ;when n reaches 0

    inc rdi                 ;advance pointers
    inc rsi
    jmp .next_character     ;increment/loop

.equal:
    xor eax, eax          ; set to 0/return use 32 bit for efficiency

.difference:
    sub al, bl              ;difference of n
    movzx eax, al           ;expand with zeros
    jmp .function_end

.function_end:
    pop rbp
    ret

;add size_t logic
;rcx for 64bit counter
;decrement with rcx using dec rcx before cmp
;