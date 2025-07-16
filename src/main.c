#include <stdint.h>
#include <stdlib.h>

#include "perpheral/uart.h"
#include "perpheral/gic-400.h"

#define LED_PIN             (21)

void delay(volatile int i){
    while(i-- > 0);
}

int main(){
    uint32_t gic_id = 0;
    char buf[16];

    UART_Initialize(115200);

    while(1){
        // You need to read 0x200143B from the GIC to confirm that it’s functioning correctly.
        gic_id = GIC400_GetDistID();
        itoa(gic_id,buf,16);
        UART_SendString("GIC-400 ID : ");
        UART_SendString(buf);
        UART_SendWord('\n');

        delay(0x1000000);
    }

    return 0;
}