#include "HAL_GPTimer.h"

#include "RealViewPB_a8_peripheral.h"
#include "SP804.h"

SP804_Timer* SP804_GetRegister(uint32_t timer_num){
    return (SP804_Timer*)(REALVIEW_PB_A8_GPTIMER_BASE(timer_num));
}

// The Raspberry Pi 4 has only one timer, so the timerNum argument is not used.
void HAL_GPTimer_Initialize(uint32_t timerNum){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }

    SP804_InitializeTimer((SP804_Timer *)timer);
}

void HAL_GPTimer_EnableTimer(uint32_t timerNum,bool value){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }

    SP804_EnableTimer((SP804_Timer *)timer, value);
}

void HAL_GPTimer_EnableInterrupt(uint32_t timerNum,bool value){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }

    SP804_EnableInterrupt((SP804_Timer *)timer,value);
}

void HAL_GPTimer_SetTimerMode(uint32_t timerNum, GPTIMER_MODE mode){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }

    SP804_SetTimerMode((SP804_Timer *)timer,mode);
}

void HAL_GPTimer_SetTimerSize(uint32_t timerNum, GPTIMER_SIZE size){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }

    SP804_SetTimerSize((SP804_Timer *)timer,size);
}

void HAL_GPTimer_SetTimerPrescale(uint32_t timerNum, GPTIMER_PRESCALE prescale){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }

    SP804_SetTimerPrescale((SP804_Timer *)timer,prescale);
}

void HAL_GPTimer_SetTimerLoad(uint32_t timerNum,uint32_t value){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }
    
    SP804_SetTimerLoad((SP804_Timer *)timer,value);
}

uint32_t HAL_GPTimer_GetTimerCounter(uint32_t timerNum){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return 0xFFFFFFFF;
    }

    return timer->TimerValue.value;
}

uint32_t HAL_GPTimer_GetTestValue(uint32_t timerNum){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return 0xFFFFFFFF;
    }

    return timer->TimerControl.value;
}

void HAL_GPTimer_ClearInterrupt(uint32_t timerNum){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return;
    }

    SP804_ClearInterrupt((SP804_Timer *)timer);
}

uint32_t HAL_GPTimer_GetInterruptID(uint32_t timerNum){
    SP804_Timer* timer = SP804_GetRegister(timerNum);

    if(timer == NULL){
        return 0xFFFFFFFF;
    }

    return REALVIEW_PB_A8_GIC_GPTIMER_IRQ(timerNum);
}