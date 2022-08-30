#include <utils.h>
#include <boot/limine.h>

void _start(void)
{
    limineInit();        // initialise the bootloader interface wrapper
    limineWrite("miOS"); // write text

    while (1)
        ;
}
