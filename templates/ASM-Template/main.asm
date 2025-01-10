global _start
_start:
  mov rax, 0x3c ; 60 exit
  mov rdi, 0 ; exit code
  syscall
