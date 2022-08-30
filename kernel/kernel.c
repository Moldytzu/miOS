#include <utils.h>
#include <boot/limine.h>
#include <simd/simd.h>

void _start(void)
{
    simdInit(); // initialise the simd instruction sets

    limineInit();        // initialise the bootloader interface wrapper
    limineWrite("miOS"); // write text

    while (1)
        ;
}
