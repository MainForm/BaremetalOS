#ifndef __BCM2711_UART_H__
#define __BCM2711_UART_H__

#include <stdint.h>
#include <stdbool.h>

#include "perpheral/interrupt.h"

// Default UART0 clock
#define UART0_CLK               (48000000)

// DR(Data Register) Register bits
#define UART_OE                 (0x01 << 11)
#define UART_BE                 (0x01 << 10)
#define UART_PE                 (0x01 << 9)
#define UART_FE                 (0x01 << 8)
#define UART_DATA               (0xFF)

// CR(Control Register) Register bits
#define UART_RXE                (0x01 << 9)
#define UART_TXE                (0x01 << 8)
#define UART_UARTEN             (0x01)

// FR(Flag Register) Register bits
#define UART_TXFF               (0x01 << 5)
#define UART_RXFE               (0x01 << 4)

// LCRH(Line Control Register) Register bits
#define UART_WLEN_8BIT          (0x03 << 5)
#define UART_WLEN_7BIT          (0x02 << 5)
#define UART_WLEN_6BIT          (0x01 << 5)
#define UART_WLEN_5BIT          (0x00 << 5)
#define UART_FEN                (0x01 << 4)

// IFLS(Interrupt FIFO Level Select) Register bits
#define UART_RXFLSEL_1DIV8      (0x00 << 3)
#define UART_RXFLSEL_1DIV4      (0x01 << 3)
#define UART_RXFLSEL_1DIV2      (0x02 << 3)
#define UART_RXFLSEL_3DIV4      (0x03 << 3)
#define UART_RXFLSEL_7DIV8      (0x04 << 3)

#define UART_TXFLSEL_1DIV8      (0x00)
#define UART_TXFLSEL_1DIV4      (0x01)
#define UART_TXFLSEL_1DIV2      (0x02)
#define UART_TXFLSEL_3DIV4      (0x03)
#define UART_TXFLSEL_7DIV8      (0x04)

// MIS(Masked Interrupt Status) Register bits
#define UART_RXMIS              (0x01 << 4)

// IMMSC(Interrupt Mask Set Clear) Register bits
#define UART_RTIM               (0x01 << 6)
#define UART_TXIM               (0x01 << 5)
#define UART_RXIM               (0x01 << 4)


#define UART_IRQ_COUNT          (11)

void UART_Initialize(uint32_t baudrate);
void UART_EnableInterrupt(uint32_t uartIRQ, IRQ_Handler_Callback callback);

void UART_SendWord(uint8_t data);
uint8_t UART_ReceiveWord();

void UART_SendString(const char * str);

#endif