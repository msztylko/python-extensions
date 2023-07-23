%define BOTH_UPPER          0x0A
%define FIRST_UP_SECOND_LOW 0x06
%define FIRST_LOW_SECOND_UP 0x09
%define BOTH_LOWER          0x05
%define L_ALNUM             0x03
%define H_ALNUM             0x0C

section .text
global ispalindrome

ispalindrome:
    ; rdi: s
    ; rsi: linelen -> h
    ; rcx: l
    ; rdx: scase
    ; r8:  sl
    ; r9:  sh
    xor rcx, rcx          ; char l = 0;
    sub rsi, 1            ; int h = linelen - 1;
    xor rdx, rdx          ; char scase = 0x00;
                    
.top_loop:                ; while (l < h) 
    cmp rcx, rsi
    jl .end

    mov r8, [rdi + rcx]   ; sl = s[l];
    mov r9, [rdi + rsi]   ; sh = s[h];
.sl_lower:
    ; if ('a' <= sl && sl <= 'z')
    cmp r8, 'a'
    jl .sl_upper
    cmp r8, 'z'
    jg .sl_upper
    ; scase |= (1 << 0);
    or rdx, 1
.sl_upper:
    ; if ('A' <= sl && sl <= 'Z')
    cmp r8, 'A'
    jl .sh_lower
    cmp r8, 'Z'
    jg .sh_lower
    ; scase |= (1 << 1);
    or rdx, 2
.sh_lower:
    ; if ('a' <= sh && sh <= 'z')
    cmp r8, 'a'
    jl .sh_upper
    cmp r8, 'z'
    jg .sh_upper
    ; scase |= (1 << 2);
    or rdx, 4
.sh_upper:
    ; if ('A' <= sh && sh <= 'Z')
    cmp r8, 'A'
    jl .l_loop
    cmp r8, 'Z'
    jg .l_loop
    ; scase |= (1 << 3);
    or rdx, 8
    
.l_loop:
    ; while (!(scase & L_ALNUM))
    mov rax, rdx
    and rax, L_ALNUM
    cmp eax, 0
    jne .h_loop
    ; sl = s[++l]
    add rcx, 1
    mov r8, [rdi + rcx]
    .l_loop_sl_lower:
        ;if ('a' <= sl && sl <= 'z') scase |= (1 << 0)
        cmp r8, 'a'
        jl .l_loop_sl_upper
        cmp r8, 'z'
        jg .l_loop_sl_upper
        or rdx, 1
    .l_loop_sl_upper:
        ; if ('A' <= sl && sl <= 'Z') scase |= (1 << 1)
        cmp r8, 'A'
        jl .l_loop
        cmp r8, 'Z'
        jg .l_loop
        or rdx, 2
    jmp .l_loop

.h_loop
    ; while (!(scase & H_ALNUM))
    mov rax, rdx
    and rax, H_ALNUM
    cmp eax, 0
    jne .both_upper
    ; sh = s[--h];
    sub rsi, 1
    mov r9, [rdi + rsi]
    .h_loop_sh_lower:
        ; if ('a' <= sh && sh <= 'z') scase |= (1 << 2);
        cmp r9, 'a'
        jl .h_loop_sh_upper
        cmp r9, 'z'
        jg .h_loop_sh_upper
        or rdx, 4
    .h_loop_sh_upper:
        ; if ('A' <= sh && sh <= 'Z') scase |= (1 << 3);
        cmp r9, 'A'
        jl .h_upper
        cmp r9, 'Z'
        jg .h_upper
        or rdx, 8;
    jmp .h_loop

.both_upper:
    mov rax, rdx
    cmp rax, BOTH_UPPER
    jne .first_up_second_low
    cmp r8, r9
    je .first_up_second_low
    jne .end_not_palindrome
    
.first_up_second_low:
    mov rax, rdx
    cmp rax, FIRST_UP_SECOND_LOW
    jne .first_low_second_up
    mov rcx, r9
    sub rcx, 32
    cmp r8, rcx
    je .first_low_second_up
    jne .end_not_palindrome

.first_low_second_up:
    mov rax, rdx
    cmp rax, FIRST_LOW_SECOND_UP
    jne .both_lower
    mov rcx, r8
    sub rcx, 32
    cmp rcx, r9
    je .both_lower
    jne .end_not_palindrome

.both_lower:
    mov rax, rdx
    cmp rax, BOTH_LOWER
    jne .end_top_loop
    cmp r8, r9
    je .end_top_loop
    jne .end_not_palindrome

.end_top_loop:
    sub rsi, 1
    add rcx, 1
    xor rdx, rdx

.end_not_palindrome
    xor rax, rax
    ret

.end
    mov rax, 1
    ret 
