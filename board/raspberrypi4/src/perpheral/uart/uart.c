#include "memory.h"

#include "bcm2711_peripheral.h"
#include "perpheral/gpio.h"
#include "perpheral/uart.h"

void UART_Initialize(uint32_t baudrate){
    // set the pin 14 and pin 15 to ALT0
    GPIO_SelectFunction(14,GPIO_FUNC_ALT0);
    GPIO_SelectFunction(15,GPIO_FUNC_ALT0);

    // disable the UART0
    WRITE_REG_32(BCM2711_UART0_CR, 0x0);

    // Get the BaudRateDivider
    // double BRD = (UART0_CLK)/(16.0 * baudrate);
    
    // UART_SetIBRD((uint32_t)BRD);

    // // Remove the real part of BRD
    // BRD -= (uint32_t)BRD;
    // UART_SetFBRD((uint32_t)(BRD * 64.0 + 0.5));

    WRITE_REG_32(BCM2711_UART0_IBRD, 26);
    WRITE_REG_32(BCM2711_UART0_FBRD, 3);

    // set the word length to 8bits and enable the FIFOs
    WRITE_REG_32(BCM2711_UART0_LCRH, UART_WLEN_8BIT | UART_FEN);

    // set Recv and Trans FIFO level to 1/2
    WRITE_REG_32(BCM2711_UART0_IFLS, UART_RXFLSEL_1DIV2 | UART_TXFLSEL_1DIV2);

    WRITE_REG_32(BCM2711_UART0_CR, UART_TXE | UART_RXE | UART_UARTEN);
}

void UART_SendWord(uint8_t data){
    while(READ_REG_32(BCM2711_UART0_FR) & UART_TXFF);

    WRITE_REG_32(BCM2711_UART0_DR, data);
}