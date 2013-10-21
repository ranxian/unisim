#ifndef HELPER_H
#define HELPER_H
#include "sim.h"
#include <stdint.h>
#define EB(n, b) (((n) >> (b-1)) & 1)

void printdw(int dword);
void inst_info(inst_t *inst);
uint32_t bits(int dword, int start, int end);
#endif
