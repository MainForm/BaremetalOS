#ifndef __BM_OS_STDIO_H__
#define __BM_OS_STDIO_H__

#include <stdint.h>
#include <stdarg.h>

// Function to print formatted output to a specified by uartID.
// The format specifiers supported are:
// %s - string
// %d - decimal integer
// %b - binary integer
// %x - hexadecimal integer
// %c - character
// %% - percent sign
// If an unsupported format specifier is encountered, it prints a '?' character.
void uprintf(uint32_t uartID, const char* fmt, ...);

#endif // __BM_OS_STDIO_H__