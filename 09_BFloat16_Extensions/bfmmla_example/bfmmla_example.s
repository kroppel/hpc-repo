        .text
        .align 4
        .type bfmmla_example, %function
        .global bfmmla_example

        /*
         * Perform bfmmla instruction on 256 bit input vectors A und B
         * and write result to C
         *
         * @param x1 pointer to A
         * @param x2 pointer to B
         * @param x3 pointer to C
         */ 
bfmmla_example:
        ptrue p0.b

        ld1w {z0}, p0/z, [x0]
        ld1w {z1}, p0/z, [x2]
        ld1w {z2}, p0/z, [x2]

        bfmmla 

        st1w {z2}, p0, [x2]
        
        ret
        .size bfmmla_example, (. - bfmmla_example)

