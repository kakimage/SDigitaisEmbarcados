/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : (C) Copyright Code Red Technlogies Inc. 2009
 Description : Simple SysTick timer interrupt demo.
===============================================================================
*/

#include "NXP/LPC17xx/LPC17xx.h"
#include "NXP/LPC17xx/type.h"
#include "NXP/LPC17xx/target.h"

#define NVIC_SYSTICK_CLK		0x00000004
#define NVIC_SYSTICK_INT		0x00000002
#define NVIC_SYSTICK_ENABLE		0x00000001

int gi_SystickCount;

// Enable interrupts
static inline void __enable_irq()	{ asm volatile ("cpsie i"); }

// Initialize the CM3 System Tick timer, given desired rate and the current CPU rate
void vF_SysTickInit(int i_CPUClockHz, int i_SystickHz)
{
	gi_SystickCount = 0;
	
	/* Configure SysTick to interrupt at the requested rate. */
	NVIC_ST_RELOAD = ( i_CPUClockHz / i_SystickHz ) - 1UL;
	NVIC_ST_CTRL = NVIC_SYSTICK_CLK | NVIC_SYSTICK_INT | NVIC_SYSTICK_ENABLE;
}

// Interrupt handler just increments a count forever.
// Note that CM3 interrupt handlers are regular C functions - no special attributes.
void vF_SysTickHander(void)
{
	gi_SystickCount++;
	
}

int main(void) {

	TargetResetInit();	
	
	vF_SysTickInit(96000000, 10);

	__enable_irq();
	
	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
		i++ ;
	}
	return 0 ;
}
