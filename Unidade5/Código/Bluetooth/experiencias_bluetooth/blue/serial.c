// PORTA SERIAL IMPLEMENTADA EM SOFTWARE
// Utiliza o pino 0 como TX (saida digital) e delays de espera ocupada para controlar a temporizacao da transmissao
// Utiliza o pono 2 como RX pois apenas este pino e o pino 3 sao capazes de gerar interrupcao externa
// Ao utilizar o Arduino deve-se ligar um fio entre o pino RX do Arduino (pino D0) com o pino D2

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include "digital.h"
#include "serial.h"
#include "int_ext.h"
#include <avr/interrupt.h>
#include <avr/io.h>  




volatile uint8_t  TEMPO=18;
volatile uint8_t  ESTOURO=252;
volatile uint16_t  taxa_serial;

 volatile  uint8_t PINO_TX;
 volatile  uint8_t PINO_RX;
 volatile  uint8_t contador        = 0;
 volatile  uint8_t recebeu         = 0;
 volatile  uint8_t dados_recebidos = 0;
 volatile  uint8_t palavra         = 0;

 void recebeu_start_bit (void);



inline void delay_us(uint8_t TEMPO)
{
	if (taxa_serial==38400) _delay_us(16);
	else _delay_us(94);
}




void (*funcao)(void);

// ********************** Tratamento da interrupção do timer 0 ********************************  
ISR (TIMER0_OVF_vect)  
{  
	funcao();  
	TCNT0  = ESTOURO;
}  
// ********************************************************************************************


void configura_interrupcao_tempo(void (*f)(void))
{
      // Configura o timer 0  
	  TIFR0 = 1<<TOV0;
 	  TCNT0  = ESTOURO;
      TCCR0A = 0;                     // overflow a cada 256 contagens  
      TCCR0B = _BV(CS01) | _BV(CS00); // Usar clkIO/64: int a cada   
                                       //   64*256/12000 = 1,365 ms  
      TIMSK0 = _BV(TOIE0);            // Interromper no overflow  
	  funcao = f;
     
}  

void habilita_interrupcao_tempo(void)
{
	  TIFR0 = 1<<TOV0;
 	  TCNT0  = ESTOURO;
      TCCR0A = 0;                     // overflow a cada 256 contagens  
      TCCR0B = _BV(CS01) | _BV(CS00); // Usar clkIO/64: int a cada   
                                       //   64*256/12000 = 1,365 ms  
      TIMSK0 = _BV(TOIE0);            // Interromper no overflow  
}

void desabilita_interrupcao_tempo(void)
{
	TIMSK0 = 0; 
    TCCR0B = 0;
	TIFR0 = 1<<TOV0;
}


void serial_envia_msg (char *st)
{
	int8_t x=0;

	while (st[x] != 0)
	{
			serial_envia_letra(st[x]);
			x++;	
	}
}

void serial_envia_letra(char c) {
{
	int8_t x;

	digitalWrite(PINO_TX, LOW);
	//delay_us(TEMPO);
	delay_us(TEMPO);
	for (x=7;x>=0;x--)
	{
		digitalWrite(PINO_TX, (c >> (7-x)) & 0x01);
		//delay_us(TEMPO);
		delay_us(TEMPO);
	 
	}
	digitalWrite(PINO_TX, HIGH); //STOP
	delay_us(TEMPO);
	delay_us(TEMPO);
	
	
}      
}



uint8_t serial_software_dados_disponiveis(void)
{
	return recebeu;
}

char serial_recebe_letra(void) {
 	volatile uint8_t d;
	while (!recebeu);
	cli();
		d = dados_recebidos;
		recebeu = 0;
	sei();
	return d;
}


void recebeu_bit (void)
{
	if (contador >=0 && contador <=7)
	{
        palavra = palavra | (digitalRead(PINO_RX) << contador);
		//pega bits de dados e coloca em palavra
		contador++;
	}
	
	else 
	{
		desabilita_interrupcao_tempo();
        configura_interrupcao_externa(INT0, PINO_RX, recebeu_start_bit);
		dados_recebidos = palavra;
        palavra         = 0;
		recebeu         = 1;
		contador        = 0;
	}
	
}

void recebeu_start_bit (void)
{
	desabilita_interrupcao_externa(INT0);
	configura_interrupcao_tempo(recebeu_bit);
	pinMode(PINO_RX, INPUT);
}

void serial_configura (uint16_t taxa, uint8_t pino_TX, uint8_t pino_RX)
{
	taxa_serial = taxa;
	PINO_TX = pino_TX;
	PINO_RX = pino_RX;

   
	pinMode(PINO_TX, OUTPUT);
	pinMode(PINO_RX, INPUT);


	digitalWrite(PINO_TX, HIGH);
	_delay_ms(10);

	switch (taxa)
	{
		case 9600:
			TEMPO=94;
			ESTOURO=230;
			break;
		case 38400:
			TEMPO=18;
			ESTOURO=252;
	}
	configura_interrupcao_externa(INT0, pino_RX, recebeu_start_bit);
	_delay_ms(100);
	sei();
}







