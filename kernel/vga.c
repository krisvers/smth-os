#include <vga.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static void * vga_mem = NULL;
static uint16_t width = 0;
static uint16_t height = 0;
static uint8_t depth = 0;
static bool vga = false;

void vga_setp(uint16_t x, uint16_t y, uint64_t color) {
	if (vga) {
		switch (depth) {
			case 0:
				if (color) {
					// fix this (monochrome bit shifting)

					((uint8_t *) vga_mem)[((x + y * width) / 2)] |= 1 << ((x + y * width) % 2);
					break;
				}

				((uint8_t *) vga_mem)[(x + y * width) / 2] = ~(~((uint8_t *) vga_mem)[(x + y * width) / 2] | (1 << ((x + y * width) % 2)));
			case 1:
				((uint8_t *) vga_mem)[x + y * width] = color;
				break;
			case 2:
				((uint16_t *) vga_mem)[x + y * width] = color;
				break;
			case 4:
				((uint32_t *) vga_mem)[x + y * width] = color;
				break;
			case 8:
				((uint64_t *) vga_mem)[x + y * width] = color;
				break;
			case 0xFF:
				// implement 4 color mode
				return;
			default:
				return;
		}
	}
}

void vga_clear() {
	if (vga) {
		if (!depth) {
			memset(vga_mem, 0, width * height / 8);
		}

		memset(vga_mem, 0, width * height * depth);
	}
}

void vga_init(uint16_t w, uint16_t h, void * ptr, uint8_t d) {
	width = w; height = h; vga_mem = ptr; depth = d;
	vga = true;
}
