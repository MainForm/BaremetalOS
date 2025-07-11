#include <stdint.h>

#include "bcm2711_peripheral.h"

void write32(volatile void *dst, uint32_t val){
    volatile uint32_t *dst_u = (volatile uint32_t *)dst;
    *dst_u = val;
}

uint32_t read32(volatile void *src){
    volatile uint32_t *src_u = (volatile uint32_t *)src;
    return *src_u;
}

int main(){
    uint32_t gpfsel2 = read32(BCM2711_GPFSE2);
    volatile int i = 0;

    // set the 21 pin to output
    gpfsel2 &= ~(7 << 3);
    gpfsel2 |= (1 << 3);
    write32(BCM2711_GPFSE2, gpfsel2);

    while(1){
        // set value of 21pin to high
        write32(BCM2711_GPSET0, 1 << 21);

        i = 0;
        while(i < 0x100000){
            i++;
        }

        // set value of 21pin to low
        write32(BCM2711_GPCLR0, 1 << 21);

        i = 0;
        while(i < 0x100000){
            i++;
        }
    }

    return 0;
}