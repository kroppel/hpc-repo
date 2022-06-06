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

        eor x29, x29, x29 // constantly zero
        eor x4, x4, x4 // + accumulate of p0
        fmov x6, #2.0

repeat: whilelt p0.s x29, x0 // set at most @{x0} entries of p0

        ld1w p0/z w1, [x1] // get next part of A
        ld1w p0/z w2, [x2] // get next part of B
        fmla p0 w1, w2, x6 // triad for current part: w1 = w2*x6 + w1
        st1w p0/m w1, [x3] // write results back

        incw p0, x4 // number of items processed in this iteration
        add x1, x1, x4
        add x2, x2, x4
        add x3, x3, x4
        subs x0, x0, x4 // number of remaining items to be processed
        // cmp x0 x29
        b.ne repeat
endrep:

        ret
        .size triad_low_sve_agnostic, (. - triad_low_sve_agnostic)
