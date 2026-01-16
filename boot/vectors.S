.global vectors
.align 11

// Save all registers to the stack (34 * 8 = 272 bytes)
.macro save_registers
    sub sp, sp, #272
    stp x0, x1, [sp, #0]
    stp x2, x3, [sp, #16]
    stp x4, x5, [sp, #32]
    stp x6, x7, [sp, #48]
    stp x8, x9, [sp, #64]
    stp x10, x11, [sp, #80]
    stp x12, x13, [sp, #96]
    stp x14, x15, [sp, #112]
    stp x16, x17, [sp, #128]
    stp x18, x19, [sp, #144]
    stp x20, x21, [sp, #160]
    stp x22, x23, [sp, #176]
    stp x24, x25, [sp, #192]
    stp x26, x27, [sp, #208]
    stp x28, x29, [sp, #224]

    // Save x30 (LR), and the original SP (before we modified it)
    add x0, sp, #272
    stp x30, x0, [sp, #240]

    // Save ELR_EL1 and SPSR_EL1
    mrs x0, elr_el1
    mrs x1, spsr_el1
    stp x0, x1, [sp, #256]
.endm

// Restore all registers from the stack
.macro restore_registers
    // Restore ELR_EL1 and SPSR_EL1
    ldp x0, x1, [sp, #256]
    msr elr_el1, x0
    msr spsr_el1, x1

    ldp x0, x1, [sp, #0]
    ldp x2, x3, [sp, #16]
    ldp x4, x5, [sp, #32]
    ldp x6, x7, [sp, #48]
    ldp x8, x9, [sp, #64]
    ldp x10, x11, [sp, #80]
    ldp x12, x13, [sp, #96]
    ldp x14, x15, [sp, #112]
    ldp x16, x17, [sp, #128]
    ldp x18, x19, [sp, #144]
    ldp x20, x21, [sp, #160]
    ldp x22, x23, [sp, #176]
    ldp x24, x25, [sp, #192]
    ldp x26, x27, [sp, #208]
    ldp x28, x29, [sp, #224]
    ldp x30, xzr, [sp, #240]
    add sp, sp, #272
.endm

vectors:
    // EL1t (EL1 using SP_EL0)
    .balign 0x80
    b sync_el1
    .balign 0x80
    b irq_el1
    .balign 0x80
    b fiq_el1
    .balign 0x80
    b error_el1

    // EL1h (EL1 using SP_EL1) - this is where kernel exceptions go
    .balign 0x80
    b sync_el1
    .balign 0x80
    b irq_el1
    .balign 0x80
    b fiq_el1
    .balign 0x80
    b error_el1

    // EL0 64bit
    .balign 0x80
    b sync_el0
    .balign 0x80
    b irq_el0
    .balign 0x80
    b fiq_el0
    .balign 0x80
    b error_el0

    // EL0 32bit
    .balign 0x80
    b sync_el0
    .balign 0x80
    b irq_el0
    .balign 0x80
    b fiq_el0
    .balign 0x80
    b error_el0

sync_el1:
    save_registers
    mov x0, sp              // Pass pointer to saved registers
    bl exception_sync
    restore_registers
    eret

irq_el1:
    save_registers
    mov x0, sp
    bl exception_irq
    restore_registers
    eret

fiq_el1:
    save_registers
    mov x0, sp
    bl exception_fiq
    restore_registers
    eret

error_el1:
    save_registers
    mov x0, sp
    bl exception_error
    restore_registers
    eret

sync_el0:
    b .

irq_el0:
    b .

fiq_el0:
    b .

error_el0:
    b .

