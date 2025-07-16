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
    
    /* 
     * The start address of the vector table must be aligned to 0x800 (i.e., bits [0:10] = 0).
     * Because bits 0–10 in VBAR_EL1 are reserved. 
     */
    .vector ALIGN(0x800) : {
        KEEP(*(.vector))
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
            The count of cores in BCM2711 is 4.

            So, Assign 64Kib to EL1 stack memory
        */
        __stack_EL1_bottom = .;
        . = . + (16K * 4);
        __stack_EL1_top = .;

        /* Guard page for EL1 */
        . = . + (4K);

        /* 
            Assign 32Kib per 1 processor.
            The maximum processors is 10.

            So, Assign 320Kib to EL0 stack memory
        */
         __stack_EL0_bottom = .;
        . = . + (32K * 10);
        __stack_EL0_top = .;

        /* Guard page for EL0 */
        . = . + (4K);

    } > RAM

    /* align again if needed */
    _end = .;
}
