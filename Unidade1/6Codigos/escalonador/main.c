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
#include "teclado.h"
#include "timer.h"



  uint8_t LED = PIN(4,29);

volatile uint8_t estadoLED=HIGH;

void piscaLED (void)
{
  digitalWrite(LED, estadoLED);
  estadoLED=!estadoLED;

}

int main() {

  SystemInit();
  pinMode( LED, OUTPUT);
    timer_init(piscaLED, 12000);

  while(1)
  {

  }
 
}
