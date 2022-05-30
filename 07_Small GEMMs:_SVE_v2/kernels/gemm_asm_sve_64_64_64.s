        .text
        .type gemm_asm_sve_64_64_64, %function
        .global gemm_asm_sve_64_64_64
        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (64x64) = (64x64) * (64x64).
         * The input-data is of type float.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 
gemm_asm_sve_64_64_64:
        // set predicate register to true
        ptrue p0.b

        // store
        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!

        stp  d8,  d9, [sp, #-16]!
        stp d10, d11, [sp, #-16]!
        stp d12, d13, [sp, #-16]!
        stp d14, d15, [sp, #-16]!

        // n loop index
        mov x5, #64
loop_n:

        // load 4*64 accumulate-block of C
        ldr z0, [x2]
        add x2, x2, #16*4
        ldr z1, [x2]
        add x2, x2, #16*4
        ldr z2, [x2]
        add x2, x2, #16*4
        ldr z3, [x2]
        add x2, x2, #16*4

        ldr z4, [x2]
        add x2, x2, #16*4
        ldr z5, [x2]
        add x2, x2, #16*4
        ldr z6, [x2]
        add x2, x2, #16*4
        ldr z7, [x2]
        add x2, x2, #16*4

        ldr z8, [x2]
        add x2, x2, #16*4
        ldr z9, [x2]
        add x2, x2, #16*4
        ldr z10, [x2]
        add x2, x2, #16*4
        ldr z11, [x2]
        add x2, x2, #16*4

        ldr z12, [x2]
        add x2, x2, #16*4
        ldr z13, [x2]
        add x2, x2, #16*4
        ldr z14, [x2]
        add x2, x2, #16*4
        ldr z15, [x2]
        sub x2, x2, #15*16*4

        // k loop index
        mov x3, #64
loop_k:
        // boradcast 4 entries of B
        // each entry is mutliplied by 64 entries of A
        ld1rw {z16.s}, p0/z, [x1]
        add x1, x1, #64*4
        ld1rw {z17.s}, p0/z, [x1]
        add x1, x1, #64*4
        ld1rw {z18.s}, p0/z, [x1]
        add x1, x1, #64*4
        ld1rw {z19.s}, p0/z, [x1]
        sub x1, x1, #3*64*4 - 4

        // load 64 entries of A
        ldr z20, [x0]
        add x0, x0, #16*4
        ldr z21, [x0]
        add x0, x0, #16*4
        ldr z22, [x0]
        add x0, x0, #16*4
        ldr z23, [x0]
        add x0, x0, #16*4

        // perform the fmas
        fmla  z0.s, p0/m, z20.s, z16.s
        fmla  z1.s, p0/m, z21.s, z16.s
        fmla  z2.s, p0/m, z22.s, z16.s
        fmla  z3.s, p0/m, z23.s, z16.s

        fmla  z4.s, p0/m, z20.s, z17.s
        fmla  z5.s, p0/m, z21.s, z17.s
        fmla  z6.s, p0/m, z22.s, z17.s
        fmla  z7.s, p0/m, z23.s, z17.s

        fmla  z8.s, p0/m, z20.s, z18.s
        fmla  z9.s, p0/m, z21.s, z18.s
        fmla z10.s, p0/m, z22.s, z18.s
        fmla z11.s, p0/m, z23.s, z18.s

        fmla z12.s, p0/m, z20.s, z19.s
        fmla z13.s, p0/m, z21.s, z19.s
        fmla z14.s, p0/m, z22.s, z19.s
        fmla z15.s, p0/m, z23.s, z19.s

        sub x3, x3, #1
        cbnz x3, loop_k

        // store 4*64 accumulate-block of C
        str z0, [x2]
        add x2, x2, #16*4
        str z1, [x2]
        add x2, x2, #16*4
        str z2, [x2]
        add x2, x2, #16*4
        str z3, [x2]
        add x2, x2, #16*4

        str z4, [x2]
        add x2, x2, #16*4
        str z5, [x2]
        add x2, x2, #16*4
        str z6, [x2]
        add x2, x2, #16*4
        str z7, [x2]
        add x2, x2, #16*4

        str z8, [x2]
        add x2, x2, #16*4
        str z9, [x2]
        add x2, x2, #16*4
        str z10, [x2]
        add x2, x2, #16*4
        str z11, [x2]
        add x2, x2, #16*4

        str z12, [x2]
        add x2, x2, #16*4
        str z13, [x2]
        add x2, x2, #16*4
        str z14, [x2]
        add x2, x2, #16*4
        str z15, [x2]
        add x2, x2, #16*4

        // adjust A- and B-ptr
        sub x0, x0, #64*64*4
        add x1, x1, #3*64*4


        sub x5, x5, #4
        cbnz x5, loop_n

        // restore
        ldp d14, d15, [sp], #16
        ldp d12, d13, [sp], #16
        ldp d10, d11, [sp], #16
        ldp  d8,  d9, [sp], #16

        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_sve_64_64_64, (. - gemm_asm_sve_64_64_64)
