BITS 64                             ;For RSI and RDI- they hold 64 bits

section .text
    global asm_strcmp

asm_strcmp:
    xor rax, rax

.next_character:
    mov al, byte [rdi]      ;Load byte from first string
    mov bl, byte [rsi]      ;Load byte to second string
    cmp al, 0
    jne .done  ;IF NOT ==, jump to diff
    cmp bl, 0
    jne .done
    cmp al, bl
    jne .done
    test al, al             ;Check if \0
    jz .equal                ;IF \0 strings are ==
    inc rdi                 ;advance pointers
    inc rsi
    jmp .next_character     ;increment/loop

.done:
    cmp al, bl
    jz .equal             ; If strings are equal, jump to equal
    jg .greater           ; If first string is greater, jump to greater
    jl .lesser            ; If first string is lesser, jump to lesser

.equal:
    xor rax, rax          ; Return 0
    ret
    jmp .function_end

.greater:
    mov rax, 1            ; Return pos value when >
    jmp .function_end

.lesser:
    ;mov rax, -1           ; Return neg value like strcmp when <
    ;movsx rax, al
    sub al, bl              ;this logic is not working
    jmp .function_end

.function_end:
    ret
