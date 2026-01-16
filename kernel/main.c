#include "uart.h"
#include "kernel.h"

extern void vectors(void);
extern const kernel_header_t kernel_header;

static inline void enable_exceptions(void)
{
    asm volatile("msr vbar_el1, %0" :: "r"(vectors));
    asm volatile("isb");
}


void kernel_main(void) {
  uart_init();
  uart_puts("RPOS Kernel Booting...\n");
  int verify_result;
  char version[12];

  uart_puts("RPOS Kernel Booting...\n");

  /* Verify kernel integrity via magic numbers */
  verify_result = kernel_verify_header(&kernel_header);
  if (verify_result != 0) {
    uart_puts("FATAL: Kernel header verification failed! Error: ");
    uart_puthex((u64)verify_result);
    uart_puts("\n");
    while (1);  /* Halt on corrupted kernel */
  }

  uart_puts("Kernel header OK - Magic: ");
  uart_puthex(kernel_header.magic0);
  uart_puts(" ");
  uart_puthex(kernel_header.magic1);
  uart_puts("\n");

  /* Print version */
  kernel_get_version(version, sizeof(version));
  uart_puts("Kernel version: ");
  uart_puts(version);
  uart_puts("\n");

  enable_exceptions();
  uart_puts("Exceptions enabled\n");

  uart_puts("VBAR set\n");

  /* Test exception handling (remove in production) */
  *(volatile u64 *)0x0 = 0x1234;
  asm volatile("brk #0");

  uart_puts("ERROR");

  while (1);
}

