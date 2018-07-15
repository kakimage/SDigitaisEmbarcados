
#ifndef _SA_
#define _SA_
#include <inttypes.h> 

// Definicoes do SA e da EEPROM
#define MAXIMO_ARQUIVOS 10
#define TAMANHO_EEPROM 8*1024


// inicio de cada area de memoria
#define INICIO_AREA_ENTRADA_ARQUIVOS   (TAMANHO_BLOCO_PONTEIRO)
#define INICIO_AREA_BLOCO_PONTEIROS    (CABECALHO)
#define INICIO_AREA_BLOCO_DADOS        (CABECALHO+QTD_BLOCOS*TAMANHO_BLOCO_PONTEIRO)


// tamanhos de blocos
#define TAMANHO_BLOCO_PONTEIRO 2
#define TAMANHO_BLOCO_DADOS 32
#define CABECALHO (TAMANHO_BLOCO_PONTEIRO+10*sizeof(entrada_arquivo))
#define SOMA_BLOCOS (TAMANHO_BLOCO_PONTEIRO+TAMANHO_BLOCO_DADOS)


#define BLOCO_PONTEIRO(x) (INICIO_AREA_BLOCO_PONTEIROS+x*TAMANHO_BLOCO_PONTEIRO)

#define QTD_BLOCOS ((TAMANHO_EEPROM-CABECALHO)/(SOMA_BLOCOS))
#define INVALIDO 0xFFFF

#pragma pack(1)
typedef struct {
	uint8_t  status;
	char     nome[8];
	uint16_t inicio;
	uint16_t tamanho;
}entrada_arquivo;

// ******************************* Funcoes diversas ***********************************
void faz_inicializa_memoria(void);
void faz_mostra_arquivos (void);
void mostra_entrada_arquivos(void);


// ****************************** Manipula entradas de arquivos ************************
void cria_entrada_arquivo (uint8_t numero, entrada_arquivo dados);
void le_entrada_arquivo (uint8_t numero, entrada_arquivo *dados);


// ****************************** Manipula bloco livre **********************************
void escreve_bloco_livre (uint16_t numero);
uint16_t leia_bloco_livre (void);

// **************************** Ponteiros ********************************
void cria_bloco_ponteiro(uint16_t numero, uint16_t valor);
uint16_t le_bloco_ponteiro(uint16_t numero);


uint16_t localiza_N_bloco_logico (uint8_t id, uint16_t numero);

uint16_t aloca (void);


// **************************** Blocos de Dados
void escreve_bloco_dados(uint16_t endereco, uint16_t offset, void * dados, uint16_t tam);
void le_bloco_dados (uint16_t endereco, uint16_t offset,  uint8_t * dados, uint16_t qtd);

#endif
