#ifndef MMU_H
#define MMU_H
#include "loader.h"
#define STACK_START 0x1000000
#define STACK_SIZE  0x1000000
#define STACK_TOP	0x2000000

char *V2P(int addr);

void fetch_nbyte(int addr, void *dest, int len);

void fetch_dword(int addr, void *dest);

void write_word(int addr, int word);

void write_byte(int addr, char byte);

void write_hword(int addr, short hword);

int alloc_stack();
#endif