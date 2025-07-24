#include "HAL_GPTimer.h"

#include "BCM2711_peripheral.h"

BCM2711_SP804_Timer* BCM2711_SP804_GetRegister(){
    return (BCM2711_SP804_Timer*)(BCM2711_SP804_TIMER0_BASE);
}

// The Raspberry Pi 4 has only one timer, so the timerNum argument is not used.
void HAL_GPTimer_Initialize(uint32_t timerNum){
    if(timerNum != 0){
        return;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    SP804_InitializeTimer((SP804_Timer *)timer);

    // Set the timer clock to 1MHz
    timer->PREDIV.PREDIV        = 249;

    timer->TimerControl.DebugHalt = 0;
    timer->TimerControl.EnableFreeRunning = 0;
}

void HAL_GPTimer_EnableTimer(uint32_t timerNum,bool value){
    if(timerNum != 0){
        return;
    }

    BCM2711_SP804_Timer * timer = BCM2711_SP804_GetRegister();

    SP804_EnableTimer((SP804_Timer *)timer, value);
}

void HAL_GPTimer_EnableInterrupt(uint32_t timerNum,bool value){
    if(timerNum != 0){
        return;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    SP804_EnableInterrupt((SP804_Timer *)timer,value);
}

void HAL_GPTimer_SetTimerMode(uint32_t timerNum, GPTIMER_MODE mode){
    if(timerNum != 0){
        return;
    }

    // BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    // SP804_SetTimerMode((SP804_Timer *)timer,mode);
}

void HAL_GPTimer_SetTimerSize(uint32_t timerNum, GPTIMER_SIZE size){
    if(timerNum != 0){
        return;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    SP804_SetTimerSize((SP804_Timer *)timer,size);
}

void HAL_GPTimer_SetTimerPrescale(uint32_t timerNum, GPTIMER_PRESCALE prescale){
    if(timerNum != 0){
        return;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    SP804_SetTimerPrescale((SP804_Timer *)timer,prescale);
}

void HAL_GPTimer_SetTimerLoad(uint32_t timerNum,uint32_t value){
    if(timerNum != 0){
        return;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();
    
    SP804_SetTimerLoad((SP804_Timer *)timer,value);
}

uint32_t HAL_GPTimer_GetTimerCounter(uint32_t timerNum){
    if(timerNum != 0){
        return -1;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    return timer->TimerValue.value;
}

uint32_t HAL_GPTimer_GetTestValue(uint32_t timerNum){
    if(timerNum != 0){
        return -1;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    return timer->TimerControl.value;
}

void HAL_GPTimer_ClearInterrupt(uint32_t timerNum){
    if(timerNum != 0){
        return;
    }

    BCM2711_SP804_Timer* timer = BCM2711_SP804_GetRegister();

    SP804_ClearInterrupt((SP804_Timer *)timer);
}