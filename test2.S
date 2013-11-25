
test2:     file format elf32-littleunicore32


Disassembly of section .text:

02000054 <sys_exit>:
 2000054:	ff900001 	jepriv	0x00900001
 2000058:	1a07c01e 	mov	pc, lr

0200005c <sys_div>:
 200005c:	ff9000f0 	jepriv	0x009000f0
 2000060:	1a07c01e 	mov	pc, lr

02000064 <sys_udiv>:
 2000064:	ff9000f1 	jepriv	0x009000f1
 2000068:	1a07c01e 	mov	pc, lr

0200006c <sys_mod>:
 200006c:	ff9000f2 	jepriv	0x009000f2
 2000070:	1a07c01e 	mov	pc, lr

02000074 <sys_umod>:
 2000074:	ff9000f3 	jepriv	0x009000f3
 2000078:	1a07c01e 	mov	pc, lr

0200007c <sys_putint>:
 200007c:	ff9000f4 	jepriv	0x009000f4
 2000080:	1a07c01e 	mov	pc, lr

02000084 <__divsi3>:
 2000084:	bcfffff5 	b	200005c <sys_div>

02000088 <__modsi3>:
 2000088:	bcfffff8 	b	200006c <sys_mod>

0200008c <__udivsi3>:
 200008c:	bcfffff5 	b	2000064 <sys_udiv>

02000090 <__umodsi3>:
 2000090:	bcfffff8 	b	2000074 <sys_umod>

02000094 <max>:
 2000094:	15080000 	cmpsub.a	r1, r0
 2000098:	1ad00001 	cmoveg	r0, r1
 200009c:	10ffc13e 	jump	lr

020000a0 <max3>:
 20000a0:	15080000 	cmpsub.a	r1, r0
 20000a4:	1ad00001 	cmoveg	r0, r1
 20000a8:	15000002 	cmpsub.a	r0, r2
 20000ac:	1ad80002 	cmovsl	r0, r2
 20000b0:	10ffc13e 	jump	lr

020000b4 <main>:
 20000b4:	24ef4004 	sub	sp, sp, #4	; 0x4
 20000b8:	78ef8000 	stw	lr, [sp+]
 20000bc:	3a000002 	mov	r0, #2	; 0x2
 20000c0:	bdffffee 	b.l	200007c <sys_putint>
 20000c4:	3a000014 	mov	r0, #20	; 0x14
 20000c8:	bdffffec 	b.l	200007c <sys_putint>
 20000cc:	3a000003 	mov	r0, #3	; 0x3
 20000d0:	bdffffea 	b.l	200007c <sys_putint>
 20000d4:	3a000007 	mov	r0, #7	; 0x7
 20000d8:	bdffffe8 	b.l	200007c <sys_putint>
 20000dc:	3a00000a 	mov	r0, #10	; 0xa
 20000e0:	bdffffe6 	b.l	200007c <sys_putint>
 20000e4:	3a000003 	mov	r0, #3	; 0x3
 20000e8:	bdffffe4 	b.l	200007c <sys_putint>
 20000ec:	3a000003 	mov	r0, #3	; 0x3
 20000f0:	bdffffe2 	b.l	200007c <sys_putint>
 20000f4:	3a00000a 	mov	r0, #10	; 0xa
 20000f8:	bdffffe0 	b.l	200007c <sys_putint>
 20000fc:	3a0000c0 	mov	r0, #192	; 0xc0
 2000100:	bdffffde 	b.l	200007c <sys_putint>
 2000104:	3a00000c 	mov	r0, #12	; 0xc
 2000108:	bdffffdc 	b.l	200007c <sys_putint>
 200010c:	3a00000d 	mov	r0, #13	; 0xd
 2000110:	79ef8000 	ldw	lr, [sp+]
 2000114:	28ef4004 	add	sp, sp, #4	; 0x4
 2000118:	bcffffd8 	b	200007c <sys_putint>

0200011c <_start>:
 200011c:	bdffffe5 	b.l	20000b4 <main>
 2000120:	bcffffcc 	b	2000054 <sys_exit>
