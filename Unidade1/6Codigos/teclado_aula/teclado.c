#include "teclado.h"
#include "digital.h"

void configura_teclado(void)
{
	pinMode(C0, OUTPUT);
	pinMode(C1, OUTPUT);
	pinMode(C2, OUTPUT);
	pinMode(C3, OUTPUT);
	
	pinMode(L0, INPUT);
	pinMode(L1, INPUT);
	pinMode(L2, INPUT);
	pinMode(L3, INPUT);

}
void testa_coluna (uint32_t coluna)
{
	digitalWrite(C0, HIGH);
	digitalWrite(C1, HIGH);
	digitalWrite(C2, HIGH);
	digitalWrite(C3, HIGH);
	digitalWrite(coluna, LOW);
}
uint8_t le_teclado(uint8_t bloq)
{
  	do {
	testa_coluna(C0);
    if (!digitalRead(L0)) return 1;
    if (!digitalRead(L1)) return 4;
    if (!digitalRead(L2)) return 7;
    if (!digitalRead(L3)) return 14;

	testa_coluna(C1);
    if (!digitalRead(L0)) return 2;
    if (!digitalRead(L1)) return 5;
    if (!digitalRead(L2)) return 8;
    if (!digitalRead(L3)) return 0;

	testa_coluna(C2);
    if (!digitalRead(L0)) return 3;
    if (!digitalRead(L1)) return 6;
    if (!digitalRead(L2)) return 9;
    if (!digitalRead(L3)) return 15;

	testa_coluna(C3);
    if (!digitalRead(L0)) return 10;
    if (!digitalRead(L1)) return 11;
    if (!digitalRead(L2)) return 12;
    if (!digitalRead(L3)) return 13;
   }while (bloq != NBLOQ);

   return NENHUMA_TECLA;




}
