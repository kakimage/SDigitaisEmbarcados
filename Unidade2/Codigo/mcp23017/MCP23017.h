#ifndef __MCP23017__
#define __MCP23017__

#define IODIRA 0x00
#define IODIRB 0x01

#define OLATA 0x14
#define OLATB 0x15

#define GPIOA 0x12
#define GPIOB 0x13


#include "digital.h"

#define MCP_PIN_0   0  //GPA0
#define MCP_PIN_1   1
#define MCP_PIN_2   2
#define MCP_PIN_3   3
#define MCP_PIN_4   4
#define MCP_PIN_5   5
#define MCP_PIN_6   6
#define MCP_PIN_7   7  //GPA7
#define MCP_PIN_8   8  //GPB0
#define MCP_PIN_9   9 
#define MCP_PIN_10 10 
#define MCP_PIN_11 11
#define MCP_PIN_12 12
#define MCP_PIN_13 13
#define MCP_PIN_14 14
#define MCP_PIN_15 15  //GPB7

void    MCP23017_init (void);
void    MCP23017_configura_pino (uint8_t pino, uint8_t tipo);
void    MCP23017_escreve_pino (uint8_t pino, uint8_t valor);
uint8_t MCP23017_leia_pino (uint8_t pino);

#endif
