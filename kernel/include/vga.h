#ifndef VGA_H
#define VGA_H

#include <stdint.h>

void vga_pallete_test();
void vga_setp(uint16_t x, uint16_t y, uint64_t color);
void vga_clear();
void vga_init(uint16_t w, uint16_t h, void * ptr, uint8_t d);

#endif
