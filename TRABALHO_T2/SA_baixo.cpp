#include "memoria.h"
#include "SA_baixo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




void SA_escreve_cabecalho (uint16_t bloco)
{
	memoria_write (0, 0, (uint8_t *) &bloco, sizeof(uint16_t));
}
void SA_salva_entrada_arquivo(uint8_t numero, entrada_arquivo e)
{
	uint16_t posicao = 2 + (numero * sizeof(entrada_arquivo));
	memoria_write (0, posicao, (uint8_t *) &e, sizeof(entrada_arquivo));
}
void SA_leia_entrada_arquivo (uint8_t numero, entrada_arquivo *e)
{
		uint16_t posicao = 2 + (numero * sizeof(entrada_arquivo));
	memoria_read (0, posicao, (uint8_t *) e, sizeof(entrada_arquivo));


}
void SA_salva_bloco_dados(uint8_t numero ,Tipo_Bloco b)
{
	uint16_t posicao = INICIO_AREA_BLOCO_PONTEIROS+ numero*TAMANHO_BLOCO;
	memoria_write (0, posicao, (uint8_t *) &b, sizeof(Tipo_Bloco));
}

SA_FILE * SA_fopen (const char *nome, const char *modo)
{
	entrada_arquivo ent;

	if (strcmp (modo, "w")==0)
	{

		int achou = -1;
		for (int x=0;x < 12;x++) 
		{
			SA_leia_entrada_arquivo(x, &ent);
			if ((ent.status == 0) && (achou ==-1)) achou = x;
			if (strcmp(nome, ent.nome)==0)
			{
				
				// arquivo existe, deixa para os alunos fazerem
				break;
			}

		}
		// arquivo nao existe, cria
		if (achou != -1)
		{
			// existe vaga
			ent.status = 1;
			strcpy(ent.nome,nome);
			ent.tamanho = 0;
			SA_salva_entrada_arquivo(achou, ent);
			// aloca o file e retorna ele
			SA_FILE *tmp;
			tmp = (SA_FILE *) malloc (sizeof(SA_FILE));
			tmp->id = achou;
			return tmp;
		}
		else return NULL; 

		

	}
	return NULL;
}

void SA_format(void)
{
	printf("SA_format\n");
	SA_escreve_cabecalho(0);

	entrada_arquivo ent;
	Tipo_Bloco bloco;

	ent.status = 0;
	strcpy(ent.nome,"vazio");
	ent.indireto=INVALIDO;
	ent.tamanho=0;

	for (int x=0;x<32;x++) ent.dados[x]=0;
	for (int x=0;x<MAXIMO_ARQUIVOS;x++) 	SA_salva_entrada_arquivo(x, ent);

	printf("Criando %ld\n",QTD_BLOCOS);
	for (int x=0;x<32;x++) bloco.dados[x]=0;
	for (uint16_t x=0;x<QTD_BLOCOS-1;x++)
	{
		bloco.ponteiro=x+1;
		SA_salva_bloco_dados(x,bloco);
	}
	bloco.ponteiro=INVALIDO;
	SA_salva_bloco_dados(QTD_BLOCOS-1,bloco);




}
