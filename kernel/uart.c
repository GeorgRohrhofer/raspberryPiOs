#include "uart.h"

static inline void mmio_write(u64 reg, u32 val) {
    *(volatile unsigned int*)reg = val;
}

static inline unsigned int mmio_read(u64 reg) {
    return *(volatile unsigned int*)reg;
}

void uart_putc(char c) {
    while (mmio_read(UART_BASE + 0x18) & (1 << 5));
    mmio_write(UART_BASE, c);
}

void uart_puts(const char* s) {
    while (*s) uart_putc(*s++);
}
