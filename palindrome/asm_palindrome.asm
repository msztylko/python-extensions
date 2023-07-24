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
    xor ecx, ecx          ; char l = 0;
    sub rsi, 1            ; int h = linelen - 1;
    xor edx, edx          ; char scase = 0x00;
                    
.top_loop:                ; while (l < h) 
    cmp ecx, esi
    jge .end

    movzx r8, byte [rdi + rcx]   ; sl = s[l];
    movzx r9, byte [rdi + rsi]   ; sh = s[h];
.sl_lower:
    ; if ('a' <= sl && sl <= 'z')
    cmp r8, 'a'
    jl .sl_upper
    cmp r8, 'z'
    jg .sl_upper
    ; scase |= (1 << 0);
    or edx, 1
.sl_upper:
    ; if ('A' <= sl && sl <= 'Z')
    cmp r8, 'A'
    jl .sh_lower
    cmp r8, 'Z'
    jg .sh_lower
    ; scase |= (1 << 1);
    or edx, 2
.sh_lower:
    ; if ('a' <= sh && sh <= 'z')
    cmp r9, 'a'
    jl .sh_upper
    cmp r9, 'z'
    jg .sh_upper
    ; scase |= (1 << 2);
    or edx, 4
.sh_upper:
    ; if ('A' <= sh && sh <= 'Z')
    cmp r9, 'A'
    jl .l_loop
    cmp r9, 'Z'
    jg .l_loop
    ; scase |= (1 << 3);
    or edx, 8
    
.l_loop:
    ; while (!(scase & L_ALNUM))
    mov eax, edx
    and rax, L_ALNUM
    cmp eax, 0
    jne .h_loop
    ; sl = s[++l]
    add ecx, 1
    movzx r8, byte [rdi + rcx]
    .l_loop_sl_lower:
        ;if ('a' <= sl && sl <= 'z') scase |= (1 << 0)
        cmp r8, 'a'
        jl .l_loop_sl_upper
        cmp r8, 'z'
        jg .l_loop_sl_upper
        or edx, 1
    .l_loop_sl_upper:
        ; if ('A' <= sl && sl <= 'Z') scase |= (1 << 1)
        cmp r8, 'A'
        jl .l_loop
        cmp r8, 'Z'
        jg .l_loop
        or edx, 2
    jmp .l_loop

.h_loop:
    ; while (!(scase & H_ALNUM))
    mov eax, edx
    and rax, H_ALNUM
    cmp eax, 0
    jne .both_upper
    ; sh = s[--h];
    sub rsi, 1
    movzx r9, byte [rdi + rsi]
    .h_loop_sh_lower:
        ; if ('a' <= sh && sh <= 'z') scase |= (1 << 2);
        cmp r9, 'a'
        jl .h_loop_sh_upper
        cmp r9, 'z'
        jg .h_loop_sh_upper
        or edx, 4
    .h_loop_sh_upper:
        ; if ('A' <= sh && sh <= 'Z') scase |= (1 << 3);
        cmp r9, 'A'
        jl .h_loop
        cmp r9, 'Z'
        jg .h_loop
        or edx, 8;
    jmp .h_loop

.both_upper:
    ; ((scase == BOTH_UPPER) && (sl != sh))
    mov eax, edx
    cmp rax, BOTH_UPPER
    jne .first_up_second_low
    cmp r8, r9
    je .end_top_loop
    jne .end_not_palindrome
    
.first_up_second_low:
    ; ((scase == FIRST_UP_SECOND_LOW) && (sl != sh-32))
    mov eax, edx
    cmp rax, FIRST_UP_SECOND_LOW
    jne .first_low_second_up
    mov r11, r9
    sub r11, 32
    cmp r8, r11
    je .end_top_loop
    jne .end_not_palindrome

.first_low_second_up:
    ; ((scase == FIRST_LOW_SECOND_UP) && (sl-32 != sh))
    mov eax, edx
    cmp rax, FIRST_LOW_SECOND_UP
    jne .both_lower
    mov r11, r8
    sub r11, 32
    cmp r11, r9
    je .end_top_loop
    jne .end_not_palindrome

.both_lower:
    ; ((scase == BOTH_LOWER) && (sl != sh))
    mov eax, edx
    cmp rax, BOTH_LOWER
    jne .end_top_loop
    cmp r8, r9
    je .end_top_loop
    jne .end_not_palindrome

.end_top_loop:
    sub rsi, 1      ; h--;
    add rcx, 1      ; l++;
    xor rdx, rdx    ; scase = 0x00;
    jmp .top_loop

.end_not_palindrome:
    xor eax, eax
    ret

.end:
    mov eax, 1
    ret 
