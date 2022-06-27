#include <iostream>
#include <cmath>
#include <chrono>
#include "kernels/triad.h"

/**
 * Benchmarks the different triad-implementations.
 *
 * @param i_nValues number of values in each of the arrays.
 * @param i_nRepeats nubmer of times the triads are executed.
 * @param i_type id of the triead-implementation.
 **/
void bench( uint64_t i_nValues,
            uint64_t i_nRepeats,
            int      i_type ) {
  // vars
  std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;
  std::chrono::duration<double> l_dur;
  double l_gflops = 0;
  double l_gibs = 0;

  // allocate memory
  float * l_a = new float[i_nValues];
  float * l_b = new float[i_nValues];
  float * l_c = new float[i_nValues];

  // init data
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for( uint64_t l_en = 0; l_en < i_nValues; l_en++ ) {
    l_a[l_en] = l_b[l_en] = l_c[l_en] = 1;
  }

  l_tp0 = std::chrono::high_resolution_clock::now();
  if( i_type == 0 ) {
    for( uint64_t l_re = 0; l_re < i_nRepeats; l_re++ ) {
      triad_simple( i_nValues,
                    l_a,
                    l_b,
                    l_c );
    }
  }
  l_tp1 = std::chrono::high_resolution_clock::now();

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  performance:" << std::endl;
  std::cout << "    duration: " << l_dur.count() << " seconds" << std::endl;
  l_gflops = i_nRepeats * i_nValues * 2.0;
  l_gflops /= l_dur.count() * 1E9;
  std::cout << "    GFLOPS: " << l_gflops << std::endl;
  l_gibs = i_nRepeats * i_nValues * 4 * 3;
  l_gibs /= 1024.0 * 1024.0 * 1024.0 * l_dur.count();
  std::cout << "    GiB/s: " << l_gibs << std::endl;

  // free memory
  delete[] l_a;
  delete[] l_b;
  delete[] l_c;
}

int main( int i_argc, char const * i_argv[] ) {
  // parse command line arguments
  if( i_argc != 3 ) {
    std::cerr << "use as: ./build/auto_vec N_VALUES N_REPEATS" << std::endl;
    return EXIT_FAILURE;
  }
  uint64_t l_nValues = atoll( i_argv[1] );
  uint64_t l_nRepeats = atoll( i_argv[2] );

  std::cout << "working with:" << std::endl;
  std::cout << "  N_VALUES: " << l_nValues;
  std::cout << "; this means " << l_nValues*4 / (1024.0*1024.0)
            << " MiB per array" << std::endl;
  std::cout << "  N_REPEATS: " << l_nRepeats << std::endl;

  std::cout << "benchmarking triad_simple" << std::endl;
  bench( l_nValues,
         l_nRepeats,
         0 );

  return EXIT_SUCCESS;
}
