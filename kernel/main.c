#include "uart.h"

extern void vectors(void);

void kernel_main(void) {
  uart_init();  
  uart_puts("Hello from my OS on QEMU!\n");

  uart_puthex(0x1234);
  uart_puts("\n");
  uart_puthex(0xDEADBEEFCAFEBABE);
  uart_puts("\n");

  asm volatile("msr VBAR_EL1, %0" :: "r"(vectors));
  asm volatile("isb");   // SEHR WICHTIG

  uart_puts("VBAR set\n");

  *(volatile u64 *)0x0 = 0x1234;

  while (1);
}

