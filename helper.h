#ifndef HELPER_H
#define HELPER_H
#include "sim.h"
#include <stdint.h>
#define EB(n, b) (((n) >> (b-1)) & 1)
#define UP(n, b) (((n) >> (b-1)) & 1)
#define B(n, b) (((n) >> (b)) & 1)
#define R(no) (regs[no])
#define IS_LOG(opcode) (opcode == AND || opcode == XOR || opcode == CAND || opcode == CXOR \
				|| opcode == ORR || opcode == MOV || opcode == CLB || opcode == MVN)
#define PC (regs[31])
#define LR (regs[30])
#define COPY_SBIT(r1, r2) \
	(r1.S = r2.S); \
	(r1.P = r2.P); \
	(r1.U = r2.U); \
	(r1.B = r2.B); \
	(r1.W = r2.W); \
	(r1.L = r2.L); \
	(r1.H = r2.H);

void printdw(int dword);
uint32_t bits(int dword, int start, int end);
void fetch_stat();
void decode_stat();
void execute_stat();
void memory_stat();
void writeback_stat();
char *INST_NAME(inst_type_t i);
char *OPCODE_NAME(opcode_t o);
char *SHIFT_TYPE_NAME(shifttype_t s);

extern stat_reg_t cmsr;
#endif
