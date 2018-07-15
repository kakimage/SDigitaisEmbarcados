#include <inttypes.h>
#include "digital.h"
#include "spi.h"
#include <util/delay.h>
#include "uart.h"

SoftwareSPI SPI;

SoftwareSPI::SoftwareSPI (void)
{
#ifdef DEBUG_SPI
	printf("spi.cpp:linha:%d SoftwareSPI (void)\n",__LINE__);
#endif
}


SoftwareSPI::SoftwareSPI (uint8_t pin_cs, uint8_t pin_si, uint8_t pin_so, uint8_t  pin_clk)
{
#ifdef DEBUG_SPI
	printf("spi.cpp:linha:%d SoftwareSPI (uint8_t pin_cs, uint8_t pin_si, uint8_t pin_so, uint8_t  pin_clk)\n",__LINE__);
#endif
	PINO_CS  = pin_cs;
    PINO_SI  = pin_si;
    PINO_SO  = pin_so;
    PINO_CLK = pin_clk;

    pinos.pinMode(PINO_CS, OUTPUT);
    pinos.pinMode(PINO_SI, INPUT);
    pinos.pinMode(PINO_SO, OUTPUT);
    pinos.pinMode(PINO_CLK, OUTPUT);

    pinos.digitalWrite(PINO_CS, HIGH);
    pinos.digitalWrite(PINO_SO, LOW);
    pinos.digitalWrite(PINO_CLK, LOW);
    _delay_ms(1);
}
void SoftwareSPI::habilita (void)
{
	pinos.digitalWrite(PINO_CS,LOW);
}
void SoftwareSPI::desabilita (void)
{
	pinos.digitalWrite(PINO_CS, HIGH);
}

uint8_t SoftwareSPI::write (uint8_t dado)
{
	volatile int8_t x;
	volatile uint8_t lido=0;

	for (x=7;x>=0;x--)
	{
		pinos.digitalWrite(PINO_SO, dado>>x);
		_delay_us(TEMPO);
		pinos.digitalWrite(PINO_CLK, HIGH);
		_delay_us(TEMPO);
		lido = lido | (pinos.digitalRead(PINO_SI)<<x);
		pinos.digitalWrite(PINO_CLK, LOW);
		_delay_us(TEMPO);
	}	
	return lido;

}

