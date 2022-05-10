#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>
#include "gemm-ref.h"

int main() {
  // input matrices for benchmark
  int i_m = 2; 
  int i_n = 2; 
  int i_k = 3;
  int i_lda = 2;
  int i_ldb = 3;
  int i_ldc = 2;
  float mat_a[6] = {1,2,3,1,2,3};
  float mat_b[6] = {1,2,1,2,1,2};
  float mat_c[6] = {0,0,0,0,0,0};

  // benchmark config
  int n_repetitions = 1000000;

  // NR of operations
  int n_gflops = (i_m*i_n*i_k*2) * n_repetitions;

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < n_repetitions; i++) {
    gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_b, i_ldc);
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time = end - start;
  std::cout << "Benchmark of Reference Kernel:\n";
  std::cout << "    GFLOPS: " << n_gflops/time << "\n";

  return EXIT_SUCCESS;
}
