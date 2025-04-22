extern exit
global _start
func:
push rbp
mov rbp, rsp
sub rsp, 8 ; alloca Interned { "x" }
mov rbx, rsi ; loading Interned { "b" }
mov r10, rdi ; loading Interned { "a" }
add r10, rbx
mov qword [rbp - 8], r10 ; storing Interned { "x" }
ret
main:
push rbp
mov rbp, rsp
mov rdi, 3 ; load arg 0 -> 
mov rsi, 602 ; load arg 1 -> 
call func
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

