#ifndef __REALVIEW_PB_A8_PERIPHERAL__
#define __REALVIEW_PB_A8_PERIPHERAL__

#include <stddef.h>
#include <stdint.h>

// Table 4.89. UART implementation
// return the -1 when trying to access the invailed irq number
#define REALVIEW_PB_A8_UART_BASE(UART_NUM)     (    \
    (UART_NUM == 0 ? 0x10009000 :                   \
    (UART_NUM == 1 ? 0x1000A000 :                   \
    (UART_NUM == 2 ? 0x1000B000 :                   \
    (UART_NUM == 3 ? 0x1000C000 :                   \
    (uintptr_t)NULL ))))                            \
)

// Default UART clock
#define UART_CLK                       (24000000)

// Table 4.43. Generic Interrupt Controller implementation
// return the -1 when trying to access the invailed GIC number
#define REALVIEW_PB_A8_GIC_BASE(GIC_NUM)      (    \
    (GIC_NUM == 0 ? 0x1E000000 :                   \
    (GIC_NUM == 1 ? 0x1E010000 :                   \
    (GIC_NUM == 2 ? 0x1E020000 :                   \
    (GIC_NUM == 3 ? 0x1E030000 :                   \
    (uintptr_t)NULL ))))                           \
)

#define REALVIEW_PB_A8_GIC_UART_IRQ(UART_NUM)     (     \
    (UART_NUM == 0 ? 44 :                               \
    (UART_NUM == 1 ? 45 :                               \
    (UART_NUM == 2 ? 46 :                               \
    (UART_NUM == 3 ? 47 :                               \
    (uintptr_t)NULL ))))                                \
)

#define REALVIEW_PB_A8_GIC_GPTIMER_IRQ(GPTIMER_NUM)     (   \
    (GPTIMER_NUM == 0 || GPTIMER_NUM == 1 ? 36 :            \
    (GPTIMER_NUM == 2 || GPTIMER_NUM == 3 ? 37 :            \
    (GPTIMER_NUM == 4 || GPTIMER_NUM == 5 ? 73 :            \
    (GPTIMER_NUM == 6 || GPTIMER_NUM == 7 ? 74 :            \
    (uintptr_t)NULL ))))                                    \
)

// Table 4-88 Timer implementation
// return the -1 when trying to access the invailed timer number
#define REALVIEW_PB_A8_GPTIMER_BASE(GIC_NUM)      (    \
    (GIC_NUM == 0 || GIC_NUM == 1 ? 0x10011000 :   \
    (GIC_NUM == 2 || GIC_NUM == 3 ? 0x10012000 :   \
    (GIC_NUM == 4 || GIC_NUM == 5 ? 0x10018000 :   \
    (GIC_NUM == 6 || GIC_NUM == 7 ? 0x10019000 :   \
    (uintptr_t)NULL ))))                           \
)

#define REAELVIEW_PB_A8_GPTIMER_COUNT       (8)

// Default Timer clock is REFCLK(32.769kHz)
// To use the 1 MHz TIMCLK, set bit 15 of SYS_CTRL0 in the SP810 System Controller
#define REFCLK      (32768)     // 32.768kHz
#define TIMCLK      (1000000)   // 1MHz

#endif