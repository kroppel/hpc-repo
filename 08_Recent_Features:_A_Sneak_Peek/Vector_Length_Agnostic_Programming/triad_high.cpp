#include "triad_high.h"

void triad_high( uint64_t         i_nValues,
                 float    const * i_a,
                 float    const * i_b,
                 float          * o_c ) {

  for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
  }
}