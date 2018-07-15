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
#include <string.h>
#include "SA_alto.h"






int main ( void ) 
{
	meu_FILE *A;  char buffer[200];
	 char outro[200];
	SystemInit();
   	UART0_Init(9600);

	printf("Formata a EEPROM para criar o SA\n");
	inicializa_SA();
	//cria_SA();
	//A = meu_fopen ("teste", "w");
	//if (A==NULL)
	//{
	//	printf("Erro ao criar arquivo\n");
	//}
	//else {
	//	strcpy(buffer, "Oi mundo1234567890ABCDEFGHIJKBLABLABLAmnopqrstuvxyz12345");
	//	
	//}
    //meu_fwrite((void *)buffer, 1, strlen(buffer), A);
	//printf("depois....\n");

	mostra_entrada_arquivos();
	//meu_fread((void *)outro, 1, 10, A);
	//outro[10]=0;
	//printf("Lido=%s\n",outro);
	while(1);

	return 0 ;
}


