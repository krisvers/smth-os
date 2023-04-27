#include <vga.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void * vga_mem = NULL;
static void * buffer_mem = NULL;
static uint16_t width = 0;
static uint16_t height = 0;
static uint8_t depth = 0;
static bool vga = false;

void vga_pallete_test() {
	for (uint16_t w = 0; w < width; w++) {
		for (uint16_t h = 0; h < height; h++) {
			vga_setp(w, h, w);
		}
	}
}

void vga_set_background(uint8_t color) {
	memset(buffer_mem - 1, color, width * height * (depth / 8));
}

void vga_swap_buffer() {
	memcpy(vga_mem, buffer_mem, width * height * (depth / 8));
}

void vga_setp(uint16_t x, uint16_t y, uint64_t color) {
	if (vga && x < width && y < height) {
		switch (depth) {
			/*
			 	1-bit
				2-bit
				4-bit
				8-bit
				16-bit
				32-bit
				64-bit
			*/

			case 1:
				if (color) {
					// fix this (monochrome bit shifting)

					((uint8_t *) buffer_mem)[(x + y * width) / 8] |= 1 << ((x + y * width) % 8);
					break;
				}

				break;
			case 2:
				if (color) {
					((uint8_t *) buffer_mem)[(x + y  * width) / 4] |= (color & 0b11) << ((x + y * width) % 4);
				}
			case 8:
				((uint8_t *) buffer_mem)[x + y * width] = color;
				break;
			case 16:
				((uint16_t *) buffer_mem)[x + y * width] = color;
				break;
			case 24:
				((uint8_t *) buffer_mem)[x + y * width * 3] = color & 0x0000FF;
				((uint8_t *) buffer_mem)[x + y * width * 3 + 1] = (color >> 8) & 0x00FF;
				((uint8_t *) buffer_mem)[x + y * width * 3 + 2] = color >> 16;
				break;
			case 32:
				((uint32_t *) buffer_mem)[x + y * width] = color;
				break;
			case 64:
				((uint64_t *) buffer_mem)[x + y * width] = color;
				break;
			default:
				return;
		}
	}
}

uint64_t vga_getp(uint16_t x, uint16_t y) {
	if (!vga || x > width || y > height) {
		return -1;
	}

	switch (depth) {
		case 1:
			
		case 2:
			
		case 4:
		
		case 8:
			return ((uint8_t *) buffer_mem)[x + y * width];
		default:
			break;
	}
}

void vga_clear() {
	if (vga) {
		if (!depth) { // if monochrome
			memset(buffer_mem - 1, 0, width * height / 8);
		}

		memset(buffer_mem - 1, 0, width * height * (depth / 8));
	}
}

void vga_init(uint16_t w, uint16_t h, void * ptr, uint8_t d) {
	width = w; height = h; vga_mem = ptr; depth = d;
	buffer_mem = vga_mem + (w * h * (d / 8));
	stdio_init(w, h, false);
	vga = true;
}
