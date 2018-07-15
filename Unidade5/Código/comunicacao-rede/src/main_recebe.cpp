#include "uart.h"
#include <util/delay.h>
#include <string.h>
#include <inttypes.h>
#include "nrf24.h"


Transceiver_NRF24 nrf24 = Transceiver_NRF24();
	


int main (void)
{
	uint8_t buffer[32];
	uint8_t tamanho;
	uint16_t numero;
 
	printf("MODULO RECEPTOR\n");
	nrf24.endereco(123, 124);
	nrf24.init();
		printf("Digite Enter");
	getchar();
	printf("OK\n\n");

	while(1)
	{
		tamanho=nrf24.recebe(buffer);
		if (tamanho)
		{
			buffer[tamanho]=0;
			printf("RECEBEU %s tamanho=%d\n",(char * )buffer, tamanho);
			sscanf(buffer, "mensagem:%04d",&numero);
		
			sprintf((char *)buffer, "%04d",numero);		
			_delay_ms(2);
			nrf24.envia_direto((uint8_t *)buffer, strlen((char *)buffer));
		}
	}
	return 0;
}


