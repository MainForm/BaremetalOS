#include "interrupt.h"

void IRQ_Enable(){
    __asm__ volatile(
        "MSR DAIFClr, #2    \n"
        "ISB                \n"
    );
}