#include <stdlib.h>

#include "perpheral/gpio.h"
#include "perpheral/uart.h"
#include "perpheral/gic-400.h"

#define LED_PIN				(21)
#define UART0_TX			(14)
#define UART0_RX			(15)

void delay(volatile uint32_t i){
    while(i-- > 0);
}

int main(){
    BCM2711_GPIO* gpio = BCM2711_GPIO_Initialize();
    PL011* uart0 = PL011_Initialize(115200);
    GIC400* gic400 = GIC400_Initialize();

    char buf[16];

    BCM2711_GPIO_SelectFunction(gpio,LED_PIN,FSEL_FUNC_OUTPUT);
    BCM2711_GPIO_SelectFunction(gpio,UART0_TX,FSEL_FUNC_ALT0);
    BCM2711_GPIO_SelectFunction(gpio,UART0_RX,FSEL_FUNC_ALT0);

    while(1){
        BCM2711_GPIO_SetOutput(gpio,LED_PIN,true);
        itoa(gic400->Distributor.GICD_IIDR.value,buf,16);
        PL011_SendString(uart0, "GICD_IIDR : ");
        PL011_SendString(uart0, buf);
        PL011_SendWord(uart0, '\n');

        itoa(gic400->CPU.GICC_IIDR.value,buf,16);
        PL011_SendString(uart0, "GICC_IIDR : ");
        PL011_SendString(uart0, buf);
        PL011_SendWord(uart0, '\n');

        delay(0x200000);

        BCM2711_GPIO_SetOutput(gpio,LED_PIN,false);
        delay(0x200000);
    }

    return 0;
}