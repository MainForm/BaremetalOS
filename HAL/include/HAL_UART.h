#ifndef __HAL_UART__
#define __HAL_UART__

#include <stdint.h>

typedef enum __UART_IRQ {
	UART_IRQ_CTSM	= (0x01 << 1),      // nUARTCTS modem interrupt mask
	UART_IRQ_RX	    = (0x01 << 4),      // Receive interrupt mask.
	UART_IRQ_TX 	= (0x01 << 5),      // Transmit interrupt mask.
	UART_IRQ_RT 	= (0x01 << 6),      // Receive timeout interrupt mask.
	UART_IRQ_FE 	= (0x01 << 7),      // Framing error interrupt mask.
	UART_IRQ_PE 	= (0x01 << 8),      // Parity error interrupt mask.
	UART_IRQ_BE 	= (0x01 << 9),      // Break error interrupt mask.
	UART_IRQ_OE 	= (0x01 << 10),     // Overrun error interrupt mask.
} UART_IRQ;

__attribute__((weak))
void HAL_UART_Initialize(uint32_t uart_num, uint32_t baudrate);

__attribute__((weak))
void HAL_UART_SendWord(uint32_t uart_num, uint8_t data);

__attribute__((weak))
uint32_t HAL_UART_ReceiveWord(uint32_t uart_num);

__attribute__((weak))
void HAL_UART_SendString(uint32_t uart_num, const char * string);

__attribute__((weak))
void HAL_UART_EnableInterrupt(uint32_t uart_num,UART_IRQ irq);

__attribute__((weak))
uint32_t HAL_UART_GetInterruptID(uint32_t uart_num);

#endif