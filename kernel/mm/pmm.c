#include <mm/pmm.h>
#include <boot/limine.h>
#include <io/serial.h>

struct limine_memmap_response *memmap;

const char *entriesTypes[] = {"usable", "reserved", "acpi-reclaimable", "acpi-nvs", "bad-memory", "bootloader-reclaimable", "kernel-and-modules", "framebuffer"};

pmm_pool_t pools[1024]; // stores metadata about the usable pools
int poolsIndex = 0;

void *pmmAllocateLow()
{
    pmm_pool_t *pool = &pools[0];

    if (pools->available < 4096)
        return NULL;

    for (; pool->byteIndex != pool->bitmapSize; pool->byteIndex++) // iterate over all the bytes of the bitmap
    {
        uint8_t bitmapByte = *((uint8_t *)pool->base + pool->byteIndex); // get the byte at the offset indicated by i
        for (; pool->bitIndex < 8; pool->bitIndex++, pool->pageIndex++)  // iterate over all the bits of the byte
        {
            uint8_t mask = 0b10000000 >> pool->bitIndex;
            if (mask & bitmapByte) // page at that index is not free
                continue;

            pool->available -= 4096;
            *((uint8_t *)pool->base + pool->byteIndex) |= mask; // apply the mask
            return (void *)(pool->allocableBase + pool->pageIndex * 4096);
        }

        if (pool->bitIndex == 8)
            pool->bitIndex = 0; // reset the bit index
    }

    if (pool->byteIndex < pool->bitmapSize - 1)
    {
        pool->byteIndex = 0;
        return pmmAllocate();
    }

    return NULL;
}

void *pmmAllocate()
{
    int i = 0;
    pmm_pool_t *pool = NULL;

    for (i = 1; pools[i].available < 4096; i++)
        ; // ignore first pool since it will be used for jumping from real mode to long mode (smp)

    if (pools[i].available < 4096) // not free
        return NULL;

    pool = &pools[i];

    for (; pool->byteIndex != pool->bitmapSize; pool->byteIndex++) // iterate over all the bytes of the bitmap
    {
        uint8_t bitmapByte = *((uint8_t *)pool->base + pool->byteIndex); // get the byte at the offset indicated by i
        for (; pool->bitIndex < 8; pool->bitIndex++, pool->pageIndex++)  // iterate over all the bits of the byte
        {
            uint8_t mask = 0b10000000 >> pool->bitIndex;
            if (mask & bitmapByte) // page at that index is not free
                continue;

            pool->available -= 4096;
            *((uint8_t *)pool->base + pool->byteIndex) |= mask; // apply the mask
            return (void *)(pool->allocableBase + pool->pageIndex * 4096);
        }

        if (pool->bitIndex == 8)
            pool->bitIndex = 0; // reset the bit index
    }

    if (pool->byteIndex < pool->bitmapSize - 1)
    {
        pool->byteIndex = 0;
        return pmmAllocate();
    }

    return NULL;
}

void pmmDeallocate(void *address)
{
    pmm_pool_t *pool = NULL;

    for (int i = 0; i < poolsIndex; i++)
    {
        pool = &pools[i];

        int pageIndex = 0;
        for (int i = 0; i != pool->bitmapSize; i++) // iterate over all the bytes of the bitmap
        {
            uint8_t bitmapByte = *((uint8_t *)pool->base + i); // get the byte at the offset indicated by i
            for (int j = 0; j < 8; j++, pageIndex++)           // iterate over all the bits of the byte
            {
                uint8_t mask = 0b10000000 >> j;
                if (mask & bitmapByte && (void *)(pool->allocableBase + pageIndex * 4096) == address) // page at that index is not free
                {
                    *((uint8_t *)pool->base + i) &= ~(0b10000000 >> j); // mark the page as free
                    pool->available += 4096;
                    return;
                }
            }
        }
    }
}

void pmmInit()
{
    memmap = limineGetMemmap(); // get the memory map
    serialWrites("Entries in memory map: ");
    serialWrites(to_string(memmap->entry_count)); // display the count of the entries in the memory map
    serialWrites("\n");

    for (size_t i = 0; i < memmap->entry_count; i++)
    {
        struct limine_memmap_entry *entry = memmap->entries[i];

        // display data
        serialWrites("Entry ");
        serialWrites(to_string(i));
        serialWrites(": 0x");
        serialWrites(to_hstring(entry->base));
        serialWrites("-0x");
        serialWrites(to_hstring(entry->base + entry->length));
        serialWrites(" ");
        serialWrites(entriesTypes[entry->type]);
        serialWrites("\n");

        // fill metadata about usable pools
        if (entry->type != LIMINE_MEMMAP_USABLE)
            continue;

        pmm_pool_t *pool = &pools[poolsIndex++];
        zero(pool, pmm_pool_t);

        pool->base = entry->base;
        pool->size = entry->length;

        uint64_t requiredBits = pool->size / 4096;        // minimal number of bits required to store all pages' state
        uint64_t requiredBytes = requiredBits / 8;        // minimal number of bytes
        pool->allocableBase = pool->base + requiredBytes; // we store the bitmap in the head of the entry
        pool->allocableSize = pool->size - requiredBytes;
        pool->available = pool->allocableSize;
        pool->bitmapSize = requiredBytes;

        pool->allocableBase = align(pool->allocableBase, 4096); // align to a page

        memset((void *)pool->base, 0, requiredBytes); // clear the bitmap (set all the pages to free)

        serialWrites("We need ");
        serialWrites(to_string(requiredBytes));
        serialWrites(" bytes to store the bitmap bytes\n");
    }
}