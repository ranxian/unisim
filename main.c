#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "loader.h"
#include "sim.h"
uint32_t segment_cnt;
segment_t segments[MAX_SEG_CNT];
int pc;
int ir;
int lr;
int regs[REG_NUM];
stat_reg_t cmsr, temp_cmsr;
d_reg_t f_reg, D_reg;
e_reg_t d_reg, E_reg;
m_reg_t e_reg, M_reg;

int main(int argc, char *argv[])
{
	Elf32_Ehdr ehdr;
	Elf32_Shdr shdrs[100];
	Elf32_Phdr phdrs[100];
	FILE *file = fopen(argv[1], "r");
	Elf32_Ehdr *ehdrp = &ehdr;

	fread(ehdrp, 1, sizeof(ehdr), file);
	// ehdr_stats(ehdrp);
	load_shdrs(file, ehdrp, shdrs);
	load_phdrs(file, ehdrp, phdrs);
	load_psegs(file, ehdrp, phdrs);

	simulate(ehdrp->e_entry);
	fclose(file);
}

