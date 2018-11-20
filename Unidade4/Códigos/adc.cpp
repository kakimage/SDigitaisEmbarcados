#include "LPC17xx.h"
#include "adc.h"


#define ADC_POWERON (1 << 12) 
#define PCLK_ADC 24
#define PCLK_ADC_MASK (3 << 24)
// AD0.0 - P0.23, PINSEL1 [15:14] = 01
#define SELECT_ADC0 (0x1<<14)
// ADOCR constants
#define START_ADC (1<<24)
#define OPERATIONAL_ADC (1 << 21)
#define SEL_AD0 (1 <<0)
#define ADC_DONE_BIT	(1 << 31)


int le_adc (void)
{

	int adval;
	
	// Energia o periodico conversor AD 
	LPC_SC->PCONP |=  ADC_POWERON;

	// Ajusta a frequencia de clock que o conversor ira operar
	LPC_SC->PCLKSEL0 = LPC_SC->PCLKSEL0 & ~(PCLK_ADC_MASK);
	LPC_SC->PCLKSEL0 |=  (3 << PCLK_ADC);
		
	// Configura que o pino P0.23 sera utilizado na funcao AD0.0 
	// pagina 106 do datasheet
	LPC_PINCON->PINSEL1	|= SELECT_ADC0; 
	
	// Enter an infinite loop, just checking ADC pot and incrementing a counter
	while(1) {
		// Inicia a conversao e seleciona o AD0 como canal 
		LPC_ADC->ADCR = START_ADC | OPERATIONAL_ADC | SEL_AD0 ;

		do {
			adval = LPC_ADC->ADGDR;              // Le o registrador de resultado
		} while ((adval & ADC_DONE_BIT) == 0);   
		// fica numa espera ocupada ate terminar a conversao
		
		LPC_ADC->ADGDR &= ~(START_ADC | OPERATIONAL_ADC | SEL_AD0 );   
		// Para a conversao

		 // Captura os 12 bits do valor do resultado [15:4]
		adval = (adval >> 4) & 0x0FFF ;            
		return adval;
	}
	return 0;
}
