#ifndef __BCM2711_SYSTEM_TIMER_H__
#define __BCM2711_SYSTEM_TIMER_H__

#include <stdint.h>
#include <stdbool.h>

// System Timer Control / Status Register
typedef union __BCM2711_SystemTimer_CS_REG{
    uint32_t value;

    struct {
        uint32_t M0     :  1;
        uint32_t M1     :  1;
        uint32_t M2     :  1;
        uint32_t M3     :  1;
        uint32_t        : 28;
    };
} BCM2711_SystemTimer_CS_REG;

// System Timer Counter LOwer bits
typedef union __BCM2711_SystemTimer_CLO_REG{
    uint32_t value;
} BCM2711_SystemTimer_CLO_REG;

// System Timer Counter HIgh bits
typedef union __BCM2711_SystemTimer_CHI_REG{
    uint32_t value;
} BCM2711_SystemTimer_CHI_REG;

// System Timer Compare Register
typedef union __BCM2711_SystemTimer_Cn_REG{
    uint32_t value;
} BCM2711_SystemTimer_Cn_REG;

typedef volatile struct __BCM2711_SystemTimer{
    BCM2711_SystemTimer_CS_REG     CS;
    BCM2711_SystemTimer_CLO_REG    CLO;
    BCM2711_SystemTimer_CHI_REG    CHI;
    BCM2711_SystemTimer_Cn_REG     C[4];

} BCM2711_SystemTimer;

uint32_t BCM2711_SystemTimer_GetLowCounter(BCM2711_SystemTimer* SystemTimer);
uint64_t BCM2711_SystemTimer_GetCounter(BCM2711_SystemTimer* SystemTimer);

void BCM2711_SystemTimer_SetTick(BCM2711_SystemTimer* SystemTimer,uint32_t timerID, uint32_t Tick);
void BCM2711_SystemTimer_SetNextTick(BCM2711_SystemTimer* SystemTimer,uint32_t timerID, uint32_t nextTick);
void BCM2711_SystemTimer_ClearInterrupt(BCM2711_SystemTimer* SystemTimer,uint32_t timerID);

#endif