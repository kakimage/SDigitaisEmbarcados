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
#include <stdint.h>


#define PINO 25
#define PIN(P,B) ((P<<5)|B)
#define INPUT 1
#define OUTPUT 0
#define HIGH 1
#define LOW 0


LPC_GPIO_TypeDef      * vet[5]={LPC_GPIO0,LPC_GPIO1,LPC_GPIO2,LPC_GPIO3,LPC_GPIO4};



void pinMode (uint8_t pb, uint8_t tipo)
{
	uint8_t porta = pb >> 5;
	uint8_t bit = pb & 31;
	if (tipo == OUTPUT) vet[porta]->FIODIR |= (1 << bit);
	else vet[porta]->FIODIR &= (~(1 << bit));
	
}
void digitalWrite( uint8_t pb, uint8_t valor)
{
	uint8_t porta = pb >> 5;
	uint8_t bit = pb & 31;
	
	if (valor==HIGH)
		    vet[porta]->FIOSET = (1 << bit);
	else 
		    vet[porta]->FIOCLR = (1 << bit);
}


volatile uint32_t delay;


int main() {
  
  SystemInit();
  

  pinMode( PIN(3,25), OUTPUT);
    
  for(;;) {
    for(delay = 0; delay < 1000000; delay++) {
       __asm("NOP");
    }
    
    // Turn LED ON
   digitalWrite( PIN(3,25), HIGH);
    
    for(uint32_t delay = 0; delay < 1000000; delay++) {
       __asm("NOP");
    }
    
    // Turn LED OFF
      digitalWrite( PIN(3,25), LOW);
  }
}
