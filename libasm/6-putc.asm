BITS 64

global asm_putc

asm_putc:
    push rdi               ;save data index

    mov rax, 1             ; Syscall number for write (1)
    mov rdi, 1             ; File descriptor for stdout (1)
    lea rsi, [rsp-1]           ; rsi = pointer to buffer on the stack
    mov byte [rsp-1], dil         ; Store the character on the stack
    mov rdx, 1             ; Number of bytes to write

    syscall

    pop rdi                 ;restore data index

    mov rax, 1             ; Set rax to 1
    ret