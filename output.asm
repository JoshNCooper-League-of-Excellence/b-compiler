extern putchar
printn:
push rbp
mov rbp, rsp
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
mov r10, [rbp - 8] ; loading Interned { "a" }
push rdi
mov rdi, r10 ; load arg 0 -> 
mov r10, rsi ; loading Interned { "b" }
push rsi
mov rsi, r10 ; load arg 1 -> 
call printn
pop rdi ; restore
pop rsi ; restore
.cont0:
mov r10, rdi ; loading Interned { "n" }
mov r11, rsi ; loading Interned { "b" }
mov rax, r10
cqo
 r11
mov r10, 0 ; loading literal
add rdx, r10
push rdi
mov rdi, rdx ; load arg 0 -> 
call putchar
pop rdi ; restore
ret

