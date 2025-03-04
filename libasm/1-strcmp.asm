section .text
global asm_strcmp

    asm_strcmp:
        xor rax, rax                ; set RAX to 0
        .next_character:
            mov al, byte [rdi]      ;Load byte from first string
            cmp al, byte [rsi]      ;Compare byte to second string
            jne .diff               ;IF NOT ==, jump to diff
            test al, al             ;Check if \0
            je .done                ;IF \0 strings are ==
            inc rdi                 ;advance pointers
            inc rsi
            jmp .next_character     ;increment/loop
        .diff:
            mov bl, byte [rsi]      ;Load value from memory into reg
            sub al, bl              ;return difference of AL-BL
            movsx rax, al           ;sign extend AL to RAX-mimics strcmp behavior
        .done:
            ret
