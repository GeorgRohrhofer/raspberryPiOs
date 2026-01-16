#include "uart.h"

extern void vectors(void);

static inline void enable_exceptions(void)
{
    asm volatile("msr vbar_el1, %0" :: "r"(vectors));
    asm volatile("isb");
}


void kernel_main(void) {
  uart_init();  
  uart_puts("Hello from my OS on QEMU!\n");

  enable_exceptions();
  uart_puts("Exceptions enabled\n");

  uart_puthex(0x1234);
  uart_puts("\n");
  uart_puthex(0xDEADBEEFCAFEBABE);
  uart_puts("\n");

  uart_puts("VBAR set\n");

  *(volatile u64 *)0x0 = 0x1234;
  asm volatile("brk #0");

  uart_puts("ERROR");

  while (1);
}

