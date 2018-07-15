#include <inttypes.h>
#include "digital.h"
#include "spi.h"
#include "delay.h"

uint8_t PIN_CS, PIN_SI, PIN_SO, PIN_CLK;
#define TEMPO 2


void pino_SPI (uint8_t pin, uint8_t valor)
{
	digitalWrite(pin,valor);
}
uint8_t le_SPI (uint8_t pin)
{
	
	return digitalRead(pin);
}

void spi_configura (uint8_t pin_cs, uint8_t pin_si, uint8_t pin_so, uint8_t  pin_clk)
{
	PIN_CS  = pin_cs;
	PIN_SI  = pin_si;
	PIN_SO  = pin_so;
	PIN_CLK = pin_clk;

	pinMode(PIN_SI, INPUT);
	pinMode(PIN_CS, OUTPUT);
	pinMode(PIN_SO, OUTPUT);	
	pinMode(PIN_CLK, OUTPUT);
	pino_SPI(PIN_CS, HIGH);
	pino_SPI(PIN_SO, LOW);
	pino_SPI(PIN_CLK, LOW);
}
void spi_habilita (void)
{
	pino_SPI(PIN_CS,LOW);
}
void spi_desabilita (void)
{
	pino_SPI(PIN_CS, HIGH);
}

uint8_t spi_write (uint8_t dado)
{
	volatile int8_t x;
	volatile uint8_t lido=0;

	for (x=7;x>=0;x--)
	{
		pino_SPI(PIN_SO, dado>>x);
		_delay_us(TEMPO);
		pino_SPI(PIN_CLK, HIGH);
		_delay_us(TEMPO);
		lido = lido | (le_SPI(PIN_SI)<<x);
		pino_SPI(PIN_CLK, LOW);		
		_delay_us(TEMPO);
		
	}	
	return lido;
}

