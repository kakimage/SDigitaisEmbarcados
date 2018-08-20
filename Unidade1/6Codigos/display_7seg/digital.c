
#include "digital.h"
#include "LPC17xx.h"

void pinMode (uint32_t pino, uint8_t modo)
{
    uint32_t porta;
    uint32_t bit;

    porta = pino  >> 5;
    bit   = pino & 0x1F;
    
    if (modo == OUTPUT)
    {
        switch (porta)
        {
            case 0:
                LPC_GPIO0->FIODIR |= (1 << bit);
                break;
            case 1:
                LPC_GPIO1->FIODIR |= (1 << bit);
                break;
            case 2:
                LPC_GPIO2->FIODIR |= (1 << bit);
                break;
            case 3:
                LPC_GPIO3->FIODIR |= (1 << bit);
                break;
            case 4:
                LPC_GPIO4->FIODIR |= (1 << bit);
        }
    }
    else
    {
        // codigo para configuraar pino entrada
        switch (porta)
        {
            case 0:
                LPC_GPIO0->FIODIR &= ~(1 << bit);
                break;
            case 1:
                LPC_GPIO1->FIODIR &= ~(1 << bit);
                break;
            case 2:
                LPC_GPIO2->FIODIR &= ~(1 << bit);
                break;
            case 3:
                LPC_GPIO3->FIODIR &= ~(1 << bit);
                break;
            case 4:
                LPC_GPIO4->FIODIR &= ~(1 << bit);
        }
    }
}
uint8_t digitalRead (uint32_t pino)
{
    uint32_t porta;
    uint32_t bit;

    porta = pino  >> 5;
    bit   = pino & 0x1F;

    switch (porta)
        {
            case 0:
                return (   (LPC_GPIO0->FIOPIN >> bit) & 1) ;
            case 1:
                return (   (LPC_GPIO1->FIOPIN >> bit) & 1) ;
            case 2:
                return (   (LPC_GPIO2->FIOPIN >> bit) & 1) ;
            case 3:
                return (   (LPC_GPIO3->FIOPIN >> bit) & 1) ;
            case 4:
                return (   (LPC_GPIO4->FIOPIN >> bit) & 1) ;
        }
    return 0;
}
void digitalWrite (uint32_t pino, uint8_t valor)
{
    uint32_t porta;
    uint32_t bit;

    porta = pino  >> 5;
    bit   = pino & 0x1F;

    switch (porta)
        {
            case 0:
                if (valor==HIGH)
                    LPC_GPIO0->FIOSET |= (1 << bit);
                else
                    LPC_GPIO0->FIOCLR |= (1 << bit);
                break;
            case 1:
                if (valor==HIGH)
                    LPC_GPIO1->FIOSET |= (1 << bit);
                else
                    LPC_GPIO1->FIOCLR |= (1 << bit);
                break;
            case 2:
                if (valor==HIGH)
                    LPC_GPIO2->FIOSET |= (1 << bit);
                else
                    LPC_GPIO2->FIOCLR |= (1 << bit);
                break;
            case 3:
                if (valor==HIGH)
                    LPC_GPIO3->FIOSET |= (1 << bit);
                else
                    LPC_GPIO3->FIOCLR |= (1 << bit);
                break;
            case 4:
                if (valor==HIGH)
                    LPC_GPIO4->FIOSET |= (1 << bit);
                else
                    LPC_GPIO4->FIOCLR |= (1 << bit);
                break;
        }
}



