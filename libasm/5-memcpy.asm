BITS 64

global asm_memcpy

asm_memcpy:

    mov rax, rdi        ;move data index to accumulator reg

    test rdx, rdx       ;if rdx == rdx
    jz .exit

.increment:
    mov bl, [rsi]       ;load source index to byte
    mov [rdi], bl       ;send lower base byte to data index
    inc rsi             ;increment
    inc rdi
    dec rdx
    jnz .increment      ;instead of jmp use jnz since its conditional

.exit:
    ret