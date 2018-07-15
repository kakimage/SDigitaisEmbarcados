
#include "delay.h"
#include "lcd.h"
#include "digital.h"


uint8_t	pino_RS;

uint8_t	pino_E;
uint8_t	pino_D0;
uint8_t	pino_D1;
uint8_t	pino_D2;
uint8_t	pino_D3;
uint8_t	pino_D4;
uint8_t	pino_D5;        
uint8_t	pino_D6;
uint8_t	pino_D7;


void lcd_envia_byte (uint8_t valor)
{
	
	digitalWrite (pino_D0, valor);
	digitalWrite (pino_D1, valor>>1);
	digitalWrite (pino_D2, valor>>2);
	digitalWrite (pino_D3, valor>>3);
	digitalWrite (pino_D4, valor>>4);
	digitalWrite (pino_D5, valor>>5);
	digitalWrite (pino_D6, valor>>6);
	digitalWrite (pino_D7, valor>>7);

    digitalWrite (pino_E, HIGH);
	delay_ms(4);
    digitalWrite (pino_E, LOW);


	delay_ms(10);
}

void lcd_limpa_tela (void)
{
	digitalWrite(pino_RS, LOW);
	lcd_envia_byte(0x01);
	
	digitalWrite(pino_RS, HIGH);

}

void lcd_desloca (void)
{
	digitalWrite(pino_RS, LOW);
	lcd_envia_byte(0x14);
	
	digitalWrite(pino_RS, HIGH);
}


void lcd_escreve (char st[])
{
	uint8_t  x=0;

	while (st[x]!=0) {
		lcd_envia_byte(st[x]);
		x++;
	}

    delay_ms(6);
}

void lcd_init (uint8_t RS,  uint8_t E, uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7)
{
    delay_ms(400);
	pino_RS = RS;

	pino_E  = E;
	pino_D0 = D0;
	pino_D1 = D1;
	pino_D2 = D2;
	pino_D3 = D3;
	pino_D4 = D4;
	pino_D5 = D5;
	pino_D6 = D6;
	pino_D7 = D7;

    pinMode(pino_RS, OUTPUT);
	pinMode(pino_E,  OUTPUT);	
	pinMode(pino_D0, OUTPUT);
	pinMode(pino_D1, OUTPUT);
	pinMode(pino_D2, OUTPUT);
	pinMode(pino_D3, OUTPUT);
	pinMode(pino_D4, OUTPUT);
	pinMode(pino_D5, OUTPUT);
	pinMode(pino_D6, OUTPUT);
	pinMode(pino_D7, OUTPUT);


    digitalWrite(pino_RS, LOW);
    digitalWrite(pino_E,  LOW);

    delay_ms(40);

    lcd_envia_byte(0x30);
    lcd_envia_byte(0x30);
    lcd_envia_byte(0x30);
    lcd_envia_byte(0x0F);
    lcd_envia_byte(0x38);
	lcd_envia_byte(0x02);
	lcd_envia_byte(0x01);
    // coloca no modo de dados
    digitalWrite(pino_RS, HIGH);
    delay_ms(30);
	

}
