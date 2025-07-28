#include "custom_libc/stdio.h"
#include "custom_libc/stdlib.h"

#include "HAL_UART.h"

void uprintf(uint32_t uartID, const char* fmt, ...){
    // Buffer to hold the converted integer values temporarily.
    char buf[33];

    va_list args;
    va_start(args, fmt);

    while(*fmt){
        if (*fmt == '%' && *(fmt + 1)) {
            fmt++;
            switch (*fmt) {
                // Add brace to each case to define the scope of the variable.
                case 's': { // String
                    const char *s = va_arg(args, const char *);
                    HAL_UART_SendString(uartID, s);
                    break;
                }
                case 'd': { // deximal integer
                    int d = va_arg(args, int);

                    itoa(d, buf, 10);
                    HAL_UART_SendString(uartID, buf);
                    break;
                }
                case 'b': { // binary integer
                    int b= va_arg(args, int);

                    itoa(b, buf, 2);
                    HAL_UART_SendString(uartID, buf);
                    break;
                }
                case 'x': { // hexadecimal integer
                    unsigned int x = va_arg(args, unsigned int);

                    itoa(x, buf, 16);
                    HAL_UART_SendString(uartID, buf);
                    break;
                }
                case 'c': { // character
                    char c = (char)va_arg(args, int);
                    HAL_UART_SendWord(uartID, c);
                    break;
                }
                case '%': // Percent sign
                    HAL_UART_SendWord(uartID, '%');
                    break;
                default: // Unsupported format specifier
                    HAL_UART_SendWord(uartID, '?');
                    break;
            }
        } else {
            HAL_UART_SendWord(uartID, *fmt);
        }
        fmt++;
    }

    va_end(args);

    return;
}