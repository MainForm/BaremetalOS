ENTRY(_start)

/* Add the RAM adressed from 0x0000 0000 to 0x0200 0000  */
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

    /* 
     * The start address of the vector table must be aligned to 0x20 (i.e., bits [0:4] = 0).
     * Because bits 0–4 in VBAR_EL1 are reserved. 
     */
    .vector ALIGN(0x20) : {
        KEEP(*(.vector*))
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

    /*
     * - Stack structure(48Kb + 256B)
     *      Guard page   : 4K
     *      SYS, USR    : 16Kb
     *      Guard page   : 4K
     *      SVC         : 2Kb
     *      Guard page   : 4K
     *      IRQ         : 1Kb
     *      Guard page   : 4K
     *      FIQ         : 256B
     *      Guard page   : 4K
     *      ABT         : 512B
     *      Guard page   : 4K
     *      UND         : 512B
     *      Guard page   : 4K
     */
    .stack (NOLOAD) : {
        /* align to page boundary */
        . = ALIGN(0x1000);

        . = . + 4K; /* Guard page to prevent stack overflow */

        __stack_SYS_USR_bottom__ = .;
        . = . + 16K;
        __stack_SYS_USR_top__ = .;

        . = ALIGN(0x1000);
        . = . + 4K; /* Guard page to prevent stack overflow */

        __stack_SVC_bottom__ = .;
        . = . + 2K;
        __stack_SVC_top__ = .;

        . = ALIGN(0x1000);
        . = . + 4K; /* Guard page to prevent stack overflow */

        __stack_IRQ_bottom__ = .;
        . = . + 1K;
        __stack_IRQ_top__ = .;

        . = ALIGN(0x1000);
        . = . + 4K; /* Guard page to prevent stack overflow */
        
        __stack_FIQ_bottom__ = .;
        . = . + 256;
        __stack_FIQ_top__ = .;

        . = ALIGN(0x1000);
        . = . + 4K; /* Guard page to prevent stack overflow */

        __stack_ABT_bottom__ = .;
        . = . + 512;
        __stack_ABT_top__ = .;

        . = ALIGN(0x1000);
        . = . + 4K; /* Guard page to prevent stack overflow */

        __stack_UND_bottom__ = .;
        . = . + 512;
        __stack_UND_top__ = .;

        . = ALIGN(0x1000);
        . = . + 4K; /* Guard page to prevent stack overflow */
    } > RAM

    _end = .;
}
