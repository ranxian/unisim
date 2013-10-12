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

int execute(Elf32_Ehdr *ehdr)
{
	int i;
	int pc, inst;

	pc = ehdr->e_entry;
	printdw(pc);

	for (i = 0; i < 10; i++) {
		fetch_dword(pc, &inst);
		printf("inst: ");
		printdw(inst);
		pc += 4;
	}
	return 0;
}
