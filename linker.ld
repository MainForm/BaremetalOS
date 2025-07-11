ENTRY(_start)

SECTIONS
{
    /* Start address when RaspberryPI4 has been booted. */
    . = 0x80000;

    .text : { 
        KEEP(*(.text.boot))
        *(.text*)
    }

    .rodata : { 
        *(.rodata*) 
    }

    .data : { 
        *(.data*) 
    }

    .bss : { 
        *(.bss*) *(COMMON) 
    }
}