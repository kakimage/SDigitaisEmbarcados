#include <stdio.h>

#pragma pack(1)
typedef struct {
	char c;
	int y;
}TipoX;

TipoX A[10];

int main (void)
{
	printf("tamanho do inteiro %ld\n",sizeof(int));
	printf("tamanho = %ld\n",sizeof(A));

	return 0;
}
