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
#include "teclado.h"
#include "util.h"

#include <stdint.h>



#define BOTAO0 PIN1_23
#define BOTAO1 PIN1_24
#define BOTAO2 PIN1_25
#define BOTAO3 PIN1_26


int main() {
  
  SystemInit();


  display_configura();
  configura_teclado();
  
  
  display_7seg (1);
  Delay(1000);
  display_7seg (2);
  
  display_7seg (9876);

  uint8_t a;
  for(;;) {
	if ((a=le_teclado ()) !=100) display_7seg (a);
  }
}
