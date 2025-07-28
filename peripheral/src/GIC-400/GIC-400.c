#include "GIC/GIC-400.h"

GIC400* GIC400_GetRegisters(uintptr_t BaseAddress){
    return (GIC400*)BaseAddress;
}

void GIC400_Initialize(GIC400* gic400){
    // // Set the filter of priority mask to the lowest priority to enable all interrupts
    gic400->CPU.GICC_PMR.Priority = 0xFF;

    // // Enable the distributor and the CPU interfaces
    gic400->Distributor.GICD_CTRL.Enable = 1;
    gic400->CPU.GICC_CTRL.Enable = 1;
}

void GIC400_EnableInterrupt(GIC400* gic400, uint32_t irq_num){
    gic400->Distributor.GICD_IPRIORITYR[irq_num / 4].Priority[irq_num % 4] = 0x00;
    gic400->Distributor.GICD_ITARGETSR[irq_num / 4].CPU_Target[irq_num % 4] = 0x01;
    gic400->Distributor.GICD_ISENABLER[irq_num / 32].value |= (0x01 << (irq_num % 32));
}

uint32_t GIC400_GetPendingBits(GIC400* gic400,uint32_t reg_num){
    return gic400->Distributor.GICD_ISPENDR[reg_num].value;
}

COMMON_GIC_GICD_IIDR_REG GIC400_GetDistID(GIC400* gic400){
    return gic400->Distributor.GICD_IIDR;
}

COMMON_GIC_GICC_IIDR_REG GIC400_GetCPUID(GIC400* gic400){
    return gic400->CPU.GICC_IIDR;
}

COMMON_GIC_GICC_IAR_REG GIC400_GetAcknowledge(GIC400* gic400) {
    return gic400->CPU.GICC_IAR;
}

void GIC400_EndIRQ(GIC400* gic400, uint32_t irqID) {
    gic400->CPU.GICC_EOIR.EOINTID = irqID;
}