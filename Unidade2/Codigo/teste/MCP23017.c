#include "MCP23017.h"
#include "i2c_software.h"
#include "digital.h"

#define DISPOSITIVO 0x40


uint8_t le_byte (uint8_t dispositivo, uint16_t end)
{
    uint8_t valor;

    i2c_start();
 	   i2c_envia_byte (dispositivo);
	   i2c_envia_byte (end);
	i2c_start();
    i2c_envia_byte (dispositivo|1);
    valor = i2c_envia_byte(0xff);
    i2c_stop();
    return valor;
}


void escreve_byte (uint8_t dispositivo, uint16_t end, uint8_t valor)
{
	
	i2c_start();
	    i2c_envia_byte (dispositivo);
	    i2c_envia_byte (end);
	    i2c_envia_byte (valor);
    i2c_stop();

	while (1)
    {
       i2c_start();
       if (i2c_envia_byte (dispositivo)==0) break;
    }
	i2c_stop();
}

void MCP23017_init (void)
{
	// configura os pinos i2c
	i2c_configura (PIN_0_27, PIN_0_28);     // KIT LAB
	//i2c_configura (PIN_2_05, PIN_1_31);   // MBED
}

void MCP23017_configura_pino (uint8_t pino, uint8_t tipo)
{
	// configura se um determinado pino eh entrada ou saida
	// inicialmente le o registrador IODIRx para saber quais sao entradas e saidas
	// depois, faz uma mascara para ajustar o novo pino como entrada e saida

	uint8_t resposta, porta;

	// descobre se o pino esta na porta A ou B
	if (pino <=7) porta = IODIRA;
	else {
		porta = IODIRB;
		pino  = pino-8;
	}

	// le a configuracao atual de entradas e saidas
	i2c_start();
		resposta=le_byte(DISPOSITIVO, porta);
	i2c_stop();


	// caso senha entrada faz um OR, caso saida faz um and com a negacao bit a bit
	// 1 = input   0 = output
	if (tipo==INPUT) resposta |= (1<<pino);
	else resposta &= ~(1<<pino);
	i2c_start();
		 escreve_byte(DISPOSITIVO, porta, resposta);
	i2c_stop();
}


uint8_t MCP23017_leia_byte (uint8_t pino)
{
	// Le uma porta A ou B, aquela que esta associada ao pino desejado
	// uma leitura do GPIOx le o valor existente na porta

	uint8_t resposta, porta;

	if (pino <=7) porta = GPIOA;
	else {
		porta = GPIOB;
		pino  = pino-8;
	}
	i2c_start();
		resposta=le_byte(DISPOSITIVO, porta);
	i2c_stop();
   
	return resposta;
}
void MCP23017_escreve_pino (uint8_t pino, uint8_t valor)
{
     uint8_t retorno,porta, latch;

    if (pino <8) {
             porta = GPIOA;
             latch = OLATA;
    }
    else{
       porta = GPIOB;
       latch = OLATB;
       pino -=8;
    }

    i2c_start();
		retorno=le_byte(DISPOSITIVO, latch);
	i2c_stop();

    // faz mascara
    if (valor == HIGH) retorno = retorno | (1<<pino);
    else retorno = retorno & ~(1<<pino);
     
    i2c_start();
		 escreve_byte(DISPOSITIVO,porta, retorno);
	i2c_stop();

}
uint8_t MCP23017_leia_pino (uint8_t pino)
{
     uint8_t retorno,porta;

    if (pino <8) porta = GPIOA;
    else{
       porta = GPIOB;
       pino -=8;
    }

   i2c_start();
		retorno=le_byte(DISPOSITIVO, porta);
	i2c_stop();
    return ((retorno >> pino) & 1);
}


