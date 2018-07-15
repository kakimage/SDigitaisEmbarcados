
#ifndef _nrf24_
#define _nrf24_
#include <inttypes.h>  
#include "mensagens.h"  



//Definicoes outras
#define W 0
#define R 1


// comandos
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF



// Registradores
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17

// Bits dos registradores
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0
#define AW          0
#define ARD         4
#define ARC         0
#define PLL_LOCK    4
#define RF_DR       3
#define RF_PWR      1
#define LNA_HCURR   0        
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     1
#define TX_FULL     0
#define PLOS_CNT    4
#define ARC_CNT     0
#define TX_REUSE    6
#define FIFO_FULL   5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0

#define ACK 1
#define NORMAL 0

//Prototipo das funcoes




class Transceiver_NRF24 {
	private:
		void reset_TX (void);
		void recebe_transceiver (tipo_mensagem *d);
		static const  uint16_t VALOR_INICIAL_TEMPO=100;
		volatile uint16_t contador_eventos_tempo;
		void limpa_FIFO (void);
		void reset (void);
		void rf24_read(uint8_t reg, uint8_t *val, uint8_t antval);
		uint8_t rf24_write(uint8_t reg, uint8_t *val, uint8_t antval);
		void CE_HIGH(void);
		void CE_LOW(void);
		void modo_TX(void);
		void modo_RX(void);
		void power_DOWN (void);
		void power_UP (void);
		uint8_t rf24_le_registrador (uint8_t reg);
		void inicializa_registradores(void);
		void habilita_evento_recebe(void);
		void habilita_evento_timer(void);
	public:
		void transmite_transceiver (tipo_mensagem *d);
		void evento_recebe();
		void evento_timer();
		void init(void);
		void endereco  (uint8_t recebe, uint8_t transmite);
		Transceiver_NRF24 ();
		uint8_t recebe (uint8_t buff[]);
		void envia(uint8_t *W_buff, uint8_t tam);
		void envia_direto(uint8_t *W_buff, uint8_t tam);
};


#endif
