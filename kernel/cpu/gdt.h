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

pstruct
{
    uint16_t limit;
    uint16_t base;
    uint8_t base2;
    uint8_t access;
    uint8_t limit2;
    uint8_t base3;
    uint32_t base4;
    uint32_t ignore;
}
gdt_system_segment_t;

pstruct
{
    uint32_t ignore;
    uint64_t rsp[3]; // stack pointers
    uint64_t ignore2;
    uint64_t ist[7]; // intrerrupt stack table
    uint64_t ignore3;
    uint16_t ignore4;
    uint16_t iopb; // io port bitmap
}
tss_t;

void gdtInit();
gdt_segment_t *gdtGetSegments();
tss_t *gdtGetTSS();