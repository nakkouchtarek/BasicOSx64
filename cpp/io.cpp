#include "typedef.hpp"

void outb(unsigned short port,unsigned char val)
{
    // output value to i/o port
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port)
{
    // get value from i/o port and return it
    unsigned char returnVal;
    asm volatile ("inb %1, %0"
    : "=a"(returnVal)
    : "Nd"(port));
    return returnVal;
}
