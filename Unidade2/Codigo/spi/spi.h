

#ifndef _SPI_
#define _SPI_

#include <inttypes.h>


void spi_configura (uint8_t pin_cs, uint8_t pin_si, uint8_t pin_so, uint8_t pin_clk);
void spi_habilita (void);
void spi_desabilita (void);
uint8_t spi_write (uint8_t dado);

#endif


