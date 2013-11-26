#include "stdlib.h"

int array[] = {1, 2, 3, 12, 2, 3, 5, 6, 8, 6};

int solve()
{
	int i = 0;
	int cnt = 0;
	// int cnt2 = 0;
	for (i = 0; i < 10; i ++) {
		if (array[i] > 6) {
			cnt += 1;
		} 
		// if (array[i] <= 3) {
		// 	cnt2 += 1;
		// }
	}
	sys_putint(cnt);
	// sys_putint(cnt2);
	return 0;
}

int main()
{
	solve();
}