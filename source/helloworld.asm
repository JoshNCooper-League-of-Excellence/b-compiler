extern putchar
extern exit
global _start
hello_world:
push rbp
mov rbp, rsp
mov rdi, 72 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 101 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 108 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 108 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 111 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 44 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 32 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 87 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 111 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 114 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 108 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 100 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 33 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
mov rdi, 10 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call putchar
add rsp, 8 ; restoring stack
ret
main:
push rbp
mov rbp, rsp
call hello_world
mov rdi, 0 ; load arg 0 -> 
sub rsp, 8 ; aligning stack
call exit
add rsp, 8 ; restoring stack
ret

_start:
  call main
  mov rax, 60
  xor rdi, rdi
  syscall
ret

