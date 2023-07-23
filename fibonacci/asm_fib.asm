section .text
global fib

fib:
    ; if (n < 2) return n
    mov eax, edi
    cmp eax, 2
    jl .end

    ; fib(n-1)
    sub edi, 1
    push rdi
    call fib
    pop rdi

    ; fib(n-2)
    sub edi, 1
    push rax
    call fib
    pop rdx
    
    add eax, edx ; fib(n-1) + fib(n-2)

.end:
    ret
