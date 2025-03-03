section .text
global asm_strncmp

    asm_strncmp:
        xor rax, rax                ; set RAX to 0
        .next_character:
            mov al, [rdi]          ;Load byte from first string
            cmp al, [rsi]           ;Compare to second string
            jne .diff               ;IF NOT ==, jump to diff
            test al, al             ;Check if \0
            je .done                ;IF \0 strings are ==
            inc rdi                 ;advance pointers
            inc rsi
            jmp .next_character     ;increment
        .diff:
            sub rax, [rsi]          ;return difference
        .done:
        ret
