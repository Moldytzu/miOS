#pragma once
#include <utils.h>

pstruct
{
    uint16_t size;   // size of the table in bytes - 1
    uint64_t offset; // linear address of the gdt (paging applies)
}
gdtr_t;

pstruct
{
    uint16_t limit;
    uint16_t base0;
    uint8_t base1;
    uint8_t access;
    uint8_t flags_limit;
    uint8_t base2;
}
gdt_segment_t;

void gdtInit();