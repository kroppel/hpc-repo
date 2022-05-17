
build/copy.o:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000000000 <copy_c>:
   0:	d10083ff 	sub	sp, sp, #0x20
   4:	f90007e0 	str	x0, [sp, #8]
   8:	f90003e1 	str	x1, [sp]
   c:	b9001fff 	str	wzr, [sp, #28]
  10:	1400000f 	b	4c <copy_c+0x4c>
  14:	b9801fe0 	ldrsw	x0, [sp, #28]
  18:	d37ef400 	lsl	x0, x0, #2
  1c:	f94007e1 	ldr	x1, [sp, #8]
  20:	8b000020 	add	x0, x1, x0
  24:	b9400002 	ldr	w2, [x0]
  28:	b9801fe0 	ldrsw	x0, [sp, #28]
  2c:	d37df000 	lsl	x0, x0, #3
  30:	f94003e1 	ldr	x1, [sp]
  34:	8b000020 	add	x0, x1, x0
  38:	2a0203e1 	mov	w1, w2
  3c:	f9000001 	str	x1, [x0]
  40:	b9401fe0 	ldr	w0, [sp, #28]
  44:	11000400 	add	w0, w0, #0x1
  48:	b9001fe0 	str	w0, [sp, #28]
  4c:	b9401fe0 	ldr	w0, [sp, #28]
  50:	7100181f 	cmp	w0, #0x6
  54:	54fffe0d 	b.le	14 <copy_c+0x14>
  58:	d503201f 	nop
  5c:	910083ff 	add	sp, sp, #0x20
  60:	d65f03c0 	ret

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	43434700 	.inst	0x43434700 ; undefined
   4:	4728203a 	.inst	0x4728203a ; undefined
   8:	2029554e 	.inst	0x2029554e ; undefined
   c:	2e332e38 	uqsub	v24.8b, v17.8b, v19.8b
  10:	30322031 	adr	x17, 64415 <copy_c+0x64415>
  14:	31313931 	adds	w17, w9, #0xc4e
  18:	28203132 	stnp	w18, w12, [x9, #-256]
  1c:	20646552 	.inst	0x20646552 ; undefined
  20:	20746148 	.inst	0x20746148 ; undefined
  24:	2e332e38 	uqsub	v24.8b, v17.8b, v19.8b
  28:	29352d31 	stp	w17, w11, [x9, #-88]
	...

Disassembly of section .eh_frame:

0000000000000000 <.eh_frame>:
   0:	00000010 	.inst	0x00000010 ; undefined
   4:	00000000 	.inst	0x00000000 ; undefined
   8:	00527a01 	.inst	0x00527a01 ; undefined
   c:	011e7804 	.inst	0x011e7804 ; undefined
  10:	001f0c1b 	.inst	0x001f0c1b ; undefined
  14:	00000018 	.word	0x00000018
  18:	00000018 	.word	0x00000018
  1c:	00000000 	.word	0x00000000
  20:	00000064 	.word	0x00000064
  24:	200e4100 	.word	0x200e4100
  28:	00000e57 	.word	0x00000e57
  2c:	00000000 	.word	0x00000000
