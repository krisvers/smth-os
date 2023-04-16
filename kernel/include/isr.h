#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include <cpu.h>

typedef void (*ISRHandler) (Registers* regs);

void isr_init();
void isr_reg_handler(int interrupt, ISRHandler handler);

#endif
