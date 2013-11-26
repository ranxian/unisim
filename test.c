#include "sim.h"
#include "helper.h"
#include <stdio.h>
#include <assert.h>
#include "mmu.h"
uint32_t segment_cnt;
segment_t segments[MAX_SEG_CNT];
int ir;
int regs[REG_NUM];
stat_reg_t cmsr;
stat_reg_t temp_cmsr;
d_reg_t f_reg, D_reg;
e_reg_t d_reg, E_reg;
m_reg_t e_reg, M_reg;
w_reg_t m_reg, W_reg;
#define RESSP (SP = 0x2000000)

void go()
{
	fetch(); clock_tick(); 
	#ifdef DEBUG
	fetch_stat();
	#endif
	decode(); clock_tick();
	#ifdef DEBUG
	decode_stat();
	#endif
	execute(); clock_tick();
	#ifdef DEBUG
	execute_stat();
	#endif
	memory(); clock_tick();
	#ifdef DEBUG
	memory_stat();
	#endif
	writeback(); clock_tick();
	#ifdef DEBUG
	writeback_stat();
	#endif
}

void test_instructions()
{
	int inst;
	PC = 0x80000000;
	SP = alloc_stack();

	// sub sp, sp, #4
	ir = 0x24ef4004;
	fetch(); clock_tick();
	assert(PC == 0x80000004);
	assert(D_reg.rn == 29);
	assert(D_reg.rd == 29);
	decode(); clock_tick();
	assert(E_reg.op1 = 0x200000);
	assert(E_reg.op2 = 0x4);
	assert(E_reg.opcode = SUB);
	execute(); clock_tick();
	assert(M_reg.valE = 0x1fffffc);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);
	memory(); clock_tick();
	writeback(); clock_tick();
	assert(regs[29] == 0x1fffffc);
	printf("sub inst test passed.\n");

	// add sp, sp, #4
	ir = 0x28ef4004;
	RESSP;
	go();
	assert(regs[29] == 0x2000004);
	// add r0, sp, #12
	ir = 0x28e8000c;
	SP = 0x2000000;
	go();
	assert(regs[29] == 0x2000000);
	assert(regs[0] == 0x200000c);
	printf("add inst test passed.\n");

	// add	r24, r19, #1	; 0x1
	ir = 0x289e0001;
	regs[24] = 30;
	regs[19] = -31;
	go();
	print_cmsr();
	assert(regs[24] == -30);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);

	// b.l	2000124
	ir = 0xbdffffd7;
	PC = 0x20001c4;
	go();
	assert(PC == 0x2000124);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);
	assert(LR == 0x20001c8);
	printf("b.l passed\n");

	// stw	r24, [sp-], #12
	ir = 0x70ee000c;
	regs[24] = 0x12345678;
	RESSP;
	go();
	int word;
	fetch_dword(SP - 12, &word);
	assert(word == 0x12345678);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);
	printf("stw passed\n");

	// mov	r20, r0
	ir = 0x1a050000;
	regs[20] = 0x1111;
	regs[0] = -1;
    go();
    assert(regs[20] = -1);
    assert(regs[0] == -1);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);
	printf("mov passed\n");

	// ldw	r21, [r20+],r19 << #2
	ir = 0x59a54413;
	regs[21] = 0x1;
	regs[20] = 0x1fffff0;
	regs[19] = 1;
	write_word(0x1fffff0 + 4, 0xaaaa);
	fetch(); clock_tick(); fetch_stat();
	decode(); clock_tick();
	assert(E_reg.op1 == 0x1fffff0);
	assert(E_reg.op2 == 4);
	execute(); clock_tick();
	assert(M_reg.valE = 0x1fffff4);
	memory(); clock_tick();
	writeback(); clock_tick();
	assert(regs[21] == 0xaaaa);
	assert(regs[20] == 0x1fffff0);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);
	printf("ldw passed\n");

	// cmpsub.a	r23, r24
	ir =0x15b80018;
	regs[23] = 5;
	regs[24] = -1;
	go();
	assert(regs[24] == -1);
	assert(regs[23] == 5);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);

	regs[23] = 0;
	regs[24] = 1;
	go();
	assert(cmsr.N == 1 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);

	ir =0x15b80018;
	regs[23] = -6;
	regs[24] = -5;
	go();
	print_cmsr();
	assert(cmsr.N == 1 && cmsr.Z == 0 && cmsr.C == 0 && cmsr.V == 0);
	printf("cmpsub.a passed.\n");

	// bsl	20001d8 <partition+0x98>
	ir = 0xb600000c;
	PC = 0x20001a4;
	go();
	assert(PC == 0x20001d8);

	ir =0x15b80018;
	regs[23] = 5;
	regs[24] = 4;
	go();

	ir = 0xb600000c;
	PC = 0x20001a4;
	go();
	assert(PC == 0x20001a8);
	printf("bsl passed\n");

	// beg	20001a8 <partition+0x68>
	ir =0x15b80018;
	regs[23] = 5;
	regs[24] = 4;
	go();

	ir = 0xb4fffff4;
	PC = 0x20001d4;
	go();
	assert(PC == 0x20001a8);
	printf("beg passed\n");


	printf("instruction test passed.\n");
}

int main()
{
	segment_cnt = 0;
	test_instructions();
	return 0;
}
