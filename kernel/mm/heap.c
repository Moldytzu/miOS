#include <mm/heap.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <io/serial.h>

#define HEADER(segment) ((heap_segment_t *)((uint64_t)segment - sizeof(heap_segment_t)))

heap_segment_t *heapLastSegment = NULL;
void *end = 0;

void expand(size_t);
void split(heap_segment_t *, size_t);

// initialize the heap
void heapInit()
{
    end = (void *)HEAP_START;
    expand(1); // create first segment

    serialWrites("Initialised the heap!\n");
}

// expand the heap
void expand(size_t size)
{
    size = alignD(size, VMM_PAGE); // align the size to page boundary

    heap_segment_t *next = (heap_segment_t *)end; // set new segment to the last address

    // allocate new heap pages
    for (size_t p = 0; p < (size / VMM_PAGE) + 1; p++)
    {
        vmmMap(vmmGetBaseTable(), end, pmmAllocate(), false, true);
        end += VMM_PAGE;
    }

    // generate required metadata
    next->free = true;
    next->next = NULL;
    next->signature = 0x4321;
    next->size = size;

    if (!heapLastSegment) // if the last segment is invalid then make it the newly generated segment
        heapLastSegment = next;
    else if (heapLastSegment->free == true) // if the last segment is free then extend it's size
        heapLastSegment->size += size;
    else // else link the segments together
        heapLastSegment->next = next;
}

// allocate on the heap
void *malloc(size_t size)
{
    if (size == 0)
        return NULL;

    size = align(size, 16);

    heap_segment_t *currentSegment = (void *)HEAP_START;

    while (currentSegment)
    {
        if (!currentSegment->free || currentSegment->size < size)
        {
            currentSegment = currentSegment->next;
            continue;
        }

        if (currentSegment->size > size)
        {
            split(currentSegment, size);                                                            // split the segment at the required size
            currentSegment->free = false;                                                           // mark the segment as busy
            return (heap_segment_t *)((uint64_t)currentSegment + (uint64_t)sizeof(heap_segment_t)); // return its content address
        }

        if (currentSegment->size == size)
        {
            currentSegment->free = false;                                                           // mark the segment as busy
            return (heap_segment_t *)((uint64_t)currentSegment + (uint64_t)sizeof(heap_segment_t)); // return its content address
        }
    }

    expand(size);        // expand the heap
    return malloc(size); // retry
}

// split a segment
void split(heap_segment_t *segment, size_t size)
{
    heap_segment_t *new = (heap_segment_t *)((uint64_t)segment + sizeof(heap_segment_t) + size);
    new->free = true;
    new->size = segment->size - (size + sizeof(heap_segment_t));
    new->next = segment->next;
    new->signature = 0x4321;

    if (segment->next == NULL) // link the segment if the chain is over
        heapLastSegment = new;

    segment->next = new;  // set new segment
    segment->size = size; // set new size
}

// reallocate
void *realloc(void *ptr, size_t size)
{
    void *buffer = malloc(size);                    // allocate another buffer
    size_t copySize = min(HEADER(ptr)->size, size); // calculate the required bytes to be copied

    // copy the contents
    memcpy(buffer, ptr, copySize);

    free(ptr);     // free the old buffer
    return buffer; // return the newly allocated buffer
}

// free a segment
void free(void *ptr)
{
    if (HEADER(ptr)->signature != 0x4321)
        return;

    HEADER(ptr)->free = true; // mark the segment as free
}