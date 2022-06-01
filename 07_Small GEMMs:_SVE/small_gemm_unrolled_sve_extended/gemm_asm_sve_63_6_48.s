        .text
        .type gemm_asm_sve_63_6_48, %function
        .global gemm_asm_sve_63_6_48

        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (63x6) = (63x48) * (48x6).
         * The input-data is of type float.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 

gemm_asm_sve_63_6_48:
        // set predicate register to true
        ptrue p0.b

        mov x5, #0
        mov x6, #15

        whilelt p1.s, x5, x6

        //matrix kernel64
        ldr z0, [x2]
        add x2, x2, #16*4
        ldr z1, [x2]
        add x2, x2, #16*4
        ldr z2, [x2]
        add x2, x2, #16*4
        ld1w {z3.s}, p1/z, [x2]
        add x2, x2, #15*4

        ldr z4, [x2]
        add x2, x2, #16*4
        ldr z5, [x2]
        add x2, x2, #16*4
        ldr z6, [x2]
        add x2, x2, #16*4
        ld1w {z7.s}, p1/z, [x2]
        add x2, x2, #15*4

        ldr z8, [x2]
        add x2, x2, #16*4
        ldr z9, [x2]
        add x2, x2, #16*4
        ldr z10, [x2]
        add x2, x2, #16*4
        ld1w {z11.s}, p1/z, [x2]
        add x2, x2, #15*4

        ldr z12, [x2]
        add x2, x2, #16*4
        ldr z13, [x2]
        add x2, x2, #16*4
        ldr z14, [x2]
        add x2, x2, #16*4
        ld1w {z15.s}, p1/z, [x2]
        add x2, x2, #15*4

        ldr z16, [x2]
        add x2, x2, #16*4
        ldr z17, [x2]
        add x2, x2, #16*4
        ldr z18, [x2]
        add x2, x2, #16*4
        ld1w {z19.s}, p1/z, [x2]
        add x2, x2, #15*4

        ldr z20, [x2]
        add x2, x2, #16*4
        ldr z21, [x2]
        add x2, x2, #16*4
        ldr z22, [x2]
        add x2, x2, #16*4
        ld1w {z23.s}, p1/z, [x2]
        sub x2, x2, #6*3*16*4 + 5*15*4

        // initialize loop var to 0
        eor x4, x4, x4
GEMM_LOOP:
        
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
        ld1w {z31.s}, p1/z, [x0]
        add x0, x0, #15*4

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


        add x4, x4, #1
        cmp x4, #47
        B.NE GEMM_LOOP

        // ###### last iteration of gemm_loop unrolled #####

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
        str z0, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z4.s, p0/m, z25.s, z30.s
        str z4, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z8.s, p0/m, z26.s, z30.s
        str z8, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z12.s, p0/m, z27.s, z30.s
        str z12, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z16.s, p0/m, z28.s, z30.s
        str z16, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z20.s, p0/m, z29.s, z30.s
        str z20, [x2]
        sub x2, x2, #16*4*15+15*20-16*4

        //second 16 values from A
        fmla z1.s, p0/m, z24.s, z31.s
        str z1, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z5.s, p0/m, z25.s, z31.s
        str z5, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z9.s, p0/m, z26.s, z31.s
        str z9, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z13.s, p0/m, z27.s, z31.s
        str z13, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z17.s, p0/m, z28.s, z31.s
        str z17, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z21.s, p0/m, z29.s, z31.s
        str z21, [x2]
        sub x2, x2, #16*4*15+15*20-16*4


        //load second half of A
        ldr z30, [x0]
        add x0, x0, #16*4
        ld1w {z31.s}, p1/z, [x0]
        add x0, x0, #15*4

        //second part of calculation C += AB

        //third 16 values from A
        fmla z2.s, p0/m, z24.s, z30.s
        str z2, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z6.s, p0/m, z25.s, z30.s
        str z6, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z10.s, p0/m, z26.s, z30.s
        str z10, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z14.s, p0/m, z27.s, z30.s
        str z14, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z18.s, p0/m, z28.s, z30.s
        str z18, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z22.s, p0/m, z29.s, z30.s
        str z22, [x2]
        sub x2, x2, #16*4*15+15*20-16*4

        //fourth 16 values from A
        fmla z3.s, p0/m, z24.s, z31.s
        st1w z3.s, p1, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z7.s, p0/m, z25.s, z31.s
        st1w z7.s, p1, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z11.s, p0/m, z26.s, z31.s
        st1w z11.s, p1, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z15.s, p0/m, z27.s, z31.s
        st1w z15.s, p1, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z19.s, p0/m, z28.s, z31.s
        st1w z19.s, p1, [x2]
        add x2, x2, #16*4*3+15*4
        fmla z23.s, p0/m, z29.s, z31.s
        st1w z23.s, p1, [x2]



        ret
        .size gemm_asm_sve_63_6_48, (. - gemm_asm_sve_63_6_48)
