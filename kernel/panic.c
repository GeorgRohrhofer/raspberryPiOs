#include "panic.h"
#include "uart.h"

void panic(const char *msg) {
    uart_puts("PANIC: ");
    uart_puts(msg);
    uart_puts("\n");
    while(1){
        asm volatile("wfe");
    }
}
