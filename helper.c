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

void print_cmsr()
{
	printf("CMSR:\t\tN=%d  Z=%d  C=%d  V=%d\n", cmsr.N, cmsr.Z, cmsr.C, cmsr.V);
}


void decode_stat()
{
	printf("DECODE STAGE:\n");
	printf("insttype:\t%s\n", INST_NAME(D_reg.insttype));
	printf("opcode:\t\t%s\n", OPCODE_NAME(D_reg.opcode));
	printf("Rn:\t\t%d\n", D_reg.rn);
	printf("Rd:\t\t%d\n", D_reg.rd);
	printf("Rm:\t\t%d\n", D_reg.rm);
	printf("Rs:\t\t%d\n", D_reg.rs);
	printf("rotate:\t\t%d\n", D_reg.rotate);
	printf("cond:\t\t0x%x\n", D_reg.cond);
	printf("imm9:\t\t0x%x\n", D_reg.imm9);
	printf("hioff:\t\t0x%x\n", D_reg.hioff);
	printf("lowoff:\t\t0x%x\n", D_reg.lowoff);
	printf("imm14:\t\t0x%x\n", D_reg.imm14);
	printf("imm24:\t\t0x%x\n", D_reg.imm24);
	printf("S:\t\t%d\n", D_reg.S);
	printf("P:\t\t%d\n", D_reg.P);
	printf("U:\t\t%d\n", D_reg.U);
	printf("B:\t\t%d\n", D_reg.B);
	printf("W:\t\t%d\n", D_reg.W);
	printf("L:\t\t%d\n", D_reg.L);
	printf("H:\t\t%d\n", D_reg.H);
	printf("valP:\t\t0x%x\n", D_reg.valP);
	print_cmsr();
	printf("cond:\t\t%s\n", COND_NAME(D_reg.cond));
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

void execute_stat()
{
	printf("EXECUTE STAGE:\n");
	printf("insttype:\t%s\n", INST_NAME(E_reg.insttype));
	printf("opcode:\t\t%s\n", OPCODE_NAME(E_reg.opcode));
	printf("dstE:\t\t%d\n", E_reg.dstE);
	printf("dstM:\t\t%d\n", E_reg.dstM);
	printf("valD:\t\t0x%x\n", E_reg.valD);
	printf("op1:\t\t0x%x\n", E_reg.op1);
	printf("op2:\t\t0x%x\n", E_reg.op2);
	printf("C:\t\t%d\n", E_reg.C);
	printf("S:\t\t%d\n", E_reg.S);
	printf("S2:\t\t%d\n", E_reg.S2);
	printf("P:\t\t%d\n", E_reg.P);
	printf("U:\t\t%d\n", E_reg.U);
	printf("B:\t\t%d\n", E_reg.B);
	printf("W:\t\t%d\n", E_reg.W);
	printf("L:\t\t%d\n", E_reg.L);
	printf("H:\t\t%d\n", E_reg.H);
	printf("valP:\t\t0x%x\n", E_reg.valP);
	print_cmsr();
	printf("cond:\t\t%s\n", COND_NAME(E_reg.cond));
	print_regs();
	printf("-------------------------------------------\n");
}
void memory_stat()
{
	printf("MEMORY STAGE:\n");
	printf("insttype:\t%s\n", INST_NAME(M_reg.insttype));
	printf("opcode:\t\t%s\n", OPCODE_NAME(M_reg.opcode));
	printf("dstE:\t\t%d\n", M_reg.dstE);
	printf("dstM:\t\t%d\n", M_reg.dstM);
	printf("valD:\t\t0x%x\n", M_reg.valD);
	printf("valE:\t\t0x%x\n", M_reg.valE);
	printf("S:\t\t%d\n", M_reg.S);
	printf("S2:\t\t%d\n", M_reg.S2);
	printf("P:\t\t%d\n", M_reg.P);
	printf("U:\t\t%d\n", M_reg.U);
	printf("B:\t\t%d\n", M_reg.B);
	printf("W:\t\t%d\n", M_reg.W);
	printf("L:\t\t%d\n", M_reg.L);
	printf("H:\t\t%d\n", M_reg.H);
	printf("valP:\t\t0x%x\n", M_reg.valP);
	print_cmsr();
	printf("condval:\t%d\n", M_reg.condval);
	print_regs();
	printf("-------------------------------------------\n");
}
void writeback_stat()
{
	printf("WRITEBACK STAGE:\n");
	printf("insttype:\t%s\n", INST_NAME(W_reg.insttype));
	printf("opcode:\t\t%s\n", OPCODE_NAME(W_reg.opcode));
	printf("dstE:\t\t%d\n", W_reg.dstE);
	printf("dstM:\t\t%d\n", W_reg.dstM);
	printf("valM:\t\t0x%x\n", W_reg.valM);
	printf("valE:\t\t0x%x\n", W_reg.valE);
	printf("S:\t\t%d\n", W_reg.S);
	printf("S2:\t\t%d\n", W_reg.S2);
	printf("P:\t\t%d\n", W_reg.P);
	printf("U:\t\t%d\n", W_reg.U);
	printf("B:\t\t%d\n", W_reg.B);
	printf("W:\t\t%d\n", W_reg.W);
	printf("L:\t\t%d\n", W_reg.L);
	printf("H:\t\t%d\n", W_reg.H);
	printf("valP:\t\t0x%x\n", W_reg.valP);
	printf("condval:\t%d\n", W_reg.condval);
	print_regs();
	printf("-------------------------------------------\n");
}
void end_stat()
{
	printf("INSTEND:\n");
	print_regs();
	printf("-------------------------------------------\n");
}

char *INST_NAME(inst_type_t i)
{
	static char *names[] =
	{
		"D_IMM_SH_INST", "D_REG_SH_INST", "D_IMM_INST", "MUL_INST", "BRX_INST",
	           "LSR_OFF_INST", "LSHWR_OFF_INST", "LSHWI_OFF_INST",
			   "LSI_OFF_INST", "ST_INST", "BRLK_INST", "UNKNOWN", "INOP"
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
