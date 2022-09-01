#include <utils.h>
#include <boot/limine.h>
#include <simd/simd.h>
#include <io/serial.h>
#include <cpu/gdt.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <mm/heap.h>

void _start(void)
{
    simdInit(); // initialise the simd instruction sets

    limineInit();        // initialise the bootloader interface wrapper
    limineWrite("miOS"); // write text

    serialInit(); // initialise the serial port interface

    pmmInit(); // initialises the physical memory manager

    gdtInit(); // loads a new gdt

    vmmInit(); // create and load a page table

    heapInit(); // initialise the heap

    serialWrites("RAM usage: ");
    serialWrites(to_string((pmmGetTotal() - pmmGetAvailable()) / 1024 / 1024));
    serialWrites("/");
    serialWrites(to_string(pmmGetTotal() / 1024 / 1024));
    serialWrites(" MB\n");

    while (1)
        ;
}
