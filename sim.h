#ifndef SIM_H
#define SIM_H
#include "loader.h"
#include <stdint.h>

typedef enum { D_IMM_SH_INST, D_REG_SH_INST, D_IMM_INST, MUL_INST, BRX_INST,
	           LSR_OFF_INST, LSHWR_OFF_INST, LSHWI_OFF_INST,
			   LSI_OFF_INST, ST_INST, BRLK_INST, UNKNOWN } inst_type_t;
typedef enum { AND, XOR, SUB, RSB, ADD, ADC, SBC, RSC, CAND, CXOR, CSUB,
			   CADD, ORR, MOV, CLB, MVN, NOP } opcode_t;
typedef enum { SHIFT_LL, SHIFT_LR, SHIFT_AR, SHIFT_LP } shifttype_t;
typedef struct {
	uint32_t rm:5;
	uint32_t b5:1;
	uint32_t shifttype:2;
	uint32_t b8:1;
	uint32_t imm:5;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t S:1;
	uint32_t opcode:4;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} d_imm_sh_inst_t;

typedef struct {
	uint32_t rm:5;
	uint32_t b5:1;
	uint32_t shifttype:2;
	uint32_t b8:1;
	uint32_t rs:5;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t S:1;
	uint32_t opcode:4;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} d_reg_sh_inst_t;

typedef struct {
	uint32_t rm:5;
	uint32_t b5:1;
	uint32_t b6:1;
	uint32_t b7:1;
	uint32_t b8:1;
	uint32_t rs:5;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t S:1;
	uint32_t A:1;
	uint32_t b26:1;
	uint32_t b27:1;
	uint32_t b28:1;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} mul_inst_t;

typedef struct {
	uint32_t rm:5;
	uint32_t bleft1:19;
	uint32_t L:1;
	uint32_t bleft2:7;
} brx_inst_t;

typedef struct {
	uint32_t imm:9;
	uint32_t rotate:5;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t S:1;
	uint32_t opcode:4;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} d_imm_inst_t;

typedef struct {
	uint32_t rm:5;
	uint32_t b5:1;
	uint32_t shifttype:2;
	uint32_t b8:1;
	uint32_t imm:5;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t L:1;
	uint32_t W:1;
	uint32_t B:1;
	uint32_t U:1;
	uint32_t P:1;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} lsr_off_inst_t;

typedef struct {
	uint32_t rm:5;
	uint32_t b5:1;
	uint32_t H:1;
	uint32_t S:1;
	uint32_t b8:1;
	uint32_t shift_imm:5;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t L:1;
	uint32_t W:1;
	uint32_t B:1;
	uint32_t U:1;
	uint32_t P:1;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} lshwr_off_inst_t;

typedef struct {
	uint32_t loffset:5;
	uint32_t b5:1;
	uint32_t H:1;
	uint32_t S:1;
	uint32_t b8:1;
	uint32_t hoffset:5;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t L:1;
	uint32_t W:1;
	uint32_t B:1;
	uint32_t U:1;
	uint32_t P:1;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} lshwi_off_inst_t;

typedef struct {
	uint32_t himm:14;
	uint32_t rd:5;
	uint32_t rn:5;
	uint32_t L:1;
	uint32_t W:1;
	uint32_t I:1;
	uint32_t U:1;
	uint32_t P:1;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} lsi_off_inst_t;

typedef struct {
	uint32_t offset:24;
	uint32_t L:1;
	uint32_t cond:4;
	uint32_t b29:1;
	uint32_t b30:1;
	uint32_t b31:1;
} brlk_inst_t;

typedef struct {
	uint32_t offset:24;
	uint32_t bleft:8;
} st_inst_t;

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
	inst_type_t type;
	int i;
} inst_t;

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
	int opcode;
	int rn;
	int rd;
	int rs;
	int op1;
	int op2;
	int op3;
	int S;
	int P;
	int U;
	int B;
	int W;
	int L;
	int H;
	int valP;
	int cond;
} e_reg_t;

#define REG_NUM 33

extern int regs[REG_NUM];
extern int ir;
extern stat_reg_t cmsr;
extern stat_reg_t temp_cmsr;
extern d_reg_t f_reg, D_reg;
extern e_reg_t d_reg, E_reg;

int simulate(int entry);

int fetch();

int decode();

int execute();

int memory();

int writeback();

int clock_tick();
#endif
