
test3:     file format elf32-littleunicore32


Disassembly of section .text:

02000054 <pivotLoc>:
 2000054:	1a03c401 	mov	r15, r1 << #2
 2000058:	15080002 	cmpsub.a	r1, r2
 200005c:	5903000f 	ldw	r12, [r0+],r15
 2000060:	0803c00f 	add	r15, r0, r15
 2000064:	b400000d 	beg	200009c <pivotLoc+0x48>
 2000068:	08038402 	add	r14, r0, r2 << #2
 200006c:	79734000 	ldw	r13, [r14+]
 2000070:	1560000d 	cmpsub.a	r12, r13
 2000074:	b800000c 	bsg	20000a8 <pivotLoc+0x54>
 2000078:	24108001 	sub	r2, r2, #1	; 0x1
 200007c:	24738004 	sub	r14, r14, #4	; 0x4
 2000080:	15100001 	cmpsub.a	r2, r1
 2000084:	b8fffff9 	bsg	200006c <pivotLoc+0x18>
 2000088:	1a03c001 	mov	r15, r1
 200008c:	1a00400f 	mov	r1, r15
 2000090:	1510000f 	cmpsub.a	r2, r15
 2000094:	b8fffff4 	bsg	2000068 <pivotLoc+0x14>
 2000098:	0803c40f 	add	r15, r0, r15 << #2
 200009c:	787b0000 	stw	r12, [r15+]
 20000a0:	1a000001 	mov	r0, r1
 20000a4:	10ffc13e 	jump	lr
 20000a8:	280bc001 	add	r15, r1, #1	; 0x1
 20000ac:	58034401 	stw	r13, [r0+],r1 << #2
 20000b0:	15780002 	cmpsub.a	r15, r2
 20000b4:	b4fffff5 	beg	200008c <pivotLoc+0x38>
 20000b8:	5903440f 	ldw	r13, [r0+],r15 << #2
 20000bc:	1560000d 	cmpsub.a	r12, r13
 20000c0:	b600000a 	bsl	20000ec <pivotLoc+0x98>
 20000c4:	28084002 	add	r1, r1, #2	; 0x2
 20000c8:	08004401 	add	r1, r0, r1 << #2
 20000cc:	bc000003 	b	20000dc <pivotLoc+0x88>
 20000d0:	690b4004 	ldw.w	r13, [r1]+, #4
 20000d4:	1560000d 	cmpsub.a	r12, r13
 20000d8:	b6000004 	bsl	20000ec <pivotLoc+0x98>
 20000dc:	287bc001 	add	r15, r15, #1	; 0x1
 20000e0:	15780002 	cmpsub.a	r15, r2
 20000e4:	b6fffffa 	bsl	20000d0 <pivotLoc+0x7c>
 20000e8:	bcffffe8 	b	200008c <pivotLoc+0x38>
 20000ec:	78734000 	stw	r13, [r14+]
 20000f0:	24108001 	sub	r2, r2, #1	; 0x1
 20000f4:	1a00400f 	mov	r1, r15
 20000f8:	bcffffe5 	b	2000090 <pivotLoc+0x3c>

020000fc <quickSort>:
 20000fc:	70ef8004 	stw	lr, [sp-], #4
 2000100:	70eec008 	stw	fp, [sp-], #8
 2000104:	70ee800c 	stw	sl, [sp-], #12
 2000108:	70ee4010 	stw	r25, [sp-], #16
 200010c:	70ee0014 	stw	r24, [sp-], #20
 2000110:	70edc018 	stw	r23, [sp-], #24
 2000114:	70ed801c 	stw	r22, [sp-], #28
 2000118:	70ed4020 	stw	r21, [sp-], #32
 200011c:	70ed0024 	stw	r20, [sp-], #36
 2000120:	70ecc028 	stw	r19, [sp-], #40
 2000124:	70ec802c 	stw	r18, [sp-], #44
 2000128:	70ec802c 	stw	r18, [sp-], #44
 200012c:	70ec4030 	stw	r17, [sp-], #48
 2000130:	70ec802c 	stw	r18, [sp-], #44
 2000134:	70ec4030 	stw	r17, [sp-], #48
 2000138:	24ef4030 	sub	sp, sp, #48	; 0x30
 200013c:	24ef4020 	sub	sp, sp, #32	; 0x20
 2000140:	1a060000 	mov	r24, r0
 2000144:	78e8801c 	stw	r2, [sp+], #28
 2000148:	79ebc01c 	ldw	r15, [sp+], #28
 200014c:	1508000f 	cmpsub.a	r1, r15
 2000150:	b4000014 	beg	20001a4 <quickSort+0xa8>
 2000154:	1a04c001 	mov	r19, r1
 2000158:	59c34401 	ldw	r13, [r24+],r1 << #2
 200015c:	08c3840f 	add	r14, r24, r15 << #2
 2000160:	79730000 	ldw	r12, [r14+]
 2000164:	1568000c 	cmpsub.a	r13, r12
 2000168:	b800001d 	bsg	20001e0 <quickSort+0xe4>
 200016c:	247bc001 	sub	r15, r15, #1	; 0x1
 2000170:	24738004 	sub	r14, r14, #4	; 0x4
 2000174:	15780013 	cmpsub.a	r15, r19
 2000178:	b8fffff9 	bsg	2000160 <quickSort+0x64>
 200017c:	08c2c413 	add	r11, r24, r19 << #2
 2000180:	1a03800b 	mov	r14, r11
 2000184:	1598000f 	cmpsub.a	r19, r15
 2000188:	b400001f 	beg	2000208 <quickSort+0x10c>
 200018c:	795b0000 	ldw	r12, [r11+]
 2000190:	285ac004 	add	r11, r11, #4	; 0x4
 2000194:	1568000c 	cmpsub.a	r13, r12
 2000198:	b6000016 	bsl	20001f4 <quickSort+0xf8>
 200019c:	289cc001 	add	r19, r19, #1	; 0x1
 20001a0:	bcfffff7 	b	2000180 <quickSort+0x84>
 20001a4:	28ef4020 	add	sp, sp, #32	; 0x20
 20001a8:	79ec4000 	ldw	r17, [sp+]
 20001ac:	79ec8004 	ldw	r18, [sp+], #4
 20001b0:	79ecc008 	ldw	r19, [sp+], #8
 20001b4:	79ed000c 	ldw	r20, [sp+], #12
 20001b8:	79ed4010 	ldw	r21, [sp+], #16
 20001bc:	79ed8014 	ldw	r22, [sp+], #20
 20001c0:	79edc018 	ldw	r23, [sp+], #24
 20001c4:	79ee001c 	ldw	r24, [sp+], #28
 20001c8:	79ee4020 	ldw	r25, [sp+], #32
 20001cc:	79ee8024 	ldw	sl, [sp+], #36
 20001d0:	79eec028 	ldw	fp, [sp+], #40
 20001d4:	79ef002c 	ldw	ip, [sp+], #44
 20001d8:	28ef4030 	add	sp, sp, #48	; 0x30
 20001dc:	10ffc13c 	jump	ip
 20001e0:	15780013 	cmpsub.a	r15, r19
 20001e4:	baffffe5 	bel	200017c <quickSort+0x80>
 20001e8:	58c30413 	stw	r12, [r24+],r19 << #2
 20001ec:	289cc001 	add	r19, r19, #1	; 0x1
 20001f0:	bcffffe2 	b	200017c <quickSort+0x80>
 20001f4:	58c3040f 	stw	r12, [r24+],r15 << #2
 20001f8:	247bc001 	sub	r15, r15, #1	; 0x1
 20001fc:	15780013 	cmpsub.a	r15, r19
 2000200:	b8ffffd6 	bsg	200015c <quickSort+0x60>
 2000204:	bc000001 	b	200020c <quickSort+0x110>
 2000208:	08c38413 	add	r14, r24, r19 << #2
 200020c:	249bc001 	sub	r15, r19, #1	; 0x1
 2000210:	78734000 	stw	r13, [r14+]
 2000214:	78ebc018 	stw	r15, [sp+], #24
 2000218:	1a000000 	nop			(mov r0,r0)
 200021c:	1a000000 	nop			(mov r0,r0)
 2000220:	79ebc018 	ldw	r15, [sp+], #24
 2000224:	15780001 	cmpsub.a	r15, r1
 2000228:	ba000014 	bel	200027c <quickSort+0x180>
 200022c:	1a048001 	mov	r18, r1
 2000230:	59c34401 	ldw	r13, [r24+],r1 << #2
 2000234:	08c3840f 	add	r14, r24, r15 << #2
 2000238:	79730000 	ldw	r12, [r14+]
 200023c:	1568000c 	cmpsub.a	r13, r12
 2000240:	b8000010 	bsg	2000284 <quickSort+0x188>
 2000244:	247bc001 	sub	r15, r15, #1	; 0x1
 2000248:	24738004 	sub	r14, r14, #4	; 0x4
 200024c:	15780012 	cmpsub.a	r15, r18
 2000250:	b8fffff9 	bsg	2000238 <quickSort+0x13c>
 2000254:	08c2c412 	add	r11, r24, r18 << #2
 2000258:	1a03800b 	mov	r14, r11
 200025c:	15780012 	cmpsub.a	r15, r18
 2000260:	ba000012 	bel	20002ac <quickSort+0x1b0>
 2000264:	795b0000 	ldw	r12, [r11+]
 2000268:	285ac004 	add	r11, r11, #4	; 0x4
 200026c:	1568000c 	cmpsub.a	r13, r12
 2000270:	b6000009 	bsl	2000298 <quickSort+0x19c>
 2000274:	28948001 	add	r18, r18, #1	; 0x1
 2000278:	bcfffff7 	b	2000258 <quickSort+0x15c>
 200027c:	28984001 	add	r1, r19, #1	; 0x1
 2000280:	bcffffb1 	b	2000148 <quickSort+0x4c>
 2000284:	15780012 	cmpsub.a	r15, r18
 2000288:	bafffff2 	bel	2000254 <quickSort+0x158>
 200028c:	58c30412 	stw	r12, [r24+],r18 << #2
 2000290:	28948001 	add	r18, r18, #1	; 0x1
 2000294:	bcffffef 	b	2000254 <quickSort+0x158>
 2000298:	58c3040f 	stw	r12, [r24+],r15 << #2
 200029c:	247bc001 	sub	r15, r15, #1	; 0x1
 20002a0:	15780012 	cmpsub.a	r15, r18
 20002a4:	b8ffffe3 	bsg	2000234 <quickSort+0x138>
 20002a8:	bc000001 	b	20002b0 <quickSort+0x1b4>
 20002ac:	08c38412 	add	r14, r24, r18 << #2
 20002b0:	2493c001 	sub	r15, r18, #1	; 0x1
 20002b4:	78734000 	stw	r13, [r14+]
 20002b8:	78ebc014 	stw	r15, [sp+], #20
 20002bc:	1a000000 	nop			(mov r0,r0)
 20002c0:	1a000000 	nop			(mov r0,r0)
 20002c4:	79ebc014 	ldw	r15, [sp+], #20
 20002c8:	15780001 	cmpsub.a	r15, r1
 20002cc:	ba000014 	bel	2000320 <quickSort+0x224>
 20002d0:	1a044001 	mov	r17, r1
 20002d4:	59c34401 	ldw	r13, [r24+],r1 << #2
 20002d8:	08c3840f 	add	r14, r24, r15 << #2
 20002dc:	79730000 	ldw	r12, [r14+]
 20002e0:	1568000c 	cmpsub.a	r13, r12
 20002e4:	b8000010 	bsg	2000328 <quickSort+0x22c>
 20002e8:	247bc001 	sub	r15, r15, #1	; 0x1
 20002ec:	24738004 	sub	r14, r14, #4	; 0x4
 20002f0:	15780011 	cmpsub.a	r15, r17
 20002f4:	b8fffff9 	bsg	20002dc <quickSort+0x1e0>
 20002f8:	08c2c411 	add	r11, r24, r17 << #2
 20002fc:	1a03800b 	mov	r14, r11
 2000300:	15780011 	cmpsub.a	r15, r17
 2000304:	ba000012 	bel	2000350 <quickSort+0x254>
 2000308:	795b0000 	ldw	r12, [r11+]
 200030c:	285ac004 	add	r11, r11, #4	; 0x4
 2000310:	1568000c 	cmpsub.a	r13, r12
 2000314:	b6000009 	bsl	200033c <quickSort+0x240>
 2000318:	288c4001 	add	r17, r17, #1	; 0x1
 200031c:	bcfffff7 	b	20002fc <quickSort+0x200>
 2000320:	28904001 	add	r1, r18, #1	; 0x1
 2000324:	bcffffbc 	b	2000218 <quickSort+0x11c>
 2000328:	15780011 	cmpsub.a	r15, r17
 200032c:	bafffff2 	bel	20002f8 <quickSort+0x1fc>
 2000330:	58c30411 	stw	r12, [r24+],r17 << #2
 2000334:	288c4001 	add	r17, r17, #1	; 0x1
 2000338:	bcffffef 	b	20002f8 <quickSort+0x1fc>
 200033c:	58c3040f 	stw	r12, [r24+],r15 << #2
 2000340:	247bc001 	sub	r15, r15, #1	; 0x1
 2000344:	15780011 	cmpsub.a	r15, r17
 2000348:	b8ffffe3 	bsg	20002d8 <quickSort+0x1dc>
 200034c:	bc000001 	b	2000354 <quickSort+0x258>
 2000350:	08c38411 	add	r14, r24, r17 << #2
 2000354:	248bc001 	sub	r15, r17, #1	; 0x1
 2000358:	78734000 	stw	r13, [r14+]
 200035c:	78ebc010 	stw	r15, [sp+], #16
 2000360:	1a000000 	nop			(mov r0,r0)
 2000364:	1a000000 	nop			(mov r0,r0)
 2000368:	79ebc010 	ldw	r15, [sp+], #16
 200036c:	15780001 	cmpsub.a	r15, r1
 2000370:	ba000014 	bel	20003c4 <quickSort+0x2c8>
 2000374:	1a064001 	mov	r25, r1
 2000378:	59c34401 	ldw	r13, [r24+],r1 << #2
 200037c:	08c3840f 	add	r14, r24, r15 << #2
 2000380:	79730000 	ldw	r12, [r14+]
 2000384:	1568000c 	cmpsub.a	r13, r12
 2000388:	b8000010 	bsg	20003cc <quickSort+0x2d0>
 200038c:	247bc001 	sub	r15, r15, #1	; 0x1
 2000390:	24738004 	sub	r14, r14, #4	; 0x4
 2000394:	15780019 	cmpsub.a	r15, r25
 2000398:	b8fffff9 	bsg	2000380 <quickSort+0x284>
 200039c:	08c2c419 	add	r11, r24, r25 << #2
 20003a0:	1a03800b 	mov	r14, r11
 20003a4:	15c8000f 	cmpsub.a	r25, r15
 20003a8:	b4000012 	beg	20003f4 <quickSort+0x2f8>
 20003ac:	795b0000 	ldw	r12, [r11+]
 20003b0:	285ac004 	add	r11, r11, #4	; 0x4
 20003b4:	1568000c 	cmpsub.a	r13, r12
 20003b8:	b6000009 	bsl	20003e0 <quickSort+0x2e4>
 20003bc:	28ce4001 	add	r25, r25, #1	; 0x1
 20003c0:	bcfffff7 	b	20003a0 <quickSort+0x2a4>
 20003c4:	28884001 	add	r1, r17, #1	; 0x1
 20003c8:	bcffffbc 	b	20002bc <quickSort+0x1c0>
 20003cc:	15780019 	cmpsub.a	r15, r25
 20003d0:	bafffff2 	bel	200039c <quickSort+0x2a0>
 20003d4:	58c30419 	stw	r12, [r24+],r25 << #2
 20003d8:	28ce4001 	add	r25, r25, #1	; 0x1
 20003dc:	bcffffef 	b	200039c <quickSort+0x2a0>
 20003e0:	58c3040f 	stw	r12, [r24+],r15 << #2
 20003e4:	247bc001 	sub	r15, r15, #1	; 0x1
 20003e8:	15780019 	cmpsub.a	r15, r25
 20003ec:	b8ffffe3 	bsg	200037c <quickSort+0x280>
 20003f0:	bc000001 	b	20003f8 <quickSort+0x2fc>
 20003f4:	08c38419 	add	r14, r24, r25 << #2
 20003f8:	24cbc001 	sub	r15, r25, #1	; 0x1
 20003fc:	78734000 	stw	r13, [r14+]
 2000400:	78ebc00c 	stw	r15, [sp+], #12
 2000404:	1a000000 	nop			(mov r0,r0)
 2000408:	1a000000 	nop			(mov r0,r0)
 200040c:	79ebc00c 	ldw	r15, [sp+], #12
 2000410:	15780001 	cmpsub.a	r15, r1
 2000414:	ba00008a 	bel	2000640 <quickSort+0x544>
 2000418:	1a06c001 	mov	fp, r1
 200041c:	59c34401 	ldw	r13, [r24+],r1 << #2
 2000420:	08c3840f 	add	r14, r24, r15 << #2
 2000424:	bc000004 	b	2000438 <quickSort+0x33c>
 2000428:	247bc001 	sub	r15, r15, #1	; 0x1
 200042c:	24738004 	sub	r14, r14, #4	; 0x4
 2000430:	1578001b 	cmpsub.a	r15, fp
 2000434:	ba000007 	bel	2000454 <quickSort+0x358>
 2000438:	79730000 	ldw	r12, [r14+]
 200043c:	1568000c 	cmpsub.a	r13, r12
 2000440:	bafffff9 	bel	2000428 <quickSort+0x32c>
 2000444:	1578001b 	cmpsub.a	r15, fp
 2000448:	ba000002 	bel	2000454 <quickSort+0x358>
 200044c:	58c3041b 	stw	r12, [r24+],fp << #2
 2000450:	28dec001 	add	fp, fp, #1	; 0x1
 2000454:	08c2c41b 	add	r11, r24, fp << #2
 2000458:	bc000005 	b	2000470 <quickSort+0x374>
 200045c:	795b0000 	ldw	r12, [r11+]
 2000460:	285ac004 	add	r11, r11, #4	; 0x4
 2000464:	1568000c 	cmpsub.a	r13, r12
 2000468:	b6000077 	bsl	2000648 <quickSort+0x54c>
 200046c:	28dec001 	add	fp, fp, #1	; 0x1
 2000470:	1a03800b 	mov	r14, r11
 2000474:	15d8000f 	cmpsub.a	fp, r15
 2000478:	b6fffff8 	bsl	200045c <quickSort+0x360>
 200047c:	08c3841b 	add	r14, r24, fp << #2
 2000480:	24dbc001 	sub	r15, fp, #1	; 0x1
 2000484:	78734000 	stw	r13, [r14+]
 2000488:	78ebc008 	stw	r15, [sp+], #8
 200048c:	1a000000 	nop			(mov r0,r0)
 2000490:	1a000000 	nop			(mov r0,r0)
 2000494:	79ebc008 	ldw	r15, [sp+], #8
 2000498:	15780001 	cmpsub.a	r15, r1
 200049c:	ba00006f 	bel	200065c <quickSort+0x560>
 20004a0:	1a050001 	mov	r20, r1
 20004a4:	59c34401 	ldw	r13, [r24+],r1 << #2
 20004a8:	08c3040f 	add	r12, r24, r15 << #2
 20004ac:	bc000004 	b	20004c0 <quickSort+0x3c4>
 20004b0:	247bc001 	sub	r15, r15, #1	; 0x1
 20004b4:	24630004 	sub	r12, r12, #4	; 0x4
 20004b8:	15780014 	cmpsub.a	r15, r20
 20004bc:	ba000019 	bel	2000524 <quickSort+0x428>
 20004c0:	7962c000 	ldw	r11, [r12+]
 20004c4:	1568000b 	cmpsub.a	r13, r11
 20004c8:	bafffff9 	bel	20004b0 <quickSort+0x3b4>
 20004cc:	15780014 	cmpsub.a	r15, r20
 20004d0:	ba000014 	bel	2000524 <quickSort+0x428>
 20004d4:	28a38001 	add	r14, r20, #1	; 0x1
 20004d8:	58c2c414 	stw	r11, [r24+],r20 << #2
 20004dc:	1570000f 	cmpsub.a	r14, r15
 20004e0:	b40000c2 	beg	20007ec <quickSort+0x6f0>
 20004e4:	1a02840e 	mov	r10, r14 << #2
 20004e8:	59c2c00a 	ldw	r11, [r24+],r10
 20004ec:	08c2800a 	add	r10, r24, r10
 20004f0:	1568000b 	cmpsub.a	r13, r11
 20004f4:	b60000b9 	bsl	20007dc <quickSort+0x6e0>
 20004f8:	28a24002 	add	r9, r20, #2	; 0x2
 20004fc:	08c24409 	add	r9, r24, r9 << #2
 2000500:	bc000005 	b	2000518 <quickSort+0x41c>
 2000504:	1a028009 	mov	r10, r9
 2000508:	694ac004 	ldw.w	r11, [r9]+, #4
 200050c:	1a038014 	mov	r14, r20
 2000510:	1568000b 	cmpsub.a	r13, r11
 2000514:	b60000b0 	bsl	20007d8 <quickSort+0x6dc>
 2000518:	28750001 	add	r20, r14, #1	; 0x1
 200051c:	15a0000f 	cmpsub.a	r20, r15
 2000520:	b6fffff8 	bsl	2000504 <quickSort+0x408>
 2000524:	08c28414 	add	r10, r24, r20 << #2
 2000528:	15780014 	cmpsub.a	r15, r20
 200052c:	b8ffffde 	bsg	20004a8 <quickSort+0x3ac>
 2000530:	24a3c001 	sub	r15, r20, #1	; 0x1
 2000534:	78534000 	stw	r13, [r10+]
 2000538:	78ebc004 	stw	r15, [sp+], #4
 200053c:	1a000000 	nop			(mov r0,r0)
 2000540:	1a000000 	nop			(mov r0,r0)
 2000544:	79ebc004 	ldw	r15, [sp+], #4
 2000548:	15780001 	cmpsub.a	r15, r1
 200054c:	ba0000a0 	bel	20007d0 <quickSort+0x6d4>
 2000550:	1a058001 	mov	r22, r1
 2000554:	59c2c401 	ldw	r11, [r24+],r1 << #2
 2000558:	08c3840f 	add	r14, r24, r15 << #2
 200055c:	bc000004 	b	2000570 <quickSort+0x474>
 2000560:	247bc001 	sub	r15, r15, #1	; 0x1
 2000564:	24738004 	sub	r14, r14, #4	; 0x4
 2000568:	15780016 	cmpsub.a	r15, r22
 200056c:	ba000019 	bel	20005d4 <quickSort+0x4d8>
 2000570:	79734000 	ldw	r13, [r14+]
 2000574:	1558000d 	cmpsub.a	r11, r13
 2000578:	bafffff9 	bel	2000560 <quickSort+0x464>
 200057c:	15780016 	cmpsub.a	r15, r22
 2000580:	ba000014 	bel	20005d4 <quickSort+0x4d8>
 2000584:	28b30001 	add	r12, r22, #1	; 0x1
 2000588:	58c34416 	stw	r13, [r24+],r22 << #2
 200058c:	1560000f 	cmpsub.a	r12, r15
 2000590:	b400008d 	beg	20007c8 <quickSort+0x6cc>
 2000594:	1a02440c 	mov	r9, r12 << #2
 2000598:	59c28009 	ldw	r10, [r24+],r9
 200059c:	08c24009 	add	r9, r24, r9
 20005a0:	1558000a 	cmpsub.a	r11, r10
 20005a4:	b6000082 	bsl	20007b0 <quickSort+0x6b4>
 20005a8:	28b34002 	add	r13, r22, #2	; 0x2
 20005ac:	08c3440d 	add	r13, r24, r13 << #2
 20005b0:	bc000005 	b	20005c8 <quickSort+0x4cc>
 20005b4:	1a02400d 	mov	r9, r13
 20005b8:	696a8004 	ldw.w	r10, [r13]+, #4
 20005bc:	1a030016 	mov	r12, r22
 20005c0:	1558000a 	cmpsub.a	r11, r10
 20005c4:	b6000079 	bsl	20007ac <quickSort+0x6b0>
 20005c8:	28658001 	add	r22, r12, #1	; 0x1
 20005cc:	15b0000f 	cmpsub.a	r22, r15
 20005d0:	b6fffff8 	bsl	20005b4 <quickSort+0x4b8>
 20005d4:	08c24416 	add	r9, r24, r22 << #2
 20005d8:	15780016 	cmpsub.a	r15, r22
 20005dc:	b8ffffde 	bsg	2000558 <quickSort+0x45c>
 20005e0:	24b3c001 	sub	r15, r22, #1	; 0x1
 20005e4:	784ac000 	stw	r11, [r9+]
 20005e8:	78ebc000 	stw	r15, [sp+]
 20005ec:	1a000000 	nop			(mov r0,r0)
 20005f0:	1a000000 	nop			(mov r0,r0)
 20005f4:	79ebc000 	ldw	r15, [sp+]
 20005f8:	15780001 	cmpsub.a	r15, r1
 20005fc:	ba000070 	bel	20007c0 <quickSort+0x6c4>
 2000600:	1a028001 	mov	r10, r1
 2000604:	59c2c401 	ldw	r11, [r24+],r1 << #2
 2000608:	08c3840f 	add	r14, r24, r15 << #2
 200060c:	79734000 	ldw	r13, [r14+]
 2000610:	1558000d 	cmpsub.a	r11, r13
 2000614:	b8000013 	bsg	2000664 <quickSort+0x568>
 2000618:	247bc001 	sub	r15, r15, #1	; 0x1
 200061c:	24738004 	sub	r14, r14, #4	; 0x4
 2000620:	1578000a 	cmpsub.a	r15, r10
 2000624:	b8fffff9 	bsg	200060c <quickSort+0x510>
 2000628:	1a05c00a 	mov	r23, r10
 200062c:	08c24417 	add	r9, r24, r23 << #2
 2000630:	15b8000f 	cmpsub.a	r23, r15
 2000634:	b4000025 	beg	20006cc <quickSort+0x5d0>
 2000638:	1a028017 	mov	r10, r23
 200063c:	bcfffff2 	b	2000608 <quickSort+0x50c>
 2000640:	28c84001 	add	r1, r25, #1	; 0x1
 2000644:	bcffff46 	b	2000360 <quickSort+0x264>
 2000648:	58c3040f 	stw	r12, [r24+],r15 << #2
 200064c:	247bc001 	sub	r15, r15, #1	; 0x1
 2000650:	1578001b 	cmpsub.a	r15, fp
 2000654:	b8ffff72 	bsg	2000420 <quickSort+0x324>
 2000658:	bcffff89 	b	2000480 <quickSort+0x384>
 200065c:	28d84001 	add	r1, fp, #1	; 0x1
 2000660:	bcffff68 	b	2000404 <quickSort+0x308>
 2000664:	1578000a 	cmpsub.a	r15, r10
 2000668:	baffffef 	bel	2000628 <quickSort+0x52c>
 200066c:	2855c001 	add	r23, r10, #1	; 0x1
 2000670:	58c3440a 	stw	r13, [r24+],r10 << #2
 2000674:	15b8000f 	cmpsub.a	r23, r15
 2000678:	b4ffffec 	beg	200062c <quickSort+0x530>
 200067c:	1a024417 	mov	r9, r23 << #2
 2000680:	59c30009 	ldw	r12, [r24+],r9
 2000684:	08c24009 	add	r9, r24, r9
 2000688:	1558000c 	cmpsub.a	r11, r12
 200068c:	b600000b 	bsl	20006bc <quickSort+0x5c0>
 2000690:	28534002 	add	r13, r10, #2	; 0x2
 2000694:	08c3440d 	add	r13, r24, r13 << #2
 2000698:	bc000004 	b	20006ac <quickSort+0x5b0>
 200069c:	1a02400d 	mov	r9, r13
 20006a0:	696b0004 	ldw.w	r12, [r13]+, #4
 20006a4:	1558000c 	cmpsub.a	r11, r12
 20006a8:	b6000004 	bsl	20006bc <quickSort+0x5c0>
 20006ac:	28bdc001 	add	r23, r23, #1	; 0x1
 20006b0:	15b8000f 	cmpsub.a	r23, r15
 20006b4:	b6fffff9 	bsl	200069c <quickSort+0x5a0>
 20006b8:	bcffffdc 	b	200062c <quickSort+0x530>
 20006bc:	247bc001 	sub	r15, r15, #1	; 0x1
 20006c0:	78730000 	stw	r12, [r14+]
 20006c4:	15b8000f 	cmpsub.a	r23, r15
 20006c8:	b6ffffdb 	bsl	2000638 <quickSort+0x53c>
 20006cc:	24bd4001 	sub	r21, r23, #1	; 0x1
 20006d0:	784ac000 	stw	r11, [r9+]
 20006d4:	15080015 	cmpsub.a	r1, r21
 20006d8:	b4000032 	beg	20007a4 <quickSort+0x6a8>
 20006dc:	1a034001 	mov	r13, r1
 20006e0:	59c2c401 	ldw	r11, [r24+],r1 << #2
 20006e4:	1a03c015 	mov	r15, r21
 20006e8:	08c3840f 	add	r14, r24, r15 << #2
 20006ec:	79730000 	ldw	r12, [r14+]
 20006f0:	1558000c 	cmpsub.a	r11, r12
 20006f4:	b800000a 	bsg	2000720 <quickSort+0x624>
 20006f8:	247bc001 	sub	r15, r15, #1	; 0x1
 20006fc:	24738004 	sub	r14, r14, #4	; 0x4
 2000700:	1578000d 	cmpsub.a	r15, r13
 2000704:	b8fffff9 	bsg	20006ec <quickSort+0x5f0>
 2000708:	1a06800d 	mov	sl, r13
 200070c:	08c2841a 	add	r10, r24, sl << #2
 2000710:	1578001a 	cmpsub.a	r15, sl
 2000714:	ba00001c 	bel	2000788 <quickSort+0x68c>
 2000718:	1a03401a 	mov	r13, sl
 200071c:	bcfffff2 	b	20006e8 <quickSort+0x5ec>
 2000720:	1578000d 	cmpsub.a	r15, r13
 2000724:	bafffff8 	bel	2000708 <quickSort+0x60c>
 2000728:	286e8001 	add	sl, r13, #1	; 0x1
 200072c:	58c3040d 	stw	r12, [r24+],r13 << #2
 2000730:	15d0000f 	cmpsub.a	sl, r15
 2000734:	b4fffff5 	beg	200070c <quickSort+0x610>
 2000738:	1a02841a 	mov	r10, sl << #2
 200073c:	59c3000a 	ldw	r12, [r24+],r10
 2000740:	08c2800a 	add	r10, r24, r10
 2000744:	1560000b 	cmpsub.a	r12, r11
 2000748:	b800000b 	bsg	2000778 <quickSort+0x67c>
 200074c:	286b4002 	add	r13, r13, #2	; 0x2
 2000750:	08c3440d 	add	r13, r24, r13 << #2
 2000754:	bc000004 	b	2000768 <quickSort+0x66c>
 2000758:	1a02800d 	mov	r10, r13
 200075c:	696b0004 	ldw.w	r12, [r13]+, #4
 2000760:	1558000c 	cmpsub.a	r11, r12
 2000764:	b6000004 	bsl	2000778 <quickSort+0x67c>
 2000768:	28d68001 	add	sl, sl, #1	; 0x1
 200076c:	15d0000f 	cmpsub.a	sl, r15
 2000770:	b6fffff9 	bsl	2000758 <quickSort+0x65c>
 2000774:	bcffffe5 	b	200070c <quickSort+0x610>
 2000778:	247bc001 	sub	r15, r15, #1	; 0x1
 200077c:	78730000 	stw	r12, [r14+]
 2000780:	1578001a 	cmpsub.a	r15, sl
 2000784:	b8ffffe4 	bsg	2000718 <quickSort+0x61c>
 2000788:	7852c000 	stw	r11, [r10+]
 200078c:	1a000018 	mov	r0, r24
 2000790:	24d08001 	sub	r2, sl, #1	; 0x1
 2000794:	bdfffe59 	b.l	20000fc <quickSort>
 2000798:	28d04001 	add	r1, sl, #1	; 0x1
 200079c:	15a80001 	cmpsub.a	r21, r1
 20007a0:	b8ffffce 	bsg	20006dc <quickSort+0x5e0>
 20007a4:	28b84001 	add	r1, r23, #1	; 0x1
 20007a8:	bcffff90 	b	20005ec <quickSort+0x4f0>
 20007ac:	1a030016 	mov	r12, r22
 20007b0:	78728000 	stw	r10, [r14+]
 20007b4:	247bc001 	sub	r15, r15, #1	; 0x1
 20007b8:	1a05800c 	mov	r22, r12
 20007bc:	bcffff86 	b	20005d8 <quickSort+0x4dc>
 20007c0:	28b04001 	add	r1, r22, #1	; 0x1
 20007c4:	bcffff5d 	b	200053c <quickSort+0x440>
 20007c8:	1a05800c 	mov	r22, r12
 20007cc:	bcffff81 	b	20005d4 <quickSort+0x4d8>
 20007d0:	28a04001 	add	r1, r20, #1	; 0x1
 20007d4:	bcffff2d 	b	200048c <quickSort+0x390>
 20007d8:	1a038014 	mov	r14, r20
 20007dc:	7862c000 	stw	r11, [r12+]
 20007e0:	247bc001 	sub	r15, r15, #1	; 0x1
 20007e4:	1a05000e 	mov	r20, r14
 20007e8:	bcffff4f 	b	2000528 <quickSort+0x42c>
 20007ec:	1a05000e 	mov	r20, r14
 20007f0:	bcffff4c 	b	2000524 <quickSort+0x428>

020007f4 <main>:
 20007f4:	24ef4004 	sub	sp, sp, #4	; 0x4
 20007f8:	78ef8000 	stw	lr, [sp+]
 20007fc:	24ef4014 	sub	sp, sp, #20	; 0x14
 2000800:	1a000000 	nop			(mov r0,r0)
 2000804:	79fb8058 	ldw	r14, [pc+], #88	; 2000860 <main+0x6c>
 2000808:	1a03c01d 	mov	r15, sp
 200080c:	79700000 	ldw	r0, [r14+]
 2000810:	79704004 	ldw	r1, [r14+], #4
 2000814:	79708008 	ldw	r2, [r14+], #8
 2000818:	7970c00c 	ldw	r3, [r14+], #12
 200081c:	28738010 	add	r14, r14, #16	; 0x10
 2000820:	78780000 	stw	r0, [r15+]
 2000824:	78784004 	stw	r1, [r15+], #4
 2000828:	78788008 	stw	r2, [r15+], #8
 200082c:	7878c00c 	stw	r3, [r15+], #12
 2000830:	287bc010 	add	r15, r15, #16	; 0x10
 2000834:	1a00001d 	mov	r0, sp
 2000838:	3a004000 	mov	r1, #0	; 0x0
 200083c:	79738000 	ldw	r14, [r14+]
 2000840:	3a008005 	mov	r2, #5	; 0x5
 2000844:	787b8000 	stw	r14, [r15+]
 2000848:	bdfffe2c 	b.l	20000fc <quickSort>
 200084c:	79e80000 	ldw	r0, [sp+]
 2000850:	28ef4014 	add	sp, sp, #20	; 0x14
 2000854:	79ef0000 	ldw	ip, [sp+]
 2000858:	28ef4004 	add	sp, sp, #4	; 0x4
 200085c:	10ffc13c 	jump	ip
 2000860:	02000864 	.word	0x02000864
