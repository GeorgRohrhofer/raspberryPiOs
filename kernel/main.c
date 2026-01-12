#include "uart.h"

void kernel_main(void) {
    uart_puts("Hello from my OS on QEMU!\n");

    uart_puthex(0x1234);
    uart_puts("\n");
    uart_puthex(0xDEADBEEFCAFEBABE);
    uart_puts("\n");

    while (1);
}

