#include <inttypes.h>
#include "memoria_i2c.h"
#include "i2c_software.h"
#include "digital.h"
#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

uint8_t DISPOSITIVO;
uint8_t TAM_PAGINA;


void memoria_configura(uint8_t dispositivo, uint8_t tamanho_pagina)
{
	DISPOSITIVO = dispositivo;
	TAM_PAGINA  = tamanho_pagina;

	i2c_configura (PIN_0_27, PIN_0_28);
	//i2c_configura (PIN_2_05, PIN_1_31);
	i2c_start();
	i2c_stop();
}

void read_bytes (uint8_t *b, uint16_t tam, uint16_t end)
{

	uint16_t R, qtd, contador=0;

	while (tam>0)
	{
		R = (end / TAM_PAGINA) * TAM_PAGINA +TAM_PAGINA;
		qtd = i2c_sequencial_read (DISPOSITIVO, end, b+contador, MIN(R - end, tam));
		contador+=qtd;
		end+=qtd;  tam-=qtd;
	}

	/*for (x=0;x<tam;x++)
	{
		b[x]=i2c_le_byte(DISPOSITIVO, end+x);
	}*/
	
}

void write_bytes (uint8_t *b, uint16_t tam, uint16_t end)
{
	//uint16_t x;
	uint16_t R, qtd,  contador=0;

	while (tam>0)
	{
		R = (end / TAM_PAGINA) * TAM_PAGINA +TAM_PAGINA;
		qtd = i2c_sequencial_write (DISPOSITIVO, end, b+contador, MIN(R - end, tam));
		end+=qtd;  tam-=qtd;
		contador+=qtd;
	}
	/*for (x=0;x<tam;x++)
	{
		i2c_escreve_byte(DISPOSITIVO, end+x,b[x]);
	}*/

}
