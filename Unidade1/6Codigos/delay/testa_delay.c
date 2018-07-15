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
#include "digital.h"



int main ( void ) 
{
	
	SystemInit();
	pinMode(PIN_4_29, OUTPUT);
	pinMode(PIN_3_26, OUTPUT);
	digitalWrite(PIN_3_26, HIGH);
	pinMode(PIN_1_23, INPUT);
	
	digitalWrite(PIN_4_29, HIGH);

	while(1)
	{
		digitalWrite(PIN_4_29, HIGH);
		delay_ms(100);
		digitalWrite(PIN_4_29, LOW);
		delay_ms(100);
		if (digitalRead(PIN_1_23))  digitalWrite(PIN_3_26, HIGH);
		else  digitalWrite(PIN_3_26, LOW);
	}
    return 0 ;
}

