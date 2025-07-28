#ifndef __PB_A8_GIC_H__
#define __PB_A8_GIC_H__

#include "GIC/common_GIC.h"

// -------------------------------------------------------
// PB_A8_GIC CPU Interface
// -------------------------------------------------------

typedef union __PB_A8_GIC_GICC_PMR_REG{
    uint32_t value;

	struct {
		uint32_t 			:  4;
		uint32_t Priority	:  4;
		uint32_t 			: 24;
	};

} PB_A8_GIC_GICC_PMR_REG;


// Running Interrupt Register
typedef union __PB_A8_GIC_GICC_RIR_REG{
    uint32_t value;

	struct {
		uint32_t 				:  	4;
		uint32_t Priority		:  	4;
		uint32_t 				:  24;
	};

} PB_A8_GIC_GICC_RIR_REG;

// Highest Pending Interrupt
typedef union __PB_A8_GIC_GICC_HPI_REG{
    uint32_t value;

	struct {
		uint32_t InterruptID	: 10;
		uint32_t CPUID			:  3;
		uint32_t 				: 19;
	};

} PB_A8_GIC_GICC_HPI_REG;

// PB_A8_GIC CPU Interface Structure

typedef struct __PB_A8_GIC_CPU{
	COMMON_GIC_GICC_CTLR_REG	GICC_CTRL; 			// 0x0000
	PB_A8_GIC_GICC_PMR_REG 		GICC_PMR;			// 0x0004
	COMMON_GIC_GICC_BPR_REG		GICC_BPR;			// 0x0008
	COMMON_GIC_GICC_IAR_REG		GICC_IAR;			// 0x000C
	COMMON_GIC_GICC_EOIR_REG	GICC_EOIR;			// 0x0010
	PB_A8_GIC_GICC_RIR_REG		GICC_RIR;			// 0x0014
	PB_A8_GIC_GICC_HPI_REG		GICC_HPI;			// 0x0018

	uint32_t __pading0[(0x1000 - 0x001C) / 4];		// 0x001C ~ 0x0FFC
} PB_A8_GIC_CPU;


// -------------------------------------------------------
// PB_A8_GIC Distributor Interface
// -------------------------------------------------------

typedef union __PB_A8_GIC_GICD_TYPER_REG{
    uint32_t value;

    struct {
        uint32_t ITLinesNumber  :  5;
        uint32_t CPUNumber      :  3;
		uint32_t      			: 24;
    };
} PB_A8_GIC_GICD_TYPER_REG;

typedef union __PB_A8_GIC_GICD_IPRIORITYR_REG{
    uint32_t value;
	
	struct {
		uint8_t 		: 4;
		uint8_t value 	: 4;
	} Priority[4];
} PB_A8_GIC_GICD_IPRIORITYR_REG;

typedef union __PB_A8_GIC_GICD_ITARGETSR_REG{
    uint32_t value;

	struct {
		uint8_t value	: 4;
		uint8_t  		: 4;
	} CPU_Target[4];
} PB_A8_GIC_GICD_ITARGETSR_REG;

// PB_A8_GIC Distributor Structure

typedef struct __PB_A8_GIC_Distributor{
	COMMON_GIC_GICD_CTRL_REG 		GICD_CTRL;								// 0x0000
	PB_A8_GIC_GICD_TYPER_REG		GICD_TYPER;								// 0x0004

	uint32_t __pading0[(0x0100 - 0x0008) / 4];								// 0x0008 ~ 0x00FC

	COMMON_GIC_GICD_ISENABLER_REG	GICD_ISENABLER[(0x010C - 0x0100) / 4];	// 0x0100 ~ 0x0108

	uint32_t __pading2[(0x0180 - 0x010C) / 4];								// 0x010C ~ 0x017C
	
	COMMON_GIC_GICD_ICENABLER_REG	GICD_ICENABLER[(0x018C - 0x0180) / 4];	// 0x0180 ~ 0x0188

	uint32_t __pading3[(0x0200 - 0x018C) / 4];								// 0x018C ~ 0x01FC

	COMMON_GIC_GICD_ISPENDR_REG		GICD_ISPENDR[(0x020C - 0x0200) / 4];	// 0x0200 ~ 0x0208

	uint32_t __pading4[(0x0280 - 0x020C) / 4];								// 0x020C ~ 0x027C

	COMMON_GIC_GICD_ICPENDR_REG		GICD_ICPENDR[(0x028C - 0x0280) / 4];	// 0x0280 ~ 0x0288

	uint32_t __pading5[(0x0300 - 0x028C) / 4];								// 0x028C ~ 0x02FC

	COMMON_GIC_GICD_ISACTIVER_REG	GICD_ISACTIVER[(0x030C - 0x0300) / 4];	// 0x0300 ~ 0x0308

	uint32_t __pading6[(0x0400 - 0x030C) / 4];								// 0x030C ~ 0x03FC

	PB_A8_GIC_GICD_IPRIORITYR_REG	GICD_IPRIORITYR[(0x0460 - 0x0400) / 4];	// 0x0400 ~ 0x045C

	uint32_t __pading7[(0x800 - 0x0460) / 4];								// 0x0460 ~ 0x07FC

	PB_A8_GIC_GICD_ITARGETSR_REG 	GICD_ITARGETSR[(0x0860 - 0x800) / 4];	// 0x0800 ~ 0x085C

} PB_A8_GIC_Distributor;


// PB_A8_GIC Structure

typedef volatile struct __PB_A8_GIC{
	PB_A8_GIC_CPU			CPU;					// 0x0000

	PB_A8_GIC_Distributor 	Distributor;			// 0x1000

	// We implemented the minimum register setup required to operate interrupts.
} PB_A8_GIC;

PB_A8_GIC* PB_A8_GIC_GetRegisters(uintptr_t BaseAddress);
void PB_A8_GIC_Initialize(PB_A8_GIC* PB_A8_GIC);
void PB_A8_GIC_EnableInterrupt(PB_A8_GIC* PB_A8_GIC,uint32_t irq_num);
uint32_t PB_A8_GIC_GetPendingBits(PB_A8_GIC* PB_A8_GIC,uint32_t reg_num);

COMMON_GIC_GICC_IAR_REG PB_A8_GIC_GetAcknowledge(PB_A8_GIC* PB_A8_GIC);
void PB_A8_GIC_EndIRQ(PB_A8_GIC* PB_A8_GIC,uint32_t irqID);

#endif