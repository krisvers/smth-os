#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

#define EOF (-1)

int putc(int ic);
int puts(const char * string);
int printf(const char * restrict fmt, ...);

#endif
