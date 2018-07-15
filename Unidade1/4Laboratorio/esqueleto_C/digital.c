
#include "digital.h"

static LPC_GPIO_TypeDef (* const LPC_GPIO[5]) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3, LPC_GPIO4  };

void pinMode ( uint16_t pino, uint8_t valor)
{
	if (valor==OUTPUT)  LPC_GPIO[pino >> 5]->FIODIR |= 1 << (31 & pino);
    else   LPC_GPIO[pino >> 5]->FIODIR &= ~(1 << (31 & pino));

	 LPC_GPIO[pino >> 5]->FIOMASK  &= ~(1 << (31 & pino));
}

void digitalWrite(uint16_t pino, uint8_t valor)
{
	if (valor==HIGH) 	LPC_GPIO[pino >> 5]->FIOSET |= (1 << (31 & pino));
	else LPC_GPIO[pino >> 5]->FIOCLR |= (1 << (31 & pino));
}

uint8_t digitalRead (uint16_t portbit)
{

	return 0;
}


