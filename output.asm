extern putchar
sub rsp, 8 ; alloca
mov rbx, [rbp - 8] ; loading Interned { "a" }
mov r10, rdi ; loading Interned { "n" }
mov r11, rsi ; loading Interned { "b" }
mov rax, r10
cqo
div r11
 rbx, rax
icmp rbx, 0 ; if (cond)
je .cont0 ; if (!cond)
.if0:
.cont0:

