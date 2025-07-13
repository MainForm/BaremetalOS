#ifndef __BCM2711_UART_H__
#define __BCM2711_UART_H__

#include <stdint.h>
#include <stdbool.h>

#define UART0_CLK               (48000000)

#define UART_RXE                (0x01 << 9)
#define UART_TXE                (0x01 << 8)
#define UART_UARTEN             (0x01)

#define UART_TXFF               (0x01 << 5)

#define UART_WLEN_8BIT          (0x03 << 5)
#define UART_WLEN_7BIT          (0x02 << 5)
#define UART_WLEN_6BIT          (0x01 << 5)
#define UART_WLEN_5BIT          (0x00 << 5)

#define UART_FEN                (0x01 << 4)

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

void UART_Initialize(uint32_t baudrate);

void UART_SendWord(uint8_t data);
void UART_SendString(const char * str);

#endif