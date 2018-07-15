// Demonstra como utilizar a interrupcao externa INT0
#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"

 void (*funcao0)(void);
 void (*funcao1)(void);


// *************************** tratador de interrupcao externa ******************************
// O tratador automaticamente limpa o FLAG de interrupcao externa antes do tratador terminar
ISR (INT0_vect)
{
     funcao0();
}

ISR (INT1_vect)
{
     funcao1();
}
// ******************************************************************************************



void configura_interrupcao_externa(uint8_t numero_interrupcao, uint8_t pin,  void (*f)(void))
{

	if (numero_interrupcao==INT0)
	{
		EICRA   = EICRA | 0x02;   // configura que a interrupção sera na borda de descida
      	EIMSK   = EIMSK | 0x01;   // configura que a interrupcao escolhida sera INT0 pino D2 do atmega328
                                  // que corresponde ao pino digital 2 do arduino UNO
	  	EIFR    = EIFR  | 1;
	  	funcao0 = f;
	}
	else {
		EICRA   = EICRA | 0x08;   // configura que a interrupção sera na borda de descida
		EIMSK   = EIMSK | 0x02;   // configura que a interrupcao escolhida sera INT0 pino D2 do atmega328
		EIFR    = EIFR  | 0x02;
		funcao1 = f;
	}
}
void habilita_interrupcao_externa (uint8_t numero_interrupcao)
{
	if (numero_interrupcao==INT0)
	{
		EICRA   = EICRA | 0x02;   // configura que a interrupção sera na borda de descida
      	EIMSK   = EIMSK | 0x01;   // configura que a interrupcao escolhida sera INT0 pino D2 do atmega328
                                  // que corresponde ao pino digital 2 do arduino UNO
	  	EIFR    = EIFR  | 1;
	}
	else
	{
		EICRA   = EICRA | 0x08;   // configura que a interrupção sera na borda de descida
		EIMSK   = EIMSK | 0x02;   // configura que a interrupcao escolhida sera INT0 pino D2 do atmega328
		EIFR    = EIFR  | 0x02;
	}
}
void desabilita_interrupcao_externa (uint8_t numero_interrupcao)
{
	EIMSK=0; 

	if (numero_interrupcao==INT0) EIMSK = EIMSK & 0xFE;  
	else EIMSK = EIMSK & 0xFD;  
	
}
