#ifndef FONT_H
#define FONT_H

#include <stdint.h>

void font_set_color(uint8_t color);
void font_putc(uint16_t x, uint16_t y, unsigned char c, uint8_t color);

#endif
