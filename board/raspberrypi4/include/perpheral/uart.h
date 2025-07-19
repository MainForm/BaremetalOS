#ifndef __BCM2711_UART_H__
#define __BCM2711_UART_H__

#include <stdint.h>
#include <stdbool.h>

#include "perpheral/gpio.h"
#include "perpheral/interrupt.h"

#define BCM2711_UART0_BASE      (0xFE201000)

// Default UART0 clock
#define UART0_CLK               (48000000)

#define UART_IRQ_COUNT          (11)

typedef union __PL011_DR_REG{
    uint32_t value;

    struct {
        uint32_t Data   : 8;    // 0 ~ 7 bits
        uint32_t FE     : 1;    // 8 bit
        uint32_t PE     : 1;    // 9 bit
        uint32_t BE     : 1;    // 10 bit
        uint32_t OE     : 1;    // 11 bit
    };
} PL011_DR_REG;

typedef union __PL011_FR_REG{
    uint32_t value;

    struct {    
        uint32_t CTS    : 1;    // 0 bit
        uint32_t DSR    : 1;    // 1 bit
        uint32_t DCD    : 1;    // 2 bit
        uint32_t BUSY   : 1;    // 3 bit
        uint32_t RXFE   : 1;    // 4 bit
        uint32_t TXFF   : 1;    // 5 bit
        uint32_t RXFF   : 1;    // 6 bit
        uint32_t TXFE   : 1;    // 7 bit
        uint32_t RI     : 1;    // 8 bit
    };
} PL011_FR_REG;

typedef union __PL011_IBRD_REG{
    uint32_t value;

} PL011_IBRD_REG;

typedef union __PL011_FBRD_REG{
    uint32_t value;

} PL011_FBRD_REG;

typedef enum __PL011_WLEN{
	PL011_WLEN_8BITS	= 0b11,
	PL011_WLEN_7BITS	= 0b10,
	PL011_WLEN_6BITS	= 0b01,
	PL011_WLEN_5BITS	= 0b00,
} PL011_WLEN;

typedef union __PL011_LCRH_REG{
    uint32_t value;

    struct {
        uint32_t BRK    : 1;    // 0 bit
        uint32_t PEN    : 1;    // 1 bit
        uint32_t EPS    : 1;    // 2 bit
        uint32_t STP2   : 1;    // 3 bit
        uint32_t FEN	: 1;    // 4 bit
        uint32_t WLEN	: 2;    // 5 ~ 6 bit
        uint32_t SPS	: 1;    // 7 bit
    };
} PL011_LCRH_REG;

typedef union __PL011_CR_REG{
    uint32_t value;

    struct {
        uint32_t UARTEN 	: 1;	// 0 bit
		uint32_t SIREN 		: 1;	// 1 bit
		uint32_t SIRLP 		: 1;	// 2 bit
		uint32_t 			: 3;	// 3 ~ 6 bits : reservd
		uint32_t LBE 		: 1;	// 7 bit
		uint32_t TXE 		: 1;	// 8 bit
		uint32_t RXE 		: 1;	// 9 bit
		uint32_t DTR 		: 1;	// 10 bit
		uint32_t RTS 		: 1;	// 11 bit
		uint32_t OUT1 		: 1;	// 12 bit
		uint32_t OUT2 		: 1;	// 13 bit
		uint32_t RTSEN 		: 1;	// 14 bit
		uint32_t CTSEN 		: 1;	// 15 bit
    };
} PL011_CR_REG;

typedef union __PL011_IFLS_REG{
    uint32_t value;

    struct {
        uint32_t TXIFLSEL	: 3;	// 0 ~ 2 bits
		uint32_t RXIFLSEL	: 3;	// 3 ~ 5 bits
		uint32_t TXIFPSEL	: 3;	// 6 ~ 8 bits
		uint32_t RXIFPSEL	: 3;	// 9 ~ 11 bits
    };
} PL011_IFLS_REG;

typedef enum __PL011_IMSC{
	PL011_IMSC_RIMIM 	= (0x01 << 0),
	PL011_IMSC_CTSMIM	= (0x01 << 1),
	PL011_IMSC_DCDMIM	= (0x01 << 2),
	PL011_IMSC_DSRMIM	= (0x01 << 3),
	PL011_IMSC_RXIM		= (0x01 << 4),
	PL011_IMSC_TXIM 	= (0x01 << 5),
	PL011_IMSC_RTIM 	= (0x01 << 6),
	PL011_IMSC_FEIM 	= (0x01 << 7),
	PL011_IMSC_PEIM 	= (0x01 << 8),
	PL011_IMSC_BEIM 	= (0x01 << 9),
	PL011_IMSC_OEIM 	= (0x01 << 10),
} PL011_IMSC;

typedef union __PL011_IMSC_REG{
    uint32_t value;

    struct {
        uint32_t RIMIM 		: 1;	// 0 bit
		uint32_t CTSMIM 	: 1;	// 1 bit
		uint32_t DCDMIM 	: 1;	// 2 bit
		uint32_t DSRMIM 	: 1;	// 3 bit
		uint32_t RXIM		: 3;	// 4 bit
		uint32_t TXIM 		: 1;	// 5 bit
		uint32_t RTIM 		: 1;	// 6 bit
		uint32_t FEIM 		: 1;	// 7 bit
		uint32_t PEIM 		: 1;	// 8 bit
		uint32_t BEIM 		: 1;	// 9 bit
		uint32_t OEIM 		: 1;	// 10 bit
    };
} PL011_IMSC_REG;

typedef union __PL011_RIS_REG{
    uint32_t value;

	// need to implement the member various with bit field
} PL011_RIS_REG;

typedef union __PL011_MIS_REG{
    uint32_t value;

    struct {
        uint32_t RIMMIS 	: 1;	// 0 bit
		uint32_t CTSMMIS 	: 1;	// 1 bit
		uint32_t DCDMMIS 	: 1;	// 2 bit
		uint32_t DSRMMIS 	: 1;	// 3 bit
		uint32_t RXMIS		: 3;	// 4 bit
		uint32_t TXMIS 		: 1;	// 5 bit
		uint32_t RTMIS 		: 1;	// 6 bit
		uint32_t FEMIS 		: 1;	// 7 bit
		uint32_t PEMIS 		: 1;	// 8 bit
		uint32_t BEMIS 		: 1;	// 9 bit
		uint32_t OEMIS 		: 1;	// 10 bit
    };
} PL011_MIS_REG;

typedef union __PL011_ICR_REG{
    uint32_t value;

    struct {
        uint32_t RIMIC 		: 1;	// 0 bit
		uint32_t CTSMIC 	: 1;	// 1 bit
		uint32_t DCDMIC 	: 1;	// 2 bit
		uint32_t DSRMIC 	: 1;	// 3 bit
		uint32_t RXIC		: 3;	// 4 bit
		uint32_t TXIC 		: 1;	// 5 bit
		uint32_t RTIC 		: 1;	// 6 bit
		uint32_t FEIC 		: 1;	// 7 bit
		uint32_t PEIC 		: 1;	// 8 bit
		uint32_t BEIC 		: 1;	// 9 bit
		uint32_t OEIC 		: 1;	// 10 bit
    };
} PL011_ICR_REG;

typedef volatile struct __PL011{
	PL011_DR_REG	DR;				// Offset : 0x00
	uint32_t		PSRECR;			// Offset : 0x04

    struct{ 
        uint32_t    :32;        	// Offset : 0x08
    };
	struct{ 
        uint32_t    :32;        	// Offset : 0x0C
    };
	struct{ 
        uint32_t    :32;        	// Offset : 0x10
    };
	struct{ 
        uint32_t    :32;        	// Offset : 0x14
    };

	PL011_FR_REG	FR;				// Offset : 0x18

	struct{ 
        uint32_t    :32;        	// Offset : 0x1C
    };

	uint32_t		ILPR;			// Offset : 0x20
	PL011_IBRD_REG	IBRD;			// Offset : 0x24
	PL011_FBRD_REG 	FBRD;			// Offset : 0x28
	PL011_LCRH_REG 	LCRH;			// Offset : 0x2C
	PL011_CR_REG	CR;				// Offset : 0x30
	PL011_IFLS_REG  IFLS;			// Offset : 0x34
	PL011_IMSC_REG 	IMSC;			// Offset : 0x38
	PL011_RIS_REG	RIS;			// Offset : 0x3C
	PL011_MIS_REG	MIS;			// Offset : 0x40
	PL011_ICR_REG 	ICR;			// Offset : 0x44
} PL011;

PL011* PL011_Initialize(uint32_t baudrate);
void PL011_EnableInterrupt(PL011* pl011,GIC400* gic400, PL011_IMSC uartIRQ, IRQ_Handler_Callback callback);

void PL011_SendWord(PL011* pl011,uint8_t data);
void PL011_SendString(PL011* pl011, const char * str);

uint8_t PL011_ReceiveWord(PL011* pl011);

#endif