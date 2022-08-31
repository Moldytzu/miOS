#pragma once
#include <utils.h>

pstruct
{
    uint64_t base;
    uint64_t size;
    uint64_t allocableBase;
    uint64_t allocableSize;
    uint64_t bitmapSize;
    uint64_t available;
    uint64_t byteIndex;
    uint64_t bitIndex;
    uint64_t pageIndex;
}
pmm_pool_t;

void *pmmAllocateLow(); // allocate in the lower memory part (< 1M)
void *pmmAllocate();    // allocate in the higher memory part (> 1M)
void pmmDeallocate(void *address);
void pmmInit();