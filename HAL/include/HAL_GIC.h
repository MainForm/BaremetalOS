#ifndef __HAL_GIC__
#define __HAL_GIC__

#include <stdint.h>

__attribute__((weak))
void HAL_GIC_Initialize();

__attribute__((weak))
void HAL_GIC_EnableInterrupt(uint32_t irq_num);

__attribute__((weak))
uint32_t HAL_GIC_GetAcknowledge();

__attribute__((weak))
void HAL_GIC_EndIRQ(uint32_t irqID);

#endif