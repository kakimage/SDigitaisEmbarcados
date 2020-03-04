// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                    make flash

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "src/LPC17xx.h"
#include "uart.h"
#include "adc.h"
#include "delay.h"




int main ( void ) 
{
	
	
	SystemInit();
	UART0_Init(9600);
	printf("Rodando\n");

	uint16_t dado;
	float temp;
	while(1)
	{
		dado = le_adc();
		temp = ((dado * 3.3) / 4095)*100;
		printf("%f\n",temp);
		delay_ms(2000);
	}
	
    return 0 ;
}

