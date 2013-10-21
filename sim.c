#include "sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#define UP(n, b) (((n) >> (b-1)) & 1)
#define B(n, b) (((n) >> (b)) & 1)
#define R(no) ((no) == 31 ? regs[no] + 4 : regs[no])
#define IS_LOG(opcode) (opcode == AND || opcode == XOR || opcode == CAND || opcode == CXOR \
		|| opcode == ORR || opcode == MOV || opcode == CLB || opcode == MVN)

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

int dp_inst_remain(opcode_t opcode, int rd, int oper1, int oper2, int setcc)
{
	uint32_t carry = cmsr.C;
	int tmp_result;
	int V = 0, C = 0;
	long long long_res;
	switch(opcode) {
		case AND:
			tmp_result = oper1 & oper2;
			break;
		case XOR:
			tmp_result = oper1 ^ oper2;
			break;
		case SUB:
			tmp_result = oper1 - oper2;
			long_res = (unsigned)(oper1 - oper2);
			break;
		case RSB:
			tmp_result = oper2 - oper1;
			long_res = (unsigned)(oper2 - oper1);
			break;
		case ADD:
			tmp_result = oper1 + oper2;
			long_res = (unsigned)(oper1 + oper2);
			break;
		case ADC:
			tmp_result = oper1 + oper2 + carry;
			long_res = (unsigned)(oper1 + oper2 + carry);
			break;
		case SBC:
			tmp_result = oper1 - oper2 + carry - 1;
			long_res = (unsigned)(oper1 - oper2 + carry - 1);
			break;
		case RSC:
			tmp_result = oper2 - oper1 + carry - 1;
			long_res = (unsigned)(oper2 - oper1 + carry - 1);
			break;
		case CAND:
			tmp_result = oper1 & oper2;
			break;
		case CXOR:
			tmp_result = oper1 ^ oper2;
			break;
		case CSUB:
			tmp_result = oper1 - oper2;
			long_res = (unsigned)(oper1 - oper2);
			break;
		case CADD:
			tmp_result = oper1 + oper2;
			long_res = (unsigned)(oper1 + oper2);
			break;
		case ORR:
			tmp_result = oper1 | oper2;
			break;
		case MOV:
			tmp_result = oper2;
			break;
		case CLB:
			tmp_result = oper1 & (~oper2);
			break;
		case MVN:
			tmp_result = ~oper2;
			break;
		default:
			printf("unkown opcode, panic!\n");
			exit(0);
	}
	if (!(opcode == CAND || opcode == CXOR || opcode == CADD || opcode == CSUB))
		regs[rd] = tmp_result;
	// set cmsr bit
	if (setcc && rd != 31) {
		if (IS_LOG(opcode)) {
			if (tmp_result == 0)
				cmsr.Z = 1;
			cmsr.N = B(tmp_result, 31);
		} else {
			if (tmp_result == 0)
				cmsr.Z = 1;
			cmsr.N = B(tmp_result, 31);
			if (B(oper1, 31) == 1 && B(oper2, 31) == 0 && B(tmp_result, 31) == 0)
				cmsr.V = 1;
			else if (B(oper1, 31) == 0 && B(oper2, 31) == 1 && B(tmp_result, 31) == 1)
				cmsr.V = 1;
			else
				cmsr.V = 0;
			if (opcode == ADD || opcode == SUB || opcode == RSB || opcode == ADC
					|| opcode == SBC || opcode == RSC || opcode == CSUB || opcode == CADD) {
				if (long_res & 0xffffffff00000000 != 0)
					cmsr.C = 1;
				else cmsr.C = 0;
			}
		}
	}
}

int shifted(shifttype_t shifttype, int n1, int n2, int setC)
{
	int res, C = 0;

	switch(shifttype) {
		case SHIFT_LL:
			res = n1 << n2;
			if (n2) C = B(n1, 32 - n2);
			break;
		case SHIFT_LR:
			res = ((unsigned)n1) >> n2;
			if (n2) C = B(n1, n2-1);
			break;
		case SHIFT_AR:
			res = n1 >> n2;
			if (n2) C = B(n1, n2-1);
			break;
		case SHIFT_LP:
			return (((unsigned)n1) >> n2) | (n1 << (32-n2));
		default:
			printf("unknown shift type!\n");
			exit(0);
	}

	if (setC)
		cmsr.C = C;
	return res;
}

int execute(inst_t *inst)
{
	int ii = inst->i;
	int oper1, oper2;
	int pc_changed = 0;
	int shift_setC = 0;

	switch(inst->type) {
		case D_IMM_SH_INST:
			{
				d_imm_sh_inst_t ninst = *(d_imm_sh_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifted(ninst.shifttype, R(ninst.rm), ninst.imm, IS_LOG(ninst.opcode) && ninst.S);

				dp_inst_remain(ninst.opcode, ninst.rd,  oper1, oper2, ninst.S);
				break;
			}
		case D_REG_SH_INST:
			{
				d_reg_sh_inst_t ninst = *(d_reg_sh_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifted(ninst.shifttype, R(ninst.rm), R(ninst.rs), IS_LOG(ninst.opcode) && ninst.S);

				dp_inst_remain(ninst.opcode, ninst.rd, oper1, oper2, ninst.S);
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
				oper2 = shifted(SHIFT_LP, ninst.imm, ninst.rotate, IS_LOG(ninst.opcode) && ninst.S);

				dp_inst_remain(ninst.opcode, ninst.rd, oper1, oper2, ninst.S);
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

