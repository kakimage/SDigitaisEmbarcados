typedef struct _partitions {
	unsigned char status;
	unsigned char head;
	uint16_t chs;
	unsigned char partition_type;
	unsigned char ehead;
	uint16_t echs;
	uint32_t lsector;
	uint32_t xsector;
 }Tpartition;





typedef struct _MBR {
	unsigned char codeArea[446];
	Tpartition    partitions[4]; 
	unsigned char MBRsignature[2];
}MBR;
