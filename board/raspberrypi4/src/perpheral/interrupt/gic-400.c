#include "perpheral/gic-400.h"

GIC400* GIC400_Initialize(){
    GIC400* gic400 = (GIC400*)BCM2711_GIC_BASE;

    // // Set the filter of priority mask to the lowest priority to enable all interrupts
    gic400->CPU.GICC_PMR.Priority = 0xFF;

    // // Enable the distributor and the CPU interfaces
    gic400->Distributor.GICD_CTRL.Enable = 1;
    gic400->CPU.GICC_CTRL.Enable = 1;

    return gic400;
}

void GIC400_EnableInterrupt(GIC400* gic400, int irq_num){
    gic400->Distributor.GICD_IPRIORITYR[irq_num / 4].Priority[irq_num % 4] = 0x0F;
    gic400->Distributor.GICD_ITARGETSR[irq_num / 4].CPU_Target[irq_num % 4] = 0x01;
    gic400->Distributor.GICD_ISENABLER[irq_num / 32].value |= (0x01 << (irq_num % 32));
}

uint32_t GIC400_GetPendingBits(GIC400* gic400,int reg_num){
    return gic400->Distributor.GICD_ISPENDR[reg_num].value;
}

GIC400_GICD_IIDR_REG GIC400_GetDistID(GIC400* gic400){
    return gic400->Distributor.GICD_IIDR;
}

GIC400_GICC_IIDR_REG GIC400_GetCPUID(GIC400* gic400){
    return gic400->CPU.GICC_IIDR;
}

GIC400_GICC_IAR_REG GIC400_GetAcknowledge(GIC400* gic400) {
    return gic400->CPU.GICC_IAR;
}

void GIC400_EndIRQ(GIC400* gic400, uint32_t irqID) {
    gic400->CPU.GICC_EOIR.EOINTID = irqID;
}