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


int main() {

  SystemInit();
    
  periodica_init();
  delay_init();
  seg_init( );
   
  
  for (uint16_t v=0;v<9999;v++)
  {
  	seg_apresenta(v);
  	delay_ms(500);
  }
  while(1){}
 
 
 
 
 
 
}
