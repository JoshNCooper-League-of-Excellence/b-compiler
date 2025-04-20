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
cmp 0, 0 ; if (cond)
je .cont0 ; if (!cond)
.if0:
mov rbx, [rbp - 8] ; loading Interned { "a" }
push rdi
mov rdi, rbx ; load arg 0 -> 
mov rbx, rsi ; loading Interned { "b" }
push rsi
mov rsi, rbx ; load arg 1 -> 
call printn
pop rdi ; restore
pop rsi ; restore
.cont0:
mov rbx, 0 ; loading literal
mov r10, rsi ; loading Interned { "b" }
mov r11, rdi ; loading Interned { "n" }
mov rax, r11
cqo
 r10
add rdx, rbx
push rdi
mov rdi, rdx ; load arg 0 -> 
call putchar
pop rdi ; restore
ret

