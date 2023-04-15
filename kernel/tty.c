#include <tty.h>

static unsigned char * const video_ram = ((unsigned char *) 0xB8000);

void tty_putc(uint16_t x, uint16_t y, char c) {
	video_ram[(x + y * 80) * 2] = c;
	video_ram[(x + y * 80) * 2 + 1] = 0x02;
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
