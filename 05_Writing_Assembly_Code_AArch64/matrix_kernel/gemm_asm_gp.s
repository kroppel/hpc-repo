	.text
        .type gemm_asm_gp, %function
        .global gemm_asm_gp
        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (4x2) = (4x2) * (2x2).
         * The input-data is of type uint32_t.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 

gemm_asm_gp:
        // store
        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!

        //matrix-kernel

        //load C

        ldp w3, w4,   [x2       ]
        ldp w5, w6,   [x2,    #8]
        ldp w7, w8,   [x2,   #16]
        ldp w9, w10,  [x2,   #24]

        //load first column from A

        ldp w11, w12,   [x0      ]
        ldp w13, w14,   [x0, #2*4]

        //load first entry from B

        ldr w15,  [x1, #0]


        //calculation

        madd w3, w11, w15, w3
        madd w4, w12, w15, w4
        madd w5, w13, w15, w5
        madd w6, w14, w15, w6

        //load second entry from B

        ldr w15,  [x1, #0]






        // restore
        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_gp, (. - gemm_asm_gp)

