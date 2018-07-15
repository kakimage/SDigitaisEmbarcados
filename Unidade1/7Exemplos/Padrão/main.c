/**
 * \file  main.c
 * \brief  Teste de hardware do XM700
 * \author Marcelo Martins Maia do Couto
 * \version 1.0
 * \date  Inicio: 25/Ago/2010
 * \date  Final: 25/Ago/2010 
 * \todo 
 * \li Site: www.exsto.com.br
 * \li Email: marcelo@exsto.com.br
 *
 *  (Objetivo) Validar o funcionamento do módulo 7 Segment Display do Projeto XM700  
 */

#include "LPC17xx.h"

// Function to provide short delay
void short_delay (int n);

// Configurando os pinos que estão ligados aos leds
void SSeg_Config(void){

  LPC_GPIO0->FIODIR = 0x00000ff0;
  LPC_GPIO3->FIODIR = 0xffffffff;
  LPC_GPIO4->FIODIR = 0xffffffff;
}

void SSegWrite(unsigned char number){
	unsigned int SSegChar[] = {0xf3ff/*0*/,0xf06f/*1*/,0xf5bf/*2*/,0xf4ff/*3*/
							  ,0xf66f/*4*/,0xf6Df/*5*/,0xf7cf/*6*/,0xf07f/*7*/
							  ,0xf7ff/*8*/,0xf67f/*9*/,0xf77f/*A*/,0xf7cf/*B*/
							  ,0xf39f/*C*/,0xf5ef/*D*/,0xf79f/*E*/,0xf71f/*F*/};
	LPC_GPIO0->FIOPINL =  (SSegChar[number]);
}

void short_delay(int n)
{
   volatile int d;
   for (d=0; d<n*3000; d++){}
}

// MAIN function
int main(void) {

	// Declarando variáveis
	unsigned char counter;
	
	// Set up board/processor
	SystemInit();

	// Configurando Display de Sete Segmentos... 
	SSeg_Config();

	LPC_GPIO4->FIOPIN = 0xf0000000;
	LPC_GPIO3->FIOPIN = 0x0f000000;

	while(1)
	{
		for (counter = 0; counter < 16; counter++)
      	{
      		SSegWrite(counter);
			short_delay(2000);
		}
	}
	return 0 ;
}


