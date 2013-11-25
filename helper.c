#include "helper.h"
#include "sim.h"
#include <stdio.h>

void print_regs()
{
	int i;
	for (i = 0; i < 32; i++) {
		if (i % 5 == 0) {
			printf("\n");
		}
		if (i == 31) {
			printf("PC=0x%x\t", regs[i]);
		} else if (i == 29) {
			printf("SP=0x%x\t", regs[i]);
		} else if (i == 28) {
			printf("IP=0x%x\t", regs[i]);
		} else {
			printf("REG[%2d]=0x%x\t", i, regs[i]);
		}
	}
	printf("\n");
}
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
	printf("opcode:\t\t%s\n", OPCODE_NAME(f_reg.opcode));
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
	printf("cond:\t\t%s\n", COND_NAME(f_reg.cond));
	print_regs();
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
	printf("DECODE STAGE:\n");
	print_inst_name(d_reg.insttype);
	printf("opcode:\t\t%s\n", OPCODE_NAME(d_reg.opcode));
	printf("dstE:\t\t%d\n", d_reg.dstE);
	printf("dstM:\t\t%d\n", d_reg.dstM);
	printf("valD:\t\t%d\n", d_reg.valD);
	printf("op1:\t\t0x%x\n", d_reg.op1);
	printf("op2:\t\t0x%x\n", d_reg.op2);
	printf("C:\t\t%d\n", d_reg.C);
	printf("S:\t\t%d\n", d_reg.S);
	printf("S2:\t\t%d\n", d_reg.S2);
	printf("P:\t\t%d\n", d_reg.P);
	printf("U:\t\t%d\n", d_reg.U);
	printf("B:\t\t%d\n", d_reg.B);
	printf("W:\t\t%d\n", d_reg.W);
	printf("L:\t\t%d\n", d_reg.L);
	printf("H:\t\t%d\n", d_reg.H);
	printf("valP:\t\t0x%x\n", d_reg.valP);
	print_cmsr(&cmsr);
	printf("cond:\t\t%s\n", COND_NAME(d_reg.cond));
	print_regs();
	printf("-------------------------------------------\n");
}
void execute_stat()
{
	printf("EXECUTE STAGE:\n");
	printf("insttype:\t%s\n", INST_NAME(e_reg.insttype));
	printf("opcode:\t\t%s\n", OPCODE_NAME(e_reg.opcode));
	printf("dstE:\t\t%d\n", e_reg.dstE);
	printf("dstM:\t\t%d\n", e_reg.dstM);
	printf("valD:\t\t%d\n", e_reg.valD);
	printf("valE:\t\t0x%x\n", e_reg.valE);
	printf("S:\t\t%d\n", e_reg.S);
	printf("S2:\t\t%d\n", e_reg.S2);
	printf("P:\t\t%d\n", e_reg.P);
	printf("U:\t\t%d\n", e_reg.U);
	printf("B:\t\t%d\n", e_reg.B);
	printf("W:\t\t%d\n", e_reg.W);
	printf("L:\t\t%d\n", e_reg.L);
	printf("H:\t\t%d\n", e_reg.H);
	printf("valP:\t\t0x%x\n", e_reg.valP);
	print_cmsr(&cmsr);
	printf("condval:\t%d\n", e_reg.condval);
	print_regs();
	printf("-------------------------------------------\n");
}
void memory_stat()
{
	printf("MEMORY STAGE:\n");
	printf("insttype:\t%s\n", INST_NAME(m_reg.insttype));
	printf("opcode:\t\t%s\n", OPCODE_NAME(m_reg.opcode));
	printf("dstE:\t\t%d\n", m_reg.dstE);
	printf("dstM:\t\t%d\n", m_reg.dstM);
	printf("valM:\t\t0x%x\n", m_reg.valM);
	printf("valE:\t\t0x%x\n", m_reg.valE);
	printf("S:\t\t%d\n", m_reg.S);
	printf("S2:\t\t%d\n", m_reg.S2);
	printf("P:\t\t%d\n", m_reg.P);
	printf("U:\t\t%d\n", m_reg.U);
	printf("B:\t\t%d\n", m_reg.B);
	printf("W:\t\t%d\n", m_reg.W);
	printf("L:\t\t%d\n", m_reg.L);
	printf("H:\t\t%d\n", m_reg.H);
	printf("valP:\t\t0x%x\n", m_reg.valP);
	printf("condval:\t%d\n", m_reg.condval);
	print_regs();
	printf("-------------------------------------------\n");
}
void writeback_stat()
{
	printf("WRITEBACK STAGE:\n");
	print_regs();
	printf("-------------------------------------------\n");
}

char *INST_NAME(inst_type_t i)
{
	static char *names[] =
	{
		"D_IMM_SH_INST", "D_REG_SH_INST", "D_IMM_INST", "MUL_INST", "BRX_INST",
	           "LSR_OFF_INST", "LSHWR_OFF_INST", "LSHWI_OFF_INST",
			   "LSI_OFF_INST", "ST_INST", "BRLK_INST", "UNKNOWN"
	};
	return names[i];
}

char *OPCODE_NAME(opcode_t o)
{
	static char *names[] =
	{
		"AND", "XOR", "SUB", "RSB", "ADD", "ADC", "SBC", "RSC", "CAND", "CXOR", "CSUB","CADD", "ORR", "MOV", "CLB", "MVN", "MUL", "NOP", "NONE"
	};
	return names[o];
}

char *SHIFT_TYPE_NAME(shifttype_t s)
{
	static char *names[] =
	{
		"SHIFT_LL", "SHIFT_LR", "SHIFT_AR", "SHIFT_LP"
	};
	return names[s];
}

char *COND_NAME(cond_t c) {
	static char *names[] = 
	{
		"EQ", "NE", "UGE", "ULT", "N", "NN", "OV", "NV", "UGT", "ULE", "SGE", "SLT", "SGT",
		"SLE", "AL"
	};
	return names[c];
}
