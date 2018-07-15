#include "digital.h"
#include "teclado.h"


uint8_t C0, C1, C2, C3;
uint8_t L0, L1, L2, L3;
uint8_t linhas[4];

uint8_t teclas[4][4]={{'1', '2', '3', 'A'},{'4','5','6','B'},{'7','8','9','C'}, {'E','0','F','D'}};

void configura_teclado( uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t l0, uint8_t l1, uint8_t l2, uint8_t l3) 
{
	C0 = c0;
    C1 = c1;
    C2 = c2;
    C3 = c3;
    L0 = l0;
    L1 = l1;
    L2 = l2;
    L3 = l3;

	pinMode(C0, INPUT);
	pinMode(C1, INPUT);
	pinMode(C2, INPUT);
	pinMode(C3, INPUT);

	pinMode(L0, OUTPUT);
	pinMode(L1, OUTPUT);
	pinMode(L2, OUTPUT);
	pinMode(L3, OUTPUT);

    linhas[0]=L0;
    linhas[1]=L1;
    linhas[2]=L2;
    linhas[3]=L3;



}
void seleciona_linha (uint8_t numero)
{
	digitalWrite(L0, HIGH);
	digitalWrite(L1, HIGH);
	digitalWrite(L2, HIGH);
	digitalWrite(L3, HIGH);
	digitalWrite(linhas[numero],LOW);
	

}

uint8_t testa_colunas (void)
{
	if (digitalRead(C0)==0) return 1;
	if (digitalRead(C1)==0) return 2;
	if (digitalRead(C2)==0) return 3;
	if (digitalRead(C3)==0) return 4;
	return 0;
	
}

uint8_t le_teclado (void)
{
	uint8_t linha, valor_colunas;
    while(1)
	{ 
		for (linha=0; linha < 4; linha++)
		{
			seleciona_linha(linha);
			valor_colunas = testa_colunas();
			if (valor_colunas)
			{
				while ( testa_colunas());

				return teclas[linha][valor_colunas-1];
			}
		}
	}
}
