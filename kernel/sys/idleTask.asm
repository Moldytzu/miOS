bits 64

global idleTask

idleTask:
    mov rax, 10
    syscall
    jmp $