#ifndef HELPER_H
#define HELPER_H
#include "sim.h"
#include <stdint.h>
#define EB(n, b) (((n) >> (b-1)) & 1)
#define UP(n, b) (((n) >> (b-1)) & 1)
#define B(n, b) (((n) >> (b)) & 1)
#define R(no) ((no) == 31 ? regs[no] + 4 : regs[no])
#define IS_LOG(opcode) (opcode == AND || opcode == XOR || opcode == CAND || opcode == CXOR \
				|| opcode == ORR || opcode == MOV || opcode == CLB || opcode == MVN)
#define PC (regs[31])
#define LR (regs[30])

void printdw(int dword);
void inst_info();
uint32_t bits(int dword, int start, int end);
#endif
