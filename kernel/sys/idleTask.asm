bits 64

global idleTask

idleTask:
    mov rax, 10
    syscall
    mov rax, 420
    syscall
    jmp $