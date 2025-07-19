#ifndef __GIC400_H__
#define __GIC400_H__

#include <stdint.h>

#define BCM2711_GIC_BASE                (0xFF840000)

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

// GIC-400 Distribute Distributor Structures

typedef union __GIC400_GICD_CTRL_REG{
    uint32_t value;

    struct {
        uint32_t Enable     : 1;
    };
} GIC400_GICD_CTRL_REG;

typedef union __GIC400_GICD_TYPER_REG{
    uint32_t value;

    struct {
        uint32_t ITLinesNumber  : 5;
        uint32_t CPUNumber      : 3;
		uint32_t      			: 2;
		uint32_t SecurityExtn	: 1;
		uint32_t LSPI			: 4;
    };
} GIC400_GICD_TYPER_REG;

typedef union __GIC400_GICD_IIDR_REG{
    uint32_t value;

    struct {
        uint32_t Implementer  	: 12;
        uint32_t Revision      	: 4;
		uint32_t Variant		: 4;
		uint32_t SecurityExtn	: 4;
		uint32_t LSPI			: 8;
    };
} GIC400_GICD_IIDR_REG;

typedef union __GIC400_GICD_IGROUPR_REG{
    uint32_t value;

} GIC400_GICD_IGROUPR_REG;

typedef union __GIC400_GICD_ISENABLER_REG{
    uint32_t value;

} GIC400_GICD_ISENABLER_REG;

typedef union __GIC400_GICD_ICENABLER_REG{
    uint32_t value;

} GIC400_GICD_ICENABLER_REG;

typedef union __GIC400_GICD_ISPENDR_REG{
    uint32_t value;

} GIC400_GICD_ISPENDR_REG;

typedef union __GIC400_GICD_ICPENDR_REG{
    uint32_t value;

} GIC400_GICD_ICPENDR_REG;

typedef union __GIC400_GICD_ISACTIVER_REG{
    uint32_t value;

} GIC400_GICD_ISACTIVER_REG;

typedef union __GIC400_GICD_ICACTIVER_REG{
    uint32_t value;

} GIC400_GICD_ICACTIVER_REG;

typedef union __GIC400_GICD_IPRIORITYR_REG{
    uint32_t value;

	uint8_t Priority[4];
} GIC400_GICD_IPRIORITYR_REG;

typedef union __GIC400_GICD_ITARGETSR_REG{
    uint32_t value;

	uint8_t CPU_Target[4];
} GIC400_GICD_ITARGETSR_REG;

// GIC-400 Distributor Structure

typedef struct __GIC400_Distributor{
	GIC400_GICD_CTRL_REG 		GICD_CTRL;							// 0x0000
	GIC400_GICD_TYPER_REG		GICD_TYPER;							// 0x0004
	GIC400_GICD_IIDR_REG		GICD_IIDR;							// 0x0008

	uint32_t __pading0[(0x080 - 0x00C) / 4];						// 0x000C ~ 0x007C

	GIC400_GICD_IGROUPR_REG	 	GICD_IGROUPR[(0x0C0 - 0x080) / 4];	// 0x0080 ~ 0x00BC

	uint32_t __pading1[(0x100 - 0x0C0) / 4];						// 0x00C0 ~ 0x00FC 

	GIC400_GICD_ISENABLER_REG	GICD_ISENABLER[(0x140 - 0x100) / 4];// 0x0100 ~ 0x013C

	uint32_t __pading2[(0x180 - 0x140) / 4];						// 0x0140 ~ 0x017C
	
	GIC400_GICD_ICENABLER_REG	GICD_ICENABLER[(0x1C0 - 0x180) / 4];// 0x0180 ~ 0x01BC

	uint32_t __pading3[(0x200 - 0x1C0) / 4];						// 0x01C0 ~ 0x01FC

	GIC400_GICD_ISPENDR_REG		GICD_ISPENDR[(0x240 - 0x200) / 4];	// 0x0200 ~ 0x023C

	uint32_t __pading4[(0x280 - 0x240) / 4];						// 0x0240 ~ 0x027C

	GIC400_GICD_ICPENDR_REG		GICD_ICPENDR[(0x2C0 - 0x280) / 4];	// 0x0280 ~ 0x02BC

	uint32_t __pading5[(0x300 - 0x2C0) / 4];						// 0x02C0 ~ 0x02FC

	GIC400_GICD_ISACTIVER_REG	GICD_ISACTIVER[(0x340 - 0x300) / 4];// 0x0300 ~ 0x033C

	uint32_t __pading6[(0x380 - 0x340) / 4];						// 0x0340 ~ 0x037C

	GIC400_GICD_ICACTIVER_REG	GICD_ICACTIVER[(0x3C0 - 0x380) / 4];// 0x0380 ~ 0x03BC

	uint32_t __pading7[(0x400 - 0x3C0) / 4];						// 0x03C0 ~ 0x03FC

	GIC400_GICD_IPRIORITYR_REG	GICD_IPRIORITYR[(0x600 - 0x400) / 4];// 0x0400 ~ 0x05FC

	uint32_t __pading8[(0x800 - 0x600) / 4];						// 0x0600 ~ 0x07FC

	GIC400_GICD_ITARGETSR_REG 	GICD_ITARGETSR[(0xA00 - 0x800) / 4];// 0x0800 ~ 0x09FC

	// We implemented the minimum register setup required to operate interrupts.
	uint32_t __pading9[(0x1000 - 0xA00) / 4];						// 0x0A00 ~ 0x0FFC

} GIC400_Distributor;

// GIC-400 CPU Interface Register Structure

typedef union __GIC400_GICC_CTLR_REG{
    uint32_t value;

	struct {
		uint32_t Enable : 1;
	};

} GIC400_GICC_CTLR_REG;

typedef union __GIC400_GICC_PMR_REG{
    uint32_t value;

	struct {
		uint32_t Priority	: 8;
	};

} GIC400_GICC_PMR_REG;

typedef union __GIC400_GICC_IIDR_REG{
    uint32_t value;

	struct {
		uint32_t Implementer			: 12;
		uint32_t Revision				:  4;
		uint32_t ArchitectureVersion	:  4;
		uint32_t ProductID				: 12;
	};

} GIC400_GICC_IIDR_REG;

// GIC-400 CPU Interface Structure

typedef struct __GIC400_CPU{
	GIC400_GICC_CTLR_REG	GICC_CTRL; 			// 0x0000

	GIC400_GICC_PMR_REG 	GICC_PMR;			// 0x0004

	uint32_t __pading0[(0x00FC - 0x0008) / 4];	// 0x0008 ~ 0x00F8

	GIC400_GICC_IIDR_REG	GICC_IIDR;			// 0x00FC

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


GIC400* GIC400_Initialize();
void GIC400_EnableInterrupt(int irq_num);
uint32_t GIC400_GetPendingBits(int reg_num);
uint32_t GIC400_GetDistID();

uint32_t GIC400_GetAcknowledge(void);
void GIC400_EndIRQ(uint32_t irqID);

#endif