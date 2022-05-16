
#include "teclado.h"
#include "digital.h"

uint8_t c[4],l[4];

 void teclado_configura(uint8_t coluna0, uint8_t coluna1, uint8_t coluna2,uint8_t  coluna3, uint8_t linha0, uint8_t linha1, uint8_t linha2, uint8_t linha3)
 {

     c[0] = coluna0;
     c[1] = coluna1;
     c[2] = coluna2;
     c[3] = coluna3;
     l[0] = linha0;
     l[1] = linha1;
     l[2] = linha2;
     l[3] = linha3;
    
    for (uint8_t x=0;x<4;x++)
    {
        pinMode(l[x],OUTPUT);
        pinMode(c[x],INPUT);
    }

 
 }

 void   teclado_bread(uint8_t *letra)
 {
     uint8_t m[4][4];
     
      uint8_t x=1;
      for (uint8_t ll=0;ll < 3;ll++)
      {
          for (uint8_t cc=0;cc<3;cc++)
          {
              m[ll][cc] = x;
              x++;
          }
      }
      m[0][3]=10;
      m[1][3]=11;
      m[2][3]=12;
      m[3][3]=13;
      m[3][0]=14;
      m[3][1]=0;
      m[3][2]=15;
      
      
      
      
      


     
     
     
    for (uint8_t x=0;x<4;x++) digitalWrite(l[x],HIGH);

    // testa a linha 0;
    digitalWrite(l[0],LOW);


 }
