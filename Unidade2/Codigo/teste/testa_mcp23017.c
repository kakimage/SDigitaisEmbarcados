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
#include <stdio.h>
#include "MCP23017.h"
#include "delay.h"




void configura_entrada_saida (void)
{
	MCP23017_configura_pino(MCP_PIN_0, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_1, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_2, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_3, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_4, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_5, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_6, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_7, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_8, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_9, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_10, OUTPUT);
	MCP23017_configura_pino(MCP_PIN_11, OUTPUT);

	MCP23017_configura_pino(MCP_PIN_12, INPUT);
	MCP23017_configura_pino(MCP_PIN_13, INPUT);
	MCP23017_configura_pino(MCP_PIN_14, INPUT);
	MCP23017_configura_pino(MCP_PIN_15, INPUT);
}

int main ( void ) 
{
	SystemInit();
   	UART0_Init(9600);


	MCP23017_init();
	configura_entrada_saida();
	printf("Aqui\n");
	while(1)
	{
		MCP23017_escreve_pino (MCP_PIN_0, HIGH);
		delay_ms(1000);
		MCP23017_escreve_pino (MCP_PIN_0, LOW);
		delay_ms(1000);

		if (MCP23017_leia_pino(MCP_PIN_15)==HIGH)	printf("botao em nivel alto\n");
		else printf("botao em nivel baixo\n");
	}

	return 0 ;
}


