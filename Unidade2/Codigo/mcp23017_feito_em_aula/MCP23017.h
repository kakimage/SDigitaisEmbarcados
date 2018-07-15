#ifndef _MCP_23017_
#define _MCP_23017_
#include <inttypes.h>

#define MCP_PIN_0 0
#define MCP_PIN_1 1
#define MCP_PIN_2 2
#define MCP_PIN_3 3
#define MCP_PIN_4 4
#define MCP_PIN_5 5
#define MCP_PIN_6 6
#define MCP_PIN_7 7
#define MCP_PIN_8 8
#define MCP_PIN_9 9
#define MCP_PIN_10 10
#define MCP_PIN_11 11
#define MCP_PIN_12 12
#define MCP_PIN_13 13
#define MCP_PIN_14 14
#define MCP_PIN_15 15


// definir os registradores
#define IODIRA 0
#define IODIRB 1

#define OLATCHA 0x14
#define OLATCHB 0x15

#define GPIOA 0x12
#define GPIOB 0x13


#define DISPOSITIVO 0x40

void mcp23017_init (void);
void mcp23017_escreve_pino(uint8_t pino, uint8_t valor);
uint8_t mcp23017_le_pino(uint8_t pino);
void mcp23017_configura_pino( uint8_t pino, uint8_t tipo);

#endif
