#include "sim.h"
#include <stdio.h>

int main()
{
	inst_t inst;
	printf("inst_t:\t%d\n", sizeof(inst.inst));
	printf("dp_inst_t:\t%d\n", sizeof(dp_inst_t));
	printf("sdt_inst_t:\t%d\n", sizeof(sdt_inst_t));
	printf("mul_inst_t:\t%d\n", sizeof(mul_inst_t));
	printf("hdt_inst_t:\t%d\n", sizeof(hdt_inst_t));
	printf("brx_inst_t:\t%d\n", sizeof(brx_inst_t));
	printf("softi_inst_t:\t%d\n", sizeof(softi_inst_t));
}
