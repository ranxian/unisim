#include "helper.h"
#include <stdio.h>

void printdw(int dword)
{
	int i;
	printf("\n");
	for (i = 0; i < 32; i++)
		printf("%2d ", 31 - i);
	printf("\n");
	for (i = 0; i < 32; i++)
	{
		printf("%2d ", (dword >> (31 - i)) & 1);
	}
	printf("\n");
}
