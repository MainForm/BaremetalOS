#include "HAL_GPTimer.h"

#include "RealViewPB_a8_peripheral.h"
#include "SP804.h"

SP804_Timer* SP804_GetRegister(uint32_t timer_num){
    return (SP804_Timer*)(REALVIEW_PB_A8_GPTIMER_BASE(timer_num));
}

// The Raspberry Pi 4 has only one timer, so the timerNum argument is not used.
void HAL_GPTimer_Initialize(uint32_t timerNum){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    SP804_InitializeTimer((SP804_Timer *)timer);
}

void HAL_GPTimer_EnableTimer(uint32_t timerNum,bool value){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    SP804_EnableTimer((SP804_Timer *)timer, value);
}

void HAL_GPTimer_EnableInterrupt(uint32_t timerNum,bool value){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    SP804_EnableInterrupt((SP804_Timer *)timer,value);
}

void HAL_GPTimer_SetTimerMode(uint32_t timerNum, GPTIMER_MODE mode){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    SP804_SetTimerMode((SP804_Timer *)timer,mode);
}

void HAL_GPTimer_SetTimerSize(uint32_t timerNum, GPTIMER_SIZE size){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    SP804_SetTimerSize((SP804_Timer *)timer,size);
}

void HAL_GPTimer_SetTimerPrescale(uint32_t timerNum, GPTIMER_PRESCALE prescale){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    SP804_SetTimerPrescale((SP804_Timer *)timer,prescale);
}

void HAL_GPTimer_SetTimerLoad(uint32_t timerNum,uint32_t value){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);
    
    SP804_SetTimerLoad((SP804_Timer *)timer,value);
}

uint32_t HAL_GPTimer_GetTimerCounter(uint32_t timerNum){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return 0xFFFFFFFF;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    return timer->TimerValue.value;
}

uint32_t HAL_GPTimer_GetTestValue(uint32_t timerNum){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return 0xFFFFFFFF;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    return timer->TimerControl.value;
}

void HAL_GPTimer_ClearInterrupt(uint32_t timerNum){
    if(timerNum >= REAELVIEW_PB_A8_GPTIMER_COUNT){
        return;
    }

    SP804_Timer* timer = SP804_GetRegister(timerNum);

    SP804_ClearInterrupt((SP804_Timer *)timer);
}