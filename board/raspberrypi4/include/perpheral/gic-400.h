#ifndef __GIC400_H__
#define __GIC400_H__

#include <stdint.h>

#include "bcm2711_peripheral.h"

#define GIC400_DIST_BASE                (BCM2711_GIC_BASE + 0x1000)

#define GIC400_DIST_CTLR                ((volatile void *)(GIC400_DIST_BASE))
#define GIC400_DIST_TYPER               ((volatile void *)(GIC400_DIST_BASE + 0x004))
#define GIC400_DIST_IIDR                ((volatile void *)(GIC400_DIST_BASE + 0x008))
#define GIC400_DIST_ISENABLER0          ((volatile void *)(GIC400_DIST_BASE + 0x100))
#define GIC400_DIST_ISENABLER1          ((volatile void *)(GIC400_DIST_BASE + 0x104))
#define GIC400_DIST_ISPENDR0            ((volatile void *)(GIC400_DIST_BASE + 0x200))
#define GIC400_DIST_IPRIORITYR0         ((volatile void *)(GIC400_DIST_BASE + 0x400))
#define GIC400_DIST_ITARGETSR0          ((volatile void *)(GIC400_DIST_BASE + 0x800))

#define GIC400_CPU_BASE                 (BCM2711_GIC_BASE + 0x2000)

#define GIC400_CPU_CTLR                 ((volatile void *)(GIC400_CPU_BASE))
#define GIC400_CPU_PMR                  ((volatile void *)(GIC400_CPU_BASE + 0x0004))
#define GIC400_CPU_IAR                  ((volatile void *)(GIC400_CPU_BASE + 0x000C))
#define GIC400_CPU_EOIR                 ((volatile void *)(GIC400_CPU_BASE + 0x0010))

#define GIC400_IRQ_ACK                  (0x3FF)
#define GIC400_EOIINTID                 (0x3FF)

void GIC400_Initialize();
void GIC400_EnableInterrupt(int irq_num);
uint32_t GIC400_GetPendingBits(int reg_num);
uint32_t GIC400_GetDistID();

uint32_t GIC400_GetAcknowledge(void);
void GIC400_EndIRQ(uint32_t irqID);

#endif