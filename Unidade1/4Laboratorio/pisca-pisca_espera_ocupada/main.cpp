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
#include <stdint.h>

void delay (void)
{
	uint32_t delay;
	  for(delay = 0; delay < 1000000; delay++) {
       __asm("NOP");
	
    }
}

int main() {
	SystemInit();
	LPC_GPIO4->FIODIR |= (1 << LED4_PIN);
  	LPC_GPIO4->FIOSET = (1 << LED4_PIN);
  	delay();
  	LPC_GPIO4->FIOCLR = (1 << LED4_PIN);
  	delay();	
}

