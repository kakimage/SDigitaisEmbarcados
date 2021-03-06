#ifndef _DIGITAL_
#define _DIGITAL_


#include <inttypes.h> 
#include <avr/io.h>

#define HIGH 1U
#define LOW 0U

#define INPUT 0
#define OUTPUT 1

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13


void digitalWrite( uint8_t pino, uint8_t valor);
unsigned char digitalRead (int pino);
void pinMode (int8_t pino, int8_t valor);


#endif



