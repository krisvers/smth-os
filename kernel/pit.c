#include <pit.h>
#include <pic.h>
#include <irq.h>
#include <cpu.h>
#include <io.h>
#include <stdio.h>

#define MAX_PIT_EVENTS 32

static struct pitEvent pit_events[MAX_PIT_EVENTS];
static uint8_t pit_event_num = 0;

static size_t ticks = 0;
static uint16_t hertz = 0;

int pit_register_event(void (*func)(Registers * regs), uint16_t freq, uint16_t offset) {
	if (pit_event_num >= MAX_PIT_EVENTS) {
		return -1;
	}

	pit_events[pit_event_num].func = func;
	pit_events[pit_event_num].freq = freq;
	pit_events[pit_event_num].offset = offset;

	++pit_event_num;
}

static void pit_isr(Registers * regs) {
	pic_send_eoi();
	++ticks;

	for (uint8_t i = 0; i < pit_event_num; i++) {
		if ((ticks % (pit_events[i].freq + pit_events[i].offset)) == 0) {
			pit_events[i].func(regs);
		}
	}
}

void pit_set_freq(size_t hz) {
	size_t div = 3579545 / (hz * 3);
	outb(0x43, 0x36);
	outb(0x40, div & 0xFF);
	outb(0x40, div >> 8);
	hertz = hz;
}

void pit_init() {
	pit_set_freq(10000);
	log(0x07, "pit initialized [");
	log(0x0A, "*");
	log(0x07, "]\n\thertz: %d, ticks: %d\n", hertz, ticks);
	irq_reg_handler(0, pit_isr);
}
