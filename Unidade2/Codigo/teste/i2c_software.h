
#ifndef _I2C_SOFTWARE_
#define _I2C_SOFTWARE_
#include <inttypes.h>

#define TAMANHO_PAGINA 32

#define min(A,B) (A<B?A:B)

// configura o I2C informando qual o pino de dados e qual o pino de clock
void i2c_configura (uint32_t pino_dados, uint32_t pino_clock);

// envia um byte 
uint8_t i2c_envia_byte (uint8_t dados);

// gera o inicio de uma transacao
void i2c_start ();

//gera o final de uma transacao
void i2c_stop  ();


// le um byte da memoria, informa a posicao que deseja ler
uint8_t i2c_memoria_le (uint16_t end);


// le uma serie de bytes da memoria
void i2c_memoria_le_bytes( uint8_t buffer[], uint16_t end,  uint16_t qtd);

// escreve um byte na memoria
void i2c_memoria_escreve (uint16_t end, uint8_t v);

// escreve uma serie de bytes na memoria
void i2c_memoria_escreve_bytes( uint8_t buffer[], uint16_t end, uint16_t qtd);

 
#endif
