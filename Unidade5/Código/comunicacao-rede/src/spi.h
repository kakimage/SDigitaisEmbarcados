#ifndef _SPI_
#define _SPI_

#include <inttypes.h>

#define TEMPO 0

class SoftwareSPI {
	private:
		uint8_t PINO_CS, PINO_SI, PINO_SO, PINO_CLK;
	public:
		SoftwareSPI (uint8_t pin_cs, uint8_t pin_si, uint8_t pin_so, uint8_t pin_clk);
		SoftwareSPI (void);
		void habilita(void);
		void desabilita (void);
		uint8_t write (uint8_t dado);
};
extern SoftwareSPI SPI;
#endif
