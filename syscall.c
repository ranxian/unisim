#include "syscall.h"
#include "sim.h"
#include "helper.h"
#include <stdlib.h>
#include <stdint.h>

int syscall(int callnum)
{
	switch (callnum) {
		case SYS_putint:
			printf("%d\n", R(0));
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
        	#ifdef BENCH
        	printf("%d %d %d %d %d %d %d %d\n", inst_cnt, ncycle, nstall, nbubble, nforward, misspred, dcache.nmiss, dcache.nhit);
        	#endif
        	return 0;
		default:
			printf("unimplemented syscall\n");
			return -1;
	}
	return 0;
}
