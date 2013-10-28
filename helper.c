#include "helper.h"
#include <stdio.h>

void printdw(int dword)
{
	int i;
	for (i = 0; i < 32; i++)
		printf("%2d ", 31 - i);
	printf("\n");
	for (i = 0; i < 32; i++)
	{
		printf("%2d ", (dword >> (31 - i)) & 1);
	}
	printf("\n");
}

void print_cmsr(stat_reg_t *r)
{
	printf("CMSR:\t\tN=%d  Z=%d  C=%d  V=%d\n", r->N, r->Z, r->C, r->V);
}

void print_inst_name(inst_type_t type)
{
	printf("insttype:\t");
	switch(type) {
		case D_IMM_SH_INST:
			printf("d_imm_sh_inst\n");
			break;
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
			printf("lsi_off_inst\n");
			break;
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

void fetch_stat()
{
	printf("FETCH STAGE:\n");
	print_inst_name(f_reg.insttype);
	printf("opcode:\t\t0x%x\n", f_reg.opcode);
	printf("Rn:\t\t%d\n", f_reg.rn);
	printf("Rd:\t\t%d\n", f_reg.rd);
	printf("Rm:\t\t%d\n", f_reg.rm);
	printf("Rs:\t\t%d\n", f_reg.rs);
	printf("rotate:\t\t%d\n", f_reg.rotate);
	printf("cond:\t\t0x%x\n", f_reg.cond);
	printf("imm9:\t\t0x%x\n", f_reg.imm9);
	printf("hioff:\t\t0x%x\n", f_reg.hioff);
	printf("lowoff:\t\t0x%x\n", f_reg.lowoff);
	printf("imm14:\t\t0x%x\n", f_reg.imm14);
	printf("imm24:\t\t0x%x\n", f_reg.imm24);
	printf("S:\t\t%d\n", f_reg.S);
	printf("P:\t\t%d\n", f_reg.P);
	printf("U:\t\t%d\n", f_reg.U);
	printf("B:\t\t%d\n", f_reg.B);
	printf("W:\t\t%d\n", f_reg.W);
	printf("L:\t\t%d\n", f_reg.L);
	printf("H:\t\t%d\n", f_reg.H);
	printf("valP:\t\t0x%x\n", f_reg.valP);
	print_cmsr(&cmsr);

	printf("-------------------------------------------\n");
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

void decode_stat()
{
	print_inst_name(d_reg.insttype);
	printf("opcode:\t\t0x%x\n", f_reg.opcode);
	printf("Rn:\t\t%d\n", d_reg.rn);
	printf("Rd:\t\t%d\n", d_reg.rd);
	printf("Rs:\t\t%d\n", d_reg.rs);
	printf("op1:\t\t0x%x\n", d_reg.op1);
	printf("op2:\t\t0x%x\n", d_reg.op2);
	printf("op3:\t\t0x%x\n", d_reg.op3);
	printf("S:\t\t%d\n", d_reg.S);
	printf("P:\t\t%d\n", d_reg.P);
	printf("U:\t\t%d\n", d_reg.U);
	printf("B:\t\t%d\n", d_reg.B);
	printf("W:\t\t%d\n", f_reg.W);
	printf("L:\t\t%d\n", f_reg.L);
	printf("H:\t\t%d\n", f_reg.H);
	printf("cond:\t\t%x\n", d_reg.cond);
	printf("valP:\t\t0x%x\n", d_reg.valP);
	print_cmsr(&cmsr);
}
void execute_stat() {}
void memory_stat() {}
void writeback_stat() {}

