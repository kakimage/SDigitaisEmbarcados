
#ifndef __LCD__
#define __LCD__

#include <inttypes.h>  

void lcd_init (uint8_t RS,  uint8_t E, uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7);
void lcd_envia_byte (uint8_t valor);
void lcd_escreve (char st[]);
void lcd_limpa_tela (void);
void lcd_desloca (void);
#endif
