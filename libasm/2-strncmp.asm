BITS 64                             ;For RSI and RDI- they hold 64 bits

section .text
global asm_strncmp

    asm_strncmp:
         xor rax, rax                ; set RAX to 0
        .next_character:
            mov al, [esp + 4]       ;Load byte from first string
            mov bl, [esl + 8]
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
            ;movsx rax, al           ;sign extend AL to RAX-mimics strcmp behavior
        .done:
            ret
