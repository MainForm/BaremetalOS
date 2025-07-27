.section ".text.boot"
.code 32
.global _start

    .equ    ARM_MODE_USR,   0x10   
    .equ    ARM_MODE_FIQ,   0x11
    .equ    ARM_MODE_IRQ,   0x12
    .equ    ARM_MODE_SVC,   0x13
    .equ    ARM_MODE_ABT,   0x17
    .equ    ARM_MODE_UND,   0x1B
    .equ    ARM_MODE_SYS,   0x1F
    .equ    ARM_MODE_MON,   0x16
    
.macro SET_STACK mode:req sp_top:req
    MRS     r0, cpsr
    BIC     r0, r0, #0x1F
    LDR     r1, =\mode
    ORR     r0, r0, r1
    MSR     cpsr_c, r0
    ISB

    LDR     sp, =\sp_top
.endm

.macro SET_VECTOR_BASE base:req
    /* Clear SCTLR.V (bit 13) to allow VBAR usage */
    MRC     p15, 0, r0, c1, c0, 0
    BIC     r0, r0, #(1 << 13)
    MCR     p15, 0, r0, c1, c0, 0
    DSB
    ISB

    /* Set VBAR to your vector-table base */
    LDR     r0, =\base
    MCR     p15, 0, r0, c12, c0, 0
    DSB
    ISB
.endm

_start:
    SET_STACK   ARM_MODE_SVC __stack_SVC_top__
    SET_STACK   ARM_MODE_ABT __stack_ABT_top__
    SET_STACK   ARM_MODE_UND __stack_UND_top__
    SET_STACK   ARM_MODE_IRQ __stack_IRQ_top__
    SET_STACK   ARM_MODE_FIQ __stack_FIQ_top__
    SET_STACK   ARM_MODE_SYS __stack_SYS_USR_top__

    // Enble to calculate the float number
    /* CPACR bits[23:20] = 0x0F */
    /* Enable accessibility for CP10 and CP11 coprocessors. */
    LDR     r0, =(0x0F << 20)
    MCR     p15, 0, r0, c1, c0, 2
    ISB

    /* FPEXC.EN = 1 */
    /* Enable the Advanced SIMD and Floating-point Extensions */
    LDR     r0, =(0x01 << 30)
    VMSR    fpexc, r0
    ISB

    // Set the base address of vector table
    SET_VECTOR_BASE vector_table

    // Clear the entire BSS section to 0.
    LDR     r1, =__bss_start__
    LDR     r2, =__bss_end__
    MOV     r0, #0
    clear_bss:
        CMP     r1, r2
        BHS    done_clear
        STR     r0, [r1], #4
        B       clear_bss
    done_clear:

    BL      main
    
halt:
    B   .


// The start address of the vector table must be aligned to 0x20 (i.e., bits [0:4] = 0).
// Because bits 0–4 in VBAR are reserved.
.section .vector, "ax"
.align 5

// This is based on “Table B1-3 The vector tables” in the ARMv7-A and ARMv7-R edition.
vector_table:
    B       .                   // Reset
    B       .                   // Undef
    B       .                   // Supervisor
    B       .                   // Prefetch
    B       .                   // Data
    B       .                   // Not used 
    B       IRQ_ARM_Handler     // IRQ
    B       .                   // FIQ