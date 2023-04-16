#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <tty.h>

static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;
static char hex_chars[16] = "0123456789ABCDEF";

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
