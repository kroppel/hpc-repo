        .text
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

        /*ptrue p0.h, VL16
        ptrue p1.h, VL16
        ptrue p2.s, VL8

        ld1w {z0.s}, p0/z, [x0]
        ld1w {z1.s}, p1/z, [x1] 
        ld1w {z2.s}, p2/z, [x2]*/

        ldr z0, [x0]
        ldr z1, [x1]
        ld1 z2, [x2]


        bfmmla z2.s, z0.h, z1.h

        str z2, [x2]

        //st1w {z2.s}, p2, [x2]
        ret
        .size bfmmla_example, (. - bfmmla_example)

