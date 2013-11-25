
test1:     file format elf32-littleunicore32


Disassembly of section .text:

02000054 <main>:
 2000054:	1a07001d 	mov	ip, sp
 2000058:	70efc004 	stw	pc, [sp-], #4
 200005c:	70ef8008 	stw	lr, [sp-], #8
 2000060:	70ef000c 	stw	ip, [sp-], #12
 2000064:	70ef000c 	stw	ip, [sp-], #12
 2000068:	70eec010 	stw	fp, [sp-], #16
 200006c:	70ef000c 	stw	ip, [sp-], #12
 2000070:	70eec010 	stw	fp, [sp-], #16
 2000074:	24ef4010 	sub	sp, sp, #16	; 0x10
 2000078:	24e6c004 	sub	fp, ip, #4	; 0x4
 200007c:	24ef4008 	sub	sp, sp, #8	; 0x8
 2000080:	3a03c001 	mov	r15, #1	; 0x1
 2000084:	70dbc014 	stw	r15, [fp-], #20
 2000088:	3a03c002 	mov	r15, #2	; 0x2
 200008c:	70dbc010 	stw	r15, [fp-], #16
 2000090:	71db8014 	ldw	r14, [fp-], #20
 2000094:	1a000000 	nop			(mov r0,r0)
 2000098:	71dbc010 	ldw	r15, [fp-], #16
 200009c:	1570000f 	cmpsub.a	r14, r15
 20000a0:	ba000002 	bel	20000ac <main+0x58>
 20000a4:	71dbc014 	ldw	r15, [fp-], #20
 20000a8:	bc000001 	b	20000b0 <main+0x5c>
 20000ac:	71dbc010 	ldw	r15, [fp-], #16
 20000b0:	1a00000f 	mov	r0, r15
 20000b4:	1a07001b 	mov	ip, fp
 20000b8:	71dec00c 	ldw	fp, [fp-], #12
 20000bc:	71e74008 	ldw	sp, [ip-], #8
 20000c0:	71e70004 	ldw	ip, [ip-], #4
 20000c4:	10ffc13c 	jump	ip

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	undefined instruction 0x43434700
   4:	5528203a 	undefined instruction 0x5528203a
   8:	315f3443 	cmpand.a	r11, #4288	; 0x10c0
   c:	675f302e 	ldb.u	ip, [r11]-, #12334
  10:	5f616d61 	ldh.w	r5, [r12+], #705
  14:	30313032 	undefined instruction 0x30313032
  18:	36323131 	undefined instruction 0x36323131
  1c:	2e342029 	rsubc	r16, r6, #2686976	; 0x290000
  20:	00322e34 	and	r8, r6, r20 << r23

Disassembly of section .UNICORE32.attributes:

00000000 <.UNICORE32.attributes>:
   0:	00000f41 	and	r0, r0, r1 >> #7
   4:	61656100 	ldw.w	r21, [r12]-, #8448
   8:	01006962 	and.a	r1, r0, r2 >> r20
   c:	00000005 	and	r0, r0, r5
