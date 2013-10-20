#include "sim.h"
#include <stdio.h>

int main()
{
	printf("d_imm_sh_inst_t: %d\n", sizeof(d_imm_sh_inst_t));
	printf("d_reg_sh_inst_t: %d\n", sizeof(d_reg_sh_inst_t));
	printf("mul_inst_t: %d\n", sizeof(mul_inst_t));
	printf("brx_inst_t: %d\n", sizeof(brx_inst_t));
	printf("d_imm_inst_t: %d\n", sizeof(d_imm_inst_t));
	printf("lsr_offt_inst_t: %d\n", sizeof(lsr_off_inst_t));
	printf("lshwi_off_inst_t: %d\n", sizeof(lshwi_off_inst_t));
	printf("lshwr_off_inst_t: %d\n", sizeof(lshwr_off_inst_t));
	printf("lsi_off_inst_t: %d\n", sizeof(lsi_off_inst_t));
	printf("brlk_inst_t: %d\n", sizeof(brlk_inst_t));
	printf("st_inst_t: %d\n", sizeof(st_inst_t));
	inst_t inst;
}
