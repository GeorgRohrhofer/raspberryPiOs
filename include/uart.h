#ifndef _UART_h
#define _UART_h

#include "hardwareDefines.h"
#include "types.h"

static inline void mmio_write(u64 reg, u32 val);
static inline unsigned int mmio_read(u64 reg);

void uart_putc(char c); 
void uart_puts(const char* s);

#endif
