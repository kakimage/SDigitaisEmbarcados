#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "spi.h"
#include "nrf24.h"
#include "digital.h"
#include "uart.h"
#include "mensagens.h"

#define CE 8



Transceiver_NRF24* handler;

lista_mensagens mensagens_recebidas;
lista_mensagens mensagens_enviar;

// Evento de recepcao de mensagem
ISR (INT0_vect)
{
    handler->evento_recebe();
}

//evento de timer
ISR (TIMER0_OVF_vect)  
{  
	handler->evento_timer();
	TCNT0  = 6;
}  

void Transceiver_NRF24::evento_timer(void)
{
	volatile uint8_t x, qtd;
	struct tipo_mensagem m;

	contador_eventos_tempo--;
	if (contador_eventos_tempo==0)
	{
		contador_eventos_tempo = VALOR_INICIAL_TEMPO;

		qtd =  mensagens_enviar.qtd_mensagens();

		if (qtd)
		{
			for (x=0;x<qtd;x++)
			{
				mensagens_enviar.consulta(x, &m);
				transmite_transceiver(&m);

			}
			reset();
			mensagens_enviar.remove_ACKs();
		}
	}
}
void Transceiver_NRF24::habilita_evento_recebe(void)
{
	EICRA   = EICRA | 0x02;   // configura que a interrupção sera na borda de descida
   	EIMSK   = EIMSK | 0x01;   // configura que a interrupcao escolhida sera INT0 pino D2 do atmega328
                              // que corresponde ao pino digital 2 do arduino UNO
  	EIFR    = EIFR  | 1;
}

void Transceiver_NRF24::habilita_evento_timer(void)
{
	  TIFR0 = 1<<TOV0;
 	  TCNT0  = 6;
      TCCR0A = 0;                     // overflow a cada 256 contagens  
      TCCR0B = _BV(CS01) | _BV(CS00); // Usar clkIO/64: int a cada   
                                       //   64*256/12000 = 1,365 ms  
      TIMSK0 = _BV(TOIE0);            // Interromper no overflow  
}

void Transceiver_NRF24::transmite_transceiver (tipo_mensagem *d)
{
	volatile uint8_t cabecalho,y;
	volatile uint8_t buffer[32];

	cabecalho  = (d->tipo<<6) | d->tamanho;
	buffer[0]  = cabecalho;
	buffer[1]  = d->numero_serie;
	for (y=0;y<d->tamanho;y++) buffer[2+y]=d->dados[y];


	modo_TX();
	
	SPI.habilita();
		SPI.write(FLUSH_TX);
	SPI.desabilita();

	SPI.habilita();
		SPI.write(W_TX_PAYLOAD);
		for (y=0;y<32;y++)	SPI.write(buffer[y]);
	SPI.desabilita();
		

/*
	_delay_ms(10);
	CE_HIGH();
	_delay_us(20);
	CE_LOW();
	_delay_ms(20);

	
	modo_RX();
	_delay_ms(10);
	CE_HIGH();*/

/*volatile uint8_t cabecalho,y;
	volatile uint8_t buffer[32];

	cabecalho  = (d->tipo<<6) | d->tamanho;
	buffer[0]  = cabecalho;
	buffer[1]  = d->numero_serie;
	for (y=0;y<d->tamanho;y++) buffer[2+y]=d->dados[y];

	modo_TX();
	rf24_read(FLUSH_TX, (uint8_t *) buffer, 0);
	rf24_read(W_TX_PAYLOAD, (uint8_t *) buffer, 32);*/
	CE_HIGH();
	_delay_us(20);
	CE_LOW();
	_delay_ms(20);
	reset();
	modo_RX();
}

void Transceiver_NRF24::recebe_transceiver (tipo_mensagem *d)
{
		volatile uint8_t buffer[32], tmp, x;

		


	rf24_read(R_RX_PAYLOAD, (uint8_t *) buffer, 32);
	tmp = buffer[0];
	d->numero_serie = buffer[1];
	d->tipo         = tmp >> 6;
	d->tamanho      = tmp & 63;
	for (x=0;x<30;x++) d->dados[x]=buffer[2+x];
	reset();
	
}
void Transceiver_NRF24::evento_recebe(void)
{
	 struct tipo_mensagem meta;
	
	recebe_transceiver(&meta);
	reset();

	SPI.habilita();
		SPI.write(FLUSH_RX);
	SPI.desabilita();

   
	switch (meta.tipo)
	{
		case NORMAL:
					// verifica se o numero_serie esta na faixa de aceitacao da janela
					// case esteja, recebe a mensagem e envia ACK
					// caso seja o numero de uma msg ja aceita, envia ACK apenas
				    // caso seja um numero maior do que a janela, ignora
					

					//printf("Recebeu NORMAL [serie=%d] [tamanho=%d]\n",meta.numero_serie, meta.tamanho);

					mensagens_recebidas.insere_mensagem(meta);
					//if (mensagens_recebidas.insere_mensagem(meta))
					//{
					//	mensagens_enviar.nova_mensagem_ACK(meta);				
					//}
					break;
		case ACK:
					printf("ACK\n");
					//mensagens_enviar.procura_apaga_por_numero_serie(meta);			
					//mensagens_enviar.retira_mensagem(buffer);
	}
}

// ******************************************************************************************
void Transceiver_NRF24::limpa_FIFO(void)
{
	uint8_t origem;
	
	origem = rf24_le_registrador(CONFIG);
	
	_delay_us(10);
	modo_RX();
	SPI.habilita();
		SPI.write(FLUSH_RX);
	SPI.desabilita();

	modo_TX();
	SPI.habilita();
		SPI.write(FLUSH_TX);
	SPI.desabilita();

	rf24_write(CONFIG,(uint8_t *)&origem,1);
}

void Transceiver_NRF24::modo_TX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	reg_config = rf24_le_registrador(CONFIG);
	reg_config = (   (reg_config | _BV(PWR_UP) )    & ~_BV(PRIM_RX));
	rf24_write(CONFIG,(uint8_t *)&reg_config,1);
	_delay_us(150);
}

void Transceiver_NRF24::modo_RX(void)
{
	uint8_t reg_config;

	// le o valor corrente do registrador CONFIG
	reg_config = rf24_le_registrador(CONFIG);
	reg_config = reg_config | 3;
	rf24_write(CONFIG,(uint8_t *)&reg_config,1);

	_delay_us(150);
	
}

uint8_t Transceiver_NRF24::rf24_write(uint8_t reg, uint8_t *val, uint8_t antval)
{
	CE_LOW();
	reg = W_REGISTER| (0x1f & reg);

	//_delay_us(10);
	SPI.habilita();
	//_delay_us(10);
	reg=SPI.write(reg);
	//_delay_us(10);
	
	int i;
	for (i=0;i<antval;i++)
	{
			SPI.write(val[i]);
			//_delay_us(10);
	}
	SPI.desabilita();
	CE_HIGH();
	return reg;
}
void Transceiver_NRF24::rf24_read(uint8_t reg, uint8_t *val, uint8_t antval)
{


	//_delay_us(10);
	SPI.habilita();
	//_delay_us(10);
	SPI.write(reg);
	//_delay_us(10);
	
	int i;
	for (i=0;i<antval;i++)
	{
			if (reg != W_TX_PAYLOAD)
			{
				val[i] = SPI.write(0xff);
				//_delay_us(10);
			}
			else
			{
				SPI.write(val[i]);
				//_delay_us(10);
			}
	}
	SPI.desabilita();

}

void Transceiver_NRF24::envia_direto(uint8_t *W_buff, uint8_t tam)
{
	struct tipo_mensagem m;

	uint8_t x;

	for (x=0;x<tam;x++) 	m.dados[x]=W_buff[x];
	m.tipo    = NORMAL;
	m.tamanho = tam;
	m.numero_serie = 1;
	cli();
		transmite_transceiver(&m);
	sei();

}

void Transceiver_NRF24::envia(uint8_t *W_buff, uint8_t tam)
{

	volatile uint8_t  repete=1;


    while (repete)
	{
		cli();
		if (mensagens_enviar.nova_mensagem_normal(W_buff, tam)) repete=0;
		_delay_ms(10);
		sei();
	}



	
}
void Transceiver_NRF24::CE_HIGH(void)
{
	pinos.digitalWrite(CE, HIGH);
}
void Transceiver_NRF24::CE_LOW(void)
{
	pinos.digitalWrite(CE, LOW);
}


void Transceiver_NRF24::power_DOWN (void)
{
	uint8_t reg_config;

	reg_config = rf24_le_registrador(CONFIG);
	reg_config = reg_config & 0xFD; 
	rf24_write(CONFIG,(uint8_t *)&reg_config,1);
}
void Transceiver_NRF24::power_UP (void)
{
	uint8_t reg_config;

	reg_config = rf24_le_registrador(CONFIG);
	reg_config = reg_config | 0x02; 
	rf24_write(CONFIG,(uint8_t *)&reg_config,1);
}
void Transceiver_NRF24::inicializa_registradores(void)
{
	uint8_t val[5];

    reset();



 	val[0]=0x00;  // desabilita confirmacao
	rf24_write(EN_AA, val, 1);

	// numero de canais de dados  1
	val[0]=0x01;
	rf24_write(EN_RXADDR,val,1);

	val[0]=0x01;
	rf24_write(SETUP_AW,val,1);

	val[0]=0x00;
	rf24_write(SETUP_RETR,val,1);

	val[0]=0x00;
	rf24_write(RF_CH,val,1);

    val[0]=1;
    
	rf24_write(RF_SETUP,val,1);

	val[0]=0x0E;
	rf24_write(STATUS,val,1);

	val[0]=8;
	rf24_write(RX_PW_P0,val,1);
	
    val[0]=0x33;     
	rf24_write(CONFIG,val,1);

	val[0]=1;
	val[1]=1;
	val[2]=1;
	
	rf24_write(RX_ADDR_P0,val,3);
	rf24_write(TX_ADDR,val,3);


	
	val[0]=0x11;
	rf24_write(FIFO_STATUS,val,1);
}
Transceiver_NRF24::Transceiver_NRF24 (void)
{
	pinos.pinMode(CE, OUTPUT);
	CE_LOW();
	SPI = SoftwareSPI (10,12, 11, 13);
	_delay_ms(300);

	//power_DOWN();
	//_delay_ms(30);
	CE_HIGH();
	power_UP();

	limpa_FIFO();	
	inicializa_registradores();


	printf("inicializacao do transceiver :");
	if (rf24_le_registrador(STATUS)==14) printf("OK\n");
	else printf("ERRO\n");
	//_delay_ms(100);
	handler = this;
	contador_eventos_tempo = VALOR_INICIAL_TEMPO;
	limpa_FIFO();
	reset();
	habilita_evento_recebe();
	//habilita_evento_timer();
	sei();
    
}
void Transceiver_NRF24::init (void)
{
	
}

void Transceiver_NRF24::endereco (uint8_t recebe, uint8_t transmite)
{
	uint8_t i;

	uint8_t val[5];

	for (i=0; i<5; i++) val[i]=recebe;
	rf24_write(RX_ADDR_P0,val,5);

	for (i=0; i<5; i++) val[i]=transmite;
	rf24_write(TX_ADDR,val,5);
}
void Transceiver_NRF24::reset_TX (void)
{
	_delay_us(10);
	SPI.habilita();
		SPI.write(W_REGISTER|STATUS);
		SPI.write(0x70);
	SPI.desabilita();
}

void Transceiver_NRF24::reset (void)
{
	CE_LOW();
	_delay_us(10);
	SPI.habilita();
	_delay_us(10);
	SPI.write(W_REGISTER+STATUS);
	_delay_us(10);
	SPI.write(0x70);
	_delay_us(10);
	SPI.desabilita();
	CE_HIGH();
}

uint8_t Transceiver_NRF24::recebe (uint8_t buff[])
{
	volatile uint8_t qtd=0;
	


        cli(); // desabilita int
		qtd=mensagens_recebidas.retira_mensagem(buff);
		sei(); 
 
	return qtd;
	
}

uint8_t Transceiver_NRF24::rf24_le_registrador (uint8_t reg)
{
	volatile uint8_t recebido;

	SPI.habilita();
	SPI.write(R_REGISTER| (0x1f & reg));
	recebido = 	SPI.write(0xff);
	SPI.desabilita();
	return recebido;			
}




