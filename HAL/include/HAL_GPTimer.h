#ifndef __HAL_GPTIMER__
#define __HAL_GPTIMER__

#include <stdint.h>
#include <stdbool.h>

typedef enum __GPTIMER_MODE{
    GPTIMER_MODE_FREE_RUNNING   = 0,
    GPTIMER_MODE_PERIODIC       = 1,
    GPTIMER_MODE_ONE_SHOT       = 2,
} GPTIMER_MODE;

typedef enum __GPTIMER_SIZE{
    GPTIMER_SIZE_16BITS = 0,
    GPTIMER_SIZE_32BITS = 1,
} GPTIMER_SIZE;

typedef enum __GPTIMER_PRESCALE{
    GPTIMER_PRESCALE_1          = 0b00,
    GPTIMER_PRESCALE_16         = 0b01,
    GPTIMER_PRESCALE_256        = 0b10,
} GPTIMER_PRESCALE;


__attribute__((weak))
void HAL_GPTimer_Initialize(uint32_t timerNum);

__attribute__((weak))
void HAL_GPTimer_EnableTimer(uint32_t timerNum,bool value);

__attribute__((weak))
void HAL_GPTimer_EnableInterrupt(uint32_t timerNum,bool value);

__attribute__((weak))
void HAL_GPTimer_SetTimerMode(uint32_t timerNum, GPTIMER_MODE mode);

__attribute__((weak))
void HAL_GPTimer_SetTimerSize(uint32_t timerNum, GPTIMER_SIZE size);

__attribute__((weak))
void HAL_GPTimer_SetTimerPrescale(uint32_t timerNum,GPTIMER_PRESCALE prescale);

__attribute__((weak))
void HAL_GPTimer_SetTimerLoad(uint32_t timerNum,uint32_t value);

__attribute__((weak))
uint32_t HAL_GPTimer_GetTimerCounter(uint32_t timerNum);

__attribute__((weak))
uint32_t HAL_GPTimer_GetTestValue(uint32_t timerNum);\

__attribute__((weak))
void HAL_GPTimer_ClearInterrupt(uint32_t timerNum);

__attribute__((weak))
uint32_t HAL_GPTimer_GetInterruptID(uint32_t timerNum);

#endif