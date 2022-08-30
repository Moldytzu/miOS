#include <cpu/gdt.h>

extern void gdtLoad(gdtr_t *);

gdtr_t gdtr;                                          // descriptor
gdt_segment_t segments[4096 / sizeof(gdt_segment_t)]; // 1024 segments (todo: switch this with an allocated page)

int lastSegment = 0;
void gdtCreateSegment(uint8_t access)
{
    gdt_segment_t *currentSegment = &segments[lastSegment++]; // get the address of the segment we will write
    zero(currentSegment, gdt_segment_t);                      // clear the segment

    currentSegment->access = access;
    currentSegment->flags_limit = 0b10100000; // 4 kb blocks, long-mode
}

void gdtInit()
{
    memset(&gdtr, 0, sizeof(gdtr_t)); // clear the gdtr

    gdtCreateSegment(0);          // null segment
    gdtCreateSegment(0b10011110); // kernel code
    gdtCreateSegment(0b10010110); // kernel data
    gdtCreateSegment(0);          // null segment
    gdtCreateSegment(0b11111110); // user code
    gdtCreateSegment(0b11110110); // user data
    gdtCreateSegment(0);          // null segment

    gdtr.offset = (uint64_t)segments;                      // set the offset
    gdtr.size = (lastSegment * sizeof(gdt_segment_t)) - 1; // set the size

    gdtLoad(&gdtr); // load the gdt
}