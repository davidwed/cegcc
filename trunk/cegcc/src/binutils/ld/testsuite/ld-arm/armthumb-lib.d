
tmpdir/armthumb-lib.so:     file format elf32-(little|big)arm
architecture: arm, flags 0x00000150:
HAS_SYMS, DYNAMIC, D_PAGED
start address 0x.*

Disassembly of section .plt:

.* <.plt>:
 .*:	e52de004 	str	lr, \[sp, #-4\]!
 .*:	e59fe004 	ldr	lr, \[pc, #4\]	; .* <\.plt\+0x10>
 .*:	e08fe00e 	add	lr, pc, lr
 .*:	e5bef008 	ldr	pc, \[lr, #8\]!
 .*:	.*
 .*:	e28fc6.* 	add	ip, pc, #.*	; 0x.*
 .*:	e28cca.* 	add	ip, ip, #.*	; 0x.*
 .*:	e5bcf.* 	ldr	pc, \[ip, #.*\]!
Disassembly of section .text:

.* <lib_func1>:
 .*:	e1a0c00d 	mov	ip, sp
 .*:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
 .*:	ebfffff. 	bl	.* <.text-0x..>
 .*:	e89d6800 	ldmia	sp, {fp, sp, lr}
 .*:	e12fff1e 	bx	lr
 .*:	e1a00000 	nop			\(mov r0,r0\)
 .*:	e1a00000 	nop			\(mov r0,r0\)
 .*:	e1a00000 	nop			\(mov r0,r0\)

.* <__real_lib_func2>:
 .*:	4770      	bx	lr
 .*:	46c0      	nop			\(mov r8, r8\)
 .*:	46c0      	nop			\(mov r8, r8\)
 .*:	46c0      	nop			\(mov r8, r8\)
 .*:	46c0      	nop			\(mov r8, r8\)
 .*:	46c0      	nop			\(mov r8, r8\)
 .*:	46c0      	nop			\(mov r8, r8\)
 .*:	46c0      	nop			\(mov r8, r8\)

.* <lib_func2>:
 .*:	e59fc004 	ldr	ip, \[pc, #4\]	; 33c <lib_func2\+0xc>
 .*:	e08cc00f 	add	ip, ip, pc
 .*:	e12fff1c 	bx	ip
 .*:	ffffffe5 	.*
