#include <utils.h>

int strlen(const char *str) // calculate the lenght in bytes of a string
{
    int i = 0;
    for (; str[i] != 0; i++)
        ;
    return i;
}

void memset(void *dest, uint8_t data, size_t count) // sets the contents of the addresses in the range of [dest, dest + count] to the data argument
{
    uint8_t *destPtr = (uint8_t *)dest;
    for(; count; count--)
        *(destPtr++) = data;
}