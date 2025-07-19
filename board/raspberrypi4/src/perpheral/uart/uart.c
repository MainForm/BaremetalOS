#include <stddef.h>

#include "memory.h"

#include "perpheral/uart.h"
#include "perpheral/interrupt.h"

IRQ_Handler_Callback uartIRQ_Callbacks[UART_IRQ_COUNT];

static void PL011_HandlingIRQ(void* interrupted_pl011){
    PL011* pl011 = (PL011*)interrupted_pl011;
    uint32_t uartIRQ_status = pl011->MIS.value; // REG_32(BCM2711_UART0_MIS);

    for(uint32_t idx = 0, mask = 1; idx < UART_IRQ_COUNT;++idx, mask <<= 1){
        if(uartIRQ_status & mask){
            if(uartIRQ_Callbacks[idx] != NULL){
                uartIRQ_Callbacks[idx](interrupted_pl011);
            }
        }
    }
}

PL011* PL011_Initialize(uint32_t baudrate){
    PL011* pl011 = (PL011 *)BCM2711_UART0_BASE;
    // disable the UART0
    pl011->CR.value = 0x00;

    // Get the BaudRateDivider
    double BRD = (UART0_CLK)/(16.0 * baudrate);
    
    pl011->IBRD.value = (uint32_t)BRD;

    // Remove the real part of BRD
    BRD -= (uint32_t)BRD;
    pl011->FBRD.value =  (uint32_t)(BRD * 64.0 + 0.5);

    // set the word length to 8bits and enable the FIFOs
    pl011->LCRH.WLEN = PL011_WLEN_8BITS;

    pl011->ICR.value = 0x7FF;

    // Enable the transmission data and the reception data
    // Enable the UART0
    pl011->CR.TXE = 1;
    pl011->CR.RXE = 1;
    pl011->CR.UARTEN = 1;

    return pl011;
}

void PL011_EnableInterrupt(PL011* pl011,GIC400* gic400, PL011_IMSC uartIRQ, IRQ_Handler_Callback callback){
    // Mask the specific bit to enable the interrupt
    pl011->IMSC.value |= uartIRQ;

    if(IRQ_IsEnableInterrupt(IRQ_UART_NUM) == false){
        IRQ_AttachInterrupt(gic400, IRQ_UART_NUM,PL011_HandlingIRQ,(void*)pl011);
    }

    for(uint32_t idx = 0; idx < UART_IRQ_COUNT;++idx, uartIRQ >>= 1){
        if(uartIRQ & 0x01){
            uartIRQ_Callbacks[idx] = callback;
            break;
        }
    }
}

void PL011_SendWord(PL011* pl011,uint8_t data){
    while(pl011->FR.TXFF);

    pl011->DR.Data = data;
}

void PL011_SendString(PL011* pl011, const char * str){
    while(*str != '\0'){
        PL011_SendWord(pl011, (uint8_t)*str);

        ++str;
    }
}

uint8_t PL011_ReceiveWord(PL011* pl011){
    while(pl011->FR.RXFE);

    PL011_DR_REG DataReg = pl011->DR;
    while(DataReg.OE | DataReg.BE | DataReg.PE | DataReg.FE){
        return 0;
    }

    return DataReg.Data;
}