ENTRY(_start)

/* Add the RAM adressed from 0x0008 0000 to 0x0208 0000  */
MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000, LENGTH = 32M
}

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

    /* align to page boundary */
    . = ALIGN(4096);

    /* stack section */
    .stack : {
        *(.stack*)
    }

    /* align again if needed */
    . = ALIGN(4096);
}