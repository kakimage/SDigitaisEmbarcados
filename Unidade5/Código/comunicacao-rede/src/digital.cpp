
#include "digital.h"


IO pinos;
void IO::mapeia_pinos (uint8_t pino )
{
	if (pino >=0 && pino <=7)
	{ 
		DIRECAO = &DDRD;
		ENTRADA = &PIND;
		SAIDA   = &PORTD;
		BIT     = pino;
	}
	else
	{
		if (pino>=8 && pino <=13)
		{
			DIRECAO = &DDRB;
			ENTRADA = &PINB;
			SAIDA   = &PORTB;
			BIT     = pino - 8;
		}
		else {
			DIRECAO = &DDRC;
			ENTRADA = &PINC;
			SAIDA   = &PORTC;
			BIT     = pino - 14;
		}
	}
}

void IO::pinMode (uint8_t pino, uint8_t funcao )
{
	mapeia_pinos (pino);

	if (funcao==INPUT) 	*DIRECAO = *DIRECAO & ~(1<<BIT);
	else *DIRECAO = *DIRECAO | 1<<BIT; 
}

void IO::digitalWrite( uint8_t pino, uint8_t valor)
{
	mapeia_pinos (pino);
	valor = valor & 1;
	if (valor) *SAIDA = *SAIDA | (1<<BIT);
	else *SAIDA = *SAIDA & ~(1<<BIT);
}

uint8_t IO::digitalRead( uint8_t pino )
{
	mapeia_pinos (pino);
	return ( ((*ENTRADA)>>BIT) & 1 );
}
