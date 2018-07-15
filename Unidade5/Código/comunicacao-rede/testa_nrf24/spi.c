#include <stdio.h>
#include "spi.h"
#include "digital.h"
#include "uart.h"
#include <util/delay.h> 

uint8_t PINO_CS;
uint8_t PINO_SI;
uint8_t PINO_SO;
uint8_t PINO_SCK;



void SPI_init (uint8_t pino_cs,uint8_t pino_si, uint8_t pino_so, uint8_t pino_sck )
{
    PINO_CS  = pino_cs;
    PINO_SI  = pino_si;
    PINO_SO  = pino_so;
    PINO_SCK = pino_sck;

    pinMode(PINO_CS, OUTPUT);
    pinMode(PINO_SI, OUTPUT);
    pinMode(PINO_SO, INPUT);
    pinMode(PINO_SCK, OUTPUT);

    digitalWrite(PINO_CS, HIGH);
    digitalWrite(PINO_SI, HIGH);
    digitalWrite(PINO_SCK, LOW);
    _delay_ms(1);

    


   
}
void SPI_enable(void)
{
   digitalWrite(PINO_CS, LOW);
}

uint8_t SPI_write_bit (uint8_t bit)
{   
    uint8_t lido;

    digitalWrite(PINO_SI, bit);
    digitalWrite(PINO_SCK, HIGH);
    _delay_us(10);
    lido=digitalRead(PINO_SO);
    digitalWrite(PINO_SCK, LOW);

  
    return lido;  
}

uint8_t SPI_write(uint8_t valor)
{
    uint8_t lido=0,x;
    for (x=0;x<8;x++)
    {
       lido<<=1;
       lido = lido | SPI_write_bit(valor >> 7);
       valor<<=1;
    }
    return lido;
}

void SPI_disable(void)
{
  digitalWrite(PINO_CS, HIGH);
}
