#include <stdlib.h>

#include "perpheral/gpio.h"
#include "perpheral/uart.h"

#define LED_PIN				(21)
#define UART0_TX			(14)
#define UART0_RX			(15)

void delay(volatile uint32_t i){
    while(i-- > 0);
}

int main(){
    BCM2711_GPIO* gpio = BCM2711_GPIO_Initialize();
    PL011* uart0 = PL011_Initialize(115200);

    BCM2711_GPIO_SelectFunction(gpio,LED_PIN,FSEL_FUNC_OUTPUT);
    BCM2711_GPIO_SelectFunction(gpio,UART0_TX,FSEL_FUNC_ALT0);
    BCM2711_GPIO_SelectFunction(gpio,UART0_RX,FSEL_FUNC_ALT0);

    while(1){
        BCM2711_GPIO_SetOutput(gpio,LED_PIN,true);
		PL011_SendWord(uart0,'1');
        delay(0x200000);

        BCM2711_GPIO_SetOutput(gpio,LED_PIN,false);
		PL011_SendWord(uart0,'0');
        delay(0x200000);
    }

    return 0;
}