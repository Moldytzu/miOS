#include <utils.h>
#include <boot/limine.h>
#include <simd/simd.h>
#include <io/serial.h>
#include <cpu/gdt.h>
#include <mm/pmm.h>

void _start(void)
{
    simdInit(); // initialise the simd instruction sets

    limineInit();        // initialise the bootloader interface wrapper
    limineWrite("miOS"); // write text

    serialInit(); // initialise the serial port interface

    gdtInit(); // loads a new gdt

    pmmInit(); // initialises the physical memory manager

    while (1)
        ;
}
