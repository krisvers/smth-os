extern char _BSS_START;
extern char _BSS_END;

void main();

void __attribute((section(".entry"))) _kentry() {
	main();

	while (1);
}
