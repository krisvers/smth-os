#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <tty.h>
#include <vga.h>
#include <font.h>

#define SCR_CLEAR()			(tty) ? tty_clear() : vga_clear()
#define SCR_PUTC(x, y, c, color)	(tty) ? tty_putc(x, y, c) : font_putc(x * 8, y * 8, c, color)
#define SCR_COLOR(color)		(tty) ? tty_set_color(color) : font_set_color(color)

static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;
static uint16_t width = 40;
static uint16_t height = 25;
static char hex_chars[16] = "0123456789ABCDEF";
static bool tty = false;

void stdio_init(uint16_t w, uint16_t h, bool t) {
	width = w;
	height = h;
	tty = t;
}

int putc(int ic) {
	switch (ic) {
		case '\n':
			cursor_x = 0;
			if (++cursor_y >= height) {
				cursor_x = 0; cursor_y = 0;
				SCR_CLEAR();
			}
			break;
		case '\t':
			cursor_x += 4;
			if (cursor_x >= width) {
				cursor_x = 0;
			}
			break;
		case '\b':
			if (--cursor_x >= width) {
				if (--cursor_y >= height) {
					return -1;
				}

				cursor_x = width - 1;
				SCR_PUTC(cursor_x, cursor_y, ' ', 0xF);
			}

			SCR_PUTC(cursor_x, cursor_y, ' ', 0xF);

			break;
		default:
			SCR_PUTC(cursor_x, cursor_y, (char) ic, 0xF);
			if (++cursor_x >= width) {
				cursor_x = 0;
				if (++cursor_y >= height) {
					cursor_y = 0;
					SCR_CLEAR();
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

static bool print(const char * data, size_t length) {
	const unsigned char * bytes = (const unsigned char *) data;
	for (size_t i = 0; i < length; i++)
		if (putc(bytes[i]) == EOF) {
			return false;
		}
	return true;
}
 
int printf(const char * restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
 
	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;
 
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%') {
				format++;
			}
			size_t amount = 1;
			while (format[amount] && format[amount] != '%') {
				amount++;
			}
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount)) {
				return -1;
			}
			format += amount;
			written += amount;
			continue;
		}

		const char * format_begun_at = format++;
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c))) {
				return -1;
			}
			written++;
		} else if (*format == 's') {
			format++;
			const char * str = va_arg(parameters, const char *);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len)) {
				return -1;
			}
			written += len;
		} else if (*format == 'd' || *format == 'i') {
			format++;
			int num = va_arg(parameters, int);
			char buffer[32];
			int pos = 0;

			do {
				unsigned long long rem = num % 10;
				num /= 10;
				buffer[pos++] = hex_chars[rem];
			} while (num > 0);

			while (--pos >= 0) {
				putc(buffer[pos]);
			}
		} else if (*format == 'x') {
			putc('0');
			putc('x');
			format++;
			int num = va_arg(parameters, int);
			char buffer[32];
			int pos = 0;

			do {
				unsigned long long rem = num % 16;
				num /= 16;
				buffer[pos++] = hex_chars[rem];
			} while (num > 0);

			while (--pos >= 0) {
				putc(buffer[pos]);
			}
		} else if (*format == 'b') {
			putc('0');
			putc('b');
			format++;
			int num = va_arg(parameters, int);
			char buffer[32];
			int pos = 0;

			do {
				unsigned long long rem = num % 2;
				num /= 2;
				buffer[pos++] = hex_chars[rem];
			} while (num > 0);

			while (--pos >= 0) {
				putc(buffer[pos]);
			}
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len)) {
				return -1;
			}
			written += len;
			format += len;
		}
	}
 
	va_end(parameters);
	return written;
}

int log(uint8_t color, const char * restrict format, ...) {
	SCR_COLOR(color);

	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
 
	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;
 
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%') {
				format++;
			}
			size_t amount = 1;
			while (format[amount] && format[amount] != '%') {
				amount++;
			}
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				goto errno;
			}
			if (!print(format, amount)) {
				goto errno;
			}
			format += amount;
			written += amount;
			continue;
		}

		const char * format_begun_at = format++;
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				goto errno;

			}
			if (!print(&c, sizeof(c))) {
				goto errno;
			}
			written++;
		} else if (*format == 's') {
			format++;
			const char * str = va_arg(parameters, const char *);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				goto errno;
			}
			if (!print(str, len)) {
				goto errno;
			}
			written += len;
		} else if (*format == 'd' || *format == 'i') {
			format++;
			int num = va_arg(parameters, int);
			char buffer[32];
			int pos = 0;

			do {
				unsigned long long rem = num % 10;
				num /= 10;
				buffer[pos++] = hex_chars[rem];
			} while (num > 0);

			while (--pos >= 0) {
				putc(buffer[pos]);
			}
		} else if (*format == 'x') {
			putc('0');
			putc('x');
			format++;
			int num = va_arg(parameters, int);
			char buffer[32];
			int pos = 0;

			do {
				unsigned long long rem = num % 16;
				num /= 16;
				buffer[pos++] = hex_chars[rem];
			} while (num > 0);

			while (--pos >= 0) {
				putc(buffer[pos]);
			}
		} else if (*format == 'b') {
			putc('0');
			putc('b');
			format++;
			int num = va_arg(parameters, int);
			char buffer[32];
			int pos = 0;

			do {
				unsigned long long rem = num % 2;
				num /= 2;
				buffer[pos++] = hex_chars[rem];
			} while (num > 0);

			while (--pos >= 0) {
				putc(buffer[pos]);
			}
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				goto errno;
			}
			if (!print(format, len)) {
				goto errno;
			}
			written += len;
			format += len;
		}
	}
 
	va_end(parameters);
	(tty) ? tty_reset_color() : font_set_color(0);
	return written;

errno:
	(tty) ? tty_reset_color() : font_set_color(0);
	return -1;
}
