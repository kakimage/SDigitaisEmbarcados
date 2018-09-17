#include "display.h"
#include "digital.h"
#include <string.h>

#include <ctype.h>


char vetor_pinos[]   ={SEGA,SEGB,SEGC,SEGD,SEGE,SEGF,SEGG};
char vetor_enable[]  ={ENABLE_DISP0,ENABLE_DISP1,ENABLE_DISP2,ENABLE_DISP3};
char vetor_simbolos[]={ 0x3f , 0x06, 0x5b, 0x4f };

char digitos[4]={'0','0','0','0'};

volatile uint32_t delay;


void fazDelay(void)
{
	for(delay = 0; delay < 10000; delay++) {
    	   __asm("NOP");
	}
}	


void mostra (char *st)
{
	int x, p;


	p = 4 - strlen(st);
	x = 0;
	while (st[x] != 0)
	{
		digitos[p+x] = st[x];
		x++;
	}

	
	
	while (1)
	{
		for (x = 0; x<4;x++) display(x,digitos[x]);
	}
}
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
void display(int disp, char c)
{
	char k;

	for (int x=0;x<=3;x++) digitalWrite(vetor_enable[x],LOW);	
	digitalWrite(vetor_enable[disp],HIGH);
	
	if (isdigit(c)) k = vetor_simbolos[c-'0'];
	else k = vetor_simbolos[c-55];

	for (int x=0;x<7;x++)
	{
		if (k & (1<< x)) digitalWrite(vetor_pinos[x], HIGH);
		else digitalWrite(vetor_pinos[x], LOW);
	}
	fazDelay();
}