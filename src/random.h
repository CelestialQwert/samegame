#include <stdint.h>

#ifndef __random_INCLUDE
#define __random_INCLUDE

extern uint16_t seed;
void init_random();
uint8_t randuint8(uint8_t max);

#endif