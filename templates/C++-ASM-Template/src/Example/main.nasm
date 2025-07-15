section .text
global _start
extern HelloWorldASM

_start:
  call HelloWorldASM
  mov rdi, rax ; Move return value into program return code

  ; Exit syscall
  mov rax, 0x3C
  syscall
