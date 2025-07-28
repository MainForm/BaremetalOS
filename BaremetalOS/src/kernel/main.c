#include "custom_libc/stdlib.h"
#include "custom_libc/stdio.h"
#include <stdbool.h>

#include "HAL_UART.h"
#include "HAL_GIC.h"
#include "HAL_GPTimer.h"
#include "HAL_GPIO.h"
#include "HAL_SystemTimer.h"

#include "interrupt.h"

#define UART0               (0)
#define TIMER0              (0)
#define GIC0                (0)
// System Timer 0 is already used for something else.
#define SYSTIMER1           (1)

#define SYSTIMER0_INTERVAL  (1000)

#define RASP4_UART0_TX      (14)
#define RASP4_UART0_RX      (15)

void delay(volatile uint32_t i){
    while(i-- > 0);
}

void UART0_Rx_IRQ_Handler(){
    uint8_t data = HAL_UART_ReceiveWord(UART0);

    HAL_UART_SendWord(UART0,data);
}

static uint32_t cnt = 0;
// Caution)
// Clearing the system timer IRQ and updating the compare register must be done at the beginning of the handler.
void SystemTimer_IRQ_Handler(){
    HAL_SystemTimer_ClearInterrupt(SYSTIMER1);
    HAL_SystemTimer_SetNextTick(SYSTIMER1,SYSTIMER0_INTERVAL);
    uint32_t counter = HAL_SystemTimer_GetLowCounter();
    uint32_t compare = HAL_SystemTimer_GetCompare(SYSTIMER1);

    if(cnt >= 1000){
        char buf[16];
        HAL_UART_SendString(UART0,"Timer is working\n");
        itoa(counter,buf,10);
        HAL_UART_SendString(UART0,"counter : ");
        HAL_UART_SendString(UART0,buf);
        HAL_UART_SendWord(UART0,'\n');

        itoa(compare,buf,10);
        HAL_UART_SendString(UART0,"compare : ");
        HAL_UART_SendString(UART0,buf);
        HAL_UART_SendWord(UART0,'\n');
        HAL_UART_SendWord(UART0,'\n');
        cnt = 0;
    }

    ++cnt;
}

int main(){
    HAL_UART_Initialize(UART0, 115200);
    HAL_UART_EnableInterrupt(UART0, UART_IRQ_RX);
    
    if(HAL_GPIO_IsEnable()){
        HAL_GPIO_SetFunction(RASP4_UART0_RX, GPIO_FUNC_ALT0);
        HAL_GPIO_SetFunction(RASP4_UART0_TX, GPIO_FUNC_ALT0);
    }

    HAL_GIC_Initialize(GIC0);
    IRQ_Enable();

    IRQ_AttachInterrupt(GIC0, HAL_UART_GetInterruptID(UART0), UART0_Rx_IRQ_Handler);

    if(HAL_SystemTimer_IsEnable()){
        HAL_SystemTimer_Initailize(SYSTIMER1,SYSTIMER0_INTERVAL);
        IRQ_AttachInterrupt(GIC0, HAL_SystemTimer_GetInterruptID(SYSTIMER1), SystemTimer_IRQ_Handler);
    }

    int value = 0x1A2B;

    while(1){
        uprintf(UART0, "n : 0x%x\n", value);
        delay(0x8000000);
    }

    return 0;
}