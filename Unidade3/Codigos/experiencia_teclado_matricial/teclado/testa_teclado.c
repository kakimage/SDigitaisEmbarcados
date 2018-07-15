// EXEMPLO DE UM Pisca Pisca que usa a Lampada do kit
// para compilar:  
//                    make
// para gravar na SystemInit();placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000
//
// para gravar na placa (usando o JTAG)
//                   openocd -f lpc1768.cfg
// abrir outro shell
// telnet localhost 4444
// > reset halt
// > flash write_image erase main.bin 0x0 bin
#include "LPC17xx.h"
#include "digital.h"
#include "delay.h"
#include "uart.h"
#include "teclado.h"
#include <stdio.h>


int main ( void ) 
{
	uint8_t a,b;

	SystemInit();
    UART0_Init(9600);



    configura_teclado(PIN_2_00,PIN_2_01, PIN_2_02, PIN_2_03, PIN_2_04, PIN_2_05, PIN_2_06, PIN_2_07);
   
	while(1)
	{
		a = le_teclado();
		b = le_teclado();
		printf("Tecla lida = %c  %c\n",a, b);
	}
    return 0 ;
}

