BITS 64

section .text
    global asm_strspn

asm_strspn:
    xor rax, rax          ; Clear RAX (to store the count)

.next_character:
    mov dl, byte [rdi]    ; Load current character from s1 into dl
    test dl, dl           ; Check if null
    jz .done              ; If null, end

    mov rcx, rsi          ; Set up pointer to accept in rcx

.check_accept:
    mov bl, byte [rcx]    ; Load current character from accept into bl
    test bl, bl           ; Check if null
    jz .not_in_accept      ; If null, character is not in accept

    cmp dl, bl            ; Compare s1's character (dl) with accept's (bl)
    je .in_accept         ; If match, character is in accept

    inc rcx               ; Move to next character in accept
    jmp .check_accept     ; Repeat the check for the next character

.in_accept:
    inc rax               ; Increment count (rax) for matching character
    inc rdi               ; Move to the next character in s1
    jmp .next_character     ; Repeat for the next character in s1

.not_in_accept:
    jmp .done

.done:
    ret                   ; Return the count in rax
