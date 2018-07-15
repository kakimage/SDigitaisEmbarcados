/*****************************************************************************
 *   iotest.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/

#include "lpc17xx.h"
#include "type.h"

int main (void)
{	    		
	uint32_t i, j;

	SystemInit();
	
	LPC_GPIO2->FIODIR = 0x000000FF;		/* P2.xx defined as Outputs */
	LPC_GPIO2->FIOCLR = 0x000000FF;		/* turn off all the LEDs */

	while(1)
	{
		for(i = 0; i < 8; i++)
		{
			LPC_GPIO2->FIOSET = 1 << i;
			for(j = 1000000; j > 0; j--);
		}
		LPC_GPIO2->FIOCLR = 0x000000FF;
		for(j = 1000000; j > 0; j--);
	}
}





