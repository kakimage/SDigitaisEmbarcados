    // Programa para teste do avr-gcc  
      
#include <inttypes.h>  
#include <avr/io.h>  
#include <stdio.h>
#include <util/delay.h>
#include "digital.h"
#include "uart.h"
#include "spi.h"
   
#define RS 2
#define RW 3
#define E 4

#define D0 5
#define D1 6
#define D2 7

#define D3 8
#define D4 9
#define D5 10
#define D6 11
#define D7 12


#define R_REGISTER 0x00
#define STATUS     0x07

uint8_t le_registrador (uint8_t reg)
{
	uint8_t recebido;


	SPI_enable();
	_delay_us(10);
	SPI_write(R_REGISTER+reg);
	_delay_us(10);
	recebido = 	SPI_write(0xff);
	_delay_us(10);
	SPI_disable();
	return recebido;		
	
}



      
    // Programa Principal  
    int main (void)  
    {  
       	uint8_t lido;

		pinMode(8,OUTPUT);     //CE=1 habilita o chip
		digitalWrite(8,HIGH);  //

		_delay_ms(2000);
        uart_init();
		


        SPI_init (10,11, 12, 13 );
		lido = le_registrador (STATUS);
		printf("lido = %d \n",lido);
		
		

		while (1);
        return 0;
    }  
      
    
