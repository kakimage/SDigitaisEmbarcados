//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000

#include "LPC17xx.h"
#include <stdint.h>
#include "display.h"
#include "digital.h"


int main() {
  
  SystemInit();

  pinMode(PIN_4_29, OUTPUT);  // LED G1
  pinMode(PIN_1_08, INPUT);

  while (1)
  {
  	if (  !digitalRead(PIN_1_08)  ) digitalWrite(PIN_4_29, HIGH);
  	else digitalWrite(PIN_4_29, LOW);
  }


  //display_init();

  //mostra("1230");




  while(1)
  {

  }
}
