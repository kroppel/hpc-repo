#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>
#include <chrono>

extern "C" {
    void gemm_asm_sve_64_6_1(   float const * i_a,
                                float const * i_b,
                                float       * io_c );
    void gemm_asm_sve_64_6_1_opt(   float const * i_a,
                                float const * i_b,
                                float       * io_c );
    void gemm_asm_sve_64_6_48(   float const * i_a,
                                float const * i_b,
                                float       * io_c );
    void gemm_asm_sve_64_6_48_opt(   float const * i_a,
                                float const * i_b,
                                float       * io_c );
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
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            //std::cout << c1[i*n+j]-c2[i*n+j] << "\n";
            diff += std::abs(c1[i*n+j]-c2[i*n+j]);
        }
    }
    return diff;
}

void benchmark_gemm_asm_sve_64_6_1() {
    std::cout << "Run benchmark gemm_asm_sve_64_6_1\n";

    //variables for time measurement
    std::chrono::high_resolution_clock::time_point l_tp0;
    std::chrono::high_resolution_clock::time_point l_tp1;
    std::chrono::duration<double> l_dur;
    unsigned long l_n_repetitions;
    double l_gflops = 0;

    //Matrizen A, B, C
    float l_a[64] = {0};
    float l_b[6] = {0};
    
    float l_c_ref[6*64] = {0};

    float l_c[6*64] = {0};

    // fill matrices
    srand48(time(NULL));
    for (int i = 0; i < 64; i++) {
        l_a[i] = (float) drand48();
    }
    for (int i = 0; i < 6; i++) {
        l_b[i] = (float) drand48();
    }


    /*
     * SVE: 64,6,1
     */

    l_n_repetitions = 50000000;

    // run reference implementation
    gemm_ref(   l_a, 
                l_b,
                l_c_ref,
                64,
                6,
                1,
                64,
                1,
                64);


    // run kernel for validation and dry run
    gemm_asm_sve_64_6_1(    l_a,
                            l_b,
                            l_c );

    //testing for correctness
    double diff = mat_diff_sum(l_c, l_c_ref, 64, 6);
    std::cout << "Difference is " << diff << "\n";
    assert(diff < 0.05);

    // time measurement for SVE kernel

    l_tp0 = std::chrono::high_resolution_clock::now();
    for(    unsigned int l_re = 0; l_re < l_n_repetitions; l_re++){
        gemm_asm_sve_64_6_1 (   l_a,
                                l_b,
                                l_c );
    }
    
    l_tp1 = std::chrono::high_resolution_clock::now();

    l_dur = std::chrono::duration_cast<std::chrono::duration<double>> (l_tp1 - l_tp0);

    std::cout << " duration: " << l_dur.count() << " seconds" << "\n";
    l_gflops = l_n_repetitions;
    l_gflops *= 64 * 6 * 1 * 2;
    l_gflops *= 1.0E-9;
    l_gflops /= l_dur.count();
    std::cout << " GFLOPS: " << l_gflops << std::endl;
}

void benchmark_gemm_asm_sve_64_6_1_opt() {
    std::cout << "Run benchmark gemm_asm_sve_64_6_1_opt\n";

    //variables for time measurement
    std::chrono::high_resolution_clock::time_point l_tp0;
    std::chrono::high_resolution_clock::time_point l_tp1;
    std::chrono::duration<double> l_dur;
    unsigned long l_n_repetitions;
    double l_gflops = 0;

    //Matrizen A, B, C
    float l_a[64] = {0};
    float l_b[6] = {0};
    
    float l_c_ref[6*64] = {0};

    float l_c[6*64] = {0};

    // fill matrices
    srand48(time(NULL));
    for (int i = 0; i < 64; i++) {
        l_a[i] = (float) drand48();
    }
    for (int i = 0; i < 6; i++) {
        l_b[i] = (float) drand48();
    }


    /*
     * SVE: 64,6,1
     */

    l_n_repetitions = 50000000;

    // run reference implementation
    gemm_ref(   l_a, 
                l_b,
                l_c_ref,
                64,
                6,
                1,
                64,
                1,
                64);


    // run kernel for validation and dry run
    gemm_asm_sve_64_6_1_opt(    l_a,
                            l_b,
                            l_c );

    //testing for correctness
    double diff = mat_diff_sum(l_c, l_c_ref, 64, 6);
    std::cout << "Difference is " << diff << "\n";
    assert(diff < 0.05);


    // time measurement for SVE kernel

    l_tp0 = std::chrono::high_resolution_clock::now();
    for(    unsigned int l_re = 0; l_re < l_n_repetitions; l_re++){
        gemm_asm_sve_64_6_1_opt (   l_a,
                                l_b,
                                l_c );
    }
    
    l_tp1 = std::chrono::high_resolution_clock::now();

    l_dur = std::chrono::duration_cast<std::chrono::duration<double>> (l_tp1 - l_tp0);

    std::cout << " duration: " << l_dur.count() << " seconds" << "\n";
    l_gflops = l_n_repetitions;
    l_gflops *= 64 * 6 * 1 * 2;
    l_gflops *= 1.0E-9;
    l_gflops /= l_dur.count();
    std::cout << " GFLOPS: " << l_gflops << std::endl;
}

void benchmark_gemm_asm_sve_64_6_48() {
    std::cout << "Run benchmark gemm_asm_sve_64_6_48\n";

    //variables for time measurement
    std::chrono::high_resolution_clock::time_point l_tp0;
    std::chrono::high_resolution_clock::time_point l_tp1;
    std::chrono::duration<double> l_dur;
    unsigned long l_n_repetitions;
    double l_gflops = 0;

    //Matrizen A, B, C
    float l_a[64*48] = {0};
    float l_b[48*6] = {0};
    
    float l_c_ref[6*64] = {0};

    float l_c[6*64] = {0};

    // fill matrices
    srand48(time(NULL));
    for (int i = 0; i < 64*48; i++) {
        l_a[i] = (float) drand48();
    }
    for (int i = 0; i < 48*6; i++) {
        l_b[i] = (float) drand48();
    }


    /*
     * SVE: 64,6,1
     */

    l_n_repetitions = 5000000;

    // run reference implementation
    gemm_ref(   l_a, 
                l_b,
                l_c_ref,
                64,
                6,
                48,
                64,
                48,
                64);


    // run kernel for validation and dry run
    gemm_asm_sve_64_6_48(    l_a,
                            l_b,
                            l_c );

    //testing for correctness
    double diff = mat_diff_sum(l_c, l_c_ref, 64, 6);
    std::cout << "Difference is " << diff << "\n";
    assert(diff < 0.05);

    // time measurement for SVE kernel

    l_tp0 = std::chrono::high_resolution_clock::now();
    for(    unsigned int l_re = 0; l_re < l_n_repetitions; l_re++){
        gemm_asm_sve_64_6_48 (   l_a,
                                l_b,
                                l_c );
    }
    
    l_tp1 = std::chrono::high_resolution_clock::now();

    l_dur = std::chrono::duration_cast<std::chrono::duration<double>> (l_tp1 - l_tp0);

    std::cout << " duration: " << l_dur.count() << " seconds" << "\n";
    l_gflops = l_n_repetitions;
    l_gflops *= 64 * 6 * 48 * 2;
    l_gflops *= 1.0E-9;
    l_gflops /= l_dur.count();
    std::cout << " GFLOPS: " << l_gflops << std::endl;
}

void benchmark_gemm_asm_sve_64_6_48_opt() {
    std::cout << "Run benchmark gemm_asm_sve_64_6_48_opt\n";

    //variables for time measurement
    std::chrono::high_resolution_clock::time_point l_tp0;
    std::chrono::high_resolution_clock::time_point l_tp1;
    std::chrono::duration<double> l_dur;
    unsigned long l_n_repetitions;
    double l_gflops = 0;

    //Matrizen A, B, C
    float l_a[64*48] = {0};
    float l_b[48*6] = {0};
    
    float l_c_ref[6*64] = {0};

    float l_c[6*64] = {0};

    // fill matrices
    srand48(time(NULL));
    for (int i = 0; i < 64*48; i++) {
        l_a[i] = (float) drand48();
    }
    for (int i = 0; i < 48*6; i++) {
        l_b[i] = (float) drand48();
    }


    /*
     * SVE: 64,6,1
     */

    l_n_repetitions = 5000000;

    // run reference implementation
    gemm_ref(   l_a, 
                l_b,
                l_c_ref,
                64,
                6,
                48,
                64,
                48,
                64);


    // run kernel for validation and dry run
    gemm_asm_sve_64_6_48_opt(    l_a,
                            l_b,
                            l_c );

    //testing for correctness
    double diff = mat_diff_sum(l_c, l_c_ref, 64, 6);
    std::cout << "Difference is " << diff << "\n";
    assert(diff < 0.05);

    // time measurement for SVE kernel

    l_tp0 = std::chrono::high_resolution_clock::now();
    for(    unsigned int l_re = 0; l_re < l_n_repetitions; l_re++){
        gemm_asm_sve_64_6_48_opt (   l_a,
                                l_b,
                                l_c );
    }
    
    l_tp1 = std::chrono::high_resolution_clock::now();

    l_dur = std::chrono::duration_cast<std::chrono::duration<double>> (l_tp1 - l_tp0);

    std::cout << " duration: " << l_dur.count() << " seconds" << "\n";
    l_gflops = l_n_repetitions;
    l_gflops *= 64 * 6 * 48 * 2;
    l_gflops *= 1.0E-9;
    l_gflops /= l_dur.count();
    std::cout << " GFLOPS: " << l_gflops << std::endl;
}



int main(){

    benchmark_gemm_asm_sve_64_6_1();
    benchmark_gemm_asm_sve_64_6_1_opt();
    benchmark_gemm_asm_sve_64_6_48();
    benchmark_gemm_asm_sve_64_6_48_opt();

    return EXIT_SUCCESS;    
}

