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

#include "mmu.h"

.macro	switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, 0xc
	b.eq	\el3_label
	cmp	\xreg, 0x8
	b.eq	\el2_label
	cmp	\xreg, 0x4
	b.eq	\el1_label
.endm

.macro armv8_switch_to_el1_m, ep, flag, tmp
	mrs	\tmp, cnthctl_el2
	orr	\tmp, \tmp, #(CNTHCTL_EL2_EL1PCEN_EN | CNTHCTL_EL2_EL1PCTEN_EN )
	orr	\tmp, \tmp, #(1<<10)
	orr	\tmp, \tmp, #(1<<11)
	msr	cnthctl_el2, \tmp
	msr	cntvoff_el2, xzr

	mrs	\tmp, midr_el1
	msr	vpidr_el2, \tmp
	mrs	\tmp, mpidr_el1
	msr	vmpidr_el2, \tmp

	mov	\tmp, #CPTR_EL2_RES1
	msr	cptr_el2, \tmp
	msr	hstr_el2, xzr
	mov	\tmp, #CPACR_EL1_FPEN_EN
	msr	cpacr_el1, \tmp

	#msr ttbr0_el2, \tmp
	#mrs \tmp, ttbr0_el1
	#msr ttbr1_el2, \tmp
	#mrs \tmp, ttbr1_el1

	ldr	\tmp, =(SCTLR_EL1_RES1 | SCTLR_EL1_UCI_DIS | SCTLR_EL1_EE_LE | SCTLR_EL1_WXN_DIS | SCTLR_EL1_NTWE_DIS | SCTLR_EL1_NTWI_DIS | \
			SCTLR_EL1_UCT_DIS | SCTLR_EL1_DZE_DIS |	SCTLR_EL1_ICACHE_DIS | SCTLR_EL1_UMA_DIS | SCTLR_EL1_SED_EN | SCTLR_EL1_ITD_EN | \
			SCTLR_EL1_CP15BEN_DIS | SCTLR_EL1_SA0_DIS | SCTLR_EL1_SA_DIS | SCTLR_EL1_DCACHE_DIS | SCTLR_EL1_ALIGN_DIS | SCTLR_EL1_MMU(0))
	msr	sctlr_el1, \tmp

	mov	\tmp, sp
	msr	sp_el1, \tmp
	mrs	\tmp, vbar_el2
	msr	vbar_el1, \tmp

	cmp	\flag, #ES_TO_AARCH32
	b.eq	1f

	ldr	\tmp, =(HCR_EL2_RW_AARCH64 | HCR_EL2_HCD_DIS)
	msr	hcr_el2, \tmp

	ldr	\tmp, =(SPSR_EL_DEBUG_MASK | SPSR_EL_SERR_MASK | SPSR_EL_IRQ_MASK | SPSR_EL_FIQ_MASK | SPSR_EL_M_AARCH64 | SPSR_EL_M_EL1H)
	msr	spsr_el2, \tmp
	msr elr_el2, \ep
	eret
1:
	ldr	\tmp, =(HCR_EL2_RW_AARCH32 | HCR_EL2_HCD_DIS)
	msr	hcr_el2, \tmp

	ldr	\tmp, =(SPSR_EL_END_LE | SPSR_EL_ASYN_MASK |\
			SPSR_EL_IRQ_MASK | SPSR_EL_FIQ_MASK |\
			SPSR_EL_T_A32 | SPSR_EL_M_AARCH32 |\
			SPSR_EL_M_SVC)
	msr     spsr_el2, \tmp
	msr     elr_el2, \ep
	eret
.endm

.section ".text.boot"

.globl _start
_start:
	mrs   x1, mpidr_el1
	and   x1, x1, #3
    cbz   x1, 2f
    // cpu id > 0, stop
1:  wfe
    b     1b
2:
	ldr	x5, =ES_TO_AARCH64
	ldr	x4, =_entry
	armv8_switch_to_el1_m x4, x5, x6

_entry:
	ldr	  x0, =_vectors
	msr	  vbar_el1, x0
	ldr	  x0, =_start
	mov	  sp, x0

    ldr   x1, =__bss_start
    ldr   w2, =__bss_size
5:  cbz   w2, 6f
    str   xzr, [x1], #8
    sub   w2, w2, #1
    cbnz  w2, 5b

6:	bl    main
    b     6b

    .align 11
    .globl	_vectors
_vectors:
	.align 7
    b	UnexpectedStub
	.align 7
	b	IRQStub
	.align 7
	b	FIQStub
	.align 7
	b	UnexpectedStub

	.align 7
    b	UnexpectedStub
	.align 7
	b	IRQStub
	.align 7
	b	FIQStub
	.align 7
	b	UnexpectedStub

	.align 7
    b	EmptyStub
	.align 7
	b	EmptyStub
	.align 7
	b	EmptyStub
	.align 7
	b	EmptyStub

	.align 7
    b	EmptyStub
	.align 7
	b	EmptyStub
	.align 7
	b	EmptyStub
	.align 7
	b	EmptyStub

FIQStub:
	bl	_exception_entry
	bl gic_fiq_handler
	b 	_exception_exit

IRQStub:
	bl	_exception_entry
	bl gic_irq_handler
	b 	_exception_exit

UnexpectedStub:
	bl	_exception_entry
	bl  exc_handler
	b 	_exception_exit

EmptyStub:
	bl	_exception_entry
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

	mrs	x1, spsr_el1
	mrs	x2, elr_el1
	mrs	x3, daif
	mrs	x4, vbar_el1
	mrs	x5, esr_el1
	sub	x6, sp, #(8*30)
	mrs	x7, sctlr_el1
	#mrs	x8, hcr_el1
	mrs	x9, ttbr0_el1

	stp x2, x0, [sp, #-16]!
	stp	x3, x1, [sp, #-16]!
	stp	x5, x4, [sp, #-16]!
	stp	x7, x6, [sp, #-16]!
	stp	x9, x8, [sp, #-16]!
	mov	x0, sp
	ret

_exception_exit:
	add	sp, sp, #(8*6)
	ldp	x2, x0, [sp],#16
	msr	spsr_el1, x0
	ldp	x2, x0, [sp],#16
	msr	elr_el1, x2

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