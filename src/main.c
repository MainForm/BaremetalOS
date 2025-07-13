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
    int num = 0xABCD;
    char buf[10] = "";

    GPIO_SelectFunction(LED_PIN,GPIO_FUNC_OUTPUT);
    UART_Initialize(115200);

    while(1){
        GPIO_SetOutput(LED_PIN,1);
        itoa(num,buf,16);
        UART_SendString(buf);

        delay();

        GPIO_SetOutput(LED_PIN,0);

        delay();
    }

    return 0;
}