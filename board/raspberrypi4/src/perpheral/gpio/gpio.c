#include "bcm2711_peripheral.h"
#include "perpheral/gpio.h"

#include "memory.h"

#define SELECT_GPFSEL(index)    (BCM2711_GPFSEL##index)

void GPIO_SelectFunction(uint32_t pin, uint32_t function){
    uint32_t regIndex = (pin / 10);
    uint32_t shiftCount = (pin % 10) * 3;

    WRITE_MEMROY_32(BCM2711_GPFSEL0 + regIndex,(function & 0x07) << shiftCount);
}

void GPIO_SetOutput(uint32_t pin,uint32_t value){
    volatile uint32_t * Reg = (value == 0 ? BCM2711_GPCLR0 : BCM2711_GPSET0);

    if(pin > 31){
        Reg += 2;
        pin -= 32;
    }

    WRITE_MEMROY_32(Reg,(1 << pin));
}