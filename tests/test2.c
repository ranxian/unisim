#include "testheader.h"

int max(int a, int b) {
	if (a > b)
		return a;
	else return b;
}

int max3(int a, int b, int c) {
	return max(max(a, b), c);
}

int min(int a, int b) {
	if (a > b)
		return b;
	else return a;
}

int min3(int a, int b, int c) {
	return min(min(a, b), c);
}

int main()
{
	sys_putint(max(1, 2));
	sys_putint(max(10, 20));
	sys_putint(max(3, 2));
	sys_putint(max(4, 7));
	sys_putint(max(10, 8));
	sys_putint(max(3, 3));
	sys_putint(max3(1, 2, 3));
	sys_putint(max3(4, 8, 10));
	sys_putint(max3(192, 3, 2));
	sys_putint(max3(12, 1, 12));
	sys_putint(max3(12, 12, 13));

	sys_putint(min(1, 2));
	sys_putint(min(10, 20));
	sys_putint(min(3, 2));
	sys_putint(min(4, 7));
	sys_putint(min(10, 8));
	sys_putint(min(3, 3));
	sys_putint(min3(1, 2, 3));
	sys_putint(min3(4, 8, 10));
	sys_putint(min3(192, 3, 2));
	sys_putint(min3(12, 1, 12));
	sys_putint(min3(12, 12, 13));
}
