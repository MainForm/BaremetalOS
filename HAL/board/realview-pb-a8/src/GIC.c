#include "HAL_GIC.h"

#include "RealViewPB_a8_peripheral.h"
#include "PB-A8_GIC.h"

#include "HAL_UART.h"
#include "stdlib.h"


void HAL_GIC_Initialize(){
    PB_A8_GIC* gic = PB_A8_GIC_GetRegisters(REALVIEW_PB_A8_GIC_BASE(0));

    PB_A8_GIC_Initialize(gic);
}

void HAL_GIC_EnableInterrupt(uint32_t irq_num){
    PB_A8_GIC* gic = PB_A8_GIC_GetRegisters(REALVIEW_PB_A8_GIC_BASE(0));

    PB_A8_GIC_EnableInterrupt(gic, irq_num);

    char test[10];
    itoa(gic->Distributor.GICD_ISENABLER[1].value,test,16);
    HAL_UART_SendString(0,test);
    HAL_UART_SendWord(0,'\n');
}

uint32_t HAL_GIC_GetAcknowledge(){
    PB_A8_GIC* gic = PB_A8_GIC_GetRegisters(REALVIEW_PB_A8_GIC_BASE(0));

    return PB_A8_GIC_GetAcknowledge(gic).InterruptID;
}

void HAL_GIC_EndIRQ(uint32_t irqID){
    PB_A8_GIC* gic = PB_A8_GIC_GetRegisters(REALVIEW_PB_A8_GIC_BASE(0));

    PB_A8_GIC_EndIRQ(gic,irqID);
}
