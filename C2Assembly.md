# C2Assembly

For certain C programs the translation to assembly is rather straightforward, for example [Fibonacci sequence](https://github.com/msztylko/python-extensions/blob/master/fibonacci/c_fib.c) and its [assembly version](https://github.com/msztylko/python-extensions/blob/master/fibonacci/asm_fib.asm). This is not as easy for other programs such as [palindrome](https://github.com/msztylko/python-extensions/blob/master/palindrome/c_palindrome.c). 
And even if it were, it is still useful to consider how given algorithm is going to be realized in the machine code. This can guide us towards more compact/efficient version.

Let's discuss process of translating C to Assembly with Palindrome example.

### C Palindrome first version

```C
bool ispalindrome(char s[], int linelen) {
    int l = 0;
    int h = linelen - 1;

    while (l < h) {
        while (!isalnum(s[l]) && l<h) 
            l++;
        while (!isalnum(s[h]) && l<h) 
            h--;
        if (tolower(s[l++]) != tolower(s[h--]))
            return false;
    }
    return true;
    
}
```

This code is quite compact, but it's due to the usage of functions from the C library. Our handwritten Assembly will not use these functions, so let's start by replacing them. 

### C Palindrome second version

Function calls replaced by primitive operations.

```C
int ispalindrome(char *s, int linelen) {
    int l = 0;
    int h = linelen - 1;

    while (l < h) {
        while (!(('A' <= s[l] && s[l] <= 'Z') || ('a' <= s[l] && s[l] <= 'z')) && l<h)
            l++;
        while (!(('A' <= s[h] && s[h] <= 'Z') || ('a' <= s[h] && s[h] <= 'z')) && l<h)
            h--;
        // both uppper
        if (('A' <= s[l] && s[l] <= 'Z') && ('A' <= s[h] && s[h] <= 'Z')) {
            if (s[l] != s[h])
                return 0;
        }   
        // first upper, second lower
        if (('A' <= s[l] && s[l] <= 'Z') && ('a' <= s[h] && s[h] <= 'z')) {
            if (s[l] != (s[h] - 32))
                return 0;
        }   
        // first lower, second upper
        if (('a' <= s[l] && s[l] <= 'z') && ('A' <= s[h] && s[h] <= 'Z')) {
            if ((s[l] - 32) != s[h])
                return 0;
        }   
        // both lower
        if (('a' <= s[l] && s[l] <= 'z') && ('a' <= s[h] && s[h] <= 'z')) {
            if (s[l] != s[h])
                return 0;
        }   
        h--;
        l++;
    }   
    return 1;
}
```

This version is more mechanistic, so it will be easier to translate to Assembly. However, it is clear that there is a lot of redundant computations, so let's start by simplifying them.

### C Palindrome third version

In the main loop we perform a lot of comparisons like `'A' <= s[l]` and so on. This is to determine whether current character is lower or upper case. First, let's stop accessing string for each comparison and instead store the result for low and high pointers.

```C
sl = s[l];
sh = s[h];
```

Then I thought about checking the case of `sl` and `sh` and storing it in 4 variables like:

```C
char l_lower;
char l_upper;
char h_lower;
char h_upper;

sl = s[l];
sh = s[h];

if ('a' <= sl && sl <= 'z')
    l_lower = 1;
...
```

However, I realized that the information that I try to encode here requires only 4 bits and there's good reason to use 4 1-byte long variables to encode it. Instead I decided to use single 1-byte variable `scase` and use its 4 low-order bits. So now we have:

```
char scase = 0x00;

if ('a' <= sl && sl <= 'z')
    scase |= (1 << 0);
```

in this representation:

```
0b0000 0000
       ||||__ l_lower
       |||__ l_upper
       ||__ h_lower
       |__ h_upper
```

full code for this version:

```C
#define BOTH_UPPER          0x0A
#define FIRST_UP_SECOND_LOW 0x06
#define FIRST_LOW_SECOND_UP 0x09
#define BOTH_LOWER          0x05
#define L_ALNUM             0x03
#define H_ALNUM             0x0C

char ispalindrome(char *s, char linelen) {
    char l = 0;
    char h = linelen - 1;

    char scase = 0x00;
    char sl, sh; 

    while (l < h) {
        sl = s[l];
        sh = s[h];
        if ('a' <= sl && sl <= 'z')
            scase |= (1 << 0); 
        if ('A' <= sl && sl <= 'Z')
            scase |= (1 << 1); 
        if ('a' <= sh && sh <= 'z')
            scase |= (1 << 2); 
        if ('A' <= sh && sh <= 'Z')
            scase |= (1 << 3); 

        while (!(scase & L_ALNUM)) {
            sl = s[++l];
            if ('a' <= sl && sl <= 'z')
                scase |= (1 << 0); 
            if ('A' <= sl && sl <= 'Z')
                scase |= (1 << 1); 
        }   
        while (!(scase & H_ALNUM)) {
            sh = s[--h];
            if ('a' <= sh && sh <= 'z')
                scase |= (1 << 2); 
            if ('A' <= sh && sh <= 'Z')
                scase |= (1 << 3); 
        }   
    
        if ((scase == BOTH_UPPER) && (sl != sh))
            return 0;

        if ((scase == FIRST_UP_SECOND_LOW) && (sl != sh-32))
            return 0;

        if ((scase == FIRST_LOW_SECOND_UP) && (sl-32 != sh))
            return 0;

        if ((scase ==BOTH_LOWER) && (sl != sh))
            return 0;

        h--;
        l++;
        scase = 0x00;
    }   
    return 1;
}
```

### Assembly Palindrome

From this C version is was much easier to arrive at the final [Assembly version](https://github.com/msztylko/python-extensions/blob/master/palindrome/asm_palindrome.asm) of this program:

```assembly
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
```
