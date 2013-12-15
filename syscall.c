#include "syscall.h"
#include "sim.h"
#include "helper.h"
#include <stdlib.h>
#include <stdint.h>

int syscall(int callnum)
{
	switch (callnum) {
		case SYS_putint:
			printf("SYS_putint: %d\n", R(0));
			break;
		case SYS_exit:
			printf("SYS_exit: retval = %d\n", R(0));
			halted = 1;
			// exit(0);
			break;
		case SYS_udiv:
			return (uint32_t)R(0) / (uint32_t)R(1);
		case SYS_div:
			return (int)R(0) / (int)R(1);
		case SYS_mod:
            return (int)R(0) % (int)R(1);
        case SYS_umod:
            return (uint32_t)R(0) % (uint32_t)R(1);
        case SYS_state:
        	printf("inst: %d, cycle: %d\n", inst_cnt, ncycle);
        	return 0;
		default:
			printf("unimplemented syscall\n");
			return -1;
	}
	return 0;
}
