#include "exception.h"
#include "panic.h"
#include "uart.h"
#include "types.h"

static u64 read_esr_el1(void)
{
    u64 val;
    asm volatile("mrs %0, ESR_EL1" : "=r"(val));
    return val;
}

static u64 read_elr_el1(void)
{
    u64 val;
    asm volatile("mrs %0, ELR_EL1" : "=r"(val));
    return val;
}

void exception_sync(void)
{
    uart_puts("\n[EXCEPTION] Synchronous\n");

    u64 esr = read_esr_el1();
    u64 elr = read_elr_el1();

    uart_puts("ESR_EL1 = ");
    uart_puthex(esr);
    uart_puts("\nELR_EL1 = ");
    uart_puthex(elr);
    uart_puts("\n");

    panic("Synchronous exception");
}

void exception_irq(void)
{
    panic("IRQ exception");
}

void exception_fiq(void)
{
    panic("FIQ exception");
}

void exception_error(void)
{
    panic("SError exception");
}

