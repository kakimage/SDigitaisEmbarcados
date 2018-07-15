


// Testa o acesso ao protocolo i2c enviado caracteres para serem gravados em posicoes sequenciais da memoria 24c64 EEPROM
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
// Este programa usa os pinos (PIN_0_27, PIN_0_28); que sao os usados pela EEPROM no kit
// Para usar no MBED deve-se trocar os pinos
#include <stdlib.h>
#include "uart.h"
#include "digital.h"
#include <stdio.h>
#include <string.h>
#include "nrf24.h"
#include "delay.h"

int main ( void ) 
{
	uint8_t buffer[20];
	uint16_t x;
	uart_init();

	nrf24_init();

	

	printf("Servidor...\n");
	nrf24_endereco(10,20);
	x=0;uint8_t c=0;
	while(1)
	{
		x = nrf24_recebe(buffer);
		if (x)
		{
			printf("Servidor recebeu msg para atender a mesa=%d id=%d\n",buffer[0],buffer[1]);
			buffer[0]=27;
			buffer[1]=0;
			printf("Envia a confirmacao\n");
			
			nrf24_transmite(buffer);	
			
		}
	}

	return 0 ;
}


