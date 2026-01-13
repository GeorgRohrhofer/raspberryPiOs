#include "registers.h"
#include "uart.h"

void print_registers(registers_t *regs){
  uart_puts("\n=== REGISTER STATE ===\n");

  uart_puts("PC : 0x"); uart_puthex(regs->pc); uart_puts("\n");
  uart_puts("SP : 0x"); uart_puthex(regs->sp); uart_puts("\n");
  uart_puts("PST: 0x"); uart_puthex(regs->pstate); uart_puts("\n");
  uart_puts("LR : 0x"); uart_puthex(regs->x30); uart_puts("\n");

  uart_puts("\n--- General Purpose ---\n");

  for (int i = 0; i < 31; i++) {
    uart_puts("x"); uart_puthex(i); uart_puts(": 0x"); uart_puthex(regs->x0 + i); uart_puts("\n");
  }
}
