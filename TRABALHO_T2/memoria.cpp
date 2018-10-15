
#include "memoria.h"

#ifdef _USA_ARM_
#include "digital.h"

void memoria_init (void)
{
	i2c_configura(PIN_0_27, PIN_0_28);

}

uint16_t memoria_write (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t qtd)
{
	uint16_t tmp;

	tmp =  i2c_sequencial_write ( dispositivo,  end,  b,  qtd);
	return tmp;

}

uint16_t memoria_read (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t qtd)
{
	uint16_t tmp;
	tmp = i2c_sequencial_read ( dispositivo,  end,  b,  qtd);
	return tmp;
}

#else
#include <stdio.h>
FILE *A;
void memoria_init (void)
{
	A = fopen ("PARTICAO.BIN", 	"r+");
	if (A == NULL)
	{
		A = fopen ("PARTICAO.BIN","w+");
		for (int x=0;x<8192;x++)
			fputc(0, A);
	}
}
uint16_t memoria_write (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t qtd)
{
	fseek(A, end, SEEK_SET);
	return fwrite(b, 1, qtd, A);

}
uint16_t memoria_read (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t qtd)
{
	fseek(A, end, SEEK_SET);
	return fread(b, 1, qtd, A);
}
#endif

