#include "sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "shifter.h"
#include "mmu.h"
#include "extender.h"

int simulate(int entry)
{
	int i;

	PC = entry;
	SP = alloc_stack();

	int inst_cnt = 0;
	// printdw(PC);

	for (i = 0; i < 1000; i++) {
		inst_cnt += 1;
		#ifdef DEBUG
		printf("PC: 0x%x\n", PC);
		#endif
		// fetch
		fetch_dword(PC, &ir);
		#ifdef DEBUG
		printf("inst: 0x%x\n", ir);
		#endif
		#ifdef DEBUG
		printdw(ir);
		#endif
		fetch();
		#ifdef DEBUG
		fetch_stat();
		#endif
		clock_tick();
		// decode
		decode();
		#ifdef DEBUG
		decode_stat();
		#endif
		clock_tick();
		// execute
		execute();
		#ifdef DEBUG
		execute_stat();
		#endif
		clock_tick();
		// memory
		memory();
		#ifdef DEBUG
		memory_stat();
		#endif
		clock_tick();
		// write-back
		writeback();
		#ifdef DEBUG
		writeback_stat();
		#endif
		clock_tick();
		// getchar();
	}
	printf("%d inst executed\n", inst_cnt);
	return 0;
}

int fetch()
{
	int ii = ir;
	uint32_t f29_31 = bits(ii, 29, 31);
	uint32_t f25_28 = bits(ii, 25, 28);
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
	f_reg.cond = f25_28;
	PC += 4;

	switch(f29_31) {
		case 0x0:
			if (B(ii, 8) == 0 && B(ii, 5) == 0) {
				f_reg.insttype = D_IMM_SH_INST;
			}
			else if (B(ii, 8) == 0 && B(ii, 5) == 1)
				f_reg.insttype = D_REG_SH_INST;
			if (B(ii, 28) == 0) {
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

	if (f_reg.insttype == ST_INST) {
		syscall(f_reg.imm24);
	}

	return 1;
}

int alu()
{
	uint32_t carry = cmsr.C;
	int tmp_result;
	long long long_res;
	int op1 = E_reg.op1, op2 = E_reg.op2;
	opcode_t opcode = E_reg.opcode;
	switch(opcode) {
		case AND:
			tmp_result = op1 & op2;
			break;
		case XOR:
			tmp_result = op1 ^ op2;
			break;
		case SUB:
			tmp_result = op1 - op2;
			long_res = (unsigned)(op1 - op2);
			break;
		case RSB:
			tmp_result = op2 - op1;
			long_res = (unsigned)(op2 - op1);
			break;
		case ADD:
			tmp_result = op1 + op2;
			long_res = (unsigned)(op1 + op2);
			break;
		case ADC:
			tmp_result = op1 + op2 + carry;
			long_res = (unsigned)(op1 + op2 + carry);
			break;
		case SBC:
			tmp_result = op1 - op2 + carry - 1;
			long_res = (unsigned)(op1 - op2 + carry - 1);
			break;
		case RSC:
			tmp_result = op2 - op1 + carry - 1;
			long_res = (unsigned)(op2 - op1 + carry - 1);
			break;
		case CAND:
			tmp_result = op1 & op2;
			break;
		case CXOR:
			tmp_result = op1 ^ op2;
			break;
		case CSUB:
			tmp_result = op1 - op2;
			long_res = (unsigned)(op1 - op2);
			break;
		case CADD:
			tmp_result = op1 + op2;
			long_res = (unsigned)(op1 + op2);
			break;
		case ORR:
			tmp_result = op1 | op2;
			break;
		case MOV:
			tmp_result = op2;
			break;
		case CLB:
			tmp_result = op1 & (~op2);
			break;
		case MVN:
			tmp_result = ~op2;
			break;
		case MUL:
			tmp_result = op1 * op2;
			break;
		case NOP:
			tmp_result = op2;
			break;
		default:
			printf("unkown opcode, panic!\n");
			exit(0);
	}
	// set cmsr bit

	if (E_reg.insttype == D_IMM_INST || E_reg.insttype == D_IMM_SH_INST
		|| E_reg.insttype == D_REG_SH_INST) {
		if (E_reg.S && E_reg.dstE != 31) {
			if (IS_LOG(opcode)) {
				if (tmp_result == 0)
					cmsr.Z = 1;
				cmsr.N = B(tmp_result, 31);
				cmsr.C = E_reg.C;
			} else {
				if (tmp_result == 0)
					cmsr.Z = 1;
				cmsr.N = B(tmp_result, 31);
				if (B(op1, 31) == 1 && B(op2, 31) == 0 && B(tmp_result, 31) == 0)
					cmsr.V = 1;
				else if (B(op1, 31) == 0 && B(op2, 31) == 1 && B(tmp_result, 31) == 1)
					cmsr.V = 1;
				else
					cmsr.V = 0;
				if (opcode == ADD || opcode == SUB || opcode == RSB || opcode == ADC
						|| opcode == SBC || opcode == RSC || opcode == CSUB || opcode == CADD) {
					if ((long_res & 0xffffffff00000000) != 0)
						cmsr.C = 1;
					else cmsr.C = 0;
				}
			}
		}
	}

	return tmp_result;
}

int condman(cond_t c) {
	switch (c) {
		case EQ:  return cmsr.Z == 1;
		case NE:  return cmsr.Z == 0;
		case UGE: return cmsr.C == 1;
		case ULT: return cmsr.C == 0;
		case N:   return cmsr.N == 1;
		case NN:  return cmsr.N == 0;
		case OV:  return cmsr.V == 1;
		case NV:  return cmsr.V == 0;
		case UGT: return cmsr.C == 1 && cmsr.Z == 0;
		case ULE: return cmsr.C == 0 || cmsr.Z == 1;
		case SGE: return cmsr.N == cmsr.V;
		case SLT: return cmsr.N != cmsr.V;
		case SGT: return cmsr.Z == 0 && (cmsr.N == cmsr.V);
		case SLE: return cmsr.Z == 1 || (cmsr.N != cmsr.V);
		case AL:  return 1;
		default:  return 1;
	}
}

int decode()
{
	switch(D_reg.insttype) {
		case D_IMM_SH_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, R(D_reg.rm), D_reg.shift_imm);
				d_reg.dstE = D_reg.rd;
				break;
			}
		case D_REG_SH_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, R(D_reg.rm), R(D_reg.rs));
				d_reg.dstE = D_reg.rd;
				break;
			}
		case MUL_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = R(D_reg.rm);
				d_reg.dstE = D_reg.rd;
				break;
			}
		case BRX_INST:
			{
				d_reg.op2 = R(D_reg.rm);
				d_reg.dstE = 31;
				break;
			}
		case D_IMM_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(SHIFT_LP, D_reg.imm9, D_reg.rotate);
				d_reg.dstE = D_reg.rd;
				break;
			}
		case LSR_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, R(D_reg.rm), D_reg.shift_imm);
				d_reg.valD = R(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case LSHWR_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = R(D_reg.rm);
				d_reg.valD = R(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case LSHWI_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = (D_reg.hioff << 5) | (D_reg.lowoff);
				d_reg.valD = R(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case LSI_OFF_INST:
			{
				d_reg.op1 = R(D_reg.rn);
				d_reg.op2 = D_reg.imm14;
				d_reg.valD = R(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case ST_INST:
			{
				break;
			}
		case BRLK_INST:
			{
				d_reg.op1 = extend(D_reg.imm24, 24, 1) << 2;
				d_reg.op2 = D_reg.valP;
				d_reg.dstE = 31;
				break;
			}
		case UNKNOWN:
			{
				printf("unknown inst encountered\n");
				return -1;
			}
		default: break;
	}
	d_reg.opcode = D_reg.opcode;
	switch(D_reg.insttype) {
		case MUL_INST:
			d_reg.opcode = MUL;
			break;
		case BRX_INST:
			d_reg.opcode = NOP;
			break;
		case LSR_OFF_INST:
		case LSI_OFF_INST:
		case LSHWR_OFF_INST:
		case LSHWI_OFF_INST:
			{
				if (D_reg.U == 1) d_reg.opcode = ADD;
				else d_reg.opcode = SUB;
				break;
			}
		case BRLK_INST:
			d_reg.opcode = ADD;
			break;
		case ST_INST:
			d_reg.opcode = NOP;
			break;
		default:
			break;
	}
	d_reg.insttype = D_reg.insttype;
	d_reg.valP = D_reg.valP;
	d_reg.cond = D_reg.cond;
	d_reg.S2 = D_reg.S2;
	COPY_SBIT(d_reg, D_reg);
	return 0;
}

int memory()
{
	switch(M_reg.insttype) {
		case LSR_OFF_INST:
		case LSI_OFF_INST:
		{
			int addr;
			addr = M_reg.P ? M_reg.valE : R(M_reg.dstE);
			// printf("0x%x\n", addr);
			if (M_reg.L) {
				if (M_reg.B) {
					fetch_nbyte(addr, &m_reg.valM, 1);
				} else {
					fetch_nbyte(addr, &m_reg.valM, 4);
				}
			} else {
				if (M_reg.B) {
					#ifdef DEBUG
					printf("write 0x%x to 0x%x\n", M_reg.valD & 0xff, addr);
					#endif
					write_byte(addr, M_reg.valD & 0xff);
				} else {
					#ifdef DEBUG
					printf("write 0x%x to 0x%x\n", M_reg.valD, addr);
					#endif
					write_word(addr, M_reg.valD);
				}
			}
			break;
		}
		case LSHWR_OFF_INST:
		case LSHWI_OFF_INST:
		{
			int addr;
			addr = M_reg.P ? M_reg.valE : R(M_reg.dstE);
			if (M_reg.L) {
				if (M_reg.H) {
					fetch_nbyte(addr, &m_reg.valM, 2);
				} else {
					fetch_nbyte(addr, &m_reg.valM, 4);
				}
			} else {
				if (M_reg.H) {
					write_hword(addr, M_reg.valD & 0xffff);
					#ifdef DEBUG
					printf("write 0x%x to 0x%x\n", M_reg.valD & 0xffff, addr);
					#endif
				} else {
					write_word(addr, M_reg.valD);
					#ifdef DEBUG
					printf("write 0x%x to 0x%x\n", M_reg.valD, addr);
					#endif
				}
			}
			break;
		}
		default: break;
	}

	COPY_SBIT(m_reg, M_reg);
	m_reg.dstE = M_reg.dstE;
	m_reg.dstM = M_reg.dstM;
	m_reg.valE = M_reg.valE;
	m_reg.valP = M_reg.valP;
	m_reg.S2   = M_reg.S2;
	m_reg.opcode = M_reg.opcode;
	m_reg.insttype = M_reg.insttype;
	m_reg.condval = M_reg.condval;
}

int writeback()
{
	switch (W_reg.insttype) {
		case D_IMM_SH_INST:
		case D_REG_SH_INST:
		case D_IMM_INST:
			if (!NO_WRITE(W_reg.opcode)) {
				regs[W_reg.dstE] = W_reg.valE;
				#ifdef DEBUG
				printf("register #%d is updated to 0x%x\n", W_reg.dstE, W_reg.valE);
				#endif
			}
			break;
		case MUL_INST:
			regs[W_reg.dstE] = W_reg.valE;
			break;
		case BRX_INST:
			regs[W_reg.dstE] = W_reg.valE;
			if (W_reg.L)
				LR = W_reg.valP & 0xfffffffe;
			break;
		case LSR_OFF_INST:
		case LSI_OFF_INST:
		case LSHWR_OFF_INST:
		case LSHWI_OFF_INST:
			if (W_reg.L)
				regs[W_reg.dstM] = W_reg.valM;
			if (!W_reg.P || W_reg.W)
				regs[W_reg.dstE] = W_reg.valE;
			break;
		case BRLK_INST:
			if (W_reg.condval) {
				regs[W_reg.dstE] = W_reg.valE;
				#ifdef DEBUG
				printf("register #%d is updated to 0x%x\n", W_reg.dstE, W_reg.valE);
				#endif
				if (W_reg.L) LR = W_reg.valP;
			}
			break;
		case ST_INST:
			break;
		default:
			printf("writeback panic\n");
			break;
	}
	return 0;
}

int execute()
{
	inst_type_t t = E_reg.insttype;
	opcode_t opcode = E_reg.opcode;
	if (!(opcode == CADD || opcode == CAND || opcode == CSUB || opcode == CXOR)) {
		e_reg.valE = alu();
	} else alu();

	if (E_reg.insttype == BRLK_INST) {
		e_reg.condval = condman(E_reg.cond);
	}

	e_reg.valP = E_reg.valP;
	e_reg.insttype = E_reg.insttype;
	e_reg.dstE = E_reg.dstE;
	e_reg.dstM = E_reg.dstM;
	e_reg.valD = E_reg.valD;
	e_reg.opcode = E_reg.opcode;
	COPY_SBIT(e_reg, E_reg);
}

int clock_tick()
{
	D_reg = f_reg;
	E_reg = d_reg;
	M_reg = e_reg;
	W_reg = m_reg;
}
