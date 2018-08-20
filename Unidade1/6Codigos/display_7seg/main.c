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

#define MEU_LED PIN4_29
#define BOTAO7   PIN1_08

#define BOTAO0 PIN1_23
#define BOTAO1 PIN1_24
#define BOTAO2 PIN1_25
#define BOTAO3 PIN1_26

#define HABILITA_DISPLAY0 PIN3_25
#define HABILITA_DISPLAY1 PIN3_26
#define HABILITA_DISPLAY2 PIN4_28
#define HABILITA_DISPLAY3 PIN4_29
void mostra (uint32_t alvo, uint8_t caracter);

uint8_t display[]={63,6, 0x5b,0x4f,0x66,0x6d ,0x7d,0x07, 0x7f, 0x6f };
void apresenta (uint16_t numero)
{
    uint32_t disp[]={HABILITA_DISPLAY0,HABILITA_DISPLAY1,HABILITA_DISPLAY2,HABILITA_DISPLAY3};
    uint8_t x, d;
    uint16_t DIVISOR;
   

    DIVISOR = 1000;
    for (x=0;x<4;x++)
    {
        d = numero / DIVISOR;
        numero = numero % DIVISOR;
        DIVISOR = DIVISOR/10;
        mostra(disp[x],d);
    }
}
void mostra (uint32_t alvo, uint8_t caracter)
{
    uint8_t v;

    digitalWrite(HABILITA_DISPLAY0, LOW); 
    digitalWrite(HABILITA_DISPLAY1, LOW);  
    digitalWrite(HABILITA_DISPLAY2, LOW);  
    digitalWrite(HABILITA_DISPLAY3, LOW);  
 
    v = display[caracter];
    if (v & 1)      digitalWrite(SEGA, HIGH);
    else digitalWrite(SEGA, LOW);

    if ((v>>1) & 1) digitalWrite(SEGB, HIGH);
    else digitalWrite(SEGB, LOW);    
    
    if ((v>>2) & 1) digitalWrite(SEGC, HIGH);
    else digitalWrite(SEGC, LOW);

    if ((v>>3) & 1) digitalWrite(SEGD, HIGH);
    else digitalWrite(SEGD, LOW);

    if ((v>>4) & 1) digitalWrite(SEGE, HIGH);
    else digitalWrite(SEGE, LOW);

    if ((v>>5) & 1) digitalWrite(SEGF, HIGH);
    else digitalWrite(SEGF, LOW);

    if ((v>>6) & 1) digitalWrite(SEGG, HIGH);
    else digitalWrite(SEGG, LOW);  

    digitalWrite(alvo, HIGH);
    for (int x=0;x<10000;x++) asm("nop");

}
int main() {
  
  SystemInit();

  
  pinMode(SEGA, OUTPUT);
  pinMode(SEGB, OUTPUT);
  pinMode(SEGC, OUTPUT);
  pinMode(SEGD, OUTPUT);
  pinMode(SEGE, OUTPUT);
  pinMode(SEGF, OUTPUT);
  pinMode(SEGG, OUTPUT);
   
  pinMode(HABILITA_DISPLAY0, OUTPUT);
  pinMode(HABILITA_DISPLAY1, OUTPUT);
  pinMode(HABILITA_DISPLAY2, OUTPUT);
  pinMode(HABILITA_DISPLAY3, OUTPUT);
 
  digitalWrite(HABILITA_DISPLAY0, LOW);
  digitalWrite(HABILITA_DISPLAY1, LOW);
  digitalWrite(HABILITA_DISPLAY2, LOW);
  digitalWrite(HABILITA_DISPLAY3, LOW);
  for(;;) {
   apresenta(12);
  

  }
}
