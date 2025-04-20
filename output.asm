extern putchar
printn:
sub rsp, 8 ; alloca
mov rax, rdi
cqo
div rsi
 [rbp - 0], rax
icmp [rbp - 0], 0 ; if (cond)
je .cont0 ; if (!cond)
.if0:
.cont0:

