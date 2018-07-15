
#ifndef _TECLADO_
#define _TECLADO_
#include <stdint.h>


#define NENHUMA_TECLA 100
#define C0 PIN2_00
#define C1 PIN2_01
#define C2 PIN2_02
#define C3 PIN2_03

#define L0 PIN2_04
#define L1 PIN2_05
#define L2 PIN2_06
#define L3 PIN2_07
 
#define BLOQ 1
#define NBLOQ 0
 
 


void configura_teclado(void);
uint8_t le_teclado(uint8_t bloq);

#endif
