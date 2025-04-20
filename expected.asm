section .text

extern putchar
global _start

printn:
  push rbp                ; Save base pointer
  mov rbp, rsp            ; Set up stack frame
  sub rsp, 8              ; Allocate space for local variable 'a'

  mov rax, rdi            ; Load n (numerator) into RAX
  cqo                     ; Sign-extend RAX into RDX
  idiv rsi                ; Divide RDX:RAX by RSI (b)
  mov qword [rbp-8], rax  ; Store quotient (a = n / b) on the stack

  cmp rax, 0              ; Check if a == 0
  je .cont                ; If a == 0, skip recursion
.if:
  push rdi                ; Save rdi (n)
  push rsi                ; Save rsi (b)
  mov rdi, qword [rbp-8]  ; Load a (quotient) into RDI
  call printn             ; Recursive call
  pop rsi                 ; Restore rsi (b)
  pop rdi                 ; Restore rdi (n)
.cont:
  mov rax, rdx            ; Load remainder (n % b) into RAX
  add rax, '0'            ; Convert remainder to ASCII
  mov rdi, rax            ; Move ASCII character to RDI
  call putchar            ; Print the character

  leave                   ; Clean up stack frame
  ret                     ; Return

_start:
  mov rdi, 500            ; Set n = 500
  mov rsi, 10             ; Set b = 10
  call printn             ; Call printn(500, 10)
  ret