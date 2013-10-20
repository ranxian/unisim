#include "sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#define UP(n, b) (((n) >> (b-1)) & 1)
#define B(n, b) (((n) >> (b)) & 1)
#define R(no) ((no) == 31 ? regs[no] + 4 : regs[no])
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

void fetch_dword(int addr, int *dest)
{
	int i;
	char *src;
	for (i = 0; i < segment_cnt; i++) {
		if (segments[i].offset <= addr && segments[i].offset + segments[i].size >= addr - 4) {
			src = segments[i].content + addr - segments[i].offset;
		}
	}
	memcpy(dest, src, sizeof(int));
}

int simulate(int entry)
{
	int i;

	pc = entry;
	printdw(pc);

	for (i = 0; i < 10; i++) {
		// fetch
		fetch_dword(pc, &ir.i);
		// decode
		decode(&ir);
		inst_info(&ir);
		// execute
		execute(&ir);
		// memory
		memory(&ir);
		// write-back
		writeback(&ir);
		printf("inst: ");
		printdw(ir.i);
	}
	return 0;
}

int decode(inst_t *inst)
{
	int ii = inst->i;
	uint32_t f29_31 = bits(ii, 29, 31);
	uint32_t f26_28 = bits(ii, 26, 28);
	uint32_t f19_23 = bits(ii, 19, 23);
	uint32_t f14_18 = bits(ii, 14, 18);
	uint32_t f5_8 = bits(ii, 5, 8);
	uint32_t f9_13 = bits(ii, 9, 13);

	switch(f29_31) {
		case 0x0:
			if (B(ii, 8) == 0 && B(ii, 5) == 0)
				inst->type = D_IMM_SH_INST;
			else if (B(ii, 8) == 0 && B(ii, 5) == 1)
				inst->type = D_REG_SH_INST;
			if (f26_28 == 0) {
				if (f5_8 == 0x9)
					inst->type = MUL_INST;
			} else if (f26_28 == 0x4) {
				if (B(ii, 25) == 0 && f19_23 == 0x1f &&
						f14_18 == 0x1f	&& f9_13 == 0 && f5_8 == 0x9)
					inst->type = BRX_INST;
			}
			break;
		case 0x1:
			inst->type = D_IMM_INST;
			break;
		case 0x2:
			if (B(ii, 5) == 0 && B(ii, 8) == 0)
				inst->type = LSR_OFF_INST;
			else if (B(ii, 26) == 0 && f9_13 == 0 && B(ii, 5) == 1 && B(ii, 8) == 1)
				inst->type = LSHWR_OFF_INST;
			else if (B(ii, 26) == 1 && B(ii, 5) == 1 && B(ii, 8) == 1)
				inst->type = LSHWI_OFF_INST;
			break;
		case 0x3:
			inst->type = LSI_OFF_INST;
			break;
		case 0x5:
			inst->type = BRLK_INST;
			break;
		case 0x7:
			if (bits(ii, 24, 28) == 0x1f)
				inst->type = ST_INST;
			break;
		default:
			inst->type = UNKNOWN;
	}
}

int dp_inst_remain(opcode_t opcode, int *dst_reg, int oper1, int oper2, int setcc)
{
	uint32_t carry = cmsr.C;
	switch(opcode) {
		case AND:
			*dst_reg = oper1 & oper2;
			break;
		case XOR:
			*dst_reg = oper1 ^ oper2;
			break;
		case SUB:
			*dst_reg = oper1 - oper2;
			break;
		case RSB:
			*dst_reg = oper2 - oper1;
			break;
		case ADD:
			*dst_reg = oper1 + oper2;
			break;
		case ADC:
			*dst_reg = oper1 + oper2 + carry;
			break;
		case SBC:
			*dst_reg = oper1 - oper2 + carry - 1;
			break;
		case RSC:
			*dst_reg = oper2 - oper1 + carry - 1;
			break;
		case CAND:
			// oper1 & oper2
			break;
		case CXOR:
			// oper1 ^ oper2
			break;
		case CSUB:
			// oper1 - oper2
			break;
		case CADD:
			// oper1 + oper2
			break;
		case ORR:
			*dst_reg = oper1 | oper2;
			break;
		case MOV:
			*dst_reg = oper2;
			break;
		case CLB:
			*dst_reg = oper1 & (~oper2);
			break;
		case MVN:
			*dst_reg = ~oper2;
			break;
		default:
			printf("unkown opcode, panic!\n");
			exit(0);
	}
}

int shifted(shifttype_t shifttype, int n1, int n2)
{
	switch(shifttype) {
		case SHIFT_LL:
			return n1 << n2;
		case SHIFT_LR:
			return ((unsigned)n1) >> n2;
		case SHIFT_AR:
			return n1 >> n2;
		case SHIFT_LP:
			return (((unsigned)n1) >> n2) | (n1 << (32-n2));
		default:
			printf("unknown shift type!\n");
			exit(0);
	}
}

int execute(inst_t *inst)
{
	int ii = inst->i;
	int oper1, oper2;
	int pc_changed = 0;

	switch(inst->type) {
		case D_IMM_SH_INST:
			{
				d_imm_sh_inst_t ninst = *(d_imm_sh_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifted(ninst.shifttype, R(ninst.rm), ninst.imm);

				dp_inst_remain(ninst.opcode, &regs[ninst.rd],  oper1, oper2, ninst.S);
				break;
			}
		case D_REG_SH_INST:
			{
				d_reg_sh_inst_t ninst = *(d_reg_sh_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifted(ninst.shifttype, R(ninst.rm), R(ninst.rs));

				dp_inst_remain(ninst.opcode, &regs[ninst.rd], oper1, oper2, ninst.S);
				break;
			}
		case MUL_INST:
			{
				mul_inst_t ninst = *(mul_inst_t *)&ii;
				regs[ninst.rd] = R(ninst.rn) * R(ninst.rm) + R(ninst.rs);
				break;
			}
		case BRX_INST:
			{
				brx_inst_t ninst = *(brx_inst_t *)&ii;
				break;
			}
		case D_IMM_INST:
			{
				d_imm_inst_t ninst = *(d_imm_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifted(SHIFT_LP, ninst.imm, ninst.rotate);

				dp_inst_remain(ninst.opcode, &regs[ninst.rd], oper1, oper2, ninst.S);
				break;
			}
		case LSR_OFF_INST:
			{
				lsr_off_inst_t ninst = *(lsr_off_inst_t *)&ii;
				if (ninst.L == 1) {
					lr = pc + 4;
					pc = R(ninst.rm);
					pc_changed = 1;
				}
				break;
			}
		case LSHWR_OFF_INST:
			{
				lshwr_off_inst_t ninst = *(lshwr_off_inst_t *)&ii;
				break;
			}
		case LSHWI_OFF_INST:
			{
				lshwi_off_inst_t ninst = *(lshwi_off_inst_t *)&ii;
				break;
			}
		case LSI_OFF_INST:
			{
				lsi_off_inst_t ninst = *(lsi_off_inst_t *)&ii;
				break;
			}
		case ST_INST:
			{
				st_inst_t ninst = *(st_inst_t *)&ii;
				break;
			}
		case BRLK_INST:
			{
				brlk_inst_t ninst = *(brlk_inst_t *)&ii;
				break;
			}
		case UNKNOWN:
			{
				printf("unknown inst encountered");
				return -1;
			}
		default: break;
	}
	if (!pc_changed) pc += 4;
	return 0;
}

int memory(inst_t *inst)
{
	return 0;
}

int writeback(inst_t *inst)
{
	return 0;
}

