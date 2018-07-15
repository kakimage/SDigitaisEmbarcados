/*****************************************************************************
 *   extint.c:  External interrupt API C file for NXP LPC17xx 
 *   Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "extint.h"

volatile uint32_t eint0_counter;

/*****************************************************************************
** Function name:		EINT0_Handler
**
** Descriptions:		external INT handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void EINT0_IRQHandler (void) 
{
  LPC_SC->EXTINT = EINT0;		/* clear interrupt */
		
  eint0_counter++;
  if ( eint0_counter & 0x01 )	/* alternate the LED display */
  {
	LPC_GPIO2->FIOSET = 0x0000000F;	/* turn off P2.0~3 */	
	LPC_GPIO2->FIOCLR = 0x000000F0;	/* turn on P2.4~7 */
  }
  else
  {
	LPC_GPIO2->FIOSET = 0x000000F0;	/* turn on P2.0~3 */	
	LPC_GPIO2->FIOCLR = 0x0000000F;	/* turn off P2.4~7 */
  }

}

/*****************************************************************************
** Function name:		EINTInit
**
** Descriptions:		Initialize external interrupt pin and
**						install interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the interrupt
**						handler can't be installed to the VIC table.
** 
*****************************************************************************/
uint32_t EINTInit( void )
{

  LPC_PINCON->PINSEL4 = 0x00100000;	/* set P2.10 as EINT0 and
									P2.0~7 GPIO output */
  LPC_GPIO2->FIODIR = 0x000000FF;	/* port 2, bit 0~7 only */
  LPC_GPIO2->FIOCLR = 0x000000FF;	/* turn off LEDs */

  LPC_GPIOINT->IO2IntEnF = 0x200;	/* Port2.10 is falling edge. */
  LPC_SC->EXTMODE = EINT0_EDGE;		/* INT0 edge trigger */
  LPC_SC->EXTPOLAR = 0;				/* INT0 is falling edge by default */

  NVIC_EnableIRQ(EINT0_IRQn);
  return( TRUE );
}

/******************************************************************************
**                            End Of File
******************************************************************************/

