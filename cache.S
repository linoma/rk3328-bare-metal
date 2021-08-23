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

.section ".text"

#define ARM64_WORKAROUND_CLEAN_CACHE		0
.macro	dcache_line_size, reg, tmp
	mrs	\tmp, ctr_el0			// read CTR
	ubfm	\tmp, \tmp, #16, #19		// cache line size encoding
	mov	\reg, #4			// bytes per word
	lsl	\reg, \reg, \tmp		// actual cache line size
	.endm

.macro dcache_by_line_op op, domain, kaddr, size, tmp1, tmp2
	dcache_line_size \tmp1, \tmp2
	add	\size, \kaddr, \size
	sub	\tmp2, \tmp1, #1
	bic	\kaddr, \kaddr, \tmp2
9998:
	.if	(\op == cvau || \op == cvac)
alternative_if_not ARM64_WORKAROUND_CLEAN_CACHE
	dc	\op, \kaddr
alternative_else
	dc	civac, \kaddr
alternative_endif
	.else
	dc	\op, \kaddr
	.endif
	add	\kaddr, \kaddr, \tmp1
	cmp	\kaddr, \size
	b.lo	9998b
	dsb	\domain
	.endm

.globl __flush_dcache_area
__flush_dcache_area:
	dcache_by_line_op civac, sy, x0, x1, x2, x3
	ret