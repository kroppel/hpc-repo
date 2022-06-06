#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>
#include <chrono>
#include "triad_high.h"

extern "C" {
    void triad_low_sve_agnostic( uint64_t         i_nValues,
                float    const * i_a,
                float    const * i_b,
                float          * o_c );
}

double mat_diff_sum(float * c1, float * c2, unsigned int m, unsigned int n) {
    double diff = 0;
    for (unsigned int i = 0; i < n*m; i++) {
        diff += std::abs(c1[i]-c2[i]);
    }
    return diff;
}

void benchmark_triad_low() {
    std::cout << "Run benchmark triad_low\n";

    //variables for time measurement
    std::chrono::high_resolution_clock::time_point l_tp0;
    std::chrono::high_resolution_clock::time_point l_tp1;
    std::chrono::duration<double> l_dur;
    unsigned long l_n_repetitions;
    double l_gflops = 0;
    uint64_t nValues = 100;

    //Vectors A, B, C
    float l_a[nValues] = {0};
    float l_b[nValues] = {0};
    
    float l_c_ref[nValues] = {0};

    float l_c[nValues] = {0};

    // fill vectors
    srand48(time(NULL));
    for (unsigned int i = 0; i < nValues; i++) {
        l_a[i] = (float) drand48();
    }
    for (unsigned int i = 0; i < nValues; i++) {
        l_b[i] = (float) drand48();
    }


    l_n_repetitions = 20000;

    // run reference implementation
    triad_high(nValues, l_a, l_b, l_c_ref);


    // run kernel for validation and dry run
    triad_low_sve_agnostic(nValues, l_a, l_b, l_c);

    //testing for correctness
    double diff = mat_diff_sum(l_c, l_c_ref, nValues, 1);
    std::cout << "Difference is " << diff << "\n";
    assert(diff < 0.05);

    // time measurement for SVE kernel

    l_tp0 = std::chrono::high_resolution_clock::now();
    for(unsigned int l_re = 0; l_re < l_n_repetitions; l_re++){
        triad_low_sve_agnostic(nValues, l_a, l_b, l_c);
    }
    
    l_tp1 = std::chrono::high_resolution_clock::now();

    l_dur = std::chrono::duration_cast<std::chrono::duration<double>> (l_tp1 - l_tp0);

    std::cout << " duration: " << l_dur.count() << " seconds" << "\n";
    std::cout << " #executions: " << l_n_repetitions << std::endl;
    l_gflops = l_n_repetitions;
    l_gflops *= nValues * 2;     // nValues -> Anzahl der werte in jedem Vektor; 2 -> FMLA
    l_gflops *= 1.0E-9;
    l_gflops /= l_dur.count();
    std::cout << " GFLOPS: " << l_gflops << std::endl;
    std::cout << " %PEAK: " << l_gflops/(1.8*2*2*16) << std::endl;
}


int main(){

    benchmark_triad_low();

    return EXIT_SUCCESS;    
}

