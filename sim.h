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

typedef struct {
	int S:1;

} inst_t;

int execute(Elf32_Ehdr *ehdr);

#endif
