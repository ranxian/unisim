#include "sim.h"
#include "helper.h"
#include <stdio.h>
#include <assert.h>
#include "memory.h"

#define RESSP (SP = 0x2000000)

void go()
{
	fetch(); clock_tick(); 

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
	PC = 0x2000200;
	SP = STACK_TOP;

	// sub sp, sp, #4
	ir = 0x24ef4004;
	fetch(); clock_tick();
	assert(PC == 0x2000204);
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
	fetch(); clock_tick();
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

	// ldw	r15, [pc+], #188	; 20001ec <add_prime+0xe8>
	ir = 0x79fbc0bc;
	PC = 0x200012c;
	write_word(0x20001ec, 0x020082cc);
	go();
	assert(regs[15] == 0x020082cc);
	assert(PC == 0x2000130);
	printf("ldw passed\n");


	// cmpsub.a	r23, r24
	ir =0x15b80018;
	regs[23] = 5;
	regs[24] = -1;
	go();
	assert(regs[24] == -1);
	assert(regs[23] == 5);
	assert(cmsr.N == 0 && cmsr.Z == 0 && cmsr.C == 1 && cmsr.V == 0);

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

	// cmpadd.a	r0, sl
	ir = 0x1700001a;
	regs[0] = 1;
	regs[26] = -1;
	go();

	// beq	2000244 <main+0x50>
	ir = 0xa0fffff8;
	PC = 0x2000260;
	go();
	assert(PC == 0x2000244);
	printf("cmpadd.a beq passed.\n");

	// cmpsub.a r15, #0	; 0x0
	ir = 0x35780000;
	regs[15] = 0;
	go();

	// beb	2000244 <main+0x50>
	ir = 0xb2fffff5;
	PC = 0x200026c;
	go();
	print_cmsr();
	assert(PC == 0x2000244);
	printf("beb passed\n");

	// cmpsub.a	r15, sl
	ir = 0x1578001a;
	regs[15] = 123;
	regs[26] = 11;
	go();

	// bua	200028c <main+0x98>
	ir = 0xb0fffffa;
	PC = 0x20002a0;
	go();
	assert(PC == 0x200028c);
	printf("bua passed\n");

	// mul	r15, r1, r1
	ir = 0x000bc121;
	regs[15] = 1;
	regs[1] = -1;
	go();
	assert(regs[15] == 1); 
	printf("mul inst passed\n");

	// 1500000f 	cmpsub.a	r0, r15
	ir = 0x1500000f;
	regs[0] = 25;
	regs[15] = 25;
	go();
 	print_cmsr();
 	
	// a600000a 	bub	2000178 <add_prime+0x74>
 	ir = 0xa600000a;
 	PC = 0x200014c;
 	go();
 	print_cmsr();
 	assert(PC != 0x2000178);
 	printf("bub passed\n");

	printf("instruction test passed.\n");
}

int main()
{
	mem_init();
	test_instructions();
 	mem_destroy();
	return 0;
}
