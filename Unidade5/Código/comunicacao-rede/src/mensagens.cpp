#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

#include "mensagens.h"


lista_mensagens::lista_mensagens (void)
{
	numero_serie = 0;
	L.qtd_msg    = 0;
    L.inicio     = NULL;
}

uint8_t lista_mensagens::qtd_mensagens(void)
{
	return L.qtd_msg;
}
void    lista_mensagens::remove_ACKs(void)
{
	struct tipo_mensagem *tmp, *aux,*anterior = NULL;

	if (L.qtd_msg) 
	{
		tmp = L.inicio;
		while (tmp != NULL)
		{
			if (tmp->tipo==ACK)
			{
				L.qtd_msg--;

				aux = tmp;
				if (anterior==NULL)
				{
					L.inicio = tmp->proximo;
				}
				else anterior->proximo = tmp->proximo;
				tmp = tmp->proximo;
				free(aux);
			}
			else 
			{
				anterior = tmp;
	
				tmp = tmp->proximo;
			}
		}
		


	}

}
uint8_t lista_mensagens::consulta(uint8_t indice, tipo_mensagem *m)
{
	struct tipo_mensagem *tmp;
	volatile uint8_t x;

	if (L.qtd_msg && indice < L.qtd_msg) 
	{
		tmp = L.inicio;
		for (x=0;x<indice;x++)	tmp = tmp->proximo;
		
		m->tipo         = tmp->tipo;
		m->numero_serie = tmp->numero_serie;
		m->tamanho      = tmp->tamanho;
		for (x=0;x<m->tamanho;x++) m->dados[x] = tmp->dados[x];

		return 1;
	}
	return 0;
}


uint8_t lista_mensagens::novo_numero_serie(void)
{
	uint8_t tmp = numero_serie;
	
	numero_serie++;
	return tmp;
}

uint8_t lista_mensagens::nova_mensagem_ACK(tipo_mensagem M)
{	
	struct tipo_mensagem *tmp;

	if (L.qtd_msg <10)
	{
		L.qtd_msg++;

		tmp = (struct tipo_mensagem *) malloc (sizeof(struct tipo_mensagem));
		tmp->tipo    = ACK;
		tmp->tamanho = 1;
		tmp->dados[0] = M.numero_serie;
		tmp->numero_serie = 0;

		tmp->proximo = L.inicio;
		L.inicio = tmp;		

		return 1;
	}
	return 0;
}
uint8_t lista_mensagens::nova_mensagem_normal(uint8_t dados[], uint8_t tam)
{	
	uint8_t x;
	struct tipo_mensagem *tmp, *R, *anterior=NULL;

	if (L.qtd_msg <10)
	{
		L.qtd_msg++;

		tmp = (struct tipo_mensagem *) malloc (sizeof(struct tipo_mensagem));
		tmp->tipo    = NORMAL;
		tmp->tamanho = tam;
		tmp->numero_serie = novo_numero_serie();
		for (x=0;x<tam;x++) tmp->dados[x] = dados[x];
		R = L.inicio;
		while (R != NULL)
		{
			// verifica se eh o primeiro
			if (R->numero_serie < tmp->numero_serie) break;
           	anterior = R;
        	R = (R->proximo);
		}
		tmp->proximo = R;
		if (L.inicio==R) L.inicio = tmp;
		else   anterior->proximo=tmp;

		return 1;
	}
	return 0;
}
uint8_t lista_mensagens::procura_apaga_por_numero_serie(tipo_mensagem m)
{
	return 0;
}
uint8_t lista_mensagens::insere_mensagem(tipo_mensagem m)
{	
	volatile uint8_t x;
	struct tipo_mensagem *tmp, *R, *anterior=NULL;

	if (L.qtd_msg <10)
	{
		L.qtd_msg++;
		tmp = (struct tipo_mensagem *) malloc (sizeof(struct tipo_mensagem));
		tmp->tipo    = m.tipo;
		tmp->tamanho = m.tamanho;
		tmp->numero_serie = m.numero_serie;
		for (x=0;x<tmp->tamanho;x++) tmp->dados[x] = m.dados[x];
		R = L.inicio;
		while (R != NULL)
		{
			// verifica se eh o primeiro
			if (R->numero_serie < tmp->numero_serie) break;
           	anterior = R;
        	R = (R->proximo);
		}
		tmp->proximo = R;
		if (L.inicio==R) L.inicio = tmp;
		else   anterior->proximo=tmp;

		return 1;
	}
	return 0;
}
uint8_t lista_mensagens::retira_mensagem   (uint8_t dados[])
{
	uint8_t x, tamanho;
	struct tipo_mensagem *m;

	if (!L.inicio) return 0;
	
	m = L.inicio;

	tamanho=m->tamanho; 
	
	for (x=0;x<m->tamanho;x++) dados[x] = m->dados[x];
	L.inicio = m->proximo;
	free(m);
	L.qtd_msg--;

	return tamanho;
		
}
