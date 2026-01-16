.global vectors
.align 11

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
    bl exception_sync
    b .

irq_el1:
    bl exception_irq
    b .

fiq_el1:
    bl exception_fiq
    b .

error_el1:
    bl exception_error
    b .

sync_el0:
    b .

irq_el0:
    b .

fiq_el0:
    b .

error_el0:
    b .

