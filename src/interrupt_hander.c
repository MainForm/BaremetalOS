#include <stdint.h>
#include "perpheral/interrupt.h"

void IRQ_Handler(){
    uint32_t irqID = GIC400_GetAcknowledge();

    IRQ_CallHandlerCallback(irqID - IRQ_VC_IRQ_BASE);

    GIC400_EndIRQ(irqID);
    return;
}