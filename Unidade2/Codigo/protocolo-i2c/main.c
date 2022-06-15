// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                    make flash



#ifdef _USA_ARM_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "src/LPC17xx.h"
#include "delay.h"
#include "digital.h"
#include "uart.h"

#else
#include <stdio.h>
#include <string.h>
#endif


#include "memoria.h"
int main ( void ) 
{
	char vetor[]={"UFSC2022 - Eng. de computacao"};
	char buffer[30];

	memoria_init();	
#ifdef _USA_ARM_
	SystemInit();
	UART0_Init(9600);

#endif
	printf("Funcionando\n");
	
	memoria_write(0, 20,  (uint8_t *)vetor, strlen(vetor));
	
	memoria_read (0, 31, (uint8_t *)buffer, 18);

	buffer[18]=0;
	printf("%s\n",buffer);

	
	memoria_flush();
	while(1){
		
	}
    return 0 ;
}

