#include <stdint.h>

#include "interrupt.h"
#include "HAL_GIC.h"

inline void IRQ_Enable(void)
{
    __asm__ volatile ("cpsie i" : : : "memory");
}

__attribute__ ((interrupt ("IRQ")))
void IRQ_ARM_Handler(){
    IRQ_HandlerCallback();
}