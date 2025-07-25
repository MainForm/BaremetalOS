#include "interrupt.h"

inline void IRQ_Enable(void)
{
    __asm__ volatile ("cpsie i" : : : "memory");
}