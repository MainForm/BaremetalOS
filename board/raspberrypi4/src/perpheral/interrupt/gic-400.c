#include "bcm2711_peripheral.h"
#include "perpheral/gic-400.h"

#include "memory.h"

void GIC400_Initialize(){
    // Set the filter of priority mask to the lowest priority to enable all interrupts
    REG_32(GIC400_CPU_PMR) = 0xFF;

    // Enable the distributor and the CPU interfaces
    REG_32(GIC400_DIST_CTLR) = 0x01;
    REG_32(GIC400_CPU_CTLR) = 0x01;
}

void GIC400_EnableInterrupt(int irq_num){
    volatile uint32_t * ISENABLER_base = GIC400_DIST_ISENABLER0;
    volatile uint32_t * ITARGETSR_base = GIC400_DIST_ITARGETSR0;
    volatile uint32_t * IPRIORITYR_base = GIC400_DIST_IPRIORITYR0;

    REG_32(IPRIORITYR_base + (irq_num / 4)) |= (0x0F << ((irq_num % 4) * 8));
    REG_32(ITARGETSR_base + (irq_num / 4)) |= (0x01 << ((irq_num % 4) * 8));
    REG_32(ISENABLER_base + (irq_num / 32)) |= (0x01 << (irq_num % 32));
}

uint32_t GIC400_GetPendingBits(int reg_num){
    volatile uint32_t * ISPENDR_base = GIC400_DIST_ISPENDR0;

    return REG_32(ISPENDR_base + reg_num);
}

uint32_t GIC400_GetDistID(){
    return REG_32(GIC400_DIST_IIDR);
}

uint32_t GIC400_GetAcknowledge(void) {
    return REG_32(GIC400_CPU_IAR) & GIC400_IRQ_ACK;
}

void GIC400_EndIRQ(uint32_t irqID) {
    REG_32(GIC400_CPU_EOIR) = irqID & GIC400_EOIINTID;
}