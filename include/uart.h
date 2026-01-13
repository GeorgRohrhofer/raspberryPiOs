#ifndef _UART_h
#define _UART_h

#include "hardwareDefines.h"
#include "types.h"

void uart_init();
void uart_putc(char c); 
void uart_puts(const char* s);
void uart_puthex(u64 val);

#endif
