#include <tty.h>

static unsigned short int cursor_x = 0;
static unsigned short int cursor_y = 0;
static unsigned char * const video_ram = ((unsigned char *) 0xB8000);

void putc(char c) {
	if (c == '\n') {
		cursor_x = 0;
		
		if (++cursor_y >= 25) {
			cursor_x = 0; cursor_y = 0;
		}

		return;
	}

	video_ram[(cursor_x + cursor_y * 80) * 2] = c;
	video_ram[(cursor_x + cursor_y * 80) * 2 + 1] = 0x02;

	if (++cursor_x >= 80) {
		if (++cursor_y >= 25) {
			cursor_x = 0; cursor_y = 0;
		}
	}
}

void puts(const char * str) {
	for (; *str != '\0'; str++) {
		putc(*str);
	}
}
