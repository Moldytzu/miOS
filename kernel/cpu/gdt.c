#include <cpu/gdt.h>
#include <io/serial.h>
#include <mm/pmm.h>

extern void gdtLoad(gdtr_t *);

gdtr_t gdtr;             // descriptor
gdt_segment_t *segments; // pointer to the segments
tss_t *tss;              // pointer to the tss

int gdtlastSegment = 0;
void gdtCreateSegment(uint8_t access)
{
    gdt_segment_t *currentSegment = &segments[gdtlastSegment++]; // get the address of the segment we will write
    zero(currentSegment, gdt_segment_t);                         // clear the segment

    currentSegment->access = access;
    currentSegment->flags_limit = 0b10100000; // 4 kb blocks, long-mode
}

void gdtInstallTSS()
{
    uint64_t base = (uint64_t)tss;

    gdt_system_segment_t *currentSegment = (gdt_system_segment_t *)&segments[gdtlastSegment++]; // get the address of the segment we will write
    currentSegment->access = 0b10001001;                                                        // present, dpl 0, system segment and 64 bit tss
    currentSegment->limit = sizeof(tss_t);                                                      // set limit to the size of the tss

    // set the base bytes accordingly
    currentSegment->base = base & 0xFFFF;
    base >>= 16;
    currentSegment->base2 = base & 0xFF;
    base >>= 8;
    currentSegment->base3 = base & 0xFF;
    base >>= 8;
    currentSegment->base4 = base & 0xFFFFFFFF;
}

void gdtInit()
{
    segments = pmmAllocate(); // allocate the segments
    tss = pmmAllocate();      // allocate the tss

    // clear the variables' contents
    memset(tss, 0, 4096);
    memset(segments, 0, 4096);
    memset(&gdtr, 0, sizeof(gdtr_t));

    gdtCreateSegment(0);          // null segment
    gdtCreateSegment(0b10011110); // kernel code
    gdtCreateSegment(0b10010110); // kernel data
    gdtCreateSegment(0b11110110); // user data
    gdtCreateSegment(0b11111110); // user code

    gdtInstallTSS(); // install the tss

    gdtr.offset = (uint64_t)segments;                               // set the offset
    gdtr.size = ((gdtlastSegment + 1) * sizeof(gdt_segment_t)) - 1; // set the size (we increment the last segment count because the system segments are double in size than regular segments)

    gdtLoad(&gdtr); // load the gdt

    serialWrites("Loaded the GDT!\n");
}

gdt_segment_t *gdtGetSegments()
{
    return segments;
}