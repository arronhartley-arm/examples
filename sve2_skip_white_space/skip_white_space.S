/* Copyright (c) 2019-2020 Arm Limited (or its affiliates). All rights reserved. */
/* Use, modification and redistribution of this file is subject to your possession of a     */
/* valid End User License Agreement for the Arm Product of which these examples are part of */
/* and your compliance with all applicable terms and conditions of such licence agreement.  */

    .cfi_sections .debug_frame  // put stack frame info into .debug_frame instead of .eh_frame

    .global DisableSveTraps
    .type DisableSveTraps, "function"
    .cfi_startproc
// Disable all SVE and SIMD traps by setting CPTR_EL3.EZ bit [8] and clearing CPTR_EL3.TFP bit [10]
DisableSveTraps:
    MRS x3, cptr_el3
    BIC x3, x3, #(1<<10)
    ORR x3, x3, #(1<<8)
    MSR cptr_el3, x3
    ISB
    RET
    .cfi_endproc

    .global SkipWhiteSpace
    .type SkipWhiteSpace, "function"
    .cfi_startproc
// SVE2 optimized assembler version of SkipWhiteSpace
SkipWhiteSpace:
    MOV w3, #0xD090000
    ADD w3, w3, #0xA20
    MOV z1.s, w3 // 0x0D090A20, ascii for '\r\t\n '
    WHILELT p0.b, x0, x1

.L_start:
    LD1B z0.b, p0/Z, [x0]
    NMATCH p1.b, p0/z, z0.b, z1.b
    B.ANY .L_spacesEnd
    INCB x0
    WHILELT p0.b, x0, x1
    B.FIRST .L_start

    MOV x0, x1
    B .L_return

    .L_spacesEnd:
    BRKB p2.b, p0/z, p1.b
    INCP x0, p2.b

    .L_return:
    MOV x2, x0
    RET
    .cfi_endproc
