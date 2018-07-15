#ifndef _SA_ALTO_
#define _SA_ALTO_
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#include <inttypes.h> 
#include "SA_baixo.h"



typedef struct {
	uint8_t  id;	
	entrada_arquivo arquivo;
	uint16_t posicao;
}meu_FILE;



#define MIN(A,B) ((A<B)?A:B)
void meu_fseek (meu_FILE *A, uint16_t offset, uint8_t origem);
void inicializa_SA(void);
void cria_SA (void);
void mostra_entrada_arquivos(void);
meu_FILE * meu_fopen (char nome[], char modo[]);
uint16_t meu_fwrite( void *buffer, uint8_t tamanho_bytes, uint16_t qtd, meu_FILE *A);
void meu_fread( void *buffer, uint8_t tamanho_bytes, uint16_t qtd, meu_FILE *A);




#endif
