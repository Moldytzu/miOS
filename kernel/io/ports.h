#pragma once
#include <utils.h>

ifunc void outb(uint16_t port, uint8_t val) // out byte
{
    iasm("outb %0, %1" ::"a"(val), "Nd"(port));

    iasm("outb %0, %1" ::"a"((uint8_t)0), "Nd"((uint16_t)0x80)); // wait a bit by sending 0 to the 0x80 port (that isn't present)
}

ifunc uint8_t inb(uint16_t port) // in byte
{
    uint8_t val;
    iasm("inb %%dx,%%al"
         : "=a"(val)
         : "d"(port));
    return val;
}