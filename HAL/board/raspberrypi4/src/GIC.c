#include "HAL_GIC.h"

#include "BCM2711_peripheral.h"
#include "GIC-400.h"


void HAL_GIC_Initialize(uint32_t gic_num){
    GIC400* gic400 = GIC400_GetRegisters(BCM2711_GIC_BASE);

    GIC400_Initialize(gic400);
}

void HAL_GIC_EnableInterrupt(uint32_t gic_num,uint32_t irq_num){
    GIC400* gic400 = GIC400_GetRegisters(BCM2711_GIC_BASE);

    GIC400_EnableInterrupt(gic400, irq_num);
}

uint32_t HAL_GIC_GetAcknowledge(uint32_t gic_num){
    GIC400* gic400 = GIC400_GetRegisters(BCM2711_GIC_BASE);

    return GIC400_GetAcknowledge(gic400).InterruptID;
}

void HAL_GIC_EndIRQ(uint32_t gic_num,uint32_t irqID){
    GIC400* gic400 = GIC400_GetRegisters(BCM2711_GIC_BASE);

    GIC400_EndIRQ(gic400,irqID);
}