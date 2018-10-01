#include <stdio.h>
#include "uart.h"
#include "interrupcao_externa.h"
#include "teclado.h"
#include "digital.h"

#define PINO_DADOS PIN_2_09

TECLADO teclado;
volatile unsigned char contador = 0;
volatile unsigned char tecla_lida=0;
volatile unsigned char existe_tecla_lida = 0;



unsigned char conversao (unsigned char cod)
{
	
	switch (cod)
	{
		case 0x1c:  return 'A';
		case 0x32:  return 'B';
		case 0x21:  return 'C';
        case 0x23:  return 'D';

					
	}
	return 200;
}

void meu_tratador_interrupcao_externa (void)
{
	static unsigned char dados=0;	static unsigned char ignore=0;

	switch (contador)
	{
		case 0: 
				//start
				dados = 0;
				break;
		case 1:// bits dados do menos significativo para o mais significativo
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
				dados = dados | (   digitalRead(PINO_DADOS) << (contador -1)   ); 
				break;
		case 9:	//paridade
				break;

		case 10:
				//stop bit

				contador=0;

				if (dados == 0xf0)
				{ 
					ignore = 1;
				}
				else
				{
					if (ignore==1) ignore =0;
					else
					{
						tecla_lida        = conversao(dados);
						existe_tecla_lida = 1;
					}

				}


				return;

	}
	contador++;
}
	

char TECLADO::leTecla (void)
{
	static int testa = 0;

	if (testa==0)
	{

		existe_tecla_lida = 0;
		configura_interrupcao_externa(meu_tratador_interrupcao_externa, PIN_2_13_INT_EXT_3, BORDA_DESCIDA); 
		pinMode(PINO_DADOS, INPUT);  
		testa = 1;
	}

	while (1)
	{
		if (existe_tecla_lida)
		{
			existe_tecla_lida = 0;
			return tecla_lida;
		}
		
	}

}


