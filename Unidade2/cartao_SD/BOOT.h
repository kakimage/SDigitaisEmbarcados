
#pragma pack(1)

typedef struct ss {
	unsigned char physical_drive_number; 
	unsigned char reserved;
	unsigned char extended_boot_signature;
	unsigned char ID[4];
	char volume_label[11];
	unsigned char fat_type[8];
	unsigned char code[448];
	unsigned char boot_sector_signature[2];
}_fat_antiga;



typedef struct as{
	uint32_t sector_per_file_table;
	uint16_t fat_flags;
	uint16_t	version;
	uint32_t	cluster_root;
	uint16_t   sector_number_fs;
	uint16_t   boot_sector;
	char 	reserved[12];
	char 	physical_drive_number;
	char 	reserved2;
	char 	assinatura;
	uint32_t	ID;
	char	volume_label[11];
	char	fat_file_system[8];
 	char    lixo[422];
}_fat_nova;

typedef union  xx{
	 _fat_antiga fat_antiga;
	 _fat_nova   fat_nova;	
}Extended_d;

typedef struct _boot {
	unsigned char jmp[2];
	unsigned char nop;
	unsigned char oem[8];
	unsigned char bytes_per_sector[2];
	unsigned char sectors_per_cluster;
	unsigned char reserved_sectors[2];
	unsigned char num_fats;
	uint16_t root_entry;
	unsigned char total_sectors[2];
	unsigned char media;
	unsigned char setores_por_fat[2];
	unsigned char setores_por_trilha[2];
	unsigned char numero_de_faces[2];
	unsigned char Hidden[4];
	uint32_t	total_sectors2;
	Extended_d fat;
}bootsector;


