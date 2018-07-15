#include "serial.h"
#include "digital.h"
#include "delay.h"
#include <stdio.h>


#define stduart (LPC_UART_TypeDef *)LPC_UART0_BASE



#define TEMPO 104


volatile uint8_t PINO_TX = PIN_0_02;
volatile uint8_t PINO_RX = PIN_0_03;


int _write (int fd, const void *buf, size_t count)
{
	uint8_t x;
	char *vet = (char *) buf;

	for (x=0;x<count;x++) serial_envia_letra(  vet[x]);
	return count;
}


void serial_envia_letra(char c) 
{
	int8_t x;

	digitalWrite(PINO_TX, LOW);
	delay_us(TEMPO);

	for (x=7;x>=0;x--)
	{
		digitalWrite(PINO_TX, (c >> (7-x)) & 0x01);
		delay_us(TEMPO); 
	}
	digitalWrite(PINO_TX, HIGH); //STOP
	delay_us(TEMPO*2);       
}      

void serial_configura (void)
{
 
  //  LPC_PINCON->PINSEL0 = 0;
	pinMode(PINO_TX, OUTPUT);
	pinMode(PINO_RX, INPUT);


	digitalWrite(PINO_TX, LOW);
	
	delay_ms(100);	
}

