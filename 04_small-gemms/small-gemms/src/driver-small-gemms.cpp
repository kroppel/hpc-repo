#include <cstdint>
#include <cmath>
#include <chrono>
#include <iostream>
#include "gemm-ref.h"

int main() {
  // input matrices for benchmark

  int lambdas[8] = {4,8,12,16,24,32,48,64};

  for (int lambda:lambdas) {

    int i_m = lambda; gemm_compiler_32_32_32_32_32_32_mnk( float const * i_a,
                                          float const * i_b,
                                          float       * io_c )
    float mat_a[i_m*i_k] = {2};
    float mat_b[i_k*i_n] = {3};
    float mat_c[i_m*i_n] = {0};

    // benchmark config
    //long n_repetitions = 10;
    long n_repetitions = (long) 10E8/(i_m*i_n*i_k*2);

    // NR of operations
    long n_gflops = (i_m*i_n*i_k*2) * n_repetitions;

    // Dry Run
    gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n_repetitions; i++) {
      gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_s = end - start;
    std::chrono::duration<double, std::milli> time_ms = end - start;
    
    std::cout << "Benchmark of Reference Kernel:\n";
    std::cout << "    Dim: " << lambda << "\n";
    std::cout << "    n_gflops: " << n_gflops << "\n";
    std::cout << "    time: " << time_s.count() << "s\n";
    std::cout << "    GFLOPS: " << n_gflops/(10E9 * time_s.count()) << "\n";
    std::cout << "    Average Kernel Duration: " << time_s.count()/n_repetitions << "\n";

  }

  return EXIT_SUCCESS;
}
