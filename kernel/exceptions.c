#include "exceptions.h"
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

static u64 esr_get_ec(u64 esr)
{
    return (esr >> 26) & 0x3F;
}

static u64 esr_get_iss(u64 esr)
{
    return esr & 0x1FFFFFF;
}

static const char *ec_to_string(u64 ec)
{
    switch (ec) {
    case 0b000000: return "Unknown";
    case 0b010101: return "SVC from EL0";
    case 0b010100: return "SVC from EL1";
    case 0b100000: return "Instruction Abort, lower EL";
    case 0b100001: return "Instruction Abort, same EL";
    case 0b100100: return "Data Abort, lower EL";
    case 0b100101: return "Data Abort, same EL";
    default:       return "Unhandled EC";
    }
}

static u64 read_far_el1(void)
{
    u64 val;
    asm volatile("mrs %0, FAR_EL1" : "=r"(val));
    return val;
}

void exception_sync(void)
{
    uart_puts("\n[EXCEPTION] Synchronous\n");

    u64 esr = read_esr_el1();
    u64 elr = read_elr_el1();
    u64 far = read_far_el1();

    u64 ec  = esr_get_ec(esr);
    u64 iss = esr_get_iss(esr);

    uart_puts("ESR_EL1 = ");
    uart_puthex(esr);
    uart_puts("\n  EC  = ");
    uart_puts(ec_to_string(ec));
    uart_puts("\n  ISS = ");
    uart_puthex(iss);

    uart_puts("\nELR_EL1 = ");
    uart_puthex(elr);

    uart_puts("\nFAR_EL1 = ");
    uart_puthex(far);
    uart_puts("\n");

    panic("Fatal synchronous exception");
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

