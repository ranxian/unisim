#include "testheader.h"

int main()
{
	int array[] = {3, 1, 2, 3, 9, 12, 32, 43 };
	int num = array[0];
	int i = 0;
	while (num != 12) {
		i++;
		num = array[i];
	}
	sys_putint(i);
}