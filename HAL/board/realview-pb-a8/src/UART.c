#include "HAL_UART.h"
#include "UART/PL011.h"
#include "RealViewPB_a8_peripheral.h"

void HAL_UART_Initialize(uint32_t uart_num, uint32_t baudrate){
    PL011* pl011 = PL011_GetRegisters(REALVIEW_PB_A8_UART_BASE(uart_num));

    if(pl011 == NULL){
        return;
    }

    PL011_Initialize(pl011,UART_CLK, baudrate);
}

void HAL_UART_SendWord(uint32_t uart_num, uint8_t data){
    PL011* pl011 = PL011_GetRegisters(REALVIEW_PB_A8_UART_BASE(uart_num));

    if(pl011 == NULL){
        return;
    }

    PL011_SendWord(pl011,data);
}

uint32_t HAL_UART_ReceiveWord(uint32_t uart_num){
    PL011* pl011 = PL011_GetRegisters(REALVIEW_PB_A8_UART_BASE(uart_num));

    if(pl011 == NULL){
        return 0xFFFFFFFF;
    }

    return PL011_ReceiveWord(pl011);
}

void HAL_UART_SendString(uint32_t uart_num, const char * string){
    PL011* pl011 = PL011_GetRegisters(REALVIEW_PB_A8_UART_BASE(uart_num));

    if(pl011 == NULL){
        return;
    }

    PL011_SendString(pl011,string);
}

void HAL_UART_EnableInterrupt(uint32_t uart_num,UART_IRQ irq){
    PL011* pl011 = PL011_GetRegisters(REALVIEW_PB_A8_UART_BASE(uart_num));

    if(pl011 == NULL){
        return;
    }

    PL011_EnableInterrupt(pl011,(PL011_IMSC)irq);
}

uint32_t HAL_UART_GetInterruptID(uint32_t uart_num){
    PL011* pl011 = PL011_GetRegisters(REALVIEW_PB_A8_UART_BASE(uart_num));

    if(pl011 == NULL){
        return 0xFFFFFFFF;
    }

    return REALVIEW_PB_A8_GIC_UART_IRQ(uart_num);
}