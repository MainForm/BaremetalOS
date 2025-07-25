#include <stdint.h>
#include "HAL_GIC.h"
#include "interrupt.h"

__attribute__ ((interrupt ("IRQ")))
void IRQ_Handler(){
    uint32_t irqNum = HAL_GIC_GetAcknowledge();

    IRQ_CallHandlerCallback(irqNum);

    HAL_GIC_EndIRQ(irqNum);
}