BITS 64

global asm_putc

asm_putc:

    mov rax, 1             ; Syscall number for write (1)
    mov rdi, 1             ; File descriptor for stdout (1)
    lea rsi, [rsp-8]           ; rsi = pointer to buffer on the stack
    mov byte [rsp-8], dil         ; Store the character on the stack
    mov rdx, 1             ; Number of bytes to write

    syscall


    mov rax, 1             ; Set rax to 1
    ret