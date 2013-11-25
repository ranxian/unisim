#include "syscall.h"
#include "sim.h"
#include "helper.h"
#include <stdlib.h>

int syscall(int callnum, int *res)
{
	printf("0x%x\n", callnum);
	switch (callnum) {
		case SYS_putint:
			printf("SYS_putint: %d\n", R(0));
			break;
		case SYS_exit:
			printf("SYS_exit: retval = %d\n", R(0));
			exit(0);
			break;
		default:
			printf("unimplemented syscall\n");
	}
}