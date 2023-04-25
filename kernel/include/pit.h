#ifndef PIT_H
#define PIT_H

#include <stdint.h>
#include <irq.h>

struct pitEvent {
	void (*func)(Registers * regs);
	uint16_t freq;
	uint16_t offset;
};

int pit_register_event(void (*func)(Registers * regs), uint16_t freq, uint16_t offset);
void pit_set_freq(size_t hz);
void pit_init();

#endif
