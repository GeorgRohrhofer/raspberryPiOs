.global vectors
.align 11

vectors:
    // EL1t
    b sync_el1
    b irq_el1
    b fiq_el1
    b error_el1

    // EL1h
    b sync_el1
    b irq_el1
    b fiq_el1
    b error_el1

    // EL0 64bit
    b sync_el0
    b irq_el0
    b fiq_el0
    b error_el0

    // EL0 32bit
    b sync_el0
    b irq_el0
    b fiq_el0
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

