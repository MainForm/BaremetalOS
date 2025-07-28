#include <stddef.h>

#include "UART/PL011.h"

PL011* PL011_GetRegisters(uintptr_t BaseAddress){
    return (PL011*)BaseAddress;
}

void PL011_Initialize(PL011* pl011,uint32_t UARTCLK, uint32_t baudrate){
    // disable the UART0
    pl011->CR.value = 0x00;

    // Get the BaudRateDivider
    double BRD = (UARTCLK)/(16.0 * baudrate);
    
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
}

void PL011_EnableInterrupt(PL011* pl011, PL011_IMSC uartIRQ){
    // Mask the specific bit to enable the interrupt
    pl011->IMSC.value |= uartIRQ;
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