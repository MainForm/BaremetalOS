#ifndef __BCM2711_PERIPHERAL__
#define __BCM2711_PERIPHERAL__

#include <stddef.h>
#include <stdint.h>
#include "Timer/SP804.h"

// Default APB Clock of BCM2711 :       250MHz
#define BCM2711_APB_CLOCK               (250000000)

// ────────────────────────────────────────────
// GPIO peripheral
// ────────────────────────────────────────────

// GPIO peripheral base address
#define BCM2711_GPIO_BASE               (0xFE200000)

// ────────────────────────────────────────────
// UART peripheral
// ────────────────────────────────────────────

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

// ────────────────────────────────────────────
// GIC interrupt peripheral
// ────────────────────────────────────────────

// GIC base address
#define BCM2711_GIC_BASE                (0xFF840000)
#define BCM2711_GIC_COUNT               (1)

// This is based on “6.3. GIC-400 interrupt controller” in the bcm2711-peripherals Manual.
// You can check the base number of the VideoCore peripheral IRQs.

#define IRQ_ARMC_BASE       (64)
#define IRQ_ARMC_GPTIMER    (IRQ_ARMC_BASE + 0)

#define IRQ_VC_BASE         (96)
#define IRQ_VC_UART         (IRQ_VC_BASE + 57)

#define IRQ_SYSTEM_TIMER0   (IRQ_VC_BASE + 0)
#define IRQ_SYSTEM_TIMER1   (IRQ_VC_BASE + 1)
#define IRQ_SYSTEM_TIMER2   (IRQ_VC_BASE + 2)
#define IRQ_SYSTEM_TIMER3   (IRQ_VC_BASE + 3)

#define BCM2711_GIC_UART_IRQ(UART_NUM)     (    \
    (UART_NUM == 0 ? IRQ_VC_UART :              \
    (UART_NUM == 2 ? IRQ_VC_UART :              \
    (UART_NUM == 3 ? IRQ_VC_UART :              \
    (UART_NUM == 4 ? IRQ_VC_UART :              \
    (UART_NUM == 5 ? IRQ_VC_UART :              \
    (uintptr_t)NULL )))))                       \
)

#define BCM2711_GIC_SYSTEM_TIMER_IRQ(TIMER_NUM)  (      \
    (TIMER_NUM == 0 ? IRQ_SYSTEM_TIMER0 :               \
    (TIMER_NUM == 1 ? IRQ_SYSTEM_TIMER1 :               \
    (TIMER_NUM == 2 ? IRQ_SYSTEM_TIMER2 :               \
    (TIMER_NUM == 3 ? IRQ_SYSTEM_TIMER3 :               \
    (uintptr_t)NULL ))))                                \
)

#define BCM2711_GIC_GPTIMER_IRQ(GPTIMER_NUM)     (      \
    (GPTIMER_NUM == 0 ? IRQ_ARMC_GPTIMER :              \
    (uintptr_t)NULL )                                   \
)

// ────────────────────────────────────────────
// System Timer peripheral
// ────────────────────────────────────────────

#define BCM2711_SYSTEM_TIMER_BASE               (0xFE003000)

#define BCM2711_SYSTEM_TIMER_COUNT              (4)

// ────────────────────────────────────────────
// Timer peripheral
// ────────────────────────────────────────────

// Timer base address
#define BCM2711_SP804_BASE              (0xFE00B000)
#define BCM2711_SP804_TIMER0_BASE       (BCM2711_SP804_BASE + 0x400)

typedef union __BCM2711_SP804_TimerControl_REG{
    uint32_t value;

    struct {
        uint32_t                    :  1;
        uint32_t TimerSize          :  1;
        uint32_t TimerPre           :  2;
        uint32_t                    :  1;
        uint32_t IntEnable          :  1;
        uint32_t                    :  1;
        uint32_t TimerEn            :  1;
        uint32_t DebugHalt          :  1;
        uint32_t EnableFreeRunning  :  1;
        uint32_t                    :  6;
        uint32_t FreeDiv            :  8;
        uint32_t                    :  8;
    };
} BCM2711_SP804_TimerControl_REG;

typedef union __BCM2711_SP804_PREDIV_REG{
    uint32_t value;

    struct {
        uint32_t PREDIV     : 10;
    };
} BCM2711_SP804_PREDIV_REG;

typedef union __BCM2711_SP804_FREECNT_REG{
    uint32_t value;
} BCM2711_SP804_FREECNT_REG;

typedef volatile struct __BCM2711_SP804_Timer{
    SP804_TimerLoad_REG             TimerLoad;      // Offset : 0x0000
    SP804_TimerValue_REG            TimerValue;     // Offset : 0x0004
    // only for BCM2711 register
    BCM2711_SP804_TimerControl_REG  TimerControl;   // Offset : 0x0008

    SP804_TimerIntClr_REG           TimerIntClr;    // Offset : 0x000C
    SP804_TimerRIS_REG              TimerRIS;       // Offset : 0x0010
    SP804_TimerMIS_REG              TimerMIS;       // Offset : 0x0014
    SP804_TimerBGLoad_REG           TimerBGLoad;    // Offset : 0x0018

    // only for BCM2711 register
    BCM2711_SP804_PREDIV_REG        PREDIV;         // Offset : 0x001C
    BCM2711_SP804_FREECNT_REG       FREECNT;        // Offset : 0x0020

} BCM2711_SP804_Timer;

#endif