#ifndef __HAL_SYSTEM_TIMER__
#define __HAL_SYSTEM_TIMER__

#include <stdint.h>
#include <stdbool.h>

__attribute__((weak))
bool HAL_SystemTimer_IsEnable();

__attribute__((weak))
uint32_t HAL_SystemTimer_GetInterruptID(uint32_t timerID);

__attribute__((weak))
uint32_t HAL_SystemTimer_GetLowCounter();

__attribute__((weak))
uint32_t HAL_SystemTimer_GetCompare(uint32_t timerID);

__attribute__((weak))
void HAL_SystemTimer_Initailize(uint32_t timerID, uint32_t nextTick);

__attribute__((weak))
void HAL_SystemTimer_SetNextTick(uint32_t timerID, uint32_t nextTick);

__attribute__((weak))
void HAL_SystemTimer_ClearInterrupt(uint32_t timerID);

#endif