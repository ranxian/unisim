#include "sim.h"
#include <stdio.h>
#include <string.h>
#include "helper.h"
#define UP(n, b) (((n) >> (b-1)) & 1)
#define B(n, b) (((n) >> (b)) & 1)

uint32_t bits(int dword, int start, int end)
{
	int i;
	uint32_t res = 0;
	for (i = start; i <= end; i++) {
		res |= 1 << i;
	}
	return dword & res;
}

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

	pc = entry;
	printdw(pc);

	for (i = 0; i < 10; i++) {
		// fetch
		fetch_dword(pc, &ir.i);
		// decode
		decode(&ir);
		// execute
		execute(&ir);
		// memory
		memory(&ir);
		// write-back
		writeback(&ir);
		printf("inst: ");
		printdw(ir.i);
		pc += 4;
	}
	return 0;
}

int decode(inst_t *inst)
{
	int ii = inst->i;
	uint32_t f29_31 = bits(ii, 29, 31);
	uint32_t f26_28 = bits(ii, 26, 28);
	uint32_t f19_23 = bits(ii, 19, 23);
	uint32_t f14_f18 = bits(ii, 14, 18);
	uint32_t f5_8 = bits(ii, 5, 8);
	uint32_t f9_13 = bits(ii, 9, 13);

	switch(f29_31) {
		case 0x0:
			if (B(ii, 8) == 0 && B(ii, 5) == 0)
				inst->type = D_IMM_SH_INST;
			else if (B(ii, 8) == 0 && B(ii, 5) == 1)
				inst->type = D_REG_SH_INST;
			if (f26_28 == 0) {
				if (f5_8 == 0x9)
					inst->type = MUL_INST;
			} else if (f26_28 == 0x4) {
				if (B(ii, 25) == 0 && f19_23 == 0x1f &&
						f14_f18 == 0x1f	&& f9_13 == 0 && f5_8 == 0x9)
					inst->type = BRX_INST;
			}
			break;
		case 0x1:
			inst->type = D_IMM_INST;
			break;
		case 0x2:
			if (B(ii, 5) == 0 && B(ii, 8) == 0)
				inst->type = LSR_OFF_INST;
			else if (B(ii, 26) == 0 && f9_13 == 0 && B(ii, 5) == 1 && B(ii, 8) == 1)
				inst->type = LSHWR_OFF_INST;
			else if (B(ii, 26) == 1 && B(ii, 5) == 1 && B(ii, 8) == 1)
				inst->type = LSHWI_OFF_INST;
			break;
		case 0x3:
			inst->type = LSI_OFF_INST;
			break;
		case 0x5:
			inst->type = BRLK_INST;
			break;
		case 0x7:
			if (bits(ii, 24, 28) == 0x1f)
				inst->type = ST_INST;
			break;
		default:
			inst->type = UNKNOWN;
	}
}

int execute(inst_t *inst)
{
	return 0;
}

int memory(inst_t *inst)
{
	return 0;
}

int writeback(inst_t *inst)
{
	return 0;
}

