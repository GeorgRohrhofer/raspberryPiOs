.section .text
.align 11 // 2KB aligned
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
