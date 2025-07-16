#include <stdlib.h>

#include "perpheral/gpio.h"
#include "perpheral/interrupt.h"
#include "perpheral/uart.h"

#define LED_PIN             (21)

uint32_t test;

void UART_IRQ_RecvData_callback(){
    uint8_t data = UART_ReceiveWord();
    UART_SendWord(data);
}

void delay(volatile uint32_t i){
    while(i-- > 0);
}

int main(){
    GPIO_SelectFunction(LED_PIN, GPIO_FUNC_OUTPUT);

    IRQ_Initialize();

    UART_Initialize(115200);
    UART_EnableInterrupt(UART_RXIM, UART_IRQ_RecvData_callback);

    GPIO_SetOutput(LED_PIN,true);

    while(1){
    }

    return 0;
}