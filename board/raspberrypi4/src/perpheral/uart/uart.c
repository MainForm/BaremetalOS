#include <stddef.h>

#include "memory.h"

#include "bcm2711_peripheral.h"
#include "perpheral/gpio.h"
#include "perpheral/uart.h"
#include "perpheral/interrupt.h"

IRQ_Handler_Callback uartIRQ_Callbacks[UART_IRQ_COUNT] = {0,};

static void UART_HandlingIRQ(void){
    int32_t uartIRQ_status = REG_32(BCM2711_UART0_MIS);

    for(int32_t idx = 0, mask = 1; idx < UART_IRQ_COUNT;++idx, mask <<= 1){
        if(uartIRQ_status & mask){
            if(uartIRQ_Callbacks[idx] != NULL){
                uartIRQ_Callbacks[idx]();
            }
        }
    }
}

void UART_Initialize(BCM2711_GPIO* gpio, uint32_t baudrate){
    // set the pin 14 and pin 15 to ALT0
    BCM2711_GPIO_SelectFunction(gpio, 14,FSEL_FUNC_ALT0);
    BCM2711_GPIO_SelectFunction(gpio, 15,FSEL_FUNC_ALT0);

    // disable the UART0
    REG_32(BCM2711_UART0_CR) = 0x0;

    // Get the BaudRateDivider
    double BRD = (UART0_CLK)/(16.0 * baudrate);
    
    REG_32(BCM2711_UART0_IBRD) = (uint32_t)BRD;

    // Remove the real part of BRD
    BRD -= (uint32_t)BRD;
    REG_32(BCM2711_UART0_FBRD) =  (uint32_t)(BRD * 64.0 + 0.5);

    // set the word length to 8bits and enable the FIFOs
    REG_32(BCM2711_UART0_LCRH) = UART_WLEN_8BIT;

    REG_32(BCM2711_UART0_ICR) = 0x7FF;

    // Enable the transmission data and the reception data
    // Enable the UART0
    REG_32(BCM2711_UART0_CR) = UART_TXE | UART_RXE | UART_UARTEN;
}

void UART_EnableInterrupt(uint32_t uartIRQ, IRQ_Handler_Callback callback){
    // Mask the specific bit to enable the interrupt
    REG_32(BCM2711_UART0_IMSC) |= uartIRQ;

    if(IRQ_IsEnableInterrupt(IRQ_UART_NUM) == false){
        IRQ_AttachInterrupt(IRQ_UART_NUM,UART_HandlingIRQ);
    }

    for(uint32_t idx = 0; idx < UART_IRQ_COUNT;++idx, uartIRQ >>= 1){
        if(uartIRQ & 0x01){
            uartIRQ_Callbacks[idx] = callback;
            break;
        }
    }
}

void UART_SendWord(uint8_t data){
    while(REG_32(BCM2711_UART0_FR) & UART_TXFF);

    REG_32(BCM2711_UART0_DR) = data;
}

uint8_t UART_ReceiveWord(){
    while(REG_32(BCM2711_UART0_FR) & UART_RXFE);

    uint32_t DataRegValue = REG_32(BCM2711_UART0_DR);
    if(DataRegValue & (UART_OE | UART_BE | UART_PE | UART_FE)){
        return 0;
    }

    return DataRegValue;
}

void UART_SendString(const char * str){
    while(*str != '\0'){
        UART_SendWord((uint8_t)*str);

        ++str;
    }
}