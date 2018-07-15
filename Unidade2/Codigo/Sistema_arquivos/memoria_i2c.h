#ifndef _MEMORIA_I2C
#define _MEMORIA_I2C

#include "digital.h"
#include <inttypes.h>


#define PINO_DADOS PIN_0_27
#define PINO_CLOCK PIN_0_28



#define DISPOSITIVO_PLACA 0
#define DISPOSITIVO_EXTERNO 3

void read_bytes  (uint8_t *b, uint16_t tam, uint16_t end);
void write_bytes (uint8_t *b, uint16_t tam, uint16_t end);
void memoria_configura(uint8_t dispositivo, uint8_t tamanho_pagina);


#endif
