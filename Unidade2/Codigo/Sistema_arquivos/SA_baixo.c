
#include "SA_baixo.h"
#include "memoria_i2c.h"
#include <stdio.h>
#include <string.h>

uint16_t captura_bloco_inicial(uint8_t id)
{
	entrada_arquivo tmp;
	le_entrada_arquivo (id, &tmp);
	
	return tmp.inicio; 
}
uint16_t localiza_N_bloco_logico (uint8_t id, uint16_t numero)
{
	uint16_t bloco;
	uint16_t contador=0;
	
    bloco  = captura_bloco_inicial(id);
    
	
	if (numero==contador) return bloco;
   
	while (bloco != INVALIDO)
	{
		bloco    = le_bloco_ponteiro (bloco);
		if (numero==contador+1) return bloco;
		contador++;		
	}
	return INVALIDO;
}
void atualiza_primeiro_bloco_logico(uint8_t id, uint16_t novo)
{
	entrada_arquivo dados;

	le_entrada_arquivo (id, &dados);
	dados.inicio = novo;
	cria_entrada_arquivo (id, dados);

}	

// *******************************************************************************


uint16_t aloca ()
{
	uint16_t livre, proximo;

	livre   = leia_bloco_livre ();
	proximo = le_bloco_ponteiro(livre);
	cria_bloco_ponteiro(livre, INVALIDO);
	escreve_bloco_livre(proximo);
	
	return livre;
		
}
void faz_inicializa_memoria(void)
{
	memoria_configura(DISPOSITIVO_PLACA,32);
}
void cria_entrada_arquivo (uint8_t numero, entrada_arquivo dados)
{	
	uint16_t posicao;
	posicao =  TAMANHO_BLOCO_PONTEIRO+numero*sizeof(entrada_arquivo);
	
	//printf("Cria entrada de arquivo no endereco %d\n", posicao);
	write_bytes ((uint8_t *) &dados, sizeof(entrada_arquivo),posicao);
}
void le_entrada_arquivo (uint8_t numero, entrada_arquivo *dados)
{
	uint16_t posicao;
	posicao =  TAMANHO_BLOCO_PONTEIRO+numero*sizeof(entrada_arquivo);
	read_bytes ((uint8_t *) dados, sizeof(entrada_arquivo),posicao);
}

// ROTINAS QUE MANIPULAM BLOCOS LIVRES
void escreve_bloco_livre (uint16_t numero)
{
#ifdef _DEBUG_
	printf("DEBUG:escreve_bloco_livre(%d)\n",numero);
#endif
	write_bytes ((uint8_t *) &numero, TAMANHO_BLOCO_PONTEIRO,0);
}
uint16_t leia_bloco_livre (void)
{	
	uint16_t numero;
#ifdef _DEBUG_
	printf("DEBUG:leia_bloco_livre = %d\n",numero);
#endif
	read_bytes ((uint8_t *) &numero, TAMANHO_BLOCO_PONTEIRO,0);
	return numero;
}

// 
void 	faz_mostra_arquivos(void)
{
	entrada_arquivo dados; 
	uint8_t x;

	for (x=0;x<10;x++)
	{
		le_entrada_arquivo (x, &dados);
		printf("Status:%d Nome:%s tamanho:%d inicio:%d\n",dados.status, dados.nome, dados.tamanho, dados.inicio);
	}
}


// ROTINAS QUE MANIPULAM BLOCOS DE PONTEIROS
void cria_bloco_ponteiro(uint16_t numero, uint16_t valor)
{
	uint16_t posicao;
	//printf("cria_bloco_ponteiro(%d, %d)\n",numero, valor);
	posicao = numero*TAMANHO_BLOCO_PONTEIRO+INICIO_AREA_BLOCO_PONTEIROS ;
	write_bytes ((uint8_t *) &valor, TAMANHO_BLOCO_PONTEIRO,posicao);
}

uint16_t le_bloco_ponteiro(uint16_t numero)
{
	uint16_t valor;
	uint16_t posicao;
	
	//printf("cria_bloco_ponteiro(%d, %d)\n",numero, valor);
	posicao = numero*TAMANHO_BLOCO_PONTEIRO+INICIO_AREA_BLOCO_PONTEIROS ;
	read_bytes ((uint8_t *) &valor, TAMANHO_BLOCO_PONTEIRO,posicao);
	return valor;
}



// ROTINAS QUE MANIPULAM BLOCOS DE DADOS

void escreve_bloco_dados(uint16_t endereco, uint16_t offset, void * dados, uint16_t tam)
{	
	uint16_t posicao;
	posicao = INICIO_AREA_BLOCO_DADOS + endereco*TAMANHO_BLOCO_DADOS;
	write_bytes ((uint8_t *)dados, tam, posicao+offset);
}
void le_bloco_dados (uint16_t endereco, uint16_t offset,  uint8_t * dados, uint16_t qtd)
{
	uint16_t posicao;

	posicao = INICIO_AREA_BLOCO_DADOS + endereco*TAMANHO_BLOCO_DADOS;
	read_bytes (dados, qtd, posicao+offset);
}


