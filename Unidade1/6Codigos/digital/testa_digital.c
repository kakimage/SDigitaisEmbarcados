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
#include <stdio.h>


int main ( void ) 
{
	uint8_t a;

	SystemInit();
    UART0_Init(9600);

	pinMode(PIN_2_12,INPUT_PULLDOWN);

   
	while(1)
	{
		a = digitalRead(PIN_2_12);
		printf("PIN_2_12 valor lido=%d\n",a);
		delay_ms(1000);
	}
    return 0 ;
}

