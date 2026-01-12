#include "uart.h"

static inline void mmio_write(u64 reg, u32 val) {
    *(volatile unsigned int*)reg = val;
}

static inline unsigned int mmio_read(u64 reg) {
    return *(volatile unsigned int*)reg;
}

static inline char hex_digit(u8 val) {
  if (val < 10) {
    return '0' + val;
  }

  return 'A' + val - 10;
}


void uart_putc(char c) {
    while (mmio_read(UART_BASE + 0x18) & (1 << 5));
    mmio_write(UART_BASE, c);
}

void uart_puts(const char* s) {
    while (*s) uart_putc(*s++);
}

void uart_puthex(u64 val) {
    uart_puts("0x");
    for (int i = 60; i >= 0; i -= 4) {
        char c = hex_digit((val >> i) & 0xF);
        uart_putc(c);
    }
}
