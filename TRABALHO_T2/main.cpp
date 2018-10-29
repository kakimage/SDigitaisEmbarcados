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
#include "memoria.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "SA_baixo.h"
#endif

int main ( void ) 
{
	
	
#ifdef _USA_ARM_
	SystemInit();
	UART0_Init(9600);
#endif
	memoria_init();

	SA_FILE *A, *B;

	SA_format();
	A = SA_fopen ("meu","w");
	B = SA_fopen ("UFSC","w");
	if (( A == NULL) || (B==NULL) )
	{
		printf("Erro tentando criar um arquivo\n");
	}
	else
	{
		printf("criou o arquivo\n");

		//SA_fputc('X',A);
		SA_fputc('Y',B);

		for (int x=0; x< 31; x++) SA_fputc(65+x,B);
		
			SA_fputc('a',B);
	}
	
	
    return 0 ;
}

