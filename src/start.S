.section .stack
.align 12

/* 
    Assign 16Kib per 1 CPU core.
    The count of cores in BCM2711 is 10.

    So, Assign 128Kib to EL1 stack memory
*/
el1_stack:
    .skip 128*1024      // Assign 128Kib to EL1 stack memory
el1_stack_top:

/* Guard page for EL1 */
el1_stack_guard:
    .skip 4*1024        // 4KiB guard

/* 
    Assign 32Kib per 1 processor.
    The maximum processors is 10.

    So, Assign 320Kib to EL0 stack memory
*/
el0_stack:
    .skip 320*1024
el0_stack_top:

/* Guard page for EL0 */
el0_stack_guard:
    .skip 4*1024        // 4KiB guard

.section ".text.boot"

.global _start

_start:
    // HCR_EL2: Hypervisor Configuration Register
    // Set the 31 bit of HCR_EL2 to 1 to use AArch64 for EL smaller than EL2
    MOV x0, #(1 << 31)
    MSR hcr_el2, x0

    // Set the top of EL1 Stack address
    LDR x0, =el1_stack_top
    MSR sp_el1, x0

    //Set the top of EL0 Stack address
    LDR x0, =el0_stack_top
    MSR sp_el0, x0

    // SPSR_EL2: Saved Program Status Register for EL2
    // Set the SPSR_EL2 to 0b0101 to use EL1 stack in EL1 mode
    MOV x0, #(0b0101)
    MSR spsr_el2, x0
    
    // ELR_EL2: Exception Link
    LDR x0, =prev_main
    MSR elr_el2, x0

    ERET

.global prev_main
prev_main:
    // enable the FPU and the SIMD to make it possible to use floating-point
    MRS x0, cpacr_el1
    ORR x0, x0, #(0b11 << 20)
    MSR cpacr_el1, x0
    ISB

    // Branch to main function
    BL main

halt:
    wfe
    B halt
