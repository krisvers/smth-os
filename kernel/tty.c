#include <tty.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define DEFAULT_COLOR 0x0F

static uint8_t * video_ram;
static uint8_t color = DEFAULT_COLOR;
static uint16_t width = 0;
static uint16_t height = 0;
static bool tty = false;

void tty_clear() {
	if (tty) {
		for (uint8_t * ptr = video_ram; ptr < video_ram + (width * height); *ptr += 2) {
			*ptr = 0x00;
		}
	}
}

void tty_init(uint16_t w, uint16_t h, void * ptr) {
	video_ram = ptr; width = w; height = h;
	stdio_init(w, h, true);
	tty = true;
}

void tty_putc(uint16_t x, uint16_t y, char c) {
	if (tty) {
		video_ram[(x + (y * width)) * 2] = c;
		video_ram[(x + (y * width)) * 2 + 1] = color;
	}
}

void tty_puts(uint16_t x, uint16_t y, const char * str) {
	for (; *str != '\0'; str++) {
		tty_putc(x, y, *str);
		if (++x >= width) {
			x = 0;
			if (++y >= height) {
				y = 0;
			}
		}
	}
}

void tty_set_color(uint8_t c) {
	color = c;
}

void tty_reset_color() {
	color = DEFAULT_COLOR;
}
