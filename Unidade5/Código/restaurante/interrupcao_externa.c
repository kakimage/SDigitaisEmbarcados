#include <avr/io.h>
#include <avr/interrupt.h>
#include "interrupcao_externa.h"

void (*funcao)();

// *************************** tratador de interrupcao externa ******************************
// O tratador automaticamente limpa o FLAG de interrupcao externa antes do tratador terminar
ISR (INT0_vect)
{
   funcao();
}
// ******************************************************************************************



void configura_interrupcao_externa(void (*f)(void))
{
      EICRA=0x02;   // configura que a interrupção sera na borda de descida
      EIMSK=1;      // configura que a interrupcao escolhida sera INT0 pino D2 do atmega328
                    // que corresponde ao pino digital 2 do arduino UNO
	  funcao = f;
}
