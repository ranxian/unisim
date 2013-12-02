#include "sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "shifter.h"
#include "mmu.h"
#include "extender.h"

int ncycle = 0;
int simulate(int entry)
{
	int i;

	PC = entry;
	SP = alloc_stack();

	int inst_cnt = 0;
	D_reg.insttype = E_reg.insttype = M_reg.insttype = W_reg.insttype = INOP;
	for (i = 0; ; i++) {
		inst_cnt += 1;
		gen_pipe_consig();

		writeback();
		
		memory();
		
		execute();
		
		decode();
		
		if (!F_stall)
			fetch();
		
		clock_tick();
		#ifdef DEBUG
		getchar();
		#endif
	}
	printf("%d inst executed\n", inst_cnt);
	return 0;
}

int fetch()
{
	// Should have jump
	if (E_reg.insttype == BRLK_INST && e_reg.condval) {
		PC = e_reg.valE;
		printf("PC forward from e_reg.valE with value 0x%x\n", e_reg.valE);
	}
		
	fetch_dword(PC, &ir);
	#ifdef DEBUG
		printf("FETCH STAGE:\n");
		printf("PC:\t\t0x%x\n", PC);
		printf("inst:\t\t0x%x\n", ir);
		printdw(ir);
		printf("-------------------------------------------\n");
	#endif
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
		regs[0] = syscall(f_reg.imm24);
	}

	return 1;
}

int alu()
{
	uint32_t carry = cmsr.C;
	int tmp_result;
	int op1 = E_reg.op1, op2 = E_reg.op2, op3 = E_reg.op3;
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
			break;
		case RSB:
			tmp_result = op2 - op1;
			break;
		case ADD:
			tmp_result = op1 + op2;
			break;
		case ADC:
			tmp_result = op1 + op2 + carry;
			break;
		case SBC:
			tmp_result = op1 - op2 + carry - 1;
			break;
		case RSC:
			tmp_result = op2 - op1 + carry - 1;
			break;
		case CAND:
			tmp_result = op1 & op2;
			break;
		case CXOR:
			tmp_result = op1 ^ op2;
			break;
		case CSUB:
			tmp_result = op1 - op2;
			break;
		case CADD:
			tmp_result = op1 + op2;
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
			printf("mul: %d*%d\n", op1, op2);
			tmp_result = op1 * op2 + op3;
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
			if (opcode == MVN || opcode == MOV) {
				int c = condman(E_reg.cond);
				if (!c) goto end;
			}
			cmsr.Z = tmp_result == 0;
			cmsr.N = B(tmp_result, 31);
			switch (opcode){
		        case SUB:
		        case SBC:
		        case CSUB:
		        {
	                cmsr.V = ((((op1^op2)>>31) != 0) && (((tmp_result^op2)>>31) == 0));
	                // unsigned t = tmp_result;
	                // t -= (opcode == SBC)? cmsr.C: 1;
	                cmsr.C = (op1 >= op2);
	                // cmsr.C = (t < op1 || t < (~op2));
	                break;
	            }
		        case RSB:
		        case RSC:
		        {
	                cmsr.V = ((((op1^op2)>>31) != 0) && (((tmp_result^op1)>>31) == 0));
	                // unsigned t = tmp_result;
	                // t -= (opcode == RSC)? cmsr.C: 1;
	                // cmsr.C = (t < (~op1) || t < op2)
	                cmsr.C = (op1 < op2);
	                break;
	            }
		        case ADD:
		        case ADC:
		        case CADD:
		        {
	                cmsr.V = ((((op1^op2)>>31) == 0) && (((tmp_result^op1)>>31) != 0));
	                unsigned t = tmp_result;
	                if (opcode == ADC) t -= cmsr.C;
	                cmsr.C = (t < op1 || t < op2);
	                break;
	            }
		        default:
	                cmsr.C = E_reg.C;
	                break;
	        }
		}
	}

	if (E_reg.insttype == MUL_INST && E_reg.S) {
		cmsr.N = B(tmp_result, 31);
		cmsr.Z = (tmp_result == 0);
	}

	end:
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
	#ifdef DEBUG
	decode_stat();
	#endif
	if (D_bubble) {
		d_reg.insttype = INOP;
		return 0;
	}

	

	if (D_reg.insttype == INOP) {
		d_reg.insttype = INOP;
		return 0;
	}

	d_reg.insttype = D_reg.insttype;
	d_reg.valP = D_reg.valP;
	d_reg.cond = D_reg.cond;
	d_reg.S2 = D_reg.S2;
	COPY_SBIT(d_reg, D_reg);
	switch(D_reg.insttype) {
		case D_IMM_SH_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, fwdR(D_reg.rm), D_reg.shift_imm);
				d_reg.dstE = D_reg.rd;
				d_reg.dstM = -1;
				break;
			}
		case D_REG_SH_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, fwdR(D_reg.rm), fwdR(D_reg.rs));
				d_reg.dstE = D_reg.rd;
				d_reg.dstM = -1;
				break;
			}
		case MUL_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = fwdR(D_reg.rm);
				d_reg.op3 = D_reg.rs ? fwdR(D_reg.rs) : 0;
				d_reg.dstE = D_reg.rd;
				d_reg.dstM = -1;
				break;
			}
		case BRX_INST:
			{
				d_reg.op2 = R(D_reg.rm);
				d_reg.dstE = 31;
				d_reg.dstM = -1;
				break;
			}
		case D_IMM_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = shifter(SHIFT_LP, D_reg.imm9, D_reg.rotate);
				d_reg.dstE = D_reg.rd;
				d_reg.dstM = -1;
				break;
			}
		case LSR_OFF_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = shifter(D_reg.shifttype, fwdR(D_reg.rm), D_reg.shift_imm);
				d_reg.valD = fwdR(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case LSHWR_OFF_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = fwdR(D_reg.rm);
				d_reg.valD = fwdR(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case LSHWI_OFF_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = (D_reg.hioff << 5) | (D_reg.lowoff);
				d_reg.valD = fwdR(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case LSI_OFF_INST:
			{
				d_reg.op1 = fwdR(D_reg.rn);
				d_reg.op2 = D_reg.imm14;
				d_reg.valD = fwdR(D_reg.rd);
				d_reg.dstE = D_reg.rn;
				d_reg.dstM = D_reg.rd;
				break;
			}
		case ST_INST:
			{
				d_reg.dstE = -1;
				d_reg.dstM = -1;
				break;
			}
		case BRLK_INST:
			{
				d_reg.op1 = extend(D_reg.imm24, 24, 1) << 2;
				d_reg.op2 = D_reg.valP;
				d_reg.dstE = 31;
				d_reg.dstM = -1;
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
			d_reg.opcode = INOP;
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
			d_reg.opcode = INOP;
			break;
		default:
			break;
	}
	if (D_reg.insttype == D_IMM_INST || D_reg.insttype == D_IMM_SH_INST
		|| D_reg.insttype == D_REG_SH_INST) {
		d_reg.cond = (D_reg.rn & 0x10) ? (D_reg.rn & 0xf) : AL;
	}

	return 0;
}

int memory()
{
	#ifdef DEBUG
	memory_stat();
	#endif
	if (M_reg.insttype == INOP) {
		m_reg.insttype = INOP;
		return 0;
	}

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
	#ifdef DEBUG
	writeback_stat();
	#endif
	if (W_reg.insttype == INOP)
		return 0;
	switch (W_reg.insttype) {
		case D_IMM_SH_INST:
		case D_REG_SH_INST:
		case D_IMM_INST:
			if (!NO_WRITE(W_reg.opcode)) {
				if (W_reg.dstE == 31) break; 
				if (W_reg.opcode == MVN || W_reg.opcode == MOV) {
					if (W_reg.condval) {
						regs[W_reg.dstE] = W_reg.valE;	
					}	
				} else {
					regs[W_reg.dstE] = W_reg.valE;
				}
				
				// #ifdef DEBUG
				printf("register #%d is updated to 0x%x\n", W_reg.dstE, W_reg.valE);
				// #endif
			}
			break;
		case MUL_INST:
			if (W_reg.dstE == 31) break; 
			printf("register #%d is updated to 0x%x\n", W_reg.dstE, W_reg.valE);
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
				if (W_reg.dstE == 31) break; 
				print_cmsr();
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
	#ifdef DEBUG
	execute_stat();
	#endif
	if (E_bubble) {
		e_reg.insttype = INOP;
		return 0;
	}
	
	if (E_reg.insttype == INOP) {
		e_reg.insttype = INOP;
		return;
	}
	e_reg.valE = alu();

	if (E_reg.insttype == BRLK_INST || E_reg.insttype == D_IMM_SH_INST ||
		E_reg.insttype == D_IMM_INST || E_reg.insttype == D_REG_SH_INST) {
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
	printf("cycle %d\n", ncycle);
	ncycle += 1;
	
	D_reg = f_reg;
	E_reg = d_reg;
	M_reg = e_reg;
	W_reg = m_reg;
	return 0;
}

static inline LUtrigger()
{
	return (MEMINST(E_reg.insttype) && E_reg.L
		&& (E_reg.dstM == D_reg.rn || E_reg.dstM == D_reg.rd
			|| E_reg.dstM == D_reg.rm || E_reg.dstM == D_reg.rs));
}

int gen_pipe_consig()
{
	// Fetch stage stall or bubble
	if (LUtrigger()) {
		F_stall = 1;
	} else F_stall = 0;

	// Decode stage stall or bubble
	if (LUtrigger()) {
		D_stall = 1;
	} else D_stall = 0;

	if (// Conditional jump
		E_reg.insttype == BRLK_INST && e_reg.condval && !D_stall) {
		D_bubble = 1;
	} else D_bubble = 0;

	// Execute stage stall or bubble
	if (// Conditional jump and LU
		(E_reg.insttype == BRLK_INST && e_reg.condval) || LUtrigger()) {
		E_bubble = 1;
	} else E_bubble = 0;

	if (F_stall) {
		printf("Fetch stall\n");
	}
	if (D_stall) {
		printf("Decode stall\n");
	}
	if (D_bubble) {
		printf("Decode bubble\n");
	}
	if (E_bubble) {
		printf("Execute bubble\n");
	}

	return 0;
}

int fwdR(int n)
{
	if (n == 31)
		return R(n);
	if (n == E_reg.dstE) {
		printf("regs[%d] forwarded from e_reg.valE with value 0x%x\n", n, e_reg.valE);
		return e_reg.valE;
	}
	if (n == M_reg.dstM) {
		printf("regs[%d] forwarded from e_reg.valE with value 0x%x\n", n, m_reg.valM);
		return m_reg.valM;
	}
	if (n == M_reg.dstE) {
		printf("regs[%d] forwarded from e_reg.valE with value 0x%x\n", n, M_reg.valE);
		return M_reg.valE;
	}
	if (n == W_reg.dstM) {
		printf("regs[%d] forwarded from e_reg.valE with value 0x%x\n", n, W_reg.valM);
		return W_reg.valM;
	}
	if (n == W_reg.dstE) {
		printf("regs[%d] forwarded from e_reg.valE with value 0x%x\n", n, W_reg.valE);
		return W_reg.valE;
	}
	return R(n);

}