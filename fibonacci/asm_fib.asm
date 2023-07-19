section .text
global fib

fib:
    mov eax, edi
    cmp eax, 1
    jle .end

    sub edi, 1
    push rdi
    call fib
    pop rdi

    sub edi, 1
    push rax
    call fib
    pop rdx

    add eax, edx

.end:
    ret
