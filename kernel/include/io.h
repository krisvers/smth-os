#ifndef IO_H
#define IO_H

#include <stdint.h>

#define UNUSED_PORT 0x80

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void outb(uint8_t value, uint16_t port);
void outw(uint16_t value, uint16_t port);
void outl(uint32_t value, uint16_t port);

inline void io_wait() {
	inb(UNUSED_PORT);
}

#endif
