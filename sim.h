#ifndef SIM_H
#define SIM_H
#include "loader.h"
#include <stdint.h>

typedef enum { D_IMM_SH_INST, D_REG_SH_INST, D_IMM_INST, MUL_INST, BRX_INST,
	           LSR_OFF_INST, LSHWR_OFF_INST, LSHWI_OFF_INST,
			   LSI_OFF_INST, ST_INST, BRLK_INST, UNKNOWN } inst_type_t;

typedef enum { AND, XOR, SUB, RSB, ADD, ADC, SBC, RSC, CAND, CXOR, CSUB,
			   CADD, ORR, MOV, CLB, MVN, MUL, NOP, NONE } opcode_t;

typedef enum { SHIFT_LL, SHIFT_LR, SHIFT_AR, SHIFT_LP } shifttype_t;

typedef enum { EQ, NE, UGE, ULT, N, NN, OV, NV, UGT, ULE, SGE, SLT, SGT,
			   SLE, AL } cond_t;

typedef struct {
	uint32_t N:1;
	uint32_t Z:1;
	uint32_t C:1;
	uint32_t V:1;
	uint32_t unused:20;
	uint32_t I:1;
	uint32_t F:1;
	uint32_t T:1;
	uint32_t mode:5;
} stat_reg_t;

typedef struct {
	inst_type_t insttype;
	opcode_t 	opcode;
	int 		rn;
	int 		rd;
	int 		rm;
	int 		rs;
	int 		shift_imm;
	shifttype_t	shifttype;
	int 		rotate;
	int 		cond;
	int 		imm9;
	int 		hioff;
	int 		lowoff;
	int 		imm14;
	int 		imm24;
	int 		S;
	int 		S2;
	int 		P;
	int 		U;
	int 		B;
	int 		W;
	int 		A;
	int 		L;
	int 		H;
	int 		valP;
} d_reg_t;

typedef struct {
	inst_type_t insttype;
	opcode_t 	opcode;
	int dstE;
	int dstM;
	int valD;
	int op1;
	int op2;
	int S;
	int S2;
	int P;
	int U;
	int B;
	int W;
	int L;
	int H;
	int C;
	int valP;
	int cond;
} e_reg_t;

typedef struct {
	inst_type_t insttype;
	int dstE;
	int dstM;
	int valD;
	int valE;
	int S;
	int S2;
	int P;
	int U;
	int B;
	int W;
	int L;
	int H;
	int valP;
	int condval;
	opcode_t opcode;
} m_reg_t;

typedef struct {
	inst_type_t insttype;
	opcode_t opcode;
	int dstE;
	int dstM;
	int valM;
	int valE;
	int S;
	int S2;
	int P;
	int U;
	int B;
	int W;
	int L;
	int H;
	int valP;
	int condval;
} w_reg_t;

#define REG_NUM 33

extern int regs[REG_NUM];
extern int ir;
extern stat_reg_t cmsr;
extern stat_reg_t temp_cmsr;
extern d_reg_t f_reg, D_reg;
extern e_reg_t d_reg, E_reg;
extern m_reg_t e_reg, M_reg;
extern w_reg_t m_reg, W_reg;

int simulate(int entry);

int fetch();

int decode();

int execute();

int memory();

int writeback();

int clock_tick();

int condman(cond_t c);
#endif
