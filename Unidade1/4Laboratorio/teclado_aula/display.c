#include "display.h"
#include "LPC17xx.h"
#include "digital.h"
#include "timer.h"

void mostra (uint8_t alvo, uint8_t caracter);
void atualiza_displays (void);

uint8_t numeros_globais[4];
uint8_t display[]={63,6, 0x5b,0x4f,0x66,0x6d ,0x7d,0x07, 0x7f, 0x6f };


void display_configura (void)
{
  
  timer_init (atualiza_displays, 200);
  pinMode(SEGA, OUTPUT);
  pinMode(SEGB, OUTPUT);
  pinMode(SEGC, OUTPUT);
  pinMode(SEGD, OUTPUT);
  pinMode(SEGE, OUTPUT);
  pinMode(SEGF, OUTPUT);
  pinMode(SEGG, OUTPUT);
   
  pinMode(HABILITA_DISPLAY0, OUTPUT);
  pinMode(HABILITA_DISPLAY1, OUTPUT);
  pinMode(HABILITA_DISPLAY2, OUTPUT);
  pinMode(HABILITA_DISPLAY3, OUTPUT);
 
  digitalWrite(HABILITA_DISPLAY0, LOW);
  digitalWrite(HABILITA_DISPLAY1, LOW);
  digitalWrite(HABILITA_DISPLAY2, LOW);
  digitalWrite(HABILITA_DISPLAY3, LOW);
}

void mostra (uint8_t alvo, uint8_t caracter)
{
    uint8_t v;
	uint32_t disp[]=			{HABILITA_DISPLAY0,HABILITA_DISPLAY1,HABILITA_DISPLAY2,HABILITA_DISPLAY3};

    digitalWrite(HABILITA_DISPLAY0, LOW); 
    digitalWrite(HABILITA_DISPLAY1, LOW);  
    digitalWrite(HABILITA_DISPLAY2, LOW);  
    digitalWrite(HABILITA_DISPLAY3, LOW);  
 
    v = display[caracter];
    if (v & 1)      digitalWrite(SEGA, HIGH);
    else digitalWrite(SEGA, LOW);

    if ((v>>1) & 1) digitalWrite(SEGB, HIGH);
    else digitalWrite(SEGB, LOW);    
    
    if ((v>>2) & 1) digitalWrite(SEGC, HIGH);
    else digitalWrite(SEGC, LOW);

    if ((v>>3) & 1) digitalWrite(SEGD, HIGH);
    else digitalWrite(SEGD, LOW);

    if ((v>>4) & 1) digitalWrite(SEGE, HIGH);
    else digitalWrite(SEGE, LOW);

    if ((v>>5) & 1) digitalWrite(SEGF, HIGH);
    else digitalWrite(SEGF, LOW);

    if ((v>>6) & 1) digitalWrite(SEGG, HIGH);
    else digitalWrite(SEGG, LOW);  

    digitalWrite(disp[alvo], HIGH);
 

}


void atualiza_displays (void) {
   static uint8_t display_da_vez=0;
 
  	mostra(display_da_vez, numeros_globais[display_da_vez]);
  	display_da_vez++;
  	if (display_da_vez ==4) display_da_vez=0;
 
}


void display_7seg (uint16_t numero)
{
 	
    uint8_t x, d;
    uint16_t DIVISOR;
   

    DIVISOR = 1000;
    for (x=0;x<4;x++)
    {
        d = numero / DIVISOR;
        numero = numero % DIVISOR;
        DIVISOR = DIVISOR/10;
		numeros_globais[x]=d;
    }
}

