
// Os campos abaixo representam as entradas de arquivos. A area do Diretorio ROOT possui ate X entradas dessas, o valor de X pode ser obtido
// do BOOT. Tipicamente X vale 512 e desta forma, no diretorio ROOT podemos ter ate 512 elementos (arquivos+diretorios)

typedef struct _entrada{
	char nome[8];
	char ext[3];
	uint8_t atributo;
	uint8_t reservado;
	uint8_t create_time;
	uint8_t create_time2[2];
	uint8_t create_date[2];
	uint8_t last_access[2];
	uint16_t first_cluster_high;
	uint8_t modified_time[2];
	uint8_t modified_date[2];
	uint16_t first_cluster;
	uint32_t file_size;
}entrada_FAT;
