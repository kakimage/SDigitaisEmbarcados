/*
	FreeRTOS V5.4.1 - Copyright (C) 2009 Real Time Engineers Ltd.

	This file is part of the FreeRTOS distribution.

	FreeRTOS is free software; you can redistribute it and/or modify it	under
	the terms of the GNU General Public License (version 2) as published by the
	Free Software Foundation and modified by the FreeRTOS exception.
	**NOTE** The exception to the GPL is included to allow you to distribute a
	combined work that includes FreeRTOS without being obliged to provide the
	source code for proprietary components outside of the FreeRTOS kernel.
	Alternative commercial license and support terms are also available upon
	request.  See the licensing section of http://www.FreeRTOS.org for full
	license details.

	FreeRTOS is distributed in the hope that it will be useful,	but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
	more details.

	You should have received a copy of the GNU General Public License along
	with FreeRTOS; if not, write to the Free Software Foundation, Inc., 59
	Temple Place, Suite 330, Boston, MA  02111-1307  USA.


	***************************************************************************
	*                                                                         *
	* Looking for a quick start?  Then check out the FreeRTOS eBook!          *
	* See http://www.FreeRTOS.org/Documentation for details                   *
	*                                                                         *
	***************************************************************************

	1 tab == 4 spaces!

	Please ensure to read the configuration and relevant port sections of the
	online documentation.

	http://www.FreeRTOS.org - Documentation, latest information, license and
	contact details.

	http://www.SafeRTOS.com - A version that is certified for use in safety
	critical systems.

	http://www.OpenRTOS.com - Commercial support, development, porting,
	licensing and training services.
*/


//#error The batch file Demo\CORTEX_LPC1768_GCC_RedSuite\CreateProjectDirectoryStructure.bat must be executed before the first build.  After executing the batch file hit F5 to refrech the Eclipse project, then delete this line.



/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the standard demo application tasks
 * (which just exist to test the kernel port and provide an example of how to use
 * each FreeRTOS API function).
 *
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Check" hook -  This only executes fully every five seconds from the tick
 * hook.  Its main function is to check that all the standard demo tasks are
 * still operational.  The status can be viewed using on the Task Stats page
 * served by the WEB server.
 *
 * "uIP" task -  This is the task that handles the uIP stack.  All TCP/IP
 * processing is performed in this task.
 */

/* Standard includes. */
#include "stdio.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo app includes. */
#include "BlockQ.h"
#include "integer.h"
#include "blocktim.h"
#include "flash.h"
#include "partest.h"
#include "semtest.h"
#include "PollQ.h"
#include "GenQTest.h"
#include "QPeek.h"
#include "recmutex.h"

/* Red Suite includes. */
/*
// NXP: Used with RDB1768 from CodeRed
#include "lcd_driver.h"
#include "lcd.h"
*/

// NXP: Use Keil MCB1700 instead
#include "GLCD.h"

// NXP: Include these files to used with LPC1700CMSIS FwLib
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"

// NXP: Added to use some old macro definitions
#include "LPC17xx_FreeRTOS_def.h"

/*-----------------------------------------------------------*/

/* The time between cycles of the 'check' functionality (defined within the
tick hook. */
#define mainCHECK_DELAY						( ( portTickType ) 5000 / portTICK_RATE_MS )

/* Task priorities. */
#define mainQUEUE_POLL_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainSEM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1 )
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainUIP_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainINTEGER_TASK_PRIORITY           ( tskIDLE_PRIORITY )
#define mainGEN_QUEUE_TASK_PRIORITY			( tskIDLE_PRIORITY )
#define mainFLASH_TASK_PRIORITY				( tskIDLE_PRIORITY + 2 )

/* The WEB server has a larger stack as it utilises stack hungry string
handling library calls. */
#define mainBASIC_WEB_STACK_SIZE            ( configMINIMAL_STACK_SIZE * 4 )

/* The message displayed by the WEB server when all tasks are executing
without an error being reported. */
#define mainPASS_STATUS_MESSAGE				"All tasks are executing without error."

/*-----------------------------------------------------------*/

/*
 * Configure the hardware for the demo.
 */
static void prvSetupHardware( void );

/*
 * The task that handles the uIP stack.  All TCP/IP processing is performed in
 * this task.
 */
extern void vuIP_Task( void *pvParameters );

/*
 * Simply returns the current status message for display on served WEB pages.
 */
char *pcGetTaskStatusMessage( void );

/*-----------------------------------------------------------*/

/* Holds the status message displayed by the WEB server. */
static char *pcStatusMessage = mainPASS_STATUS_MESSAGE;

/*-----------------------------------------------------------*/


/* ---------------------------------------------------------------
 * LPC1700CMSIS fwlib using section
 * --------------------------------------------------------------- */
void lpc1700cmsis_fwlib_uart_demo(void)
{
	/*
	 * NXP : These following variable used with LPC1700CMSIS FwLib
	 * UART could be a good example
	 */
	// UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;
	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	// Pin configuration for UART0
	PINSEL_CFG_Type PinCfg;
	// Welcome Screen menu
	uint8_t welcome_menu[] = "Hello NXP Semiconductors \n\r" \
								"This is demo of porting FreeRTOS to LPC1700CMSIS project \n\r" \
								"NXP LPC1768 based on ARM Cortex-M3" \
								"FreeRTOS V5.4.0";

	/*
	 * Initialize UART0 pin connect
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 2;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);
	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 9600bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);

	// Initialize UART0 peripheral with given to corresponding parameter
	UART_Init(LPC_UART0, &UARTConfigStruct);

	/* Initialize FIFOConfigStruct to default state:
	 * 				- FIFO_DMAMode = DISABLE
	 * 				- FIFO_Level = UART_FIFO_TRGLEV0
	 * 				- FIFO_ResetRxBuf = ENABLE
	 * 				- FIFO_ResetTxBuf = ENABLE
	 * 				- FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);
	// Enable UART Transmit
	UART_TxCmd(LPC_UART0, ENABLE);
	// Print a welcome menu
	UART_Send(LPC_UART0, welcome_menu, sizeof(welcome_menu), BLOCKING);
}


int main( void )
{
char cIPAddress[ 16 ]; /* Enough space for "xxx.xxx.xxx.xxx\0". */

	/* Configure the hardware for use by this demo. */
	// NXP: in case of using LPC1700CMSIS fwlib driver, SystemInit() should
	// be called instead of this function below:
	// prvSetupHardware();

	// This is complaint with CMSIS
	SystemInit();
	// Implement for prvSetupHardware()
	/* Configure the LEDs. */
	vParTestInitialise();

	// UART demo
	lpc1700cmsis_fwlib_uart_demo();

	/* Start the standard demo tasks.  These are just here to exercise the
	kernel port and provide examples of how the FreeRTOS API can be used. */
	vStartBlockingQueueTasks( mainBLOCK_Q_PRIORITY );
    vCreateBlockTimeTasks();
    vStartSemaphoreTasks( mainSEM_TEST_PRIORITY );
    vStartPolledQueueTasks( mainQUEUE_POLL_PRIORITY );
    vStartIntegerMathTasks( mainINTEGER_TASK_PRIORITY );
    vStartGenericQueueTasks( mainGEN_QUEUE_TASK_PRIORITY );
    vStartQueuePeekTasks();
    vStartRecursiveMutexTasks();
	vStartLEDFlashTasks( mainFLASH_TASK_PRIORITY );

	/* Display the IP address, then create the uIP task.  The WEB server runs
	in this task. */
	/*
	// NXP: Used with RDB1768 from CodeRed
	LCDdriver_initialisation();
	LCD_PrintString( 5, 10, "FreeRTOS.org", 14, COLOR_GREEN);
	sprintf( cIPAddress, "%d.%d.%d.%d", configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 );
	LCD_PrintString( 5, 30, cIPAddress, 14, COLOR_RED);
    xTaskCreate( vuIP_Task, ( signed char * ) "uIP", mainBASIC_WEB_STACK_SIZE, ( void * ) NULL, mainUIP_TASK_PRIORITY, NULL );
	*/
	// NXP: Change to use with Keil MCB1700
	GLCD_init();
	GLCD_clear(White);                              /* Clear the GLCD        */
	GLCD_setBackColor(Blue);                        /* Set the Text Color    */
	GLCD_setTextColor(White);                       /* Set the Text Color    */
	GLCD_displayStringLn(Line0, "    FreeRTOS.org    ");
	GLCD_displayStringLn(Line1, " Cortex-M3 LPC1768  ");
	sprintf( cIPAddress, "IP: %d.%d.%d.%d", configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 );
	GLCD_displayStringLn(Line2, cIPAddress);

	xTaskCreate( vuIP_Task, ( signed char * ) "uIP", mainBASIC_WEB_STACK_SIZE, ( void * ) NULL, mainUIP_TASK_PRIORITY, NULL );

    /* Start the scheduler. */
	vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle
    task.  The idle task is created within vTaskStartScheduler(). */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
static unsigned portLONG ulTicksSinceLastDisplay = 0;

	/* Called from every tick interrupt as described in the comments at the top
	of this file.

	Have enough ticks passed to make it	time to perform our health status
	check again? */
	ulTicksSinceLastDisplay++;
	if( ulTicksSinceLastDisplay >= mainCHECK_DELAY )
	{
		/* Reset the counter so these checks run again in mainCHECK_DELAY
		ticks time. */
		ulTicksSinceLastDisplay = 0;

		/* Has an error been found in any task? */
		if( xAreGenericQueueTasksStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Generic Queue test/demo.";
		}
		else if( xAreQueuePeekTasksStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Peek Queue test/demo.";
		}
		else if( xAreBlockingQueuesStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Block Queue test/demo.";
		}
		else if( xAreBlockTimeTestTasksStillRunning() != pdTRUE )
		{
			pcStatusMessage = "An error has been detected in the Block Time test/demo.";
		}
	    else if( xAreSemaphoreTasksStillRunning() != pdTRUE )
	    {
	        pcStatusMessage = "An error has been detected in the Semaphore test/demo.";
	    }
	    else if( xArePollingQueuesStillRunning() != pdTRUE )
	    {
	        pcStatusMessage = "An error has been detected in the Poll Queue test/demo.";
	    }
	    else if( xAreIntegerMathsTaskStillRunning() != pdTRUE )
	    {
	        pcStatusMessage = "An error has been detected in the Int Math test/demo.";
	    }
	    else if( xAreRecursiveMutexTasksStillRunning() != pdTRUE )
	    {
	    	pcStatusMessage = "An error has been detected in the Mutex test/demo.";
	    }
	}
}
/*-----------------------------------------------------------*/

char *pcGetTaskStatusMessage( void )
{
	/* Not bothered about a critical section here. */
	return pcStatusMessage;
}
/*-----------------------------------------------------------*/

void prvSetupHardware( void )
{
	/* Disable peripherals power. */
	LPC_SC->PCONP = 0;

	/* Enable GPIO power. */
	LPC_SC->PCONP = PCONP_PCGPIO;

	/* Disable TPIU. */
	LPC_PINCON->PINSEL10 = 0;

	/* Disconnect the main PLL. */
	LPC_SC->PLL0CON &= ~PLLCON_PLLC;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;
	while ((LPC_SC->PLL0STAT & PLLSTAT_PLLC) != 0);

	/* Turn off the main PLL. */
	LPC_SC->PLL0CON &= ~PLLCON_PLLE;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;
	while ((LPC_SC->PLL0STAT & PLLSTAT_PLLE) != 0);

	/* No CPU clock divider. */
	LPC_SC->CCLKCFG = 0;

	/* OSCEN. */
	LPC_SC->SCS = 0x20;
	while ((LPC_SC->SCS & 0x40) == 0);

	/* Use main oscillator. */
	LPC_SC->CLKSRCSEL = 1;
	LPC_SC->PLL0CFG = (PLLCFG_MUL16 | PLLCFG_DIV1);

	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/*  Activate the PLL by turning it on then feeding the correct
	sequence of bytes. */
	LPC_SC->PLL0CON  = PLLCON_PLLE;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/* 6x CPU clock divider (64 MHz) */
	LPC_SC->CCLKCFG = 5;

	/*  Wait for the PLL to lock. */
	while ((LPC_SC->PLL0STAT & PLLSTAT_PLOCK) == 0);

	/*  Connect the PLL. */
	LPC_SC->PLL0CON  = PLLCON_PLLC | PLLCON_PLLE;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/*  Setup the peripheral bus to be the same as the PLL output (64 MHz). */
	LPC_SC->PCLKSEL0 = 0x05555555;

	/* Configure the LEDs. */
	vParTestInitialise();
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
	/* This function will get called if a task overflows its stack. */

	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}
/*-----------------------------------------------------------*/

void vConfigureTimerForRunTimeStats( void )
{
const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;

	/* This function configures a timer that is used as the time base when
	collecting run time statistical information - basically the percentage
	of CPU time that each task is utilising.  It is called automatically when
	the scheduler is started (assuming configGENERATE_RUN_TIME_STATS is set
	to 1). */

	/* Power up and feed the timer. */
	LPC_SC->PCONP |= 0x02UL;
	LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & (~(0x3<<2))) | (0x01 << 2);

	/* Reset Timer 0 */
	LPC_TIM0->TCR = TCR_COUNT_RESET;

	/* Just count up. */
	LPC_TIM0->CTCR = CTCR_CTM_TIMER;

	/* Prescale to a frequency that is good enough to get a decent resolution,
	but not too fast so as to overflow all the time. */
	LPC_TIM0->PR =  ( configCPU_CLOCK_HZ / 10000UL ) - 1UL;

	/* Start the counter. */
	LPC_TIM0->TCR = TCR_COUNT_ENABLE;
}
/*-----------------------------------------------------------*/

