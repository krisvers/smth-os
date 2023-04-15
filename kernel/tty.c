#include <tty.h>
#include <stdint.h>

static uint8_t * const video_ram = ((uint8_t *) 0xB8000);

void tty_clear() {
	for (uint8_t * ptr = video_ram; ptr < video_ram + (80 * 25); *ptr += 2) {
		*ptr = 0x00;
	}
}

void tty_putc(uint16_t x, uint16_t y, char c) {
	video_ram[(x + (y * 80)) * 2] = c;
	video_ram[(x + (y * 80)) * 2 + 1] = 0x02;
}

void tty_puts(uint16_t x, uint16_t y, const char * str) {
	for (; *str != '\0'; str++) {
		tty_putc(x, y, *str);
		if (++x >= 80) {
			x = 0;
			if (++y >= 25) {
				y = 0;
			}
		}
	}
}
