
#ifndef __SEG__
#define __SEG__
#include <stdint.h>

void configuraDisplay( uint8_t pSEGA,  uint8_t pSEGB, uint8_t pSEGC,  uint8_t pSEGD,  uint8_t pSEGE,  uint8_t pSEGF,  uint8_t pSEGG,  uint8_t pDISPLAY0, uint8_t pDISPLAY1,  uint8_t pDISPLAY2,  uint8_t pDISPLAY3);
void mostraDisplay (uint8_t numero_display, uint8_t valor);
void mostra (uint16_t valor);


#endif
