//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// main_adc.c demonstrates the use of the ADC potentiometer
// on the RDB1768 development board.
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
#include "NXP\LPC17xx\target.h"
#include "NXP\LPC17xx\LPC17xx.h"
#include <stdio.h>

// PCADC / PCAD
#define ADC_POWERON (1 << 12) 

#define PCLK_ADC 24
#define PCLK_ADC_MASK (3 << 24)

// AD0.0 - P0.23, PINSEL1 [15:14] = 01
#define SELECT_ADC0 (0x1<<14)

// ADOCR constants
#define START_ADC (1<<24)
#define OPERATIONAL_ADC (1 << 21)
#define SEL_AD0 (1 <<0)

#define ADC_DONE_BIT	(1 << 31)

// Function to provide short delay
void main_delay (int n) __attribute__((noinline));
void main_delay(int n)
{
   volatile int d;
   for (d=0; d<n*3000; d++){}
}


int main(void) {

	volatile static int i = 0 ;
	int adval;
	
	// Set up board/processor
	TargetResetInit();

	// Turn on power to ADC block 
	PCONP |=  ADC_POWERON;

	// Turn on ADC peripheral clock
	PCLKSEL0 = PCLKSEL0 & ~(PCLK_ADC_MASK);
	PCLKSEL0 |=  (3 << PCLK_ADC);
		
	// Set P0.23 to AD0.0 in PINSEL1
	PINSEL1	|= SELECT_ADC0; 
	
	// Enter an infinite loop, just checking ADC pot and incrementing a counter
	while(1) {

		// Start A/D conversion for on AD0.0
		AD0CR = START_ADC | OPERATIONAL_ADC | SEL_AD0 ;

		do {
			adval = AD0GDR;                      // Read A/D Data Register
		} while ((adval & ADC_DONE_BIT) == 0);   // Wait for end of A/D Conversion
		
		AD0CR &= ~(START_ADC | OPERATIONAL_ADC | SEL_AD0 );   // Stop A/D Conversion

		 // Extract AD0.0 value - 12 bit result in bits [15:4]
		adval = (adval >> 4) & 0x0FFF ;            

		printf ("%d - Pot val = %d\n", i, adval);
		main_delay(5000);	//Short delay before doing another ADC read
		i++ ;
	}
	return 0 ;
}
