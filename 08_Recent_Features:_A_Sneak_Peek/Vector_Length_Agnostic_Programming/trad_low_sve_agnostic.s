        .text
        .type triad_low_sve_agnostic, %function
        .global triad_low_sve_agnostic

        /*
         * Performs the STREAM triad C=A + s*B
         * on vectors of common length
         * with fixed scalar s
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 

triad_low_sve_agnostic:
        // set predicate register to true
        ptrue p0.b


        ret
        .size triad_low_sve_agnostic, (. - triad_low_sve_agnostic)
