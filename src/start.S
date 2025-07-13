.section ".text.boot"
.global _start

_start:
    // HCR_EL2: Hypervisor Configuration Register
    // Set the 31 bit of HCR_EL2 to 1 to use AArch64 for EL smaller than EL2
    MOV x0, #(1 << 31)
    MSR hcr_el2, x0

    // Set the top of EL1 Stack address
    LDR x0, =__stack_EL1_top
    MSR sp_el1, x0

    //Set the top of EL0 Stack address
    LDR x0, =__stack_EL0_top
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
    // Enable the FPU and the SIMD to make it possible to use floating-point
    // The FPU and the SIMD must be set when in the EL1 mode
    MRS x0, cpacr_el1
    ORR x0, x0, #(0b11 << 20)
    MSR cpacr_el1, x0
    ISB

    // Branch to main function
    BL main

halt:
    wfe
    B halt
