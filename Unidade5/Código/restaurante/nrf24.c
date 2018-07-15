#include <stdio.h>
#include "digital.h"
#include "nrf24.h"
#include "spi.h"
#include "delay.h"
#include <avr/interrupt.h>
#include "interrupcao_externa.h"

void modo_RX(void);
void modo_TX(void);
void nrf24_flush_TX (void);
//void reset (void);
void limpa_FIFO(void);
void nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[]);

uint8_t pino_CE;
volatile uint8_t nova_msg=0;
volatile uint8_t MSG_RECEBIDA[20];

void MEU_TRATADOR_INT_EXT (void)
{
	uint8_t x,valor;
	uint16_t crc_calculado=0xff, crc_recebido;

	CE_LOW();
	spi_habilita();
		spi_write(R_RX_PAYLOAD);
		for (x=0;x<6;x++) 
		{
			MSG_RECEBIDA[x] = spi_write(0xff);
			crc_calculado = crc_calculado + MSG_RECEBIDA[x];
		}
		crc_recebido  = spi_write(0xff)<<8;
		crc_recebido |= spi_write(0xff);
		//if (crc_recebido == crc_calculado ) 
		nova_msg=1;	
	spi_desabilita();
	
	spi_habilita();
		spi_write(FLUSH_RX);
	spi_desabilita();

    valor=0x70;
	nrf24_escreve_registrador (STATUS,1,(uint8_t *)&valor);
	
	
	CE_HIGH();
	_delay_ms(1);
	
	
}
void CE_HIGH(void)
{
	digitalWrite(pino_CE, HIGH);
}
void CE_LOW(void)
{
	digitalWrite(pino_CE, LOW);
}
void power_DOWN (void)
{
	uint8_t reg_config;

	reg_config = le_registrador(CONFIG);

	reg_config = reg_config & 0xFD; 
	nrf24_escreve_registrador(CONFIG,1,(uint8_t *)&reg_config);
}
void power_UP (void)
{
	uint8_t reg_config;

	reg_config = le_registrador(CONFIG);
	reg_config = reg_config | 0x02; 
	nrf24_escreve_registrador(CONFIG,1,(uint8_t *)&reg_config);
}
void nrf24_init (void)
{
	uint8_t parametros[5];

	// configura os pinos que serao usados para o CSN, MISO, MOSI, SCK
	_delay_ms(100);
	spi_configura (10,12,11,13);
	pino_CE = 8;
	pinMode(pino_CE, OUTPUT);
	CE_LOW();
	power_DOWN();
	_delay_ms(300);
	

	limpa_FIFO();	
	
	parametros[0] = 0x01;
    nrf24_escreve_registrador (EN_RXADDR, 1, parametros);

	
    
	parametros[0] = 0x00;
    nrf24_escreve_registrador (EN_AA, 1, parametros);

	parametros[0] = 0x01;
    nrf24_escreve_registrador (SETUP_AW, 1, parametros);
	
	

	parametros[0] = 0x01;
    nrf24_escreve_registrador (RF_CH, 1, parametros);


	parametros[0]=0;
	nrf24_escreve_registrador (SETUP_RETR, 1, parametros);

	parametros[0] = 0x26;
    nrf24_escreve_registrador (RF_SETUP, 1, parametros);

	parametros[0] = 0x10;
	parametros[1] = 0x10;
	parametros[2] = 0x10;
	
    nrf24_escreve_registrador (RX_ADDR_P0, 3, parametros);

	parametros[0] = 0x20;
	parametros[1] = 0x20;
	parametros[2] = 0x20;
	nrf24_escreve_registrador (TX_ADDR, 3, parametros);

	parametros[0] = TAMANHO_MSG;
	nrf24_escreve_registrador (RX_PW_P0, 1, parametros);

	

	parametros[0]=0x70;
	nrf24_escreve_registrador (STATUS,1,parametros);


	parametros[0]=0x11;
	nrf24_escreve_registrador (FIFO_STATUS, 1, parametros);


	configura_interrupcao_externa(MEU_TRATADOR_INT_EXT);


	parametros[0] = 0x37;
    nrf24_escreve_registrador (CONFIG, 1, parametros);
	

	limpa_FIFO();
	//reset();
	power_UP();
	CE_HIGH();
	_delay_ms(200);
	
	sei();
	
	
}

void nrf24_endereco(uint8_t rx, uint8_t tx)
{
	uint8_t parametros[5];
	parametros[0] = rx;
	parametros[1] = rx;
	parametros[2] = rx;
	
    nrf24_escreve_registrador (RX_ADDR_P0, 3, parametros);

	parametros[0] = tx;
	parametros[1] = tx;
	parametros[2] = tx;
	nrf24_escreve_registrador (TX_ADDR, 3, parametros);
}

void nrf24_transmite(uint8_t buffer[])
{
	uint8_t x, status, valor;
	uint16_t crc = 0xff;
   
	cli();
		CE_LOW();
   		modo_TX();
		
		
		spi_habilita();
			spi_write(FLUSH_TX);
		spi_desabilita();
		
	
		spi_habilita();
			spi_write(W_TX_PAYLOAD);
			for (x=0;x<TAMANHO_MSG-2;x++)
			{
				crc = crc + buffer[x];
				spi_write(buffer[x]);
			}
			spi_write(crc>>8);
			spi_write(crc);
		spi_desabilita();
	uint8_t reg_config;

	_delay_ms(10);
	CE_HIGH();
	_delay_us(20);
	CE_LOW();
	_delay_ms(10);
	

	
		modo_RX();
		CE_HIGH();
		 valor=0x70;
		_delay_ms(1);
		nrf24_escreve_registrador (STATUS,1,(uint8_t *)&valor);

		sei();
	



}


void modo_TX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	nrf24_le_registrador(1,CONFIG, &reg_config);
	reg_config = (   (reg_config | _BV(PWR_UP) )    & ~_BV(PRIM_RX));
	nrf24_escreve_registrador(CONFIG,1,(uint8_t *)&reg_config);
	_delay_us(150);
}

void modo_RX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	nrf24_le_registrador(CONFIG, 1, &reg_config);
	reg_config = reg_config | 3;
	nrf24_escreve_registrador(CONFIG,1, (uint8_t *)&reg_config);

	delay_us(20);
	
}

void limpa_FIFO(void)
{
	uint8_t origem;
	
	nrf24_le_registrador(CONFIG, 1, &origem);
	
	_delay_us(10);
	

	modo_TX();
	spi_habilita();
		spi_write(FLUSH_TX);
	spi_desabilita();

    modo_RX();
	spi_habilita();
		spi_write(FLUSH_RX);
	spi_desabilita();

	nrf24_escreve_registrador (CONFIG,1,(uint8_t *)&origem);
}

uint8_t nrf24_recebe(uint8_t buffer[])
{
	uint8_t x=0;

	cli();
	if (nova_msg)
	{
		for (x=0;x<8;x++) buffer[x]=MSG_RECEBIDA[x];
		nova_msg=0;
		x=1;
		
	}
	sei();
	return x;
   	
}
void nrf24_le_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[])
{
	uint8_t x;
	spi_habilita();
		spi_write(R_REGISTER|reg);
		for (x=0;x<qtd;x++)  vet[x] = spi_write(0x00);
	spi_desabilita();
}
void nrf24_flush_TX (void)
{
	spi_habilita();
		spi_write(FLUSH_TX);
	spi_desabilita();
}
void nrf24_escreve_registrador (uint8_t reg, uint8_t qtd, uint8_t vet[])
{
	uint8_t x;

	spi_habilita();
		spi_write(W_REGISTER|reg);
		for (x=0;x<qtd;x++)  spi_write(vet[x]);
	spi_desabilita();
}
uint8_t le_registrador (uint8_t reg)
{
	uint8_t x;
	spi_habilita();
		spi_write(R_REGISTER|reg);
		x = spi_write(0x00);
	spi_desabilita();
	return x;
}



