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

void memcpy(void *dest, void *src, size_t count) // copies the contents of an addres to another address
{
    uint8_t *destPtr = (uint8_t *)dest;
    uint8_t *srcPtr = (uint8_t *)src;
    for(; count; count--)
        *(destPtr++) = *(srcPtr++);
}

int memcmp(void *a, void *b, size_t count) // compare blocks of memory
{
    for (size_t i = 0; i < count; i++, a++, b++)
    {
        if (*(uint8_t *)a != *(uint8_t *)b)
            return *(uint8_t *)a - *(uint8_t *)b;
    }

    return 0;
}

// convert to a string (base 10)
char to_stringout[32];
const char *to_string(uint64_t val)
{
    if (!val)
        return "0"; // if the value is 0 then return a constant string "0"

    zero(to_stringout,to_stringout); // clear output
    for (int i = 0; val; i++, val /= 10)
        to_stringout[i] = (val % 10) + '0';

    strrev(to_stringout); // reverse string

    return to_stringout;
}

// convert to a string (base 16)
char to_hstringout[32];
const char *to_hstring(uint64_t val)
{
    const char *digits = "0123456789ABCDEF";
    if (!val)
        return "0"; // if the value is 0 then return a constant string "0"

    zero(to_hstringout,to_hstringout); // clear output

    for (int i = 0; i < 16; i++, val = val >> 4) // shift the value by 4 to get each nibble
        to_hstringout[i] = digits[val & 0xF];    // get each nibble

    strrev(to_hstringout); // reverse string

    // move the pointer until the first valid digit
    uint8_t offset = 0;
    for (; to_hstringout[offset] == '0'; offset++)
        ;

    return to_hstringout + offset; // return the string
}

void strrev(char *str)
{
    size_t len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        const char a = str[i];
        str[i] = str[j];
        str[j] = a;
    }
}