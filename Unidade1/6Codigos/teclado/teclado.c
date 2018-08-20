#include "teclado.h"
#include "digital.h"

void configura_teclado (void)
{
	pinMode(TECLADO_C0, OUTPUT);
	pinMode(TECLADO_C1, OUTPUT);
	pinMode(TECLADO_C2, OUTPUT);
	pinMode(TECLADO_C3, OUTPUT);

    digitalWrite(TECLADO_C0, LOW);
    digitalWrite(TECLADO_C1, LOW);
    digitalWrite(TECLADO_C2, LOW);
    digitalWrite(TECLADO_C3, LOW);

	pinMode(TECLADO_L0, INPUT);
	pinMode(TECLADO_L1, INPUT);
	pinMode(TECLADO_L2, INPUT);
	pinMode(TECLADO_L3, INPUT);
}

void testa_coluna (uint32_t pino)
{
	digitalWrite(TECLADO_C0, HIGH);
    digitalWrite(TECLADO_C1, HIGH);
    digitalWrite(TECLADO_C2, HIGH);
    digitalWrite(TECLADO_C3, HIGH);
	digitalWrite(pino, LOW);
}
uint8_t le_teclado (void)
{
	testa_coluna(TECLADO_C0);
	if (!digitalRead(TECLADO_L0)) return 1;
	if (!digitalRead(TECLADO_L1)) return 4;
	if (!digitalRead(TECLADO_L2)) return 7;
	if (!digitalRead(TECLADO_L3)) return 14;





	testa_coluna(TECLADO_C1);
	if (!digitalRead(TECLADO_L0)) return 2;
	if (!digitalRead(TECLADO_L1)) return 5;
	if (!digitalRead(TECLADO_L2)) return 8;
	if (!digitalRead(TECLADO_L3)) return 0;


	testa_coluna(TECLADO_C2);
	if (!digitalRead(TECLADO_L0)) return 3;
	if (!digitalRead(TECLADO_L1)) return 6;
	if (!digitalRead(TECLADO_L2)) return 9;
	if (!digitalRead(TECLADO_L3)) return 15;


	testa_coluna(TECLADO_C3);
	if (!digitalRead(TECLADO_L0)) return 10;
	if (!digitalRead(TECLADO_L1)) return 11;
	if (!digitalRead(TECLADO_L2)) return 12;
	if (!digitalRead(TECLADO_L3)) return 13;

	return 100;

}


