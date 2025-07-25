#ifndef __COMMON_GIC_H__
#define __COMMON_GIC_H__

#include <stdint.h>

// -------------------------------------------------------
// COMMON_GIC Distributor Interface
// -------------------------------------------------------

// COMMON_GIC Distribute Distributor Structures
typedef union __COMMON_GIC_GICD_CTRL_REG{
    uint32_t value;

    struct {
        uint32_t Enable     : 1;
		uint32_t 			: 31;
    };
} COMMON_GIC_GICD_CTRL_REG;

typedef union __COMMON_GIC_GICD_TYPER_REG{
    uint32_t value;

    struct {
        uint32_t ITLinesNumber  :  5;
        uint32_t CPUNumber      :  3;
		uint32_t      			:  2;
		uint32_t SecurityExtn	:  1;
		uint32_t LSPI			:  4;
		uint32_t				: 16;
    };
} COMMON_GIC_GICD_TYPER_REG;

typedef union __COMMON_GIC_GICD_IIDR_REG{
    uint32_t value;

    struct {
        uint32_t Implementer  	: 12;
        uint32_t Revision      	: 4;
		uint32_t Variant		: 4;
		uint32_t SecurityExtn	: 4;
		uint32_t LSPI			: 8;
    };
} COMMON_GIC_GICD_IIDR_REG;

typedef union __COMMON_GIC_GICD_IGROUPR_REG{
    uint32_t value;

} COMMON_GIC_GICD_IGROUPR_REG;

typedef union __COMMON_GIC_GICD_ISENABLER_REG{
    uint32_t value;

} COMMON_GIC_GICD_ISENABLER_REG;

typedef union __COMMON_GIC_GICD_ICENABLER_REG{
    uint32_t value;

} COMMON_GIC_GICD_ICENABLER_REG;

typedef union __COMMON_GIC_GICD_ISPENDR_REG{
    uint32_t value;

} COMMON_GIC_GICD_ISPENDR_REG;

typedef union __COMMON_GIC_GICD_ICPENDR_REG{
    uint32_t value;

} COMMON_GIC_GICD_ICPENDR_REG;

typedef union __COMMON_GIC_GICD_ISACTIVER_REG{
    uint32_t value;

} COMMON_GIC_GICD_ISACTIVER_REG;

typedef union __COMMON_GIC_GICD_ICACTIVER_REG{
    uint32_t value;

} COMMON_GIC_GICD_ICACTIVER_REG;

typedef union __COMMON_GIC_GICD_IPRIORITYR_REG{
    uint32_t value;

	uint8_t Priority[4];
} COMMON_GIC_GICD_IPRIORITYR_REG;

typedef union __COMMON_GIC_GICD_ITARGETSR_REG{
    uint32_t value;

	uint8_t CPU_Target[4];
} COMMON_GIC_GICD_ITARGETSR_REG;


// -------------------------------------------------------
// COMMON_GIC CPU Interface
// -------------------------------------------------------

typedef union __COMMON_GIC_GICC_CTLR_REG{
    uint32_t value;

	struct {
		uint32_t Enable 	: 1;
		uint32_t 			: 31;
	};

} COMMON_GIC_GICC_CTLR_REG;

typedef union __COMMON_GIC_GICC_PMR_REG{
    uint32_t value;

	struct {
		uint32_t Priority	:  8;
		uint32_t 			: 24;
	};

} COMMON_GIC_GICC_PMR_REG;

typedef union __COMMON_GIC_GICC_BPR_REG{
    uint32_t value;

	struct {
		uint32_t BinaryPoint	:  3;
		uint32_t 				: 29;
	};

} COMMON_GIC_GICC_BPR_REG;

typedef union __COMMON_GIC_GICC_IAR_REG{
    uint32_t value;

	struct {
		uint32_t InterruptID	: 10;
		uint32_t CPUID			:  3;
		uint32_t 				: 19;
	};

} COMMON_GIC_GICC_IAR_REG;

typedef union __COMMON_GIC_GICC_EOIR_REG{
    uint32_t value;

	struct {
		uint32_t EOINTID		: 10;
		uint32_t CPUID			:  3;
		uint32_t 				: 19;
	};

} COMMON_GIC_GICC_EOIR_REG;

typedef union __COMMON_GIC_GICC_IIDR_REG{
    uint32_t value;

	struct {
		uint32_t Implementer			: 12;
		uint32_t Revision				:  4;
		uint32_t ArchitectureVersion	:  4;
		uint32_t ProductID				: 12;
	};

} COMMON_GIC_GICC_IIDR_REG;


#endif // __COMMON_GIC_H__