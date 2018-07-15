// EXEMPLO DE UM Pisca Pisca que usa a Lampada do kit
// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000


#include <stdio.h>
#include "LPC17xx.h"
#include "uart.h"
#include "tarefa.h"
#include "memoria.h"
#include <stdint.h>



int main() {
  
  
  	uint8_t valor;
	SystemInit();
	
	UART0_Init(9600);
	printf("Rodando\n");
   
    tarefa.start();
    memoriaInit();
    
  	uint8_t vetor[]={65,66,67,68,69,70}; 
  	uint8_t vetor2[6];
  	
    escreveBuffer (20, vetor, 6);
    
    leBuffer  ( 20, vetor2, 6);
    
    for (int x=0;x<10;x++) printf("%d\n",vetor2[x]);
       
  while (1)
  {
	 
     
  }

	
	
	
}
