#include <stdlib.h>

#include "HAL_UART.h"

#define UART0               (0)

void delay(volatile uint32_t i){
    while(i-- > 0);
}

int main(){
    HAL_UART_Initialize(UART0, 115200);

    HAL_UART_SendString(UART0, "Hello RealView-PB-A8\n");

    while(1){}

    return 0;
}