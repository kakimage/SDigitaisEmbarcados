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
#include "timer.h"
#include "digital.h"
#include "uart.h"
#include <stdio.h>
#include "misc.h"



int _write (int fd, const void *buf, size_t count)
{
	uint8_t x;
	char *vet = (char *) buf;

	for (x=0;x<count;x++) UART0_Sendchar(  vet[x]);
	return count;
}

int _read (int fd, const void *buf, size_t count)
{
	uint8_t  contador=0;
	char *vet = (char *) buf;
	char letra;


	while (contador < count)
	{
		letra = UART0_Getchar();
		if (letra=='\n') break;
		vet[contador]=letra;
		contador++;	
	}
	vet[contador]='\n';
	return contador+1;
}


void meu_tratador_int_tempo()
{
	static char valor =1;
	digitalWrite(PIN_2_11, valor);
	valor = !valor;
	printf("X\n");
}

int main ( void ) 
{
	SystemInit();
	
	pinMode(PIN_2_11, OUTPUT);
	digitalWrite(PIN_2_11, HIGH);



	timer_init(meu_tratador_int_tempo,10);
	UART0_Init(9600);
	printf("............Digite algo.................\n");
	getchar();
	while(1)
	{
	}

    return 0;
}

