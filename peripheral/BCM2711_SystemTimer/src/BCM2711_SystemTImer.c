#include "BCM2711_SystemTimer.h"

inline uint32_t BCM2711_SystemTimer_GetLowCounter(BCM2711_SystemTimer* SystemTimer){
    return SystemTimer->CLO.value;
}

inline uint64_t BCM2711_SystemTimer_GetCounter(BCM2711_SystemTimer* SystemTimer){
    return ((uint64_t)SystemTimer->CHI.value << 32) | (uint64_t)SystemTimer->CLO.value;
}

inline void BCM2711_SystemTimer_SetTick(BCM2711_SystemTimer* SystemTimer,uint32_t timerID, uint32_t Tick){
    SystemTimer->C[timerID].value = Tick;
}

inline void BCM2711_SystemTimer_SetNextTick(BCM2711_SystemTimer* SystemTimer,uint32_t timerID, uint32_t nextTick){
    SystemTimer->C[timerID].value = SystemTimer->CLO.value + nextTick;
}

inline void BCM2711_SystemTimer_ClearInterrupt(BCM2711_SystemTimer* SystemTimer,uint32_t timerID){
    SystemTimer->CS.value = 0b01 << timerID;
}