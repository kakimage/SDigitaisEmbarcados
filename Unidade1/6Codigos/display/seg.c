
#include "seg.h"
#include "delay.h"
#include "digital.h"


 uint8_t SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG;
 uint8_t DISPLAY0,DISPLAY1, DISPLAY2, DISPLAY3;
  
 uint8_t disp[]={0x3f,0x06, 0x5b, 0x4f, 0x66, 0xcd,0x7d,0x07,0x7f,0x6f};
  
void configuraDisplay( uint8_t pSEGA,  uint8_t pSEGB, uint8_t pSEGC,  uint8_t pSEGD,  uint8_t pSEGE,  uint8_t pSEGF,  uint8_t pSEGG,  uint8_t pDISPLAY0, uint8_t pDISPLAY1,  uint8_t pDISPLAY2,  uint8_t pDISPLAY3)
{
	SEGA = pSEGA;
	SEGB = pSEGB;
	SEGC = pSEGC;
	SEGD = pSEGD;
	SEGE = pSEGE;
	SEGF = pSEGF;
	SEGG = pSEGG;
	DISPLAY0 = pDISPLAY0;
	DISPLAY1 = pDISPLAY1;
	DISPLAY2 = pDISPLAY2;
	DISPLAY3 = pDISPLAY3;

	  pinMode( SEGA, OUTPUT);
  pinMode( SEGB, OUTPUT);
  pinMode( SEGC, OUTPUT);
  pinMode( SEGD, OUTPUT);
  pinMode( SEGE, OUTPUT);
  pinMode( SEGF, OUTPUT);
  pinMode( SEGG, OUTPUT);
  pinMode(DISPLAY0, OUTPUT);
  pinMode(DISPLAY1, OUTPUT);
  pinMode(DISPLAY2, OUTPUT);
  pinMode(DISPLAY3, OUTPUT);
}

  
void mostra (uint16_t valor)
{
	uint8_t digitos[4];
	uint16_t divisor=1000;
	
	for (int a=0;a<4;a++)
	{
		digitos[a]=valor/divisor;
		valor = valor - digitos[a]*divisor;
		divisor=divisor/10;
	}
	
	uint8_t podeOmitir;
	while (1)
	{
		podeOmitir = 1;
		for (int b=0; b< 4;b++)
		{
			if (digitos[b] != 0) podeOmitir=0;
			
			if (!podeOmitir) mostraDisplay(b, digitos[b]);
			
			delay_ms();
		}
	}
	
	
}


void mostraDisplay (uint8_t numero_display, uint8_t valor)
{
  uint8_t v[]={DISPLAY0,DISPLAY1,DISPLAY2,DISPLAY3};
	
  digitalWrite(SEGA, HIGH);
  digitalWrite(SEGB, HIGH);
  digitalWrite(SEGC, HIGH);
  digitalWrite(SEGD, HIGH);
  digitalWrite(SEGE, LOW);
  digitalWrite(SEGF, LOW);
  digitalWrite(SEGG, HIGH);
  digitalWrite(DISPLAY0, LOW);
  digitalWrite(DISPLAY1, LOW);
  digitalWrite(DISPLAY2, LOW);
  digitalWrite(DISPLAY3, LOW);
  
  
  digitalWrite(v[numero_display], HIGH);
  
  digitalWrite(SEGA, disp[valor]&1);
  digitalWrite(SEGB, (disp[valor]>>1)&1);
  digitalWrite(SEGC, (disp[valor]>>2)&1);
  digitalWrite(SEGD, (disp[valor]>>3)&1);
  digitalWrite(SEGE, (disp[valor]>>4)&1);
  digitalWrite(SEGF, (disp[valor]>>5)&1);
  digitalWrite(SEGG, (disp[valor]>>6)&1);
  
}
