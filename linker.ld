ENTRY(_start)

SECTIONS {
  . = 0x80000;

  /* Boot code must be first - this is where execution starts */
  .text.boot : {
    _kernel_start = .;
    *(.text.boot)
  }

  /* Kernel header with magic numbers */
  .kernel_header : {
    KEEP(*(.kernel_header))
  }

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
  _kernel_end = .;
  _end = .;

  /* Kernel size calculation */
  _kernel_size = _kernel_end - _kernel_start;

  /* Stack: 16 KB */
  . = ALIGN(16);
  _stack_top = . + 0x4000;
}

