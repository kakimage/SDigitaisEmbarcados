


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

#include "uart.h"
#include "digital.h"
#include <stdio.h>
#include <string.h>
#include "nrf24.h"
#include "delay.h"
#include <stdlib.h>

#define BOTAO 3

int main ( void ) 
{
	uint8_t x, mesa, solicita_atendimento;
	uint8_t buffer[10]; uint16_t contador=0, contador_msg=0;;

	uart_init();

	nrf24_init();
	nrf24_endereco(20,10);
	
	printf("Rodando...\n");
	pinMode(BOTAO, INPUT);
	mesa=27;
	printf("Cliente mesa %d\n",mesa);
	solicita_atendimento = 0;
	
	while(1)
	{
		if (digitalRead(BOTAO)==1)
		{
			printf("botao apertado\n");
			solicita_atendimento=1;

		}
		
		

		x = nrf24_recebe(buffer);
		if (x)
		{
			printf("recebida confirmacao da mesa=%d\n",buffer[0]);
			if (buffer[0]==mesa)
			{		
				printf("mensagem atendida\n");
				solicita_atendimento=0;
			}
		}
		else
		if (solicita_atendimento)
		{
			if (contador==2000)
			{
				buffer[0]=mesa;
				buffer[1]=contador_msg;
				contador_msg++;
				buffer[2]=0;
				nrf24_transmite(buffer);
				contador=0;
			}
			contador++;

			
			
		
		}
		
	}
	return 0;
}


