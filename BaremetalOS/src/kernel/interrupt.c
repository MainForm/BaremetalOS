#include "interrupt.h"
#include "HAL_GIC.h"

#include <stddef.h>

static IRQ_Handler_Callback IRQ_Handler_Callbacks[IRQ_MAXIMUM_COUNT];

void IRQ_AttachInterrupt(int gic_num,int irq_num, IRQ_Handler_Callback callback){

    if(IRQ_IsEnableInterrupt(irq_num) == false){
       HAL_GIC_EnableInterrupt(gic_num, irq_num);
    }

    IRQ_Handler_Callbacks[irq_num] = callback;
}

bool IRQ_IsEnableInterrupt(int irq_num){
    return IRQ_Handler_Callbacks[irq_num] != NULL ? true : false;
}

void IRQ_HandlerCallback(){
    uint32_t gicCount = HAL_GIC_GetCountGIC();

    for(uint32_t gicNum = 0;gicNum < gicCount;++gicNum){
        uint32_t irqID = HAL_GIC_GetAcknowledge(gicNum);

        // If the IRQ ID is equal to 1023, it is reserved for spurious IRQs.
        // IRQ ID 1023 indicates that there are no pending IRQs with sufficient priority to be activated.
        if(irqID == 1023){
            continue;
        }

        IRQ_CallHandlerCallback(irqID);

        HAL_GIC_EndIRQ(gicNum, irqID);
        break;
    }
}

void IRQ_CallHandlerCallback(int irq_num){
    if(IRQ_MAXIMUM_COUNT <= irq_num){
        return;
    }

    if(IRQ_Handler_Callbacks[irq_num] == NULL){
        return;
    }

    IRQ_Handler_Callbacks[irq_num]();
}