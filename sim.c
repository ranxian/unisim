#include "sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "shifter.h"

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

	PC = entry;
	// printdw(PC);

	for (i = 0; i < 10; i++) {
		// fetch
		fetch_dword(PC, &ir);
		printdw(ir);
		fetch();
		fetch_stat();
		clock_tick();
		// decode
		decode();
		decode_stat();
		clock_tick();
		// execute
		execute();
		execute_stat();
		clock_tick();
		// memory
		memory();
		memory_stat();
		clock_tick();
		// write-back
		writeback();
		writeback_stat();
		clock_tick();
		PC += 4;
		break; // break for debug
	}
	return 0;
}

int fetch()
{
	int ii = ir;
	uint32_t f29_31 = bits(ii, 29, 31);
	uint32_t f25_28 = bits(ii, 26, 28);
	uint32_t f19_23 = bits(ii, 19, 23);
	uint32_t f14_18 = bits(ii, 14, 18);
	uint32_t f5_8 = bits(ii, 5, 8);
	uint32_t f9_13 = bits(ii, 9, 13);

	f_reg.opcode = f25_28;
	f_reg.rn = f19_23;
	f_reg.rd = f14_18;
	f_reg.shift_imm = f9_13;
	f_reg.shifttype = bits(ii, 6, 7);
	f_reg.rm = bits(ii, 0, 4);
	f_reg.rotate = f9_13;
	f_reg.imm9 = bits(ii, 0, 8);
	f_reg.hioff = f9_13;
	f_reg.lowoff = bits(ii, 0, 4);
	f_reg.imm14 = bits(ii, 0, 13);
	f_reg.cond = f25_28;
	f_reg.imm24 = bits(ii, 0, 23);
	f_reg.S = B(ii, 24);
	f_reg.L = B(ii, 24);
	f_reg.A = B(ii, 25);
	f_reg.B = B(ii, 26);
	f_reg.U = B(ii, 27);
	f_reg.P = B(ii, 28);
	f_reg.S2 = B(ii, 7);
	f_reg.H = B(ii, 6);
	f_reg.valP = PC + 4;

	switch(f29_31) {
		case 0x0:
			if (B(ii, 8) == 0 && B(ii, 5) == 0) {
				f_reg.insttype = D_IMM_SH_INST;
			}
			else if (B(ii, 8) == 0 && B(ii, 5) == 1)
				f_reg.insttype = D_REG_SH_INST;
			if (B(ii, 28)) {
				if (f5_8 == 0x9)
					f_reg.insttype = MUL_INST;
			} else if (B(ii, 28) == 1) {
				if (B(ii, 25) == 0 && f19_23 == 0x1f &&
						f14_18 == 0x1f	&& f9_13 == 0 && f5_8 == 0x9)
					f_reg.insttype = BRX_INST;
			}
			break;
		case 0x1:
			f_reg.insttype = D_IMM_INST;
			break;
		case 0x2:
			if (B(ii, 5) == 0 && B(ii, 8) == 0)
				f_reg.insttype = LSR_OFF_INST;
			else if (B(ii, 26) == 0 && f9_13 == 0 && B(ii, 5) == 1 && B(ii, 8) == 1)
				f_reg.insttype = LSHWR_OFF_INST;
			else if (B(ii, 26) == 1 && B(ii, 5) == 1 && B(ii, 8) == 1)
				f_reg.insttype = LSHWI_OFF_INST;
			break;
		case 0x3:
			f_reg.insttype = LSI_OFF_INST;
			break;
		case 0x5:
			f_reg.insttype = BRLK_INST;
			break;
		case 0x7:
			if (bits(ii, 24, 28) == 0x1f)
				f_reg.insttype = ST_INST;
			break;
		default:
			f_reg.insttype = UNKNOWN;
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

int ls_inst_remain(int inst, int offset)
{
	// hack the inst to be like a lsi_off_inst_t, because except the offset the rest are the same
	lsi_off_inst_t ninst = *(lsi_off_inst_t *)&inst;
	int addr = R(ninst.rn);
	int baseoff = addr;
	if (ninst.U) {
		baseoff += offset;
	} else {
		baseoff -= offset;
	}
	if (ninst.P) {
		addr = baseoff;
	}
}

int decode()
{
	switch(D_reg.insttype) {
		case D_IMM_SH_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, R(D_reg.rm), D_reg.shift_imm);
				break;
			}
		case D_REG_SH_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, R(D_reg.rm), R(D_reg.rs));
				break;
			}
		case MUL_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = R(D_reg.rm);
				d_reg.op3 = R(D_reg.rs);
				break;
			}
		case BRX_INST:
			{
				d_reg.op2 = R(D_reg.rm);
				break;
			}
		case D_IMM_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(SHIFT_LP, D_reg.imm9, D_reg.rotate);
				break;
			}
		case LSR_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, R(D_reg.rm), D_reg.shift_imm);
				break;
			}
		case LSHWR_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = R(D_reg.rm);
				break;
			}
		case LSHWI_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = (D_reg.hioff << 5) | (D_reg.lowoff);
				break;
			}
		case LSI_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, R(D_reg.rm), D_reg.shift_imm);
				break;
			}
		case ST_INST:
			{
				break;
			}
		case BRLK_INST:
			{
				d_reg.op1 = D_reg.imm24 << 2;
				d_reg.op2 = D_reg.valP;
				break;
			}
		case UNKNOWN:
			{
				printf("unknown inst encountered");
				return -1;
			}
		default: break;
	}
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

int execute()
{}

int clock_tick()
{
	D_reg = f_reg;
	E_reg = d_reg;
}
