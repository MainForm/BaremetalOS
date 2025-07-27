#include <stdint.h>

#include "interrupt.h"
#include "HAL_GIC.h"

void IRQ_Enable(){
    __asm__ volatile(
        "MSR DAIFClr, #2    \n"
        "ISB                \n"
    );
}

void IRQ_ARM64_Handler(){
    IRQ_HandlerCallback();
}