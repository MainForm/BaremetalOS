#ifndef __BCM2711_INTERRUPT_H__
#define __BCM2711_INTERRUPT_H__

#include <stdbool.h>
#include "perpheral/gic-400.h"

// This is based on “6.3. GIC-400 interrupt controller” in the bcm2711-peripherals Manual.
// You can check the base number of the VideoCore peripheral IRQs.
#define IRQ_VC_IRQ_BASE     (96)
#define IRQ_UART_NUM        (57)

typedef void (*IRQ_Handler_Callback)(void);

void IRQ_Initialize();
void IRQ_Enable();
bool IRQ_IsEnableInterrupt(int irq_num);
bool IRQ_AttachInterrupt(int irq_num, IRQ_Handler_Callback callback);
void IRQ_CallHandlerCallback(int irq_num);

#endif