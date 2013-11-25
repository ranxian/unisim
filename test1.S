
test1:     file format elf32-littleunicore32


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

0200009c <_start>:
 200009c:	3a03c001 	mov	r15, #1	; 0x1
 20000a0:	79fb800c 	ldw	r14, [pc+], #12	; 20000b0 <_start+0x14>
 20000a4:	1a00000f 	mov	r0, r15
 20000a8:	7873c000 	stw	r15, [r14+]
 20000ac:	bcfffff1 	b	2000074 <sys_exit>
 20000b0:	020080d8 	.word	0x020080d8

020000b4 <__divsi3>:
 20000b4:	bcfffff1 	b	200007c <sys_div>

020000b8 <__modsi3>:
 20000b8:	bcfffff4 	b	200008c <sys_mod>

020000bc <__udivsi3>:
 20000bc:	bcfffff1 	b	2000084 <sys_udiv>

020000c0 <__umodsi3>:
 20000c0:	bcfffff4 	b	2000094 <sys_umod>

020000c4 <main>:
 20000c4:	79fbc00c 	ldw	r15, [pc+], #12	; 20000d4 <main+0x10>
 20000c8:	3a000001 	mov	r0, #1	; 0x1
 20000cc:	78780000 	stw	r0, [r15+]
 20000d0:	10ffc13e 	jump	lr
 20000d4:	020080d8 	.word	0x020080d8
