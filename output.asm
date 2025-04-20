extern putchar
printn:
push rbp
mov rbp, rsp
sub rsp, 8 ; alloca Interned { "a" }
mov rbx, rsi ; loading Interned { "b" }
mov r10, rdi ; loading Interned { "n" }
mov rax, r10
cqo
div rbx
mov [rbp - 8], rax ; storing Interned { "a" }
icmp 0, 0 ; if (cond)
je .cont0 ; if (!cond)
.if0:
.cont0:
ret

