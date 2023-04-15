#include <stdio.h>
#include <stdint.h>
#include <tty.h>

static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;

int putc(int ic) {
	switch (ic) {
		case '\n':
			cursor_x = 0;
			if (++cursor_y >= 25) {
				cursor_x = 0; cursor_y = 0;
				tty_clear();
			}
			break;
		case '\t':
			cursor_x += 4;
			if (cursor_x >= 80) {
				cursor_x = 0;
			}
			break;
		case '\b':
			if (--cursor_x >= 80) {
				if (--cursor_y >= 25) {
					return -1;
				}

				cursor_x = 79;
				tty_putc(cursor_x, cursor_y, ' ');
			}

			tty_putc(cursor_x, cursor_y, ' ');

			break;
		default:
			tty_putc(cursor_x, cursor_y, (char) ic);
			if (++cursor_x >= 80) {
				cursor_x = 0;
				if (++cursor_y >= 25) {
					cursor_y = 0;
					tty_clear();
				}
			}

			break;
	}
	
	return ic;
}

int puts(const char * string) {
	for (; *string != '\0'; string++) {
		putc(*string);
	}

	return *string;
}
