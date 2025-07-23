#ifndef __SP804_H__
#define __SP804_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum __SP804_TIMER_MODE{
    SP804_TIMER_MODE_FREE_RUNNING   = 0,
    SP804_TIMER_MODE_PERIODIC       = 1,
    SP804_TIMER_MODE_ONE_SHOT       = 2,
} SP804_TIMER_MODE;

typedef enum __SP804_TIMER_SIZE{
    SP804_TIMER_SIZE_16BITS         = 0,
    SP804_TIMER_SIZE_32BITS         = 1,
} SP804_TIMER_SIZE;

typedef enum __SP804_TIMER_PRESCALE{
    SP804_TIMER_PRESCALE_1          = 0b00,
    SP804_TIMER_PRESCALE_16         = 0b01,
    SP804_TIMER_PRESCALE_256        = 0b10,
} SP804_TIMER_PRESCALE;

typedef union __SP804_TimerLoad_REG{
    uint32_t value;
} SP804_TimerLoad_REG;

typedef union __SP804_TimerValue_REG{
    uint32_t value;
} SP804_TimerValue_REG;

typedef union __SP804_TimerControl_REG{
    uint32_t value;

    struct {
        uint32_t OneShot        :  1;
        uint32_t TimerSize      :  1;
        uint32_t TimerPre       :  2;
        uint32_t                :  1;
        uint32_t IntEnable      :  1;
        uint32_t TimerMode      :  1;
        uint32_t TimerEn        :  1;
        uint32_t                : 24;
    };
} SP804_TimerControl_REG;

typedef union __SP804_TimerIntClr_REG{
    uint32_t value;
} SP804_TimerIntClr_REG;

typedef union __SP804_TimerRIS_REG{
    uint32_t value;

    struct {
        uint32_t TimerRIS       :  1;
        uint32_t                : 31;
    };
} SP804_TimerRIS_REG;

typedef union __SP804_TimerMIS_REG{
    uint32_t value;

    struct {
        uint32_t TimerMIS       :  1;
        uint32_t                : 31;
    };
} SP804_TimerMIS_REG;

typedef union __SP804_TimerBGLoad_REG{
    uint32_t value;
} SP804_TimerBGLoad_REG;

typedef volatile struct __SP804_Timer{
    SP804_TimerLoad_REG     TimerLoad;      // Offset : 0x0000
    SP804_TimerValue_REG    TimerValue;     // Offset : 0x0004
    SP804_TimerControl_REG  TimerControl;   // Offset : 0x0008
    SP804_TimerIntClr_REG   TimerIntClr;    // Offset : 0x000C
    SP804_TimerRIS_REG      TimerRIS;       // Offset : 0x0010
    SP804_TimerMIS_REG      TimerMIS;       // Offset : 0x0014
    SP804_TimerBGLoad_REG   TimerBGLoad;    // Offset : 0x0018
} SP804_Timer;

typedef struct __SP804{
    SP804_Timer         Timer1;             // Offset : 0x0000

    struct {
        uint32_t                : 32;       // Offset : 0x001C
    };

    SP804_Timer         Timer2;             // Offset : 0x0020
} SP804;

volatile SP804_Timer* SP804_GetTimerRegister(uintptr_t address);

void SP804_InitializeTimer(volatile SP804_Timer* timer);

void SP804_SetTimerMode(SP804_Timer* timer, SP804_TIMER_MODE mode);
void SP804_SetTimerSize(SP804_Timer* timer, SP804_TIMER_SIZE size);
void SP804_SetTimerPrescale(SP804_Timer* timer,SP804_TIMER_PRESCALE prescale);
void SP804_SetTimerLoad(SP804_Timer* timer,uint32_t value);

uint32_t SP804_GetTimerCounter(SP804_Timer* timer);

void SP804_EnableTimer(SP804_Timer* timer,bool value);
void SP804_EnableInterrupt(SP804_Timer* timer,bool value);

void SP804_ClearInterrupt(SP804_Timer* timer);

#endif