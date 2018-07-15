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
// Here, we describe what should be done when the interrupt on Timer 0 is handled;
// We do that by writing this function, whose address is “recorded” in the vector table
// from file startup_LPC17xx.s under the name TIMER0_IRQHandler;
void TIMER0_IRQHandler(void)
{
 if ( (LPC_TIM0->IR & 0x01) == 0x01 ) // if MR0 interrupt
 {
 LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag (see page 492 and 493 of user manual)
 LPC_GPIO0->FIOPIN ^= 1 << 11; // Toggle the LED (see lab1)
 }

}

int main (void)
{
 // (1) Timer 0 configuration (see page 490 of user manual)
 LPC_SC->PCONP |= 1 << 1; // Power up Timer 0 (see page 63 of user manual)
 LPC_SC->PCLKSEL0 |= 1 << 2; // Clock for timer = CCLK, i.e., CPU Clock (see page 56 of user manual)
 LPC_TIM0->MR0 = 1 << 23; // Give a value suitable for the LED blinking
 // frequency based on the clock frequency (see page 492 and 496 of user manual)
 LPC_TIM0->MCR |= 1 << 0; // Interrupt on Match 0 compare (see page 492 and 496 of user manual)
 LPC_TIM0->MCR |= 1 << 1; // Reset timer on Match 0 (see page 492 and 496 of user manual)
 LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer 0 (forced); (see page 492 and 494 of user manual)
 LPC_TIM0->TCR &= ~(1 << 1); // Stop resetting the timer (see page 492 and 494 of user manual)
 // (2) Enable timer interrupt; TIMER0_IRQn is 1, see lpc17xx.h and page 73 of user manual
 NVIC_EnableIRQ(TIMER0_IRQn); // see core_cm3.h header file
 LPC_TIM0->TCR |= 1 << 0; // Start timer (see page 492 and 494 of user manual)
 LPC_SC->PCONP |= ( 1 << 15 ); // Power up GPIO (see lab1)
 LPC_GPIO0->FIODIR |= 1 << 11; // Put P1.29 into output mode. LED is connected to P1.29
 while (1) // Why do we need this?
 {
 // do nothing
 }
 return 0;

}

