#ifndef SIM_H
#define SIM_H
#include "loader.h"
#include "cache.h"
#include <stdint.h>

typedef enum { D_IMM_SH_INST, D_REG_SH_INST, D_IMM_INST, MUL_INST, BRX_INST,
	           LSR_OFF_INST, LSHWR_OFF_INST, LSHWI_OFF_INST,
			   LSI_OFF_INST, ST_INST, BRLK_INST, UNKNOWN, INOP } inst_type_t;

typedef enum { AND, XOR, SUB, RSB, ADD, ADC, SBC, RSC, CAND, CXOR, CSUB,
			   CADD, ORR, MOV, CLB, MVN, MUL, NOP, NONE } opcode_t;

typedef enum { SHIFT_LL, SHIFT_LR, SHIFT_AR, SHIFT_LP } shifttype_t;

typedef enum { EQ, NE, UGE, ULT, N, NN, OV, NV, UGT, ULE, SGE, SLT, SGT,
			   SLE, AL } cond_t;

#define MEMINST(inst) (inst == LSR_OFF_INST || inst == LSHWR_OFF_INST 	\
						|| inst == LSHWI_OFF_INST || inst == LSI_OFF_INST)

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
	int 		bubble;
} d_reg_t;

typedef struct {
	inst_type_t insttype;
	opcode_t 	opcode;
	int dstE;
	int dstM;
	int valD;
	int op1;
	int op2;
	int op3;
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
	int bubble;
} e_reg_t;

typedef struct {
	inst_type_t insttype;
	int dstE;
	int dstM;
	int dstP;
	int valD;
	int valE;
	int WM; 	// 是否写内存 (用 valD)
	int WER;	// 是否用 valE 写寄存器
	int WMR;	// 是否用 valM 写寄存器
	int WLR;	// 是否写 LR (用 valP)
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
	int dstP;
	int valM;
	int valE;
	int WM; 	// 是否写内存 (用 valD)
	int WER;	// 是否用 valE 写寄存器
	int WMR;	// 是否用 valM 写寄存器
	int WLR;	// 是否写 LR (用 valP)
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
extern cache_t icache;
extern cache_t dcache;
extern int ncycle;
extern int halted;
extern int inst_cnt;
extern int nforward;
extern int nstall;
extern int nbubble;
extern int misspred;
extern int F_stall, D_stall, D_bubble, E_bubble;
extern int icnt[13];

int simulate(int entry);

int fetch();

int decode();

int execute();

int memory();

int writeback();

int clock_tick();

int condman(cond_t c);

int gen_pipe_consig();

int fwdR(int n);

#endif
