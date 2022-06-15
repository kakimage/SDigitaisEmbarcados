
#include "memoria.h"

#ifdef _USA_ARM_
#include "digital.h"
#include "i2c_software.h"


#define MIN(a,b) (((a)<(b))?(a):(b))
void memoria_init (void)
{
	i2c_configura(PIN(0,27), PIN(0,28));

}

uint16_t memoria_write (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t tam)
{
	
	uint16_t R, qtd,  contador=0;

	while (tam>0)
	{
		R = (end / 32) * 32 +32;
		qtd = i2c_sequencial_write (dispositivo, end, b+contador, MIN(R - end, tam));
		end+=qtd;  tam-=qtd;
		contador+=qtd;
	}
	return contador;

}


uint16_t memoria_read (uint8_t dispositivo, uint16_t end, uint8_t b[], uint16_t tam)
{
	uint16_t R, qtd, contador=0;

	while (tam>0)
	{
		R = (end / 32) * 32 +32;
		qtd = i2c_sequencial_read (dispositivo, end, b+contador, MIN(R - end, tam));
		contador+=qtd;
		end+=qtd;  tam-=qtd;
	}
	return contador;
}
void memoria_flush (void)
{

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
		fseek(A, 0, SEEK_SET);
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
void memoria_flush (void)
{
	fclose(A);
}
#endif

