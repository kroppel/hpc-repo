#ifndef __gemm_ref_include__
#define __gemm_ref_include__

void gemm_compiler_32_32_32_32_32_32_mnk( float const * i_a,
                                          float const * i_b,
                                          float       * io_c );

void gemm_compiler_32_32_32_32_32_32_nkm( float const * i_a,
                                          float const * i_b,
                                          float       * io_c );

#endif