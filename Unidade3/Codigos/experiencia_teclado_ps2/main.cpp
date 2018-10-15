// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                    make flash

#include "src/LPC17xx.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "teclado.h"
#include "uart.h"




int main ( void ) 
{

	SystemInit();
	
	
	 UART0_Init(9600);

	printf("teclado Rodando\n");

	unsigned char a;
	char buff[100];
	int contador=0;

	while(1)
	{
		a = teclado.leTecla();
		if (a=='\r')
		{
			buff[contador]=0;
			contador=0;
			printf("%s\n",buff);
		}
		else buff[contador++]=a;
		
	}
    return 0 ;
}

