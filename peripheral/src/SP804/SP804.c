#include "Timer/SP804.h"

volatile SP804_Timer* SP804_GetTimerRegister(uintptr_t address){
    return (volatile SP804_Timer*)address;
}

// The timer initialization process is described in section 2.2.6, “Timer Operation,” of the SP804 datasheet.
// The timer is not enabled after initialization.
void SP804_InitializeTimer(SP804_Timer* timer){
    timer->TimerControl.TimerEn     = 0;

    timer->TimerControl.TimerMode   = 0;
    timer->TimerControl.OneShot     = 0;

    timer->TimerControl.TimerSize   = 0;

    timer->TimerControl.TimerPre    = 0x0;

    timer->TimerControl.IntEnable    = 1;

    timer->TimerLoad.value          = 0;
    timer->TimerValue.value         = 0xFFFFFFFF;
}

void SP804_SetTimerMode(SP804_Timer* timer, SP804_TIMER_MODE mode){
    switch(mode){
    case SP804_TIMER_MODE_FREE_RUNNING:
        timer->TimerControl.OneShot     = 0;
        timer->TimerControl.TimerMode   = 0;
        break;
    case SP804_TIMER_MODE_PERIODIC:
        timer->TimerControl.OneShot     = 0;
        timer->TimerControl.TimerMode   = 1;
        break;
    case SP804_TIMER_MODE_ONE_SHOT:
        timer->TimerControl.OneShot     = 1;
        break;
    default:

        break;
    }
}

inline void SP804_SetTimerSize(SP804_Timer* timer, SP804_TIMER_SIZE size){
    timer->TimerControl.TimerSize = size;
}

inline void SP804_SetTimerPrescale(SP804_Timer* timer,SP804_TIMER_PRESCALE prescale){
    timer->TimerControl.TimerPre = prescale;
}

inline void SP804_SetTimerLoad(SP804_Timer* timer,uint32_t value){
    timer->TimerLoad.value = value;
}

inline uint32_t SP804_GetTimerCounter(SP804_Timer* timer){
    return timer->TimerValue.value;
}

inline void SP804_EnableTimer(SP804_Timer* timer,bool value){
    timer->TimerControl.TimerEn = value;
}

inline void SP804_EnableInterrupt(SP804_Timer* timer,bool value){
    timer->TimerIntClr.value = 1;
    timer->TimerControl.TimerSize = value;
}

void SP804_ClearInterrupt(SP804_Timer* timer){
    timer->TimerIntClr.value = 1;
}