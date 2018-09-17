#ifndef __TECLADO__
#define __TECLADO__
#include <stdint.h>

#define C0 PIN_2_00
#define C1 PIN_2_01
#define C2 PIN_2_02
#define C3 PIN_2_03

#define L0 PIN_2_04
#define L1 PIN_2_05
#define L2 PIN_2_06
#define L3 PIN_2_07

#define BLQ 1
#define NBLQ 0

void init_keyboard(void);
uint8_t leia_tecla (uint8_t tipo);


#endif