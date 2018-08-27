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
#include "digital.h"


volatile uint32_t _delay;

void delay (void)
{
	for(uint32_t _delay = 0; _delay < 1000000; _delay++) {
       __asm("NOP");
    }
}

int main() {
  
  SystemInit();
  
  pinMode(Pino(4, 29), OUTPUT);

  pinMode(PIN3_26, OUTPUT);
  digitalWrite(PIN3_26, HIGH);
  for(;;) {
    delay();
    digitalWrite(PIN4_29, HIGH);
    delay();
    digitalWrite(PIN4_29, LOW);

  }
}
