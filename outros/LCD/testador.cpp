// EXEMPLO DE UM Pisca Pisca que usa a Lampada do kit
// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000

#include <stdio.h>
#include "LPC17xx.h"
#include "tarefa.h"
#include "lcd.h"

int main() {

	SystemInit();
	
	tarefa.start();
	
	LCD.init();
	LCD.escreve("UFSC 2018");
	
	
	while(1)
	{
		delay_ms(1000);
		LCD.escreve('A');
	}
 
	
	
}
