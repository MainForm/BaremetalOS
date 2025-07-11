.section ".text.boot"

.global _start

_start:
    MOV     sp, #0x80000    // Initialize the sp(Stack Pointer) register to 0x80000
    BL      main            // Branch to the main function that is written in main.c

halt:
    wfe
    B halt
