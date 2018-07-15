
#ifndef _SERIAL_
#define _SERIAL_


#include <inttypes.h>
#include <stdio.h>

void serial_configura (uint16_t taxa, uint8_t pino_TX, uint8_t pino_RX);
void  serial_envia_msg (char *st);
uint8_t serial_software_dados_disponiveis(void);



void serial_envia_letra(char c);
char serial_recebe_letra(void);
void mensagem (char *st);


extern FILE uart_output;
extern FILE uart_input ;

#endif
