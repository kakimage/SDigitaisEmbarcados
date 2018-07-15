/*****************************************************************************
 *   target.c:  Target C file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include "NXP/LPC17xx/LPC17xx.h"
#include "NXP/LPC17xx/type.h"
#include "NXP/LPC17xx/target.h"
//#include "target.h"
/******************************************************************************
** Function name:		TargetInit
**
** Descriptions:		Initialize the target board; it is called in a necessary 
**						place, change it as needed
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetInit(void)
{
  /* Add your codes here */
  return;
}

/******************************************************************************
** Function name:		GPIOResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**				function; User may change it as needed, but may not 
**				deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void GPIOResetInit(void)
{
  /* Reset all GPIO pins to default: primary function */
  PINSEL0 = 0x00000000;
  PINSEL1 = 0x00000000;
  PINSEL2 = 0x00000000;
  PINSEL3 = 0x00000000;
  PINSEL4 = 0x00000000;
  PINSEL5 = 0x00000000;
  PINSEL6 = 0x00000000;
  PINSEL7 = 0x00000000;
  PINSEL8 = 0x00000000;
  PINSEL9 = 0x00000000;
  PINSEL10 = 0x00000000;
    
  FIO0DIR = 0x00000000;
  FIO1DIR = 0x00000000;
  FIO2DIR = 0x00000000;
  FIO3DIR = 0x00000000;
  FIO4DIR = 0x00000000;
    
  FIO0SET = 0x00000000;
  FIO1SET = 0x00000000;
  FIO2SET = 0x00000000;
  FIO3SET = 0x00000000;
  FIO4SET = 0x00000000;
  return;        
}

/******************************************************************************
** Function name:		ConfigurePLL
**
** Descriptions:		Configure PLL switching to main OSC instead of IRC
**						at power up and wake up from power down. 
**						This routine is used in TargetResetInit() and those
**						examples using power down and wake up such as
**						USB suspend to resume, ethernet WOL, and power management
**						example
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ConfigurePLL(void)
{
  DWORD MValue, NValue, PValue;

  if ( PLL0STAT & (1 << 25) )
  {
	PLL0CON = 1;			/* Enable PLL, disconnected */
	PLL0FEED = 0xaa;
	PLL0FEED = 0x55;
  }

  PLL0CON = 0;				/* Disable PLL, disconnected */
  PLL0FEED = 0xaa;
  PLL0FEED = 0x55;
    
  SCS |= 0x20;			/* Enable main OSC */
  while( !(SCS & 0x40) );	/* Wait until main OSC is usable */

  CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

  PLL0CFG = PLL0_MValue | (PLL0_NValue << 16);
  PLL0FEED = 0xaa;
  PLL0FEED = 0x55;
      
  PLL0CON = 1;				/* Enable PLL, disconnected */
  PLL0FEED = 0xaa;
  PLL0FEED = 0x55;

  CCLKCFG = CCLKDivValue;	/* Set clock divider */

  while ( ((PLL0STAT & (1 << 26)) == 0) );	/* Check lock bit status */
    
  MValue = PLL0STAT & 0x00007FFF;
  NValue = (PLL0STAT & 0x00FF0000) >> 16;
  while ((MValue != PLL0_MValue) && ( NValue != PLL0_NValue) );

  PLL0CON = 3;				/* enable and connect */
  PLL0FEED = 0xaa;
  PLL0FEED = 0x55;
  while ( ((PLL0STAT & (1 << 25)) == 0) );	/* Check connect bit status */

#if USE_USB
  if ( PLL1STAT & (1 << 9) )
  {
	PLL1CON = 1;			/* Enable PLL, disconnected */
	PLL1FEED = 0xaa;
	PLL1FEED = 0x55;
  }

  PLL1CON = 0;				/* Disable PLL, disconnected */
  PLL1FEED = 0xaa;
  PLL1FEED = 0x55;

  PLL1CFG = PLL1_MValue | (PLL1_PValue << 5);
  PLL1FEED = 0xaa;
  PLL1FEED = 0x55;
      
  PLL1CON = 1;				/* Enable PLL, disconnected */
  PLL1FEED = 0xaa;
  PLL1FEED = 0x55;
  while ( ((PLL1STAT & (1 << 10)) == 0) );	/* Check lock bit status */

  MValue = PLL1STAT & 0x0000001F;
  PValue = (PLL1STAT & 0x00000060) >> 5;
  while ((MValue != PLL1_MValue) && ( PValue != PLL1_PValue) );

  PLL1CON = 3;				/* enable and connect */
  PLL1FEED = 0xaa;
  PLL1FEED = 0x55;
  while ( ((PLL1STAT & (1 << 9)) == 0) );	/* Check connect bit status */
#endif

  return;
}

/******************************************************************************
** Function name:		TargetResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**						function; User may change it as needed, but may not 
**						deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetResetInit(void)
{
#if USE_USB
//  PCONP |= 0x80000000;		/* Turn On USB PCLK */
#endif
  /* Configure PLL, switch from IRC to Main OSC */
  ConfigurePLL();

  /* Set system timers for each component */
#if (Fpclk / (Fcclk / 4)) == 1
  PCLKSEL0 = 0x00000000;	/* PCLK is 1/4 CCLK */
  PCLKSEL1 = 0x00000000;
#endif
#if (Fpclk / (Fcclk / 4)) == 2
  PCLKSEL0 = 0xAAAAAAAA;	/* PCLK is 1/2 CCLK */
  PCLKSEL1 = 0xAAAAAAAA;	 
#endif
#if (Fpclk / (Fcclk / 4)) == 4
  PCLKSEL0 = 0x55555555;	/* PCLK is the same as CCLK */
  PCLKSEL1 = 0x55555555;	
#endif

  GPIOResetInit();

  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
