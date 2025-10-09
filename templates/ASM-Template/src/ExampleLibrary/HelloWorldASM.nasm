section .text

%include "ExampleLibrary/TestInclude.hsm"

global HelloWorldASM
HelloWorldASM:
  push rbp
  mov rbp, rsp

  ;; Do sum stuff

  mov rax, 1 ; Return

  mov rsp, rbp
  pop rbp
  ret
