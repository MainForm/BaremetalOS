.section ".text.boot"
.global _start

_start:
    // Set the sp register to the EL1 stack top address temporarily.
    LDR     x0, =__stack_EL1_top__
    MOV     sp, x0

    // HCR_EL2: Hypervisor Configuration Register
    // Set the 31 bit of HCR_EL2 to 1 to use AArch64 for EL smaller than EL2
    MOV     x0, #(1 << 31)
    MSR     hcr_el2, x0
    ISB

    // Set up the sp register to the EL1 stack top based on the current core ID
    BL      get_el1_current_core_sp_top
    MSR     sp_el1, x0
    ISB

    // Set the top of EL1 Stack address
    // LDR     x0, =__stack_EL1_top__
    // MSR     sp_el1, x0
    // ISB

    //Set the top of EL0 Stack address
    // LDR     x0, =__stack_EL0_top
    // MSR     sp_el0, x0
    // ISB

    // SPSR_EL2: Saved Program Status Register for EL2
    // Set the SPSR_EL2 to 0b0101 to use EL1 stack in EL1 mode
    MOV     x0, #(0b0101)
    MSR     spsr_el2, x0
    ISB
    
    // ELR_EL2: Exception Link
    LDR     x0, =prev_main
    MSR     elr_el2, x0
    ISB

    ERET

.global prev_main
prev_main:
    // Enable the FPU and the SIMD to make it possible to use floating-point
    // The FPU and the SIMD must be set when in the EL1 mode
    MRS     x0, cpacr_el1
    ORR     x0, x0, #(0b11 << 20)
    MSR     cpacr_el1, x0
    ISB

    // Set the vector table address in VBAR_EL1 so that the ARM core knows where to fetch the exception handler commands.
    ADR     x0, vector_table
    MSR     vbar_el1, x0
    ISB

    // Clear the entire BSS section to 0.
    ADR     x1, __bss_start__
    ADR     X2, __bss_end__
    MOV     x0, #0
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
    B   halt

// FUNC_PROLOGUE is a macro designed to simplify function prologue code
.macro FUNC_PROLOGUE name:req
.global \name
.type   \name, %function
\name:
    .cfi_startproc

    // Save x29 (frame pointer) and x30 (link register) onto the stack
    // x29 (frame pointer) stores the previous stack pointer address, which is needed to restore the stack when the function returns.
    // x30 (link register) stores the return address, which is the instruction to execute after the function returns.
    STP     x29, x30, [sp, #-16]!
    .cfi_def_cfa    sp, 16

    // Set x29 to the current value of the sp register.
    // x29 holds the top address of the current function’s stack frame.
    MOV     x29, sp
    .cfi_def_cfa_register x29
.endm

.macro FUNC_EPILOG
    // Restore x29 (frame pointer) and x30 (link register) from the stack
    LDP     x29, x30, [sp], #16
    .cfi_def_cfa    sp, 0

    .cfi_endproc
    RET
.endm


// Get current working core to x0
    .equ CORE_MASK,     0x03
FUNC_PROLOGUE get_current_core
    MRS     x0, mpidr_el1
    AND     x0, x0, #CORE_MASK
FUNC_EPILOG

// Set the stack pointer when starting OS
FUNC_PROLOGUE get_el1_current_core_sp_top
    // store the current working core to x0 register
    BL      get_current_core
    ADD     x0, x0, #1

    LDR     x1, =EL1_STRIDE
    MADD    x0, x0, x1, xzr

    LDR     x1, =__stack_EL1_bottom__
    ADD     x0, x0, x1

FUNC_EPILOG


// The start address of the vector table must be aligned to 0x800 (i.e., bits [0:10] = 0).
// Because bits 0–10 in VBAR_EL1 are reserved.
.section .vector, "ax"
.align 11

.macro STORE_GP_REG
    // Save all registers to the stack. (x0–x30, xzr(dummy))
    STP     x0,  x1,  [sp, #-16]!      // SP -= 16; [SP] = x0; [SP+8] = x1
    STP     x2,  x3,  [sp, #-16]!
    STP     x4,  x5,  [sp, #-16]!
    STP     x6,  x7,  [sp, #-16]!
    STP     x8,  x9,  [sp, #-16]!
    STP     x10, x11, [sp, #-16]!
    STP     x12, x13, [sp, #-16]!
    STP     x14, x15, [sp, #-16]!
    STP     x16, x17, [sp, #-16]!
    STP     x18, x19, [sp, #-16]!
    STP     x20, x21, [sp, #-16]!
    STP     x22, x23, [sp, #-16]!
    STP     x24, x25, [sp, #-16]!
    STP     x26, x27, [sp, #-16]!
    STP     x28, x29, [sp, #-16]!
    STP     x30, xzr, [sp, #-16]!     // x30=LR, xzr(dummy)
.endm

.macro RESTORE_GP_REG
    // Restore all saved registers from the stack. (Restoring is the reverse of saving.)
    LDP     x30, xzr, [sp], #16     // x30 = LR, xzr(dummy)
    LDP     x28, x29, [sp], #16     // x28 = [SP]; x29 = [SP+8];SP += 16; 
    LDP     x26, x27, [sp], #16
    LDP     x24, x25, [sp], #16
    LDP     x22, x23, [sp], #16
    LDP     x20, x21, [sp], #16
    LDP     x18, x19, [sp], #16
    LDP     x16, x17, [sp], #16
    LDP     x14, x15, [sp], #16
    LDP     x12, x13, [sp], #16
    LDP     x10, x11, [sp], #16
    LDP     x8,  x9,  [sp], #16
    LDP     x6,  x7,  [sp], #16
    LDP     x4,  x5,  [sp], #16
    LDP     x2,  x3,  [sp], #16
    LDP     x0,  x1,  [sp], #16
.endm

// The offset address for each vector must be set to 0x80 (1 << 7).
// This is based on “Table D1-7: Vector offsets from vector table base address” in the ARMv8-A Architecture Reference Manual.
vector_table:
    BL      halt
    .align 7
    BL      halt
    .align 7
    BL      halt
    .align 7
    BL      halt
    .align 7

    BL      halt
    .align 7
irq_start:
    STORE_GP_REG

    MOV     x10, sp

    BL      get_el1_current_core_sp_top

    LDR     x1, =EL1_KERNEL_STACK_SIZE
    SUB     x0, x0, x1

    LDR     x1, =EL1_GUARD_SIZE
    SUB     x0, x0, x1

    MOV     sp, x0


    STP     x10, xzr,    [sp, #-16]!

    BL      IRQ_Handler

irq_restore:
    LDP     x11, xzr,    [sp], #16
    MOV     sp, x11

    RESTORE_GP_REG

    ERET
    
    .align 7
    BL      halt
    .align 7
    BL      halt
    .align 7

// Set the kernel stack pointer to the top of the stack for the current core.
FUNC_PROLOGUE set_el1_current_core_IRQ_sp
    BL      get_el1_current_core_sp_top

    LDR     x1, =EL1_KERNEL_STACK_SIZE
    SUB     x0, x0, x1

    LDR     x1, =EL1_GUARD_SIZE
    SUB     x0, x0, x1

    MOV     sp, x0
FUNC_EPILOG