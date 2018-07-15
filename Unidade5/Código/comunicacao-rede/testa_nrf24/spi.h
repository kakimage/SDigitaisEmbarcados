#ifndef _SPI_
#define _SPI_
#include <inttypes.h>

extern uint8_t PINO_CS;
extern uint8_t PINO_SI;
extern uint8_t PINO_SO;
extern uint8_t PINO_SCK;

#define COMANDO_READ_BLOCK  17

uint8_t SD_init (void);
void SPI_init (uint8_t pino_cs,uint8_t pino_si, uint8_t pino_so, uint8_t pino_sck );
void SPI_enable(void);
uint8_t SPI_write(uint8_t valor);
void SPI_disable(void);


#endif

