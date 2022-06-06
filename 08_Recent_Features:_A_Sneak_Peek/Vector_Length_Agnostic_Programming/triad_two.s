        .text
        .align 4
        .type triad_two, %function
        .global triad_two

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
triad_two:
        mov x4, #0

        whilelt p0.s, x4, x0
        b.none end_loop
        fmov z5.s, #2
loop:   
        ld1w {z0.s}, p0/z, [x1,x4, lsl #2]
        ld1w {z1.s}, p0/z, [x2,x4, lsl #2]

        fmla z0.s, p0/m, z5.s, z1.s
        st1w z0.s, p0, [x3, x4, lsl #2]
        incw x4
        whilelt p0.s, x4, x0
        b.any loop
end_loop:
        ret
        .size triad_two, (. - triad_two)

