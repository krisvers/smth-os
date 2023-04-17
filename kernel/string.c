#include <string.h>
#include <stdint.h>

size_t strlen(const char * str) {
	const char * s;

	for (s = str; *s; ++s);

	return s - str;
}

void * memset(void * dest, uint8_t value, size_t len) {
	uint8_t * d = dest;

	while (len-- && d++) {
		*d = value;
	}

	return dest;
}

void * memcpy(void * dest, const void * src, size_t len) {
	char * d = (char *) dest;
	const char * s = src;

	while (len--) {
		*d++ = *s++;
	}

	return dest;
}

void * mempcpy(void * dest, const void * src, size_t len) {
	char * d = (char *) dest;
	const char * s = src;

	for (; len--;) {
		*d++ = *s++;
	}

	return d;
}

char * strcpy(char * dest, const char * src) {
	char * p = mempcpy(dest, src, strlen(src));

	*p = '\0';

	return dest;
}
