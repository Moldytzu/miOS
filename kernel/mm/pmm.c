#include <mm/pmm.h>
#include <boot/limine.h>
#include <io/serial.h>

struct limine_memmap_response *memmap;

void pmmInit()
{
    memmap = limineGetMemmap(); // get the memory map
    for(size_t i = 0; i < memmap->entry_count; i++)
        serialWrite('A');
}