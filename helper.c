#include "helper.h"
#include <stdio.h>

void printdw(int dword)
{
	int i;
	for (i = 0; i < 32; i++)
	{
		printf("%d", (dword >> (31 - i)) & 1);
	}
	printf("\n");
}

