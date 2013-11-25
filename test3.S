
test3:     file format elf32-littleunicore32


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

020000b4 <print_value>:
 20000b4:	70ef8004 	stw	lr, [sp-], #4
 20000b8:	70ef8004 	stw	lr, [sp-], #4
 20000bc:	70ee8008 	stw	sl, [sp-], #8
 20000c0:	70ef8004 	stw	lr, [sp-], #4
 20000c4:	70ee8008 	stw	sl, [sp-], #8
 20000c8:	24ef4008 	sub	sp, sp, #8	; 0x8
 20000cc:	1a000000 	nop			(mov r0,r0)
 20000d0:	79fe8044 	ldw	sl, [pc+], #68	; 2000118 <print_value+0x64>
 20000d4:	79d00000 	ldw	r0, [sl+]
 20000d8:	bdfffff0 	b.l	200009c <sys_putint>
 20000dc:	79d00004 	ldw	r0, [sl+], #4
 20000e0:	bdffffee 	b.l	200009c <sys_putint>
 20000e4:	79d00008 	ldw	r0, [sl+], #8
 20000e8:	bdffffec 	b.l	200009c <sys_putint>
 20000ec:	79d0000c 	ldw	r0, [sl+], #12
 20000f0:	bdffffea 	b.l	200009c <sys_putint>
 20000f4:	79d00010 	ldw	r0, [sl+], #16
 20000f8:	bdffffe8 	b.l	200009c <sys_putint>
 20000fc:	79d00014 	ldw	r0, [sl+], #20
 2000100:	bdffffe6 	b.l	200009c <sys_putint>
 2000104:	3a003781 	mov	r0, #12320	; 0x3020
 2000108:	28000019 	add	r0, r0, #25	; 0x19
 200010c:	69ee8004 	ldw.w	sl, [sp]+, #4
 2000110:	69ef8004 	ldw.w	lr, [sp]+, #4
 2000114:	bcffffe1 	b	200009c <sys_putint>
 2000118:	02008864 	.word	0x02008864

0200011c <pivotLoc>:
 200011c:	1a03c401 	mov	r15, r1 << #2
 2000120:	15080002 	cmpsub.a	r1, r2
 2000124:	5903000f 	ldw	r12, [r0+],r15
 2000128:	0803c00f 	add	r15, r0, r15
 200012c:	b400000d 	beg	2000164 <pivotLoc+0x48>
 2000130:	08038402 	add	r14, r0, r2 << #2
 2000134:	79734000 	ldw	r13, [r14+]
 2000138:	1560000d 	cmpsub.a	r12, r13
 200013c:	b800000c 	bsg	2000170 <pivotLoc+0x54>
 2000140:	24108001 	sub	r2, r2, #1	; 0x1
 2000144:	24738004 	sub	r14, r14, #4	; 0x4
 2000148:	15100001 	cmpsub.a	r2, r1
 200014c:	b8fffff9 	bsg	2000134 <pivotLoc+0x18>
 2000150:	1a03c001 	mov	r15, r1
 2000154:	1a00400f 	mov	r1, r15
 2000158:	1510000f 	cmpsub.a	r2, r15
 200015c:	b8fffff4 	bsg	2000130 <pivotLoc+0x14>
 2000160:	0803c40f 	add	r15, r0, r15 << #2
 2000164:	787b0000 	stw	r12, [r15+]
 2000168:	1a000001 	mov	r0, r1
 200016c:	10ffc13e 	jump	lr
 2000170:	280bc001 	add	r15, r1, #1	; 0x1
 2000174:	58034401 	stw	r13, [r0+],r1 << #2
 2000178:	15780002 	cmpsub.a	r15, r2
 200017c:	b4fffff5 	beg	2000154 <pivotLoc+0x38>
 2000180:	5903440f 	ldw	r13, [r0+],r15 << #2
 2000184:	1560000d 	cmpsub.a	r12, r13
 2000188:	b600000a 	bsl	20001b4 <pivotLoc+0x98>
 200018c:	28084002 	add	r1, r1, #2	; 0x2
 2000190:	08004401 	add	r1, r0, r1 << #2
 2000194:	bc000003 	b	20001a4 <pivotLoc+0x88>
 2000198:	690b4004 	ldw.w	r13, [r1]+, #4
 200019c:	1560000d 	cmpsub.a	r12, r13
 20001a0:	b6000004 	bsl	20001b4 <pivotLoc+0x98>
 20001a4:	287bc001 	add	r15, r15, #1	; 0x1
 20001a8:	15780002 	cmpsub.a	r15, r2
 20001ac:	b6fffffa 	bsl	2000198 <pivotLoc+0x7c>
 20001b0:	bcffffe8 	b	2000154 <pivotLoc+0x38>
 20001b4:	78734000 	stw	r13, [r14+]
 20001b8:	24108001 	sub	r2, r2, #1	; 0x1
 20001bc:	1a00400f 	mov	r1, r15
 20001c0:	bcffffe5 	b	2000158 <pivotLoc+0x3c>

020001c4 <quickSort>:
 20001c4:	70ef8004 	stw	lr, [sp-], #4
 20001c8:	70eec008 	stw	fp, [sp-], #8
 20001cc:	70ee800c 	stw	sl, [sp-], #12
 20001d0:	70ee4010 	stw	r25, [sp-], #16
 20001d4:	70ee0014 	stw	r24, [sp-], #20
 20001d8:	70edc018 	stw	r23, [sp-], #24
 20001dc:	70ed801c 	stw	r22, [sp-], #28
 20001e0:	70ed4020 	stw	r21, [sp-], #32
 20001e4:	70ed0024 	stw	r20, [sp-], #36
 20001e8:	70ecc028 	stw	r19, [sp-], #40
 20001ec:	70ec802c 	stw	r18, [sp-], #44
 20001f0:	70ec802c 	stw	r18, [sp-], #44
 20001f4:	70ec4030 	stw	r17, [sp-], #48
 20001f8:	70ec802c 	stw	r18, [sp-], #44
 20001fc:	70ec4030 	stw	r17, [sp-], #48
 2000200:	24ef4030 	sub	sp, sp, #48	; 0x30
 2000204:	24ef4010 	sub	sp, sp, #16	; 0x10
 2000208:	79fd85f0 	ldw	r22, [pc+], #1520	; 20007fc <quickSort+0x638>
 200020c:	1a060000 	mov	r24, r0
 2000210:	1a064002 	mov	r25, r2
 2000214:	3a068000 	mov	sl, #0	; 0x0
 2000218:	59b0001a 	ldw	r0, [r22+],sl
 200021c:	28d68004 	add	sl, sl, #4	; 0x4
 2000220:	78e84000 	stw	r1, [sp+]
 2000224:	bdffff9d 	b.l	200009c <sys_putint>
 2000228:	35d00018 	cmpsub.a	sl, #24	; 0x18
 200022c:	79e84000 	ldw	r1, [sp+]
 2000230:	a2fffff9 	bne	2000218 <quickSort+0x54>
 2000234:	3a003781 	mov	r0, #12320	; 0x3020
 2000238:	28000019 	add	r0, r0, #25	; 0x19
 200023c:	bdffff97 	b.l	200009c <sys_putint>
 2000240:	79e84000 	ldw	r1, [sp+]
 2000244:	15080019 	cmpsub.a	r1, r25
 2000248:	b4000015 	beg	20002a0 <quickSort+0xdc>
 200024c:	1a04c001 	mov	r19, r1
 2000250:	59c34401 	ldw	r13, [r24+],r1 << #2
 2000254:	1a03c019 	mov	r15, r25
 2000258:	08c3840f 	add	r14, r24, r15 << #2
 200025c:	79730000 	ldw	r12, [r14+]
 2000260:	1568000c 	cmpsub.a	r13, r12
 2000264:	b800001d 	bsg	20002dc <quickSort+0x118>
 2000268:	247bc001 	sub	r15, r15, #1	; 0x1
 200026c:	24738004 	sub	r14, r14, #4	; 0x4
 2000270:	15780013 	cmpsub.a	r15, r19
 2000274:	b8fffff9 	bsg	200025c <quickSort+0x98>
 2000278:	08c2c413 	add	r11, r24, r19 << #2
 200027c:	1a03800b 	mov	r14, r11
 2000280:	1598000f 	cmpsub.a	r19, r15
 2000284:	b400001f 	beg	2000304 <quickSort+0x140>
 2000288:	795b0000 	ldw	r12, [r11+]
 200028c:	285ac004 	add	r11, r11, #4	; 0x4
 2000290:	1568000c 	cmpsub.a	r13, r12
 2000294:	b6000016 	bsl	20002f0 <quickSort+0x12c>
 2000298:	289cc001 	add	r19, r19, #1	; 0x1
 200029c:	bcfffff7 	b	200027c <quickSort+0xb8>
 20002a0:	28ef4010 	add	sp, sp, #16	; 0x10
 20002a4:	79ec4000 	ldw	r17, [sp+]
 20002a8:	79ec8004 	ldw	r18, [sp+], #4
 20002ac:	79ecc008 	ldw	r19, [sp+], #8
 20002b0:	79ed000c 	ldw	r20, [sp+], #12
 20002b4:	79ed4010 	ldw	r21, [sp+], #16
 20002b8:	79ed8014 	ldw	r22, [sp+], #20
 20002bc:	79edc018 	ldw	r23, [sp+], #24
 20002c0:	79ee001c 	ldw	r24, [sp+], #28
 20002c4:	79ee4020 	ldw	r25, [sp+], #32
 20002c8:	79ee8024 	ldw	sl, [sp+], #36
 20002cc:	79eec028 	ldw	fp, [sp+], #40
 20002d0:	79ef002c 	ldw	ip, [sp+], #44
 20002d4:	28ef4030 	add	sp, sp, #48	; 0x30
 20002d8:	10ffc13c 	jump	ip
 20002dc:	15780013 	cmpsub.a	r15, r19
 20002e0:	baffffe5 	bel	2000278 <quickSort+0xb4>
 20002e4:	58c30413 	stw	r12, [r24+],r19 << #2
 20002e8:	289cc001 	add	r19, r19, #1	; 0x1
 20002ec:	bcffffe2 	b	2000278 <quickSort+0xb4>
 20002f0:	58c3040f 	stw	r12, [r24+],r15 << #2
 20002f4:	247bc001 	sub	r15, r15, #1	; 0x1
 20002f8:	15780013 	cmpsub.a	r15, r19
 20002fc:	b8ffffd6 	bsg	2000258 <quickSort+0x94>
 2000300:	bc000001 	b	2000308 <quickSort+0x144>
 2000304:	08c38413 	add	r14, r24, r19 << #2
 2000308:	249ec001 	sub	fp, r19, #1	; 0x1
 200030c:	78734000 	stw	r13, [r14+]
 2000310:	3a068000 	mov	sl, #0	; 0x0
 2000314:	1a000000 	nop			(mov r0,r0)
 2000318:	59b0001a 	ldw	r0, [r22+],sl
 200031c:	28d68004 	add	sl, sl, #4	; 0x4
 2000320:	78e84000 	stw	r1, [sp+]
 2000324:	bdffff5d 	b.l	200009c <sys_putint>
 2000328:	35d00018 	cmpsub.a	sl, #24	; 0x18
 200032c:	79e84000 	ldw	r1, [sp+]
 2000330:	a2fffff8 	bne	2000314 <quickSort+0x150>
 2000334:	3a003781 	mov	r0, #12320	; 0x3020
 2000338:	28000019 	add	r0, r0, #25	; 0x19
 200033c:	bdffff57 	b.l	200009c <sys_putint>
 2000340:	79e84000 	ldw	r1, [sp+]
 2000344:	15d80001 	cmpsub.a	fp, r1
 2000348:	ba0000b2 	bel	2000614 <quickSort+0x450>
 200034c:	1a048001 	mov	r18, r1
 2000350:	59c34401 	ldw	r13, [r24+],r1 << #2
 2000354:	1a03c01b 	mov	r15, fp
 2000358:	08c3840f 	add	r14, r24, r15 << #2
 200035c:	bc000004 	b	2000370 <quickSort+0x1ac>
 2000360:	247bc001 	sub	r15, r15, #1	; 0x1
 2000364:	24738004 	sub	r14, r14, #4	; 0x4
 2000368:	15780012 	cmpsub.a	r15, r18
 200036c:	ba000007 	bel	200038c <quickSort+0x1c8>
 2000370:	79730000 	ldw	r12, [r14+]
 2000374:	1568000c 	cmpsub.a	r13, r12
 2000378:	bafffff9 	bel	2000360 <quickSort+0x19c>
 200037c:	15780012 	cmpsub.a	r15, r18
 2000380:	ba000002 	bel	200038c <quickSort+0x1c8>
 2000384:	58c30412 	stw	r12, [r24+],r18 << #2
 2000388:	28948001 	add	r18, r18, #1	; 0x1
 200038c:	08c2c412 	add	r11, r24, r18 << #2
 2000390:	bc000005 	b	20003a8 <quickSort+0x1e4>
 2000394:	795b0000 	ldw	r12, [r11+]
 2000398:	285ac004 	add	r11, r11, #4	; 0x4
 200039c:	1568000c 	cmpsub.a	r13, r12
 20003a0:	b600009e 	bsl	200061c <quickSort+0x458>
 20003a4:	28948001 	add	r18, r18, #1	; 0x1
 20003a8:	1a03800b 	mov	r14, r11
 20003ac:	1590000f 	cmpsub.a	r18, r15
 20003b0:	b6fffff8 	bsl	2000394 <quickSort+0x1d0>
 20003b4:	08c38412 	add	r14, r24, r18 << #2
 20003b8:	2493c001 	sub	r15, r18, #1	; 0x1
 20003bc:	78734000 	stw	r13, [r14+]
 20003c0:	78ebc00c 	stw	r15, [sp+], #12
 20003c4:	3a068000 	mov	sl, #0	; 0x0
 20003c8:	1a000000 	nop			(mov r0,r0)
 20003cc:	59b0001a 	ldw	r0, [r22+],sl
 20003d0:	28d68004 	add	sl, sl, #4	; 0x4
 20003d4:	78e84000 	stw	r1, [sp+]
 20003d8:	bdffff30 	b.l	200009c <sys_putint>
 20003dc:	35d00018 	cmpsub.a	sl, #24	; 0x18
 20003e0:	79e84000 	ldw	r1, [sp+]
 20003e4:	a2fffff8 	bne	20003c8 <quickSort+0x204>
 20003e8:	3a003781 	mov	r0, #12320	; 0x3020
 20003ec:	28000019 	add	r0, r0, #25	; 0x19
 20003f0:	bdffff2a 	b.l	200009c <sys_putint>
 20003f4:	79e84000 	ldw	r1, [sp+]
 20003f8:	79ebc00c 	ldw	r15, [sp+], #12
 20003fc:	15780001 	cmpsub.a	r15, r1
 2000400:	ba00008b 	bel	2000630 <quickSort+0x46c>
 2000404:	1a044001 	mov	r17, r1
 2000408:	59c34401 	ldw	r13, [r24+],r1 << #2
 200040c:	08c3040f 	add	r12, r24, r15 << #2
 2000410:	bc000004 	b	2000424 <quickSort+0x260>
 2000414:	247bc001 	sub	r15, r15, #1	; 0x1
 2000418:	24630004 	sub	r12, r12, #4	; 0x4
 200041c:	15780011 	cmpsub.a	r15, r17
 2000420:	ba000019 	bel	2000488 <quickSort+0x2c4>
 2000424:	7962c000 	ldw	r11, [r12+]
 2000428:	1568000b 	cmpsub.a	r13, r11
 200042c:	bafffff9 	bel	2000414 <quickSort+0x250>
 2000430:	15780011 	cmpsub.a	r15, r17
 2000434:	ba000014 	bel	2000488 <quickSort+0x2c4>
 2000438:	288b8001 	add	r14, r17, #1	; 0x1
 200043c:	58c2c411 	stw	r11, [r24+],r17 << #2
 2000440:	1570000f 	cmpsub.a	r14, r15
 2000444:	b400000f 	beg	2000484 <quickSort+0x2c0>
 2000448:	1a02840e 	mov	r10, r14 << #2
 200044c:	59c2c00a 	ldw	r11, [r24+],r10
 2000450:	08c2800a 	add	r10, r24, r10
 2000454:	1568000b 	cmpsub.a	r13, r11
 2000458:	b60000e4 	bsl	20007ec <quickSort+0x628>
 200045c:	288a4002 	add	r9, r17, #2	; 0x2
 2000460:	08c24409 	add	r9, r24, r9 << #2
 2000464:	bc000004 	b	2000478 <quickSort+0x2b4>
 2000468:	1a028009 	mov	r10, r9
 200046c:	694ac004 	ldw.w	r11, [r9]+, #4
 2000470:	1568000b 	cmpsub.a	r13, r11
 2000474:	b60000dd 	bsl	20007ec <quickSort+0x628>
 2000478:	28738001 	add	r14, r14, #1	; 0x1
 200047c:	1570000f 	cmpsub.a	r14, r15
 2000480:	b6fffff9 	bsl	2000468 <quickSort+0x2a4>
 2000484:	1a04400e 	mov	r17, r14
 2000488:	08c28411 	add	r10, r24, r17 << #2
 200048c:	15780011 	cmpsub.a	r15, r17
 2000490:	b8ffffde 	bsg	200040c <quickSort+0x248>
 2000494:	248bc001 	sub	r15, r17, #1	; 0x1
 2000498:	78534000 	stw	r13, [r10+]
 200049c:	78ebc008 	stw	r15, [sp+], #8
 20004a0:	3a068000 	mov	sl, #0	; 0x0
 20004a4:	1a000000 	nop			(mov r0,r0)
 20004a8:	59b0001a 	ldw	r0, [r22+],sl
 20004ac:	28d68004 	add	sl, sl, #4	; 0x4
 20004b0:	78e84000 	stw	r1, [sp+]
 20004b4:	bdfffef9 	b.l	200009c <sys_putint>
 20004b8:	35d00018 	cmpsub.a	sl, #24	; 0x18
 20004bc:	79e84000 	ldw	r1, [sp+]
 20004c0:	a2fffff8 	bne	20004a4 <quickSort+0x2e0>
 20004c4:	3a003781 	mov	r0, #12320	; 0x3020
 20004c8:	28000019 	add	r0, r0, #25	; 0x19
 20004cc:	bdfffef3 	b.l	200009c <sys_putint>
 20004d0:	79e84000 	ldw	r1, [sp+]
 20004d4:	79ebc008 	ldw	r15, [sp+], #8
 20004d8:	15780001 	cmpsub.a	r15, r1
 20004dc:	ba0000c1 	bel	20007e4 <quickSort+0x620>
 20004e0:	1a054001 	mov	r21, r1
 20004e4:	59c2c401 	ldw	r11, [r24+],r1 << #2
 20004e8:	08c3840f 	add	r14, r24, r15 << #2
 20004ec:	bc000004 	b	2000500 <quickSort+0x33c>
 20004f0:	247bc001 	sub	r15, r15, #1	; 0x1
 20004f4:	24738004 	sub	r14, r14, #4	; 0x4
 20004f8:	15780015 	cmpsub.a	r15, r21
 20004fc:	ba000019 	bel	2000564 <quickSort+0x3a0>
 2000500:	79734000 	ldw	r13, [r14+]
 2000504:	1558000d 	cmpsub.a	r11, r13
 2000508:	bafffff9 	bel	20004f0 <quickSort+0x32c>
 200050c:	15780015 	cmpsub.a	r15, r21
 2000510:	ba000014 	bel	2000564 <quickSort+0x3a0>
 2000514:	28ab0001 	add	r12, r21, #1	; 0x1
 2000518:	58c34415 	stw	r13, [r24+],r21 << #2
 200051c:	1560000f 	cmpsub.a	r12, r15
 2000520:	b40000ae 	beg	20007dc <quickSort+0x618>
 2000524:	1a02440c 	mov	r9, r12 << #2
 2000528:	59c28009 	ldw	r10, [r24+],r9
 200052c:	08c24009 	add	r9, r24, r9
 2000530:	1558000a 	cmpsub.a	r11, r10
 2000534:	b60000a3 	bsl	20007c4 <quickSort+0x600>
 2000538:	28ab4002 	add	r13, r21, #2	; 0x2
 200053c:	08c3440d 	add	r13, r24, r13 << #2
 2000540:	bc000005 	b	2000558 <quickSort+0x394>
 2000544:	1a02400d 	mov	r9, r13
 2000548:	696a8004 	ldw.w	r10, [r13]+, #4
 200054c:	1a030015 	mov	r12, r21
 2000550:	1558000a 	cmpsub.a	r11, r10
 2000554:	b600009a 	bsl	20007c0 <quickSort+0x5fc>
 2000558:	28654001 	add	r21, r12, #1	; 0x1
 200055c:	15a8000f 	cmpsub.a	r21, r15
 2000560:	b6fffff8 	bsl	2000544 <quickSort+0x380>
 2000564:	08c24415 	add	r9, r24, r21 << #2
 2000568:	15780015 	cmpsub.a	r15, r21
 200056c:	b8ffffde 	bsg	20004e8 <quickSort+0x324>
 2000570:	24abc001 	sub	r15, r21, #1	; 0x1
 2000574:	784ac000 	stw	r11, [r9+]
 2000578:	78ebc004 	stw	r15, [sp+], #4
 200057c:	1a000000 	nop			(mov r0,r0)
 2000580:	1a000000 	nop			(mov r0,r0)
 2000584:	79b00000 	ldw	r0, [r22+]
 2000588:	78e84000 	stw	r1, [sp+]
 200058c:	bdfffec3 	b.l	200009c <sys_putint>
 2000590:	79b00004 	ldw	r0, [r22+], #4
 2000594:	bdfffec1 	b.l	200009c <sys_putint>
 2000598:	79b00008 	ldw	r0, [r22+], #8
 200059c:	bdfffebf 	b.l	200009c <sys_putint>
 20005a0:	79b0000c 	ldw	r0, [r22+], #12
 20005a4:	bdfffebd 	b.l	200009c <sys_putint>
 20005a8:	79b00010 	ldw	r0, [r22+], #16
 20005ac:	bdfffebb 	b.l	200009c <sys_putint>
 20005b0:	79b00014 	ldw	r0, [r22+], #20
 20005b4:	bdfffeb9 	b.l	200009c <sys_putint>
 20005b8:	3a003781 	mov	r0, #12320	; 0x3020
 20005bc:	28000019 	add	r0, r0, #25	; 0x19
 20005c0:	bdfffeb6 	b.l	200009c <sys_putint>
 20005c4:	79e84000 	ldw	r1, [sp+]
 20005c8:	79ebc004 	ldw	r15, [sp+], #4
 20005cc:	15780001 	cmpsub.a	r15, r1
 20005d0:	ba000080 	bel	20007d4 <quickSort+0x610>
 20005d4:	1a028001 	mov	r10, r1
 20005d8:	59c2c401 	ldw	r11, [r24+],r1 << #2
 20005dc:	08c3840f 	add	r14, r24, r15 << #2
 20005e0:	79734000 	ldw	r13, [r14+]
 20005e4:	1558000d 	cmpsub.a	r11, r13
 20005e8:	b8000013 	bsg	2000638 <quickSort+0x474>
 20005ec:	247bc001 	sub	r15, r15, #1	; 0x1
 20005f0:	24738004 	sub	r14, r14, #4	; 0x4
 20005f4:	1578000a 	cmpsub.a	r15, r10
 20005f8:	b8fffff9 	bsg	20005e0 <quickSort+0x41c>
 20005fc:	1a05c00a 	mov	r23, r10
 2000600:	08c24417 	add	r9, r24, r23 << #2
 2000604:	15b8000f 	cmpsub.a	r23, r15
 2000608:	b4000025 	beg	20006a0 <quickSort+0x4dc>
 200060c:	1a028017 	mov	r10, r23
 2000610:	bcfffff2 	b	20005dc <quickSort+0x418>
 2000614:	28984001 	add	r1, r19, #1	; 0x1
 2000618:	bcfffefe 	b	2000214 <quickSort+0x50>
 200061c:	58c3040f 	stw	r12, [r24+],r15 << #2
 2000620:	247bc001 	sub	r15, r15, #1	; 0x1
 2000624:	15780012 	cmpsub.a	r15, r18
 2000628:	b8ffff4b 	bsg	2000358 <quickSort+0x194>
 200062c:	bcffff62 	b	20003b8 <quickSort+0x1f4>
 2000630:	28904001 	add	r1, r18, #1	; 0x1
 2000634:	bcffff36 	b	2000310 <quickSort+0x14c>
 2000638:	1578000a 	cmpsub.a	r15, r10
 200063c:	baffffef 	bel	20005fc <quickSort+0x438>
 2000640:	2855c001 	add	r23, r10, #1	; 0x1
 2000644:	58c3440a 	stw	r13, [r24+],r10 << #2
 2000648:	15b8000f 	cmpsub.a	r23, r15
 200064c:	b4ffffec 	beg	2000600 <quickSort+0x43c>
 2000650:	1a024417 	mov	r9, r23 << #2
 2000654:	59c30009 	ldw	r12, [r24+],r9
 2000658:	08c24009 	add	r9, r24, r9
 200065c:	1558000c 	cmpsub.a	r11, r12
 2000660:	b600000b 	bsl	2000690 <quickSort+0x4cc>
 2000664:	28534002 	add	r13, r10, #2	; 0x2
 2000668:	08c3440d 	add	r13, r24, r13 << #2
 200066c:	bc000004 	b	2000680 <quickSort+0x4bc>
 2000670:	1a02400d 	mov	r9, r13
 2000674:	696b0004 	ldw.w	r12, [r13]+, #4
 2000678:	1558000c 	cmpsub.a	r11, r12
 200067c:	b6000004 	bsl	2000690 <quickSort+0x4cc>
 2000680:	28bdc001 	add	r23, r23, #1	; 0x1
 2000684:	15b8000f 	cmpsub.a	r23, r15
 2000688:	b6fffff9 	bsl	2000670 <quickSort+0x4ac>
 200068c:	bcffffdc 	b	2000600 <quickSort+0x43c>
 2000690:	247bc001 	sub	r15, r15, #1	; 0x1
 2000694:	78730000 	stw	r12, [r14+]
 2000698:	15b8000f 	cmpsub.a	r23, r15
 200069c:	b6ffffdb 	bsl	200060c <quickSort+0x448>
 20006a0:	24bd0001 	sub	r20, r23, #1	; 0x1
 20006a4:	784ac000 	stw	r11, [r9+]
 20006a8:	79b00000 	ldw	r0, [r22+]
 20006ac:	78e84000 	stw	r1, [sp+]
 20006b0:	bdfffe7a 	b.l	200009c <sys_putint>
 20006b4:	79b00004 	ldw	r0, [r22+], #4
 20006b8:	bdfffe78 	b.l	200009c <sys_putint>
 20006bc:	79b00008 	ldw	r0, [r22+], #8
 20006c0:	bdfffe76 	b.l	200009c <sys_putint>
 20006c4:	79b0000c 	ldw	r0, [r22+], #12
 20006c8:	bdfffe74 	b.l	200009c <sys_putint>
 20006cc:	79b00010 	ldw	r0, [r22+], #16
 20006d0:	bdfffe72 	b.l	200009c <sys_putint>
 20006d4:	79b00014 	ldw	r0, [r22+], #20
 20006d8:	bdfffe70 	b.l	200009c <sys_putint>
 20006dc:	3a003781 	mov	r0, #12320	; 0x3020
 20006e0:	28000019 	add	r0, r0, #25	; 0x19
 20006e4:	bdfffe6d 	b.l	200009c <sys_putint>
 20006e8:	79e84000 	ldw	r1, [sp+]
 20006ec:	15a00001 	cmpsub.a	r20, r1
 20006f0:	ba000031 	bel	20007b8 <quickSort+0x5f4>
 20006f4:	1a034001 	mov	r13, r1
 20006f8:	59c2c401 	ldw	r11, [r24+],r1 << #2
 20006fc:	1a03c014 	mov	r15, r20
 2000700:	08c3840f 	add	r14, r24, r15 << #2
 2000704:	79730000 	ldw	r12, [r14+]
 2000708:	1558000c 	cmpsub.a	r11, r12
 200070c:	b800000a 	bsg	2000738 <quickSort+0x574>
 2000710:	247bc001 	sub	r15, r15, #1	; 0x1
 2000714:	24738004 	sub	r14, r14, #4	; 0x4
 2000718:	1578000d 	cmpsub.a	r15, r13
 200071c:	b8fffff9 	bsg	2000704 <quickSort+0x540>
 2000720:	1a06800d 	mov	sl, r13
 2000724:	08c2841a 	add	r10, r24, sl << #2
 2000728:	1578001a 	cmpsub.a	r15, sl
 200072c:	ba00001c 	bel	20007a0 <quickSort+0x5dc>
 2000730:	1a03401a 	mov	r13, sl
 2000734:	bcfffff2 	b	2000700 <quickSort+0x53c>
 2000738:	1578000d 	cmpsub.a	r15, r13
 200073c:	bafffff8 	bel	2000720 <quickSort+0x55c>
 2000740:	286e8001 	add	sl, r13, #1	; 0x1
 2000744:	58c3040d 	stw	r12, [r24+],r13 << #2
 2000748:	15d0000f 	cmpsub.a	sl, r15
 200074c:	b4fffff5 	beg	2000724 <quickSort+0x560>
 2000750:	1a02841a 	mov	r10, sl << #2
 2000754:	59c3000a 	ldw	r12, [r24+],r10
 2000758:	08c2800a 	add	r10, r24, r10
 200075c:	1558000c 	cmpsub.a	r11, r12
 2000760:	b600000b 	bsl	2000790 <quickSort+0x5cc>
 2000764:	286b4002 	add	r13, r13, #2	; 0x2
 2000768:	08c3440d 	add	r13, r24, r13 << #2
 200076c:	bc000004 	b	2000780 <quickSort+0x5bc>
 2000770:	1a02800d 	mov	r10, r13
 2000774:	696b0004 	ldw.w	r12, [r13]+, #4
 2000778:	1558000c 	cmpsub.a	r11, r12
 200077c:	b6000004 	bsl	2000790 <quickSort+0x5cc>
 2000780:	28d68001 	add	sl, sl, #1	; 0x1
 2000784:	15d0000f 	cmpsub.a	sl, r15
 2000788:	b6fffff9 	bsl	2000770 <quickSort+0x5ac>
 200078c:	bcffffe5 	b	2000724 <quickSort+0x560>
 2000790:	247bc001 	sub	r15, r15, #1	; 0x1
 2000794:	78730000 	stw	r12, [r14+]
 2000798:	1578001a 	cmpsub.a	r15, sl
 200079c:	b8ffffe4 	bsg	2000730 <quickSort+0x56c>
 20007a0:	7852c000 	stw	r11, [r10+]
 20007a4:	1a000018 	mov	r0, r24
 20007a8:	24d08001 	sub	r2, sl, #1	; 0x1
 20007ac:	bdfffe85 	b.l	20001c4 <quickSort>
 20007b0:	28d04001 	add	r1, sl, #1	; 0x1
 20007b4:	bcffffbc 	b	20006a8 <quickSort+0x4e4>
 20007b8:	28b84001 	add	r1, r23, #1	; 0x1
 20007bc:	bcffff6f 	b	200057c <quickSort+0x3b8>
 20007c0:	1a030015 	mov	r12, r21
 20007c4:	78728000 	stw	r10, [r14+]
 20007c8:	247bc001 	sub	r15, r15, #1	; 0x1
 20007cc:	1a05400c 	mov	r21, r12
 20007d0:	bcffff65 	b	2000568 <quickSort+0x3a4>
 20007d4:	28a84001 	add	r1, r21, #1	; 0x1
 20007d8:	bcffff31 	b	20004a0 <quickSort+0x2dc>
 20007dc:	1a05400c 	mov	r21, r12
 20007e0:	bcffff60 	b	2000564 <quickSort+0x3a0>
 20007e4:	28884001 	add	r1, r17, #1	; 0x1
 20007e8:	bcfffef6 	b	20003c4 <quickSort+0x200>
 20007ec:	7862c000 	stw	r11, [r12+]
 20007f0:	247bc001 	sub	r15, r15, #1	; 0x1
 20007f4:	1a04400e 	mov	r17, r14
 20007f8:	bcffff24 	b	200048c <quickSort+0x2c8>
 20007fc:	02008864 	.word	0x02008864

02000800 <main>:
 2000800:	70ef8004 	stw	lr, [sp-], #4
 2000804:	70ef8004 	stw	lr, [sp-], #4
 2000808:	70ee8008 	stw	sl, [sp-], #8
 200080c:	70ef8004 	stw	lr, [sp-], #4
 2000810:	70ee8008 	stw	sl, [sp-], #8
 2000814:	24ef4008 	sub	sp, sp, #8	; 0x8
 2000818:	1a000000 	nop			(mov r0,r0)
 200081c:	79fe8020 	ldw	sl, [pc+], #32	; 2000840 <main+0x40>
 2000820:	3a004000 	mov	r1, #0	; 0x0
 2000824:	1a00001a 	mov	r0, sl
 2000828:	3a008006 	mov	r2, #6	; 0x6
 200082c:	bdfffe65 	b.l	20001c4 <quickSort>
 2000830:	79d00000 	ldw	r0, [sl+]
 2000834:	69ee8004 	ldw.w	sl, [sp]+, #4
 2000838:	69ef0004 	ldw.w	ip, [sp]+, #4
 200083c:	10ffc13c 	jump	ip
 2000840:	02008864 	.word	0x02008864

02000844 <_start>:
 2000844:	79fe8018 	ldw	sl, [pc+], #24	; 2000860 <_start+0x1c>
 2000848:	3a004000 	mov	r1, #0	; 0x0
 200084c:	1a00001a 	mov	r0, sl
 2000850:	3a008006 	mov	r2, #6	; 0x6
 2000854:	bdfffe5b 	b.l	20001c4 <quickSort>
 2000858:	79d00000 	ldw	r0, [sl+]
 200085c:	bcfffe05 	b	2000074 <sys_exit>
 2000860:	02008864 	.word	0x02008864
