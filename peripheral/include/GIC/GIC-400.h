#ifndef __GIC400_H__
#define __GIC400_H__

#include "GIC/common_GIC.h"

// GIC-400 Distributor Structure

typedef struct __GIC400_Distributor{
	COMMON_GIC_GICD_CTRL_REG 		GICD_CTRL;							// 0x0000
	COMMON_GIC_GICD_TYPER_REG		GICD_TYPER;							// 0x0004
	COMMON_GIC_GICD_IIDR_REG		GICD_IIDR;							// 0x0008

	uint32_t __pading0[(0x080 - 0x00C) / 4];						// 0x000C ~ 0x007C

	COMMON_GIC_GICD_IGROUPR_REG	 	GICD_IGROUPR[(0x0C0 - 0x080) / 4];	// 0x0080 ~ 0x00BC

	uint32_t __pading1[(0x100 - 0x0C0) / 4];						// 0x00C0 ~ 0x00FC 

	COMMON_GIC_GICD_ISENABLER_REG	GICD_ISENABLER[(0x140 - 0x100) / 4];// 0x0100 ~ 0x013C

	uint32_t __pading2[(0x180 - 0x140) / 4];						// 0x0140 ~ 0x017C
	
	COMMON_GIC_GICD_ICENABLER_REG	GICD_ICENABLER[(0x1C0 - 0x180) / 4];// 0x0180 ~ 0x01BC

	uint32_t __pading3[(0x200 - 0x1C0) / 4];						// 0x01C0 ~ 0x01FC

	COMMON_GIC_GICD_ISPENDR_REG		GICD_ISPENDR[(0x240 - 0x200) / 4];	// 0x0200 ~ 0x023C

	uint32_t __pading4[(0x280 - 0x240) / 4];						// 0x0240 ~ 0x027C

	COMMON_GIC_GICD_ICPENDR_REG		GICD_ICPENDR[(0x2C0 - 0x280) / 4];	// 0x0280 ~ 0x02BC

	uint32_t __pading5[(0x300 - 0x2C0) / 4];						// 0x02C0 ~ 0x02FC

	COMMON_GIC_GICD_ISACTIVER_REG	GICD_ISACTIVER[(0x340 - 0x300) / 4];// 0x0300 ~ 0x033C

	uint32_t __pading6[(0x380 - 0x340) / 4];						// 0x0340 ~ 0x037C

	COMMON_GIC_GICD_ICACTIVER_REG	GICD_ICACTIVER[(0x3C0 - 0x380) / 4];// 0x0380 ~ 0x03BC

	uint32_t __pading7[(0x400 - 0x3C0) / 4];						// 0x03C0 ~ 0x03FC

	COMMON_GIC_GICD_IPRIORITYR_REG	GICD_IPRIORITYR[(0x600 - 0x400) / 4];// 0x0400 ~ 0x05FC

	uint32_t __pading8[(0x800 - 0x600) / 4];						// 0x0600 ~ 0x07FC

	COMMON_GIC_GICD_ITARGETSR_REG 	GICD_ITARGETSR[(0xA00 - 0x800) / 4];// 0x0800 ~ 0x09FC

	// We implemented the minimum register setup required to operate interrupts.
	uint32_t __pading9[(0x1000 - 0xA00) / 4];						// 0x0A00 ~ 0x0FFC

} GIC400_Distributor;


// GIC-400 CPU Interface Structure

typedef struct __GIC400_CPU{
	COMMON_GIC_GICC_CTLR_REG	GICC_CTRL; 			// 0x0000
	COMMON_GIC_GICC_PMR_REG 	GICC_PMR;			// 0x0004
	COMMON_GIC_GICC_BPR_REG		GICC_BPR;			// 0x0008
	COMMON_GIC_GICC_IAR_REG		GICC_IAR;			// 0x000C
	COMMON_GIC_GICC_EOIR_REG	GICC_EOIR;			// 0x0010

	uint32_t __pading0[(0x00FC - 0x0014) / 4];	// 0x0014 ~ 0x00F8

	COMMON_GIC_GICC_IIDR_REG	GICC_IIDR;			// 0x00FC

	uint32_t __pading1[(0x1000 - 0x0100) / 4];	// 0x0100 ~ 0x0FFC

	// We implemented the minimum register setup required to operate interrupts.
} GIC400_CPU;


// GIC-400 Structure

typedef volatile struct __GIC400{
	uint32_t 			Reserved[0x1000 / 4];	// 0x0000

	GIC400_Distributor 	Distributor;			// 0x1000

	GIC400_CPU			CPU;					// 0x2000

	// We implemented the minimum register setup required to operate interrupts.
} GIC400;

GIC400* GIC400_GetRegisters(uintptr_t BaseAddress);
void GIC400_Initialize(GIC400* gic400);
void GIC400_EnableInterrupt(GIC400* gic400,uint32_t irq_num);
uint32_t GIC400_GetPendingBits(GIC400* gic400,uint32_t reg_num);
COMMON_GIC_GICD_IIDR_REG GIC400_GetDistID(GIC400* gic400);
COMMON_GIC_GICC_IIDR_REG GIC400_GetCPUID(GIC400* gic400);

COMMON_GIC_GICC_IAR_REG GIC400_GetAcknowledge(GIC400* gic400);
void GIC400_EndIRQ(GIC400* gic400,uint32_t irqID);

#endif