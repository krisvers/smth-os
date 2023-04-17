#ifndef TTY_H
#define TTY_H

#include <stdint.h>

void tty_clear();
void tty_init(uint16_t w, uint16_t h, void * ptr);
void tty_putc(uint16_t x, uint16_t y, char c);
void tty_puts(uint16_t x, uint16_t y, const char * str);
void tty_set_color(uint8_t color);
void tty_reset_color();

#endif
