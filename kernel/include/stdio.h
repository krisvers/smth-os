#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <stdint.h>

#define EOF (-1)

int putc(int ic);
int puts(const char * string);
int printf(const char * restrict fmt, ...);
int log(uint8_t color, const char * restrict fmt, ...);

#endif
