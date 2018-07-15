#ifndef _TIMER_
#define _TIMER_
#include "LPC17xx.h"
#define bit16 (1<<16)
#define bit26 (1<<26)
#define bit27 (1<<27)
#define bit1  (1<<1)
#define bit0  (1<<0)
#define bit3  (1<<3)
void timer_init(void (*f)(void), uint32_t freq);



#endif
