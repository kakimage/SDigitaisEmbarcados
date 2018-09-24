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
#include "src/LPC17xx.h"
#include "interrupcao-timer.h"


#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

volatile  int minhaVariavel = 0;

void minha_funcao(void)
{
	minhaVariavel++;
}

void delay (int x)
{
	
	minhaVariavel = 0;
	
	while (minhaVariavel< x);
}
int main ( void ) 
{

	SystemInit();
	

	
	UART0_Init(9600);
	timer_init(minha_funcao);
	
	delay(10000);
	printf("oi mundo\n");
	delay(20000);
	printf("vida cruel\n");

	while(1){}
	
    return 0 ;
}

