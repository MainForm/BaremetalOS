#include <stdlib.h>

#include "HAL_GPIO.h"
#include "HAL_UART.h"
#include "HAL_GIC.h"
#include "HAL_GPTimer.h"
#include "interrupt.h"

#define UART0               (0)
#define TIMER0              (0)

#define IRQ_UART            (96 + 57)
#define IRQ_TIMER0          (64 +  0)

#define LED_PIN				(21)
#define UART0_TX			(14)
#define UART0_RX			(15)

static inline uintptr_t get_sp(void) {
    uintptr_t sp;
    __asm__ volatile (
        "MOV %0, sp\n"
        : "=r"(sp)
    );
    return sp;
}

void delay(volatile uint32_t i){
    while(i-- > 0);
}

void UART_IRQ_Rx_Handler(){
    uint8_t data = HAL_UART_ReceiveWord(UART0);

    HAL_UART_SendWord(UART0,data);
}

void UART_Timer0_handler(){
    static int count = 0;

    if(count >= 1000){
        char buf[10];
        uintptr_t address_sp = get_sp();

        itoa(address_sp,buf,16);
        HAL_UART_SendString(UART0,"sp in IRQ : ");
        HAL_UART_SendString(UART0,buf);
        HAL_UART_SendWord(UART0,'\n');

        count = 0;
    }

    ++count;

    HAL_GPTimer_ClearInterrupt(TIMER0);
}

int main(){
    // char buf[10];


    // // Initializing GIC to enable IRQs
    // HAL_GIC_Initialize();
    // HAL_GIC_EnableInterrupt(IRQ_UART);
    // IRQ_Enable();
    // // Initializing UART
    // HAL_UART_Initialize(UART0,115200);
    // HAL_UART_EnableInterrupt(UART0,UART_IRQ_RX);

    // // Initailizing Timer0
    // HAL_GPTimer_Initialize(TIMER0);
    // HAL_GPTimer_SetTimerSize(TIMER0, GPTIMER_SIZE_32BITS);
    // HAL_GPTimer_SetTimerPrescale(TIMER0, GPTIMER_PRESCALE_1);
    // HAL_GPTimer_EnableInterrupt(TIMER0, true);
    // HAL_GPTimer_SetTimerLoad(TIMER0,1000);
    // HAL_GPTimer_EnableTimer(TIMER0, true);

    // // Set the GPIO to use Rx, Tx for UART
    // HAL_GPIO_SetFunction(UART0_TX,GPIO_FUNC_ALT0);
    // HAL_GPIO_SetFunction(UART0_RX,GPIO_FUNC_ALT0);

    // // Set the LED pin to output
    // HAL_GPIO_SetFunction(LED_PIN,GPIO_FUNC_OUTPUT);

    // IRQ_AttachInterrupt(IRQ_UART,UART_IRQ_Rx_Handler);
    // IRQ_AttachInterrupt(IRQ_TIMER0,UART_Timer0_handler);

    // HAL_GPIO_SetOutput(LED_PIN,HIGH);

    // while(1){
    //     uintptr_t address_sp = get_sp();
    //     itoa(address_sp,buf,16);
    //     HAL_UART_SendString(UART0,"sp in main func : ");
    //     HAL_UART_SendString(UART0,buf);
    //     HAL_UART_SendWord(UART0,'\n');

    //     delay(0x400000);
    // }

    while(1){}

    return 0;
}