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
	printdw(PC);

	for (i = 0; i < 10; i++) {
		// fetch
		fetch_dword(PC, &ir);
		printf("inst: ");
		printdw(ir);
		fetch();
		inst_info();
		// decode
		decode();
		// execute
		execute();
		// memory
		memory();
		// write-back
		writeback();
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

	d_reg.opcode = f25_28;
	d_reg.rn = f19_23;
	d_reg.rd = f14_18;
	d_reg.shift_imm = f9_13;
	d_reg.shifttype = bits(ii, 6, 7);
	d_reg.rm = bits(ii, 0, 4);
	d_reg.rotate = f9_13;
	d_reg.imm9 = bits(ii, 0, 8);
	d_reg.hioff = f9_13;
	d_reg.lowoff = bits(ii, 0, 4);
	d_reg.imm14 = bits(ii, 0, 13);
	d_reg.cond = f25_28;
	d_reg.imm24 = bits(ii, 0, 23);

	switch(f29_31) {
		case 0x0:
			if (B(ii, 8) == 0 && B(ii, 5) == 0) {
				d_reg.insttype = D_IMM_SH_INST;
			}
			else if (B(ii, 8) == 0 && B(ii, 5) == 1)
				d_reg.insttype = D_REG_SH_INST;
			if (B(ii, 28)) {
				if (f5_8 == 0x9)
					d_reg.insttype = MUL_INST;
			} else if (B(ii, 28) == 1) {
				if (B(ii, 25) == 0 && f19_23 == 0x1f &&
						f14_18 == 0x1f	&& f9_13 == 0 && f5_8 == 0x9)
					d_reg.insttype = BRX_INST;
			}
			break;
		case 0x1:
			d_reg.insttype = D_IMM_INST;
			break;
		case 0x2:
			if (B(ii, 5) == 0 && B(ii, 8) == 0)
				d_reg.insttype = LSR_OFF_INST;
			else if (B(ii, 26) == 0 && f9_13 == 0 && B(ii, 5) == 1 && B(ii, 8) == 1)
				d_reg.insttype = LSHWR_OFF_INST;
			else if (B(ii, 26) == 1 && B(ii, 5) == 1 && B(ii, 8) == 1)
				d_reg.insttype = LSHWI_OFF_INST;
			break;
		case 0x3:
			d_reg.insttype = LSI_OFF_INST;
			break;
		case 0x5:
			d_reg.insttype = BRLK_INST;
			break;
		case 0x7:
			if (bits(ii, 24, 28) == 0x1f)
				d_reg.insttype = ST_INST;
			break;
		default:
			d_reg.insttype = UNKNOWN;
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

int execute(inst_t *inst)
{/*
	int ii = inst->i;
	int oper1, oper2;
	int old_pc = PC;
	int shift_setC = 0;

	switch(inst->type) {
		case D_IMM_SH_INST:
			{
				d_imm_sh_inst_t ninst = *(d_imm_sh_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifter(ninst.shifttype, R(ninst.rm), ninst.imm);

				dp_inst_remain(ninst.opcode, ninst.rd,  oper1, oper2, ninst.S);
				break;
			}
		case D_REG_SH_INST:
			{
				d_reg_sh_inst_t ninst = *(d_reg_sh_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifter(ninst.shifttype, R(ninst.rm), R(ninst.rs));

				dp_inst_remain(ninst.opcode, ninst.rd, oper1, oper2, ninst.S);
				break;
			}
		case MUL_INST:
			{
				mul_inst_t ninst = *(mul_inst_t *)&ii;
				int tmp = R(ninst.rn) * R(ninst.rm) + R(ninst.rs);
				if (tmp == 0)
					cmsr.Z = 1;
				cmsr.N = B(tmp, 31);
				regs[ninst.rd] = tmp;
				break;
			}
		case BRX_INST:
			{
				brx_inst_t ninst = *(brx_inst_t *)&ii;
				if (ninst.L)
					LR = R(31);
				PC = R(ninst.rm);
				regs[30] &= 0xfffffffc;
				break;
			}
		case D_IMM_INST:
			{
				d_imm_inst_t ninst = *(d_imm_inst_t *)&ii;
				oper1 = R(ninst.rn);
				oper2 = shifter(SHIFT_LP, ninst.imm, ninst.rotate);

				dp_inst_remain(ninst.opcode, ninst.rd, oper1, oper2, ninst.S);
				break;
			}
		case LSR_OFF_INST:
			{
				lsr_off_inst_t ninst = *(lsr_off_inst_t *)&ii;
				int offset = shifter(ninst.shifttype, R(ninst.rm), R(ninst.imm));
				ls_inst_remain(ii, offset);
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
				int offset = ninst.himm;
				ls_inst_remain(ii, offset);
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
	if (PC == old_pc) PC += 4;

	return 0;*/
}

int memory(inst_t *inst)
{
	return 0;
}

int writeback(inst_t *inst)
{
	return 0;
}

int decode()
{}
