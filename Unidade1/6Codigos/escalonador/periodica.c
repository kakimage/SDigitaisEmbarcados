#include "periodica.h"
#include "timer.h"
#include <stdlib.h>
#include <string.h>


struct elemento *lista;

void tratadorTimer(void)
{
	struct elemento *tmp;
	
	tmp = lista;
    
	while (tmp != NULL)
    {
            tmp->contador--;
            if (tmp->contador==0)
            {

                tmp->contador=tmp->periodo;
                tmp->funcao();
            }
        	tmp = tmp->proximo;
    }
        	
}

void periodica_init(void)
{
    lista = NULL;
    timer_init(tratadorTimer);
}
void periodica_cria(char *nome, uint16_t periodo, void (*funcao)(void) )
{

    struct elemento *novo;

    novo = (struct elemento *) malloc (sizeof (struct elemento));

    novo->periodo = periodo;
    novo->contador = periodo;
    novo->funcao = funcao;
    strcpy(novo->nome, nome);
    novo->proximo = lista;
    lista = novo;

}


