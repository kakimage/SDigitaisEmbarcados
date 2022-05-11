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


#define PINO 25


void mostraDisplay (uint8_t numero_display, uint8_t valor);

 uint8_t SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG;
  uint8_t DISPLAY0,DISPLAY1, DISPLAY2, DISPLAY3;
  
  uint8_t disp[]={0x3f,0x06, 0x5b, 0x4f, 0x66, 0xcd,0x7d,0x07,0x7f,0x6f};
  




volatile uint32_t delay;
void mostra (uint16_t valor)
{
	uint8_t digitos[4];
	uint16_t divisor=1000;
	
	for (int a=0;a<4;a++)
	{
		digitos[a]=valor/divisor;
		valor = valor - digitos[a]*divisor;
		divisor=divisor/10;
	}
	
	uint8_t podeOmitir;
	while (1)
	{
		podeOmitir = 1;
		for (int b=0; b< 4;b++)
		{
			if (digitos[b] != 0) podeOmitir=0;
			
			if (!podeOmitir) mostraDisplay(b, digitos[b]);
			
			for(delay = 0; delay < 40000; delay++) {
       				__asm("NOP");
    			}
		}
	}
	
	
}
void mostraDisplay (uint8_t numero_display, uint8_t valor)
{
  uint8_t v[]={DISPLAY0,DISPLAY1,DISPLAY2,DISPLAY3};
	
  digitalWrite(SEGA, HIGH);
  digitalWrite(SEGB, HIGH);
  digitalWrite(SEGC, HIGH);
  digitalWrite(SEGD, HIGH);
  digitalWrite(SEGE, LOW);
  digitalWrite(SEGF, LOW);
  digitalWrite(SEGG, HIGH);
  digitalWrite(DISPLAY0, LOW);
  digitalWrite(DISPLAY1, LOW);
  digitalWrite(DISPLAY2, LOW);
  digitalWrite(DISPLAY3, LOW);
  
  
  digitalWrite(v[numero_display], HIGH);
  
  digitalWrite(SEGA, disp[valor]&1);
  digitalWrite(SEGB, (disp[valor]>>1)&1);
  digitalWrite(SEGC, (disp[valor]>>2)&1);
  digitalWrite(SEGD, (disp[valor]>>3)&1);
  digitalWrite(SEGE, (disp[valor]>>4)&1);
  digitalWrite(SEGF, (disp[valor]>>5)&1);
  digitalWrite(SEGG, (disp[valor]>>6)&1);
  
}
int main() {
  
  SystemInit();


 
  
  SEGA = PIN(0,4);
  SEGB = PIN(0,5);
  SEGC = PIN(0,6);
  SEGD = PIN(0,7);
  SEGE = PIN(0,8);
  SEGF = PIN(0,9);
  SEGG = PIN(0,10);
  DISPLAY0 = PIN(3,25);
  DISPLAY1 = PIN(3,26);
  DISPLAY2 = PIN(4,28);
  DISPLAY3 = PIN(4,29);
  
  
  
  pinMode( SEGA, OUTPUT);
  pinMode( SEGB, OUTPUT);
  pinMode( SEGC, OUTPUT);
  pinMode( SEGD, OUTPUT);
  pinMode( SEGE, OUTPUT);
  pinMode( SEGF, OUTPUT);
  pinMode( SEGG, OUTPUT);
  pinMode(DISPLAY0, OUTPUT);
  pinMode(DISPLAY1, OUTPUT);
  pinMode(DISPLAY2, OUTPUT);
  pinMode(DISPLAY3, OUTPUT);
  
    mostra(123);
  for(;;) {
    
  }
}
