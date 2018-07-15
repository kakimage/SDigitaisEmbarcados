
#ifndef _INT_EXT_
#define _INT_EXT_

#define INT1 1  // PINO 3 do Arduino
#define INT0 0  // PINO 2 do Arduino

void configura_interrupcao_externa(uint8_t numero_interrupcao, uint8_t pin, void (*f)(void));
void habilita_interrupcao_externa (uint8_t numero_interrupcao);
void desabilita_interrupcao_externa (uint8_t numero_interrupcao);

#endif
