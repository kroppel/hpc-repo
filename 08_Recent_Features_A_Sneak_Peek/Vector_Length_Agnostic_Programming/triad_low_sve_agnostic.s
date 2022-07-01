        .text
        .type triad_low_sve_agnostic, %function
        .global triad_low_sve_agnostic

        /*
         * Performs the STREAM triad C=A + s*B
         * on vectors of common length
         * with fixed scalar s
         *
         * @param x0 vector length
         * @param x1 pointer to A
         * @param x2 pointer to B
         * @param x3 pointer to C
         */ 

triad_low_sve_agnostic:
        ptrue p0.s
        eor x5, x5, x5 // constantly zero
        eor x4, x4, x4 // + accumulate of p0
        fmov z3.s, p0/m, #2

repeat: 
        eor x4, x4, x4 // constantly zero
        whilelt p0.s, x5, x0 // set at most @{x0} entries of p0

        ld1w {z1.s}, p0/z, [x1] // get next part of A
        ld1w {z2.s}, p0/z, [x2] // get next part of B
        fmla z1.s, p0/m, z2.s, z3.s // triad for current part: z1 = z1 + z2*z3
        st1w {z1.s}, p0, [x3] // write results back

        incp x4, p0.s // number of items processed in this iteration
        addvl x1, x1, #1
        addvl x2, x2, #1
        addvl x3, x3, #1
        subs x0, x0, x4 // number of remaining items to be processed
        //cmp x0, x5
        b.gt repeat

        ret
        .size triad_low_sve_agnostic, (. - triad_low_sve_agnostic)
