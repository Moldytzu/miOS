bits 64

%macro PUSH_REG 0
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rbp
    push rdi
    push rsi
    push rdx
    push rcx
    push rbx
    push rax
    mov rax, cr3
    push rax
%endmacro

%macro POP_REG 0
    pop rax
    mov cr3, rax
    pop rax
    pop rbx
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    pop rbp
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
%endmacro

global idtExceptionHandlerEntry, idtLoad, syscallHandlerEntry
extern idtExceptionHandler, syscallHandler

idtExceptionHandlerEntry:
    cli ; disable intrerrupts
    PUSH_REG
    mov rdi, rsp ; give the handler the stack frame
    call idtExceptionHandler
    POP_REG
    add rsp, 8 ; cancel the error code
    iretq

syscallHandlerEntry:
    cli
    PUSH_REG
    mov rdi, rsp ; give the handler the stack frame
    call syscallHandler
    POP_REG
    o64 sysret

idtLoad:
    lidt [rdi]
    ret