#ifndef DIO_H
#define DIO_H

#include<stdint.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t d);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t d);

#pragma aux inb = \
"in al, dx" \
value [al] \
parm [dx];

#pragma aux outb = \
"out dx, al" \
parm [dx] [al];

#pragma aux inw = \
"in ax, dx" \
value [ax] \
parm [dx];

#pragma aux outw = \
"out dx, ax" \
parm [dx] [ax]; 

#endif
