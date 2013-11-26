
test8:     file format elf32-littleunicore32


Disassembly of section .text:

02000074 <sys_exit>:
 2000074:	ff900001 	jepriv	0x00900001
 2000078:	1a07c01e 	mov	pc, lr

0200007c <sys_div>:
 200007c:	ff9000f0 	jepriv	0x009000f0
 2000080:	1a07c01e 	mov	pc, lr

02000084 <sys_udiv>:
 2000084:	ff9000f1 	jepriv	0x009000f1
 2000088:	1a07c01e 	mov	pc, lr

0200008c <sys_mod>:
 200008c:	ff9000f2 	jepriv	0x009000f2
 2000090:	1a07c01e 	mov	pc, lr

02000094 <sys_umod>:
 2000094:	ff9000f3 	jepriv	0x009000f3
 2000098:	1a07c01e 	mov	pc, lr

0200009c <sys_putint>:
 200009c:	ff9000f4 	jepriv	0x009000f4
 20000a0:	1a07c01e 	mov	pc, lr

020000a4 <__divsi3>:
 20000a4:	bcfffff5 	b	200007c <sys_div>

020000a8 <__modsi3>:
 20000a8:	bcfffff8 	b	200008c <sys_mod>

020000ac <__udivsi3>:
 20000ac:	bcfffff5 	b	2000084 <sys_udiv>

020000b0 <__umodsi3>:
 20000b0:	bcfffff8 	b	2000094 <sys_umod>

020000b4 <solve>:
 20000b4:	24ef4004 	sub	sp, sp, #4	; 0x4
 20000b8:	78ef8000 	stw	lr, [sp+]
 20000bc:	3a03c000 	mov	r15, #0	; 0x0
 20000c0:	1a000000 	nop			(mov r0,r0)
 20000c4:	79fb0034 	ldw	r12, [pc+], #52	; 20000fc <solve+0x48>
 20000c8:	1a00000f 	mov	r0, r15
 20000cc:	5963400f 	ldw	r13, [r12+],r15
 20000d0:	28038001 	add	r14, r0, #1	; 0x1
 20000d4:	287bc004 	add	r15, r15, #4	; 0x4
 20000d8:	35680007 	cmpsub.a	r13, #7	; 0x7
 20000dc:	1ad0000e 	cmoveg	r0, r14
 20000e0:	35780014 	cmpsub.a	r15, #20	; 0x14
 20000e4:	a2fffff9 	bne	20000cc <solve+0x18>
 20000e8:	bdffffec 	b.l	200009c <sys_putint>
 20000ec:	3a000000 	mov	r0, #0	; 0x0
 20000f0:	79ef0000 	ldw	ip, [sp+]
 20000f4:	28ef4004 	add	sp, sp, #4	; 0x4
 20000f8:	10ffc13c 	jump	ip
 20000fc:	02008110 	.word	0x02008110

02000100 <_start>:
 2000100:	bdffffec 	b.l	20000b4 <solve>
 2000104:	3a000000 	mov	r0, #0	; 0x0
 2000108:	bcffffda 	b	2000074 <sys_exit>

0200010c <main>:
 200010c:	bcffffe9 	b	20000b4 <solve>
