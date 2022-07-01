#include "gemm_compiler_32_32_32_32_32_32.h"

void gemm_compiler_32_32_32_32_32_32_mnk( float const * i_a,
                                          float const * i_b,
                                          float       * io_c ) {
    for (int m = 0; m < 32; m++) {
        for (int n = 0; n < 32; n++) {
            for (int k = 0; k < 32; k++) {
                io_c[n*32+m] += i_a[k*32+m]*i_b[n*32+k];
            }
        }
    }
}

void gemm_compiler_32_32_32_32_32_32_nkm( float const * i_a,
                                          float const * i_b,
                                          float       * io_c ) {
    for (int n = 0; n < 32; n++) {
        for (int k = 0; k < 32; k++) {
            for (int m = 0; m < 32; m++) {
                io_c[n*32+m] += i_a[k*32+m]*i_b[n*32+k];
            }
        }
    }
}