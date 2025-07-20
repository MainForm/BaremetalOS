#include "interrupt.h"
#include "GIC-400.h"

#include "PL011.h"

#include <stddef.h>

static IRQ_Handler_Callback IRQ_Handler_Callbacks[64];
static void* IRQ_Handler_data[64];

void IRQ_Enable(){
    __asm__ volatile(
        "MSR DAIFClr, #2    \n"
        "ISB                \n"
    );
}

bool IRQ_AttachInterrupt(GIC400* gic400, int irq_num, IRQ_Handler_Callback callback,void * data){

    if(IRQ_IsEnableInterrupt(irq_num) == false){
        GIC400_EnableInterrupt(gic400, IRQ_VC_IRQ_BASE + irq_num);
    }

    IRQ_Handler_Callbacks[irq_num] = callback;
    IRQ_Handler_data[irq_num] = data;
    return true;
}

bool IRQ_IsEnableInterrupt(int irq_num){
    return IRQ_Handler_Callbacks[irq_num] != NULL ? true : false;
}

void IRQ_CallHandlerCallback(int irq_num){
    if(IRQ_Handler_Callbacks[irq_num] == NULL){
        return;
    }

    IRQ_Handler_Callbacks[irq_num](IRQ_Handler_data[irq_num]);
}