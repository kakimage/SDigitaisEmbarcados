
#ifndef _SA_
#define _SA_
#include <inttypes.h> 

// Definicoes do SA e da EEPROM
#define MAXIMO_ARQUIVOS 10
#define TAMANHO_EEPROM 8*1024


// inicio de cada area de memoria
#define INICIO_AREA_ENTRADA_ARQUIVOS   (TAMANHO_BLOCO_PONTEIRO)
#define INICIO_AREA_BLOCO_PONTEIROS    (CABECALHO)


// tamanhos de blocos
#define TAMANHO_BLOCO 34
#define CABECALHO (TAMANHO_BLOCO_PONTEIRO+10*sizeof(entrada_arquivo))




#define BLOCO(x) (INICIO_AREA_BLOCO_PONTEIROS+x*TAMANHO_BLOCO)

#define INVALIDO 0xFFFF

#pragma pack(1)
typedef struct {
	uint8_t  status;
	char     nome[8];
	char     dados[32];
	uint16_t inicio;
	uint16_t tamanho;
}entrada_arquivo;


void SA_format(void);

#endif
