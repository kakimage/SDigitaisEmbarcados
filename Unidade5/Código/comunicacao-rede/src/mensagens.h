#ifndef _MENSAGENS_
#define _MENSAGENS_
#include <inttypes.h>  

#define ACK 1
#define NORMAL 0
#define PAYLOAD 30
#define QTD_MENSAGENS 10

typedef struct {
    int qtd_msg;
    struct tipo_mensagem *inicio;
}Minha_Lista;

struct tipo_mensagem{
	uint8_t tamanho;
	uint8_t tipo; // 0 normal 1 ACK
	uint8_t numero_serie;
	uint8_t dados[PAYLOAD];

	struct tipo_mensagem *proximo;
};



class lista_mensagens {

	private:
		uint8_t numero_serie;
		Minha_Lista L;
		uint8_t novo_numero_serie(void);

	public:
		uint8_t procura_apaga_por_numero_serie(tipo_mensagem m);
		uint8_t nova_mensagem_ACK(tipo_mensagem M);
		uint8_t nova_mensagem_normal(uint8_t dados[], uint8_t tam);
		void remove_ACKs(void);
		lista_mensagens(void);
		uint8_t insere_mensagem(tipo_mensagem m);
		uint8_t retira_mensagem   (uint8_t dados[]);
		uint8_t consulta(uint8_t indice, tipo_mensagem *m);
		uint8_t qtd_mensagens(void);
};

#endif
