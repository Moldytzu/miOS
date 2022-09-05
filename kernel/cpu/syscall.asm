bits 64

global sysretInit, userspaceJump
extern syscallHandlerEntry

sysretInit:
	mov rax, syscallHandlerEntry ; syscall handler entry
	mov	rdx, rax
	shr	rdx, 0x20
	mov rcx, 0xC0000082 ; LSTAR
	wrmsr
	mov	rcx, 0xC0000080 ; IA32_EFER
	rdmsr
	or eax, 1 ; set SCE (syscall extensions)
	wrmsr
	mov	rcx, 0xC0000081 ; STAR
	rdmsr
	mov	rdx, 0x00130008 ; kernel's base is 0x08, user's base is 0x13
	wrmsr
	mov	rcx, 0xC0000084 ; FMASK
	rdmsr
	mov	rax, (0xFFFFFFFFFFFFFFFF & ~0b10) ; mask every flag
	wrmsr
	ret

userspaceJump:
    mov rcx, rdi ; set the new rip
    mov rsp, rsi ; set the new stack
    mov r11, 0x202 ; rflags, enable intrerrupts
    o64 sysret ; to userspace and beyond