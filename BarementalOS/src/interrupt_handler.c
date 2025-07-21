#include <stdint.h>
#include "HAL_GIC.h"
#include "interrupt.h"

#include "HAL_GPIO.h"

void IRQ_Handler(){
    uint32_t irqNum = HAL_GIC_GetAcknowledge();

    HAL_GPIO_SetOutput(21, LOW);
    IRQ_CallHandlerCallback(irqNum);

    HAL_GIC_EndIRQ(irqNum);
    return;
}