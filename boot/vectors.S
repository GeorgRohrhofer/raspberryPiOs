.section .text
.align 11
.global vectors
vectors:
    b sync_el1
    .space 124
    b irq_el1
    .space 124
    b fiq_el1
    .space 124
    b error_el1
    .space 124
sync_el1:
    stp x29, x30, [sp, #-16]!
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    stp x0, xzr, [sp, #-16]!    // x0 und ein Dummy (für 16-byte Align)
    // SP, ELR, SPSR sichern
    mov x0, sp
    stp x0, xzr, [sp, #-16]!    // SP + Dummy
    mrs x0, ELR_EL1
    stp x0, xzr, [sp, #-16]!    // ELR + Dummy
    mrs x0, SPSR_EL1
    str x0, [sp, #-8]!          // SPSR (8-byte, letzte Position)
    mov x0, sp
    bl exception_sync
    // Wiederherstellung
    ldr x0, [sp], #8            // SPSR
    msr SPSR_EL1, x0
    ldp x0, xzr, [sp], #16      // ELR
    msr ELR_EL1, x0
    ldp x0, xzr, [sp], #16      // Alter SP (ignoriert)
    ldp x0, x1, [sp], #16       // x0, x1
    ldp x2, x3, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x28, x29, [sp], #16
    ldp x30, xzr, [sp], #16     // LR
    eret
irq_el1:
    stp x29, x30, [sp, #-16]!
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    stp x0, xzr, [sp, #-16]!
    mov x0, sp
    stp x0, xzr, [sp, #-16]!
    mrs x0, ELR_EL1
    stp x0, xzr, [sp, #-16]!
    mrs x0, SPSR_EL1
    str x0, [sp, #-8]!
    mov x0, sp
    bl exception_irq
    ldr x0, [sp], #8
    msr SPSR_EL1, x0
    ldp x0, xzr, [sp], #16
    msr ELR_EL1, x0
    ldp x0, xzr, [sp], #16
    ldp x0, x1, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x28, x29, [sp], #16
    ldp x30, xzr, [sp], #16
    eret
fiq_el1:
    stp x29, x30, [sp, #-16]!
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    stp x0, xzr, [sp, #-16]!
    mov x0, sp
    stp x0, xzr, [sp, #-16]!
    mrs x0, ELR_EL1
    stp x0, xzr, [sp, #-16]!
    mrs x0, SPSR_EL1
    str x0, [sp, #-8]!
    mov x0, sp
    bl exception_fiq
    ldr x0, [sp], #8
    msr SPSR_EL1, x0
    ldp x0, xzr, [sp], #16
    msr ELR_EL1, x0
    ldp x0, xzr, [sp], #16
    ldp x0, x1, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x28, x29, [sp], #16
    ldp x30, xzr, [sp], #16
    eret
error_el1:
    stp x29, x30, [sp, #-16]!
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    stp x0, xzr, [sp, #-16]!
    mov x0, sp
    stp x0, xzr, [sp, #-16]!
    mrs x0, ELR_EL1
    stp x0, xzr, [sp, #-16]!
    mrs x0, SPSR_EL1
    str x0, [sp, #-8]!
    mov x0, sp
    bl exception_error
    ldr x0, [sp], #8
    msr SPSR_EL1, x0
    ldp x0, xzr, [sp], #16
    msr ELR_EL1, x0
    ldp x0, xzr, [sp], #16
    ldp x0, x1, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x28, x29, [sp], #16
    ldp x30, xzr, [sp], #16
    eret
