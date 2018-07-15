

#ifndef _DIGITAL_
#include <inttypes.h>
#include "LPC17xx.h"
#define _DIGITAL_



#define TRUE 1
#define FALSE 0

#define HIGH 1
#define LOW 0

#define INPUT 0
#define OUTPUT 1

#define PIN_4_29  ((4<<5)|29)
#define PIN_1_23  ((1<<5)|23)


void pinMode( uint16_t portbit, uint8_t bitVal );
void digitalWrite( uint16_t portbit, uint8_t valor );
uint8_t digitalRead (uint16_t portbit);


#endif
