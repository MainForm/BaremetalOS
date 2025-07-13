ENTRY(_start)

/* Add the RAM adressed from 0x0008 0000 to 0x0208 0000  */
MEMORY
{
    RAM   (rwx): ORIGIN = 0x80000,   LENGTH = 32M
}

SECTIONS
{
    /* Start address when RaspberryPI4 has been booted. */
    . = 0x80000;

    .text : { 
        KEEP(*(.text.boot))
        *(.text*)
        *(.rodata*) 
    } > RAM

    .data : { 
        *(.data*) 
    } > RAM

    .bss : { 
        *(.bss*)
        *(COMMON) 
    } > RAM

        /* stack section */
    .stack (NOLOAD) : {
        /* align to page boundary */
        . = ALIGN(16);

        /* 
            Assign 16Kib per 1 CPU core.
            The count of cores in BCM2711 is 10.

            So, Assign 128Kib to EL1 stack memory
        */
        __stack_EL1_bottom = .;
        . = . + (128K);
        __stack_EL1_top = .;

        /* Guard page for EL1 */
        . = . + (4K);

        /* 
            Assign 32Kib per 1 processor.
            The maximum processors is 10.

            So, Assign 320Kib to EL0 stack memory
        */
         __stack_EL0_bottom = .;
        . = . + (320K);
        __stack_EL0_top = .;

        /* Guard page for EL0 */
        . = . + (4K);

    } > RAM

    /* align again if needed */
    _end = .;
}
