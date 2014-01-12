#include "memory.h"
#include <stdlib.h>
#include <string.h>

char *m_memory;

void mem_read(int addr, char *dst, int len)
{
	memcpy(dst, V2P(addr), len);
}

void mem_write(int addr, char *src, int len)
{
	memcpy(V2P(addr), src, len);
}

int mem_init()
{
	m_memory = malloc(MEM_SIZE);
	return 0;
}	

int mem_destroy()
{
	free(m_memory);
	return 0;
}