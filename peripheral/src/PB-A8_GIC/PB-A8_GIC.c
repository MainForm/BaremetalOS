#include "GIC/PB-A8_GIC.h"

PB_A8_GIC* PB_A8_GIC_GetRegisters(uintptr_t BaseAddress){
    return (PB_A8_GIC*)BaseAddress;
}

void PB_A8_GIC_Initialize(PB_A8_GIC* PB_A8_GIC){
    // // Set the filter of priority mask to the lowest priority to enable all interrupts
    PB_A8_GIC->CPU.GICC_PMR.Priority = 0xF;

    // // Enable the distributor and the CPU interfaces
    PB_A8_GIC->Distributor.GICD_CTRL.Enable = 1;
    PB_A8_GIC->CPU.GICC_CTRL.Enable = 1;
}

void PB_A8_GIC_EnableInterrupt(PB_A8_GIC* PB_A8_GIC, uint32_t irq_num){
    PB_A8_GIC->Distributor.GICD_IPRIORITYR[irq_num / 4].Priority[irq_num % 4].value = 0x00;
    PB_A8_GIC->Distributor.GICD_ITARGETSR[irq_num / 4].CPU_Target[irq_num % 4].value = 0x01;
    PB_A8_GIC->Distributor.GICD_ISENABLER[irq_num / 32].value |= (0x01 << (irq_num % 32));
}

uint32_t PB_A8_GIC_GetPendingBits(PB_A8_GIC* PB_A8_GIC,uint32_t reg_num){
    return PB_A8_GIC->Distributor.GICD_ISPENDR[reg_num].value;
}

COMMON_GIC_GICC_IAR_REG PB_A8_GIC_GetAcknowledge(PB_A8_GIC* PB_A8_GIC) {
    return PB_A8_GIC->CPU.GICC_IAR;
}

void PB_A8_GIC_EndIRQ(PB_A8_GIC* PB_A8_GIC, uint32_t irqID) {
    PB_A8_GIC->CPU.GICC_EOIR.EOINTID = irqID;
}