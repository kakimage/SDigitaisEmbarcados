// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                    make flash

#include "src/LPC17xx.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "digital.h"
#include "uart.h"
#include "i2c_software.h"
#include "delay.h"


int main ( void ) 
{
	char vetor[]={"Oi mundo"};
	char buffer[20];
	SystemInit();
	
	i2c_configura(PIN_0_27, PIN_0_28);
	UART0_Init(9600);
	printf("Rodando\n");
		uint8_t ack,dado=0;


	i2c_sequencial_write(0, 10, (uint8_t *)vetor, 8);

	i2c_sequencial_read(0, 10, (uint8_t *)buffer, 8);

	buffer[8]=0;
	printf("%s\n",buffer);

	while(1){
		
	}
    return 0 ;
}

