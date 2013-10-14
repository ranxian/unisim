#include "sim.h"
#include <stdio.h>
#include <string.h>
#include "helper.h"

void fetch_dword(int addr, int *dest)
{
	int i;
	char *src;
	for (i = 0; i < segment_cnt; i++) {
		if (segments[i].offset <= addr && segments[i].offset + segments[i].size >= addr - 4) {
			src = segments[i].content + addr - segments[i].offset;
		}
	}
	memcpy(dest, src, sizeof(int));
}

int simulate(int entry)
{
	int i;
	inst_t ir;
	int dword;

	pc = entry;
	printdw(pc);

	for (i = 0; i < 10; i++) {
		fetch_dword(pc, &dword);
		// *ir = *(inst_t *)&dword;
		printf("inst: ");
		printdw(dword);
		pc += 4;
	}
	return 0;
}

int decode(inst_t *inst)
{
	return 0;
}
