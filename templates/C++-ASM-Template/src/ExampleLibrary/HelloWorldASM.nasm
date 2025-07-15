section .text

global HelloWorldASM
HelloWorldASM:
  push rbp
  mov rbp, rsp

  ;; Do sum stuff

  mov rax, 4 ; Return

  mov rsp, rbp
  pop rbp
  ret
