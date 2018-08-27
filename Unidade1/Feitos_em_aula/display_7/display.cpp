#include "display.h"
#include "digital.h"
#include <ctype.h>


char vetor_pinos[]   ={SEGA,SEGB,SEGC,SEGD,SEGE,SEGF,SEGG};
char vetor_enable[]  ={ENABLE_DISP0,ENABLE_DISP1,ENABLE_DISP2,ENABLE_DISP3};
char vetor_simbolos[]={ 0 , 0x06, 0x5b };

void display_init(void)
{
	// configura os pinos como saidas   ENABLE
	for (int x=0;x<=3;x++) 
	{
		pinMode(vetor_enable[x],OUTPUT);
		digitalWrite(vetor_enable[x],HIGH);	
	}

	// configura os pinos como saidas   Barramento
	for (int x=0;x<7;x++) 
	{
		pinMode(vetor_pinos[x],OUTPUT);
		digitalWrite(vetor_pinos[x],HIGH);	
	}
	

}
void display(char c)
{
	char k;

	if (isdigit(c)) k = vetor_simbolos[c-'0'];
	else k = vetor_simbolos[c-55];

	for (int x=0;x<7;x++)
	{
		if (k & (1<< x)) digitalWrite(vetor_pinos[x], HIGH);
		else digitalWrite(vetor_pinos[x], LOW);
	}
}