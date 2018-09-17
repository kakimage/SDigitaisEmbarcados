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
#include "src/LPC17xx.h"

#include "delay.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include "digital.h"
#include <inttypes.h>
#include "interrupcao_externa.h"





void meu_tratador_interrupcao_externa (void)
{
	printf("Evento\n");
}

int main ( void ) 
{
	SystemInit();
    UART0_Init(9600);
	printf("Rodando 1 2 3...\n");

	configura_interrupcao_externa(meu_tratador_interrupcao_externa, PIN_2_13_INT_EXT_3, BORDA_DESCIDA);   

	printf("Agora com as int desabilitadas\n");
	desabilita_interrupcao_externa();
	printf("Agora com as int habilitadas\n");
	habilita_interrupcao_externa();
	while(1);

}

