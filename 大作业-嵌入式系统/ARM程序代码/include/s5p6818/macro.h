#ifndef __MACRO_H__
#define __MACRO_H__

#define L1_CACHE_SHIFT      6
#define L1_CACHE_BYTES      (1 << L1_CACHE_SHIFT)

#define CPU_BE(code...)
#define CPU_LE(code...) code

#define ASM_NL       ;
#define SYMBOL_NAME(X)      X
#define SYMBOL_NAME_LABEL(X)    X:
#ifndef __ALIGN
#define __ALIGN .align      4
#endif

#ifndef __ALIGN_STR
#define __ALIGN_STR     ".align 4"
#endif

#define ALIGN           __ALIGN
#define ALIGN_STR       __ALIGN_STR

#define LENTRY(name) \
    ALIGN ASM_NL \
    SYMBOL_NAME_LABEL(name)

#define ENTRY(name) \
    .globl SYMBOL_NAME(name) ASM_NL \
    LENTRY(name)

#define WEAK(name) \
    .weak SYMBOL_NAME(name) ASM_NL \
    LENTRY(name)

#ifndef END
#define END(name) \
    .size name, .-name
#endif

#ifndef ENDPROC
#define ENDPROC(name) \
    .type name STT_FUNC ASM_NL \
    END(name)
#endif


.macro  switch_el, xreg, el3_label, el2_label, el1_label
    mrs \xreg, CurrentEL
    cmp \xreg, 0xc
    b.eq    \el3_label
    cmp \xreg, 0x8
    b.eq    \el2_label
    cmp \xreg, 0x4
    b.eq    \el1_label
.endm

.macro armv8_switch_to_el2_m, xreg1
    /* 64bit EL2 | HCE | SMD | RES1 (Bits[5:4]) | Non-secure EL0/EL1 */
    mov \xreg1, #0x5b1
    msr scr_el3, \xreg1
    msr cptr_el3, xzr       /* Disable coprocessor traps to EL3 */
    mov \xreg1, #0x33ff
    msr cptr_el2, \xreg1    /* Disable coprocessor traps to EL2 */

    /* Initialize Generic Timers */
    msr cntvoff_el2, xzr

    /* Initialize SCTLR_EL2
     *
     * setting RES1 bits (29,28,23,22,18,16,11,5,4) to 1
     * and RES0 bits (31,30,27,26,24,21,20,17,15-13,10-6) +
     * EE,WXN,I,SA,C,A,M to 0
     */
    mov \xreg1, #0x0830
    movk    \xreg1, #0x30C5, lsl #16
    msr sctlr_el2, \xreg1

    /* Return to the EL2_SP2 mode from EL3 */
    mov \xreg1, sp
    msr sp_el2, \xreg1      /* Migrate SP */
    mrs \xreg1, vbar_el3
    msr vbar_el2, \xreg1    /* Migrate VBAR */
    mov \xreg1, #0x3c9
    msr spsr_el3, \xreg1    /* EL2_SP2 | D | A | I | F */
    msr elr_el3, x30
    eret
.endm

.macro  branch_if_master, xreg1, xreg2, master_label
    /* NOTE: MPIDR handling will be erroneous on multi-cluster machines */
    mrs \xreg1, mpidr_el1
    lsr \xreg2, \xreg1, #32
    lsl \xreg1, \xreg1, #40
    lsr \xreg1, \xreg1, #40
    orr \xreg1, \xreg1, \xreg2
    cbz \xreg1, \master_label
.endm

#endif

