section .text
global my_strlen

my_strlen:
    xor rax, rax    			;set RAX to 0 - RAX stores the string length
.next_character:
    cmp byte [rdi + rax], 0		;compare current byte to 0 - RDI points to input string
    je .done					;IF 0 jump to done
    inc rax						;incrment RAX
    jmp .next_character			;loop
.done:
    ret							;return length in RAX