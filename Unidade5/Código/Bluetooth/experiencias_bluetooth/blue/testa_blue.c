#include <stdio.h>
#include "serial.h"
#include "uart.h"
#include <util/delay.h>
#include "digital.h"
#include <string.h>


#define PINO_KEY 8
#define PINO_ENERGIA 9

#define PINO_TX_SOFTWARE    3
#define PINO_RX_SOFTWARE    2



#define TEMPO 18

//---------------------------------------------------------------------------
void serial_envia_letra_38400(char c) {

	int8_t x;

	digitalWrite(PINO_TX_SOFTWARE, LOW);
	_delay_us(TEMPO);

	for (x=7;x>=0;x--)
	{
		digitalWrite(PINO_TX_SOFTWARE, (c >> (7-x)) & 0x01);
		_delay_us(TEMPO); 
	}
	digitalWrite(PINO_TX_SOFTWARE, HIGH); //STOP
	_delay_us(TEMPO*2);        
}
void serial_string_38400(char st[]) {
	uint8_t x=0;

	while (st[x] != 0)
	{
		serial_envia_letra_38400(st[x]);
		x++;
	}
}
//----------------------------------------------------------------
void leia_comando (char st[])
{
	uint8_t contador=0;
	char a;
	while (1)
	{
		a = getchar();
		if (a=='#')
		{
			st[contador]=0;
			return;
		}
		if ((a != '\r') && (a != '\n') )
		{
			st[contador]=a;
			contador++;
		}
	}
}
void configura_pinos (void)
{
	pinMode(PINO_TX_SOFTWARE,OUTPUT);
	digitalWrite(PINO_TX_SOFTWARE,HIGH);


   pinMode(PINO_KEY, OUTPUT);
   pinMode(PINO_ENERGIA, OUTPUT);
   digitalWrite(PINO_ENERGIA, LOW);
}
void MODO_DADOS (void)
{
    // serial a 9600
    digitalWrite(PINO_ENERGIA, LOW);
    _delay_ms(1000);
    digitalWrite(PINO_KEY, LOW);
    _delay_ms(100);
    digitalWrite(PINO_ENERGIA, HIGH);
    _delay_ms(1000);
    digitalWrite(PINO_KEY,HIGH);
    _delay_ms(1000);
}

void MODO_COMANDO2 (void)
{
	serial_configura (9600,PINO_TX_SOFTWARE, PINO_RX_SOFTWARE); // vai usar porta serial 9600
    digitalWrite(PINO_ENERGIA, LOW);
    _delay_ms(10000);
    digitalWrite(PINO_KEY, LOW);
    _delay_ms(100);
    digitalWrite(PINO_ENERGIA, HIGH);
    _delay_ms(1000);
    digitalWrite(PINO_KEY,HIGH);
    _delay_ms(1000);
}

void MODO_COMANDO1(void)
{
   serial_configura (38400,PINO_TX_SOFTWARE, PINO_RX_SOFTWARE); // vai usar porta serial 38400
    digitalWrite(PINO_ENERGIA, LOW);
    _delay_ms(200);
    digitalWrite(PINO_KEY, HIGH);
    digitalWrite(PINO_ENERGIA, HIGH);
    _delay_ms(1000);

}

int main()
{
	uint8_t c;
	
	uart_init();
	printf("Interface com o PC rodando\r\n");
	_delay_ms(1000);	
	configura_pinos();
	
	MODO_COMANDO2();  
	// coloca no modo de recepcao de comandos a 38400
	//neste momento nao existe comunicacao com o PC
  	//envia comando a 38400 para fazer a serial funcionar a 9600
	//depois, todos os comandos serao enviados a 9600
	//somente existe transmissao de dados, nada sera recebido
	//serial_string_38400("AT\r\n");  // comando para testar a comunicacao
	//_delay_ms(500);
	//serial_string_38400("AT+UART=9600,1,0\r\n"); //coloca em 9600, 1 stop bit, sem paridade



    //depois deste ponto, pode enviar comandos pela serial a 9600 e receber as respostas tb
    //os dados que o PC envia sao recebidos no pino RX pelo Arduino e pelo bluetooth
	//os dados transmitidos pelo bluetooth sao enviados pelo pino TX 


	printf("Pronto para enviar/receber comandos\r\n");
	
	while(1)
	{
		if (serial_hardware_dados_disponiveis())
		{
			c=getchar();
			serial_envia_letra(c);			
		}
		if (serial_software_dados_disponiveis())
		{
			c = serial_recebe_letra();
			putchar(c);
		}
	}

	return 0;
}

