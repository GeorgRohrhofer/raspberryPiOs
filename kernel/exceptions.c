#include "exceptions.h"

#include "uart.h"
#include "panic.h"
#include "types.h"

static inline u64 read_esr_el1(void)
{
    u64 v;
    asm volatile("mrs %0, esr_el1" : "=r"(v));
    return v;
}

static inline u64 read_elr_el1(void)
{
    u64 v;
    asm volatile("mrs %0, elr_el1" : "=r"(v));
    return v;
}

void exception_sync(void)
{
    uart_puts("\nEXCEPTION: SYNC\n");
    uart_puts("ESR_EL1 = ");
    uart_puthex(read_esr_el1());
    uart_puts("\nELR_EL1 = ");
    uart_puthex(read_elr_el1());
    uart_puts("\n");

    panic("SYNC");
}

void exception_irq(void)
{
    uart_puts("\nEXCEPTION: IRQ\n");
    panic("IRQ");
}

void exception_fiq(void)
{
    uart_puts("\nEXCEPTION: FIQ\n");
    panic("FIQ");
}

void exception_error(void)
{
    uart_puts("\nEXCEPTION: ERROR\n");
    panic("ERROR");
}

