        .text
        .type gemm_asm_sve_128_6_48, %function
        .global gemm_asm_sve_128_6_48

        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (128x6) = (128x48) * (48x6).
         * The input-data is of type float.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 

gemm_asm_sve_128_6_48:
        // set predicate register to true
        ptrue p0.b

        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!

        stp d8, d9, [sp, #-16]!
        stp d10, d11, [sp, #-16]!
        stp d12, d13, [sp, #-16]!
        stp d14, d15, [sp, #-16]!
        
        // initialize loop_m var to 128
        mov x4, #128
GEMM_LOOP_M:
        sub x4, x4, #64

        // Load C
        ldr z0, [x2,#0,MUL VL]
        ldr z1, [x2,#1,MUL VL]
        ldr z2, [x2,#2,MUL VL]
        ldr z3, [x2,#3,MUL VL]

        ldr z4, [x2,#8,MUL VL]
        ldr z5, [x2,#9,MUL VL]
        ldr z6, [x2,#10,MUL VL]
        ldr z7, [x2,#11,MUL VL]

        ldr z8, [x2,#16,MUL VL]
        ldr z9, [x2,#17,MUL VL]
        ldr z10, [x2,#18,MUL VL]
        ldr z11, [x2,#19,MUL VL]

        ldr z12, [x2,#24,MUL VL]
        ldr z13, [x2,#25,MUL VL]
        ldr z14, [x2,#26,MUL VL]
        ldr z15, [x2,#27,MUL VL]

        ldr z16, [x2,#32,MUL VL]
        ldr z17, [x2,#33,MUL VL]
        ldr z18, [x2,#34,MUL VL]
        ldr z19, [x2,#35,MUL VL]

        ldr z20, [x2,#40,MUL VL]
        ldr z21, [x2,#41,MUL VL]
        ldr z22, [x2,#42,MUL VL]
        ldr z23, [x2,#43,MUL VL]

        // initialize loop_k var to 48
        mov x3, #48

GEMM_LOOP_K:
        subs x3, x3, #1
        
        //load B
        ld1rw {z24.s}, p0/z, [x1]
        add x1, x1, #4*48
        ld1rw {z25.s}, p0/z, [x1]
        add x1, x1, #4*48
        ld1rw {z26.s}, p0/z, [x1]
        add x1, x1, #4*48
        ld1rw {z27.s}, p0/z, [x1]
        add x1, x1, #4*48
        ld1rw {z28.s}, p0/z, [x1]
        add x1, x1, #4*48
        ld1rw {z29.s}, p0/z, [x1]
        sub x1, x1, #4*48*5
        add x1, x1, #4


        //load first half of A
        ldr z30, [x0]
        add x0, x0, #16*4
        ldr z31, [x0]
        add x0, x0, #16*4

        //first part of calculation C += AB

        //first 16 values from A
        fmla z0.s, p0/m, z24.s, z30.s
        fmla z4.s, p0/m, z25.s, z30.s
        fmla z8.s, p0/m, z26.s, z30.s
        fmla z12.s, p0/m, z27.s, z30.s
        fmla z16.s, p0/m, z28.s, z30.s
        fmla z20.s, p0/m, z29.s, z30.s

        //second 16 values from A
        fmla z1.s, p0/m, z24.s, z31.s
        fmla z5.s, p0/m, z25.s, z31.s
        fmla z9.s, p0/m, z26.s, z31.s
        fmla z13.s, p0/m, z27.s, z31.s
        fmla z17.s, p0/m, z28.s, z31.s
        fmla z21.s, p0/m, z29.s, z31.s


        //load second half of A
        ldr z30, [x0]
        add x0, x0, #16*4
        ldr z31, [x0]
        add x0, x0, #16*4*5


        //second part of calculation C += AB

        //third 16 values from A
        fmla z2.s, p0/m, z24.s, z30.s
        fmla z6.s, p0/m, z25.s, z30.s
        fmla z10.s, p0/m, z26.s, z30.s
        fmla z14.s, p0/m, z27.s, z30.s
        fmla z18.s, p0/m, z28.s, z30.s
        fmla z22.s, p0/m, z29.s, z30.s

        //fourth 16 values from A
        fmla z3.s, p0/m, z24.s, z31.s
        fmla z7.s, p0/m, z25.s, z31.s
        fmla z11.s, p0/m, z26.s, z31.s
        fmla z15.s, p0/m, z27.s, z31.s
        fmla z19.s, p0/m, z28.s, z31.s
        fmla z23.s, p0/m, z29.s, z31.s

        cbnz x3, GEMM_LOOP_K
        
        // store C
        str z0, [x2,#0,MUL VL]
        str z1, [x2,#1,MUL VL]
        str z2, [x2,#2,MUL VL]
        str z3, [x2,#3,MUL VL]

        str z4, [x2,#8,MUL VL]
        str z5, [x2,#9,MUL VL]
        str z6, [x2,#10,MUL VL]
        str z7, [x2,#11,MUL VL]

        str z8, [x2,#16,MUL VL]
        str z9, [x2,#17,MUL VL]
        str z10, [x2,#18,MUL VL]
        str z11, [x2,#19,MUL VL]

        str z12, [x2,#24,MUL VL]
        str z13, [x2,#25,MUL VL]
        str z14, [x2,#26,MUL VL]
        str z15, [x2,#27,MUL VL]

        str z16, [x2,#32,MUL VL]
        str z17, [x2,#33,MUL VL]
        str z18, [x2,#34,MUL VL]
        str z19, [x2,#35,MUL VL]

        str z20, [x2,#40,MUL VL]
        str z21, [x2,#41,MUL VL]
        str z22, [x2,#42,MUL VL]
        str z23, [x2,#43,MUL VL]

        // Prepare addresses for next loop_m iteration
        sub x0, x0, #48*128*4
        add x0, x0, #64*4
        sub x1, x1, #48*4
        add x2, x2, #64*4

        cbnz x4, GEMM_LOOP_M

        ldp d14, d15, [sp], #16
        ldp d12, d13, [sp], #16
        ldp d10, d11, [sp], #16
        ldp d8, d9, [sp], #16
        

        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_sve_128_6_48, (. - gemm_asm_sve_128_6_48)
