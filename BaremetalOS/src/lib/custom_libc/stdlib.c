#include "custom_libc/stdlib.h"
#include <stdint.h>
#include <stdbool.h>

char* itoa(uint32_t value,char* str,int base){
    int idx = 0;
    int ridx = 0;
    char temp = 0;

    if(value == 0){
        str[0] = '0';
        str[1] = '\0';
        
        return str;
    }

    while(value > 0){
        str[idx] = value % base;

        str[idx] += (str[idx] < 10 ? '0' : 'A' - 10);

        value /= base;
        idx += 1;
    }

    str[idx] = '\0';
    idx -= 1;

    while(idx > ridx){
        temp = str[idx];
        str[idx] = str[ridx];
        str[ridx] = temp;

        idx -= 1;
        ridx += 1;
    }

    return str;
}