//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcddemo.c calls a number of functions to demonstrate the use of the
// LCD display on the RDB1768 development board.
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

#include "NXP/LPC17xx/type.h"
#include "NXP/LPC17xx/target.h"

#include "lcd.h"
#include "lcddemo.h"
#include <stdlib.h>

// Function to add short delays in writing things to the LCD.
void main_delay(int n)
{
   volatile int d;
   for (d=0; d<n*3000; d++){}
}

int main(void)
{
	//	Set up general system / board / PLL / clocks ....	
	TargetResetInit();
	
	// Initialize the ST7637 LCD Controller/driver for use
	LCDdriver_initialisation();

	// Continuously loop through the LCD demonstration
	while(1)
	{	
		// *****************************************
		// ** LCD Demo part 1 - Graphics and text **
		// *****************************************		
		cycle_graphics();
		
		// *****************************************************
		// ** LCD Demo part 2 - Primitives for drawing shapes **
		// *****************************************************		
		draw_shapes();
	
		// ****************************************
		// ** LCD Demo part 3 - Simple animation **
		// ****************************************		
		bounce_logo();
		
		// *************************************
		// ** LCD Demo part 4 - Text Terminal **
		// *************************************		
		text_terminal();		

	}	// of while
	return 0 ;
} 
