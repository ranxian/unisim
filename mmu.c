#include "mmu.h"
#include <stdlib.h>
#include <string.h>
char *V2P(int addr) {
	int i;
	char *src = NULL;
	for (i = 0; i < segment_cnt; i++) {
		if (segments[i].offset <= addr && segments[i].offset + segments[i].size >= addr - 4) {
			src = segments[i].content + addr - segments[i].offset;
			break;
		}
	}
	return src;
}

void fetch_nbyte(int addr, void *dest, int len)
{
	memcpy(dest, V2P(addr), len);
}

void fetch_dword(int addr, void *dest)
{
	fetch_nbyte(addr, dest, 4);
}

void write_word(int addr, int word)
{
	memcpy(V2P(addr), &word, 4);
}

void write_byte(int addr, char byte)
{
	memcpy(V2P(addr), &byte, 1);
}

void write_hword(int addr, short hword)
{
	memcpy(V2P(addr), &hword, 2);
}

int alloc_stack()
{
	segment_t *ss = &segments[segment_cnt];
	segment_cnt ++;

	ss->offset = STACK_START;
	ss->size = STACK_SIZE;
	ss->content = malloc(STACK_SIZE);

	return STACK_TOP;
}

int alloc_cs()
{
	segment_t *cs = &segments[segment_cnt];
	segment_cnt ++;
	
	cs->offset = CS_START;
	cs->size = CS_SIZE;
	cs->content = malloc(CS_SIZE);

	return CS_START;
}
