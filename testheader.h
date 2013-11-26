#ifndef TESTHEADER_H
#define TESTHEADER_H
#ifndef X86
#include "stdlib.h"
#include <stdint.h>
#endif

#ifdef X86
#include <stdio.h>
void sys_putint(int i) {
	printf("%d\n", i);
}
#endif
#endif
