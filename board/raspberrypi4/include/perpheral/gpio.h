#ifndef __BCM2711_GPIO_H__
#define __BCM2711_GPIO_H__

#include <stdint.h>
#include <stdbool.h>

#define BCM2711_GPIO_BASE                   (0xFE200000)

typedef enum __FSEL_FUNC{
    FSEL_FUNC_INPUT =    0b000,
    FSEL_FUNC_OUTPUT =   0b001,
    FSEL_FUNC_ALT0 =     0b100,
    FSEL_FUNC_ALT1 =     0b101,
    FSEL_FUNC_ALT2 =     0b110,
    FSEL_FUNC_ALT3 =     0b111,
    FSEL_FUNC_ALT4 =     0b011,
    FSEL_FUNC_ALT5 =     0b010,
} FSEL_FUNC;

typedef union __GPFSEL0_REG{
    uint32_t value;

    struct {
        uint32_t FSEL0 : 3;
        uint32_t FSEL1 : 3;
        uint32_t FSEL2 : 3;
        uint32_t FSEL3 : 3;
        uint32_t FSEL4 : 3;
        uint32_t FSEL5 : 3;
        uint32_t FSEL6 : 3;
        uint32_t FSEL7 : 3;
        uint32_t FSEL8 : 3;
        uint32_t FSEL9 : 3;
    };
} GPFSEL0_REG;

typedef union __GPFSEL1_REG{
    uint32_t value;

    struct {
        uint32_t FSEL10 : 3;
        uint32_t FSEL11 : 3;
        uint32_t FSEL12 : 3;
        uint32_t FSEL13 : 3;
        uint32_t FSEL14 : 3;
        uint32_t FSEL15 : 3;
        uint32_t FSEL16 : 3;
        uint32_t FSEL17 : 3;
        uint32_t FSEL18 : 3;
        uint32_t FSEL19 : 3;
    };
} GPFSEL1_REG;

typedef union __GPFSEL2_REG{
    uint32_t value;

    struct {
        uint32_t FSEL20 : 3;
        uint32_t FSEL21 : 3;
        uint32_t FSEL22 : 3;
        uint32_t FSEL23 : 3;
        uint32_t FSEL24 : 3;
        uint32_t FSEL25 : 3;
        uint32_t FSEL26 : 3;
        uint32_t FSEL27 : 3;
        uint32_t FSEL28 : 3;
        uint32_t FSEL29 : 3;
    };
} GPFSEL2_REG;

typedef union __GPFSEL3_REG{
    uint32_t value;

    struct {
        uint32_t FSEL30 : 3;
        uint32_t FSEL31 : 3;
        uint32_t FSEL32 : 3;
        uint32_t FSEL33 : 3;
        uint32_t FSEL34 : 3;
        uint32_t FSEL35 : 3;
        uint32_t FSEL36 : 3;
        uint32_t FSEL37 : 3;
        uint32_t FSEL38 : 3;
        uint32_t FSEL39 : 3;
    };
} GPFSEL3_REG;

typedef union __GPFSEL4_REG{
    uint32_t value;

    struct {
        uint32_t FSEL40 : 3;
        uint32_t FSEL41 : 3;
        uint32_t FSEL42 : 3;
        uint32_t FSEL43 : 3;
        uint32_t FSEL44 : 3;
        uint32_t FSEL45 : 3;
        uint32_t FSEL46 : 3;
        uint32_t FSEL47 : 3;
        uint32_t FSEL48 : 3;
        uint32_t FSEL49 : 3;
    };
} GPFSEL4_REG;

typedef union __GPFSEL5_REG{
    uint32_t value;

    struct {
        uint32_t FSEL50 : 3;
        uint32_t FSEL51 : 3;
        uint32_t FSEL52 : 3;
        uint32_t FSEL53 : 3;
        uint32_t FSEL54 : 3;
        uint32_t FSEL55 : 3;
        uint32_t FSEL56 : 3;
        uint32_t FSEL57 : 3;
    };
} GPFSEL5_REG;

typedef union __GPSET0_REG{
    uint32_t value;

    uint32_t SETn;
} GPSET0_REG;

typedef union __GPSET1_REG{
    uint32_t value;
    
    uint32_t SETn;
} GPSET1_REG;

typedef union __GPCLR0_REG{
    uint32_t value;
    
    uint32_t CLRn;
} GPCLR0_REG;

typedef union __GPCLR1_REG{
    uint32_t value;
    
    uint32_t CLRn;
} GPCLR1_REG;

typedef volatile struct __BCM2711_GPIO{
    GPFSEL0_REG GPFSEL0;        // Offset : 0x00
    GPFSEL1_REG GPFSEL1;        // Offset : 0x04    
    GPFSEL2_REG GPFSEL2;        // Offset : 0x08
    GPFSEL3_REG GPFSEL3;        // Offset : 0x0C
    GPFSEL4_REG GPFSEL4;        // Offset : 0x10
    GPFSEL5_REG GPFSEL5;        // Offset : 0x14

    struct{ 
        uint32_t    :32;        // Offset : 0x18
    };

    GPSET0_REG  GPSET0;         // Offset : 0x1C
    GPSET1_REG  GPSET1;         // Offset : 0x20

    struct{
        uint32_t    :32;        // Offset : 0x24
    };

    GPCLR0_REG  GPCLR0;         // Offset : 0x28
    GPCLR1_REG  GPCLR1;         // Offset : 0x2C

} BCM2711_GPIO;

BCM2711_GPIO* BCM2711_GPIO_Initialize();
void BCM2711_GPIO_SelectFunction(BCM2711_GPIO* gpio,uint32_t pin,FSEL_FUNC function);
void BCM2711_GPIO_SetOutput(BCM2711_GPIO* gpio,uint32_t pin,bool value);

#endif