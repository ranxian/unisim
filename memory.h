#ifndef MEMORY_H
#define MEMORY_H
#define STACK_START 0x1000000
#define STACK_SIZE  0x1000000
#define STACK_TOP	0x2000000
#define CS_START	0x2000004
#define CS_SIZE		0x1000000
#define CS_END		0x3000004
#define MEM_SIZE 	0x4000000

#define V2P(addr) (m_memory + addr)

void mem_read(int addr, char *dst, int len);

void mem_write(int addr, char *src, int len);

int mem_init();

int mem_destroy();

extern char *m_memory;

#endif