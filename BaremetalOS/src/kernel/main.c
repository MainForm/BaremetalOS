#include <stdlib.h>
#include <stdbool.h>

#include "HAL_UART.h"
#include "HAL_GIC.h"
#include "HAL_GPTimer.h"

#include "interrupt.h"

#define UART0               (0)
#define TIMER0              (0)
#define GIC0                (0)

void delay(volatile uint32_t i){
    while(i-- > 0);
}

void UART0_Rx_IRQ_Handler(){
    uint8_t data = HAL_UART_ReceiveWord(UART0);

    HAL_UART_SendWord(UART0,data);
}

void TIMER0_IRQ_Handler(){
    static uint32_t cnt = 0;

    if(cnt >= 100){
        HAL_UART_SendString(UART0,"Timer is working\n");

        cnt = 0;
    }

    ++cnt;

    HAL_GPTimer_ClearInterrupt(TIMER0);
}

int main(){
    HAL_UART_Initialize(UART0, 115200);
    HAL_UART_EnableInterrupt(UART0, UART_IRQ_RX);

    HAL_GPTimer_Initialize(TIMER0);
    HAL_GPTimer_SetTimerMode(TIMER0,GPTIMER_MODE_PERIODIC);
    HAL_GPTimer_SetTimerSize(TIMER0,GPTIMER_SIZE_32BITS);
    HAL_GPTimer_SetTimerPrescale(TIMER0, GPTIMER_PRESCALE_16);
    HAL_GPTimer_SetTimerLoad(TIMER0,1000);
    HAL_GPTimer_EnableInterrupt(TIMER0,true);
    HAL_GPTimer_EnableTimer(TIMER0,true);

    HAL_GIC_Initialize(GIC0);
    IRQ_Enable();

    IRQ_AttachInterrupt(GIC0, HAL_UART_GetInterruptID(UART0), UART0_Rx_IRQ_Handler);
    IRQ_AttachInterrupt(GIC0, HAL_GPTimer_GetInterruptID(TIMER0), TIMER0_IRQ_Handler);

    while(1){
        HAL_UART_SendString(UART0,"main func is working\n");
        delay(0xC000000);
    }

    return 0;
}