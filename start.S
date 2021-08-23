/*
 * Copyright (C) 2021 Lino
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

.macro	switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, 0xc
	b.eq	\el3_label
	cmp	\xreg, 0x8
	b.eq	\el2_label
	cmp	\xreg, 0x4
	b.eq	\el1_label
.endm

.macro armv8_switch_to_el1_m, xreg1, xreg2
	mrs	\xreg1, cnthctl_el2
	orr	\xreg1, \xreg1, #0x3
	msr	cnthctl_el2, \xreg1
	msr	cntvoff_el2, xzr

	mrs	\xreg1, midr_el1
	mrs	\xreg2, mpidr_el1
	msr	vpidr_el2, \xreg1
	msr	vmpidr_el2, \xreg2

	mov	\xreg1, #0x33ff
	msr	cptr_el2, \xreg1
	msr	hstr_el2, xzr
	mov	\xreg1, #3 << 20
	msr	cpacr_el1, \xreg1

	mov	\xreg1, #(1 << 31)|(1<<29)
	msr	hcr_el2, \xreg1

	mov	\xreg1, #0x0800
	movk \xreg1, #0x30d0, lsl #16
	msr	sctlr_el1, \xreg1

	mov	\xreg1, #0x3c5
	msr	spsr_el2, \xreg1
	adr	\xreg1, 9f
	msr	elr_el2, \xreg1
	eret
9:
	.endm

.section ".text.boot"

.globl _start
_start:
	mrs   x1, mpidr_el1
	and   x1, x1, #3
    cbz   x1, 1f
    // cpu id > 0, stop
4:  wfe
    b     4b

1:	ldr	  x0, =_vectors
	msr	  vbar_el2, x0
	ldr	  x0, =_start
	mov	  sp, x0

    ldr   x1, =__bss_start
    ldr   w2, =__bss_size
4:  cbz   w2, 5f
    str   xzr, [x1], #8
    sub   w2, w2, #1
    cbnz  w2, 4b

5:	msr   daifclr, #15
	bl    main
    b     5b

    .align 11
    .globl	_vectors
_vectors:
	.align 7
    b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub

	.align 7
    b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub

	.align 7
    b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub

	.align 7
    b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub
	.align 7
	b	UnexpectedStub

.globl	UnexpectedStub
UnexpectedStub:
	bl	_exception_entry
	bl  exc_handler
	b 	_exception_exit

_exception_entry:
	stp	x29, x30, [sp, #-16]!
	stp	x27, x28, [sp, #-16]!
	stp	x25, x26, [sp, #-16]!
	stp	x23, x24, [sp, #-16]!
	stp	x21, x22, [sp, #-16]!
	stp	x19, x20, [sp, #-16]!
	stp	x17, x18, [sp, #-16]!
	stp	x15, x16, [sp, #-16]!
	stp	x13, x14, [sp, #-16]!
	stp	x11, x12, [sp, #-16]!
	stp	x9, x10, [sp, #-16]!
	stp	x7, x8, [sp, #-16]!
	stp	x5, x6, [sp, #-16]!
	stp	x3, x4, [sp, #-16]!
	stp	x1, x2, [sp, #-16]!

	mrs	x1, esr_el2
	mrs	x2, elr_el2
	mrs	x3, daif
	mrs	x4, vbar_el2
	mrs	x5, spsr_el2
	sub	x6, sp, #(8*30)
	mrs	x7, sctlr_el2
	mrs	x8, hcr_el2
	mrs	x9, ttbr0_el2

	stp x2, x0, [sp, #-16]!
	stp	x3, x1, [sp, #-16]!
	stp	x5, x4, [sp, #-16]!
	stp	x7, x6, [sp, #-16]!
	stp	x9, x8, [sp, #-16]!
	mov	x0, sp
	ret

_exception_exit:
	add	sp, sp, #(8*8)
	ldp	x2, x0, [sp],#16

	msr	elr_el2, x2

	ldp	x1, x2, [sp],#16
	ldp	x3, x4, [sp],#16
	ldp	x5, x6, [sp],#16
	ldp	x7, x8, [sp],#16
	ldp	x9, x10, [sp],#16
	ldp	x11, x12, [sp],#16
	ldp	x13, x14, [sp],#16
	ldp	x15, x16, [sp],#16
	ldp	x17, x18, [sp],#16
	ldp	x19, x20, [sp],#16
	ldp	x21, x22, [sp],#16
	ldp	x23, x24, [sp],#16
	ldp	x25, x26, [sp],#16
	ldp	x27, x28, [sp],#16
	ldp	x29, x30, [sp],#16
	eret

/*
2:	mrs	x0, CurrentEL
	cmp	x0, #4
	beq	3f
	ldr x1, =_start
	msr	sp_el1, x1
	ldr	x0, =_vectors
	msr	vbar_el2, x0
	armv8_switch_to_el1_m x0, x1
*/

/*
	mrs	  x1, cnthctl_el2
	orr	  x1, x1, #0x3
	msr	  cnthctl_el2, x1
	msr	  cntvoff_el2, xzr
	mrs	  x1, midr_el1
	mrs	  x2, mpidr_el1
	msr	  vpidr_el2, x1
	msr	  vmpidr_el2, x2
	mov	  x2, #0x33ff
	msr	  cptr_el2, x2
	msr	  hstr_el2, xzr
	mov	  x2, #3 << 20
	msr	  cpacr_el1, x2
	mov   x2, #(1 << 31)|(1 << 29)
	orr   x2, x2, #(1 << 1)
	msr   hcr_el2, x2
	mov	  x2, #0x0800
	movk  x2, #0x30d0, lsl #16
	msr	  sctlr_el1, x2
	mov   x0, #0x3c5
	msr   spsr_el2, x0
	ldr   x0, =start1
	msr   elr_el2, x0
	eret
*/