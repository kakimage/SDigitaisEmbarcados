#ifndef _TECLADO_
#define _TECLADO_
#include <stdint.h>


#define TECLADO_C0 PIN2_00
#define TECLADO_C1 PIN2_01
#define TECLADO_C2 PIN2_02
#define TECLADO_C3 PIN2_03

#define TECLADO_L0 PIN2_04
#define TECLADO_L1 PIN2_05
#define TECLADO_L2 PIN2_06
#define TECLADO_L3 PIN2_07


uint8_t le_teclado (void);
void configura_teclado (void);


#endif

