#include "testheader.h"

int fab(int n) {
	if (n == 1 || n == 0)
		return 1;
	else return fab(n-2) + fab(n-1);
}

int main()
{
	fab(35);
}
