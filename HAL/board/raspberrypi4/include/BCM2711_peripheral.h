#ifndef __BCM2711_PERIPHERAL__
#define __BCM2711_PERIPHERAL__

#include <stddef.h>
#include <stdint.h>

// GPIO peripheral base address
#define BCM2711_GPIO_BASE               (0xFE200000)

// UART peripheral base address
// return the -1 when trying to access the invailed irq number
#define BCM2711_UART_BASE(UART_NUM)     (   \
    (UART_NUM == 0 ? 0xFE201000 :           \
    (UART_NUM == 2 ? 0xFE201400 :           \
    (UART_NUM == 3 ? 0xFE201600 :           \
    (UART_NUM == 4 ? 0xFE201800 :           \
    (UART_NUM == 5 ? 0xFE201a00 :           \
    (uintptr_t)NULL )))))                   \
)

// Default UART0 clock
#define UART_CLK                       (48000000)

#define UART_IRQ_COUNT                  (11)

// GIC base address
#define BCM2711_GIC_BASE                (0xFF840000)

// This is based on “6.3. GIC-400 interrupt controller” in the bcm2711-peripherals Manual.
// You can check the base number of the VideoCore peripheral IRQs.
#define IRQ_VC_IRQ_BASE     (96)
#define IRQ_UART_NUM        (57)

#endif