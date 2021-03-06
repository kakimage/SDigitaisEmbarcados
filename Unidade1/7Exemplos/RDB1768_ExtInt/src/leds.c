//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// leds.c provided functions to access the  "user LEDs" on the
// RDB1768 development board (LEDs 2-5).
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

#include "NXP\LPC17xx\type.h"
#include "NXP\LPC17xx\LPC17xx.h"
#include "leds.h"

// Function to turn all leds on
void leds_all_on (void)
{
	FIO1SET = LED_ALL;
}

// Function to turn all leds off
void leds_all_off (void)
{
	FIO1CLR = LED_ALL;
}

// Function to invert current state of leds
void leds_invert (void)
{
	int ledstate;
	// read current state of GPIO P1_16..31, which includes LEDs
	ledstate = FIO1PIN;
	// turn off LEDs that are on 
	// (ANDing to ensure we only affect the LED outputs)
	FIO1CLR = ledstate & LED_ALL;
	// turn on LEDs that are off 
	// (ANDing to ensure we only affect the LED outputs)	
	FIO1SET = ((~ledstate) & LED_ALL);
}

// Function to turn on chosen led(s)
void led_on (unsigned int ledstate)
{
	// turn on requested LEDs
	// (ANDing to ensure we only affect the LED outputs)
	FIO1SET = ledstate & LED_ALL;
}

// Function to turn off chosen led(s)
void led_off (unsigned int ledstate)
{
	// turn off requested LEDs
	// (ANDing to ensure we only affect the LED outputs)
	FIO1CLR = ledstate & LED_ALL;
}
