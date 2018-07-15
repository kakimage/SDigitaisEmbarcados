#include "digital.h"
#include <stdio.h>
#include "tarefa.h"


 uint8_t pinoSDA, pinoSCL;
 
 void SDA (uint8_t valor)
 {
 	if (valor==HIGH)
 	{
 		Digital.pinMode(pinoSDA, INPUT);
 	}
 	else
 	{
 		 Digital.pinMode(pinoSDA, OUTPUT);
 		 Digital.digitalWrite(pinoSDA, LOW);
 	}
 }
 void SCL (uint8_t valor)
 {
 	if (valor==HIGH)
 	{
 		Digital.pinMode(pinoSCL, INPUT);
 	}
 	else
 	{
 		 Digital.pinMode(pinoSCL, OUTPUT);
 		 Digital.digitalWrite(pinoSCL, LOW);
 	}
 }
 void i2c_start(void )
 {
       SCL(HIGH);
     delay_ms(1);
     SDA(HIGH);
     delay_ms(1);
     SDA(LOW);
    delay_ms(1);
     SCL(LOW);
   delay_ms(1);  
 	
 }
 void i2c_stop(void )
 {
  SDA(LOW);
  SCL(HIGH);
  delay_ms(2);
  SDA(HIGH);
  SCL(LOW);
  SDA(LOW);
  delay_ms(10);
 }
 void i2c_init(uint8_t scl, uint8_t sda)
 {
 	printf("i2c_init\n");
 	pinoSCL = scl;
 	pinoSDA = sda;
 	
 	SDA(HIGH);
 	SCL(HIGH);
 	delay_ms(10);
 	
 }
 
uint8_t i2c_le_bit (void)
{
    uint8_t valor;
  
  	SDA(HIGH);
    delay_us(10);
    SCL(HIGH);
    valor = Digital.digitalRead(pinoSDA);
    delay_us(10);
    SCL(LOW);
    return valor;
}

uint8_t i2c_le_byte (void)
{
 	printf("i2c_le_byte\n");
	uint8_t d=0;
  SCL(LOW);

  for (uint8_t x=0; x<8;x++)
  {
    d = (d << 1) | i2c_le_bit();
  }
  return d;
}

 uint8_t i2c_escreve_byte (uint8_t dado)
 {
 	printf("i2c_escreve_byte\n");
  SCL(LOW);
  for (uint8_t x=0; x<8;x++)
  {
    if ((dado & 0x80) == 0) SDA(LOW);
    else SDA(HIGH);
    dado = dado << 1;
    SCL(HIGH);
        delay_us(20);
    SCL(LOW);
    delay_us(20);
  }
  return i2c_le_bit();
 }
 
 
