#include <utils.h>
#include <boot/limine.h>
#include <simd/simd.h>
#include <io/serial.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <sys/syscall.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <mm/heap.h>
#include <acpi/acpi.h>

void cpuRun()
{
    // USERSPACE \/
    void *kernelIntStack = pmmAllocate();
    void *userStack = pmmAllocate();
    void *userspace = pmmAllocate();

    // set the stacks in the tss
    tss_t *tss = gdtGetTSS();

    tss->rsp[0] = (uint64_t)kernelIntStack + 4096;
    tss->rsp[2] = (uint64_t)userStack + 4096;

    // copy the idle task's contents in physical memory
    memcpy(userspace, idleTask, 4096);

    // map the task's contents as rw userspace
    vmmMap(vmmGetBaseTable(), userspace, userspace, true, true);

    // map the user stack as rw userspace
    vmmMap(vmmGetBaseTable(), userStack, userStack, true, true);

    // jump in userspace
    userspaceJump(userspace, userStack + 4096);
}

// used to set the same enviroment to all the cpus
void cpuBootstrap()
{
    // todo: load the gdt

    idtLoad(idtGetIDT());       // load the idt
    vmmSwap(vmmGetBaseTable()); // swap the page table
    sysretInit();               // enable syscalls

    cpuRun(); // run the program
}

// kernel entry point
void _start(void)
{
    simdInit(); // initialise the simd instruction sets

    limineInit();        // initialise the bootloader interface wrapper
    limineWrite("miOS"); // write text

    serialInit(); // initialise the serial port interface
    pmmInit();    // initialises the physical memory manager
    gdtInit();    // loads a new gdt
    idtInit();    // load an idt
    vmmInit();    // create and load a page table
    heapInit();   // initialise the heap
    acpiInit();   // initialise the acpi interface

    serialWrites("RAM usage: ");
    serialWrites(to_string((pmmGetTotal() - pmmGetAvailable()) / 1024 / 1024));
    serialWrites("/");
    serialWrites(to_string(pmmGetTotal() / 1024 / 1024));
    serialWrites(" MB\n");

    // go run the cpu (todo: bootstrap all the cpus)
    cpuBootstrap();

    while (1)
        ;
}
