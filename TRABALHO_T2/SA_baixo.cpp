#include "memoria.h"
#include "SA_baixo.h"
#include <stdio.h>
#include <string.h>



void SA_escreve_cabecalho (uint16_t bloco)
{
	memoria_write (0, 0, (uint8_t *) &bloco, sizeof(uint16_t));
}
void SA_salva_entrada_arquivo(uint8_t numero, entrada_arquivo e)
{
	uint16_t posicao = 2 + (numero * sizeof(entrada_arquivo));
	memoria_write (0, posicao, (uint8_t *) &e, sizeof(entrada_arquivo));


}
void SA_format(void)
{
	printf("SA_format\n");
	SA_escreve_cabecalho(65);

	entrada_arquivo ent;

	ent.status = 0;
	strcpy(ent.nome,"vazio");
	ent.inicio=INVALIDO;
	ent.tamanho=0;

	for (int x=0;x<10;x++) 	SA_salva_entrada_arquivo(x, ent);



}
