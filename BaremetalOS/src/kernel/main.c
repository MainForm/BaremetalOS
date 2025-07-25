#include <stdlib.h>

#include "HAL_UART.h"
#include "HAL_GIC.h"

#include "interrupt.h"

#define UART0               (0)
#define RASP4_IRQ_UART0     (96 + 57)
#define RV_PB_IRQ_UART0     (44)

void delay(volatile uint32_t i){
    while(i-- > 0);
}

void UART0_Rx_IRQ_Handler(){
    uint8_t data = HAL_UART_ReceiveWord(UART0);

    HAL_UART_SendWord(UART0,data);
}

int main(){
    HAL_UART_Initialize(UART0, 115200);
    HAL_UART_EnableInterrupt(UART0, UART_IRQ_RX);

    HAL_GIC_Initialize();
    IRQ_Enable();

    IRQ_AttachInterrupt(RV_PB_IRQ_UART0,UART0_Rx_IRQ_Handler);

    while(1){}

    return 0;
}