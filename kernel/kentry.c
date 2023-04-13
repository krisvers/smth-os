extern unsigned char _BSS_START;
extern unsigned char _BSS_END;

extern int test(char c);

static unsigned short int cursor = 0;
static unsigned char * const video_ram = ((unsigned char *) 0xB8000);

void putc(char c) {
	video_ram[cursor++] = c;
	video_ram[cursor++] = 0x02;
}

void puts(const char * str) {
	for (; *str != '\0'; str++) {
		putc(*str);
	}
}

void __attribute__((section(".entry"))) _kentry() {
	for (unsigned char * addr = &_BSS_START; addr < &_BSS_END; addr++) {
		addr[0] = 0;
	}

	test(0x69);

	puts("fortnite");

	while(1);
}
