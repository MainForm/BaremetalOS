ENTRY(_start)

/* Add the RAM adressed from 0x0000 0000 to 0x0208 0000  */
MEMORY
{
    RAM   (rwx): ORIGIN = 0x00000000,   LENGTH = 32M
}

SECTIONS
{
    /* Reset address when realview-pb-a8 has been booted. */
    . = 0x00000000;

    .text : { 
        KEEP(*(.text.boot))
        *(.text*)
        *(.rodata*) 
    } > RAM

    .data : { 
        *(.data*) 
    } > RAM

    .bss : {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON) 
        __bss_end__ = .;
    } > RAM

    _end = .;
}
