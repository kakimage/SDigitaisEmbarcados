
#include <stdint.h>

void memoria_init (void);
void memoria_flush (void);
uint16_t memoria_write (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t qtd);
uint16_t memoria_read (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t qtd);
