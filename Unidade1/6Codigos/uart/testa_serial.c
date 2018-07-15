// EXEMPLO DE UM Pisca Pisca que usa a Lampada do kit
// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000
//
// para gravar na placa (usando o JTAG)
//                   openocd -f lpc1768.cfg
// abrir outro shell
// telnet localhost 4444
// > reset halt
// > flash write_image erase main.bin 0x0 bin
#include "LPC17xx.h"

#include "delay.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include "digital.h"
#include <inttypes.h>

#define COMANDO_LIGA_L1 1
#define COMANDO_LIGA_L2 2
#define COMANDO_DESLIGA_L1 3
#define COMANDO_DESLIGA_L2 4
#define OUTRO 5

int le_comando(void)
{
	char linha[100];

	gets(linha);
	if (strncmp("COMANDO_LIGA_L1",linha,15)==0) return COMANDO_LIGA_L1;
	if (strncmp("COMANDO_LIGA_L2",linha,15)==0) return COMANDO_LIGA_L2;
	if (strncmp("COMANDO_DESLIGA_L1",linha,18)==0) return COMANDO_DESLIGA_L1;
	if (strncmp("COMANDO_DESLIGA_L2",linha,18)==0) return COMANDO_DESLIGA_L2;
    return OUTRO;
} 


int main ( void ) 
{
	int c;
	SystemInit();

	
	UART0_Init(9600);
	pinMode(PIN_4_29, OUTPUT);
	pinMode(PIN_3_26, OUTPUT);

    digitalWrite(PIN_4_29, LOW);
    digitalWrite(PIN_3_26, LOW);


	
	
	printf("............INTERPRETADOR DE COMANDOS.................\n");
	getchar();
	while(1){
		printf("Digite o comando:\n");	
		c = le_comando();
        switch (c)
		{
			case COMANDO_LIGA_L1:
				digitalWrite(PIN_4_29, HIGH);
				break;
			case COMANDO_LIGA_L2:
				digitalWrite(PIN_3_26, HIGH);
				break;
			case COMANDO_DESLIGA_L1:
				digitalWrite(PIN_4_29, LOW);
				break;
			case COMANDO_DESLIGA_L2:
				digitalWrite(PIN_3_26, LOW);
			
		} 
		printf("Comando recebido %d\n",c);
	}
    return 0 ;
}

