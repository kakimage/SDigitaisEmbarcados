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
#include "lcd.h"
#include <stdio.h>


#define RS PIN_2_12
#define E  PIN_2_13

#define D0 PIN_0_04
#define D1 PIN_0_05
#define D2 PIN_0_06
#define D3 PIN_0_07
#define D4 PIN_0_08
#define D5 PIN_0_09
#define D6 PIN_0_10
#define D7 PIN_0_11



int main ( void ) 
{
	SystemInit();
   	lcd_init (RS,  E, D0, D1, D2, D3, D4, D5, D6, D7);
	lcd_escreve("Oi mundo");
	delay_ms(2000);
	lcd_limpa_tela();
	lcd_escreve("UFSC");
	while(1)
	{
	}
    return 0 ;
}

