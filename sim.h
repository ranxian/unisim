#ifndef SIM_H
#define SIM_H
#include "loader.h"
#include <stdint.h>

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
typedef enum { DP_INST, MUL_INST, SDT_INST } inst_type_t;

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
	int b29:1;
	int b30:1;
	int b31:1;
} dp_inst_t;

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
	int b24:1;
	int b25:1;
	int b26:1;
	int b27:1;
	int b28:1;
	int b29:1;
	int b30:1;
	int b31:1;
} mul_inst_t;

typedef struct {
	inst_type_t inst_type;
	union {
		dp_inst_t dp_inst;
	} inst;
} inst_t;

int execute(Elf32_Ehdr *ehdr);

#endif
