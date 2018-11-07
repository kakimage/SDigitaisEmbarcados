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
#include "SA_baixo.h"

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

	//SA_format();
	A = SA_fopen ("meu","w");
	B = SA_fopen ("UFSC","w");
	if (( A == NULL) || (B==NULL) )
	{
		printf("Erro tentando criar um arquivo\n");
	}
	else
	{
		printf("criou o arquivo\n");

		for (int x=0; x< 32; x++) SA_fputc(65+x,B);
		for (int x=0; x< 32; x++) SA_fputc(65+x,B);
		SA_fputc('a',B);
		SA_fputc('b',B);
		SA_fseek(B, 0);
		int lido;
		while (!SA_feof(B))
		{
			lido = SA_fgetc(B);
			printf ("%d\n",lido);
		}
		


	}
	
	
    return 0 ;
}

