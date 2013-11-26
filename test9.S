
test9:     file format elf32-littleunicore32


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

02000094 <fab>:
 2000094:	70ef8004 	stw	lr, [sp-], #4
 2000098:	70ee8008 	stw	sl, [sp-], #8
 200009c:	70ee8008 	stw	sl, [sp-], #8
 20000a0:	70ee000c 	stw	r24, [sp-], #12
 20000a4:	70ee8008 	stw	sl, [sp-], #8
 20000a8:	70ee000c 	stw	r24, [sp-], #12
 20000ac:	24ef400c 	sub	sp, sp, #12	; 0xc
 20000b0:	1a068000 	mov	sl, r0
 20000b4:	35000001 	cmpsub.a	r0, #1	; 0x1
 20000b8:	3a060000 	mov	r24, #0	; 0x0
 20000bc:	3a000001 	mov	r0, #1	; 0x1
 20000c0:	b2000007 	beb	20000e0 <fab+0x4c>
 20000c4:	24d00002 	sub	r0, sl, #2	; 0x2
 20000c8:	bdfffff2 	b.l	2000094 <fab>
 20000cc:	24d68001 	sub	sl, sl, #1	; 0x1
 20000d0:	35d00001 	cmpsub.a	sl, #1	; 0x1
 20000d4:	08c60000 	add	r24, r24, r0
 20000d8:	b0fffffa 	bua	20000c4 <fab+0x30>
 20000dc:	28c00001 	add	r0, r24, #1	; 0x1
 20000e0:	69ee0004 	ldw.w	r24, [sp]+, #4
 20000e4:	69ee8004 	ldw.w	sl, [sp]+, #4
 20000e8:	69ef0004 	ldw.w	ip, [sp]+, #4
 20000ec:	10ffc13c 	jump	ip

020000f0 <main>:
 20000f0:	24ef4004 	sub	sp, sp, #4	; 0x4
 20000f4:	78ef8000 	stw	lr, [sp+]
 20000f8:	3a000002 	mov	r0, #2	; 0x2
 20000fc:	bdffffe5 	b.l	2000094 <fab>
 2000100:	bdffffde 	b.l	200007c <sys_putint>
 2000104:	3a000003 	mov	r0, #3	; 0x3
 2000108:	bdffffe2 	b.l	2000094 <fab>
 200010c:	bdffffdb 	b.l	200007c <sys_putint>
 2000110:	3a000004 	mov	r0, #4	; 0x4
 2000114:	bdffffdf 	b.l	2000094 <fab>
 2000118:	bdffffd8 	b.l	200007c <sys_putint>
 200011c:	3a000005 	mov	r0, #5	; 0x5
 2000120:	bdffffdc 	b.l	2000094 <fab>
 2000124:	79ef8000 	ldw	lr, [sp+]
 2000128:	28ef4004 	add	sp, sp, #4	; 0x4
 200012c:	bcffffd3 	b	200007c <sys_putint>

02000130 <_start>:
 2000130:	bdffffef 	b.l	20000f0 <main>
 2000134:	bcffffc7 	b	2000054 <sys_exit>
