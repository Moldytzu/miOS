#include <utils.h>

int strlen(char *str) // calculate the lenght in bytes of a string
{
    int i = 0;
    for(; str[i] != 0; i++);
    return i;
}