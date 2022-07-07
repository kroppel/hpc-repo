#include "triad_offloading.h"
#include <atomic>
#include <stdio.h>
#include <omp.h>

void triad_offloading( uint64_t         i_nValues,
                   float    const * i_a,
                   float    const * i_b,
                   float          * o_c,
                   const int number_of_teams,
                   const int number_of_threads) {
#pragma omp target teams num_teams(number_of_teams)
#pragma omp parallel for num_threads(number_of_threads)
  for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
  }

}
