//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// AudioLevelMeter example project for RDB1768 development board
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
//
//*****************************************************************************
#include "NXP\LPC17xx\type.h"
#include "NXP/LPC17xx/LPC17xx.h"
#include "RDB1768_AUDIO.h"
#include "NXP\LPC17xx\target.h"

#include <math.h>
#include "lcd.h"
#include "delay.h"

// Header for Code Red logo displayed on LCD
#include "codered128x37.h"

// Top left corner of meters (including outer rectangle)
#define METER_X_OFFSET 18
#define METER0_Y_OFFSET 65
// Top left corner of top meter (excluding outer rectangle)
#define METER_X_INN_OS (METER_X_OFFSET+1)
#define METER0_Y_INN_OS (METER0_Y_OFFSET+1)
// Width of meter (excluding outer rectangle)
#define METER_X_INNERWIDTH 100
// Float version of width of meter
#define METER_X_INNERWIDTH_FLOAT 100.0
// Height of meter (excluding outer rectangle)
#define METER_Y_INNERWIDTH 20
	// Width of meter (inccluding outer rectangle)
#define METER_X_OUTERWIDTH (METER_X_INNERWIDTH+2)
// Height of meter (including outer rectangle)
#define METER_Y_OUTERWIDTH (METER_Y_INNERWIDTH+2)
// Vertical position of bottom meter (including outer rectangle)
#define METER1_Y_OFFSET (METER0_Y_OFFSET + METER_Y_OUTERWIDTH +	10)
// Vertical position of bottom meter (excluding outer rectangle)
#define METER1_Y_INN_OS (METER1_Y_OFFSET+1)	

extern long int gQ31_Peak_L, gQ31_Peak_R;
extern long int gQ31_Peak[2];

static inline void __enable_irq()	{ asm volatile ("cpsie i"); }
static inline void __disable_irq()  { asm volatile ("cpsid i"); }

float f_dBPeak[2] = {-METER_X_INNERWIDTH_FLOAT,-METER_X_INNERWIDTH_FLOAT};
float f_dBDisplayPeak[2] = {-METER_X_INNERWIDTH_FLOAT,-METER_X_INNERWIDTH_FLOAT};

int main(void)
{
	int i;
	float f;
	int i_Channel;  

	CLKSRCSEL |= 0x40;
	// Main system setup
	TargetResetInit();

	// Initialize the ST7637 LCD Controller/driver for use
	LCDdriver_initialisation();

	// Enable interrupts (needed for I2C init, and audio I/O)
	__enable_irq();
	
	// Initialize the Audio Codec through I2C
	vfAudioInit();

	// Plot Code Red logo at top of screen
	LCD_PlotBitmap (0, 0, codered128x37_pixel_data ,codered128x37_width, codered128x37_height);	

	// Print 'title' text. Printing split over several calls because
	// string (including spaces) is too wide for screen (max 16 characters).
	// By splitting it up we can effectively reduce size of space characters
	// and fit all of string on one line
	LCD_PrintString(1,43,"Audio", COLOR_WHITE, COLOR_BLACK);
	LCD_PrintString(44,43,"Level", COLOR_WHITE, COLOR_BLACK);
	LCD_PrintString(87,43,"Meter", COLOR_WHITE, COLOR_BLACK);
	
	// Draw outer rectangle for holding top audio meter (left channel)
	LCD_Rect (METER_X_OFFSET, METER_X_OFFSET + METER_X_OUTERWIDTH,
			METER0_Y_OFFSET, METER0_Y_OFFSET + METER_Y_OUTERWIDTH,
			COLOR_WHITE);

	// Draw outer rectangle for holding top audio meter (left channel)
	LCD_Rect (METER_X_OFFSET, METER_X_OFFSET + METER_X_OUTERWIDTH,
			METER1_Y_OFFSET, METER1_Y_OFFSET + METER_Y_OUTERWIDTH,
			COLOR_WHITE);

	// Print left/right channel indicators next to meters
	LCD_PrintString(5,METER0_Y_OFFSET+(METER_Y_INNERWIDTH/5),"L", COLOR_BLUE, COLOR_BLACK);
	LCD_PrintString(5,METER1_Y_OFFSET+(METER_Y_INNERWIDTH/5),"R", COLOR_RED, COLOR_BLACK);	

	
	while(1)
	{
		// Leave short pause before next screen update
		delay (150);

		// Update screen - once though loop for left channel, once for right
		for(i_Channel = 0;i_Channel<2;i_Channel++)
		{
			// Now compute the dB value
			if(gQ31_Peak[i_Channel] > 0)	// don't want division by zero or log of zero
			{
				f_dBPeak[i_Channel] = 20.0 * log10(((float)gQ31_Peak[i_Channel])/((float)0x7fffff00)); 
				// Range produced will be 0db -> -xxxxdb
			}
			else
				f_dBPeak[i_Channel] = -120.0;
		
			if(f_dBPeak[i_Channel] > f_dBDisplayPeak[i_Channel])
			{
				f_dBDisplayPeak[i_Channel] = f_dBPeak[i_Channel];
				gQ31_Peak[i_Channel] = 0;					// reset the peak hold
			}

			// range is now +'METER_X_INNERWIDTH_FLOAT' to -xxxxx WITH 1.5dB per pixel
			f = (METER_X_INNERWIDTH_FLOAT + (1.5 * f_dBDisplayPeak[i_Channel]));

			i = (int)f;		
			if(i < 1)
				i = 1;	// always show something on the screen
			if(i > METER_X_INNERWIDTH)
				i = METER_X_INNERWIDTH;
			if(i_Channel == 0)
			{	// Update top meter (left channel)
				LCD_FilledRect (METER_X_INN_OS, METER_X_INN_OS + i,
						METER0_Y_INN_OS, METER0_Y_INN_OS + METER_Y_INNERWIDTH,
						COLOR_BLUE);
				if (i < METER_X_INNERWIDTH) // Don't need overwrite if channel at max
					LCD_FilledRect (METER_X_INN_OS+1+i,METER_X_INN_OS + METER_X_INNERWIDTH,
						METER0_Y_INN_OS, METER0_Y_INN_OS + METER_Y_INNERWIDTH,
						COLOR_BLACK);
			}
			else
			{// Update bottom meter (right channel)
				LCD_FilledRect (METER_X_INN_OS,METER_X_INN_OS + i,
						METER1_Y_INN_OS, METER1_Y_INN_OS + METER_Y_INNERWIDTH,
						COLOR_RED);
				if (i < METER_X_INNERWIDTH) // Don't need overwrite if channel at max
					LCD_FilledRect (METER_X_INN_OS+1+i,METER_X_INN_OS + METER_X_INNERWIDTH,
						METER1_Y_INN_OS, METER1_Y_INN_OS + METER_Y_INNERWIDTH,
						COLOR_BLACK);
			}
		
			// Decay the display over time the negative dB value
			if(f_dBDisplayPeak[i_Channel] != 0.0)
				f_dBDisplayPeak[i_Channel] *= 1.1;
			else
				// This stops it getting stuck at full-scale if dB==0
				f_dBDisplayPeak[i_Channel] = -0.5; 		

		} //for(i_Channel...
	} // while (1)
	
	return 0 ;
}
