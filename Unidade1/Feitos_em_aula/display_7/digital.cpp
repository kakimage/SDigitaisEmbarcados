
#include "digital.h"
#include "LPC17xx.h"

LPC_GPIO_TypeDef    *vet[]={LPC_GPIO0,LPC_GPIO1,LPC_GPIO2, LPC_GPIO3, LPC_GPIO4}; 

uint8_t Pino (uint8_t porta, uint8_t bit)
{
	return (porta<<5) | bit;
}

void pinMode (uint8_t pino, uint8_t tipo)
{
	uint8_t bit, porta;
	porta = pino >> 5;
	bit   = pino & 31;


	if (tipo==OUTPUT) vet[porta]->FIODIR|= (1<< bit) ;
	else  vet[porta]->FIODIR &= ~(1<< bit);

	/*switch (porta)
	{
		case 0:
			if (tipo==OUTPUT) LPC_GPIO0->FIODIR|= (1<< bit) ;
			else  LPC_GPIO0->FIODIR &= ~(1<< bit);
			break;
		case 1:
			if (tipo==OUTPUT) LPC_GPIO1->FIODIR|= (1<< bit) ;
			else  LPC_GPIO1->FIODIR &= ~(1<< bit);
			break;
		case 2:
			if (tipo==OUTPUT) LPC_GPIO2->FIODIR|= (1<< bit) ;
			else  LPC_GPIO2->FIODIR &= ~(1<< bit);
			break;
		case 3:
			if (tipo==OUTPUT) LPC_GPIO3->FIODIR|= (1<< bit) ;
			else  LPC_GPIO3->FIODIR &= ~(1<< bit);
			break;
		case 4:
			if (tipo==OUTPUT) LPC_GPIO4->FIODIR|= (1<< bit) ;
			else  LPC_GPIO4->FIODIR &= ~(1<< bit);
			break;
	}*/


}

void digitalWrite(uint8_t pino, uint8_t valor)
{
	uint8_t bit, porta;
	porta = pino >> 5;
	bit   = pino & 31;

	if (valor==HIGH) vet[porta]->FIOSET|= (1<<bit);
	else vet[porta]->FIOCLR|= (1<<bit);
}

