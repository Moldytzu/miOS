#include <io/ports.h>

#define COM1 0x3F8
#define COM1_DATA (COM1 + 0)
#define COM1_INTRERRUPT (COM1 + 1)
#define COM1_LDIVISOR (COM1 + 0)
#define COM1_MDIVISOR (COM1 + 1)
#define COM1_FIFO (COM1 + 2)
#define COM1_LINE_CONTROL (COM1 + 3)
#define COM1_MODEM_CONTROL (COM1 + 4)
#define COM1_LINE_STATUS (COM1 + 5)
#define COM1_MODEM_STATUS (COM1 + 6)
#define COM1_SCRATCH (COM1 + 7)

void serialInit();

ifunc void serialWrite(char character)
{
    if(character == '\n') // we don't use carriage return in combination with line feed in our OS
        outb(COM1, '\r'); // send the carriage return

    outb(COM1, character); // send the character
}

ifunc void serialWrites(const char *str)
{
    while(*str) // write every byte of the string
        serialWrite(*str++);
}