#ifndef TESTHEADER_H
#define TESTHEADER_H
#ifndef X86
#include "../stdlib.h"
#include <stdint.h>
#endif

#ifdef X86
#include <stdio.h>
void sys_putint(int i) {
	printf("%d\n", i);
}
int sys_state(int i) {
	// just in accordance with unisim system call sys_state
	return 0;
}
#endif

#ifndef MAXN
#define MAXN 10
#endif

#endif
