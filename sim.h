#ifndef SIM_H
#define SIM_H
#include "loader.h"
#include <stdint.h>
#pragma pack(1)

typedef enum { D_IMM_SH_INST, D_REG_SH_INST, MUL_INST, BRX_INST, SDT_INST, ST_INST,
			   BRLK_INST, LSI_OFFSET_INST, LSHWI_OFFSET_INST } inst_type_t;
typedef struct {
	int rm:5;
	int b5:1;
	int shift:2;
	int b8:1;
	int shift_imm:5;
	int rd:5;
	int rn:5;
	int S:1;
	int opcode:4;
	int b29:1;
	int b30:1;
	int b31:1;
} d_imm_sh_inst_t;

typedef struct {
	int rm:5;
	int b5:1;
	int shift:2;
	int b8:1;
	int rs:5;
	int rd:5;
	int rn:5;
	int S:1;
	int opcode:4;
	int b29:1;
	int b30:1;
	int b31:1;
} d_reg_sh_inst_t;

typedef struct {
	int rm:5;
	int b5:1;
	int b6:1;
	int b7:1;
	int b8:1;
	int rs:5;
	int rd:5;
	int rn:5;
	int S:1;
	int A:1;
	int b26:1;
	int b27:1;
	int b28:1;
	int b29:1;
	int b30:1;
	int b31:1;
} mul_inst_t;

typedef struct {
	int rm:5;
	int bleft1:19;
	int L:1;
	int bleft2:7;
} brx_inst_t;

typedef struct {
	int imm:9;
	int rotate:5;
	int rd:5;
	int rn:5;
	int S:1;
	int opcode:4;
	int b29:1;
	int b30:1;
	int b31:1;
} d_imm_inst_t;

typedef struct {
	int rm:5;
	int b5:1;
	int shift:2;
	int b8:1;
	int shift_imm:5;
	int rd:5;
	int rn:5;
	int L:1;
	int W:1;
	int B:1;
	int U:1;
	int P:1;
	int b29:1;
	int b30:1;
	int b31:1;
} lsr_offset_inst_t;

typedef struct {
	int rm:5;
	int b5:1;
	int H:1;
	int S:1;
	int b8:1;
	int shift_imm:5;
	int rd:5;
	int rn:5;
	int L:1;
	int W:1;
	int B:1;
	int U:1;
	int P:1;
	int b29:1;
	int b30:1;
	int b31:1;
} lshwr_offset_inst_t;

typedef struct {
	int loffset:5;
	int b5:1;
	int H:1;
	int S:1;
	int b8:1;
	int hoffset:5;
	int rd:5;
	int rn:5;
	int L:1;
	int W:1;
	int B:1;
	int U:1;
	int P:1;
	int b29:1;
	int b30:1;
	int b31:1;
} lshwi_offset_inst_t;

typedef struct {
	int himm:14;
	int rd:5;
	int rn:5;
	int L:1;
	int W:1;
	int I:1;
	int U:1;
	int P:1;
	int b29:1;
	int b30:1;
	int b31:1;
} lsi_offset_inst_t;

typedef struct {
	int offset:24;
	int L:1;
	int cond:4;
	int b29:1;
	int b30:1;
	int b31:1;
} brlk_inst_t;

typedef struct {
	int offset:24;
	int bleft:8;
} st_inst_t;

typedef struct {
	int N:1;
	int Z:1;
	int C:1;
	int V:1;
	int unused:20;
	int I:1;
	int F:1;
	int T:1;
	int mode:5;
} stat_reg_t;

typedef struct {
	inst_type_t inst_type;
} inst_t;

#define REG_NUM 33

extern int pc;
extern int regs[REG_NUM];

int simulate(int entry);

int fetch(inst_t *inst);

int decode(inst_t *inst);

int execute(inst_t *inst);

int memory(inst_t *inst);

int writeback(inst_t *inst);
#endif
