#include "memory.h"
#include <stdlib.h>
#include <string.h>

char *m_memory;

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