extern exit
extern putchar
global _start
_start:
  call main
  mov rax, 60
  xor rdi, rdi
  syscall
  ret
main:
push rbp
mov rbp, rsp
sub rsp, 8 ; alloca Interned { "x" }
mov rbx, 1 ; loading literal
neg rbx ; negate
mov qword [rbp - 8], rbx ; storing Interned { "x" }
mov rdi, 0 ; load arg 0 -> 
call exit
ret

