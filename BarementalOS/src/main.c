#include <stdlib.h>

#include "HAL_GPIO.h"
#include "HAL_UART.h"
#include "HAL_GIC.h"
#include "interrupt.h"

#include "BCM2711_peripheral.h"
#include "GIC-400.h"

#define UART0               (0)

#define IRQ_UART            (96 + 57)

#define LED_PIN				(21)
#define UART0_TX			(14)
#define UART0_RX			(15)

void delay(volatile uint32_t i){
    while(i-- > 0);
}

void UART_IRQ_Rx_Handler(){
    uint8_t data = HAL_UART_ReceiveWord(UART0);

    HAL_UART_SendWord(UART0,data);
}

int main(){
    HAL_GIC_Initialize();
    IRQ_Enable();

    HAL_GIC_EnableInterrupt(IRQ_UART);

    HAL_UART_Initialize(UART0,115200);
    HAL_UART_EnableInterrupt(UART0,UART_IRQ_RX);
    
    HAL_GPIO_SetFunction(UART0_TX,GPIO_FUNC_ALT0);
    HAL_GPIO_SetFunction(UART0_RX,GPIO_FUNC_ALT0);

    HAL_GPIO_SetFunction(LED_PIN,GPIO_FUNC_OUTPUT);

    IRQ_AttachInterrupt(IRQ_UART,UART_IRQ_Rx_Handler);

    HAL_GPIO_SetOutput(LED_PIN,HIGH);
    
    while(1){}

    return 0;
}