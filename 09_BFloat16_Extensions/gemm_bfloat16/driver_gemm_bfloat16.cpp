#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>
#include <chrono>
#include <arm_bf16.h>
#include <arm_neon.h>

extern "C" {
    void gemm_bfloat16( bfloat16_t const * i_a,
                        bfloat16_t const * i_b,
                        float            * io_c );
}

void convert_a_to_bfmmla( uint64_t           i_m,
                          uint64_t           i_n,
                          uint64_t           i_ld,
                          bfloat16_t const * i_a_col_major,
                          bfloat16_t       * o_a_fmmla )
{
  for (int at = 0; at < i_n*i_m; ++at)
    o_a_fmmla[i_m*(at%i_n) + (int)at/i_n] = i_a_col_major[at];
}

void convert_b_to_bfmmla( uint64_t           i_m,
                          uint64_t           i_n,
                          uint64_t           i_ld,
                          bfloat16_t const * i_b_col_major,
                          bfloat16_t       * o_b_fmmla )
{
  for (int at = 0; at < i_n*i_m; ++at)
    o_b_fmmla[at] = i_b_col_major[at];
}

void convert_c_to_bfmmla( uint64_t         i_m,
                          uint64_t         i_n,
                          uint64_t         i_ld,
                          float    const * i_c_col_major,
                          float          * o_c_fmmla )
{
  int blkpos, cblk, rite, blk;
  for (int at = 0; at < i_n*i_m; ++at)
  {
    cblk = (int)at/32;
    blkpos = at % 32;
    rite = (int)blkpos/16;
    blkpos %= 16;
    blk = blkpos/2;
    blkpos %= 2;
    o_c_fmmla[32*cblk + 2*rite + 4*blk + blkpos] = i_c_col_major[at];
  }
}
void convert_c_from_bfmmla( uint64_t         i_m,
                            uint64_t         i_n,
                            uint64_t         i_ld,
                            float    const * i_c_fmmla,
                            float          * o_c_col_major )
{
  int blkpos, cblk, rite, blk;
  for (int at = 0; at < i_n*i_m; ++at)
  {
    cblk = (int)at/32;
    blkpos = at % 32;
    rite = (int)blkpos/16;
    blkpos %= 16;
    blk = blkpos/2;
    blkpos %= 2;
    o_c_col_major[at] = i_c_fmmla[32*cblk + 2*rite + 4*blk + blkpos];
  }
}

void gemm_ref( float        const * i_a,
               float        const * i_b,
               float              * io_c,
               unsigned int         i_m,
               unsigned int         i_n,
               unsigned int         i_k,
               unsigned int         i_lda,
               unsigned int         i_ldb,
               unsigned int         i_ldc) {
    for (unsigned int m = 0; m < i_m; m++) {
        for (unsigned int n = 0; n < i_n; n++) {
            for (unsigned int k = 0; k < i_k; k++) {
                io_c[n*i_ldc+m] += i_a[k*i_lda+m]*i_b[n*i_ldb+k];
            }
        }
    }
}

double mat_diff_sum(float * c1, float * c2, unsigned int m, unsigned int n) {
    double diff = 0;
    for (unsigned int i = 0; i < n*m; i++) {
        diff += std::abs(c1[i]-c2[i]);
    }
    return diff;
}

void benchmark_gemm_bfloat16() {
    std::cout << "Run benchmark gemm_bfloat16\n";

    // variables for time measurement
    std::chrono::high_resolution_clock::time_point l_tp0;
    std::chrono::high_resolution_clock::time_point l_tp1;
    std::chrono::duration<double> l_dur;
    unsigned long l_n_repetitions;
    double l_gflops = 0;

    // Matrizen A, B, C
    bfloat16_t * l_a = (bfloat16_t*) malloc(16*4*2);
    bfloat16_t * l_b = (bfloat16_t*) malloc(4*12*2);
    float l_c[16*12] = {0};

    // Matrizen für reference kernel
    float l_a_ref[16*4] = {0};
    float l_b_ref[4*12] = {0};
    float l_c_ref[16*12] = {0};

    // fill matrices
    srand48(time(NULL));
    for (int i = 0; i < 16*4; i++) {
        float el_a = (float) drand48();
        l_a[i] = vcvth_bf16_f32(el_a);
        l_a_ref[i] = vcvtah_f32_bf16(vcvth_bf16_f32(el_a));
    }
    for (int i = 0; i < 4*12; i++) {
        float el_b = (float) drand48();
        l_b[i] = vcvth_bf16_f32(el_b);
        l_b_ref[i] = vcvtah_f32_bf16(vcvth_bf16_f32(el_b));
    }



    /*
     * SVE BFLOAT: 16,12,4
     */

    l_n_repetitions = 1000;

    // run reference implementation
    gemm_ref(   l_a_ref, 
                l_b_ref,
                l_c_ref,
                16,
                12,
                4,
                16,
                4,
                16);


    // run kernel for validation and dry run
    gemm_bfloat16(  l_a,
                    l_b,
                    l_c );

    //testing for correctness
    double diff = mat_diff_sum(l_c, l_c_ref, 16, 12);
    std::cout << "Difference is " << diff << "\n";
    assert(diff < 0.005);

    // time measurement for SVE kernel

    l_tp0 = std::chrono::high_resolution_clock::now();
    for( unsigned int l_re = 0; l_re < l_n_repetitions; l_re++){
        gemm_bfloat16( l_a,
                       l_b,
                       l_c);
    }
    
    l_tp1 = std::chrono::high_resolution_clock::now();

    l_dur = std::chrono::duration_cast<std::chrono::duration<double>> (l_tp1 - l_tp0);

    std::cout << " duration: " << l_dur.count() << " seconds" << "\n";
    std::cout << " #executions: " << l_n_repetitions << std::endl;
    l_gflops = l_n_repetitions;
    l_gflops *= 16 * 12 * 4 * 2;
    l_gflops *= 1.0E-9;
    l_gflops /= l_dur.count();
    std::cout << " GFLOPS: " << l_gflops << std::endl;
    // 2.6 GHZ -> processor speed of graviton3
    std::cout << " %PEAK: " << l_gflops/(2.6*2*2*16) << std::endl;

    free(l_a);
    free(l_b);
}



int main(){

    benchmark_gemm_bfloat16();

    return EXIT_SUCCESS;    
}

