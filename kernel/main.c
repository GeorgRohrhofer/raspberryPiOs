#include "uart.h"

void kernel_main(void) {
    uart_puts("Hello from my OS on QEMU!\n");
    while (1);
}

