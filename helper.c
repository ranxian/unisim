#include "helper.h"
#include <stdio.h>

void printdw(int dword)
{
	int i;
	printf("\n");
	for (i = 0; i < 32; i++)
		printf("%2d ", 31 - i);
	printf("\n");
	for (i = 0; i < 32; i++)
	{
		printf("%2d ", (dword >> (31 - i)) & 1);
	}
	printf("\n");
}

void inst_info(inst_t *inst)
{
	switch(inst->type) {
		case D_IMM_SH_INST:
			printf("d_imm_sh_inst\n"); break;
		case D_REG_SH_INST:
			printf("d_reg_sh_inst\n"); break;
		case MUL_INST:
			printf("mul_inst\n"); break;
		case BRX_INST:
			printf("brx_inst\n"); break;
		case D_IMM_INST:
			printf("d_imm_inst\n"); break;
		case LSR_OFF_INST:
			printf("lst_off_inst"); break;
		case LSHWR_OFF_INST:
			printf("lshwr_off_inst\n"); break;
		case LSHWI_OFF_INST:
			printf("lshwi_off_inst\n"); break;
		case LSI_OFF_INST:
			printf("lsi_off_inst\n"); break;
		case ST_INST:
			printf("st_inst\n"); break;
		case BRLK_INST:
			printf("brlk_inst\n"); break;
		case UNKNOWN:
			printf("unknown\n"); break;
		default:
			printf("inst_info panic\n"); break;
	}
}

uint32_t bits(int dword, int start, int end)
{
	int i;
	uint32_t res = 0;
	for (i = start; i <= end; i++) {
		res |= 1 << i;
	}
	return (dword & res) >> start;
}

