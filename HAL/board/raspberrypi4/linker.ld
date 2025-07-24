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
        __bss_start__ = .;
        *(.bss*)
        *(COMMON) 
        __bss_end__ = .;
    } > RAM

     /* stack section */
    CORE_COUNT                  =  4;
    EL1_KERNEL_STACK_SIZE       = 16K;   /* 커널 */
    EL1_IRQ_STACK_SIZE          =  4K;   /* IRQ */
    EL1_GUARD_SIZE              =  4K;   /* per-stack guard */
    EL1_STRIDE                  = EL1_KERNEL_STACK_SIZE + EL1_IRQ_STACK_SIZE + (EL1_GUARD_SIZE * 2);

    TASK_COUNT                  = 10;
    EL0_USTACK_SIZE             = 32K;   /* 사용자 모드 */
    EL0_GUARD_SIZE              =  4K;

    PAGE_SIZE                   =  4K;

    .stack (NOLOAD) : {
        /* align to page boundary */
        . = ALIGN(PAGE_SIZE);

        /* 
            Assign 28Kib(16Kib for kerenl, 4Kib for IRQ, 8Kib for Gard page) per 1 CPU core.
            The count of cores in BCM2711 is 4.

            So, Assign 112Kib to EL1 stack memory
        */
        __stack_EL1_bottom__ = .;

        /*
        EL1 stack structure
        4Kb     for gard page
        4Kb    for IRQ
        4Kb     for gard page
        16Kb     for kernel
        */
        . = . + (EL1_STRIDE * CORE_COUNT);

        __stack_EL1_top__ = .;

        /* Guard page for EL1 to prevent overflow */
        . = . + PAGE_SIZE;

        /* 
            Assign 32Kib per 1 task.
            The maximum tasks is 10.

            So, Assign 320Kib to EL0 stack memory
        */
        . = ALIGN(PAGE_SIZE);

         __stack_EL0_bottom__ = .;
        . = . + (32K * TASK_COUNT);
        __stack_EL0_top__ = .;

        /* Guard page for EL0 to prevent overflow */
        . = . + PAGE_SIZE;

    } > RAM

    /* align again if needed */
    _end = .;
}
