
#include "MCP23S17.h"
#include "spi.h"
#include "digital.h"




void mcp23S17_init (void)
{
	// configura os pinos que serao usados para o CS, SI, SO, SCK
	spi_configura (PIN_1_26, PIN_1_25, PIN_1_24, PIN_1_23);



	//mbed          p20       p19      p18       p17
	//spi_configura (PIN_1_31, PIN_1_30, PIN_0_26, PIN_0_25);



}

void  mcp23S17_configura_pino (uint8_t pino, uint8_t tipo)
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
	spi_habilita();
		spi_write(DISPOSITIVO|1);
		spi_write(porta);
		resposta=spi_write(0x00);
	spi_desabilita();


	// caso senha entrada faz um OR, caso saida faz um and com a negacao bit a bit
	// 1 = input   0 = output
	if (tipo==INPUT) resposta |= (1<<pino);
	else resposta &= ~(1<<pino);
	spi_habilita();
		spi_write(DISPOSITIVO);
		spi_write(porta);
		spi_write(resposta);
	spi_desabilita();   
}


uint8_t mcp23S17_leia_byte (uint8_t pino)
{
	// Le uma porta A ou B, aquela que esta associada ao pino desejado
	// uma leitura do GPIOx le o valor existente na porta

	uint8_t resposta, porta;

	if (pino <=7) porta = GPIOA;
	else {
		porta = GPIOB;
		pino  = pino-8;
	}
	spi_habilita();
		spi_write(0x41);
		spi_write(porta);
		resposta=spi_write(0x00);
	spi_desabilita();
   
	return resposta;
}


void mcp23S17_escreve_pino (uint8_t pino, uint8_t valor)
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

    spi_habilita();
		spi_write(DISPOSITIVO|1);
		spi_write(latch);
		retorno=spi_write(0x00);
    spi_desabilita();

    // faz mascara
    if (valor == HIGH) retorno = retorno | (1<<pino);
    else retorno = retorno & ~(1<<pino);
     
    spi_habilita();
		spi_write(DISPOSITIVO);
		spi_write(porta);
		spi_write(retorno);
    spi_desabilita();

}

uint8_t mcp23S17_le_pino (uint8_t pino)
{
     uint8_t retorno,porta;

    if (pino <8) porta = GPIOA;
    else{
       porta = GPIOB;
       pino -=8;
    }

    spi_habilita();
		spi_write(DISPOSITIVO|1);
		spi_write(porta);
		retorno=spi_write(0x00);
    spi_desabilita();
    return ((retorno >> pino) & 1);
}
