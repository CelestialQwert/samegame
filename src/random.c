#include <rand.h>
#include <stdint.h>
#include <gb/gb.h>

#include "random.h"
#include "vars.h"

uint16_t seed = 0;

void init_random(){
    seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
}

uint8_t randuint8(uint8_t max){
    j = max;
    // j is max rounded up to next 2^n
    j--;
    j |= j >> 1;
    j |= j >> 2;
    j |= j >> 4;
    j++;
    i = max;
    while (i>max-1){
        i = ((uint8_t)rand()) & (j-1);
    }
    return i;
}