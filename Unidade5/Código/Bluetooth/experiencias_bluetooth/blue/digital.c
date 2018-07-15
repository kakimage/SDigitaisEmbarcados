
#include "digital.h"
       
void descobre_porta (int8_t pino, int8_t *porta, int8_t *bit)
{
    if (pino <=7)
    { 
        *porta = 1;
        *bit   = pino;
    }
    else {
        *porta = 0;
        *bit   = pino - 8;
    }
    
}
void pinMode (int8_t pino, int8_t valor)
{
    int8_t porta, bit;
  
    descobre_porta (pino, &porta, &bit);
    switch (porta)
    { 
         case 0:
            if (valor==INPUT) DDRB=DDRB & ~(_BV(bit));
            else DDRB= DDRB | _BV(bit);
            break;
         case 1:
            if (valor==INPUT) DDRD=DDRD & ~(_BV(bit));
            else DDRD= DDRD | _BV(bit);
            break;
         
    }
}

unsigned char digitalRead (int pino)
{
      int8_t porta, bit;
  
    descobre_porta (pino, &porta, &bit);

    switch (porta)
    { 
         case 0:
            if (PINB & _BV(bit)) return 1;
            break;
         case 1:
            if (PIND & _BV(bit)) return 1;
            break;
    }
    return 0;
}
void digitalWrite( uint8_t pino, uint8_t valor)
{
     int8_t porta, bit;
  
    descobre_porta (pino, &porta, &bit);

    switch (porta)
    { 
         case 0:
            if (valor==HIGH) PORTB=PORTB | _BV(bit);
            else PORTB=PORTB & ~(_BV(bit));
            
            break;
         case 1:
            if (valor==HIGH) PORTD=PORTD| _BV(bit);
            else PORTD=PORTD & ~(_BV(bit));
            break;
         
    }
}


