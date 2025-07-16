.section ".text.boot"
.global _start

_start:
    // HCR_EL2: Hypervisor Configuration Register
    // Set the 31 bit of HCR_EL2 to 1 to use AArch64 for EL smaller than EL2
    MOV x0, #(1 << 31)
    MSR hcr_el2, x0
    ISB

    // Set the top of EL1 Stack address
    LDR x0, =__stack_EL1_top
    MSR sp_el1, x0
    ISB

    //Set the top of EL0 Stack address
    // LDR x0, =__stack_EL0_top
    // MSR sp_el0, x0
    // ISB

    // SPSR_EL2: Saved Program Status Register for EL2
    // Set the SPSR_EL2 to 0b0101 to use EL1 stack in EL1 mode
    MOV x0, #(0b0101)
    MSR spsr_el2, x0
    ISB
    
    // ELR_EL2: Exception Link
    LDR x0, =prev_main
    MSR elr_el2, x0
    ISB

    ERET

.global prev_main
prev_main:
    // Enable the FPU and the SIMD to make it possible to use floating-point
    // The FPU and the SIMD must be set when in the EL1 mode
    MRS x0, cpacr_el1
    ORR x0, x0, #(0b11 << 20)
    MSR cpacr_el1, x0
    ISB

    // Set the vector table address in VBAR_EL1 so that the ARM core knows where to fetch the exception handler commands.
    ADR x0, vector_table
    MSR VBAR_EL1, x0
    ISB

    // Clear the entire BSS section to 0.
    ADR x1, __bss_start__
    ADR X2, __bss_end__
    MOV x0, #0
    clear_bss:
        CMP     x1, X2
        B.HS    done_clear
        STR     x0, [x1], #8
        B       clear_bss
    done_clear:

    // Branch to main function
    BL main

halt:
    wfe
    B halt

// The start address of the vector table must be aligned to 0x800 (i.e., bits [0:10] = 0).
// Because bits 0–10 in VBAR_EL1 are reserved.
.section .vector, "ax"
.align 11

// The offset address for each vector must be set to 0x80 (1 << 7).
// This is based on “Table D1-7: Vector offsets from vector table base address” in the ARMv8-A Architecture Reference Manual.
vector_table:
    BL   halt
    .align 7
    BL   halt
    .align 7
    BL   halt
    .align 7
    BL   halt
    .align 7

    BL   halt
    .align 7
    BL   IRQ_Handler
    ERET
    
    .align 7
    BL   halt
    .align 7
    BL   halt
    .align 7