#include <stdint.h>
#include "GIC-400.h"
#include "interrupt.h"

void IRQ_Handler(){
    GIC400* gic400 = (GIC400 *)BCM2711_GIC_BASE;
    GIC400_GICC_IAR_REG cpuIIDR = GIC400_GetAcknowledge(gic400);

    IRQ_CallHandlerCallback(cpuIIDR.InterruptID - IRQ_VC_IRQ_BASE);

    GIC400_EndIRQ(gic400, cpuIIDR.InterruptID);
    return;
}