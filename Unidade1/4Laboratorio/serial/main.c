// EXEMPLO DE UM Pisca Pisca que usa a Lampada do kit
// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000
//
// para gravar na placa (usando o JTAG)
//                   openocd -f lpc1768.cfg
// abrir outro shell
// telnet localhost 4444
// > reset halt
// > flash write_image erase main.bin 0x0 bin
#include "LPC17xx.h"

//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// UART example project for RDB1768 development board
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

#include "type.h"
#include "LPC17xx.h"
#include "uart.h"
//#include "target.h"

// Control how the character received by the board is echoed back to the host
// Set to true to increment character ('a' echoed as 'b')
#define INCREMENT_ECHO_BY_1 TRUE

// Control whether debug printf are displayed via semihosting to the 
// debugger console window
#define SEMIHOSTING_CONSOLE TRUE

#ifdef SEMIHOSTING_CONSOLE
#include <stdio.h>
#define DBG	printf
#else
#define DBG(x ...)
#endif

// PCUART0
#define PCUART0_POWERON (1 << 3)

#define PCLK_UART0 6
#define PCLK_UART0_MASK (3 << 6)

// Function to set up UART
void UART0_Init(int cclk, int baudrate)
{
	unsigned long int Fdiv;

	// Turn on power to UART0
	PCONP |=  PCUART0_POWERON;
		
	// Turn on UART0 peripheral clock
	PCLKSEL0 = PCLKSEL0 & ~(PCLK_UART0_MASK);
	PCLKSEL0 |=  (0 << PCLK_UART0);		// PCLK_periph = CCLK/4
	
	// Set PINSEL0 so that P0.2 = TXD0, P0.3 = RXD0
	PINSEL0 = (PINSEL0 & ~0xf0) | (1 << 4) | (1 << 6);
	
    U0LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
    Fdiv = ( cclk / 16 ) / baudrate ;	// Set baud rate
    U0DLM = Fdiv / 256;							
    U0DLL = Fdiv % 256;
	U0LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
    U0FCR = 0x07;		// Enable and reset TX and RX FIFO
}


// Function to send character over UART
void UART0_Sendchar(char c)
{
	while( (U0LSR & LSR_THRE) == 0 );	// Block until tx empty
	
	U0THR = c;
}


// Function to get character from UART
char UART0_Getchar()
{
	char c;
	while( (U0LSR & LSR_RDR) == 0 );  // Nothing received so just block 	
	c = U0RBR; // Read Receiver buffer register
	return c;
}

// Function to prints the string out over the UART
void UART_PrintString(char *pcString)
{
	int i = 0;
	// loop through until reach string's zero terminator
	while (pcString[i] != 0) {	
		UART0_Sendchar(pcString[i]); // print each character
		i++;
	}
}


int main(void)
{	
	char c;
	volatile static int i = 0 ;
	
	TargetResetInit();	// Main system setup
	
	UART0_Init(96000000/4, 115200); // Setup UART to 115200 baud

	// Startup message for display in debugger console window
	// {displayed only if SEMIHOSTING_CONSOLE define is set).
	DBG("RDB1768 UART Demonstration\n");
	DBG("==========================\n\n");
	DBG("Press a key within your terminal\n");
	DBG("And the board will echo it back\n");	
#ifdef INCREMENT_ECHO_BY_1
	DBG("incremented by 1 ('a'->'b')\n");
#endif	
	DBG("Debugger console will display keys pressed\n");
	DBG("when buffer flushed by pressing 'enter'\n\n");	
	
	
	// Startup message for display in PC's terminal window.
	// You must make sure the terminal program is already
	// running when this code is executed if you want to
	// see it !
	
	UART_PrintString("RDB1768 UART Demonstration\r\n");
	UART_PrintString("==========================\r\n\n");
	UART_PrintString("Press a key within your terminal\r\n");
	UART_PrintString("and the board will echo it back");	
#ifdef INCREMENT_ECHO_BY_1
	UART_PrintString(",\r\nincremented by 1 ('a'->'b')");
#endif
	UART_PrintString(".\r\n\n");
	
	// Enter an infinite loop, accessing UART and incrementing a counter

	while(1) {

		c = UART0_Getchar();	// wait for next character from terminal
		if (c != EOF) {
			// show on debugger console
			if ((c == 9) || (c == 10) || (c == 13) || ((c >= 32) && (c <= 126))) {
				DBG("%c", c);
				
				// Some terminal programs can be configured to send both
				// newline and carriage return when 'enter' key is pressed.
				// However not all can. As semihosting requires a newline
				// in order to flush its buffer, we add one just in case
				// the terminal doesn't send one.
				if (c==13) { DBG("\n"); } 
			}
			else {
				DBG(".");	// non-printable character
			}
		 
// Echo character back over UART as is, or incremented by 1, as per #define.
#ifdef INCREMENT_ECHO_BY_1
			if ((c >= 32) && (c <= 126)) {
				c++;			// only increment "standard" characters
			}
#endif	
		// resend received character back over UART to host		
			if ((c == 9) || (c == 10) || (c == 13) || ((c >= 32) && (c <= 126))) {
				UART0_Sendchar(c);
				
				// Some terminal programs can be configured to print both
				// a newline and a carriage return when they receive a carriage
				// return character. However not all can, so here we send a
				// newline in case. Otherwise the output for the next line will
				// be "staggered" part way across the screen.
				if (c==13) { UART0_Sendchar('\n'); } 
			}
			else {
				UART0_Sendchar('.'); // non-printable character
			}		
	
			i++ ;
		}
	}
	return 0;
}
