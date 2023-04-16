#include <stdlib.h>
#include <stdio.h>
#include <cpu.h>

void abort() {
	printf("Kernel panic!\n");

	cli();
	hlt();

	for (;;);

	__builtin_unreachable();
}
