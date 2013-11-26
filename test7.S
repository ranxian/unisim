
test7:     file format elf32-littleunicore32


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

02000094 <print>:
 2000094:	70ef8004 	stw	lr, [sp-], #4
 2000098:	70ef8004 	stw	lr, [sp-], #4
 200009c:	70ee8008 	stw	sl, [sp-], #8
 20000a0:	70ef8004 	stw	lr, [sp-], #4
 20000a4:	70ee8008 	stw	sl, [sp-], #8
 20000a8:	24ef4008 	sub	sp, sp, #8	; 0x8
 20000ac:	1a068000 	mov	sl, r0
 20000b0:	79000000 	ldw	r0, [r0+]
 20000b4:	bdfffff1 	b.l	200007c <sys_putint>
 20000b8:	79d00004 	ldw	r0, [sl+], #4
 20000bc:	bdffffef 	b.l	200007c <sys_putint>
 20000c0:	79d00008 	ldw	r0, [sl+], #8
 20000c4:	69ee8004 	ldw.w	sl, [sp]+, #4
 20000c8:	69ef8004 	ldw.w	lr, [sp]+, #4
 20000cc:	bcffffeb 	b	200007c <sys_putint>

020000d0 <swap>:
 20000d0:	1a004401 	mov	r1, r1 << #2
 20000d4:	1a008402 	mov	r2, r2 << #2
 20000d8:	5903c001 	ldw	r15, [r0+],r1
 20000dc:	59038002 	ldw	r14, [r0+],r2
 20000e0:	58038001 	stw	r14, [r0+],r1
 20000e4:	5803c002 	stw	r15, [r0+],r2
 20000e8:	10ffc13e 	jump	lr

020000ec <partition>:
 20000ec:	70ef8004 	stw	lr, [sp-], #4
 20000f0:	70ee8008 	stw	sl, [sp-], #8
 20000f4:	70ee000c 	stw	r24, [sp-], #12
 20000f8:	70ee000c 	stw	r24, [sp-], #12
 20000fc:	70edc010 	stw	r23, [sp-], #16
 2000100:	70ee000c 	stw	r24, [sp-], #12
 2000104:	70edc010 	stw	r23, [sp-], #16
 2000108:	24ef4010 	sub	sp, sp, #16	; 0x10
 200010c:	1a068000 	mov	sl, r0
 2000110:	79000000 	ldw	r0, [r0+]
 2000114:	1a060001 	mov	r24, r1
 2000118:	1a05c002 	mov	r23, r2
 200011c:	bdffffd7 	b.l	200007c <sys_putint>
 2000120:	79d00004 	ldw	r0, [sl+], #4
 2000124:	bdffffd5 	b.l	200007c <sys_putint>
 2000128:	79d00008 	ldw	r0, [sl+], #8
 200012c:	bdffffd3 	b.l	200007c <sys_putint>
 2000130:	1a000018 	mov	r0, r24
 2000134:	bdffffd1 	b.l	200007c <sys_putint>
 2000138:	1a000017 	mov	r0, r23
 200013c:	bdffffcf 	b.l	200007c <sys_putint>
 2000140:	1a024418 	mov	r9, r24 << #2
 2000144:	28c38001 	add	r14, r24, #1	; 0x1
 2000148:	59d2c009 	ldw	r11, [sl+],r9
 200014c:	15b8000e 	cmpsub.a	r23, r14
 2000150:	08d34009 	add	r13, sl, r9
 2000154:	08d3c40e 	add	r15, sl, r14 << #2
 2000158:	b600001c 	bsl	20001cc <partition+0xe0>
 200015c:	797b4000 	ldw	r13, [r15+]
 2000160:	28738001 	add	r14, r14, #1	; 0x1
 2000164:	1558000d 	cmpsub.a	r11, r13
 2000168:	ba000005 	bel	2000180 <partition+0x94>
 200016c:	28c60001 	add	r24, r24, #1	; 0x1
 2000170:	1a030418 	mov	r12, r24 << #2
 2000174:	59d2800c 	ldw	r10, [sl+],r12
 2000178:	58d3400c 	stw	r13, [sl+],r12
 200017c:	787a8000 	stw	r10, [r15+]
 2000180:	287bc004 	add	r15, r15, #4	; 0x4
 2000184:	15b8000e 	cmpsub.a	r23, r14
 2000188:	b4fffff4 	beg	200015c <partition+0x70>
 200018c:	1a03c418 	mov	r15, r24 << #2
 2000190:	59d34009 	ldw	r13, [sl+],r9
 2000194:	08d3800f 	add	r14, sl, r15
 2000198:	59d2c00f 	ldw	r11, [sl+],r15
 200019c:	78734000 	stw	r13, [r14+]
 20001a0:	1a000018 	mov	r0, r24
 20001a4:	58d2c009 	stw	r11, [sl+],r9
 20001a8:	bdffffb4 	b.l	200007c <sys_putint>
 20001ac:	79f80028 	ldw	r0, [pc+], #40	; 20001d8 <partition+0xec>
 20001b0:	bdffffb2 	b.l	200007c <sys_putint>
 20001b4:	1a000018 	mov	r0, r24
 20001b8:	69edc004 	ldw.w	r23, [sp]+, #4
 20001bc:	69ee0004 	ldw.w	r24, [sp]+, #4
 20001c0:	69ee8004 	ldw.w	sl, [sp]+, #4
 20001c4:	69ef0004 	ldw.w	ip, [sp]+, #4
 20001c8:	10ffc13c 	jump	ip
 20001cc:	1a03800d 	mov	r14, r13
 20001d0:	1a03400b 	mov	r13, r11
 20001d4:	bcfffff1 	b	200019c <partition+0xb0>
 20001d8:	423a35c7 	.word	0x423a35c7

020001dc <quicksort>:
 20001dc:	70ef8004 	stw	lr, [sp-], #4
 20001e0:	70eec008 	stw	fp, [sp-], #8
 20001e4:	70ee800c 	stw	sl, [sp-], #12
 20001e8:	70ee4010 	stw	r25, [sp-], #16
 20001ec:	70ee0014 	stw	r24, [sp-], #20
 20001f0:	70edc018 	stw	r23, [sp-], #24
 20001f4:	70ed801c 	stw	r22, [sp-], #28
 20001f8:	70ed4020 	stw	r21, [sp-], #32
 20001fc:	70ed0024 	stw	r20, [sp-], #36
 2000200:	70ecc028 	stw	r19, [sp-], #40
 2000204:	70ec802c 	stw	r18, [sp-], #44
 2000208:	70ec802c 	stw	r18, [sp-], #44
 200020c:	70ec4030 	stw	r17, [sp-], #48
 2000210:	70ec802c 	stw	r18, [sp-], #44
 2000214:	70ec4030 	stw	r17, [sp-], #48
 2000218:	24ef4030 	sub	sp, sp, #48	; 0x30
 200021c:	24ef4024 	sub	sp, sp, #36	; 0x24
 2000220:	1a058000 	mov	r22, r0
 2000224:	1a068001 	mov	sl, r1
 2000228:	1a044002 	mov	r17, r2
 200022c:	1a00001a 	mov	r0, sl
 2000230:	bdffff92 	b.l	200007c <sys_putint>
 2000234:	1a000011 	mov	r0, r17
 2000238:	bdffff90 	b.l	200007c <sys_putint>
 200023c:	15d00011 	cmpsub.a	sl, r17
 2000240:	b4000091 	beg	2000488 <quicksort+0x2ac>
 2000244:	1a000016 	mov	r0, r22
 2000248:	1a00401a 	mov	r1, sl
 200024c:	1a008011 	mov	r2, r17
 2000250:	bdffffa6 	b.l	20000ec <partition>
 2000254:	24064001 	sub	r25, r0, #1	; 0x1
 2000258:	78e80020 	stw	r0, [sp+], #32
 200025c:	1a00001a 	mov	r0, sl
 2000260:	bdffff86 	b.l	200007c <sys_putint>
 2000264:	1a000019 	mov	r0, r25
 2000268:	bdffff84 	b.l	200007c <sys_putint>
 200026c:	15c8001a 	cmpsub.a	r25, sl
 2000270:	ba000082 	bel	200047c <quicksort+0x2a0>
 2000274:	1a000016 	mov	r0, r22
 2000278:	1a00401a 	mov	r1, sl
 200027c:	1a008019 	mov	r2, r25
 2000280:	bdffff9a 	b.l	20000ec <partition>
 2000284:	2406c001 	sub	fp, r0, #1	; 0x1
 2000288:	78e8001c 	stw	r0, [sp+], #28
 200028c:	1a00001a 	mov	r0, sl
 2000290:	bdffff7a 	b.l	200007c <sys_putint>
 2000294:	1a00001b 	mov	r0, fp
 2000298:	bdffff78 	b.l	200007c <sys_putint>
 200029c:	15d8001a 	cmpsub.a	fp, sl
 20002a0:	ba000073 	bel	2000470 <quicksort+0x294>
 20002a4:	1a000016 	mov	r0, r22
 20002a8:	1a00401a 	mov	r1, sl
 20002ac:	1a00801b 	mov	r2, fp
 20002b0:	bdffff8e 	b.l	20000ec <partition>
 20002b4:	2403c001 	sub	r15, r0, #1	; 0x1
 20002b8:	78e80018 	stw	r0, [sp+], #24
 20002bc:	78ebc008 	stw	r15, [sp+], #8
 20002c0:	1a00001a 	mov	r0, sl
 20002c4:	bdffff6d 	b.l	200007c <sys_putint>
 20002c8:	79e80008 	ldw	r0, [sp+], #8
 20002cc:	bdffff6b 	b.l	200007c <sys_putint>
 20002d0:	79ebc008 	ldw	r15, [sp+], #8
 20002d4:	1578001a 	cmpsub.a	r15, sl
 20002d8:	ba000062 	bel	2000464 <quicksort+0x288>
 20002dc:	1a00800f 	mov	r2, r15
 20002e0:	1a000016 	mov	r0, r22
 20002e4:	1a00401a 	mov	r1, sl
 20002e8:	bdffff80 	b.l	20000ec <partition>
 20002ec:	2403c001 	sub	r15, r0, #1	; 0x1
 20002f0:	78e80014 	stw	r0, [sp+], #20
 20002f4:	78ebc004 	stw	r15, [sp+], #4
 20002f8:	1a00001a 	mov	r0, sl
 20002fc:	bdffff5f 	b.l	200007c <sys_putint>
 2000300:	79e80004 	ldw	r0, [sp+], #4
 2000304:	bdffff5d 	b.l	200007c <sys_putint>
 2000308:	79ebc004 	ldw	r15, [sp+], #4
 200030c:	1578001a 	cmpsub.a	r15, sl
 2000310:	ba000051 	bel	2000458 <quicksort+0x27c>
 2000314:	1a00800f 	mov	r2, r15
 2000318:	1a000016 	mov	r0, r22
 200031c:	1a00401a 	mov	r1, sl
 2000320:	bdffff72 	b.l	20000ec <partition>
 2000324:	2403c001 	sub	r15, r0, #1	; 0x1
 2000328:	78e80010 	stw	r0, [sp+], #16
 200032c:	78ebc000 	stw	r15, [sp+]
 2000330:	1a00001a 	mov	r0, sl
 2000334:	bdffff51 	b.l	200007c <sys_putint>
 2000338:	79e80000 	ldw	r0, [sp+]
 200033c:	bdffff4f 	b.l	200007c <sys_putint>
 2000340:	79ebc000 	ldw	r15, [sp+]
 2000344:	1578001a 	cmpsub.a	r15, sl
 2000348:	ba000040 	bel	200044c <quicksort+0x270>
 200034c:	1a00401a 	mov	r1, sl
 2000350:	1a00800f 	mov	r2, r15
 2000354:	1a000016 	mov	r0, r22
 2000358:	bdffff64 	b.l	20000ec <partition>
 200035c:	2404c001 	sub	r19, r0, #1	; 0x1
 2000360:	78e8000c 	stw	r0, [sp+], #12
 2000364:	1a00001a 	mov	r0, sl
 2000368:	bdffff44 	b.l	200007c <sys_putint>
 200036c:	1a000013 	mov	r0, r19
 2000370:	bdffff42 	b.l	200007c <sys_putint>
 2000374:	1598001a 	cmpsub.a	r19, sl
 2000378:	ba000031 	bel	2000440 <quicksort+0x264>
 200037c:	1a00401a 	mov	r1, sl
 2000380:	1a008013 	mov	r2, r19
 2000384:	1a000016 	mov	r0, r22
 2000388:	bdffff58 	b.l	20000ec <partition>
 200038c:	24054001 	sub	r21, r0, #1	; 0x1
 2000390:	1a048000 	mov	r18, r0
 2000394:	1a00001a 	mov	r0, sl
 2000398:	bdffff38 	b.l	200007c <sys_putint>
 200039c:	1a000015 	mov	r0, r21
 20003a0:	bdffff36 	b.l	200007c <sys_putint>
 20003a4:	15a8001a 	cmpsub.a	r21, sl
 20003a8:	ba00001e 	bel	2000424 <quicksort+0x248>
 20003ac:	1a000016 	mov	r0, r22
 20003b0:	1a00401a 	mov	r1, sl
 20003b4:	1a008015 	mov	r2, r21
 20003b8:	bdffff4c 	b.l	20000ec <partition>
 20003bc:	1a050000 	mov	r20, r0
 20003c0:	24060001 	sub	r24, r0, #1	; 0x1
 20003c4:	bc000009 	b	20003ec <quicksort+0x210>
 20003c8:	1a008018 	mov	r2, r24
 20003cc:	1a000016 	mov	r0, r22
 20003d0:	bdffff46 	b.l	20000ec <partition>
 20003d4:	1a05c000 	mov	r23, r0
 20003d8:	1a00401a 	mov	r1, sl
 20003dc:	1a000016 	mov	r0, r22
 20003e0:	24b88001 	sub	r2, r23, #1	; 0x1
 20003e4:	bdffff7d 	b.l	20001dc <quicksort>
 20003e8:	28be8001 	add	sl, r23, #1	; 0x1
 20003ec:	1a00001a 	mov	r0, sl
 20003f0:	bdffff22 	b.l	200007c <sys_putint>
 20003f4:	1a000018 	mov	r0, r24
 20003f8:	bdffff20 	b.l	200007c <sys_putint>
 20003fc:	15c0001a 	cmpsub.a	r24, sl
 2000400:	1a00401a 	mov	r1, sl
 2000404:	b8fffff0 	bsg	20003c8 <quicksort+0x1ec>
 2000408:	28a68001 	add	sl, r20, #1	; 0x1
 200040c:	1a00001a 	mov	r0, sl
 2000410:	bdffff1a 	b.l	200007c <sys_putint>
 2000414:	1a000015 	mov	r0, r21
 2000418:	bdffff18 	b.l	200007c <sys_putint>
 200041c:	15a8001a 	cmpsub.a	r21, sl
 2000420:	b8ffffe2 	bsg	20003ac <quicksort+0x1d0>
 2000424:	28968001 	add	sl, r18, #1	; 0x1
 2000428:	1a00001a 	mov	r0, sl
 200042c:	bdffff13 	b.l	200007c <sys_putint>
 2000430:	1a000013 	mov	r0, r19
 2000434:	bdffff11 	b.l	200007c <sys_putint>
 2000438:	1598001a 	cmpsub.a	r19, sl
 200043c:	b8ffffcf 	bsg	200037c <quicksort+0x1a0>
 2000440:	79ebc00c 	ldw	r15, [sp+], #12
 2000444:	287e8001 	add	sl, r15, #1	; 0x1
 2000448:	bcffffb9 	b	2000330 <quicksort+0x154>
 200044c:	79ebc010 	ldw	r15, [sp+], #16
 2000450:	287e8001 	add	sl, r15, #1	; 0x1
 2000454:	bcffffa8 	b	20002f8 <quicksort+0x11c>
 2000458:	79ebc014 	ldw	r15, [sp+], #20
 200045c:	287e8001 	add	sl, r15, #1	; 0x1
 2000460:	bcffff97 	b	20002c0 <quicksort+0xe4>
 2000464:	79ebc018 	ldw	r15, [sp+], #24
 2000468:	287e8001 	add	sl, r15, #1	; 0x1
 200046c:	bcffff87 	b	200028c <quicksort+0xb0>
 2000470:	79ebc01c 	ldw	r15, [sp+], #28
 2000474:	287e8001 	add	sl, r15, #1	; 0x1
 2000478:	bcffff78 	b	200025c <quicksort+0x80>
 200047c:	79ebc020 	ldw	r15, [sp+], #32
 2000480:	287e8001 	add	sl, r15, #1	; 0x1
 2000484:	bcffff69 	b	200022c <quicksort+0x50>
 2000488:	28ef4024 	add	sp, sp, #36	; 0x24
 200048c:	79ec4000 	ldw	r17, [sp+]
 2000490:	79ec8004 	ldw	r18, [sp+], #4
 2000494:	79ecc008 	ldw	r19, [sp+], #8
 2000498:	79ed000c 	ldw	r20, [sp+], #12
 200049c:	79ed4010 	ldw	r21, [sp+], #16
 20004a0:	79ed8014 	ldw	r22, [sp+], #20
 20004a4:	79edc018 	ldw	r23, [sp+], #24
 20004a8:	79ee001c 	ldw	r24, [sp+], #28
 20004ac:	79ee4020 	ldw	r25, [sp+], #32
 20004b0:	79ee8024 	ldw	sl, [sp+], #36
 20004b4:	79eec028 	ldw	fp, [sp+], #40
 20004b8:	79ef002c 	ldw	ip, [sp+], #44
 20004bc:	28ef4030 	add	sp, sp, #48	; 0x30
 20004c0:	10ffc13c 	jump	ip

020004c4 <main>:
 20004c4:	24ef4004 	sub	sp, sp, #4	; 0x4
 20004c8:	78ef8000 	stw	lr, [sp+]
 20004cc:	24ef400c 	sub	sp, sp, #12	; 0xc
 20004d0:	1a000000 	nop			(mov r0,r0)
 20004d4:	79fb8050 	ldw	r14, [pc+], #80	; 2000528 <main+0x64>
 20004d8:	79700000 	ldw	r0, [r14+]
 20004dc:	79704004 	ldw	r1, [r14+], #4
 20004e0:	79708008 	ldw	r2, [r14+], #8
 20004e4:	78e80000 	stw	r0, [sp+]
 20004e8:	78e84004 	stw	r1, [sp+], #4
 20004ec:	78e88008 	stw	r2, [sp+], #8
 20004f0:	3a004000 	mov	r1, #0	; 0x0
 20004f4:	3a008003 	mov	r2, #3	; 0x3
 20004f8:	1a00001d 	mov	r0, sp
 20004fc:	bdffff37 	b.l	20001dc <quicksort>
 2000500:	79e80000 	ldw	r0, [sp+]
 2000504:	bdfffedd 	b.l	200007c <sys_putint>
 2000508:	79e80004 	ldw	r0, [sp+], #4
 200050c:	bdfffedb 	b.l	200007c <sys_putint>
 2000510:	79e80008 	ldw	r0, [sp+], #8
 2000514:	bdfffed9 	b.l	200007c <sys_putint>
 2000518:	28ef400c 	add	sp, sp, #12	; 0xc
 200051c:	79ef0000 	ldw	ip, [sp+]
 2000520:	28ef4004 	add	sp, sp, #4	; 0x4
 2000524:	10ffc13c 	jump	ip
 2000528:	0200057c 	.word	0x0200057c

0200052c <_start>:
 200052c:	79fb8048 	ldw	r14, [pc+], #72	; 2000578 <_start+0x4c>
 2000530:	79700000 	ldw	r0, [r14+]
 2000534:	79704004 	ldw	r1, [r14+], #4
 2000538:	79708008 	ldw	r2, [r14+], #8
 200053c:	78e80000 	stw	r0, [sp+]
 2000540:	78e84004 	stw	r1, [sp+], #4
 2000544:	78e88008 	stw	r2, [sp+], #8
 2000548:	3a004000 	mov	r1, #0	; 0x0
 200054c:	3a008003 	mov	r2, #3	; 0x3
 2000550:	1a00001d 	mov	r0, sp
 2000554:	bdffff21 	b.l	20001dc <quicksort>
 2000558:	79e80000 	ldw	r0, [sp+]
 200055c:	bdfffec7 	b.l	200007c <sys_putint>
 2000560:	79e80004 	ldw	r0, [sp+], #4
 2000564:	bdfffec5 	b.l	200007c <sys_putint>
 2000568:	79e80008 	ldw	r0, [sp+], #8
 200056c:	bdfffec3 	b.l	200007c <sys_putint>
 2000570:	3a000000 	mov	r0, #0	; 0x0
 2000574:	bdfffeb7 	b.l	2000054 <sys_exit>
 2000578:	0200057c 	.word	0x0200057c
