#include "LPC17xx.h"
#include "digital.h"



static LPC_GPIO_TypeDef   (* const LPC_GPIO[5] ) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3, LPC_GPIO4  };


static __IO uint32_t * LPC_MODE[10];
static __IO uint32_t * LPC_PINSEL[10];


void pinMode( uint16_t portbit, uint8_t bitVal )
{
	uint8_t baixa=1, modo;
	uint32_t c;

	if ( (31&portbit) <= 15) baixa=0;
	modo = 2* (portbit>>5) + baixa;
	if (modo %2 )  	c = (2*  (  (31&portbit) - 16)  );
	else  			c = (2*(31&portbit));


	LPC_PINSEL[0] = &(LPC_PINCON->PINSEL0);
	LPC_PINSEL[1] = &(LPC_PINCON->PINSEL1);
	LPC_PINSEL[2] = &(LPC_PINCON->PINSEL2);
	LPC_PINSEL[3] = &(LPC_PINCON->PINSEL3);
	LPC_PINSEL[4] = &(LPC_PINCON->PINSEL4);
	LPC_PINSEL[5] = &(LPC_PINCON->PINSEL5);
	LPC_PINSEL[6] = &(LPC_PINCON->PINSEL6);
	LPC_PINSEL[7] = &(LPC_PINCON->PINSEL7);
	LPC_PINSEL[8] = &(LPC_PINCON->PINSEL8);
	LPC_PINSEL[9] = &(LPC_PINCON->PINSEL9);


	LPC_MODE[0] = &(LPC_PINCON->PINMODE0);
	LPC_MODE[1] = &(LPC_PINCON->PINMODE1);
	LPC_MODE[2] = &(LPC_PINCON->PINMODE2);
	LPC_MODE[3] = &(LPC_PINCON->PINMODE3);
	LPC_MODE[4] = &(LPC_PINCON->PINMODE4);
	LPC_MODE[5] = &(LPC_PINCON->PINMODE5);
	LPC_MODE[6] = &(LPC_PINCON->PINMODE6);
	LPC_MODE[7] = &(LPC_PINCON->PINMODE7);
	LPC_MODE[8] = &(LPC_PINCON->PINMODE8);
	LPC_MODE[9] = &(LPC_PINCON->PINMODE9);

	*(LPC_PINSEL[modo]) = (*LPC_PINSEL[modo]) &~ (3<<c);
	switch (bitVal)
	{
		case INPUT_PULLUP:
			LPC_GPIO[portbit>>5]->FIODIR &= ~(1<<(31&portbit));
			(*LPC_MODE[modo]) = (*LPC_MODE[modo]) &~ (3<<c);
			break;
		case INPUT_PULLDOWN:
			LPC_GPIO[portbit>>5]->FIODIR &= ~(1<<(31&portbit));
			(*LPC_MODE[modo]) = (*LPC_MODE[modo]) &~(3<<c);
			*(LPC_MODE[modo]) = (*LPC_MODE[modo]) | (3<<c);
 			break;
		case OUTPUT:
			LPC_GPIO[(uint8_t)(portbit>>5)]->FIODIR |= (1<<(31&portbit));
			break;
		case INPUT:
			LPC_GPIO[portbit>>5]->FIODIR &= ~(1<<(31&portbit));
			(*LPC_MODE[modo]) = (*LPC_MODE[modo]) &~(3<<c);
			*(LPC_MODE[modo]) = (*LPC_MODE[modo]) | (2<<c);
		
	}
  
}

void digitalWrite( uint16_t portbit, uint8_t valor )
{
	valor = valor & 1;
    LPC_GPIO[portbit>>5]->FIOMASK = ~(1<<(31&portbit));
	if (valor == LOW)  LPC_GPIO[(uint8_t)(portbit>>5)]->FIOCLR = (1<<(31&portbit));
    else LPC_GPIO[(uint8_t)(portbit>>5)]->FIOSET = (1<<(31&portbit));
}


uint8_t digitalRead (uint16_t portbit)
{
    uint32_t val;

    LPC_GPIO[portbit>>5]->FIOMASK = ~(1<<(31&portbit));
    val = LPC_GPIO[portbit>>5]->FIOPIN;
    val = val >> (31&portbit);
    LPC_GPIO[portbit>>5]->FIOMASK = 0x00000000;
    return (uint8_t)(val& 1);
}

