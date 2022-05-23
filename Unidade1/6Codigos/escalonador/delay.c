#include "delay.h"
#include <stdint.h>

volatile uint32_t delay;

void delay_ms(void)
{

    for(delay = 0; delay < 40000; delay++) {
        __asm("NOP");
    }
}