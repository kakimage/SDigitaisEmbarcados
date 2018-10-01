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

	while(1)
	{
		a = teclado.leTecla();
		printf("%c\n",a);
	}
    return 0 ;
}

