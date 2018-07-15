


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

#include "LPC17xx.h"
#include "uart.h"
#include "digital.h"
#include <stdio.h>
#include <string.h>
#include "MCP23S17.h"
#include "delay.h"







int main ( void ) 
{
	SystemInit();
   	UART0_Init(9600);

	mcp23S17_init();
	mcp23S17_configura_pino(MCP_PIN_15, INPUT);
	mcp23S17_configura_pino(MCP_PIN_0 , OUTPUT);

	while(1)
	{
		mcp23S17_escreve_pino(MCP_PIN_0, HIGH);
		delay_ms(1000);
		mcp23S17_escreve_pino(MCP_PIN_0, LOW);
		delay_ms(1000);

		if (mcp23S17_le_pino(MCP_PIN_15)==HIGH)
		{
			printf("Botao em VCC\n");
		}
		else printf("Botao em GND\n");

	}

	return 0 ;
}


