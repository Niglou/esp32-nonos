#include <registers/specreg.h>

/* ********************* ISR ******************** */

#define INTR_STACK_SIZE 76

.macro intr_save_registers
    /* save in stack */
    mov     a0, sp
    addi    sp, sp, -INTR_STACK_SIZE
    s32i    a0, sp, 0
    s32i    a2, sp, 4
    s32i    a3, sp, 8
    s32i    a4, sp, 12
    s32i    a5, sp, 16
    s32i    a6, sp, 20
    s32i    a7, sp, 24
    s32i    a8, sp, 28
    s32i    a9, sp, 32
    s32i    a10, sp, 36
    s32i    a11, sp, 40
    s32i    a12, sp, 44
    s32i    a13, sp, 48
    s32i    a14, sp, 52
    s32i    a15, sp, 56
    rsr     a2, LBEG
    s32i    a2, sp,  60
    rsr     a2, LEND
    s32i    a2, sp,  64
    rsr     a2, LCOUNT
    s32i    a2, sp,  68
    rsr     a2, SAR
    s32i    a2, sp,  72
    /* set LCOUNT register to 0 */
    movi    a2, 0
    wsr     a2, LCOUNT
    isync
.endm

.macro intr_restore_registers
    /* restore register */
    l32i    a2, sp,  60
    wsr     a2, LBEG
    l32i    a2, sp,  64
    wsr     a2, LEND
    l32i    a2, sp,  68
    wsr     a2, LCOUNT
    l32i    a2, sp,  72
    wsr     a2, SAR
    isync

    l32i    a2, sp, 4
    l32i    a3, sp, 8
    l32i    a4, sp, 12
    l32i    a5, sp, 16
    l32i    a6, sp, 20
    l32i    a7, sp, 24
    l32i    a8, sp, 28
    l32i    a9, sp, 32
    l32i    a10, sp, 36
    l32i    a11, sp, 40
    l32i    a12, sp, 44
    l32i    a13, sp, 48
    l32i    a14, sp, 52
    l32i    a15, sp, 56
    l32i    sp, sp, 0
.endm


/* INTR LVL 2 */
    .text
    .global     xt_highint2
    .type       xt_highint2,@function
    .align      4
xt_highint2:
    /* clear interrupt */
    movi    a0, ((1<<29) | (1<<20) | (1<<21))
    wsr.intclear a0
    rsync

    /* save state before interrupt */
    intr_save_registers

    /* Set PS register WOE UM INTLEVEL */
    movi    a3, 0x40022
    wsr     a3, ps
    rsync

    /* Call C handler */
    call4   ISR_LVL2

    /* restore state before interrupt */
    intr_restore_registers

    /* Quit interrupt */
    rsr     a0, EXCSAVE_2
    rfi     2


/* INTR LVL 3 */
    .text
    .global     xt_highint3
    .type       xt_highint3,@function
    .align      4
xt_highint3:
    /* clear interrupt */
    movi    a0, ((1<<11) | (1<<15) | (1<<22) | (1<<23) | (1<<27) | (1<<29))
    wsr.intclear a0
    rsync

    /* save state before interrupt */
    intr_save_registers

    /* Set PS register WOE UM INTLEVEL */
    movi    a3, 0x40023
    wsr     a3, ps
    rsync

    /* Call C handler */
    call4   ISR_LVL3

    /* restore state before interrupt */
    intr_restore_registers

    /* Quit interrupt */
    rsr     a0, EXCSAVE_3
    rfi     3


/* INTR LVL 4 */
    .text
    .global     xt_highint4
    .type       xt_highint4,@function
    .align      4
xt_highint4:
    /* clear interrupt */
    movi    a0, ((1<<24) | (1<<25) | (1<<28))
    wsr.intclear a0
    rsync

    /* save state before interrupt */
    intr_save_registers

    /* Set PS register WOE UM INTLEVEL */
    movi    a3, 0x40024
    wsr     a3, ps
    rsync

    /* Call C handler */
    call4   ISR_LVL4

    /* restore state before interrupt */
    intr_restore_registers

    /* Quit interrupt */
    rsr     a0, EXCSAVE_4
    rfi     4


/* INTR LVL 5 */
    .text
    .global     xt_highint5
    .type       xt_highint5,@function
    .align      4
xt_highint5:
    /* clear interrupt */
    movi    a0, ((1<<16) | (1<<26) | (1<<31))
    wsr.intclear a0
    rsync

    /* save state before interrupt */
    intr_save_registers

    /* Set PS register WOE UM INTLEVEL */
    movi    a3, 0x40025
    wsr     a3, ps
    rsync

    /* Call C handler */
    call4   ISR_LVL5

    /* restore state before interrupt */
    intr_restore_registers

    /* Quit interrupt */
    rsr     a0, EXCSAVE_5
    rfi     5


/* INTR LVL 6 */
    .text
    .global     xt_highint6
    .type       xt_highint6,@function
    .align      4
xt_highint6:
    /* Quit interrupt */
    rsr     a0, EXCSAVE_6
    rfi     6


/* INTR LVL NMI */
    .text
    .global     xt_nmi
    .type       xt_nmi,@function
    .align      4
xt_nmi:
    /* Quit interrupt */
    rsr     a0, EXCSAVE_7
    rfi     7
