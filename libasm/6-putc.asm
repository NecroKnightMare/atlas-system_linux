BITS 64

section .text
    global asm_putc

asm_putc:

    sub rsp, 8            ; Allocate 8 bytes on the stack
    mov byte [rsp], dil   ; Store the character in the stack buffer

    mov rax, 1            ; Syscall number for write
    mov edi, 1            ; File descriptor 1 = stdout
    mov rsi, rsp          ; Pointer to the stack buffer
    mov rdx, 1            ; Number of bytes to write
    syscall               ; Make the syscall

    add rsp, 8            ; Free 8 bytes of stack space

    test rax, rax         ; Check if syscall failed rax < 0
    js .error             ; Jump to error handling if negative


    movzx eax, dil        ; Zero-extend dil into eax
    ret

.error:
    mov eax, -1           ; Set return value to EOF -1 on error
    ret
