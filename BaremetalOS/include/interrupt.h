#ifndef __BCM2711_INTERRUPT_H__
#define __BCM2711_INTERRUPT_H__

#include <stdbool.h>

// The maximum number of IRQs should be a multiple of 32.
// The number of IRQs supported by the GIC-400 must be a multiple of 32.
// The BCM2711 supports 216 IRQs.
// So, I decided to set the maximum number of IRQs to 256 because 256 is a multiple of 32 and larger than 216.
#define IRQ_MAXIMUM_COUNT       (32 * 8)    // 256

typedef void (*IRQ_Handler_Callback)();

void IRQ_Enable();
bool IRQ_IsEnableInterrupt(int irq_num);
void IRQ_AttachInterrupt(int gic_num, int irq_num, IRQ_Handler_Callback callback);
void IRQ_CallHandlerCallback(int irq_num);

#endif