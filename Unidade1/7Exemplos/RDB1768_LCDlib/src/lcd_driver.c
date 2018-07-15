//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcd_driver.c contains the lowest level access routines for the Sitronix
// ST7637 LCD Controller/driver used on the RDB1768 development board.
//
//
// Software License Agreement
// 
// The software is owned by Code Red Technologies and/or its suppliers, and is 
// protected under applicable copyright laws.  All rights are reserved.  Any 
// use in violation of the foregoing restrictions may subject the user to criminal 
// sanctions under applicable laws, as well as to civil liability for the breach 
// of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD. 

// Local copy of NXP LPC header file used due to issues with incorrect defintion
// for FIO2PIN0 used in optimized low level access to LCD controller.
//#include "NXP/LPC17xx/LPC17xx.h"
#include "LPC17xx.h"

#include "lcd.h"

// Used to control whether the optimized version of the lowest level LCD access
// routines are used, rather than the simple, direct implementations
#define OPT_LCD_ACCESS 1

// Bits within GPIO port 2 used for LCD driver
#define LCD_CSB_PIN            (1<<13)
#define LCD_A0_PIN             (1<<8)
#define LCD_WR_PIN             (1<<11)
#define LCD_RD_PIN             (1<<12)
#define LCD_DATA_PIN			0xff

// Bit within GPIO port 3 used for LCD driver
#define LCD_RESB_PIN           (1<<25)

// Bits to configure as outputs for driving LCD
#define LCD_PORT2_DIRECTIONS  (LCD_CSB_PIN | LCD_A0_PIN | LCD_WR_PIN | LCD_RD_PIN | LCD_DATA_PIN)
#define LCD_PORT3_DIRECTIONS  (LCD_RESB_PIN)

// Define names for GPIO port 2 and 3 registers to better indicate in code
// the operation being carried out on the LCD driver hardware.
#define LCD_DATA_CLR	FIO2CLR
#define LCD_DATA_SET	FIO2SET
#define LCD_CSB_CLR		FIO2CLR
#define LCD_CSB_SET		FIO2SET
#define LCD_RESB_CLR	FIO3CLR
#define LCD_RESB_SET	FIO3SET
#define LCD_A0_CLR		FIO2CLR
#define LCD_A0_SET		FIO2SET
#define LCD_WR_CLR		FIO2CLR
#define LCD_WR_SET		FIO2SET
#define LCD_RD_CLR		FIO2CLR
#define LCD_RD_SET		FIO2SET


// Routine to introduce short delays required during LCD initialisation
void ms_delay (int n) __attribute__((noinline));
void ms_delay(int n)
{
   volatile int d;
   for (d=0; d<n*3000; d++){}
}

// Routine to write data to LCD driver. Normally called in combination
// with LCDdriver_WriteCom() routine
void LCDdriver_WriteData(unsigned char LCD_Data) __attribute__((noinline));
void LCDdriver_WriteData(unsigned char LCD_Data)
{
#ifdef OPT_LCD_ACCESS
    //  ** Optimised code **
	FIO2PIN0 = LCD_Data;
	FIO2CLR = LCD_CSB_PIN | LCD_WR_PIN;
	__asm("nop\n"); // Very short delay for pin setup
	FIO2SET = LCD_CSB_PIN | LCD_WR_PIN ;  
#else
	// ** Original code **	
    LCD_DATA_CLR = LCD_DATA_PIN;
    LCD_DATA_SET = LCD_Data;
    LCD_CSB_CLR = LCD_CSB_PIN;
    LCD_WR_CLR = LCD_WR_PIN;
    __asm("nop\n");
    __asm("nop\n");
    __asm("nop\n");
    LCD_WR_SET = LCD_WR_PIN;
    LCD_CSB_SET = LCD_CSB_PIN;
#endif
}

// Routine to configure set LCD driver to accept particular command.
// A call to this routine will normally be followed by a call
// to LCDdriver_WriteData() to transfer appropriate parameters to driver.
void LCDdriver_WriteCom(unsigned char LCD_Command)  __attribute__((noinline));
void LCDdriver_WriteCom(unsigned char LCD_Command)
{
#ifdef OPT_LCD_ACCESS
	//  ** Optimised code **
	FIO2PIN0 = LCD_Command;
	FIO2CLR = LCD_A0_PIN | LCD_CSB_PIN | LCD_WR_PIN;
	__asm("nop\n");	// Very short delay for pin setup
	FIO2SET = LCD_A0_PIN |LCD_CSB_PIN | LCD_WR_PIN ; 
#else
	//	** Original code **		
	LCD_DATA_CLR = LCD_DATA_PIN;
    LCD_DATA_SET = LCD_Command;
    LCD_A0_CLR =	LCD_A0_PIN;
    LCD_CSB_CLR = LCD_CSB_PIN;
    LCD_WR_CLR = LCD_WR_PIN;
    __asm("nop\n"); // Very short delay for pin setup
    __asm("nop\n");
    __asm("nop\n");
    LCD_WR_SET = LCD_WR_PIN;
    LCD_CSB_SET = LCD_CSB_PIN;
	LCD_A0_SET = LCD_A0_PIN;
#endif
}

// Initialize GPIO connection to the LCD driver
void LCDdriver_ConfigGPIOtoLCD(void)
{
    // set direction to outputs	
	FIO2DIR |= LCD_PORT2_DIRECTIONS;	
	FIO3DIR |= LCD_PORT3_DIRECTIONS;

	// Set GPIO outputs connected to LCD to default values
	LCD_CSB_SET = LCD_CSB_PIN;
	LCD_A0_SET = LCD_A0_PIN;
	LCD_WR_SET = LCD_WR_PIN;
	LCD_RD_SET = LCD_RD_PIN;
	LCD_RESB_SET = LCD_RESB_PIN;
	LCD_DATA_CLR =  0xff; // data bus to zero 
}


// Initialisation routine to set up LCD
void LCDdriver_initialisation(void)
{
	
	LCDdriver_ConfigGPIOtoLCD();		// Initialize the GPIO for the display

	LCDdriver_WriteCom(DD_SWRESET);		// SW reset
	ms_delay(120);						// Small delay
	
	LCDdriver_WriteCom(DD_AUTOLOADSET);	// disable auto loading of mask rom data
	LCDdriver_WriteData(0xBF);

	LCDdriver_WriteCom(DD_EPCTIN);			// OTP control mode=read
	LCDdriver_WriteData(0x00);
	ms_delay(10);							// Small delay


	LCDdriver_WriteCom(DD_EPREAD);			// Start the OTP read.
	ms_delay(20);							// Small delay


	LCDdriver_WriteCom(DD_EPCTOUT);		// Cancel the OTP read (20ms should have been enough)

	LCDdriver_WriteCom(DD_DISPOFF);		// display off

	LCDdriver_WriteCom(DD_SLPOUT);			// Exit sleep mode.
	ms_delay(50);							// Small delay

	LCDdriver_WriteCom(DD_VopSet);			// set LCD operating voltage to 14V.
	LCDdriver_WriteData(0x04);
	LCDdriver_WriteData(0x01);


	LCDdriver_WriteCom(DD_BiasSel);		// Select an LCD bias voltage ratio of 1/12.
	LCDdriver_WriteData(0x00);


	LCDdriver_WriteCom(DD_BstMbpXSel);		// x8 booster circuit on
	LCDdriver_WriteData(0x07);


	LCDdriver_WriteCom(DD_ColScanDir);		// Invert the column scan direction for the panel.
	LCDdriver_WriteData(0xC0);


	LCDdriver_WriteCom(DD_COLORMOD);		// 16bpp, 5-6-5 data input mode.
	LCDdriver_WriteData(0x05);


	LCDdriver_WriteCom(DD_MADCTR);			// mem scan direction
	LCDdriver_WriteData(0x00);


	LCDdriver_WriteCom(DD_DISPON);			// display on


	LCD_ClearScreen(0);


	LCDdriver_WriteCom(DD_NORON);			// normal operation mode

}

// Routine to clear the LCD.
// Implemented by drawing a rectangle of the appropriate color 
// across the whole screen
void LCD_ClearScreen(int bgcolor)
{
	int i;
	// Now Clear the Screen
	LCDdriver_WriteCom(DD_CASET);
	LCDdriver_WriteData(0x00);
	LCDdriver_WriteData(0x7F);

	LCDdriver_WriteCom(DD_RASET);
	// Screen is offset by 1 in Y axis in relation to controller RAM buffer
	LCDdriver_WriteData(0x01);		
	LCDdriver_WriteData(0x80);


	LCDdriver_WriteCom(DD_RAMWR);
	for(i = 0; i < (LCD_MAX_X * LCD_MAX_Y); i++)
	{
		LCDdriver_WriteData(bgcolor >> 8);
		LCDdriver_WriteData(bgcolor);
	}
}



