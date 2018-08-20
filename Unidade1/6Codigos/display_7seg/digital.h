#ifndef _DIGITAL_
#define _DIGITAL_

#include <stdint.h>

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define PIN0_00 ((0<<5)|0)
#define PIN0_01 ((0<<5)|1)
#define PIN0_02 ((0<<5)|2)
#define PIN0_03 ((0<<5)|3)

#define PIN1_08 ((1<<5)|8)


#define PIN1_23 ((1<<5)|23)
#define PIN1_24 ((1<<5)|24)
#define PIN1_25 ((1<<5)|25)
#define PIN1_26 ((1<<5)|26)
#define SW0 PIN1_23
#define SW1 PIN1_24
#define SW2 PIN1_25
#define SW3 PIN1_26

#define PIN0_04 ((0<<5)|4)
#define PIN0_05 ((0<<5)|5)
#define PIN0_06 ((0<<5)|6)
#define PIN0_07 ((0<<5)|7)
#define PIN0_08 ((0<<5)|8)
#define PIN0_09 ((0<<5)|9)
#define PIN0_10 ((0<<5)|10)


#define SEGA PIN0_04
#define SEGB PIN0_05
#define SEGC PIN0_06
#define SEGD PIN0_07
#define SEGE PIN0_08
#define SEGF PIN0_09
#define SEGG PIN0_10


#define PIN3_25 ((3<<5)|25)


#define PIN3_26 ((3<<5)|26)




#define PIN2_11 ((2<<5)|11)

#define PIN4_28 ((4<<5)|28)
#define PIN4_29 ((4<<5)|29)

void    pinMode      (uint32_t pino, uint8_t modo);
void    digitalWrite (uint32_t pino, uint8_t valor);
uint8_t digitalRead  (uint32_t pino);









#endif
