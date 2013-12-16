#include "testheader.h"
int a = 2;
int b[10];
int Do()
{
	a = 1;
	b[1] = 2;
	return 0;
}

int main()
{
	b[0] = 1;
	Do();
	b[0] = 1;
	b[9] = 2;
	sys_putint(b[1]);
}
