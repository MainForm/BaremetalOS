#include <stdint.h>

#include "interrupt.h"
#include "HAL_GIC.h"

void IRQ_Enable(){
    __asm__ volatile(
        "MSR DAIFClr, #2    \n"
        "ISB                \n"
    );
}

void IRQ_Handler(){
    uint32_t irqNum = HAL_GIC_GetAcknowledge();

    IRQ_CallHandlerCallback(irqNum);

    HAL_GIC_EndIRQ(irqNum);
}