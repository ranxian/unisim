#include "testheader.h"

int main()
{
	int array[8] = {3, 1, 2, 3, 9, 12, 32, 43};

	int i = 0;
	int tmp = array[0];
	for (i = 0; i < 7; i++)
		array[i] = array[i+1];
	array[7] = tmp;

	for (i = 0; i < 8; i++)
		sys_putint(array[i]);
}