#include <sys/syscall.h>
#include <io/serial.h>
#include <cpu/idt.h>

void syscallHandler(idt_intrerrupt_stack_t *rsp)
{
    serialWrites("syscall no. ");
    serialWrites(to_string(rsp->rax));
    serialWrites("\n");
}