#ifndef SIM_H
#define SIM_H
#include "loader.h"
#include <stdint.h>

/* program state register */
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
typedef enum { DP_INST, MUL_INST, BRX_INST, SDT_INST, HDT_INST, COND_INST,
			   SOFTI_INST } inst_type_t;

/* data process inst type */
typedef struct {
	union {
		int imm:9;
		struct {
			int rm:5;
			int b5:1;
			int shift:2;
			int b8:1;
		} shift_reg_left;
	} shift_left;
	union {
		int imm:5;
		int rs:5;
		int rotate:5;
	} shift_right;
	int rd:5;
	int S:1;
	int opcode:4;
	int b29:1;		// 0
	int b30:1;		// 0
	int b31:1;		// 0 | 1
} dp_inst_t;

/* multiply inst type */
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
	int b29:1; 		// 0
	int b30:1;	 	// 0
	int b31:1; 		// 0
} mul_inst_t;

/* branch inst type */
typedef struct {
	int rm:5;
	int bleft:27; 	// 0 0 0
} brx_inst_t;

/* single data transfer inst type */
typedef struct {
	union {
		struct {
			int rm:5;
			int b5:1;
			int shift:2;
			int b8:1;
		} reg_shift;
		int imm_shift:9;
	} shift;
	int rd:5;
	int rn:5;
	int L:1;
	int W:1;
	int B:1;
	int U:1;
	int P:1;
	int b29:1;		// 0
	int b30:1;		// 1
	int b31:1; 		// 1 | 0
} sdt_inst_t;

/* half word transfer inst type */
typedef struct {
	union {
		int low_offset:5;
		int rm:5;
	} loffset;
	int b5:1;
	int H:1;
	int S:1;
	int b8:1;
	int roffset:5;
	int rd:5;
	int rn:5;
	int L:1;
	int W:1;
	int b26:1;
	int U:1;
	int P:1;
	int b29:1;		// 0
	int b30:1;		// 1
	int b31:1;		// 0
} hdt_inst_t;

/* condition inst type */
typedef struct {
	int offset:24;
	int L:1;
	int cond:4;
	int b29:1; 		// 1
	int b30:1; 		// 0
	int b31:1; 		// 1
} cond_inst_t;

typedef struct {
	int st_num:24;
	int bleft:8; 	// 11111111
} softi_inst_t;

typedef struct {
	inst_type_t inst_type;
	union {
		dp_inst_t dp_inst;
		mul_inst_t mul_inst;
		brx_inst_t brx_inst;
		sdt_inst_t sdt_inst;
		hdt_inst_t hdt_inst;
		cond_inst_t cond_inst;
		softi_inst_t softi_inst;
	} inst;
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
