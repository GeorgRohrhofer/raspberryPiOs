ENTRY(_start)

SECTIONS {
  . = 0x80000;

  .text : {
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }

  /* Ende des Kernels */
  _end = .;

  /* Stack: 16 KB */
  . = ALIGN(16);
  _stack_top = . + 0x4000;
}

