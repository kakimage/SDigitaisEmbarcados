/*****************************************************************************
 *   pwmtest.c:  main C entry file for NXP LPC17xx Family Microprocessors
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
#include "pwm.h"

extern volatile uint32_t match_counter1;

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{	    
  uint32_t cycle = PWM_CYCLE, offset = 0;
  SystemInit();
 
  if ( PWM_Init( 1, 0 ) != TRUE )
  {
	while( 1 );			/* fatal error */
  }

  PWM_Set( 1, cycle, offset );
  PWM_Start( 1 );

  while ( 1 )
  {
	if ( match_counter1 != 0 )
	{
	  match_counter1 = 0;
	  PWM_Set( 1, cycle, offset );
	}
  }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
