/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <s5p6818/macro.h>

.macro  disable_dbg
msr daifset, #8
.endm

.macro  enable_dbg
msr daifclr, #8
.endm

/*
 * Enter Exception.
 * This will save the processor state that is ELR/X0~X30
 * to the stack frame.
 */
.macro	exception_entry
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

	/* Could be running at EL3/EL2/EL1 */
	switch_el x11, 3f, 2f, 1f
3:	mrs	x1, esr_el3
	mrs	x2, elr_el3
	b	0f
2:	mrs	x1, esr_el2
	mrs	x2, elr_el2
	b	0f
1:	mrs	x1, esr_el1
	mrs	x2, elr_el1
0:
	stp	x2, x0, [sp, #-16]!
	mov	x0, sp
.endm

/*
 * Exception vectors.
 */
	.align	11
	.globl	vectors
vectors:
	.align	7
	b	_do_bad_sync	/* Current EL Synchronous Thread */

	.align	7
	b	_do_bad_irq	/* Current EL IRQ Thread */

	.align	7
	b	_do_bad_fiq	/* Current EL FIQ Thread */

	.align	7
	b	_do_bad_error	/* Current EL Error Thread */

	.align	7
	b	_do_sync	/* Current EL Synchronous Handler */

	.align	7
	b	_do_irq		/* Current EL IRQ Handler */

	.align	7
	b	_do_fiq		/* Current EL FIQ Handler */

	.align	7
	b	_do_error	/* Current EL Error Handler */


_do_bad_sync:
	exception_entry
	bl	do_bad_sync

_do_bad_irq:
	exception_entry
	bl	do_bad_irq

_do_bad_fiq:
	exception_entry
	bl	do_bad_fiq

_do_bad_error:	
	exception_entry
	bl	do_bad_error

#define ESR_ELx_EC_SHIFT    (26)
#define ESR_ELx_EC_SVC64    (0x15)
#define ESR_ELx_EC_DABT_LOW (0x24)
#define ESR_ELx_EC_IABT_LOW (0x20)
#define ESR_ELx_EC_FP_ASIMD (0x07)
#define ESR_ELx_EC_FP_EXC64 (0x2C)
#define ESR_ELx_EC_SYS64    (0x18)
#define ESR_ELx_EC_SP_ALIGN (0x26)
#define ESR_ELx_EC_PC_ALIGN (0x22)
#define ESR_ELx_EC_UNKNOWN  (0x00)
#define ESR_ELx_EC_BREAKPT_LOW  (0x30)

_do_sync:
	mrs x25, esr_el2            // read the syndrome register
	lsr x24, x25, #ESR_ELx_EC_SHIFT // exception class
	cmp x24, #ESR_ELx_EC_SVC64      // SVC in 64-bit state
	b.eq    do_el2_svc
	cmp x24, #ESR_ELx_EC_DABT_LOW   // data abort in EL0
	b.eq    do_el2_da
	cmp x24, #ESR_ELx_EC_IABT_LOW   // instruction abort in EL0                                                                                                         
	b.eq    do_el2_ia
	cmp x24, #ESR_ELx_EC_FP_ASIMD   // FP/ASIMD access                            
	b.eq    do_el2_fpsimd_acc
	cmp x24, #ESR_ELx_EC_FP_EXC64   // FP/ASIMD exception                         
	b.eq    do_el2_fpsimd_exc
	cmp x24, #ESR_ELx_EC_SYS64      // configurable trap                          
	b.eq    do_el2_undef
	cmp x24, #ESR_ELx_EC_SP_ALIGN   // stack alignment exception                  
	b.eq    do_el2_sp_pc
	cmp x24, #ESR_ELx_EC_PC_ALIGN   // pc alignment exception                     
	b.eq    do_el2_sp_pc
	cmp x24, #ESR_ELx_EC_UNKNOWN    // unknown exception in EL0                   
	b.eq    do_el2_undef
	cmp x24, #ESR_ELx_EC_BREAKPT_LOW    // debug exception in EL0
	enable_dbg
	b.ge    do_el2_dbg
	b   do_el2_inv

# exception_entry
# bl	do_sync

_do_el2_dbg:
# cmp x24, #ESR_ELx_EC_BRK64
# cinc    x24, x24, eq
	enable_dbg
	b _do_el2_dbg


_do_irq:
	exception_entry
	bl	do_irq

_do_fiq:
	exception_entry
	bl	do_fiq

_do_error:
	exception_entry
	bl	do_error
