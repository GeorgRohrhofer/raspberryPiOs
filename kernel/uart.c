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

void uart_init(void) {
    // Deactivate UART for configuration
    mmio_write(UART_BASE + 0x30, 0); 

    // Baud Rate: 115200 = 24000000 / (16 * baud)
    // IBRD = 24000000 / (16 * 115200) = 13
    // FBRD = round(0.15625 * 64) = 10
    mmio_write(UART_BASE + 0x24, 13); // IBRD
    mmio_write(UART_BASE + 0x28, 10); // FBRD
    
    // LCRH: 8 Databits, 1 Stopbit, FIFO activated
    mmio_write(UART_BASE + 0x2C, 0x70);
    
    // UART activation + TX/RX activation
    mmio_write(UART_BASE + 0x30, 0x301); // UARTCR: UARTEN + TXE + RXE
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
