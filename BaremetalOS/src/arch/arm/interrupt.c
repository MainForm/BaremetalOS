#include <stdint.h>

#include "interrupt.h"
#include "HAL_GIC.h"

inline void IRQ_Enable(void)
{
    __asm__ volatile ("cpsie i" : : : "memory");
}

__attribute__ ((interrupt ("IRQ")))
void IRQ_Handler(){
    uint32_t irqNum = HAL_GIC_GetAcknowledge();

    IRQ_CallHandlerCallback(irqNum);

    HAL_GIC_EndIRQ(irqNum);
}