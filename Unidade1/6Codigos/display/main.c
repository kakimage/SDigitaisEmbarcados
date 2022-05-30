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


#include "LPC17xx.h"
#include "digital.h"
#include <stdint.h>
#include "periodica.h"
#include "delay.h"


#define LED_VERMELHO PIN(3,26)
#define LED_VERDE     PIN(4,29)



void piscaLedVermelho (void)
{
	static uint8_t estadoLedVermelho = LOW;
	digitalWrite(LED_VERMELHO, estadoLedVermelho);
	estadoLedVermelho = !estadoLedVermelho;
}

void  piscaLedVerde (void)
{
	static uint8_t estadoLedVerde = LOW;
	digitalWrite(LED_VERDE, estadoLedVerde);
	estadoLedVerde = !estadoLedVerde;
}

int main() {

  SystemInit();
  
  pinMode(LED_VERMELHO,OUTPUT);
  pinMode(LED_VERDE    ,OUTPUT);
  
  
  periodica_init();
  delay_init();
  periodica_cria ("ledVermelho",1000, piscaLedVermelho);

  periodica_cria ("ledAzul"    ,10000, piscaLedVerde);
  delay_ms(10000);
  periodica_remove("ledVermelho");
  
  while(1)
  {

  }
 
}
