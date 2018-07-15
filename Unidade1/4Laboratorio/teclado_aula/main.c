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
#include "digital.h"
#include "teclado.h"
#include "display.h"
#include "delay.h"
#include <stdint.h>







int main(void)
{
	SystemInit();
    uint8_t a;

	configura_teclado();
    display_configura ();


	le_teclado(BLOQ);
    display_7seg(1234);

	delay_ms(5000);

	while(1)
	{
		a = le_teclado(NBLOQ);
		if (a != NENHUMA_TECLA) display_7seg(a);
		    
	}
	return 0;
}

