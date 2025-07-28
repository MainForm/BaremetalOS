#include "HAL_SystemTimer.h"
#include "BCM2711_SystemTimer.h"
#include "BCM2711_peripheral.h"

static inline 
BCM2711_SystemTimer* getSystemTimer(uintptr_t addresss){
    return (BCM2711_SystemTimer*)addresss;
}

inline 
uint32_t HAL_SystemTimer_GetInterruptID(uint32_t timerID){
    return (BCM2711_GIC_SYSTEM_TIMER_IRQ(timerID));
}

uint32_t HAL_SystemTimer_GetLowCounter(){
    BCM2711_SystemTimer* SystemTimer = getSystemTimer(BCM2711_SYSTEM_TIMER_BASE);

    return BCM2711_SystemTimer_GetLowCounter(SystemTimer);
}

uint32_t HAL_SystemTimer_GetCompare(uint32_t timerID){
    BCM2711_SystemTimer* SystemTimer = getSystemTimer(BCM2711_SYSTEM_TIMER_BASE);

    if(timerID >= BCM2711_SYSTEM_TIMER_COUNT){
        return 0xFFFFFFFF;
    }

    return SystemTimer->C[timerID].value;
}

inline bool HAL_SystemTimer_IsEnable(){
    return true;
}

inline void HAL_SystemTimer_Initailize(uint32_t timerID, uint32_t nextTick){
    BCM2711_SystemTimer* SystemTimer = getSystemTimer(BCM2711_SYSTEM_TIMER_BASE);

    if(timerID >= BCM2711_SYSTEM_TIMER_COUNT){
        return;
    }

    BCM2711_SystemTimer_SetTick(SystemTimer,timerID,SystemTimer->CLO.value + nextTick);
    BCM2711_SystemTimer_ClearInterrupt(SystemTimer,timerID);
}

inline void HAL_SystemTimer_SetNextTick(uint32_t timerID, uint32_t nextTick){
    BCM2711_SystemTimer* SystemTimer = getSystemTimer(BCM2711_SYSTEM_TIMER_BASE);

    if(timerID >= BCM2711_SYSTEM_TIMER_COUNT){
        return;
    }

    BCM2711_SystemTimer_SetNextTick(SystemTimer,timerID,nextTick);
}

inline void HAL_SystemTimer_ClearInterrupt(uint32_t timerID){
    BCM2711_SystemTimer* SystemTimer = getSystemTimer(BCM2711_SYSTEM_TIMER_BASE);

    if(timerID >= BCM2711_SYSTEM_TIMER_COUNT){
        return;
    }

    BCM2711_SystemTimer_ClearInterrupt(SystemTimer,timerID);
}