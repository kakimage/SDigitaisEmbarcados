//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000

#include "LPC17xx.h"
#include <stdint.h>
#include "display.h"
#include "keyboard.h"



int main() {
	char st[2];


  SystemInit();
  display_init();


  init_keyboard();
  
  st[0] = leia_tecla(BLQ);
  st[1] = 0;
   mostra(st);
  
  while(1)
  {

  }
}
