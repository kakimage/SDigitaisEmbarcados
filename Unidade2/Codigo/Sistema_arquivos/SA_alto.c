#include "SA_alto.h"
#include "SA_baixo.h"
#include <string.h>
#include <stdlib.h>

void atualiza_meta_dados_arquivo( meu_FILE *A)
{
	cria_entrada_arquivo (A->id, A->arquivo);
}
uint8_t aloca_bloco_arquivo ( meu_FILE *A)
{
	uint16_t  bloco, novo, inicial, anterior=0;

	novo = aloca();
	
	// encontra o primeiro bloco de um arquivo pelo seu ID
	bloco = inicial =A->arquivo.inicio;
	
	while(bloco != INVALIDO)
	{
				anterior = bloco;
				bloco    = le_bloco_ponteiro(bloco);
	}
	if (bloco==inicial)
	{
		// eh o primeiro bloco da lista
		//modifica a entrada de arquivo	
		//atualiza_primeiro_bloco_logico(id, novo);	
		A->arquivo.inicio = novo;
	}
	else {
		// nao eh o primeiro
		// modifica o ponteiro do ultimo
		cria_bloco_ponteiro(anterior, novo);

	}
	
	//return bloco_inicial;	
	return novo;	
}
void meu_fread( void *buffer, uint8_t tamanho_bytes, uint16_t qtd, meu_FILE *A)
{
	uint16_t offset, aux, resto, numero_bloco_logico, endereco, posicao, bytes_gravar, bytes_gravados=0;

	bytes_gravar = tamanho_bytes*qtd;
	
	
	
    posicao      =  MIN(A->posicao, A->arquivo.tamanho);

	while (bytes_gravados < bytes_gravar)
	{
		numero_bloco_logico = posicao / (TAMANHO_BLOCO_DADOS);
		endereco            = localiza_N_bloco_logico (A->id, numero_bloco_logico);
		if (endereco == INVALIDO) return;
		
		offset = posicao % (TAMANHO_BLOCO_DADOS);
		resto  = (TAMANHO_BLOCO_DADOS) - offset;
		aux = MIN(resto,(bytes_gravar-bytes_gravados));
		le_bloco_dados(endereco, offset, buffer+bytes_gravados, aux);
		posicao = posicao  + aux;
		bytes_gravados = bytes_gravados +aux;
		
	}
	A->posicao = posicao;
}

meu_FILE * meu_fopen (char nome[], char modo[])
{
	meu_FILE *A=NULL;
	entrada_arquivo entrada;
	uint8_t x;

	uint8_t vazia=MAXIMO_ARQUIVOS;
	
	if ( strcmp(modo,"w")==0)
	{
		for (x=0;x < MAXIMO_ARQUIVOS;x++)
		{
			le_entrada_arquivo(x, &entrada);
			if ((entrada.status==0) && (vazia ==MAXIMO_ARQUIVOS)) vazia = x;
			if ((strcmp(nome, entrada.nome)==0) && (entrada.status==1) )
			{
				// apaga o arquivo e inicia um novo	
				break;	
			}
		}
		//cria arquivo novo cuja entrada é a posicao vazia
		strcpy(entrada.nome, nome);
		entrada.status=1;
		entrada.tamanho=0;
		entrada.inicio = INVALIDO;
		cria_entrada_arquivo (vazia, entrada);

		A = (meu_FILE *) malloc (	sizeof(meu_FILE));	
		A->id = vazia;
		A->arquivo = entrada;
		A->posicao = 0;
		
	}
	return A;
}
void meu_fseek (meu_FILE *A, uint16_t offset, uint8_t origem)
{
	switch (origem)
	{
		case SEEK_SET:
				A->posicao = offset;
			break;
		case SEEK_CUR:
			break;
		case SEEK_END:
			break;
	}
}
uint16_t meu_fwrite( void *buffer, uint8_t tamanho_bytes, uint16_t qtd, meu_FILE *A)
{
	uint16_t offset, aux, resto, numero_bloco_logico, endereco, posicao, bytes_gravar, bytes_gravados=0;
 

	bytes_gravar = tamanho_bytes*qtd;
	
	
    posicao      =  MIN(A->posicao, A->arquivo.tamanho);

	while (bytes_gravados < bytes_gravar)
	{
		numero_bloco_logico = posicao / (TAMANHO_BLOCO_DADOS);
		endereco            = localiza_N_bloco_logico (A->id, numero_bloco_logico);
		if (endereco == INVALIDO)
		{
			endereco = aloca_bloco_arquivo (A);
			if (endereco==INVALIDO) break;
		}
		offset = posicao % (TAMANHO_BLOCO_DADOS);
		resto  = (TAMANHO_BLOCO_DADOS) - offset;
		aux = MIN(resto,(bytes_gravar-bytes_gravados));
		escreve_bloco_dados(endereco, offset, buffer+bytes_gravados, aux);
		posicao = posicao  + aux;
		bytes_gravados = bytes_gravados +aux;
		
	}

	if (A->arquivo.tamanho < A->posicao + bytes_gravados)
	{
		A->arquivo.tamanho  = A->posicao + bytes_gravados;
		atualiza_meta_dados_arquivo(A);

	}
	A->posicao=posicao;
	return tamanho_bytes*qtd;
}
void mostra_entrada_arquivos(void)
{
	faz_mostra_arquivos();
}
void cria_SA (void)
{
	uint16_t x;
	entrada_arquivo R;

	inicializa_SA();

	strcpy(R.nome,"NULLO");
	R.status  = 0;
	R.tamanho = 0;
	R.inicio  = INVALIDO;
	escreve_bloco_livre ( 0 );

	for (x=0; x < MAXIMO_ARQUIVOS; x++)   cria_entrada_arquivo(x, R);
	for (x=0; x < QTD_BLOCOS-1;    x++)   cria_bloco_ponteiro(x, x+1);
	cria_bloco_ponteiro(x, INVALIDO);    // ultimo bloco termina a lista encadeada

}
void inicializa_SA(void)
{
	faz_inicializa_memoria();

}

