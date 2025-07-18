#include <stdlib.h>

#include "perpheral/gpio.h"

#define LED_PIN             (21)


void delay(volatile uint32_t i){
    while(i-- > 0);
}

int main(){
    BCM2711_GPIO* gpio = BCM2711_GPIO_Initialize();

    BCM2711_GPIO_SelectFunction(gpio,LED_PIN,FSEL_FUNC_OUTPUT);


    while(1){
        BCM2711_GPIO_SetOutput(gpio,LED_PIN,true);
        delay(0x200000);

        BCM2711_GPIO_SetOutput(gpio,LED_PIN,false);
        delay(0x200000);
    }

    return 0;
}