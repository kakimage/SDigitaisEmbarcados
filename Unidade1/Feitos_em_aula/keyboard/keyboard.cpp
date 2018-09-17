#include "keyboard.h"
#include "digital.h"

uint8_t vet_linhas[4]={L0, L1, L2, L3};
uint8_t vet_colunas[4]={C0, C1, C2, C3};
uint8_t Matriz[4][4]={ {'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'E','0','F','D'}};


void init_keyboard(void)
{

	for (int x=0; x<4; x++) 
	{
		pinMode (vet_colunas[x], OUTPUT);
		pinMode (vet_linhas[x], INPUT);
	}
	
	
}

uint8_t leia_tecla (uint8_t tipo)
{
	uint8_t a;
	while (1)
	{
		for (int colunasAlvo = 0; colunasAlvo < 4; colunasAlvo++)
		{
			for (int colunas=0;colunas < 4; colunas++) digitalWrite(vet_colunas[colunas], HIGH);
			digitalWrite(vet_colunas[colunasAlvo], LOW);

			for (int linhas = 0; linhas < 4; linhas ++)
			{
				a = digitalRead (vet_linhas[linhas]);
				if (!a) return Matriz[linhas][colunasAlvo];
			}
		}	
		

	}
}


