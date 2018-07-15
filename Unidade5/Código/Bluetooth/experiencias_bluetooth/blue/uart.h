#ifndef _UART_
#define _UART_


void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);
uint8_t serial_hardware_dados_disponiveis(void);

void uart_init(void);

/* http://www.ermicro.com/blog/?p=325 */

extern FILE uart_output;
extern FILE uart_input ;
#endif
