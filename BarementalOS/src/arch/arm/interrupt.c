#include "interrupt.h"

void IRQ_Enable(){
    __asm__ volatile (
        "PUSH   {r0, r1}        \n"
        "MRS    r0, cpsr        \n"
        "BIC    r1, r0, #0x81   \n"
        "MSR    cpsr, r1        \n"
        "POP    {r0, r1}        \n"
    );
}