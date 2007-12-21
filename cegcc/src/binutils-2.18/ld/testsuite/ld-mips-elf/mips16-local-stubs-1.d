#name: MIPS16 interlinking for local functions 1
#source: mips16-local-stubs-1.s
#as: -mips4
#ld: -Ttext 0x20000000 -e caller1
#objdump: -dr
#...
Disassembly of section \.text:

20000000 <f1>:
20000000:	03e00008 	jr	ra
20000004:	00000000 	nop

20000008 <g1>:
20000008:	03e00008 	jr	ra
2000000c:	00000000 	nop

20000010 <h1>:
20000010:	e820      	jr	ra
20000012:	6500      	nop

20000014 <f2>:
20000014:	03e00008 	jr	ra
20000018:	00000000 	nop

2000001c <g2>:
2000001c:	03e00008 	jr	ra
20000020:	00000000 	nop

20000024 <h2>:
20000024:	e820      	jr	ra
20000026:	6500      	nop

20000028 <f3>:
20000028:	03e00008 	jr	ra
2000002c:	00000000 	nop

20000030 <g3>:
20000030:	03e00008 	jr	ra
20000034:	00000000 	nop

20000038 <h3>:
20000038:	e820      	jr	ra
2000003a:	6500      	nop

2000003c <caller1>:
2000003c:	0c000000 	jal	20000000 <f1>
20000040:	00000000 	nop
20000044:	0c000005 	jal	20000014 <f2>
20000048:	00000000 	nop
2000004c:	0c000002 	jal	20000008 <g1>
20000050:	00000000 	nop
20000054:	0c000007 	jal	2000001c <g2>
20000058:	00000000 	nop
2000005c:	0c000024 	jal	20000090 <stub_for_h1>
20000060:	00000000 	nop
20000064:	0c000028 	jal	200000a0 <stub_for_h2>
20000068:	00000000 	nop

2000006c <caller2>:
2000006c:	1c00 0030 	jalx	200000c0 <stub_for_f1>
20000070:	6500      	nop
20000072:	1c00 0038 	jalx	200000e0 <stub_for_f2>
20000076:	6500      	nop
20000078:	1c00 0034 	jalx	200000d0 <stub_for_g1>
2000007c:	6500      	nop
2000007e:	1c00 003c 	jalx	200000f0 <stub_for_g2>
20000082:	6500      	nop
20000084:	1800 0004 	jal	20000010 <h1>
20000088:	6500      	nop
2000008a:	1800 0009 	jal	20000024 <h2>
2000008e:	6500      	nop

20000090 <stub_for_h1>:
20000090:	3c012000 	lui	at,0x2000
20000094:	24210011 	addiu	at,at,17
20000098:	00200008 	jr	at
2000009c:	00000000 	nop

200000a0 <stub_for_h2>:
200000a0:	3c012000 	lui	at,0x2000
200000a4:	24210025 	addiu	at,at,37
200000a8:	00200008 	jr	at
200000ac:	00000000 	nop

# This isn't actually called, but is referenced from the .pdr section.
200000b0 <stub_for_h3>:
200000b0:	3c012000 	lui	at,0x2000
200000b4:	24210039 	addiu	at,at,57
200000b8:	00200008 	jr	at
200000bc:	00000000 	nop

200000c0 <stub_for_f1>:
200000c0:	3c012000 	lui	at,0x2000
200000c4:	24210000 	addiu	at,at,0
200000c8:	00200008 	jr	at
200000cc:	00000000 	nop

200000d0 <stub_for_g1>:
200000d0:	3c012000 	lui	at,0x2000
200000d4:	24210008 	addiu	at,at,8
200000d8:	00200008 	jr	at
200000dc:	00000000 	nop

200000e0 <stub_for_f2>:
200000e0:	3c012000 	lui	at,0x2000
200000e4:	24210014 	addiu	at,at,20
200000e8:	00200008 	jr	at
200000ec:	00000000 	nop

200000f0 <stub_for_g2>:
200000f0:	3c012000 	lui	at,0x2000
200000f4:	2421001c 	addiu	at,at,28
200000f8:	00200008 	jr	at
200000fc:	00000000 	nop
