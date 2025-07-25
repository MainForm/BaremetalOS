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

#endif