BITS 64

section .text
    global asm_puts

extern asm_strlen   ; Import the external strlen function

asm_puts:
    call asm_strlen   ; Call asm_strlen to get the length of the string

    mov rsi, rdi      ; Set rsi = pointer to the string
    mov rdx, rax      ; Set rdx = length of the string (from asm_strlen)
    mov rax, 1        ; Syscall number for write
    mov rdi, 1        ; File descriptor (stdout)
    syscall           ; Perform the syscall

    ret               ; Return the total bytes written, stored in rax
