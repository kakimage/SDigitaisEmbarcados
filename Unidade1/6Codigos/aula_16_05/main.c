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
#include "seg.h"
#include <stdint.h>


#define PINO 25









int main() {
  
  SystemInit();

  
 uint8_t SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG;
 uint8_t DISPLAY0,DISPLAY1, DISPLAY2, DISPLAY3;
 
  
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
  
  configuraDisplay(SEGA,SEGB,SEGC,SEGD,SEGE,SEGF,SEGG,DISPLAY0,DISPLAY1,DISPLAY2, DISPLAY3);
  
  uint8_t linha0, linha1, linha2, linha3;
  uint8_t coluna0, coluna1, coluna2, coluna3;
  
  linha0 = PIN(2,4);
linha1 = PIN(2,5);
linha2 = PIN(2,6);
linha3 = PIN(2,7);
coluna0 = PIN(2,0);
coluna1 = PIN(2,1);
coluna2 = PIN(2,2);
coluna3 = PIN(2,3);



  uint8_t letra;
   teclado_configura(coluna0,coluna1,coluna2,coluna3,linha0,linha1,linha2,linha3);
   teclado_bread(&letra);
  
    mostra(letra);
  for(;;) {
    
  }
}
