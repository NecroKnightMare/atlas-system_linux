BITS 64                             ;For RSI and RDI- they hold 64 bits

section .text
global asm_strcmp

    asm_strcmp:
         xor rax, rax                ; set RAX to 0
        .next_character:

            mov rax [rdi]
            movzx r x [rsi]
            ;mov al, [rdi]      ;Load byte from first string
            ;mov bl, [rsi]       ;Load byte from second string
            cmp al, bl      ;Compare byte to second string
            jne .diff               ;IF NOT ==, jump to diff
            test al, al             ;Check if \0
            je .done                ;IF \0 strings are ==
            inc rdi                 ;advance pointers
            inc rsi
            jmp .next_character     ;increment/loop
        .diff:
            mov bl, byte [rsi]      ;Load value from memory into reg
            ;sub al, bl              ;return difference of AL-BL
            movzx rax, al           ;sign extend AL to RAX-mimics strcmp behavior
        .done:
            ret
