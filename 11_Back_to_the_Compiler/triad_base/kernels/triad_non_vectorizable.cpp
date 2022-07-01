#include "triad_non_vectorizable.h"

void triad_non_vectorizable( uint64_t         i_nValues,
                   float    const * i_a,
                   float    const * i_b,
                   float          * o_c ) {
  for( uint64_t l_va = 0; l_va <= i_nValues-1; l_va++ ) {
    if (l_va % 3 > 1)  
      o_c[l_va] = i_a[l_va] + multiply_dummy(2.0f, i_b + l_va);
    else {
      i_b++;
      o_c[l_va] = i_a[l_va] + multiply_dummy(2.0f, i_b + l_va-1);
      i_b--;
    }
  }
}