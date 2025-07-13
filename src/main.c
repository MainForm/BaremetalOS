#include <stdint.h>
#include <stdlib.h>

#include "perpheral/gpio.h"
#include "perpheral/uart.h"

#define LED_PIN     (21)

void delay(){
    volatile int i = 0x100000;

    while(i-- > 0);
}

int main(){
    GPIO_SelectFunction(LED_PIN,GPIO_FUNC_OUTPUT);
    UART_Initialize(115200);

    GPIO_SetOutput(LED_PIN,true);

    while(1){
        uint8_t data = UART_ReceiveWord();
        
        UART_SendWord(data);
    }

    return 0;
}