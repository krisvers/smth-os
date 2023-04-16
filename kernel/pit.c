#include <pit.h>
#include <pic.h>
#include <irq.h>
#include <cpu.h>
#include <io.h>
#include <stdio.h>

static size_t mseconds = 0;

static void timer_handler(Registers * regs) {
	pic_send_eoi();
	mseconds++;
}

void pit_set_freq(size_t hz) {
	size_t div = 3579545 / (hz * 3);
	outb(0x43, 0x36);
	outb(0x40, div & 0xFF);
	outb(0x40, div >> 8);
}

void pit_init() {
	pit_set_freq(1000);
	printf("pit initialized [*]\n\thz: %d, ms: %d\n", 1000, mseconds);
	irq_reg_handler(0, timer_handler);
}
