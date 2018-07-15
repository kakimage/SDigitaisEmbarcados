#include "lcd.h"
#include "tarefa.h"
#include "digital.h"


void meuLCD::init (void)
{
	tarefa.start();
	delay_ms(30);
	Digital.pinMode(B0, OUTPUT);
	Digital.pinMode(B1, OUTPUT);
	Digital.pinMode(B2, OUTPUT);	
	Digital.pinMode(B3, OUTPUT);	
	Digital.pinMode(B4, OUTPUT);
	Digital.pinMode(B5, OUTPUT);
	Digital.pinMode(B6, OUTPUT);
	Digital.pinMode(B7, OUTPUT);
	
	Digital.pinMode(E, OUTPUT);
	Digital.pinMode(RS, OUTPUT);

	modo(COMANDO);
	escreve(CLS);
	escreve(CONFIGURA_LCD);
	escreve(CONTROLE_DISPLAY);
	escreve(FIXA);
	modo(DADO);
}

void meuLCD::modo (int modo)
{
	Digital.digitalWrite(RS, modo);	
}

void meuLCD::escreve (char *st)
{	
	int x=0;
	while (st[x] != 0)
	{
		escreve(st[x]);
		x++;
	}
}
void meuLCD::escreve (char d)
{
	Digital.digitalWrite(B7, (d>>7) );
	Digital.digitalWrite(B6, (d>>6) & 1 );
	Digital.digitalWrite(B5, (d>>5) & 1 );
	Digital.digitalWrite(B4, (d>>4) & 1 );
	Digital.digitalWrite(B3, (d>>3) & 1 );
	Digital.digitalWrite(B2, (d>>2) & 1 );
	Digital.digitalWrite(B1, (d>>1) & 1 );
	Digital.digitalWrite(B0, d & 1 );
	
	Digital.digitalWrite(E, HIGH);
	delay_ms(2);
	Digital.digitalWrite(E, LOW);
	delay_ms(3);	
}

void meuLCD::clear (void)
{
	
}

void meuLCD::gotoxy (int x, int y)
{
	
}









meuLCD LCD;
