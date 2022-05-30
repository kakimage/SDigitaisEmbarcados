#include "delay.h"
#include <stdint.h>
#include "periodica.h"

volatile uint64_t contadorTimer = 0;
void funcContador (void)
{
    contadorTimer++;
}
void delay_init(void)
{
    periodica_cria ("timer",1, funcContador);

}
void delay_ms(uint16_t tempo)
{
    uint64_t tmp = contadorTimer;
    while (contadorTimer < tmp + tempo);
   
}