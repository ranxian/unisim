#include "testheader.h"

int fab(int n) {
	if (n == 1 || n == 0)
		return 1;
	else return fab(n-2) + fab(n-1);
}

int main()
{
	// sys_putint(fab(1));
	sys_putint(fab(2));
	sys_putint(fab(3));
	sys_putint(fab(4));
	sys_putint(fab(5));
	sys_putint(fab(6));
	sys_putint(fab(7));
	sys_putint(fab(8));
	sys_putint(fab(20));

}