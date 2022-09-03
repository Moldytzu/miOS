bits 64

global gdtLoad

gdtLoad:
    lgdt [rdi] ; load gdt from the first argument
    mov ax, (8*2) ; 2nd segment, kernel data
    mov ds, ax ; set all the data segments
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ax, (8*5) ; 5th segment, tss
    ltr ax
    pop rdi
    mov rax, (8*1) ; 1st segment, kernel code
    push rax
    push rdi
    retfq ; flush the code segment