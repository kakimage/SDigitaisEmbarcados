
#include "MCP23017.h"
#include "i2c_software.h"
#include "digital.h"



void mcp23017_init (void)
{
	//i2c_configura (PIN_0_27, PIN_0_28);
	i2c_configura (PIN_2_05, PIN_1_31);   // MBED
}

void mcp23017_escreve_pino(uint8_t pino, uint8_t valor)
{
	uint8_t registrador_GPIO  = GPIOA;
	uint8_t registrador_LATCH = OLATCHA;
	uint8_t lido;

	if (pino>7)		{
		registrador_GPIO  = GPIOB;
		registrador_LATCH = OLATCHB;
		pino = pino - 8;
	}

	i2c_start();
		lido=i2c_le_byte (DISPOSITIVO, registrador_LATCH);
	i2c_stop();
	
	if (valor==LOW)	lido = lido & ~(1<<pino) ;
	else lido = lido | (1<<pino);

	i2c_start();
		i2c_escreve_byte (DISPOSITIVO, registrador_GPIO, lido);
	i2c_stop();
	
}
uint8_t mcp23017_le_pino(uint8_t pino)
{
	uint8_t registrador=GPIOA;
	uint8_t valor;


	if (pino>7)		{
		registrador = GPIOB;
		pino = pino - 8;
	}
	i2c_start();
		valor=i2c_le_byte (DISPOSITIVO, registrador);
	i2c_stop();
    return ((valor>>pino) & 1);
}


void mcp23017_configura_pino( uint8_t pino, uint8_t tipo)
{
	uint8_t registrador=IODIRA;
	uint8_t valor;

	if (pino>7)		{
		registrador = IODIRB;
		pino = pino - 8;
	}
	

	i2c_start();
		valor=i2c_le_byte (DISPOSITIVO, registrador);
	i2c_stop();

	if (tipo==OUTPUT)	valor = valor & ~(1<<pino) ;
	else valor = valor | (1<<pino);

	i2c_start();
		i2c_escreve_byte (DISPOSITIVO, registrador, valor);
	i2c_stop();

}

