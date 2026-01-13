#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "registers.h"

void exception_sync(registers_t *regs);
void exception_irq(registers_t *regs);
void exception_fiq(registers_t *regs);
void exception_error(registers_t *regs);

#endif
