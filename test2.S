
test2:     file format elf32-littleunicore32


Disassembly of section .text:

02000074 <main>:
 2000074:	1a07001d 	mov	ip, sp
 2000078:	70efc004 	stw	pc, [sp-], #4
 200007c:	70ef8008 	stw	lr, [sp-], #8
 2000080:	70ef000c 	stw	ip, [sp-], #12
 2000084:	70ef000c 	stw	ip, [sp-], #12
 2000088:	70eec010 	stw	fp, [sp-], #16
 200008c:	70ef000c 	stw	ip, [sp-], #12
 2000090:	70eec010 	stw	fp, [sp-], #16
 2000094:	24ef4010 	sub	sp, sp, #16	; 0x10
 2000098:	24e6c004 	sub	fp, ip, #4	; 0x4
 200009c:	79fbc024 	ldw	r15, [pc+], #36	; 20000c4 <main+0x50>
 20000a0:	3a038001 	mov	r14, #1	; 0x1
 20000a4:	787b8000 	stw	r14, [r15+]
 20000a8:	3a03c001 	mov	r15, #1	; 0x1
 20000ac:	1a00000f 	mov	r0, r15
 20000b0:	1a07001b 	mov	ip, fp
 20000b4:	71dec00c 	ldw	fp, [fp-], #12
 20000b8:	71e74008 	ldw	sp, [ip-], #8
 20000bc:	71e70004 	ldw	ip, [ip-], #4
 20000c0:	10ffc13c 	jump	ip
 20000c4:	020080c8 	.word	0x020080c8

Disassembly of section .bss:

020080c8 <__data_start>:
 20080c8:	00000000 	.word	0x00000000

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
