
test4:     file format elf32-littleunicore32


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

02000094 <main>:
 2000094:	3a000001 	mov	r0, #1	; 0x1
 2000098:	bcfffff8 	b	200007c <sys_putint>

0200009c <_start>:
 200009c:	3a000001 	mov	r0, #1	; 0x1
 20000a0:	bdfffff6 	b.l	200007c <sys_putint>
 20000a4:	3a000000 	mov	r0, #0	; 0x0
 20000a8:	bcffffea 	b	2000054 <sys_exit>
