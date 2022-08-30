bits 64

global simdInit

simdInit:
    fninit ; initialise the x87 fpu without checking for unhandled exceptions
    
    ; enable sse
    mov rax, cr0 
    and rax, ~(1 << 2) ; disable coprocessor emulation (CR0.EM)
    or rax, (1 << 1) ; enable coprocessor monitoring (CR0.MP)
    mov cr0, rax

    mov rax, cr4
    or rax, (1 << 9) ; enable fxsave/fxstor (CR4.OSFXSR)
    or rax, (1 << 10) ; enable operating system support for unmasked simd exceptions (CR4.OSXMMEXCPT)
    mov cr4, rax

    ret ; return