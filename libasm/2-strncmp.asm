BITS 64                             ;For RSI and RDI- they hold 64 bits

section .text
    global asm_strncmp


asm_strncmp:
    xor rcx, rcx            ;counter register

.next_character:
    cmp rcx, rdx           ;if rcx == rcx
    jge .equal               ;jump to condition

    mov al, byte [rdi + rcx]      ;Load byte from first string
    mov bl, byte [rsi + rcx]      ;Load byte to second string

    cmp al, bl
    jne .difference


    test al, al              ;Check if \0
    jz .equal                ;IF \0 strings are ==

    inc rcx                 ;increment n
    jmp .next_character     ;increment/loop

.equal:
    xor eax, eax            ; set to 0/return use 32 bit for efficiency
    ret

.difference:
    movzx eax, al           ;zero extend
    movzx ebx, bl           ;zero extend
    sub eax, ebx            ;difference
    ret

;All good!