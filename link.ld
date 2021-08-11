SECTIONS {
	. = 0x280000;
	. = ALIGN(8);
    .text :
	{
		start.o(.text.boot)
		main.o(.text)
		*(.text)
	}
    .rodata ALIGN(8) : {
		*(.rodata .rodata.*)
    }
    . = ALIGN(4096);
    PROVIDE(_data = .);
    .data ALIGN(8) : {
		*(.data .data.*)
	}
    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }
    . = ALIGN(4096);
    _end = .;
    /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start) >> 3;