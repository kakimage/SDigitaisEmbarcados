#include "digital.h"
#include "uart.h"
#include <util/delay.h>
#include <string.h>
#include <inttypes.h>
#include "nrf24.h"



Transceiver_NRF24 nrf24 = Transceiver_NRF24();
	


int main (void)
{
	char buffer[40], recebido[40];
	uint16_t cont=0,x, numero;

	
	printf("MODULO TRANSMISSOR\n");

	nrf24.endereco(124, 123);
	nrf24.init();
	printf("Digite Enter");
	getchar();
	printf("OK\n\n");

	pinos.pinMode(3, INPUT);
	
	
	while(1)
	{
		if (pinos.digitalRead(3)==1)
		{
			printf("Envia mensagem numero:%d\n",cont);
			sprintf(buffer, "mensagem:%04d",cont);
			cont++;
			while (1)
			{		
				nrf24.envia_direto((uint8_t *)buffer, strlen(buffer));
                printf(".");
				x=nrf24.recebe((uint8_t *)recebido);
				if (x)
				{
					recebido[x]=0;
					sscanf(recebido, "%04d",&numero);
					printf("   ---- recebeu: %d\n",numero);
					if (numero==(cont-1))
					{
						printf("Foi confirmada: %s\n",recebido);

						break;
					}
				}
				_delay_ms(200);
			}
		}
	}
	
	return 0;
}
