// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                    make flash


#ifdef _USA_ARM_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "memoria.h"
#include "src/LPC17xx.h"
#include "delay.h"
#include "digital.h"
#include "uart.h"

#else
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "SA.h"
#endif

int main ( void ) 
{
	char vetor[]={"UFSC2018"};
	char buffer[20];
	
#ifdef _USA_ARM_
	SystemInit();
	UART0_Init(9600);
#endif
	
	int x=4, y=0;


	SA_format();
	SA_FILE *A;

	SA_fopen ("teste","w");
	SA_fwrite();
	
	printf("Rodando\n");
	printf("divide=%d",x/y);
		uint8_t ack,dado=0;


	memoria_write(0, 20,  (uint8_t *)vetor, 8);
	memoria_read (0, 20, (uint8_t *)buffer, 8);

	buffer[8]=0;
	printf("%s\n",buffer);

	while(1){
		
	}
    return 0 ;
}

