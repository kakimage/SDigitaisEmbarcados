#include <stdio.h>
#include "SA.h"

int main (void)
{
	char vet[]="FABIO ROCHA";
	formata();
	
	MEU_FILE *A, *B;
	
	A = meu_fopen ("teste","w");
	if (A==NULL)
	{
		printf("Nao consegue criar o arquivo\n");
	}
	
	for (char x=0;x<32;x++) meu_fputc(x, A); 

	meu_fputc(100, A); 
	meu_fputc(200, A); 
	
	
	
}
