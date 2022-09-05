#include <cpu/idt.h>
#include <mm/pmm.h>
#include <io/serial.h>

idtr_t idtr;
idt_gate_descriptor_t *descriptors;

extern void idtLoad(idtr_t *); 

void idtSetGate(uint8_t vector, void *ptr)
{
    uint64_t base = (uint64_t)ptr;
    descriptors[vector].offset = base & 0xFFFF;
    base >>= 16;
    descriptors[vector].offset2 = base & 0xFFFF;
    base >>= 16;
    descriptors[vector].offset3 = base & 0xFFFFFFFF;
    descriptors[vector].segmentselector = (8 * 1); // kernel code
    descriptors[vector].attributes = 0b11101110;   // present, dpl 3, 64-bit intrerrupt gate
}

extern void idtExceptionHandlerEntry();

void idtExceptionHandler(idt_intrerrupt_stack_t *rsp)
{
    serialWrites("Generic exception handled");
}

void idtInit()
{
    descriptors = pmmAllocate();
    zero(descriptors, idt_gate_descriptor_t);

    for(int i = 0; i <= 32; i++)
        idtSetGate(i, idtExceptionHandlerEntry);

    idtr.offset = (uint64_t)descriptors;
    idtr.size = sizeof(idt_gate_descriptor_t) * 256 - 1; // 256 descriptors

    idtLoad(&idtr);
}