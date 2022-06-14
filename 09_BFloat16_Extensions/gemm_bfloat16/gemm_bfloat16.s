        .text
        .type gemm_bfloat16, %function
        .global gemm_bfloat16

        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (63x6) = (63x48) * (48x6).
         * The input-data is of type float.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 

gemm_bfloat16:
        // set predicate register to true
        ptrue p0.b

        ret
        .size gemm_bfloat16, (. - gemm_bfloat16)
