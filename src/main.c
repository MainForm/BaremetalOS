#include <stdint.h>

#include "perpheral/gpio.h"
#include "perpheral/uart.h"

#define LED_PIN     (21)

void delay(){
    int i = 0x100000;

    while(i-- > 0);
}

int main(){
    GPIO_SelectFunction(LED_PIN,GPIO_FUNC_OUTPUT);
    UART_Initialize(115200);

    while(1){
        GPIO_SetOutput(LED_PIN,1);
        UART_SendWord('T');

        delay();

        GPIO_SetOutput(LED_PIN,0);
        UART_SendWord('F');

        delay();
    }

    return 0;
}