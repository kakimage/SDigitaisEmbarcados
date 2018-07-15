#include <stdio.h>
#include "i2c.h"
#include "memoria.h"
#include "digital.h"

#include "tarefa.h"


#ifdef __LINUX__

void escreveBuffer ( uint16_t end, uint8_t *dados, int qtd)
{
	fseek(ARQUIVO_PARTICAO, end, SEEK_SET );
	fwrite(dados, 1, qtd, ARQUIVO_PARTICAO);
}
void escreveByte   ( uint16_t end, uint8_t dado)
{
	fseek(ARQUIVO_PARTICAO, end, SEEK_SET );
	fputc(dado, ARQUIVO_PARTICAO);
}
void leBuffer  ( uint16_t end, uint8_t  *dados, int qtd)
{
	fseek(ARQUIVO_PARTICAO, end, SEEK_SET );
	fread((void *) dados, 1, qtd, ARQUIVO_PARTICAO);
}
uint8_t leByte ( uint16_t end)
{
	fseek(ARQUIVO_PARTICAO, end, SEEK_SET );
	uint8_t dado = fgetc(ARQUIVO_PARTICAO);
	return dado;
}

#else

void escreveBuffer ( uint16_t end, uint8_t *dados, int qtd)
{
   for (int x=0; x< qtd;x++) escreveByte (end+x,dados[x]);
}
void escreveByte   ( uint16_t end, uint8_t dado)
{
	//printf("escreveByte\n");
	i2c_start();
		i2c_escreve_byte(0xa0);
		i2c_escreve_byte(end>>8);
		i2c_escreve_byte(end);
		i2c_escreve_byte(dado);
	i2c_stop();
	delay_ms(100);
}

void leBuffer  ( uint16_t end, uint8_t  *dados, int qtd)
{
	for (int x=0;x <qtd;x++) dados[x] = leByte(end+x);
} 
uint8_t leByte ( uint16_t end)
{
	uint8_t b;
		//printf("leByte\n");
	i2c_start();
		i2c_escreve_byte(0xa0);
		i2c_escreve_byte(end>>8);
		i2c_escreve_byte(end);
	i2c_start();
		i2c_escreve_byte(0xa1);
		b = i2c_le_byte();
		i2c_stop();
	return b;
}

void memoriaInit(void)
{
 i2c_init(PIN0_28, PIN0_27);
}

#endif
