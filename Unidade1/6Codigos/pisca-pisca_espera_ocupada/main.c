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

#define LED4_PIN (29)


volatile uint32_t delay;


int main() {
  
  SystemInit();
  
    // Setup P1.23 as output
  LPC_GPIO1->FIODIR |= (1 << LED4_PIN);
    
  for(;;) {
    for(delay = 0; delay < 1000000; delay++) {
       __asm("NOP");
    }
    
    // Turn LED ON
    LPC_GPIO1->FIOSET = (1 << LED4_PIN);
    
    for(uint32_t delay = 0; delay < 1000000; delay++) {
       __asm("NOP");
    }
    
    // Turn LED OFF
    LPC_GPIO1->FIOCLR = (1 << LED4_PIN);
  }
}
