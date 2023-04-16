#ifndef IRQ_H
#define IRQ_H

#include <cpu.h>

typedef void (*IRQHandler)(Registers * regs);

void irq_init();
void irq_reg_handler(int irq, IRQHandler handler);

#endif
