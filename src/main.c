#include <stdint.h>

#include "perpheral/gpio.h"

#define LED_PIN     (21)

void delay(){
    int i = 0x100000;

    while(i-- > 0);
}

int main(){
    GPIO_SelectFunction(LED_PIN,GPIO_FUNC_OUTPUT);

    while(1){
        GPIO_SetOutput(LED_PIN,1);

        delay();

        GPIO_SetOutput(LED_PIN,0);

        delay();
    }

    return 0;
}