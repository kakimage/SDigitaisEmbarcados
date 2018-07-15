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
#define LED4_PIN (28)

volatile unsigned long SysTickCnt;
void SysTick_Handler (void);
void Delay (unsigned long tick);
void SysTick_Handler (void) {
  SysTickCnt++;
}

void Delay (unsigned long tick) {
  unsigned long systickcnt;

  systickcnt = SysTickCnt;
  while ((SysTickCnt - systickcnt) < tick);
}

int main(void){
  SystemInit();
  LPC_GPIO4->FIODIR |= (1 << LED4_PIN);
 SysTick_Config(SystemCoreClock/(9600*4) - 1); /* Generate interrupt each 1 ms   */ 
 




 while(1){            
  LPC_GPIO4->FIOSET = (1 << LED4_PIN);
  Delay(10000);
  LPC_GPIO4->FIOCLR = (1 << LED4_PIN);
  Delay(10000);
 
 }
}
