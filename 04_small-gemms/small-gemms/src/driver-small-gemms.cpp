#include <cstdint>
#include <cmath>
#include <chrono>
#include <iostream>
#include "gemm-ref.h"
#include "gemm_compiler_32_32_32_32_32_32.h"

int main() {
  // Benchmark gemm_ref

  int lambdas[8] = {4,8,12,16,24,32,48,64};

  for (int lambda:lambdas) {

    int i_m = lambda;
    int i_n = lambda;
    int i_k = lambda;
    int i_lda = lambda;
    int i_ldb = lambda;
    int i_ldc = lambda;

    

    float mat_a[i_m*i_k] = {2};
    float mat_b[i_k*i_n] = {3};
    float mat_c[i_m*i_n] = {0};

    // benchmark config
    long n_repetitions = (long) 10E8/(i_m*i_n*i_k*2);

    // NR of operations
    long n_flops = (i_m*i_n*i_k*2) * n_repetitions;

    // Dry Run
    gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n_repetitions; i++) {
      gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_s = end - start;
    std::chrono::duration<double, std::milli> time_ms = end - start;
    
    std::cout << "Benchmark of gemm_ref:\n";
    std::cout << "    Dim: " << lambda << "\n";
    std::cout << "    GFLOPS: " << n_flops/(10E9 * time_s.count()) << "\n";
    std::cout << "    Average Kernel Duration: " << time_s.count()/n_repetitions << "\n";

  }
  
  // benchmark gemm_compiler_32_32_32_32_32_32_mnk

  float mat_a[32*32] = {2};
  float mat_b[32*32] = {3};
  float mat_c[32*32] = {0};

  // benchmark config
  long n_repetitions = 10000;

  // NR of operations
  long n_flops = (32*32*32) * n_repetitions;

  // Dry Run
  gemm_compiler_32_32_32_32_32_32_mnk(mat_a, mat_b, mat_c);

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < n_repetitions; i++) {
    gemm_compiler_32_32_32_32_32_32_mnk(mat_a, mat_b, mat_c);
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time_s = end - start;
  std::chrono::duration<double, std::milli> time_ms = end - start;
    
  std::cout << "Benchmark of gemm_compiler_32_32_32_32_32_32_mnk:\n";
  std::cout << "    n_flops: " << n_flops << "\n";
  std::cout << "    time: " << time_s.count() << "s\n";
  std::cout << "    GFLOPS: " << n_flops/(10E9 * time_s.count()) << "\n";
  std::cout << "    Average Kernel Duration: " << time_s.count()/n_repetitions << "\n";

  // benchmark gemm_compiler_32_32_32_32_32_32_nkm 

  mat_a[32*32] = {2};
  mat_b[32*32] = {3};
  mat_c[32*32] = {0};

  // benchmark config
  n_repetitions = 10000;

  // NR of operations
  n_flops = (32*32*32) * n_repetitions;

  // Dry Run
  gemm_compiler_32_32_32_32_32_32_nkm(mat_a, mat_b, mat_c);

  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < n_repetitions; i++) {
    gemm_compiler_32_32_32_32_32_32_nkm(mat_a, mat_b, mat_c);
  }
  end = std::chrono::high_resolution_clock::now();

  time_s = end - start;
  time_ms = end - start;
    
  std::cout << "Benchmark of gemm_compiler_32_32_32_32_32_32_nkm:\n";
  std::cout << "    n_flops: " << n_flops << "\n";
  std::cout << "    time: " << time_s.count() << "s\n";
  std::cout << "    GFLOPS: " << n_flops/(10E9 * time_s.count()) << "\n";
  std::cout << "    Average Kernel Duration: " << time_s.count()/n_repetitions << "\n";

  return EXIT_SUCCESS;
}
