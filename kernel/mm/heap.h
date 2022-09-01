#pragma once
#include <utils.h>

#define HEAP_START 0xF000000000

pstruct heap_segment_t heap_segment_t;

struct heap_segment_t
{
    uint16_t signature;
    bool free;
    size_t size;
    heap_segment_t *next;
};

void heapInit();
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);