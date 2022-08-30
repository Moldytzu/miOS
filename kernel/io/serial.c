#include <io/serial.h>

void serialInit()
{
    // initialisation sequence of the 16550 uart controller chip

    // enable the divisor latch access in the line control register
    uint8_t lineControl = inb(COM1_LINE_CONTROL); // get the line control register contents
    lineControl |= 0b10000000;                    // set the dlab bit
    outb(COM1_LINE_CONTROL, lineControl);         // store back the register

    // set the baud rate divisor to 1 (maximum baud rate)
    outb(COM1_LDIVISOR, 0b00000001);
    outb(COM1_MDIVISOR, 0b00000000);

    // disable the divisor latch access
    lineControl &= ~0b10000000;           // unset the dlab bit
    outb(COM1_LINE_CONTROL, lineControl); // store back the register

    // set the word length to 8 bits (1 byte)
    lineControl |= 0b00000011;            // set the word length select bits to 1 (character length to 8 bits, see 8.1 in the datasheet)
    outb(COM1_LINE_CONTROL, lineControl); // store back the register

    // set the stop bits number to one and disable parity
    lineControl |= 0b00000100;            // set the number of stop bits to 1
    lineControl &= 0b00001000;            // disable parity enable
    outb(COM1_LINE_CONTROL, lineControl); // store back the register

    // disable intrerrupts
    outb(COM1_INTRERRUPT, 0b0); // clear the bits of the intrerrupt enable register

    // disable fifo
    outb(COM1_FIFO, 0); // clear the bits of the fifo control register

    // initialisation end

    serialWrites("miOS initialised COM1!");
}