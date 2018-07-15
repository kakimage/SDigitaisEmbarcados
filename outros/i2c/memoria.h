
#ifndef __MEMORIA__
#define __MEMORIA__

void escreveByte ( uint16_t end, uint8_t dado);
uint8_t leByte ( uint16_t end);
void memoriaInit(void);
void escreveBuffer ( uint16_t end, uint8_t *dados, int qtd);
void escreveByte   ( uint16_t end, uint8_t dado);
void leBuffer  ( uint16_t end, uint8_t  *dados, int qtd);
#endif
