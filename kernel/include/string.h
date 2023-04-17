#ifndef STRING_H
#define STRING_H

#include <stdint.h>

size_t strlen(const char * str);
void * memcpy(void * dest, const void * src, size_t len);
void * memset(void * dest, uint8_t value, size_t len);
void * mempcpy(void * dest, const void * src, size_t len);
char * strcpy(char * dest, const char * src);

#endif
