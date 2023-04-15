#ifndef TTY_H
#define TTY_H

#include <stdint.h>

void tty_putc(uint16_t x, uint16_t y, char c);
void tty_puts(uint16_t x, uint16_t y, const char * str);

#endif
