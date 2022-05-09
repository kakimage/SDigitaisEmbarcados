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

uint8_t digitalRead (uint8_t pb)
{
	uint8_t porta = pb >> 5;
	uint8_t bit = pb & 31;
	 return ( (   ((vet[porta]->FIOPIN) >>  bit)  & 1)) ;
	
}

void mostraDisplay (uint8_t numero_display, uint8_t valor)
{
  digitalWrite(SEGA, HIGH);
  digitalWrite(SEGB, HIGH);
  digitalWrite(SEGC, HIGH);
  digitalWrite(SEGD, HIGH);
  digitalWrite(SEGE, LOW);
  digitalWrite(SEGF, LOW);
  digitalWrite(SEGG, HIGH);
    digitalWrite(DISPLAY0, HIGH);
}
int main() {
  
  SystemInit();


  uint8_t SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG;
  uint8_t DISPLAY0;
  
  SEGA = PIN(0,4);
  SEGB = PIN(0,5);
  SEGC = PIN(0,6);
  SEGD = PIN(0,7);
  SEGE = PIN(0,8);
  SEGF = PIN(0,9);
  SEGG = PIN(0,10);
  DISPLAY0 = PIN(3,25);
  
  
  pinMode( SEGA, OUTPUT);
  pinMode( SEGB, OUTPUT);
  pinMode( SEGC, OUTPUT);
  pinMode( SEGD, OUTPUT);
  pinMode( SEGE, OUTPUT);
  pinMode( SEGF, OUTPUT);
  pinMode( SEGG, OUTPUT);
  pinMode(DISPLAY0, OUTPUT);
  
  digitalWrite(SEGA, HIGH);
  digitalWrite(SEGB, HIGH);
  digitalWrite(SEGC, HIGH);
  digitalWrite(SEGD, HIGH);
  digitalWrite(SEGE, LOW);
  digitalWrite(SEGF, LOW);
  digitalWrite(SEGG, HIGH);
    digitalWrite(DISPLAY0, HIGH);
    
  for(;;) {
    
  }
}
